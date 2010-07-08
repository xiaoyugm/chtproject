// String2DataType.h: interface for the CString2DataType class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_STRING2DATATYPE_H__8BC63FA1_F2F2_446F_BA98_1F311D1722C2__INCLUDED_)
#define AFX_STRING2DATATYPE_H__8BC63FA1_F2F2_446F_BA98_1F311D1722C2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CString2DataType  
{
public:
	unsigned char Str2HEX(CString strData);
	unsigned char GetBitValue(unsigned char ucCh,unsigned char ucBitNo);
	CString Char2Binary(unsigned char ucCh);
	BOOL Str2Bool(CString str);
	CString Int2CString(int nInt);
	int String2Int(CString str);
	double String2Double(CString str);
	CString2DataType();
	virtual ~CString2DataType();

private:
	char HexChar(char c);

};

#endif // !defined(AFX_STRING2DATATYPE_H__8BC63FA1_F2F2_446F_BA98_1F311D1722C2__INCLUDED_)
