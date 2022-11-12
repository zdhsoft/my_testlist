#include <xconfig.h>
#include <xtype.h>
#include <xos_include.h>
#include <xstring_utils.h>
#include <FastDelegate.h>
#include <xstring.h>
#include <xdynamic_array.h>
#include <xbuffer.h>
#include <xbase64.h>
#include <xmd5.h>
#include <xcrc.h>
#include <xini.h>
#include <xdatetime.h>
#include <xstringlist.h>
#include <xmap.h>
#include <xset.h>
#include <xlog.h>
#include <xpoll.h>
#include <xcoding.h>
#include <iostream>
#include <xpollcontrol.h>
#include <xsingleton.h>
#include <xshm.h>
#include <xlist.h>
#include <xbuffer.h>
using namespace std;
//fff
//这个文件用于commonlib编译测试
using namespace zdh;
class XTestCoding
{
public:
    XTestCoding()
        :m_Number(0),m_Count(0)
    {}
    ~XTestCoding()
    {
    }
    XTestCoding(const XTestCoding & paramV)
    {
        m_Number = paramV.m_Number;
        m_Count  = paramV.m_Count;
        ArrayCopy(m_Test, paramV.m_Test);
        m_OA = paramV.m_OA;
        m_DA = paramV.m_DA;
    }
    XTestCoding & operator = (const XTestCoding & paramV)
    {
        m_Number = paramV.m_Number;
        m_Count  = paramV.m_Count;
        ArrayCopy(m_Test, paramV.m_Test);
        m_OA = paramV.m_OA;
        m_DA = paramV.m_DA;
        return *this;
    }
    XInt  m_Number;
    XByte m_Count;
    XWord m_Test[4];
    XDynamicArray<int> m_DA;
    XObjectArray<int> m_OA;
public:
    CODING_BEGIN(XTestCoding)
        CODING(m_Number)
        CODING_VERSION(1)
            CODING(m_Count)
        CODING_END_VERSION()
        CODING_VERSION(2)
            CODING_ARRAY(m_Test)
            CODING_ARRAY(m_DA)
            CODING_ARRAY(m_OA)
        CODING_END_VERSION()
    CODING_END(XTestCoding)
};

class XTestV
{
public:
    XTestV()
        :m_Number(0)
    {}

    XTestCoding m_t;
    XInt m_Number;
    XObjectArray<XTestCoding> m_OA;
public:
    CODING_BEGIN(XTestV)
        TO_CODING(m_t)
        CODING(m_Number)
        CODING_VERSION(1)
            TO_CODING_ARRAY(m_OA)
        CODING_END_VERSION()
    CODING_END(XTestV)
};
void testCoding()
{
    XTestV k,j;
    k.m_Number = 100;
    k.m_t.m_Number = 101;
    k.m_t.m_Count = 102;
    k.m_t.m_Test[0] = 1;
    k.m_t.m_Test[1] = 2;
    k.m_t.m_Test[2] = 3;
    k.m_t.m_Test[3] = 4;
    k.m_t.m_DA.Push(123456);
    k.m_t.m_DA.Push(123457);
    k.m_t.m_OA.Append(654321);
    k.m_t.m_OA.Append(654322);
    k.m_OA.Append(k.m_t);
    k.m_OA.Append(k.m_t);
    k.m_OA[0].m_Number = 200;
    k.m_OA[1].m_Number = 400;

    XCoding_BinaryEncode c;
    XBuffer stBuffer;
    XBuffer stBuffer1;
    c.SetBuffer(&stBuffer, false);
    k.ToCoding(NULL, c);
    XCoding_BinaryDecode d;
    d.SetBuffer(&stBuffer, false);
    j.ToCoding(NULL, d);
    c.SetBuffer(&stBuffer1, false);
    c.CodingReset();
    j.ToCoding(NULL,c);
    int iResult = 0;
    if (stBuffer1.getLength() != stBuffer.getLength())
    {
        cout<<"长度不一样"<<endl;
        iResult = 1;
    }
    else
    {
        for(int i = 0; i < stBuffer1->getLength(); i++)
        {
            if (stBuffer[i] != stBuffer1[i])
            {
                cout<<"KKK"<<endl;
                iResult = 2;
                break;
            }
        }
    }
    cout<<iResult<<endl;
    cout<<j.m_Number<<"\n"<<j.m_t.m_Number<<"\n"<<(XInt)j.m_t.m_Count<<endl;
//  CODING_DATA(k,c);
}   

