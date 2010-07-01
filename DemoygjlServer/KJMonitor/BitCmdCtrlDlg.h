#if !defined(AFX_BITCMDCTRLDLG_H__D23AD9F4_79CA_4FCD_9603_AB3126D22A2F__INCLUDED_)
#define AFX_BITCMDCTRLDLG_H__D23AD9F4_79CA_4FCD_9603_AB3126D22A2F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// BitCmdCtrlDlg.h : header file
//
#include "Controls\\XPStyleButtonST.h"
#include "Controls\\ThemeHelperST.h"

#include "Controls\\EditEx.hxx"

/////////////////////////////////////////////////////////////////////////////
// CBitCmdCtrlDlg dialog

class CBitCmdCtrlDlg : public CDialog
{
// Construction
public:
	void GetBitCmdtoSend();
	CString m_strSendReceiveInfo;
	void DispSendReceiveInfo(void);
	
	void SetLcmdBitCheck(void);
	unsigned char GetLcmd();
	void SetLcmdBit(unsigned char ucBit);
	CBitCmdCtrlDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CBitCmdCtrlDlg)
	enum { IDD = IDD_DLG_BITCMDCTRL };
	CXPStyleButtonST	m_ctrlBtnData;
	CXPStyleButtonST	m_ctrlBtnClear;
	CXPStyleButtonST	m_ctrlBtnComPort;
	CEditEx	m_ctrlEditData;
	CXPStyleButtonST	m_btnOK;
	CXPStyleButtonST	m_ctrlBtnStart;
	CComboBox	m_ctrlComboTrunkNO;
	CButton	m_ctrlCheckL0;
	CButton	m_ctrlCheckL1;
	CButton	m_ctrlCheckL2;
	CButton	m_ctrlCheckL3;
	CButton	m_ctrlCheckL4;
	CButton	m_ctrlCheckL5;
	CButton	m_ctrlCheckL6;
	CButton	m_ctrlCheckL7;
	UINT	m_unEditAddrDEC;
	CString	m_strEditAddrHEX;
	CString	m_strEditData;
	CString	m_strEditLcmdHEX;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBitCmdCtrlDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CBitCmdCtrlDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnCheckL0();
	afx_msg void OnCheckL1();
	afx_msg void OnCheckL2();
	afx_msg void OnCheckL3();
	afx_msg void OnCheckL4();
	afx_msg void OnCheckL5();
	afx_msg void OnCheckL6();
	afx_msg void OnCheckL7();
	afx_msg void OnChangeEditAddrdec();
	afx_msg void OnChangeEditLcmdhex();
	afx_msg void OnButtonStart();
	afx_msg void OnButtonClear();
	afx_msg void OnButtonComport();
	afx_msg void OnBUTData();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CThemeHelperST	m_ThemeHelper;

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BITCMDCTRLDLG_H__D23AD9F4_79CA_4FCD_9603_AB3126D22A2F__INCLUDED_)
