//日志类
#ifndef _X_LOG_H_
#define _X_LOG_H_
#include <xconfig.h>
#include <xos_include.h>
#include <xdatetime.h>
#include <cstdio>
#include <cstdarg>
#include <xsyn.h>
#include <xstring.h>
#include <xsingleton.h>
#include <string>
#include <xdynamic_array.h>
namespace zdh
{
    //取当前线程ID
    inline XDWord LogGetCurrentThreadID()
    {
        #if defined(OS_WINDOWS)
            return GetCurrentThreadId();
        #elif defined(OS_LINUX)
            return (XDWord)pthread_self();
        #else
            return 0;
        #endif
    }
    //取当前进程ID
    inline XDWord LogGetCurrentProcessID()
    {
        #if defined(OS_WINDOWS)
            return GetCurrentProcessId();
        #elif defined(OS_LINUX)
            return getpid();
        #else
            return 0;
        #endif
    }
    //常量
    enum EnumConstant
    {
        EC_MAX_LOG_SIZE    = 1024*1024, ///<1M
        EC_LEVEL_TRACE     = 0,
        EC_LEVEL_DEBUG     = 1,
        EC_LEVEL_INFO      = 2,
        EC_LEVEL_WARN      = 3,
        EC_LEVEL_ERROR     = 4,
        EC_LEVEL_FATAL     = 5,
        EC_NORMAL_LOG      = 0,     ///<普通的日志
        EC_ERROR_LOG       = 1,     ///<错误的日志
    };
	

	class XLogBase
	{
	public:
		XLogBase()
		{}
		virtual ~XLogBase()
		{}
		virtual XLogBase * OpenRecord() = 0;
		virtual XLogBase * CloseRecord() = 0;
	};

	class XLogRecord
	{
	public:
		XLogRecord(XLogBase * paramLog)
			:m_Log(paramLog), m_CheckFlag(true)
		{
		}
		~XLogRecord()
		{
			m_Log->CloseRecord();
		}
		bool Check()
		{
			if (m_CheckFlag)
			{
				m_CheckFlag = false;
				return true;
			}
			else
			{
				return false;
			}
		}
	private:
		XLogBase * m_Log;
		bool m_CheckFlag;
	};

	//日志输出基类
	class XLogEndBase
	{
	public:
		XLogEndBase(){}
		virtual ~XLogEndBase(){}

		virtual void OutLog(int /*paramLogLevel*/, const XAnsiString &/* paramLog*/)
		{
		}
	private:
	};

	//输出到文件
	class XLogEndFile : public XLogEndBase
	{
	public:
		XLogEndFile()
			:m_FileSize(1024*1024),
			 m_FP(NULL)
		{ 
		}
		int Init(const XAnsiString & paramFileName, int paramFileSize = 1024 * 1024)
		{
			CloseFileLog();
			m_FileName = paramFileName;
			m_FileSize = paramFileSize;
			m_FP = fopen(m_FileName.c_str(), "a");
			XInt iRet;
			if (isNULL(m_FP))
			{
				iRet = ERR_FAIL;
				CloseFileLog();
			}
			else
			{
				iRet = ERR_OK;
			}
			return iRet;
		}

		virtual ~XLogEndFile()
		{
			CloseFileLog();
		}

		virtual void OutLog(int /*paramLogLevel*/, const XAnsiString & paramLog)
		{
			CheckFileSize(paramLog.getLength());
			if (isNotNULL(m_FP))
			{
				const char * LN = "\n";
				fwrite(paramLog.c_str(), paramLog.length(), 1, m_FP);
				fwrite(LN, strlen(LN), 1, m_FP);
				fflush(m_FP);
			}
		}
	private:
		///关闭文件日志输出
		void CloseFileLog()
		{
			if (isNotNULL(m_FP))
			{
				fclose(m_FP);
				m_FP = NULL;
			}
		}
		///检查文件大小
		void CheckFileSize(XLong paramOutLength)
		{
			if (isNULL(m_FP))
			{
				return;
			}
			XDateTime<XAnsiString> stDateTime;
			stDateTime.SetNowDateTime();

			if (((XLong)ftell(m_FP) + paramOutLength) > m_FileSize)
			{
				XInt iYear, iMonth, iDay, iHour, iMinute, iSecond, iMillis;
				stDateTime.DecodeDateTime(iYear, iMonth, iDay, iHour, iMinute, iSecond, iMillis);
				XAnsiString strFileName;
				//循环10次，找到一个不冲突的文件名
				for (XInt i = 0; i < 10; i++)
				{
					strFileName = m_FileName;
					strFileName.cat_printf(".%04d%02d%02d.%02d%02d%02d.%03d-%03d.log", iYear, iMonth, iDay, iHour, iMinute, iSecond, iMillis, rand() % 1000);
					FILE * pFP = fopen(strFileName.c_str(), "r");
					if (pFP == NULL)
					{
						fclose(m_FP);
						rename(m_FileName.c_str(), strFileName.c_str());
						m_FP = fopen(m_FileName.c_str(), "w");
						break;
					}
					else
					{
						fclose(pFP);
					}
				}
			}
		}
	private:
		XAnsiString m_FileName;
		XInt        m_FileSize;
		FILE *		m_FP;
	};

