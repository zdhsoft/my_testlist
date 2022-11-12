//�ַ�����Դ������
/**
	������ṩ��һ������ini�ļ�ֵ���ַ�����ȡ�࣬�������ڶ��������á�֧��UTF-8��ʽ���ı���ȡ
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
		typedef XMap<XAnsiString, XAnsiString>     TStringKeyValue;		//���������õ���KeyValue ��ap
		typedef XMap<XAnsiString, TStringKeyValue> TStringSection;      //����Key Section Map
	public:
		XStringMgr()
		{}
		~XStringMgr()
		{
			m_Map.Clear();
		}
		//����ָ����Ini
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
		//ȡָ���ַ�������
		/**
			���û���ҵ���᷵��NULL
			@param [in] paramSection Section����
			@param [in] paramKey	 Key
			@return const XAnsiString * ���ؽ��
				- NULL δ�ҵ����򷵻�NULL
				- NOT NULL �ҵ��ˣ�������XAnsiString��ָ��
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
		//ȡָ�����ַ���
		/**
			���û�з���������᷵��һ���մ�������᷵���ַ�����
			@param [in] paramSection Section����
			@param [in] paramKey	 Key
			@return const char * ���ؽ��
		 */
		const char * getString(const XAnsiString & paramSection, const XAnsiString & paramKey)
		{
			const XAnsiString * pRet = getStringEx(paramSection, paramKey);
			if (isNULL(pRet)) return "";
			else return pRet->c_str();
		}
		//ȡ����ӳ�������ȫ������
		const TStringSection & getMap() const
		{
			return m_Map;
		}
		//ȡָ��Section���Ƶ�Section
		/**
			�����Ҫ�������Ż�����,���û���ҵ���᷵��NULL
			@param [in] paramSectionName ָ����section����
			@return const TStringKeyValue * ָ���ļ�ֵ��ӳ���
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
