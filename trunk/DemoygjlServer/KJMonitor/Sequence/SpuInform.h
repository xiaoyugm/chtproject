#if !defined(AFX_SPUINFORM_H__49EA2CC7_4843_4D4C_A6D6_956331773622__INCLUDED_)
#define AFX_SPUINFORM_H__49EA2CC7_4843_4D4C_A6D6_956331773622__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <afxdb.h>
// SpuInform.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// SpuInform recordset

class SpuInform : public CRecordset
{
public:
	SpuInform(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(SpuInform)

// Field/Param Data
	//{{AFX_FIELD(SpuInform, CRecordset)
	long 	m_ID;
	BOOL	m_exit_or_empty;
	BOOL	m_active_hangup;
	long	m_num_of_command;
	long    m_priority;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(SpuInform)
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

#endif // !defined(AFX_SPUINFORM_H__49EA2CC7_4843_4D4C_A6D6_956331773622__INCLUDED_)
