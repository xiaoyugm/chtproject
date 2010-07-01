// Spudetailed_me.cpp : implementation file
//cedit

#include "stdafx.h"
#include "..\KJMonitor.h"
#include "Spudetailed_me.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Spudetailed_me

IMPLEMENT_DYNAMIC(Spudetailed_me, CRecordset)

Spudetailed_me::Spudetailed_me(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(Spudetailed_me)
	m_spu_num = 0;
	m_step_num = 0;
	m_command_index = 0;
	m_para1 = _T("");
	m_para2 = _T("");
	m_para3 = _T("");
	m_para4 = _T("");
	m_nFields = 7;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dynaset;
}


CString Spudetailed_me::GetDefaultConnect()
{
	return _T("");
//	return _T("ODBC;DSN=masterdefine");
}

CString Spudetailed_me::GetDefaultSQL()
{
	return _T("");
//	return _T("[dbo].[spu_detailed]");
}

void Spudetailed_me::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(Spudetailed_me)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[spu_num]"), m_spu_num);
	RFX_Long(pFX, _T("[step_num]"), m_step_num);
	RFX_Long(pFX, _T("[command_index]"), m_command_index);
	RFX_Text(pFX, _T("[para1]"), m_para1);
	RFX_Text(pFX, _T("[para2]"), m_para2);
	RFX_Text(pFX, _T("[para3]"), m_para3);
	RFX_Text(pFX, _T("[para4]"), m_para4);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// Spudetailed_me diagnostics

#ifdef _DEBUG
void Spudetailed_me::AssertValid() const
{
	CRecordset::AssertValid();
}

void Spudetailed_me::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
