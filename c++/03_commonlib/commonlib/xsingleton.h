#ifndef _X_SINGLETON_H_
#define _X_SINGLETON_H_
#include <xtype.h>
namespace zdh
{
    //������亯����ǿ���˵���Ĵ�������
    template<class T, int N = 0>
    class XSingleton
    {
    public:
        typedef T TInstance;
    public:
        static void Create()
        {
            T ** p = Instance();
            if (*p == NULL)
            {
                *p = new T();
            }
        }
        static void Destory()
        {
            T ** p = Instance();
            if (*p != NULL)
            {
                delete *p;
                *p = NULL;
            }
        }
        static T * getInstance()
        {
            return *Instance();
        }
    private:
        static T ** Instance()
        {
            static T * stInstance = NULL;
            return &stInstance;
        }
    };
    //һ���򵥵ĵ���
    template<class T, int N = 0>
    class XSingletonSample
    {
    public:
        typedef T TInstance;
    public:
        static T * getInstance()
        {
            static T stInstance;
            return &stInstance;
        }
    };
}
#endif