	//输出到控制台
	class XLogEndConsole : public XLogEndBase
	{
	public:
		XLogEndConsole()
		{
		}
		virtual ~XLogEndConsole()
		{
		}
		virtual void OutLog(int /*paramLogLevel*/, const XAnsiString & paramLog)
		{
			printf("%s\n", paramLog.c_str());
		}
	};

	//输出到VS调试窗口
	class XLogEndOutputDebug : public XLogEndBase
	{
	public:
		XLogEndOutputDebug()
		{
		}
		virtual ~XLogEndOutputDebug()
		{
		}
		virtual void OutLog(int /*paramLogLevel*/, const XAnsiString & paramLog)
		{
			#if defined(OS_WINDOWS)        
				OutputDebugStringA(paramLog.c_str());
				OutputDebugStringA("\n");
			#endif
		}
	};

    //日志
    template<int N, class Lock = XNullLock>
	class XLog : public XLogBase
	{
	public:
		XLog()
			:m_TraceFlag(true),
			m_DebugFlag(true),
			m_InfoFlag(true),
			m_WarnFlag(true),
			m_ErrorFlag(true),
			m_FatalFlag(true),
			m_StreamBeginFlag(false)
		{
		}

		virtual ~XLog()
		{
			FlashStream();
			for (int i = 0; i < m_LogEndList.getLength(); i++)
			{
				delete m_LogEndList[i];
			}
			m_LogEndList.Clear();
		}

		/********************************************************************************
		  Title: 增加日志输出终端
		 
		  FullName:   zdh::XLog<N, Lock>::AddLogEnd
		  Access:     public 
		  @param [in] paramEnd 要增加的终端
		  @return     int 增加结果
			- 0 增加成功
			- 1 paramEnd为null
			- 2 该终端已经存在
		  @author     zdhsoft
		  @date       2014/05/21
		  @file       xlog.h
		 ********************************************************************************/
		int AddLogEnd(XLogEndBase * paramEnd)
		{
			if (isNULL(paramEnd)) return 1;
			for (int i = 0; i < m_LogEndList.getLength(); i++)
			{
				if (m_LogEndList[i] == paramEnd) return 2;
			}
			m_LogEndList.Append(paramEnd);
			return ERR_OK;
		}

		/********************************************************************************
		  Title: 移除日志终端
		 
		  FullName:   zdh::XLog<N, Lock>::RemoveLogEnd
		  Access:     public 
		  @param [in] paramEnd 要移动的终端
		  @return     int 移动结果
			- 0 移动成功
			- 1 paramEnd为null
			- 2 没有要移除的终端
		  @author     zdhsoft
		  @date       2014/05/21
		  @file       xlog.h
		 ********************************************************************************/
		int RemoveLogEnd(XLogEndBase * paramEnd)
		{
			if (isNULL(paramEnd)) return 1;
			bool bHas = false;
			for (int i = m_LogEndList.getLastIndex(); i>= 0; i--)
			{
				if (m_LogEndList[i] == paramEnd)
				{
					m_LogEndList.Remove(i);
					bHas = true;
				}
			}
			if (bHas) return ERR_OK;
			else return 2;
		}

		///等级标志设置
		void SetFlag(bool paramTrace, bool paramDebug, bool paramInfo, bool paramWarn, bool paramError, bool paramFatal)
		{
			m_TraceFlag = paramTrace;
			m_DebugFlag = paramDebug;
			m_InfoFlag = paramInfo;
			m_WarnFlag = paramWarn;
			m_ErrorFlag = paramError;
			m_FatalFlag = paramFatal;
		}

