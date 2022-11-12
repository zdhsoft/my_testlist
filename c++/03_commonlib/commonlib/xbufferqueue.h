#ifndef _X_BUFFER_QUEUE_H_
#define _X_BUFFER_QUEUE_H_
#include <xtype.h>
#include <xlog.h>
#include <xbuffer.h>
namespace zdh
{
    ///缓冲区环形队列
    class XBufferQueue
    {
    public:
        struct SQueueBufferHead
        {
            XInt   QueueHeadPos;      ///<队列头的位置
            XInt   QueueTailPos;      ///<队列尾的位置
            XInt   QueueBufferSize;   ///<队列可用Buffer字节数
            //XByte * QueueBuffer;       ///<队列可用buffer的地址
        };
        enum 
        {
            QUEUE_HEAD_SIZE         = sizeof(SQueueBufferHead), ///<队列尺寸大小
            QUEUE_MIN_BUFFER_SIZE   = QUEUE_HEAD_SIZE +100,     ///<最小缓冲区大小
        };
    public:
        XBufferQueue()
            :m_InitFlag(false),
             m_Buffer(NULL),
             m_BufferSize(0),
             m_QueueHead(NULL),
             m_QueueBuffer(NULL)
        {}
        ~XBufferQueue()
        {
            Close();
        }
        XInt Init(XByte * paramBuffer, XInt paramBufferSize, bool paramReset)
        {
            Close();
            if (paramBufferSize < QUEUE_MIN_BUFFER_SIZE)
            {
                ZDH_ERROR("The queue buffer is too small!, size=%lld", paramBufferSize);
                return -1;
            }
            
            if (isNULL(paramBuffer))
            {
                ZDH_ERROR("The queue buffer is NULL!");
                return -2;
            }
            
            m_Buffer        = paramBuffer;
            m_BufferSize    = paramBufferSize;
            m_QueueHead     = (SQueueBufferHead *)m_Buffer;
            if (paramReset)
            {
                MemoryZero(*m_QueueHead);
            }
            m_QueueBuffer                = m_Buffer + QUEUE_HEAD_SIZE;
            //m_QueueHead->QueueBuffer     = m_Buffer + QUEUE_HEAD_SIZE;
            m_QueueHead->QueueBufferSize = paramBufferSize - QUEUE_HEAD_SIZE;
            m_InitFlag = true;
            return ERR_OK;
        }

