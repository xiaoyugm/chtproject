// Dic.cpp: Implementierung der Klasse CDic.
//
//////////////////////////////////////////////////////////////////////

//#include "stdafx.h"
//#include "Dic.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

bool CDic::m_bLoaded = false;
CMapStringToString CDic::m_Map(20); // Increment by 20 elements

CDic::CDic()
{

}

CDic::~CDic()
{
	m_Map.RemoveAll();
}

CString CDic::GetText(LPCTSTR strSection, LPCTSTR strID, LPCTSTR strDefaultText, bool bTransform)
{
	// strSection: section of the text file. sections are enclosed by []
	// strID     : identifier to access the desired entry
	//             entry is left side of '=', text is right side
	// bTransform: if you'd like to transform string "\t" to a single character '\t'
	//             works with '\t', '\n', '\r'

	// example
	// 
	// [Preview]
	// PRINT = &Drucken...
	// NEXT = &Nächste
	// PREV = &Vorherige
	// 
	// CString strRet = CDic::GetText(_T("Preview"), _T("NEXT"), _T("&Next page"));

	if (m_bLoaded==false) // wasn't loaded, return default text
		return strDefaultText;

	CString strLookup, strRet;
	CString strPartSection(strSection);
	CString strPartID(strID);
	strPartSection.MakeUpper();
	strPartID.MakeUpper();

	// Inserting a "_" to get a difference between "Settings"+"11" and "Settings1"+"1"
	strLookup.Format(_T("%s_%s"), strPartSection, strPartID);

	if (m_Map.Lookup(strLookup, strRet)) {
		if (bTransform)
			TransformSpecChars(strRet);
		return strRet;
	}

	return strDefaultText;
}

bool CDic::LoadLanguage(LPCTSTR strFilepath)
{
	m_Map.RemoveAll();

	int iPos;
	CString strLine, strSection, strLookup, strLeft, strRight;
	CStdioFile file;
	if (file.Open(strFilepath, CFile::modeRead)) {
		while (file.ReadString(strLine)) {
			strLine.TrimLeft();
			strLine.TrimRight();
			// remove comment
			if (strLine.Left(2)==_T("//")) {
				strLine.Empty(); // entire row is a comment, ATTENTION with URLs !!
			} else if ((iPos = strLine.Find(TCHAR(';'))) >= 0) {
				strLine = strLine.Mid(iPos+1); // comment
			} 

			if (strLine.IsEmpty()==FALSE) {
				// new section?
				if (strLine.GetAt(0) == '[') {
					strLine = strLine.Mid(1);
					iPos = strLine.Find(TCHAR(']'));
					if (iPos>=0) {
						strLine = strLine.Left(iPos);
					}
					strSection = strLine;
					strSection.MakeUpper();
				} else {
					// create an entry
					iPos = strLine.Find(TCHAR('='));
					if (iPos > 0) {
						strLeft  = strLine.Left(iPos);
						strRight = strLine.Mid(iPos+1);
						strLeft.TrimRight();
						strRight.TrimLeft();
						strLeft.MakeUpper();

						strLookup.Format(_T("%s_%s"), strSection, strLeft);
						m_Map.SetAt(strLookup, strRight);
					}
				}
			}
		}

		file.Close();
		m_bLoaded = true;
		return true;
	}

	m_bLoaded = false;
	return false;
}

void CDic::TransformSpecChars(CString &strTransform)
{
	strTransform.Replace(_T("\\r"), _T("\r")); // old, new
	strTransform.Replace(_T("\\n"), _T("\n")); // old, new
	strTransform.Replace(_T("\\t"), _T("\t")); // old, new
}
