#ifndef _X_DOUBLE_LIST_H_
#define _X_DOUBLE_LIST_H_
#include <xcommon_error_code.h>
#include <xtype.h>
#include <xlog.h>
///双向链表
namespace zdh
{
    template<class T>
    class XMultList
    {
    public:
        class XNode;
        class XListHead;
    public:
        enum 
        {
            MIN_LIST_COUNT = 2,         ///<最小的链表个数
            MIN_NODE_COUNT = 1,         ///<最小的节点个数
            MAX_ERROR_MSG_SIZE = 1024,  ///<最大的错误信息长度

            LIST_INDEX_FREE = 0,        ///<未分配链表下标
            LIST_INDEX_USE  = 1,        ///<默认已使用链表下标
        };

        class XNode
        {
            friend class XMultList;
            friend class XListHead;
        public:
            XNode()
                :m_Next(NULL),m_Pre(NULL),m_Data(NULL)
            {}
            T * getData() 
            {
                return m_Data;
            }
            const T * getData() const
            {
                return m_Data;
            }
            XNode * getNext() 
            {
                return m_Next;
            }
            XNode * getPre() 
            {
                return m_Pre;
            }
            XListHead * getListHead() 
            {
                return m_ListHeadList;
            }
        private:
            XNode *     m_Next;
            XNode *     m_Pre;
            T *         m_Data;
            XListHead * m_List;
        };

        class XListHead
        {
            friend class XMultList;
        public:
            XListHead()
                :m_Head(NULL), m_Tail(NULL), m_Count(0)
            {}
            XInt getCount() const
            {
                return m_Count;
            }
            bool isEmpty() const
            {
                return m_Count <= 0;
            }
            XNode * getHeadNode()
            {
                return m_Head;
            }
            XNode * getTailNode()
            {
                return m_Tail;
            }
        private:
            XNode * m_Head;
            XNode * m_Tail;
            XInt    m_Count;
        };
    public:
        XMultList()
            :m_InitFlag(false),m_ListCount(0), m_ListHeadList(0), m_Count(0), m_NodeList(NULL), m_DataList(NULL)
        {
        }
        ~XMultList()
        {
            Close();
        }
        XInt Open(XInt paramListCount, XInt paramDataCount, T * paramDataList)
        {
            if (m_InitFlag)
            {
                m_ErrorMsg.nprintf(MAX_ERROR_MSG_SIZE, "list has already been initialized!");
                return  ECEC_HAS_ALREADY_BEEN_INITIALIZED; //已经初始化了
            }

            if (paramListCount < MIN_LIST_COUNT)
            {
                m_ErrorMsg.nprintf(MAX_ERROR_MSG_SIZE, "list init fail! list cout = %d < %d", paramListCount, MIN_LIST_COUNT);    
                return ERR_FAIL;
            }

            if (paramDataCount < MIN_NODE_COUNT)
            {
                m_ErrorMsg.nprintf(MAX_ERROR_MSG_SIZE, "list init fail! node count = %d < %d", paramDataCount, MIN_NODE_COUNT);
                return ERR_FAIL;
            }

            if (isNULL(paramDataList))
            {
                m_ErrorMsg.nprintf(MAX_ERROR_MSG_SIZE, "list init fail! paramDataList is NULL!");
                return ERR_FAIL;
            }

            //
            m_ListHeadList = new XListHead[paramListCount];
            if (isNULL(m_ListHeadList))
            {
                m_ErrorMsg.nprintf(MAX_ERROR_MSG_SIZE, "list init fail! new XListHead[%d] fail!", paramListCount);
                return ERR_FAIL;
            }

            m_ListCount = paramListCount;

            m_NodeList = new XNode[paramDataCount];
            if (isNULL(m_NodeList))
            {
                m_ErrorMsg.nprintf(MAX_ERROR_MSG_SIZE, "list init fail! new XNode[%d] fail!", paramDataCount);
                delete [] m_ListHeadList;
                m_ListHeadList = NULL;
                m_ListCount = 0;
                return ERR_FAIL;
            }

            m_Count = paramDataCount;
            m_DataList = paramDataList;

            XNode * pNode = m_NodeList;
            XListHead * pHead = &m_ListHeadList[LIST_INDEX_FREE];
            T * pData = paramDataList;
            for(XInt i = 0; i < paramDataCount; i++)
            {
                pNode->m_Data = pData;
                ListAppend(pHead, pNode);
                pNode ++;
                pData ++;
            }
            m_InitFlag = true;
            return ERR_OK;
        }
        XInt Close()
        {
            XInt iRet;
            if (m_InitFlag)
            {
                m_InitFlag = false;
                delete [] m_NodeList;
                delete [] m_ListHeadList;
                m_Count         = 0;
                m_ListCount     = 0;
                m_NodeList      = NULL;
                m_ListHeadList  = NULL;
                m_DataList      = NULL;
                iRet            = ERR_OK;
            }
            else
            {
                m_ErrorMsg = "list has not been initalised!";
                iRet = ECEC_HAS_NOT_BEEN_INITIALISED; //还没有初始化
            }
            return iRet;
        }
        bool getInitFlag() const
        {
            return m_InitFlag;
        }
        XInt getCount() const
        {
            return m_Count;
        }
        XInt getListCount() const
        {
            return m_ListCount;
        }
        const XAnsiString & getErrorMsg() const
        {
            return m_ErrorMsg;
        }
    public:
        XNode * getNodeByIndex(XLong paramIndex)
        {
            XNode * pRet = NULL;
            if (paramIndex >= 0 && paramIndex < m_Count)
            {
                pRet = m_NodeList + paramIndex;
            }
            return pRet;
        }
        XListHead * getListHead(XInt paramListIndex)
        {
            if (!m_InitFlag)
            {
                m_ErrorMsg = "list has not been initalised!";
                return NULL;
            }
            if (paramListIndex >= 0 && paramListIndex < m_ListCount)
            {
                return &m_ListHeadList[paramListIndex];
            }
            else
            {
                m_ErrorMsg.nprintf(MAX_ERROR_MSG_SIZE, "paramListIndex =(%d) < 0 or >= %d", paramListIndex, m_ListCount);
                return NULL;
            }
        }
        