		bool getStreamBeginFlag() const
		{
			return m_StreamBeginFlag;
		}

		///取指定的等级标志
		bool GetLevelFlag(XInt paramLevel) const
		{
			switch (paramLevel)
			{
			case EC_LEVEL_TRACE:
				return m_TraceFlag;
			case EC_LEVEL_DEBUG:
				return m_DebugFlag;
			case EC_LEVEL_INFO:
				return m_InfoFlag;
			case EC_LEVEL_WARN:
				return m_WarnFlag;
			case EC_LEVEL_ERROR:
				return m_ErrorFlag;
			case EC_LEVEL_FATAL:
				return m_FatalFlag;
			default:
				return false;
			}
		}
		///设置等级标志
		void SetLevelFlag(XInt paramLevel, bool paramFlag)
		{
			switch (paramLevel)
			{
			case EC_LEVEL_TRACE:
				m_TraceFlag = paramFlag;
				break;
			case EC_LEVEL_DEBUG:
				m_DebugFlag = paramFlag;
				break;
			case EC_LEVEL_INFO:
				m_InfoFlag = paramFlag;
				break;
			case EC_LEVEL_WARN:
				m_WarnFlag = paramFlag;
				break;
			case EC_LEVEL_ERROR:
				m_ErrorFlag = paramFlag;
				break;
			case EC_LEVEL_FATAL:
				m_FatalFlag = paramFlag;
				break;
			}
		}

		void Trace(const char * paramFile, int paramLine, const char * paramFormat, ...)
		{
			if ((!m_TraceFlag) || m_LogEndList.isEmpty() ) return;
			va_list argptr;
			va_start(argptr, paramFormat);
			WriteLog(paramFile, paramLine, EC_LEVEL_TRACE, paramFormat, argptr);
			va_end(argptr);
		}

		void Debug(const char * paramFile, int paramLine, const char * paramFormat, ...)
		{
			if ((!m_DebugFlag) || m_LogEndList.isEmpty()) return;
			va_list argptr;
			va_start(argptr, paramFormat);
			WriteLog(paramFile, paramLine, EC_LEVEL_DEBUG, paramFormat, argptr);
			va_end(argptr);
		}

		void Info(const char * paramFile, int paramLine, const char * paramFormat, ...)
		{
			if ((!m_InfoFlag) || m_LogEndList.isEmpty()) return;
			va_list argptr;
			va_start(argptr, paramFormat);
			WriteLog(paramFile, paramLine, EC_LEVEL_INFO, paramFormat, argptr);
			va_end(argptr);
		}

		void Warn(const char * paramFile, int paramLine, const char * paramFormat, ...)
		{
			if ((!m_WarnFlag) || m_LogEndList.isEmpty()) return;
			va_list argptr;
			va_start(argptr, paramFormat);
			WriteLog(paramFile, paramLine, EC_LEVEL_WARN, paramFormat, argptr);
			va_end(argptr);
		}

		void Error(const char * paramFile, int paramLine, const char * paramFormat, ...)
		{
			if ((!m_ErrorFlag) || m_LogEndList.isEmpty()) return;
			va_list argptr;
			va_start(argptr, paramFormat);
			WriteLog(paramFile, paramLine, EC_LEVEL_ERROR, paramFormat, argptr);
			va_end(argptr);
		}

		void Fatal(const char * paramFile, int paramLine, const char * paramFormat, ...)
		{
			if ((!m_FatalFlag) || m_LogEndList.isEmpty()) return;
			va_list argptr;
			va_start(argptr, paramFormat);
			WriteLog(paramFile, paramLine, EC_LEVEL_FATAL, paramFormat, argptr);
			va_end(argptr);
		}

		XLog & StreamTrace(const char * paramFile, XInt paramLine)
		{
			ResetStream(paramFile, paramLine, EC_LEVEL_TRACE);
			m_StreamBeginFlag = true;
			return *this;
		}

		XLog & StreamDebug(const char * paramFile, XInt paramLine)
		{
			ResetStream(paramFile, paramLine, EC_LEVEL_DEBUG);
			m_StreamBeginFlag = true;
			return *this;
		}

