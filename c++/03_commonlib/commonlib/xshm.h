#ifndef _X_SHM_H_
#define _X_SHM_H_
#include <xos_include.h>
#include <xlog.h>
namespace zdh
{
   
#ifdef OS_WINDOWS
     ///�����ڴ� 
    class XShm
    {
    public:
        XShm():
          m_Key(0), 
          m_Size(0), 
          m_Shm(0), 
          m_Buf(0)
        {
        }

        ~XShm()
        {
            Close();
        }

        /// ������������һ�鹲���ڴ�
        int Create(const char* paramKey, XInt paramSize)
        {

            m_Key = paramKey;
            m_Size = paramSize;
            m_Shm = CreateFileMappingA(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, (XDWord)m_Size, m_Key.c_str());
            if (m_Shm && (xerrno() == ERROR_ALREADY_EXISTS))
            {
                CloseHandle(m_Shm);
                m_Shm = OpenFileMappingA(FILE_MAP_ALL_ACCESS, FALSE, m_Key.c_str());
                if (!m_Shm)
                {
                    ZDH_ERROR("OpenFileMapping: %d", xerrno());
                    return -1;
                }
            }

            if (m_Shm)
            {
                m_Buf = (char*) MapViewOfFile(m_Shm, FILE_MAP_ALL_ACCESS, 0, 0, 0);
                if (!m_Buf)
                {
                    ZDH_ERROR("MapViewOfFile: %d, Handle=%x", xerrno(), m_Shm);
                    CloseHandle(m_Shm);
                    return -1;
                }

                return 0;
            }
            else
            {
                ZDH_ERROR("CreateFileMapping: %d", xerrno());
                return -1;
            }
        }

        /// �ر�һ�鹲���ڴ�
        int Close()
        {
            if (m_Buf)
            {
                if (!UnmapViewOfFile(m_Buf))
                {
                    ZDH_WARN("UnmapViewOfFile: %d", xerrno());
                }
                m_Buf = NULL;
            }

            if (m_Shm)
            {
                if (!CloseHandle(m_Shm))
                {
                    ZDH_WARN("CloseHandle: %d", xerrno());
                }
                m_Shm = NULL;
            }

            return 0;
        }

    public:
        char*        GetBuffer() const { return m_Buf; }
        const char*  GetKey()    const { return m_Key.c_str(); }
        XInt         GetSize()   const { return m_Size; }

    protected:
        XAnsiString     m_Key;
        XInt            m_Size;

        HANDLE          m_Shm;
        char*           m_Buf;
    };

#else

    #include <sys/ipc.h>
    #include <sys/shm.h>

    class XShm
    {
    public:
        XShm() 
            :m_Key(0), 
             m_Size(0), 
             m_Shm(0), 
             m_Buf(0)
        {
        }

        /// �˳�ʱ���رչ����ڴ�
        ~XShm()
        {
        }

        /// ������������һ�鹲���ڴ�
        int Create(key_t paramKey, XInt paramSize)
        {
            m_Key  = (XDWord) paramKey;
            m_Size = paramSize;

            m_Shm = shmget(paramKey, m_Size, IPC_CREAT|IPC_EXCL|0666);
            if (m_Shm < 0)
            {
                if (xerrno() != EEXIST)
                {
                    ZDH_ERROR("shmget create: %d", xerrno());
                    return -1;
                }

                m_Shm = shmget(paramKey, m_Size, 0666);
                if (m_Shm < 0)
                {
                    m_Shm = shmget(paramKey, 0, 0666);
                    if (m_Shm < 0)
                    {
                        ZDH_ERROR("shmget 0: %d", xerrno());
                        return -2;
                    }

                    if (shmctl(m_Shm, IPC_RMID, 0))
                    {
                        ZDH_ERROR("shmctl %d: %d", m_Shm, xerrno());
                        return -3;
                    }

                    m_Shm = shmget(paramKey, m_Size, IPC_CREAT|IPC_EXCL|0666);
                    if (m_Shm < 0)
                    {
                        ZDH_ERROR("shmget recreate: %d", xerrno());
                        return -4;
                    }
                }
                ZDH_TRACE("attach shm ok, id = %d", m_Shm);
            }
            else
            {
                ZDH_TRACE("create shm ok, id = %d", m_Shm);
            }

            m_Buf = (char*) shmat(m_Shm, 0, 0);
            if (!m_Buf)
            {
                ZDH_ERROR("shmat %d: %d", m_Shm, xerrno());
                return -5;
            }

            return 0;
        }

        /// ������������һ�鹲���ڴ�
        /// pszPathName��ftok�Ĳ���, pszPathName��Ӧ���ļ�����Ҫ����
        int Create(const char* paramPathName, size_t paramSize)
        {
            ////��ȡ�ļ�����Ŀ¼
            //XAnsiString s = paramPathName;
            //if (s.rfind('/') == XAnsiString::npos || s[s.length()-1] == '/')
            //{
            //    ZDH_ERROR("ftok(%s) failed, file path error", paramPathName);
            //    return -1;
            //}
            //s = s.substr(0, s.rfind('/')); //ȡ�ļ�����Ŀ¼
            ////iKey����Ϊftok�ĵڶ������ٴβ������㣬��ֹ�ظ�
            //key_t iKey = ftok(s.c_str(), 0);
            //ZDH_TRACE("dir key = %d", iKey);

            ////��ֹ�ظ�
            //iKey = ftok(paramPathName, iKey);
            //if (iKey == -1)
            //{
            //    ZDH_ERROR("ftok(%s) failed %d", paramPathName, xerrno());
            //    return -1;
            //}

            //ZDH_TRACE("dir key2 = %d", iKey);
            //ֱ��ȡ�ļ���inode
            struct stat stStat;
            memset(&stStat, 0, sizeof(stStat));
            if (stat(paramPathName, &stStat) != 0)
            {
                return xerrno();
            }

            //return ;
            return Create(stStat.st_ino, paramSize);
        }

        /// �ر�һ�鹲���ڴ�
        XInt Close()
        {
            if (m_Shm > 0)
            {
                if (shmctl(m_Shm, IPC_RMID, 0))
                {
                    ZDH_ERROR("shmctl %d: %d", m_Shm, xerrno());
                    return ERR_FAIL;
                }
            }
            return ERR_OK;       
        }

        char*  GetBuffer() const { return m_Buf; }
        key_t  GetKey()    const { return m_Key; }
        XInt   GetSize()   const { return m_Size; }
    protected:
        unsigned int    m_Key;
        XInt            m_Size;
        int             m_Shm;
        char*           m_Buf;
    };

#endif
}
#endif
