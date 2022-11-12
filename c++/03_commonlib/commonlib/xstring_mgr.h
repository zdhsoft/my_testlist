//字符串资源管理器
/**
	这个类提供了一个基于ini的键值对字符串读取类，可以用于多语言配置。支持UTF-8格式的文本读取
	@author zdhsoft
	@date 2014-6-30
 */
#ifndef _X_STRING_MANAGER_H_
#define _X_STRING_MANAGER_H_
#include <xstring.h>
#include <xini.h>
#include <xmap.h>
namespace zdh
{

	class XStringMgr
	{
	public:
		typedef XMap<XAnsiString, XAnsiString>     TStringKeyValue;		//定义这里用到的KeyValue Ｍap
		typedef XMap<XAnsiString, TStringKeyValue> TStringSection;      //定义Key Section Map
	public:
		XStringMgr()
		{}
		~XStringMgr()
		{
			m_Map.Clear();
		}
		//加载指定的Ini
		XInt Load(const XAnsiString & paramFileName, bool paramClear = true)
		{
			if (paramClear) m_Map.Clear();
			XIniText stIni;
			if (!stIni.Load(paramFileName)) return ERR_FAIL;
			
			for (int i = 0; i < stIni.getSectionCount(); i++)
			{
				XIniText::TSection * pSection = stIni.getSection(i);
				
				TStringKeyValue & stKeyValue = m_Map[pSection->getSectionName()];
				for (int j = 0; j < pSection->getLength(); j++)
				{
					XIniText::TEntry * pEntry = pSection->getEntry(j);
					
					if (isNULL(pEntry)) continue;
					if (pEntry->getEntryType() != EIET_COMMON_ENTRY) continue;
					
					XIniText::TEntryCommon * pCommonEntry = dynamic_cast<XIniText::TEntryCommon *>(pEntry);
					if (isNULL(pCommonEntry)) continue;
					
					stKeyValue[pCommonEntry->getKey().getField()] = pCommonEntry->getValue().getField();
				}
			}
			return ERR_OK;
		}
		//取指定字符串对象
		/**
			如果没有找到则会返回NULL
			@param [in] paramSection Section名称
			@param [in] paramKey	 Key
			@return const XAnsiString * 返回结果
				- NULL 未找到，则返回NULL
				- NOT NULL 找到了，并返回XAnsiString的指针
		 */
		const XAnsiString * getStringEx(const XAnsiString & paramSection, const XAnsiString & paramKey)
		{
			int iSectionIndex = m_Map.getIndexBykey(paramSection);
			if (!m_Map.isValidIndex(iSectionIndex)) return NULL;
			
			const TStringKeyValue & stKeyValue = m_Map.getValue(iSectionIndex);
			int iValueIndex = stKeyValue.getIndexBykey(paramKey);
			if (!stKeyValue.isValidIndex(iValueIndex)) return NULL;
			
			return &stKeyValue.getValue(iValueIndex);
		}
		//取指定的字符串
		/**
			如果没有返到，这个会返回一个空串，否则会返回字符串。
			@param [in] paramSection Section名称
			@param [in] paramKey	 Key
			@return const char * 返回结果
		 */
		const char * getString(const XAnsiString & paramSection, const XAnsiString & paramKey)
		{
			const XAnsiString * pRet = getStringEx(paramSection, paramKey);
			if (isNULL(pRet)) return "";
			else return pRet->c_str();
		}
		//取整个映射表，用于全部遍历
		const TStringSection & getMap() const
		{
			return m_Map;
		}
		//取指定Section名称的Section
		/**
			这个主要是用于优化操作,如果没有找到则会返回NULL
			@param [in] paramSectionName 指定的section名称
			@return const TStringKeyValue * 指定的键值对映射表
		 */
		const TStringKeyValue * getSection(const XAnsiString & paramSectionName) const
		{
			int iSectionIndex = m_Map.getIndexBykey(paramSectionName);
			if (!m_Map.isValidIndex(iSectionIndex)) return NULL;
			return &m_Map.getValue(iSectionIndex);
		}

	private:
		TStringSection m_Map;
	};
}
#endif
