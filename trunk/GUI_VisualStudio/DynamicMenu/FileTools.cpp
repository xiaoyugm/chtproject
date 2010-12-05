#include "stdafx.h"
#include "FileTools.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CFileTools::CFileTools()
{}


CFileTools::~CFileTools()
{}


BOOL CFileTools::DoesFileExist(LPCTSTR _lpFullFileName)
{
	if(_lpFullFileName!=NULL)
	{
		HANDLE hFile;

		hFile= CreateFile(_lpFullFileName,
						  0, //GENERIC_READ,           // Open for reading
						  FILE_SHARE_READ,        // Share for reading
						  NULL,                   // No security
						  OPEN_EXISTING,          // Existing file only
						  FILE_ATTRIBUTE_NORMAL,  // Normal file
						  NULL);                  // No template file

		if (hFile != INVALID_HANDLE_VALUE)
		{
			CloseHandle(hFile);
			return TRUE;
		}
	}
	return FALSE;
}

BOOL CFileTools::GetExecutableDirectory(CString& _sDirName)
{
	BOOL bRet= FALSE;
	if(&_sDirName!=NULL)
	{
		int		iLength;
		LPSTR	lpPtr= _sDirName.GetBuffer(512);
		if(lpPtr!=NULL)
		{
			iLength= ::GetModuleFileName(NULL, lpPtr, 512);
			_sDirName.ReleaseBuffer();
			if(iLength!=0)
			{
				iLength= _sDirName.GetLength();
				iLength--;
				while(iLength >0)
				{
					if(_sDirName.GetAt(iLength) == '\\')
						break;
					else
						iLength--;
				}
				_sDirName= _sDirName.Left(iLength);
				_sDirName+= "\\";
				bRet= TRUE;
			}
		}
	}
	return bRet;
}

