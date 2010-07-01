// String2DataType.cpp: implementation of the CString2DataType class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "..\kjmonitor.h"
#include "String2DataType.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CString2DataType::CString2DataType()
{

}

CString2DataType::~CString2DataType()
{

}



int CString2DataType::String2Int(CString str)
{
	char *temp=(char*)((LPCTSTR)str);
	return(atoi(temp));
}

double CString2DataType::String2Double(CString str)
{
	char *temp=(char*)((LPCTSTR)str);
	return (atof(temp));
}

CString CString2DataType::Int2CString(int nInt)
{
	CString strtemp;
	strtemp.Format("%d",nInt);
	return(strtemp);
}

BOOL CString2DataType::Str2Bool(CString str)
{
	char *temp=(char*)((LPCTSTR)str);
	if(atoi(temp))
		return TRUE;
	else
		return FALSE;
}

CString CString2DataType::Char2Binary(unsigned char ucCh)
{
	CString str=_T("");
	unsigned char ucnn=0x80;
	for(int i=0;i<8;i++)    //8
	{
		if(ucCh & ucnn)
			str+="1";
		else
			str+="0";
		ucnn>>=1;
	}
	return str;

}


//得到一个无符号字符位的值,0=<ucBitNo<=7
unsigned char CString2DataType::GetBitValue(unsigned char ucCh,unsigned char ucBitNo)
{
	unsigned char ucnn=0x01;
	ucnn<<=ucBitNo;
	if(ucnn&ucCh)
		return 1;
	else
		return 0;
}


//限制在0…256，strData最多为2个字符
unsigned char CString2DataType::Str2HEX(CString strData)
{
	int t,t1;
	strData.Replace(" ",""); //不能含空格
	int rlen=0,len=strData.GetLength();
	if(len>2)
		strData=strData.Left(2);
	if(len==1)
		strData="0"+strData;
	char h=strData[0];
	char l=strData[1];
	t=HexChar(h);
	t1=HexChar(l);
	if((t==16)||(t1==16))
		return 0;
	t=t*16+t1;
	return t;
}


char CString2DataType::HexChar(char c)
{
	if((c>='0')&&(c<='9'))
		return c-0x30;
	else if((c>='A')&&(c<='F'))
		return c-'A'+10;
	else if((c>='a')&&(c<='f'))
		return c-'a'+10;
	else 
		return 0x10;

}

CString CString2DataType::Short2Binary(unsigned short ucCh)
{
	CString str1=_T("");
	unsigned short ucnn1=0x8000;
	for(int i=0;i<16;i++)    //8
	{
		if(ucCh & ucnn1)
			str1+="1";
		else
			str1+="0";
		ucnn1>>=1;
	}
	return str1;
}
//16位