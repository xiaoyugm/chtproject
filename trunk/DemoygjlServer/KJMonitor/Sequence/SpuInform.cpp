// SpuInform.cpp : implementation file
//

#include "stdafx.h"
#include "..\KJMonitor.h"
#include "SpuInform.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// SpuInform

IMPLEMENT_DYNAMIC(SpuInform, CRecordset)

SpuInform::SpuInform(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(SpuInform)
	m_ID = 0;
	m_exit_or_empty = FALSE;
	m_active_hangup = FALSE;
	m_priority=0;
	m_num_of_command = 0;
	m_nFields = 5;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dynaset;
}


CString SpuInform::GetDefaultConnect()
{
	return _T("");
//	return _T("ODBC;DSN=masterdefine");
}

CString SpuInform::GetDefaultSQL()
{
	return _T("");
//	return _T("[dbo].[Spu_information]");
}

void SpuInform::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(SpuInform)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[ID]"), m_ID);
    RFX_Long(pFX, _T("[priority]"), m_priority);
	RFX_Bool(pFX, _T("[exit_or_empty]"), m_exit_or_empty);
	RFX_Bool(pFX, _T("[active_hangup]"), m_active_hangup);
	RFX_Long(pFX, _T("[num_of_command]"), m_num_of_command);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// SpuInform diagnostics

#ifdef _DEBUG
void SpuInform::AssertValid() const
{
	CRecordset::AssertValid();
}

void SpuInform::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
