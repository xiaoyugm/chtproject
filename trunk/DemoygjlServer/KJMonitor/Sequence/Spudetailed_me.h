#if !defined(AFX_SPUDETAILED_ME_H__C583C9A4_06A5_4018_BCDD_9A2FC74E98BD__INCLUDED_)
#define AFX_SPUDETAILED_ME_H__C583C9A4_06A5_4018_BCDD_9A2FC74E98BD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Spudetailed_me.h : header file
//
#include <afxdb.h>
/////////////////////////////////////////////////////////////////////////////
// Spudetailed_me recordset

class Spudetailed_me : public CRecordset
{
public:
	Spudetailed_me(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(Spudetailed_me)

// Field/Param Data
	//{{AFX_FIELD(Spudetailed_me, CRecordset)
	long	m_spu_num;
	long	m_step_num;
	long	m_command_index;
	CString	m_para1;
	CString	m_para2;
	CString	m_para3;
	CString	m_para4;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Spudetailed_me)
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

#endif // !defined(AFX_SPUDETAILED_ME_H__C583C9A4_06A5_4018_BCDD_9A2FC74E98BD__INCLUDED_)
