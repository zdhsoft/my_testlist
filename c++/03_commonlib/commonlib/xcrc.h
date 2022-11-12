///CRC的模板实现
/**
 * CRC的模板实现，支持CRC32和CRC16两种
 *
 * zdhsoft 2011 版权所有
 *
 * @file xcrc.h
 * @author zdhsoft
 * @version 1.0
 * @date 2011-10-21
 * company zdhsoft
 */
/**********************************************************************
    功能列表：  //主要函数及类
    1、CRC的模板实现

    历史:       //主要修改记录
    [author]    [time]      [version]       [descriptor]
    zdhsoft     2011-10-21  1.0             创建初始文件
***********************************************************************/
#ifndef _X_CRC_H_
#define _X_CRC_H_
#include <xconfig.h>
#include <xtype.h>
namespace zdh
{
    namespace detail
    {
        
        ///CRC32与CRC16静态方法类
        /**
         * 这个类主要提供CRC计算的静态方法，使我们可以方便的算出CRC<br>
         * @code
         * char v[] = "abcde";
         * char v1[] = "fghij";
         * XDWord vCRC32 = XCRC::CRC32(v,5);          //生成CRC32
         * XDWord vCRCNew = XCRC::CRC32(vCRC32,v1,5);  //在原有CRC32的基础上，继续生成CRC32 
         * XWord vCRC16 = XCRC::CRC16(v,5);          //生成CRC16
         * XWord vCRC16New = XCRC::CRC16(vCRC16,v1,5);  //在原有CRC16的基础上，继续生成CRC16
         * @endcode   
         */
        template<class T32 = XDWord,class T16 = XWord>
        class XCRC
        {
        public:
            /**CRC32相关的静态方法*/
            //@{
            ///生成CRC32
            /**
                在初始的CRC32的基础上，再次生成CRC32。这个方法用于生成不连续数据块的CRC32<br>
                @param [in] paramInitCRC 已计算出的CRC值或初始的CRC值
                @param [in] paramData 计算CRC的数据指针
                @param [in] paramSize 计算CRC的数据字节数
                @return 返回计算后的CRC值
             */
            static T32 CRC32(const T32 & paramInitCRC, const void * paramData,XInt paramSize);
            ///生成CRC32
            /**
                计算一个数据的CRC32值。
                @param [in] paramData 计算CRC的数据指针
                @param [in] paramSize 计算CRC的数据字节数
                @return 返回计算后的CRC值
             */
            static T32 CRC32(const void * paramData,XInt paramSize)
            {
                return CRC32(0xFFFFFFFF,paramData,paramSize);
            }
            ///生成指定类型数据的CRC值
            /**
                @param [in] paramValue 指定生成CRC32的数据
                @return 返回计算后的CRC值
             */
            template<class T>
            static T32 CRC32(const T & paramValue)
            {
                return CRC32(&paramValue,sizeof(T));
            }
            ///生成指定类型数据的CRC值
            /**
                初始的CRC32的基础上，再次生成CRC32。这个方法用于生成不连续数据块的CRC32<br>
                @param [in] paramInitCRC 已计算出的CRC值或初始的CRC值
                @param [in] paramValue 指定生成CRC32的数据
                @return 返回计算后的CRC值
             */
            template<class T>
            static T32 CRC32(const T32 & paramInitCRC, const T & paramValue)
            {
                return CRC32(paramInitCRC, &paramValue, sizeof(T));
            }
            //}@
            /**CRC16相关的静态方法*/
            ///生成CRC16
            /**
                在初始的CRC16的基础上，再次生成CRC16。这个方法用于生成不连续数据块的CRC16<br>
                @param [in] paramInitCRC 已计算出的CRC值或初始的CRC值
                @param [in] paramData 计算CRC的数据指针
                @param [in] paramSize 计算CRC的数据字节数
                @return 返回计算后的CRC值
             */
            static T16 CRC16(const T16 & paramInitCRC, const void * paramData,XInt paramSize);
            ///生成CRC16
            /**
                计算一个数据的CRC16值。
                @param [in] paramData 计算CRC的数据指针
                @param [in] paramSize 计算CRC的数据字节数
                @return 返回计算后的CRC值
             */
            static T16 CRC16(const void * paramData,XInt paramSize)
            {
                return CRC16(0,paramData,paramSize);
            }
            ///生成指定类型数据的CRC值
            /**
                @param [in] paramValue 指定生成CRC16的数据
                @return 返回计算后的CRC值
             */
            template<class T>
            static T16 CRC16(const T & paramValue)
            {
                return CRC16(&paramValue,sizeof(T));
            }
            ///生成指定类型数据的CRC值
            /**
                初始的CRC16的基础上，再次生成CRC16。这个方法用于生成不连续数据块的CRC16<br>
                @param [in] paramInitCRC 已计算出的CRC值或初始的CRC值
                @param [in] paramValue 指定生成CRC32的数据
                @return 返回计算后的CRC值
             */
            template<class T>
            static T16 CRC16(const T32 & paramInitCRC, const T & paramValue)
            {
                return CRC16(paramInitCRC, &paramValue, sizeof(T));
            }
            //}@
        private:
            static const T32 m_crcTable32[256];  ///<CRC32 参照表
            static const T16 m_crcTable16[256];  ///<CRC16 参照表
        };
        ///生成CRC32
        template<class T32,class T16> 
        T32 XCRC<T32,T16>::CRC32(const T32 & paramInitCRC, const void * paramData, XInt paramSize)
        {
            const XByte * srcdata = (const XByte *)paramData;
            T32 crc = paramInitCRC;
            if(paramSize > 0)
            {
                for(XInt i=0; i<paramSize; i++)
                {
                    crc = (crc << 8) ^ m_crcTable32[((crc >> 24) ^ (*srcdata++)) & 0xff];
                }
            }
            return crc;
        }
        ///生成CRC16
        template<class T32,class T16>
        T16 XCRC<T32,T16>::CRC16(const T16 & paramInitCRC,const void * paramData,XInt paramSize)
        {
            const XByte * srcdata = (const XByte *)paramData;
            T16 crc = paramInitCRC;
            if( paramSize > 0)
            {
                for(XInt i=0; i<paramSize; i++)
                {
                    crc =(T16)(( crc << 8 ) ^ m_crcTable16[ (( crc >> 8 ) ^ (*srcdata++)) & 0xff]);
                }
            }
            return crc;
        }
        ///CRC16参照表
        template<class T32,class T16> const T16 XCRC<T32,T16>::m_crcTable16[256] = 
        {
            0x0000,0x8005,0x800f,0x000a,0x801b,0x001e,0x0014,0x8011,
            0x8033,0x0036,0x003c,0x8039,0x0028,0x802d,0x8027,0x0022,
            0x8063,0x0066,0x006c,0x8069,0x0078,0x807d,0x8077,0x0072,
            0x0050,0x8055,0x805f,0x005a,0x804b,0x004e,0x0044,0x8041,
            0x80c3,0x00c6,0x00cc,0x80c9,0x00d8,0x80dd,0x80d7,0x00d2,
            0x00f0,0x80f5,0x80ff,0x00fa,0x80eb,0x00ee,0x00e4,0x80e1,
            0x00a0,0x80a5,0x80af,0x00aa,0x80bb,0x00be,0x00b4,0x80b1,
            0x8093,0x0096,0x009c,0x8099,0x0088,0x808d,0x8087,0x0082,
            0x8183,0x0186,0x018c,0x8189,0x0198,0x819d,0x8197,0x0192,
            0x01b0,0x81b5,0x81bf,0x01ba,0x81ab,0x01ae,0x01a4,0x81a1,
            0x01e0,0x81e5,0x81ef,0x01ea,0x81fb,0x01fe,0x01f4,0x81f1,
            0x81d3,0x01d6,0x01dc,0x81d9,0x01c8,0x81cd,0x81c7,0x01c2,
            0x0140,0x8145,0x814f,0x014a,0x815b,0x015e,0x0154,0x8151,
            0x8173,0x0176,0x017c,0x8179,0x0168,0x816d,0x8167,0x0162,
            0x8123,0x0126,0x012c,0x8129,0x0138,0x813d,0x8137,0x0132,
            0x0110,0x8115,0x811f,0x011a,0x810b,0x010e,0x0104,0x8101,
            0x8303,0x0306,0x030c,0x8309,0x0318,0x831d,0x8317,0x0312,
            0x0330,0x8335,0x833f,0x033a,0x832b,0x032e,0x0324,0x8321,
            0x0360,0x8365,0x836f,0x036a,0x837b,0x037e,0x0374,0x8371,
            0x8353,0x0356,0x035c,0x8359,0x0348,0x834d,0x8347,0x0342,
            0x03c0,0x83c5,0x83cf,0x03ca,0x83db,0x03de,0x03d4,0x83d1,
            0x83f3,0x03f6,0x03fc,0x83f9,0x03e8,0x83ed,0x83e7,0x03e2,
            0x83a3,0x03a6,0x03ac,0x83a9,0x03b8,0x83bd,0x83b7,0x03b2,
            0x0390,0x8395,0x839f,0x039a,0x838b,0x038e,0x0384,0x8381,
            0x0280,0x8285,0x828f,0x028a,0x829b,0x029e,0x0294,0x8291,
            0x82b3,0x02b6,0x02bc,0x82b9,0x02a8,0x82ad,0x82a7,0x02a2,
            0x82e3,0x02e6,0x02ec,0x82e9,0x02f8,0x82fd,0x82f7,0x02f2,
            0x02d0,0x82d5,0x82df,0x02da,0x82cb,0x02ce,0x02c4,0x82c1,
            0x8243,0x0246,0x024c,0x8249,0x0258,0x825d,0x8257,0x0252,
            0x0270,0x8275,0x827f,0x027a,0x826b,0x026e,0x0264,0x8261,
            0x0220,0x8225,0x822f,0x022a,0x823b,0x023e,0x0234,0x8231,
            0x8213,0x0216,0x021c,0x8219,0x0208,0x820d,0x8207,0x0202
        };
        ///CRC32参照表
        template<class T32,class T16> const T32 XCRC<T32,T16>::m_crcTable32[256] = 
        {
            0x00000000,0x04c11db7,0x09823b6e,0x0d4326d9,0x130476dc,0x17c56b6b,0x1a864db2,0x1e475005,
            0x2608edb8,0x22c9f00f,0x2f8ad6d6,0x2b4bcb61,0x350c9b64,0x31cd86d3,0x3c8ea00a,0x384fbdbd,
            0x4c11db70,0x48d0c6c7,0x4593e01e,0x4152fda9,0x5f15adac,0x5bd4b01b,0x569796c2,0x52568b75,
            0x6a1936c8,0x6ed82b7f,0x639b0da6,0x675a1011,0x791d4014,0x7ddc5da3,0x709f7b7a,0x745e66cd,
            0x9823b6e0,0x9ce2ab57,0x91a18d8e,0x95609039,0x8b27c03c,0x8fe6dd8b,0x82a5fb52,0x8664e6e5,
            0xbe2b5b58,0xbaea46ef,0xb7a96036,0xb3687d81,0xad2f2d84,0xa9ee3033,0xa4ad16ea,0xa06c0b5d,
            0xd4326d90,0xd0f37027,0xddb056fe,0xd9714b49,0xc7361b4c,0xc3f706fb,0xceb42022,0xca753d95,
            0xf23a8028,0xf6fb9d9f,0xfbb8bb46,0xff79a6f1,0xe13ef6f4,0xe5ffeb43,0xe8bccd9a,0xec7dd02d,
            0x34867077,0x30476dc0,0x3d044b19,0x39c556ae,0x278206ab,0x23431b1c,0x2e003dc5,0x2ac12072,
            0x128e9dcf,0x164f8078,0x1b0ca6a1,0x1fcdbb16,0x018aeb13,0x054bf6a4,0x0808d07d,0x0cc9cdca,
            0x7897ab07,0x7c56b6b0,0x71159069,0x75d48dde,0x6b93dddb,0x6f52c06c,0x6211e6b5,0x66d0fb02,
            0x5e9f46bf,0x5a5e5b08,0x571d7dd1,0x53dc6066,0x4d9b3063,0x495a2dd4,0x44190b0d,0x40d816ba,
            0xaca5c697,0xa864db20,0xa527fdf9,0xa1e6e04e,0xbfa1b04b,0xbb60adfc,0xb6238b25,0xb2e29692,
            0x8aad2b2f,0x8e6c3698,0x832f1041,0x87ee0df6,0x99a95df3,0x9d684044,0x902b669d,0x94ea7b2a,
            0xe0b41de7,0xe4750050,0xe9362689,0xedf73b3e,0xf3b06b3b,0xf771768c,0xfa325055,0xfef34de2,
            0xc6bcf05f,0xc27dede8,0xcf3ecb31,0xcbffd686,0xd5b88683,0xd1799b34,0xdc3abded,0xd8fba05a,
            0x690ce0ee,0x6dcdfd59,0x608edb80,0x644fc637,0x7a089632,0x7ec98b85,0x738aad5c,0x774bb0eb,
            0x4f040d56,0x4bc510e1,0x46863638,0x42472b8f,0x5c007b8a,0x58c1663d,0x558240e4,0x51435d53,
            0x251d3b9e,0x21dc2629,0x2c9f00f0,0x285e1d47,0x36194d42,0x32d850f5,0x3f9b762c,0x3b5a6b9b,
            0x0315d626,0x07d4cb91,0x0a97ed48,0x0e56f0ff,0x1011a0fa,0x14d0bd4d,0x19939b94,0x1d528623,
            0xf12f560e,0xf5ee4bb9,0xf8ad6d60,0xfc6c70d7,0xe22b20d2,0xe6ea3d65,0xeba91bbc,0xef68060b,
            0xd727bbb6,0xd3e6a601,0xdea580d8,0xda649d6f,0xc423cd6a,0xc0e2d0dd,0xcda1f604,0xc960ebb3,
            0xbd3e8d7e,0xb9ff90c9,0xb4bcb610,0xb07daba7,0xae3afba2,0xaafbe615,0xa7b8c0cc,0xa379dd7b,
            0x9b3660c6,0x9ff77d71,0x92b45ba8,0x9675461f,0x8832161a,0x8cf30bad,0x81b02d74,0x857130c3,
            0x5d8a9099,0x594b8d2e,0x5408abf7,0x50c9b640,0x4e8ee645,0x4a4ffbf2,0x470cdd2b,0x43cdc09c,
            0x7b827d21,0x7f436096,0x7200464f,0x76c15bf8,0x68860bfd,0x6c47164a,0x61043093,0x65c52d24,
            0x119b4be9,0x155a565e,0x18197087,0x1cd86d30,0x029f3d35,0x065e2082,0x0b1d065b,0x0fdc1bec,
            0x3793a651,0x3352bbe6,0x3e119d3f,0x3ad08088,0x2497d08d,0x2056cd3a,0x2d15ebe3,0x29d4f654,
            0xc5a92679,0xc1683bce,0xcc2b1d17,0xc8ea00a0,0xd6ad50a5,0xd26c4d12,0xdf2f6bcb,0xdbee767c,
            0xe3a1cbc1,0xe760d676,0xea23f0af,0xeee2ed18,0xf0a5bd1d,0xf464a0aa,0xf9278673,0xfde69bc4,
            0x89b8fd09,0x8d79e0be,0x803ac667,0x84fbdbd0,0x9abc8bd5,0x9e7d9662,0x933eb0bb,0x97ffad0c,
            0xafb010b1,0xab710d06,0xa6322bdf,0xa2f33668,0xbcb4666d,0xb8757bda,0xb5365d03,0xb1f740b4
        };
        ///重定义数据类型
        
