#ifndef _X_CODING_H_
#define _X_CODING_H_
#include <xtype.h>
#include <xstring.h>
#include <xbuffer.h>
#include <xdynamic_array.h>
namespace zdh
{
    //----------------------------------------------------------------------------------------
    ///编解码的常量
    enum EnumCodingConstant
    {
        ECC_MAX_STRING          = 4096,         ///<最大的字符串大小
        ECC_MAX_DATA            = 4096,         ///<最大的数据大小
        ECC_MAX_MESSAGE         = 128 * 1024,   ///<最大的消息大小
        ECC_MAX_ARRAY_LENGTH    = 4096,         ///<最大的动态数组大小
    };
    //----------------------------------------------------------------------------------------
    ///编解码的错误吗
    enum EnumCodingErrorCode
    {
        ECEC_NOT_ENOUGH_OF_DECODE       = 1,    ///<解码一个字段，所需的空间不够
        ECEC_INVALID_STRING_LENGTH      = 2,    ///<无效的字符串长度
        ECEC_INVALID_BUFFER_LENGTH      = 3,    ///<无效的Buffer长度
        ECEC_INVALID_ARRAY_LENGTH       = 4,    ///<无效的数组长度
    };
    #define CODING_BEGIN(class_name)    template<class Coding> \
                                        XInt ToCoding(const char  * paramName, Coding & c)  \
                                        {   \
                                            XInt iRet;  \
                                            XWord wVer = 0; \
                                            XInt  iVerPos = 0;\
                                            iRet = c.Begin(#class_name, paramName, wVer, iVerPos); \
                                            if (iRet != ERR_OK) { return iRet; }

                                            
    #define CODING_END(class_name)          iRet = c.End(#class_name, paramName, wVer, iVerPos); \
                                            if (iRet != ERR_OK) { return iRet; } \
                                            return ERR_OK; \
                                        }
                        


    #define CODING_VERSION(version_number)  iRet = c.VersionBegin(version_number, wVer); \
                                            if (iRet == ERR_OK) \
                                            {
    
    #define CODING_END_VERSION()            }

    #define CODING(field)                      { if ((iRet = c.Coding(#field, field)) != ERR_OK) return iRet; }
    #define TO_CODING(field)                   { if ((iRet = field.ToCoding(#field, c)) != ERR_OK) return iRet; }

    #define CODING_ARRAY(field)                { if ((iRet = c.CodingArray(#field, field)) != ERR_OK) return iRet; }
    #define TO_CODING_ARRAY(field)             { if ((iRet = c.ToCodingArray(#field, field)) != ERR_OK) return iRet; }
    #define CODING_DATA(data, coding_object)   data.ToCoding(#data, coding_object)
    
    //----------------------------------------------------------------------------------------
    ///编码错误信息结构体
    /**
     * 提供编码用的错误信息结构，用于方便使用
     * 
     * @author zdhsoft (2012/7/14)
     */
    struct SCodingError
    {
    public:
        SCodingError()
            :ErrorCode(ERR_OK)
        {
        }
        ///重置
        void Reset()
        {
            ErrorCode = ERR_OK;
            Msg.ToEmptyString();
        }
        ///设置错误信息
        /**
         * 设置错误信息
         * 
         * @author zdhsoft (2012/7/14)
         * 
         * @param paramErrorCode 错误代码
         * @param paramFormat 错误信息的格式
         */
        void ErrorFormat(XInt paramErrorCode, const char *paramFormat, ...)
        {
            ErrorCode = paramErrorCode;
            va_list ap;
            va_start(ap, paramFormat);
            Msg.vprintf(paramFormat, ap);
            va_end(ap);
        }
        ///设置错误信息
        /**
         * 设置错误信息
         * 
         * @author zdhsoft (2012/7/14)
         * 
         * @param paramErrorCode 错误代码
         * @param paramErrorMsg 错误信息
         */
        void Error(XInt paramErrorCode, const XAnsiString & paramErrorMsg)
        {
            ErrorCode = paramErrorCode;
            Msg = paramErrorMsg;
        }
    public:
        XInt ErrorCode;
        XAnsiString Msg;
    };
    //----------------------------------------------------------------------------------------
    ///错误编码基类
    /**
     * @author zdhsoft (2012/7/14)
     */
    class XCodingBase
    {
    public:
        SCodingError & getError() 
        {
            return m_Error;
        }
        const SCodingError & getError() const
        {
            return m_Error;
        }
    protected:
        SCodingError m_Error;       ///<错误信息
    };
    //----------------------------------------------------------------------------------------
    ///二进制编码类
    class XCoding_BinaryEncode : public XCodingBase
    {
    public:
        XCoding_BinaryEncode()
            :m_Buffer(NULL), m_BindBufferFlag(false)
        {
        }
        ~XCoding_BinaryEncode()
        {
            FreeBuffer();
        }
        ///设置缓冲区
        /**
         * 设置缓冲区，这个函数会释放已经绑定的buffer，请注意使用。 
         * 如果paramBindBufferFlag为true的时候，paramBuffer就和这个编码对象绑定了。这个对象会在 
         * 释放或重新设置的时候，将绑定的缓冲区对象释放。 
         * 如果paramBindBufferFlag为false的时候，paramBuffer这个对象仅是被这个对象使用。这个对象在 
         * 释放或重新设置缓冲区的时候，不会释放该缓冲区，使用者请注意释放这个缓冲区对象。 
         * 这样设置的原因，是减少数据的拷贝。 
         * 
         * @author zdhsoft (2012/7/14)
         * 
         * @param [in] paramBuffer 设置的缓冲区
         * @param [in] paramBindBufferFlag 绑定标志 
         *      - true 表示绑定缓冲区
         *      - false 表示不绑定缓冲区
         */
        void SetBuffer(XBuffer * paramBuffer, bool paramBindBufferFlag)
        {
            FreeBuffer();
            m_BindBufferFlag = paramBindBufferFlag;
            m_Buffer         = paramBuffer;
        }
        
        XBuffer * getBuffer()
        {
            return m_Buffer;
        }

        const XBuffer * getBuffer() const
        {
            return m_Buffer;
        }
        ///释放缓冲区
        /**
         * 只是释放绑定的缓冲区
         * 
         * @author zdhsoft (2012/7/14)
         */
        void FreeBuffer()
        {
            if (m_BindBufferFlag)
            {
                FreeObject(m_Buffer);
                m_BindBufferFlag = false;
            }
        }

        bool getBindBufferFlag() const
        {
            return m_BindBufferFlag;
        }

        void setBindBufferFlag(bool paramFlag) 
        {
            m_BindBufferFlag = paramFlag;
        }

        ///重置编码环境，可以用于重新编码
        void CodingReset()
        {
            if (isNotNULL(m_Buffer))
            {
                m_Buffer->Clear();
            }
        }
    public:
        XInt Begin(const char * /*paramClassName*/,const char * /*paramName*/, XWord & paramVer, XInt & paramVerPos)
        {
            paramVer = 0;
            paramVerPos = m_Buffer->getLength();
            m_Buffer->AppendWord(0);  
            return ERR_OK;
        }

        XInt End(const char * /*paramClassName*/, const char * /*paramName*/, XWord & paramVer, XInt & paramVerPos)
        {
            m_Buffer->WriteWord(paramVerPos, paramVer);
            return ERR_OK;
        }

        XInt VersionBegin(XWord paramVersion, XWord & paramVer)
        {
            ZDH_ASSERT(paramVer < paramVersion);
            paramVer = paramVersion;
            return ERR_OK;
        }

        //一组编码的函数
        XInt Coding(const char * /*paramName*/, XInt & paramValue)
        {
            m_Error.ErrorCode = ERR_OK;
            m_Buffer->AppendInt(paramValue);
            return m_Error.ErrorCode;
        }

        XInt Coding(const char * /*paramName*/, XDWord & paramValue)
        {
            m_Error.ErrorCode = ERR_OK;
            m_Buffer->AppendDWord(paramValue);
            return m_Error.ErrorCode;
        }

        XInt Coding(const char * /*paramName*/, XChar & paramValue)
        {
            m_Error.ErrorCode = ERR_OK;
            m_Buffer->AppendChar(paramValue);
            return m_Error.ErrorCode;
        }

        XInt Coding(const char * /*paramName*/, XByte & paramValue)
        {
            m_Error.ErrorCode = ERR_OK;
            m_Buffer->AppendByte(paramValue);
            return m_Error.ErrorCode;
        }

        XInt Coding(const char * /*paramName*/, XWord & paramValue)
        {
            m_Error.ErrorCode = ERR_OK;
            m_Buffer->AppendWord(paramValue);
            return m_Error.ErrorCode;
        }

        XInt Coding(const char * /*paramName*/, XShort & paramValue)
        {
            m_Error.ErrorCode = ERR_OK;
            m_Buffer->AppendShort(paramValue);
            return m_Error.ErrorCode;
        }

        XInt Coding(const char * /*paramName*/, XLong & paramValue)
        {
            m_Error.ErrorCode = ERR_OK;
            m_Buffer->AppendLong(paramValue);
            return m_Error.ErrorCode;
        }

        XInt Coding(const char * /*paramName*/, XDDWord & paramValue)
        {
            m_Error.ErrorCode = ERR_OK;
            m_Buffer->AppendDDWord(paramValue);
            return m_Error.ErrorCode;
        }

        XInt Coding(const char * /*paramName*/, XBool & paramValue)
        {
            m_Error.ErrorCode = ERR_OK;
            m_Buffer->AppendBool(paramValue);
            return m_Error.ErrorCode;
        }

        XInt Coding(const char * /*paramName*/, XFloat & paramValue)
        {
            m_Error.ErrorCode = ERR_OK;
            m_Buffer->AppendFloat(paramValue);
            return m_Error.ErrorCode;
        }

        XInt Coding(const char * /*paramName*/, XDouble & paramValue)
        {
            m_Error.ErrorCode = ERR_OK;
            m_Buffer->AppendDouble(paramValue);
            return m_Error.ErrorCode;
        }

        XInt Coding(const char * /*paramName*/, XAnsiString & paramString)
        {
            m_Error.ErrorCode = ERR_OK;
            m_Buffer->AppendInt(paramString.getLength());
            m_Buffer->AppendData(paramString.Data(), paramString.getLength());
            return m_Error.ErrorCode;
        }

        XInt Coding(const char * /*paramName*/, XBuffer & paramBuffer)
        {
            m_Error.ErrorCode = ERR_OK;
            m_Buffer->AppendInt(paramBuffer.getLength());
            m_Buffer->AppendBuffer(paramBuffer);
            return m_Error.ErrorCode;
        }

        template<class T>
        XInt CodingArray(const char * /*paramName*/, XDynamicArray<T> & paramValue)
        {
            m_Error.ErrorCode = ERR_OK;
            XInt iCount = paramValue.getLength();
            m_Buffer->AppendInt(iCount);
            for(XInt i = 0; i < iCount; i++)
            {
                Coding(NULL, paramValue[i]);
            }
            return m_Error.ErrorCode;
        }

        template<class T>
        XInt CodingArray(const char * /*paramName*/, XObjectArray<T> & paramValue)
        {
            m_Error.ErrorCode = ERR_OK;
            XInt iCount = paramValue.getLength();
            m_Buffer->AppendInt(iCount);
            for(XInt i = 0; i < iCount; i++)
            {
                Coding(NULL, paramValue[i]);
            }
            return m_Error.ErrorCode;
        }
        template<class T, int N>
        XInt CodingArray(const char * /*paramName*/, T (&paramValue)[N])
        {
            m_Error.ErrorCode = ERR_OK;
            m_Buffer->AppendInt(N);
            for(XInt i = 0; i < N; i++)
            {
                Coding(NULL, paramValue[i]);
            }
            return m_Error.ErrorCode;           
        }
        template<class T>
        XInt ToCodingArray(const char * /*paramName*/, XDynamicArray<T> & paramValue)
        {
            m_Error.ErrorCode = ERR_OK;
            XInt iCount = paramValue.getLength();
            m_Buffer->AppendInt(iCount);
            for(XInt i = 0; i < iCount; i++)
            {
                paramValue[i].ToCoding(NULL, *this);
            }
            return m_Error.ErrorCode;
        }

        template<class T>
        XInt ToCodingArray(const char * /*paramName*/, XObjectArray<T> & paramValue)
        {
            m_Error.ErrorCode = ERR_OK;
            XInt iCount = paramValue.getLength();
            m_Buffer->AppendInt(iCount);
            for(XInt i = 0; i < iCount; i++)
            {
                paramValue[i].ToCoding(NULL, *this);
            }
            return m_Error.ErrorCode;
        }
        template<class T, int N>
        XInt ToCodingArray(const char * /*paramName*/, T (&paramValue)[N])
        {
            m_Error.ErrorCode = ERR_OK;
            m_Buffer->AppendInt(N);
            for(XInt i = 0; i < N; i++)
            {
                paramValue[i].ToCoding(NULL, *this);
            }
            return m_Error.ErrorCode;           
        }
    private:        
        XBuffer * m_Buffer;             ///<编码缓冲区
        bool m_BindBufferFlag;          ///<绑定缓冲区标志 
    };
    //----------------------------------------------------------------------------------------
    class XCoding_BinaryDecode : public XCodingBase
    {
    public:
        XCoding_BinaryDecode()
            :m_Buffer(NULL), m_BindBufferFlag(false), m_Pos(0)
        {
        }
        ~XCoding_BinaryDecode()
        {
            FreeBuffer();
        }
        ///设置缓冲区
        /**
         * 设置缓冲区，这个函数会释放已经绑定的buffer，请注意使用。 
         * 如果paramBindBufferFlag为true的时候，paramBuffer就和这个编码对象绑定了。这个对象会在 
         * 释放或重新设置的时候，将绑定的缓冲区对象释放。 
         * 如果paramBindBufferFlag为false的时候，paramBuffer这个对象仅是被这个对象使用。这个对象在 
         * 释放或重新设置缓冲区的时候，不会释放该缓冲区，使用者请注意释放这个缓冲区对象。 
         * 这样设置的原因，是减少数据的拷贝。 
         * 
         * @author zdhsoft (2012/7/17)
         * 
         * @param [in] paramBuffer 设置的缓冲区
         * @param [in] paramBindBufferFlag 绑定标志 
         *      - true 表示绑定缓冲区
         *      - false 表示不绑定缓冲区
         */
        void SetBuffer(XBuffer * paramBuffer, bool paramBindBufferFlag, XInt paramPos = 0)
        {
            FreeBuffer();
            m_BindBufferFlag = paramBindBufferFlag;
            m_Buffer         = paramBuffer;
            m_Pos            = paramPos;
        }
        
        XBuffer * getBuffer()
        {
            return m_Buffer;
        }

        const XBuffer * getBuffer() const
        {
            return m_Buffer;
        }
        ///释放缓冲区
        /**
         * 只是释放绑定的缓冲区
         * 
         * @author zdhsoft (2012/7/14)
         */
        void FreeBuffer()
        {
            if (m_BindBufferFlag)
            {
                FreeObject(m_Buffer);
                m_BindBufferFlag = false;
                m_Pos = 0;
            }
        }

        bool getBindBufferFlag() const
        {
            return m_BindBufferFlag;
        }
        void setBindBufferFlag(bool paramFlag) 
        {
            m_BindBufferFlag = paramFlag;
        }
        //property pos
        XInt getPos() const
        {
            return m_Pos;
        }
        void setPos(XInt paramPos)
        {
            m_Pos = paramPos;
        }
        ///加偏移，返回最后的pos
        XInt AddPos(XInt paramPosOffset)
        {
            m_Pos += paramPosOffset;
            return m_Pos;
        }
        ///重置编码环境，可以用于重新编码
        void CodingReset()
        {
            m_Pos = 0;
        }
    public:
        XInt Begin(const char * paramClassName, const char * /*paramName*/, XWord & paramVer, XInt & /*paramVerPos*/)
        {
            if (CheckSize<XWord>())
            {
                paramVer = m_Buffer->ReadWord(m_Pos);
                m_Pos += (XInt)sizeof(XWord);
                m_Error.ErrorCode = ERR_OK;
            }
            else
            {
                m_Error.ErrorFormat(ECEC_NOT_ENOUGH_OF_DECODE, "class = %s,read version fail!", paramClassName);
            }
            return m_Error.ErrorCode;
        }

        XInt End(const char * /*paramClassName*/,const char * /*paramName*/, XWord & /*paramVer*/, XInt & /*paramVerPos*/)
        {
            return ERR_OK;
        }

        XInt VersionBegin(XWord paramVersion, XWord & paramVer)
        {
            if (paramVer >= paramVersion)
            {
                return ERR_OK;
            }
            else
            {
                return ERR_FAIL;
            }
        }

        template<class T>
        bool CheckSize()
        {
            return !(m_Buffer->getLength() < (m_Pos + (XInt)sizeof(T)));
        }
        //一组解码的函数
        XInt Coding(const char * /*paramName*/, XInt & paramValue)
        {
            if (CheckSize<XInt>())
            {
                paramValue = m_Buffer->ReadInt(m_Pos);
                m_Pos += (XInt)sizeof(paramValue);
                m_Error.ErrorCode = ERR_OK;
            }
            else
            {
                m_Error.ErrorCode = ECEC_NOT_ENOUGH_OF_DECODE;
            }
            return m_Error.ErrorCode;
        }
        //一组解码的函数
        XInt Coding(const char * /*paramName*/, XDWord & paramValue)
        {
            if (CheckSize<XDWord>())
            {
                paramValue = m_Buffer->ReadDWord(m_Pos);
                m_Pos += (XInt)sizeof(paramValue);
                m_Error.ErrorCode = ERR_OK;
            }
            else
            {
                m_Error.ErrorCode = ECEC_NOT_ENOUGH_OF_DECODE;
            }
            return m_Error.ErrorCode;
        }

        XInt Coding(const char * /*paramName*/, XChar & paramValue)
        {
            if (CheckSize<XChar>())
            {
                paramValue = m_Buffer->ReadChar(m_Pos);
                m_Pos += (XInt)sizeof(paramValue);
                m_Error.ErrorCode = ERR_OK;
            }
            else
            {
                m_Error.ErrorCode = ECEC_NOT_ENOUGH_OF_DECODE;
            }
            return m_Error.ErrorCode;
        }

        XInt Coding(const char * /*paramName*/, XByte & paramValue)
        {
            if (CheckSize<XByte>())
            {
                paramValue = m_Buffer->ReadByte(m_Pos);
                m_Pos += (XInt)sizeof(paramValue);
                m_Error.ErrorCode = ERR_OK;
            }
            else
            {
                m_Error.ErrorCode = ECEC_NOT_ENOUGH_OF_DECODE;
            }
            return m_Error.ErrorCode;
        }

        XInt Coding(const char * /*paramName*/, XWord & paramValue)
        {
            if (CheckSize<XWord>())
            {
                paramValue = m_Buffer->ReadWord(m_Pos);
                m_Pos += (XInt)sizeof(paramValue);
                m_Error.ErrorCode = ERR_OK;
            }
            else
            {
                m_Error.ErrorCode = ECEC_NOT_ENOUGH_OF_DECODE;
            }
            return m_Error.ErrorCode;
        }

        XInt Coding(const char * /*paramName*/, XShort & paramValue)
        {
            if (CheckSize<XShort>())
            {
                paramValue = m_Buffer->ReadShort(m_Pos);
                m_Pos += (XInt)sizeof(paramValue);
                m_Error.ErrorCode = ERR_OK;
            }
            else
            {
                m_Error.ErrorCode = ECEC_NOT_ENOUGH_OF_DECODE;
            }
            return m_Error.ErrorCode;
        }

        XInt Coding(const char * /*paramName*/, XLong & paramValue)
        {
            if (CheckSize<XLong>())
            {
                paramValue = m_Buffer->ReadLong(m_Pos);
                m_Pos += (XInt)sizeof(paramValue);
                m_Error.ErrorCode = ERR_OK;
            }
            else
            {
                m_Error.ErrorCode = ECEC_NOT_ENOUGH_OF_DECODE;
            }
            return m_Error.ErrorCode;
        }

        XInt Coding(const char * /*paramName*/, XDDWord & paramValue)
        {
            if (CheckSize<XDDWord>())
            {
                paramValue = m_Buffer->ReadDDWord(m_Pos);
                m_Pos += (XInt)sizeof(paramValue);
                m_Error.ErrorCode = ERR_OK;
            }
            else
            {
                m_Error.ErrorCode = ECEC_NOT_ENOUGH_OF_DECODE;
            }
            return m_Error.ErrorCode;        
        }

        XInt Coding(const char * /*paramName*/, XBool & paramValue)
        {
            if (CheckSize<XByte>())
            {
                paramValue = m_Buffer->ReadBool(m_Pos);
                m_Pos += (XInt)sizeof(paramValue);
                m_Error.ErrorCode = ERR_OK;
            }
            else
            {
                m_Error.ErrorCode = ECEC_NOT_ENOUGH_OF_DECODE;
            }
            return m_Error.ErrorCode;        
        }

        XInt Coding(const char * /*paramName*/, XFloat & paramValue)
        {
            if (CheckSize<XFloat>())
            {
                paramValue = m_Buffer->ReadFloat(m_Pos);
                m_Pos += (XInt)sizeof(paramValue);
                m_Error.ErrorCode = ERR_OK;
            }
            else
            {
                m_Error.ErrorCode = ECEC_NOT_ENOUGH_OF_DECODE;
            }
            return m_Error.ErrorCode;  
        }

        XInt Coding(const char * /*paramName*/, XDouble & paramValue)
        {
            if (CheckSize<XDouble>())
            {
                paramValue = m_Buffer->ReadDouble(m_Pos);
                m_Pos += (XInt)sizeof(paramValue);
                m_Error.ErrorCode = ERR_OK;
            }
            else
            {
                m_Error.ErrorCode = ECEC_NOT_ENOUGH_OF_DECODE;
            }
            return m_Error.ErrorCode; 
        }

        XInt Coding(const char * /*paramName*/, XAnsiString & paramString)
        {
            do 
            {
                if (!CheckSize<XInt>())
                {
                    m_Error.ErrorCode = ECEC_NOT_ENOUGH_OF_DECODE;
                    break;
                }

                XInt iStringLength = m_Buffer->ReadInt(m_Pos);
                m_Pos += (XInt)sizeof(XInt);
                if (iStringLength < 0 || iStringLength > ECC_MAX_STRING)
                {
                    m_Error.ErrorCode = ECEC_INVALID_STRING_LENGTH;
                    break;
                }

                paramString.assign((const XChar *)(m_Buffer->getData()) + m_Pos, iStringLength);
                m_Pos += iStringLength;
                m_Error.ErrorCode = ERR_OK;
            } while (false);
            return m_Error.ErrorCode;
        }

        XInt Coding(const char * /*paramName*/, XBuffer & paramBuffer)
        {
            do 
            {
                if (!CheckSize<XInt>())
                {
                    m_Error.ErrorCode = ECEC_NOT_ENOUGH_OF_DECODE;
                    break;
                }

                XInt iBufferLength = m_Buffer->ReadInt(m_Pos);
                m_Pos += (XInt)sizeof(XInt);
                if (iBufferLength < 0 || iBufferLength > ECC_MAX_DATA)
                {
                    m_Error.ErrorCode = ECEC_INVALID_BUFFER_LENGTH;
                    break;
                }

                paramBuffer.Clear();
                paramBuffer.AppendData(m_Buffer->getData() + m_Pos, iBufferLength);
                m_Pos += iBufferLength;
                m_Error.ErrorCode = ERR_OK;
            } while (false);
            return m_Error.ErrorCode;
        }

        template<class T>
        XInt CodingArray(const char * /*paramName*/, XDynamicArray<T> & paramValue)
        {
            do 
            {
                if (!CheckSize<XInt>())
                {
                    m_Error.ErrorCode = ECEC_NOT_ENOUGH_OF_DECODE;
                    break;
                }
                XInt iBufferLength = m_Buffer->ReadInt(m_Pos);
                m_Pos += (XInt)sizeof(XInt);
                if (iBufferLength < 0 || iBufferLength > ECC_MAX_ARRAY_LENGTH)
                {
                    m_Error.ErrorCode = ECEC_INVALID_ARRAY_LENGTH;
                    break;
                }
                paramValue.Clear();
                paramValue.ensureCapacity(iBufferLength);
                for (XInt i = 0; i < iBufferLength; i++)
                {
                    paramValue.Append();                                    
                    if ( Coding(NULL, paramValue[i]) != ERR_OK ) 
                    {
                        break;
                    }
                }
            } while (false);
            return m_Error.ErrorCode;
        }

        template<class T>
        XInt CodingArray(const char * /*paramName*/, XObjectArray<T> & paramValue)
        {
            do 
            {
                if (!CheckSize<XInt>())
                {
                    m_Error.ErrorCode = ECEC_NOT_ENOUGH_OF_DECODE;
                    break;
                }
                XInt iBufferLength = m_Buffer->ReadInt(m_Pos);
                m_Pos += (XInt)sizeof(XInt);
                if (iBufferLength < 0 || iBufferLength > ECC_MAX_ARRAY_LENGTH)
                {
                    m_Error.ErrorCode = ECEC_INVALID_ARRAY_LENGTH;
                    break;
                }
                paramValue.Clear();
                paramValue.ensureCapacity(iBufferLength);
                for (XInt i = 0; i < iBufferLength; i++)
                {
                    T * pElement = paramValue.Append();                                 
                    if ( Coding(NULL, *pElement) != ERR_OK ) 
                    {
                        break;
                    }
                }
            } while (false);
            return m_Error.ErrorCode;
        }

        template<class T, int N>
        XInt CodingArray(const char * /*paramName*/, T (&paramValue)[N])
        {
            do 
            {
                if (!CheckSize<XInt>())
                {
                    m_Error.ErrorCode = ECEC_NOT_ENOUGH_OF_DECODE;
                    break;
                }
                XInt iArrayLength = m_Buffer->ReadInt(m_Pos);
                m_Pos += (XInt)sizeof(XInt);
                if (iArrayLength != N)
                {
                    m_Error.ErrorCode = ECEC_INVALID_ARRAY_LENGTH;
                    break;
                }
                for (XInt i = 0; i < N; i++)
                {
                    if ( Coding(NULL, paramValue[i]) != ERR_OK ) 
                    {
                        break;
                    }
                }
            } while (false);
            return m_Error.ErrorCode;       
        }
        template<class T>
        XInt ToCodingArray(const char * /*paramName*/, XDynamicArray<T> & paramValue)
        {
            do 
            {
                if (!CheckSize<XInt>())
                {
                    m_Error.ErrorCode = ECEC_NOT_ENOUGH_OF_DECODE;
                    break;
                }
                XInt iBufferLength = m_Buffer->ReadInt(m_Pos);
                m_Pos += (XInt)sizeof(XInt);
                if (iBufferLength < 0 || iBufferLength > ECC_MAX_ARRAY_LENGTH)
                {
                    m_Error.ErrorCode = ECEC_INVALID_ARRAY_LENGTH;
                    break;
                }
                paramValue.Clear();
                paramValue.ensureCapacity(iBufferLength);
                for (XInt i = 0; i < iBufferLength; i++)
                {
                    paramValue.Append();                                    
                    if ( paramValue[i].ToCoding(NULL, *this) != ERR_OK )
                    {
                        break;
                    }
                }
            } while (false);
            return m_Error.ErrorCode;
        }

        template<class T>
        XInt ToCodingArray(const char * /*paramName*/, XObjectArray<T> & paramValue)
        {
            do 
            {
                if (!CheckSize<XInt>())
                {
                    m_Error.ErrorCode = ECEC_NOT_ENOUGH_OF_DECODE;
                    break;
                }
                XInt iBufferLength = m_Buffer->ReadInt(m_Pos);
                m_Pos += (XInt)sizeof(XInt);
                if (iBufferLength < 0 || iBufferLength > ECC_MAX_ARRAY_LENGTH)
                {
                    m_Error.ErrorCode = ECEC_INVALID_ARRAY_LENGTH;
                    break;
                }
                paramValue.Clear();
                paramValue.ensureCapacity(iBufferLength);
                for (XInt i = 0; i < iBufferLength; i++)
                {
                    T * pElement = paramValue.Append();                                 
                    if (pElement->ToCoding(NULL, *this) != ERR_OK ) 
                    {
                        break;
                    }
                }
            } while (false);
            return m_Error.ErrorCode;
        }

        template<class T, int N>
        XInt ToCodingArray(const char * /*paramName*/, T (&paramValue)[N])
        {
            do 
            {
                if (!CheckSize<XInt>())
                {
                    m_Error.ErrorCode = ECEC_NOT_ENOUGH_OF_DECODE;
                    break;
                }
                XInt iArrayLength = m_Buffer->ReadInt(m_Pos);
                m_Pos += (XInt)sizeof(XInt);
                if (iArrayLength != N)
                {
                    m_Error.ErrorCode = ECEC_INVALID_ARRAY_LENGTH;
                    break;
                }
                for (XInt i = 0; i < N; i++)
                {
                    if ( paramValue[i].ToCoding(NULL, *this) != ERR_OK ) 
                    {
                        break;
                    }
                }
            } while (false);
            return m_Error.ErrorCode;       
        }
    private:
        XBuffer * m_Buffer;
        bool m_BindBufferFlag;
        XInt m_Pos;
    };
}
#endif