		XLog & StreamInfo(const char * paramFile, XInt paramLine)
		{
			ResetStream(paramFile, paramLine, EC_LEVEL_INFO);
			m_StreamBeginFlag = true;
			return *this;
		}
		XLog & StreamWarn(const char * paramFile, XInt paramLine)
		{
			ResetStream(paramFile, paramLine, EC_LEVEL_WARN);
			m_StreamBeginFlag = true;
			return *this;
		}
		XLog & StreamError(const char * paramFile, XInt paramLine)
		{
			ResetStream(paramFile, paramLine, EC_LEVEL_ERROR);
			m_StreamBeginFlag = true;
			return *this;
		}
		XLog & StreamFatal(const char * paramFile, XInt paramLine)
		{
			ResetStream(paramFile, paramLine, EC_LEVEL_FATAL);
			m_StreamBeginFlag = true;
			return *this;
		}

		XLogBase * OpenRecord()
		{
			#if CONFIG_MULT_THREAD
				m_Lock.Enter();
			#endif
			return this;
		}
		XLogBase * CloseRecord()
		{
			FlashStream();
			#if CONFIG_MULT_THREAD
				m_Lock.Leave();
			#endif
			return this;
		}

        void FlashStream()
        {
            if(m_StreamBeginFlag)
            {
				va_list argptr;
#if defined(OS_WINDOWS)
				argptr = NULL;
#endif
				this->WriteLog("", 0, 0, "", argptr, true);
            }
            m_StreamBeginFlag = false;
        }

        XAnsiString & getStreamLogContent() 
        {
            return m_StreamLogContent;
        }

        const XAnsiString & getStreamLogContent() const
        {
            return m_StreamLogContent;
        }
    private:
        ///重置流日志
        void ResetStream(const char * paramFile, XInt paramLine, XInt paramLevel)
        {
            m_StreamFile        = paramFile;
            m_StreamLine        = paramLine;
            m_StreamProcessID   = LogGetCurrentProcessID();
            m_StreamLevel       = paramLevel;

            m_StreamDateTime.SetNowDateTime();
            m_StreamLogContent.ToEmptyString();
        }

        ///取指定日志的级别字符串
        static const char * getLevelString(XInt paramLevel)
        {
            static const char * sLevel[] = { "TRACE","DEBUG"," INFO"," WARN","ERROR","FATAL" };
            return sLevel[paramLevel];
        }
        ///写入日志        
        void WriteLog(const char * paramFile, int paramLine, XInt paramLevel, const char * paramFormat, va_list argptr, bool paramStream = false)
        {
            static char                     stDateTimeString[24];
            static XAnsiString              sFinal;
            static XAnsiString              sInfoBuffer;
            static XDateTime<XAnsiString>   sDateTime;

            #if CONFIG_MULT_THREAD
				if (!paramStream) m_Lock.Enter();
            #endif
            if (paramStream)
            {
                m_StreamDateTime.ToString(stDateTimeString);                
                sFinal.nprintf(4096, "[%s,%s][%u] %s(%s:%d)",
                    getLevelString(m_StreamLevel), 
                    stDateTimeString,
                    m_StreamProcessID,
                    m_StreamLogContent.c_str(),
                    m_StreamFile.c_str(),
                    m_StreamLine);
				paramLevel = m_StreamLevel;
            }
            else
            {
                sDateTime.SetNowDateTime();
                sDateTime.ToString(stDateTimeString);

                sInfoBuffer.vnprintf(4096, paramFormat, argptr);
                sFinal.nprintf(4096, "[%s,%s][%u] %s(%s:%d)", 
                    getLevelString(paramLevel), 
                    stDateTimeString,
                    LogGetCurrentProcessID(),
                    sInfoBuffer.c_str(),
                    paramFile,
                    paramLine);
            }
			int iEndCnt = m_LogEndList.getLength();
			for (int i = 0; i < iEndCnt; i++)
			{
				m_LogEndList[i]->OutLog(paramLevel, sFinal);
			}

			#if CONFIG_MULT_THREAD
				if (!paramStream) m_Lock.Leave();
			#endif
        }
    private:
        #if CONFIG_MULT_THREAD
        Lock                        m_Lock;           
        #endif
        //等级控制
        bool                        m_TraceFlag;
        bool                        m_DebugFlag;
        bool                        m_InfoFlag;
        bool                        m_WarnFlag;
        bool                        m_ErrorFlag;
        bool                        m_FatalFlag;
        //流日志相关
        bool                        m_StreamBeginFlag;  ///<日志开始标志
        XDateTime<XAnsiString>      m_StreamDateTime;   ///<流日志时间
        XInt                        m_StreamLevel;      ///<流日志级别
        XAnsiString                 m_StreamFile;       ///<对应调用的文件名
        XInt                        m_StreamLine;       ///<对应调用的行号
        XDWord                      m_StreamProcessID;  ///<对应进程的ID
        XAnsiString                 m_StreamLogContent; ///<日志的内容
		//
		XDynamicArray<XLogEndBase *> m_LogEndList;		///<日志列表
    };   

