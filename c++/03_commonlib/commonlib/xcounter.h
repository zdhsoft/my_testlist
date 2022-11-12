///计数器类
#ifndef _X_COUNTER_H_
#define _X_COUNTER_H_
namespace zdh
{
    template<class T>
    class XCounter
    {
    public:
        XCounter()
            :m_Counter(0)
        {}

        XCounter(const T & paramT)
            :m_Counter(paramT)
        {}
        //计数器加1
        T Inc()
        {
            m_Counter ++;
            return m_Counter;
        }
        //计数器减1
        T Dec()
        {
            m_Counter --;
            return m_Counter;
        }
        //
        void reset(const T & paramT)
        {
            m_Counter = paramT;
        }
        //
        const T & getCounter() const
        {
            return m_Counter;
        }
    private:
        T m_Counter;
    };
}
#endif