        XInt MoveToFreeByIndex(XLong paramIndex)
        {
            XNode * pNode = getNodeByIndex(paramIndex);
            if (isNotNULL(pNode))
            {
                return MoveToFree(pNode);
            }
            return ERR_FAIL;
        }

        XInt MoveToFree(XNode * paramNode)
        {
            return MoveTo(paramNode, LIST_INDEX_FREE);
        }

        XInt MoveToUseByIndex(XLong paramIndex)
        {
            XNode * pNode = getNodeByIndex(paramIndex);
            if (isNotNULL(pNode))
            {
                return MoveToUse(pNode);
            }
            return ERR_FAIL;
        }

        XInt MoveToUse(XNode * paramNode)
        {
            return MoveTo(paramNode, LIST_INDEX_USE);
        }

        XInt MoveTo(XNode * paramNode, XInt paramDestListIndex)
        {
            if(!m_InitFlag)
            {
                m_ErrorMsg = "list has not been initalised!";
                return ERR_FAIL;
            }
            
            if (isNULL(paramNode))
            {
                m_ErrorMsg.nprintf(MAX_ERROR_MSG_SIZE, "paramNode is null");
                return ERR_FAIL;
            }

            if (paramDestListIndex < 0 ||  paramDestListIndex >= m_ListCount)
            {
                m_ErrorMsg.nprintf(MAX_ERROR_MSG_SIZE, "paramDestListIndex =(%d) < 0 or >= %d", paramDestListIndex, m_ListCount);
                return ERR_FAIL;
            }

            XListHead * pDestList = &m_ListHeadList[paramDestListIndex];
            ListRemoveNode(paramNode);
            ListAppend(pDestList, paramNode);
            return ERR_OK;
        }
        XListHead * getFreeListHead()
        {
            return getListHead(LIST_INDEX_FREE);
        }
        XListHead * getUseListHead()
        {
            return getListHead(LIST_INDEX_USE);
        }
    private:
        void ListRemoveNode(XNode * paramNode)
        {
            XListHead * pSrcList = paramNode->m_List;
            if (pSrcList->m_Count == 1)
            {
                pSrcList->m_Head = NULL;
                pSrcList->m_Count = 0;
                pSrcList->m_Tail = NULL;
            }
            else 
            {
                if (pSrcList->m_Head == paramNode)
                {
                    pSrcList->m_Head = paramNode->m_Next;
                    pSrcList->m_Head->m_Pre = NULL;
                }
                else if(pSrcList->m_Tail == paramNode)
                {
                    pSrcList->m_Tail = paramNode->m_Pre;
                    pSrcList->m_Tail->m_Next = NULL;
                }
                else
                {
                    paramNode->m_Pre->m_Next = paramNode->m_Next;
                    paramNode->m_Next->m_Pre = paramNode->m_Pre;
                }
            }
            paramNode->m_Pre  = NULL;
            paramNode->m_Next = NULL;
            paramNode->m_List = NULL;
        }
        void ListAppend(XListHead * paramList, XNode * paramNode)
        {
            if (paramList->m_Count <= 0)
            {
                paramList->m_Count  = 1;
                paramList->m_Head   = paramNode;
                paramList->m_Tail   = paramNode;
                paramNode->m_Pre    = NULL;
                paramNode->m_Next   = NULL;
                paramNode->m_List   = paramList;
            }
            else
            {
                paramList->m_Count ++;
                paramList->m_Tail->m_Next = paramNode;
                paramNode->m_Pre  = paramList->m_Tail;
                paramNode->m_Next = NULL;
                paramList->m_Tail = paramNode;
                paramNode->m_List = paramList;
            }
        }
    private:
        bool        m_InitFlag;
        XInt        m_ListCount;
        XListHead * m_ListHeadList;
        XInt        m_Count;
        XNode *     m_NodeList;
        T *         m_DataList;
        XAnsiString m_ErrorMsg;
    };
}
#endif
