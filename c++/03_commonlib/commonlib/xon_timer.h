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
    ///定时器类型
    /**
        @param [in] paramOnTimer 对应的定时器对象
        @param [in] paramNow 当前时间
        @return XLong 返回定时器下次到达的时间
            - 0 表示不再执行次定时器
            - >0 表示下次定时到达的时间
     */
    typedef fastdelegate::FastDelegate<XLong (XOnTimer * paramOnTimer, XLong paramNow)> TOnTimerEvent;
    ///定时器对象
    class XOnTimer
    {
        friend class XOnTimerManager;
        friend struct SOnTimerListHead;
    public:
        XOnTimer()
        {}
        ///取定时器的ID
        XLong getID() const
        {
            return m_ID;
        }
        ///取定时器定时的时间
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
        XLong m_ID;                         ///<定时器对象ID，由定时器管理器负责分配
        XLong m_Timer;                      ///<定时器定时的时间
        XOnTimer * m_Pre;                   
        XOnTimer * m_Next;
        TOnTimerEvent m_OnTimerEvent;       ///<定时器委托的事件
    };
    ///定时器列表头
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

    ///定时器管理器
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
        ///释放所有定时器
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
        ///增加一个定时器 
        /**
            @param [in] paramTime 定时到达的时间点
            @return XOnTimer * 返回定时器对象 返回NULL表示分配定时器失败
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
        ///执行定时器事件
        /**
            @param [in] paramNow 当前时间
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
                    if(lngNextTime <=0)  //该定时器不再使用
                    {
                        m_OnTimerPool.Append(pCurr);  //放到待用池中
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
        XLong m_IDCounter;                          ///<定时器ID计数器
        TOnTimerEventList m_OnTimerEventList;       ///<定时器列表
        XDynamicArray<XOnTimer *> m_OnTimerPool;    ///<待用的定时器对象池    
    };
}
#endif
