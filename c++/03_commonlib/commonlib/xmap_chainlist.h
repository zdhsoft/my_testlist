#ifndef _X_MAP_CHAIN_LIST_H_
#define _X_MAP_CHAIN_LIST_H_
#include <xtype.h>
#include <xdynamic_array.h>
#include <map>
namespace zdh
{
//    const XInt INVALID_INDEX                = -1;   
//    const XInt FREE_CHAINLIST_HEAD_INDEX    = 0;    ///<未用节点的链表头下标
//    
//    ///节点区域
//    class XChainListArea
//    {
//    public:
//        ///链表头
//        struct SChainListHead
//        {
//            SChainListHead()
//                :First(INVALID_INDEX), 
//                 Tail(INVALID_INDEX),
//                 Count(0)
//            {}
//            XInt First;     ///<第一个节点下标
//            XInt Tail;      ///<最后一个节点下标
//            XInt Count;     ///<节点个数
//        };
//
//        ///链表节点
//        struct SChainListNode
//        {
//            SChainListNode()
//                :Next(INVALID_INDEX),
//                 Pre(INVALID_INDEX),
//                 ListIndex(INVALID_INDEX)
//            {}
//            XInt Next;      ///<下个节点下标
//            XInt Pre;       ///<前一个节点下标
//            XInt ListIndex; ///<所在的链表下标
//        };
//
//    public:
////      class CList
////      {
////      public:
////          CList(XChainListArea * a_Area, SChainListHead * a_Head, XInt a_ListIndex)
////              :m_Area()
////          {
//// 
////          }
////      private:
////          XChainListArea * m_Area;
////          SChainListHead * m_ListHead;
////          XInt m_ListIndex;
////      };
//    public:
//        XChainListArea()
//        {
//
//        }
//        void Init(XInt paramNodeCount, XInt paramHeadCount)  
//        {
//            if(paramNodeCount < 0)
//            {
//                paramNodeCount = 0;
//            }
//
//            if(paramHeadCount < 2) 
//            {
//                paramHeadCount = 2;
//            }
//
//            m_List.Clear();
//            m_NodeList.Clear();
//            
//            //建立链表列表
//            for (XInt i = 0; i < paramHeadCount; ++i)
//            {
//                m_List.Append();
//            }
//            //初始化节点
//            for (XInt i = 0; i < paramNodeCount; ++i)
//            {
//                ChainListAppendNode(FREE_CHAINLIST_HEAD_INDEX, m_NodeList.Append());
//            }
//        }
//
//        ///确定链表的个数
//        void ensureHeadCapacity(XInt paramHeadCount)
//        {
//            m_List.ensureCapacity(paramHeadCount);
//        }
//
//        ///确定节点的个数
//        void ensureNodeCapacity(XInt paramNodeCount)
//        {
//            m_NodeList.ensureCapacity(paramNodeCount);
//        }
//
//
//        XInt MoveNodeToList(XInt paramDestListIndex, XInt paramNodeIndex)
//        {
//            if (!m_NodeList.isValidIndex(paramNodeIndex))            
//            {
//                //如果是无效的节点下标
//                return -1;
//            }
//            
//            if (!m_List.isValidIndex(paramDestListIndex))
//            {
//                //如果是无效的链表头下标
//                return -2;
//            }
//            MoveNode(paramDestListIndex, paramNodeIndex);
//            return ERR_OK;
//        }
//
//        XInt FreeNode(XInt paramNodeIndex) 
//        {
//            return MoveNodeToList(paramNodeIndex, FREE_CHAINLIST_HEAD_INDEX);
//        }
//
//        XInt getNodePreIndex(XInt paramNodeIndex) const
//        {
//            if (!m_NodeList.isValidIndex(paramNodeIndex))
//            {
//                return INVALID_INDEX;
//            }
//
//            return m_NodeList[paramNodeIndex].Pre;
//        }
//
//        XInt getNodeNextIndex(XInt paramNodeIndex) const
//        {
//            if (!m_NodeList.isValidIndex(paramNodeIndex))
//            {
//                return INVALID_INDEX;
//            }
//
//            return m_NodeList[paramNodeIndex].Next;
//        }
//
//        XInt getListIndex(XInt paramNodeIndex) const
//        {
//            if(!m_NodeList.isValidIndex(paramNodeIndex))
//            {
//                return INVALID_INDEX;
//            }
//            return m_NodeList[paramNodeIndex].ListIndex;
//        }
//
//        XInt getListHeadIndex(XInt paramListIndex) const
//        {
//            if (!m_List.isValidIndex(paramListIndex))
//            {
//                return INVALID_INDEX;
//            }
//            return m_List[paramListIndex].First;
//        }
//        
//        XInt getListCount(XInt paramListIndex) const
//        {
//            if (!m_List.isValidIndex(paramListIndex))
//            {
//                return INVALID_INDEX;
//            }
//            return m_List[paramListIndex].Count;
//        }
//
//        XInt getListTailIndex(XInt paramListIndex) const
//        {
//            if (!m_List.isValidIndex(paramListIndex))
//            {
//                return INVALID_INDEX;
//            }
//            return m_List[paramListIndex].Tail;
//        }
//    private:
//        ///移动节点到指定链表的结尾
//        void MoveNode(XInt paramDestListIndex, XInt paramNodeIndex)
//        {
//            ChainListRemoveNode(paramNodeIndex);
//            ChainListAppendNode(paramDestListIndex, paramNodeIndex);
//        }
//
//        ///链表中删除节点
//        void ChainListRemoveNode(XInt paramNodeIndex)
//        {
//            SChainListNode & stNode = m_NodeList[paramNodeIndex];
//            SChainListHead & stHead = m_List[stNode.ListIndex];
//            if (stHead.Count <= 1)
//            {
//                //如果只有一个节点
//                stHead.First = INVALID_INDEX;
//                stHead.Tail = INVALID_INDEX;
//                stHead.Count = 0;
//            }
//            else
//            {
//                if (stHead.First == paramNodeIndex)
//                {
//                    //如果是第一个节点
//                    stHead.First = stNode.Next;
//                    m_NodeList[stHead.First].Pre = INVALID_INDEX;
//                    stHead.Count --;
//
//                }
//                else if(stHead.Tail == paramNodeIndex)
//                {
//                    //如果是最后一个节点
//                    stHead.Tail = stNode.Pre;
//                    m_NodeList[stHead.Tail].Next = INVALID_INDEX;
//                    stHead.Count --;
//                }
//                else
//                {
//                    m_NodeList[stNode.Pre].Next = stNode.Next;
//                    m_NodeList[stNode.Next].Pre = stNode.Pre;
//                    stHead.Count --;
//                }
//            }
//            stNode.ListIndex = INVALID_INDEX;
//            stNode.Next = INVALID_INDEX;
//            stNode.Pre = INVALID_INDEX;
//        }
//
//        ///链表增加节点
//        /**
//            不做检查
//         */
//        void ChainListAppendNode(XInt paramListIndex, XInt paramNodeIndex)
//        {
//            SChainListHead & stHead = m_List[paramListIndex];
//            SChainListNode & stNode = m_NodeList[paramNodeIndex];
//
//            if(stHead.Count == 0)
//            {
//                //如果是一个空链表
//                stHead.First = paramNodeIndex;
//                stHead.Tail = paramNodeIndex;
//                stHead.Count ++;
//
//                stNode.ListIndex = paramListIndex;
//                stNode.Next = INVALID_INDEX;
//                stNode.Pre = INVALID_INDEX;
//            }
//            else
//            {
//                //如果不是空链表
//                SChainListNode & stNodePre = m_NodeList[stHead.Tail];
//                stNodePre.Next = paramNodeIndex;
//                stNode.Pre = stHead.Tail;
//                stNode.ListIndex = paramListIndex;
//                stHead.Tail = paramNodeIndex;
//                stHead.Count ++;
//            }
//        }
//    private:
//        XDynamicArray<SChainListHead> m_List;   ///<链表头区域
//        XDynamicArray<SChainListNode> m_NodeList;   ///<节点区域
//    };
//
//
//    template<class ELEMENT>
//    class XHashChain
//    {
//    public:
//    private:
//        XObjectArray<XChainListArea> m_AreaList;
//        
//    };

     
}
#endif
