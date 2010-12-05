#pragma once

class CFileTools
{
private:
	CFileTools();
public:
	virtual ~CFileTools();

	static BOOL DoesFileExist(LPCTSTR _lpFullFileName);
	static BOOL GetExecutableDirectory(CString &_sDirName);
};