    template<int N, class T>
    inline XLog<N, T> & operator << (XLog<N, T> & paramStream, const char * paramString)
    {
        if (paramStream.getStreamBeginFlag())
        {
            paramStream.getStreamLogContent().AppendString(paramString);
        }
        return paramStream;
    }
    template<int N,class T>
    inline XLog<N, T> & operator << (XLog<N, T> & paramStream, const XAnsiString & paramString)
    {
        if (paramStream.getStreamBeginFlag())
        {
            paramStream.getStreamLogContent().AppendString(paramString);
        }
        return paramStream;
    }

    template<int N, class T>
    inline XLog<N, T> & operator << (XLog<N, T> & paramStream, const XInt & paramValue)
    {
        if(paramStream.getStreamBeginFlag())
        {
            paramStream.getStreamLogContent() << paramValue;
        }
        return paramStream;
    }
    template<int N, class T>
    inline XLog<N, T> & operator << (XLog<N, T> & paramStream, const XDWord & paramValue)
    {
        if(paramStream.getStreamBeginFlag())
        {
            paramStream.getStreamLogContent() << paramValue;
        }
        return paramStream;
    }
    template<int N, class T>
    inline XLog<N,T> & operator << (XLog<N, T> & paramStream, const XLong & paramValue)
    {
        if(paramStream.getStreamBeginFlag())
        {
            paramStream.getStreamLogContent() << paramValue;
        }
        return paramStream;
    }

    template<int N, class T>
    inline XLog<N,T> & operator << (XLog<N,T> & paramStream, const XDDWord & paramValue)
    {
        if(paramStream.getStreamBeginFlag())
        {
            paramStream.getStreamLogContent() << paramValue;
        }
        return paramStream;
    }

    template<int N,class T>
    inline XLog<N,T> & operator << (XLog<N,T> & paramStream, const XChar & paramValue)
    {
        if(paramStream.getStreamBeginFlag())
        {
            paramStream.getStreamLogContent().AppendChar(paramValue);
        }
        return paramStream;
    }

    template<int N,class T>
    inline XLog<N,T> & operator << (XLog<N,T> & paramStream, const XByte & paramValue)
    {
        if(paramStream.getStreamBeginFlag())
        {
            paramStream.getStreamLogContent() << paramValue;
        }
        return paramStream;
    }

    template<int N,class T>
    inline XLog<N,T> & operator <<(XLog<N,T> & paramStream, const XWord & paramValue)
    {
        if(paramStream.getStreamBeginFlag())
        {
            paramStream.getStreamLogContent() << paramValue;
        }
        return paramStream;
    }

    template<int N,class T>
    inline XLog<N,T> & operator <<(XLog<N,T> & paramStream, const XShort & paramValue)
    {
        if(paramStream.getStreamBeginFlag())
        {
            paramStream.getStreamLogContent() << paramValue;
        }
        return paramStream;
    }

    template<int N,class T>
    inline XLog<N,T> & operator <<(XLog<N,T> & paramStream, const XFloat & paramValue)
    {
        if(paramStream.getStreamBeginFlag())
        {
            paramStream.getStreamLogContent().cat_printf("%f", paramValue);
        }
        return paramStream;
    }

    template<int N,class T>
    inline XLog<N,T> & operator <<(XLog<N,T> & paramStream, const XDouble & paramValue)
    {
        if(paramStream.getStreamBeginFlag())
        {
            paramStream.getStreamLogContent().cat_printf("%lf", paramValue);
        }
        return paramStream;
    }

