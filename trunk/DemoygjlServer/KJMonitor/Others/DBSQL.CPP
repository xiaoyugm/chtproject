// DBSQL.cpp : implementation file
//

#include "stdafx.h"
#include "kjmonitor.h"
#include "DBSQL.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDBSQL

IMPLEMENT_DYNAMIC(CDBSQL, CRecordset)

CDBSQL::CDBSQL(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CDBSQL)
	m_unTrunkNumber = 0;
	m_unPortSelectStatus = 0;
	m_unPCPortNumber = 0;
	m_unMultiPortNumber = 0;
	m_unTrunkNO = 0;
	m_unPortNO = 0;
	m_bPortStatus = FALSE;
	m_nFields = 7;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dynaset;
}


CString CDBSQL::GetDefaultConnect()
{
	CString strSQL;
	strSQL=m_strSQLDSN;
	return strSQL;
}

CString CDBSQL::GetDefaultSQL()
{
	return _T("[dbo].[trunkandportnumber],[dbo].[trunkvsport]");
}

void CDBSQL::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CDBSQL)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[unTrunkNumber]"), m_unTrunkNumber);
	RFX_Long(pFX, _T("[unPortSelectStatus]"), m_unPortSelectStatus);
	RFX_Long(pFX, _T("[unPCPortNumber]"), m_unPCPortNumber);
	RFX_Long(pFX, _T("[unMultiPortNumber]"), m_unMultiPortNumber);
	RFX_Long(pFX, _T("[unTrunkNO]"), m_unTrunkNO);
	RFX_Long(pFX, _T("[unPortNO]"), m_unPortNO);
	RFX_Bool(pFX, _T("[bPortStatus]"), m_bPortStatus);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CDBSQL diagnostics

#ifdef _DEBUG
void CDBSQL::AssertValid() const
{
	CRecordset::AssertValid();
}

void CDBSQL::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG

void CDBSQL::SetDSN(CString strDSN,CString strUID,CString strPWD)
{
//	"ODBC;DSN=user");
	m_strSQLDSN=_T("ODBC;DSN=")+strDSN+_T(";UID=")+strUID+_T(";PWD=")+strPWD;
}
