#ifndef _X_MAP_CHAIN_LIST_H_
#define _X_MAP_CHAIN_LIST_H_
#include <xtype.h>
#include <xdynamic_array.h>
#include <map>
namespace zdh
{
//    const XInt INVALID_INDEX                = -1;   
//    const XInt FREE_CHAINLIST_HEAD_INDEX    = 0;    ///<δ�ýڵ������ͷ�±�
//    
//    ///�ڵ�����
//    class XChainListArea
//    {
//    public:
//        ///����ͷ
//        struct SChainListHead
//        {
//            SChainListHead()
//                :First(INVALID_INDEX), 
//                 Tail(INVALID_INDEX),
//                 Count(0)
//            {}
//            XInt First;     ///<��һ���ڵ��±�
//            XInt Tail;      ///<���һ���ڵ��±�
//            XInt Count;     ///<�ڵ����
//        };
//
//        ///����ڵ�
//        struct SChainListNode
//        {
//            SChainListNode()
//                :Next(INVALID_INDEX),
//                 Pre(INVALID_INDEX),
//                 ListIndex(INVALID_INDEX)
//            {}
//            XInt Next;      ///<�¸��ڵ��±�
//            XInt Pre;       ///<ǰһ���ڵ��±�
//            XInt ListIndex; ///<���ڵ������±�
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
//            //���������б�
//            for (XInt i = 0; i < paramHeadCount; ++i)
//            {
//                m_List.Append();
//            }
//            //��ʼ���ڵ�
//            for (XInt i = 0; i < paramNodeCount; ++i)
//            {
//                ChainListAppendNode(FREE_CHAINLIST_HEAD_INDEX, m_NodeList.Append());
//            }
//        }
//
//        ///ȷ������ĸ���
//        void ensureHeadCapacity(XInt paramHeadCount)
//        {
//            m_List.ensureCapacity(paramHeadCount);
//        }
//
//        ///ȷ���ڵ�ĸ���
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
//                //�������Ч�Ľڵ��±�
//                return -1;
//            }
//            
//            if (!m_List.isValidIndex(paramDestListIndex))
//            {
//                //�������Ч������ͷ�±�
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
//        ///�ƶ��ڵ㵽ָ������Ľ�β
//        void MoveNode(XInt paramDestListIndex, XInt paramNodeIndex)
//        {
//            ChainListRemoveNode(paramNodeIndex);
//            ChainListAppendNode(paramDestListIndex, paramNodeIndex);
//        }
//
//        ///������ɾ���ڵ�
//        void ChainListRemoveNode(XInt paramNodeIndex)
//        {
//            SChainListNode & stNode = m_NodeList[paramNodeIndex];
//            SChainListHead & stHead = m_List[stNode.ListIndex];
//            if (stHead.Count <= 1)
//            {
//                //���ֻ��һ���ڵ�
//                stHead.First = INVALID_INDEX;
//                stHead.Tail = INVALID_INDEX;
//                stHead.Count = 0;
//            }
//            else
//            {
//                if (stHead.First == paramNodeIndex)
//                {
//                    //����ǵ�һ���ڵ�
//                    stHead.First = stNode.Next;
//                    m_NodeList[stHead.First].Pre = INVALID_INDEX;
//                    stHead.Count --;
//
//                }
//                else if(stHead.Tail == paramNodeIndex)
//                {
//                    //��������һ���ڵ�
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
//        ///�������ӽڵ�
//        /**
//            �������
//         */
//        void ChainListAppendNode(XInt paramListIndex, XInt paramNodeIndex)
//        {
//            SChainListHead & stHead = m_List[paramListIndex];
//            SChainListNode & stNode = m_NodeList[paramNodeIndex];
//
//            if(stHead.Count == 0)
//            {
//                //�����һ��������
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
//                //������ǿ�����
//                SChainListNode & stNodePre = m_NodeList[stHead.Tail];
//                stNodePre.Next = paramNodeIndex;
//                stNode.Pre = stHead.Tail;
//                stNode.ListIndex = paramListIndex;
//                stHead.Tail = paramNodeIndex;
//                stHead.Count ++;
//            }
//        }
//    private:
//        XDynamicArray<SChainListHead> m_List;   ///<����ͷ����
//        XDynamicArray<SChainListNode> m_NodeList;   ///<�ڵ�����
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