    template<int N,class T>
    inline XLog<N,T> & operator <<(XLog<N,T> & paramStream, const bool & paramValue)
    {
        if(paramStream.getStreamBeginFlag())
        {
            if (paramValue)
            {
                paramStream.getStreamLogContent().AppendString("true");
            }
            else
            {
                paramStream.getStreamLogContent().AppendString("false");
            }
        }
        return paramStream;
    }

    //typedef XLog<XNullLock> TLog;
} // end of namespace zdh
#if defined(OS_WINDOWS)
	#define ZDH_LOG_OBJECT (zdh::XSingletonSample<zdh::XLog<zdh::EC_NORMAL_LOG, zdh::XNullLock>, zdh::EC_NORMAL_LOG>::getInstance())
#elif defined(OS_LINUX)
	#define ZDH_LOG_OBJECT (zdh::XSingletonSample<zdh::XLog<zdh::EC_NORMAL_LOG, zdh::XCriticalSection>, zdh::EC_NORMAL_LOG>::getInstance())
#endif

	#define ZDH_TRACE(...) ZDH_LOG_OBJECT->Trace(__FILE__,__LINE__,__VA_ARGS__)
	#define ZDH_DEBUG(...) ZDH_LOG_OBJECT->Debug(__FILE__,__LINE__,__VA_ARGS__)
	#define ZDH_INFO(...) ZDH_LOG_OBJECT->Info (__FILE__,__LINE__,__VA_ARGS__)
	#define ZDH_WARN(...)  ZDH_LOG_OBJECT->Warn (__FILE__,__LINE__,__VA_ARGS__)
	#define ZDH_ERROR(...) ZDH_LOG_OBJECT->Error(__FILE__,__LINE__,__VA_ARGS__)
	#define ZDH_FATAL(...) ZDH_LOG_OBJECT->Fatal(__FILE__,__LINE__,__VA_ARGS__)


	#define STREAM_TRACE for(zdh::XLogRecord log_rec = ZDH_LOG_OBJECT; log_rec.Check();) \
		((*ZDH_LOG_OBJECT).StreamTrace(__FILE__,__LINE__))

	#define STREAM_DEBUG for(zdh::XLogRecord log_rec =ZDH_LOG_OBJECT; log_rec.Check();) \
		((*ZDH_LOG_OBJECT).StreamDebug(__FILE__, __LINE__))

	#define STREAM_INFO  for(zdh::XLogRecord log_rec = ZDH_LOG_OBJECT; log_rec.Check();) \
		((*ZDH_LOG_OBJECT).StreamInfo (__FILE__,__LINE__))

	#define STREAM_WARN  for(zdh::XLogRecord log_rec = ZDH_LOG_OBJECT; log_rec.Check();) \
		((*ZDH_LOG_OBJECT).StreamWarn (__FILE__,__LINE__))

	#define STREAM_ERROR for(zdh::XLogRecord log_rec =ZDH_LOG_OBJECT; log_rec.Check();) \
		((*ZDH_LOG_OBJECT).StreamError(__FILE__,__LINE__))

	#define STREAM_FATAL for(zdh::XLogRecord log_rec =ZDH_LOG_OBJECT; log_rec.Check();) \
		((*ZDH_LOG_OBJECT).StreamFatal(__FILE__,__LINE__))

    #if defined(_DEBUG) //debug模式下输出的日志
		#define DLOG_TRACE(...) ZDH_LOG_OBJECT->Trace(__FILE__,__LINE__,__VA_ARGS__)
		#define DLOG_DEBUG(...) ZDH_LOG_OBJECT->Debug(__FILE__,__LINE__,__VA_ARGS__)
		#define DLOG_INFO(...)  ZDH_LOG_OBJECT->Info (__FILE__,__LINE__,__VA_ARGS__)
		#define DLOG_WARN(...)  ZDH_LOG_OBJECT->Warn (__FILE__,__LINE__,__VA_ARGS__)
		#define DLOG_ERROR(...) ZDH_LOG_OBJECT->Error(__FILE__,__LINE__,__VA_ARGS__)
		#define DLOG_FATAL(...) ZDH_LOG_OBJECT->Fatal(__FILE__,__LINE__,__VA_ARGS__)
    #else
        #define DLOG_TRACE(...)
        #define DLOG_DEBUG(...)
        #define DLOG_INFO(...)
        #define DLOG_WARN(...)
        #define DLOG_ERROR(...)
        #define DLOG_FATAL(...)
    #endif

#endif