        ///CRC32计数器类模板
        /**
            这个类主要是了为方便CRC32生成的各项操作，特别是对不连续的数据生成CRC32，而不用拼成一块数据来生成CRC32。<br>
            @code
            XCRC32Counter c1,c2;
            c1 << 1,2,3,4,5;             //重载了,运算符，使它生成CRC更简洁
            c2 << 1 << 2 << 3 << 4 << 5; //重载了<< 该结果与上面的,
            //上面两个方法的结果完全相同c1.getCRC() == c2.getCRC();
            char * p = "你好，这是一个测试";
            c1.MakeCRC(p,strlen(p));
            cout<<XDWord(c1)<<endl;
            @endcode
         */
        template<class T = XDWord>
        class XCRC32Counter
        {
        public:
            /**构造函数*/
            //@{
            ///默认构造函数
            XCRC32Counter()
                :m_CRC(0xFFFFFFFF)
            {}
            ///默认拷贝构造函数
            /**
                @param [in] paramCRC 指定的CRC32
             */
            XCRC32Counter(const XCRC32Counter & paramCRC)
                :m_CRC(paramCRC.m_CRC)
            {}
            ///指定初始CRC32的构造函数
            /**
                @param [in] paramCRC 指定的CRC32
             */
            XCRC32Counter(const T & paramCRC)
                :m_CRC(paramCRC)
            {}
            //}@
            ///默认赋值函数
            /**
                 @param [in] aCRC32 指定的CRC32
                 @return 当前对象的引用
             */
            XCRC32Counter & operator = (const XCRC32Counter & paramCRC32)
            {
                m_CRC = paramCRC32.m_CRC;
                return *this;
            }
            ///重置函数
            /**
                重置CRC32的值。
                @param [in] paramInitCRC 要重置的CRC，默认值为0xFFFFFFFF
             */
            void Reset(const T & paramInitCRC = 0xFFFFFFFF)
            {
                m_CRC = paramInitCRC;
            }
            ///生成指定数据类型的CRC32
            /**
                @param [in] paramValue 要生成CRC的数据
             */
            template<class S>
            void MakeCRC(const S & paramValue)
            {
                MakeCRC(&paramValue, sizeof(S));
            }
            ///生成指定数据的CRC32
            /**
                @param [in] paramData 要生成CRC的数据
                @param [in] paramSize 生成CRC32数据字节数
             */
            void MakeCRC(const void * paramData,XInt paramSize)
            {
                m_CRC = XCRC<>::CRC32(m_CRC,paramData,paramSize);
            }
            /**属性CRC*/
            //@{
            ///取当前的CRC32值
            const T & getCRC() const
            {
                return m_CRC;
            }
            ///设置当前CRC32的值
            /**
                与Reset的功能是一样的，只是它有一个默认值，而这个方法没有
                @param [in] paramCRC 要设置的CRC32的值
             */
            void setCRC(const T & paramCRC)
            {
                m_CRC = paramCRC;
            }
            //}@
            ///重载转换运算符
            operator T() const
            {
                return m_CRC;
            }
            /**重载<<,运算符，简化CRC32生成*/
            //@{
            ///重载<<运算符
            template<class S>
            XCRC32Counter & operator << (const S & paramValue)
            {
                MakeCRC(&paramValue,sizeof(S));
                return *this;
            }
            ///重载,运算符
            template<class S>
            XCRC32Counter & operator ,(const S & paramValue)
            {
                MakeCRC(&paramValue,sizeof(S));
                return *this;
            }
            //}@
        private:
            T m_CRC;    //生成的CRC32值
        };
        ///CRC16计数器类模板
        /**
         */
        template<class T = XWord>
        class XCRC16Counter
        {
        public:
            /**构造函数*/
            //@{
            ///默认构造函数
            XCRC16Counter()
                :m_CRC(0)
            {}
            ///默认拷贝构造函数
            /**
                @param [in] paramCRC 指定的CRC16
             */
            XCRC16Counter(const XCRC16Counter & paramCRC)
                :m_CRC(paramCRC.m_CRC)
            {}
            ///指定初始CRC16的构造函数
            /**
                @param [in] paramCRC 指定的CRC32
             */
            XCRC16Counter(const T & paramCRC)
                :m_CRC(paramCRC)
            {}
            //}@
            ///默认赋值函数
            /**
                 @param [in] paramCRC 指定的CRC16
                 @return 当前对象的引用
             */
            XCRC16Counter & operator = (const XCRC16Counter & paramCRC)
            {
                m_CRC = paramCRC.m_CRC;
                return *this;
            }
            ///重置函数
            /**
                重置CRC32的值。
                @param [in] paramInitCRC 要重置的CRC，默认值为0
             */
            void Reset(const T & paramInitCRC = 0)
            {
                m_CRC = paramInitCRC;
            }
            ///生成指定数据类型的CRC16
            /**
                @param [in] paramValue 要生成CRC的数据
             */
            template<class S>
            void MakeCRC(const S & paramValue)
            {
                MakeCRC(&paramValue, sizeof(S));
            }
            ///生成指定数据的CRC16
            /**
                @param [in] paramData 要生成CRC的数据
                @param [in] paramSize 生成CRC16数据字节数
             */
            void MakeCRC(const void * paramData,XInt paramSize)
            {
                m_CRC = XCRC<>::CRC16(m_CRC,paramData,paramSize);
            }
            /**属性CRC*/
            //@{
            ///取当前的CRC16值
            const T & getCRC() const
            {
                return m_CRC;
            }
            ///设置当前CRC16的值
            /**
                与Reset的功能是一样的，只是它有一个默认值，而这个方法没有
                @param [in] paramCRC 要设置的CRC16的值
             */
            void setCRC(const T & paramCRC)
            {
                m_CRC = paramCRC;
            }
            //}@
            ///重载转换运算符
            operator T() const
            {
                return m_CRC;
            }
            /**重载<<,运算符，简化CRC16生成*/
            //@{
            ///重载<<运算符
            template<class S>
            XCRC16Counter & operator << (const S & paramValue)
            {
                MakeCRC(&paramValue,sizeof(S));
                return *this;
            }
            ///重载,运算符
            template<class S>
            XCRC16Counter & operator ,(const S & paramValue)
            {
                MakeCRC(&paramValue,sizeof(S));
                return *this;
            }
            //}@
        private:
            T m_CRC; //生成的CRC16值
        };
    }
    typedef detail::XCRC<XDWord, XWord> XCRC;
    typedef detail::XCRC32Counter<XDWord> XCRC32Counter;
    typedef detail::XCRC16Counter<XWord> XCRC16Counter;
}
#endif
