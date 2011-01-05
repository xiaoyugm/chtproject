//#if !defined(AFX_SETTIMEDLG_H__F23E9803_41D7_40C1_B427_4AAA2CDD9ED2__INCLUDED_)
//#define AFX_SETTIMEDLG_H__F23E9803_41D7_40C1_B427_4AAA2CDD9ED2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AdjustDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAdjustDlg dialog

class CAdjustDlg : public CXTResizeDialog
{
// Construction
public:
	CAdjustDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CAdjustDlg)
	enum { IDD = IDD_DIA_ADJUST };
//	UINT	m_nSecond;
	CXTFlatComboBox	    m_CB_A;
	CXTFlatComboBox	    m_CB_C;
	CXTFlatComboBox	    m_CB_F;
	CXTListCtrl         m_L_A;
	CXTListCtrl         m_L_C;
	CXTListCtrl         m_L_F;
	CDateTimeCtrl       m_LTime;
	//}}AFX_DATA
	CXTHeaderCtrl       m_header;
	CTime m_startDateTime;
	int m_start,m_end;
	vector<CString> m_Records;
	vector<CString>::iterator  iter;
//	unsigned char  chcommand;
//	CString2DataType    m_Str2Data;
//	UINT	m_nchangev;

//	void ComDisMes(CString strmes);

  CAxContactCmd   m_ContactCmd;
  CAdjustdata     m_Adjustdata;
//  CAxSControl     *m_SControlNew;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAdjustDlg)
	protected:
	virtual BOOL DestroyWindow();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    virtual BOOL OnInitDialog();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAdjustDlg)
	afx_msg void OnCB_A();
	afx_msg void OnCB_C();
	afx_msg void OnCB_F();
	afx_msg void OnDtimeA(NMHDR* pNMHDR, LRESULT* pResult);
//	afx_msg void OnButSend();
//	afx_msg void OnchangeComboD();
    afx_msg void OnClose();
//	afx_msg void OnButCancel();
//	afx_msg void OnButRES();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

//#endif // !defined(AFX_SETTIMEDLG_H__F23E9803_41D7_40C1_B427_4AAA2CDD9ED2__INCLUDED_)
