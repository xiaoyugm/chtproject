#if !defined(AFX_COMMPARADLG_H__45303A17_61E9_4043_A038_4FDDDDDA6245__INCLUDED_)
#define AFX_COMMPARADLG_H__45303A17_61E9_4043_A038_4FDDDDDA6245__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CommParaDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCommParaDlg dialog
#include "Controls\\XPStyleButtonST.h"
#include "Controls\\ThemeHelperST.h"

#include "SQL\\sqldirect.h"
#include "SQL\\String2DataType.h"



class CCommParaDlg : public CDialog
{
// Construction
public:
	void GetDatafromDB(void);
	void ConnectDB(void);

	CSQLDirect m_SQLDirect;
	CString2DataType m_String2DataType;

	
	CCommParaDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CCommParaDlg)
	enum { IDD = IDD_DLG_COMMPARA };
	CXPStyleButtonST m_btnOK;
	CXPStyleButtonST m_btnCANCEL;
	UINT	m_unEditRepeattimes;
	UINT	m_unEditScanDelayTime;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCommParaDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CCommParaDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	CThemeHelperST	m_ThemeHelper;


};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COMMPARADLG_H__45303A17_61E9_4043_A038_4FDDDDDA6245__INCLUDED_)
