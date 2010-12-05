#if !defined(AFX_DLISTEXT_H__08F1FCD0_64CE_4BA9_8A38_E5B029874E8A__INCLUDED_)
#define AFX_DLISTEXT_H__08F1FCD0_64CE_4BA9_8A38_E5B029874E8A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DListEXT.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDListEXT dialog

class CDListEXT : public CDialog
{
// Construction
public:
	CDListEXT(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDListEXT)
	enum { IDD = IDD_DIA_LISTEXT };
	CButton m_cChMAX;
	CButton m_cChMIN;
	CButton m_cChMEAN;
	CButton m_cChB;
	CButton m_cChR;
	CButton m_cChAH;
	CButton m_cChAL;
	CButton m_cChSH;
	CButton m_cChSL;
	CButton m_cChBT;
	CButton m_cChRT;
	CButton m_cChAT;
	CButton m_cChFDT;
	CButton m_cChBS;
	CButton m_cChWN;
	CButton m_cChWT;
	//}}AFX_DATA
	UINT	m_ntrans;
	UINT	m_nlist;

	CString2DataType m_Str2Data;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDListEXT)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDListEXT)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLISTEXT_H__08F1FCD0_64CE_4BA9_8A38_E5B029874E8A__INCLUDED_)
