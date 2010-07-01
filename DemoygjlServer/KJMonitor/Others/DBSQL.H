#if !defined(AFX_DBSQL_H__53DE4011_4048_471F_9763_2E9244E93D29__INCLUDED_)
#define AFX_DBSQL_H__53DE4011_4048_471F_9763_2E9244E93D29__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DBSQL.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDBSQL recordset

class CDBSQL : public CRecordset
{
public:
	CString m_strSQLDSN;
	void SetDSN(CString strDSN,CString strUID,CString strPWD);
	CDBSQL(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CDBSQL)

// Field/Param Data
	//{{AFX_FIELD(CDBSQL, CRecordset)
	long	m_unTrunkNumber;
	long	m_unPortSelectStatus;
	long	m_unPCPortNumber;
	long	m_unMultiPortNumber;
	long	m_unTrunkNO;
	long	m_unPortNO;
	BOOL	m_bPortStatus;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDBSQL)
	public:
	virtual CString GetDefaultConnect();    // Default connection string
	virtual CString GetDefaultSQL();    // Default SQL for Recordset
	virtual void DoFieldExchange(CFieldExchange* pFX);  // RFX support
	//}}AFX_VIRTUAL

// Implementation
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DBSQL_H__53DE4011_4048_471F_9763_2E9244E93D29__INCLUDED_)
