#ifndef _X_ON_TIMER_H_
#define _X_ON_TIMER_H_
#include <xtype.h>
#include <xdynamic_array.h>
#include <FastDelegate.h>
#include <map>
namespace zdh
{
    class XOnTimer;
    class XOnTimerManager;
    struct SOnTimerListHead;
    ///��ʱ������
    /**
        @param [in] paramOnTimer ��Ӧ�Ķ�ʱ������
        @param [in] paramNow ��ǰʱ��
        @return XLong ���ض�ʱ���´ε����ʱ��
            - 0 ��ʾ����ִ�дζ�ʱ��
            - >0 ��ʾ�´ζ�ʱ�����ʱ��
     */
    typedef fastdelegate::FastDelegate<XLong (XOnTimer * paramOnTimer, XLong paramNow)> TOnTimerEvent;
    ///��ʱ������
    class XOnTimer
    {
        friend class XOnTimerManager;
        friend struct SOnTimerListHead;
    public:
        XOnTimer()
        {}
        ///ȡ��ʱ����ID
        XLong getID() const
        {
            return m_ID;
        }
        ///ȡ��ʱ����ʱ��ʱ��
        XLong getTimer() const
        {
            return m_Timer;
        }
        TOnTimerEvent & getOnTimerEvent()
        {
            return m_OnTimerEvent;
        }
    private:
        void Reset()
        {
            m_Pre   = NULL;
            m_Next  = NULL;
        }
    private:
        XLong m_ID;                         ///<��ʱ������ID���ɶ�ʱ���������������
        XLong m_Timer;                      ///<��ʱ����ʱ��ʱ��
        XOnTimer * m_Pre;                   
        XOnTimer * m_Next;
        TOnTimerEvent m_OnTimerEvent;       ///<��ʱ��ί�е��¼�
    };
    ///��ʱ���б�ͷ
    struct SOnTimerListHead
    {
    public:
        SOnTimerListHead()
            :Head(NULL),Tail(NULL),Count(0)
        {}

        void Append(XOnTimer * paramOnTimer)
        {
            if (Count == 0)
            {
                Head = paramOnTimer;
                Tail = paramOnTimer;
                Count ++;
            }
            else
            {
                Tail->m_Next = paramOnTimer;
                paramOnTimer->m_Pre = Tail;
                Tail = paramOnTimer;
                Count ++;
            }
        }
    public:
        XOnTimer * Head;        
        XOnTimer * Tail;
        XLong      Count;
    };
    
    typedef std::map<XLong, SOnTimerListHead> TOnTimerEventList;
    typedef TOnTimerEventList::iterator TOnTimerEventListIterator;

    ///��ʱ��������
    class XOnTimerManager
    {
    public:
        XOnTimerManager()
            :m_IDCounter(0)
        {}
        ~XOnTimerManager()
        {
            Clear();
        }
        ///�ͷ����ж�ʱ��
        void Clear()
        {
            for(XInt i = 0; i < m_OnTimerPool.getLength(); i++)
            {
                delete m_OnTimerPool[i];
            }
            for(TOnTimerEventListIterator iter = m_OnTimerEventList.begin(); iter != m_OnTimerEventList.end(); ++iter)
            {
                XOnTimer * pHead = iter->second.Head;
                while(isNotNULL(pHead))
                {
                    XOnTimer * p = pHead;
                    pHead = pHead->m_Next;
                    delete p;
                }
            }
            m_IDCounter = 0;
        }
        ///����һ����ʱ�� 
        /**
            @param [in] paramTime ��ʱ�����ʱ���
            @return XOnTimer * ���ض�ʱ������ ����NULL��ʾ���䶨ʱ��ʧ��
         */
        XOnTimer * AddOnTimer(XLong paramTime)
        {
            XOnTimer * pOnTimer = NULL;
            SOnTimerListHead * pHead = NULL;
            TOnTimerEventListIterator iter = m_OnTimerEventList.find(paramTime);
            if (iter == m_OnTimerEventList.end())
            {
                SOnTimerListHead stTmp;
                m_OnTimerEventList[paramTime] = stTmp;
                iter = m_OnTimerEventList.find(paramTime);
                if (iter == m_OnTimerEventList.end())
                {
                    return pOnTimer;
                }
            }
            pHead = &iter->second;
            pOnTimer = AllocOnTimer();
            
            if (isNULL(pOnTimer))
            {
                return pOnTimer;
            }
            pOnTimer->m_Timer = paramTime;
            pHead->Append(pOnTimer); 
            return pOnTimer;
        }
        ///ִ�ж�ʱ���¼�
        /**
            @param [in] paramNow ��ǰʱ��
         */
        void DoOnTimer(XLong paramNow)
        {
            SOnTimerListHead stNext;
            for (TOnTimerEventListIterator iter = m_OnTimerEventList.begin(); iter != m_OnTimerEventList.end();)
            {
                if (iter->first > paramNow)
                {
                    break;
                }

                SOnTimerListHead * pHead = &iter->second;
                XOnTimer * p = pHead->Head;
                while(isNotNULL(p))
                {
                    XOnTimer * pCurr = p;
                    p = p->m_Next;
                    XLong lngNextTime = -1;
                    if (!pCurr->m_OnTimerEvent.empty())
                    {
                        lngNextTime = pCurr->m_OnTimerEvent(pCurr, paramNow);
                    }
                    if(lngNextTime <=0)  //�ö�ʱ������ʹ��
                    {
                        m_OnTimerPool.Append(pCurr);  //�ŵ����ó���
                    }
                    else  //
                    {
                        pCurr->Reset();
                        pCurr->m_Timer = lngNextTime;
                        stNext.Append(pCurr);  
                    }
                }

                TOnTimerEventListIterator iterRemove = iter;
                ++iter;
                m_OnTimerEventList.erase(iterRemove);
            }
            XOnTimer * pNew = stNext.Head;
            while(isNotNULL(pNew))
            {
                XOnTimer * pCurr = pNew;
                pNew = pNew->m_Next;
                pCurr->Reset();
                m_OnTimerEventList[pCurr->getTimer()].Append(pCurr);
                //AddOnTimer(pCurr->getTimer());
            }
        }
    private:
        XOnTimer * AllocOnTimer()
        {
            XOnTimer * pRet = NULL;
            if (!m_OnTimerPool.Pop(pRet))
            {
                pRet = new XOnTimer();
                pRet->m_ID = m_IDCounter ++;
            }
            pRet->m_OnTimerEvent.clear();
            pRet->Reset();
            return pRet;
        }
    private:
        XLong m_IDCounter;                          ///<��ʱ��ID������
        TOnTimerEventList m_OnTimerEventList;       ///<��ʱ���б�
        XDynamicArray<XOnTimer *> m_OnTimerPool;    ///<���õĶ�ʱ�������    
    };
}
#endif
