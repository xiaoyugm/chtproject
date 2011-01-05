#if !defined(AFX_SETTIMEDLG_H__F23E9803_41D7_40C1_B427_4AAA2CDD9ED2__INCLUDED_)
#define AFX_SETTIMEDLG_H__F23E9803_41D7_40C1_B427_4AAA2CDD9ED2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SetTimeDlg.h : header file
//
//#define __STDC_WANT_SECURE_LIB__     

#include "CListCtrl_DataModel.h"
/////////////////////////////////////////////////////////////////////////////
// CSetTimeDlg dialog

class CSetTimeDlg : public CXTResizeDialog
{
// Construction
public:
	CSetTimeDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSetTimeDlg)
	enum { IDD = IDD_DIALOG_SET_TIMER };
	UINT	m_nSecond;
	CXTFlatComboBox	    m_VERIFYT;
	CXTFlatComboBox	    m_PORT;
	CXTFlatComboBox	    m_FUNCTION;
	CGridListCtrlGroups         m_listC;
	CGridListCtrlGroups         m_listC2;
	CXTHeaderCtrl       m_header;
	//}}AFX_DATA
	unsigned char  chcommand;
	CListCtrl_DataModel m_DataModel;
	CString2DataType    m_Str2Data;
	UINT	m_nchangev;
    unsigned char *m_ndkSend;
	UINT	m_nchange;

	void ComDisMes(CString strmes);
	void OnButRESre();
	void InitWGas(int gasfds);
	void Init5A();
	void Save46();

  CAxSControl     m_SControl;
  CAxSControl     *m_SControlNew;
  CAxFans         m_Fans;
    CAxCommonSet        m_CommonSet;


	vector<CString> m_Records1;
	vector<CString> m_Records2;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSetTimeDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    virtual BOOL OnInitDialog();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSetTimeDlg)
	afx_msg void OnChCBF();
	afx_msg void OnChCBP();
	afx_msg void OnChCBV();
	afx_msg void OnButSend();
	afx_msg void OnchangeComboD();
    afx_msg void OnClose();
	afx_msg void OnButCancel();
	afx_msg void OnButRES();
    afx_msg void OnItemChangedList(NMHDR *pNMHDR, LRESULT *pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SETTIMEDLG_H__F23E9803_41D7_40C1_B427_4AAA2CDD9ED2__INCLUDED_)
