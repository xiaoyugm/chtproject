#if !defined(AFX_SETTINGHOSTDLG_H__92D4ACA8_B152_425C_BBA4_A10384483A86__INCLUDED_)
#define AFX_SETTINGHOSTDLG_H__92D4ACA8_B152_425C_BBA4_A10384483A86__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SettingHostDlg.h : header file
//

//#include "CListCtrl_DataModel.h"
//Derived AxLib classes
#include "dbAx\AxPointDescription.hpp"
#include "dbAx\AxMAlocationSet.hpp"
#include "dbAx\AxAccountSet.hpp"
#include "dbAx\AxContactCmd.hpp"
#include "dbAx\AxContactSet.hpp"
#include "dbAx\CardFileEvents.hpp"
#include "dbAx\AccountSetEvents.hpp"


/////////////////////////////////////////////////////////////////////////////
// CSettingHostDlg dialog

class CSettingHostDlg : public CXTResizeDialog
{
// Construction
public:
	CSettingHostDlg(CWnd* pParent = NULL);   // standard constructor

    CCardFileEvents *pCnEvents;
// Dialog Data
	//{{AFX_DATA(CSettingHostDlg)
	enum { IDD = IDD_DIALOG_HOST_SETTING };
//	CString	m_strHostIP;
//	CString	m_strPort;
//	CString	m_strTimeOut;
	CGridListCtrlGroups         m_listCtrl;
	BOOL                m_bSortColor;
	BOOL    m_bListColor;
	BOOL    m_bRowColor;
	//}}AFX_DATA
//	COLORREF            m_crSortText;
//	COLORREF            m_crSortBack;
//	COLORREF            m_crListText;
//	COLORREF            m_crListBack;
//	COLORREF            m_crRowText;
//	COLORREF            m_crRowBack;
//	CXTColorPicker      m_cpSortText;
	CXTColorPicker      m_cpSortBack;
//	CXTColorPicker      m_cpListText;
//	CXTColorPicker      m_cpListBack;
//	CXTColorPicker      m_cpRowText;
//	CXTColorPicker      m_cpRowBack;

	HICON           m_hIcon;
	int             m_nSortedCol;
	bool            m_bAscending;
	CXTHeaderCtrl   m_header;
//	CListCtrl_DataModel m_DataModel;
	CString2DataType m_Str2Data;
	int  sqlid;
	CString     m_strtable;

  //AxLib objects
  CAxConnection   m_Cn;
  CAxAccountSet   m_AccountSet;
  CAxContactCmd   m_ContactCmd;
  CAxContactSet   m_ContactSet;
  CAxMAlocationSet   m_MAlocation;
  CAxPointDescription  m_PointDes;

  //Connect to the data provider via dbAx
  BOOL         ConnectToProvider();
  void         BuildAccountList();

  void   HideControls();
  void   HideAMD();

	void SortColumn(int iCol, bool bAsc);
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSettingHostDlg)
	protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSettingHostDlg)
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBtnADD();
	afx_msg void OnBtnDEL();
	afx_msg void OnBtnMOD();
    afx_msg void OnClose();
    afx_msg void OnItemChangedList(NMHDR *pNMHDR, LRESULT *pResult);
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SETTINGHOSTDLG_H__92D4ACA8_B152_425C_BBA4_A10384483A86__INCLUDED_)