        XInt Close()
        {
            if (!m_InitFlag)
            {
                m_InitFlag = false;
            }
            return ERR_OK;
        }
        XInt Push(const void * paramData, XInt paramDataSize)
        {
            if (!m_InitFlag)
            {
                return ERR_FAIL;
            }
            SQueueBufferHead stHead = *m_QueueHead;
            XInt iWriteLength = paramDataSize;
            XInt iFreeBytes = GetFreeSize(stHead.QueueHeadPos, stHead.QueueTailPos, stHead.QueueBufferSize);
            const XByte * pData = (const XByte *)paramData;

            if (iFreeBytes < iWriteLength) //如果空间不够
            {
                return ERR_FAIL;
            }

            XInt iRightBytes = stHead.QueueBufferSize - stHead.QueueHeadPos;
            if (iRightBytes >= iWriteLength)
            {
                MemoryCopy(m_QueueBuffer + stHead.QueueHeadPos, pData, iWriteLength);
                m_QueueHead->QueueHeadPos = RoundPos(iWriteLength + stHead.QueueHeadPos, stHead.QueueBufferSize);
            }
            else
            {
                if(iRightBytes > 0)
                {
                    MemoryCopy(m_QueueBuffer + stHead.QueueHeadPos, pData, iRightBytes);
                    MemoryCopy(m_QueueBuffer, pData + iRightBytes, iWriteLength - iRightBytes);                
                    m_QueueHead->QueueHeadPos = iWriteLength - iRightBytes;
                }
                else
                {
                    MemoryCopy(m_QueueBuffer, pData, iWriteLength);
                    m_QueueHead->QueueHeadPos = iWriteLength;

                }
            }
            return ERR_OK;
        }
        //写入有用数据的时候，要e>s
        XInt Push(const XBuffer & paramBuffer)
        {
            return Push((const void *)paramBuffer.getData(), paramBuffer.getLength());
            //if (!m_InitFlag)
            //{
            //    return ERR_FAIL;
            //}
            //SQueueBufferHead stHead = *m_QueueHead;
            //XInt iWriteLength = paramBuffer.getLength();
            //XInt iFreeBytes = GetFreeSize(stHead.QueueHeadPos, stHead.QueueTailPos, stHead.QueueBufferSize);
            //const XByte * pData = paramBuffer->getData();

            //if (iFreeBytes < iWriteLength) //如果空间不够
            //{
            //    return ERR_FAIL;
            //}

            //XInt iRightBytes = stHead.QueueBufferSize - stHead.QueueHeadPos;
            //if (iRightBytes >= paramBuffer.getLength())
            //{
            //    MemoryCopy(stHead.QueueBuffer + stHead.QueueHeadPos, pData, iWriteLength);
            //    m_QueueHead->QueueHeadPos = RoundPos(iWriteLength + stHead.QueueHeadPos, stHead.QueueBufferSize);
            //}
            //else
            //{
            //    if(iRightBytes > 0)
            //    {
            //        MemoryCopy(stHead.QueueBuffer + stHead.QueueHeadPos, pData, iRightBytes);
            //        MemoryCopy(stHead.QueueBuffer, pData + iRightBytes, iWriteLength - iRightBytes);                
            //        m_QueueHead->QueueHeadPos = iWriteLength - iRightBytes;
            //    }
            //    else
            //    {
            //        MemoryCopy(stHead.QueueBuffer, pData, iWriteLength);
            //        m_QueueHead->QueueHeadPos = iWriteLength;

            //    }
            //}
            //return ERR_OK;
        }
        //取有用的数据的时候，要s>e
        //返回读取的字节数
        XInt Pop(XBuffer & paramBuffer)
        {
            if (!m_InitFlag)
            {
                return ERR_FAIL;
            }
            SQueueBufferHead stHead = *m_QueueHead;
            XInt iUseBytes = GetUseSize(stHead.QueueHeadPos, stHead.QueueTailPos, stHead.QueueBufferSize);
            paramBuffer.ensureCapacity(paramBuffer.getLength()+iUseBytes);

            XInt iRightBytes = stHead.QueueBufferSize - stHead.QueueTailPos;
            if (iRightBytes >= iUseBytes)
            {
                paramBuffer.AppendData(m_QueueBuffer + stHead.QueueTailPos, iUseBytes);
                m_QueueHead->QueueTailPos = RoundPos(stHead.QueueTailPos + iUseBytes, stHead.QueueBufferSize);
            }
            else
            {
                paramBuffer.AppendData(m_QueueBuffer + stHead.QueueTailPos, iRightBytes);
                paramBuffer.AppendData(m_QueueBuffer, iUseBytes - iRightBytes);
                m_QueueHead->QueueTailPos = iUseBytes - iRightBytes;
            }
            return iUseBytes;
        }

    public:
        XInt GetUseSize(XInt paramStart, XInt paramEnd, XInt paramSize)
        {
            if (paramStart < paramEnd)
            {
                paramStart += paramSize;
            }
            return paramStart - paramEnd;
        }
        XInt GetFreeSize(XInt paramStart, XInt paramEnd, XInt paramSize)
        {
            if (paramEnd <= paramStart)
            {
                paramEnd += paramSize;
            }
            return paramEnd - paramStart - 1;
        }
        XInt GetUseSize()
        {
            return GetUseSize(m_QueueHead->QueueHeadPos, m_QueueHead->QueueTailPos, m_QueueHead->QueueBufferSize);
        }
        XInt GetFreeSize()
        {
            return GetFreeSize(m_QueueHead->QueueHeadPos, m_QueueHead->QueueTailPos, m_QueueHead->QueueBufferSize);
        }
        XInt RoundPos(XInt paramPos, XInt paramSize)
        {
            if( paramPos < 0)
            {
                return paramPos + paramSize;
            }
            else if (paramPos >= paramSize)
            {
                return paramPos % paramSize;
            }
            else return paramPos;
        }
    public:
        bool                m_InitFlag;     
        XByte *             m_Buffer;
        XInt                m_BufferSize;
        SQueueBufferHead *  m_QueueHead;
        XByte            *  m_QueueBuffer;     
    };
}
#endif
