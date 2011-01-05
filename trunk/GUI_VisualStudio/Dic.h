// Dic.h: Schnittstelle für die Klasse CDic.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DIC_H__F0AFADE8_5DC7_4F52_89CA_BD37152F743C__INCLUDED_)
#define AFX_DIC_H__F0AFADE8_5DC7_4F52_89CA_BD37152F743C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CDic  
{
public:
	static bool LoadLanguage(LPCTSTR strFilepath);
	static CString GetText(LPCTSTR strSection, LPCTSTR strID, LPCTSTR strDefaultText, bool bTransform = false);
	CDic();
	virtual ~CDic();

private:
	static void TransformSpecChars(CString &strTransform);
	static bool m_bLoaded;
protected:
	static CMapStringToString m_Map;
};

#endif // !defined(AFX_DIC_H__F0AFADE8_5DC7_4F52_89CA_BD37152F743C__INCLUDED_)
