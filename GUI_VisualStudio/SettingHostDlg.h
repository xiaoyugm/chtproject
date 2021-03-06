#if !defined(AFX_SETTINGHOSTDLG_H__92D4ACA8_B152_425C_BBA4_A10384483A86__INCLUDED_)
#define AFX_SETTINGHOSTDLG_H__92D4ACA8_B152_425C_BBA4_A10384483A86__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SettingHostDlg.h : header file
//

//#include "CListCtrl_DataModel.h"
//Derived AxLib classes

/////////////////////////////////////////////////////////////////////////////
// CSettingHostDlg dialog

class CSettingHostDlg : public CXTResizeDialog
{
// Construction
public:
	CSettingHostDlg(CWnd* pParent = NULL);   // standard constructor

//    CCardFileEvents *pCnEvents;
// Dialog Data
	//{{AFX_DATA(CSettingHostDlg)
	enum { IDD = IDD_DIALOG_HOST_SETTING };
//	CString	m_strHostIP;
//	CString	m_strPort;
//	CString	m_strTimeOut;
	CXTListCtrl         m_listCtrl;
	CXTListCtrl         m_listDis;
	BOOL                m_bSortColor;
	BOOL    m_bListColor;
	BOOL    m_bRowColor;
	CXTFlatComboBox	m_wndComboSize1;
	CXTFlatComboBox	m_wndComboSize2;
	CXTFlatComboBox	m_wndComboSize3;
	CXTFlatComboBox	m_wndComboSize4;
	CButton	m_ctrlCheckAlm;
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
	int  sqlid,PointDesid,nlist;
	CString     m_strtable;
	vector<CString> m_Records;
	bool            m_bADD,m_bSwitch;    //增加 开关量

	ListV m_strl[100];

  //AxLib objects
  CAxAccountSet   m_AccountSet;
  CAxContactSet   m_ContactSet;
  CAxMAlocationSet   m_MAlocation;
  CAxPointDescription  m_PointDes;
  CAxPointDescription  *m_PointDesNew;
  CAxDisPoint      *m_DisPointNew;
//  CAxContactCmd   m_ContactCmd;
  CAxControl      m_Control;
  CAxControl      *m_ControlNew;
  CAxSControl     m_SControl;
  CAxSControl     *m_SControlNew;
  CAxFeedE     m_AxFeedE;
  CAxFeedE     *m_AxFeedENew;
  CAxFans         m_Fans;

  //Connect to the data provider via dbAx
  BOOL         ConnectToProvider();
  void         BuildAccountList();

  void   HideDISPLAY();
  void   ShowDISPLAY();
  void   HideControls();
  void   ShowControls();
  void   ShowAMD();
  void   HideAMD();
  void   FalseFC();
  void   TrueFC();
  void   InsA();
  void   InsD();
  void   InsP();
  void   InsC();
  void   InsAddC();
  void   Insfeed();
  void   InsAddfeed();
  void   InsDIS();
  void   DelConFeedFan(CString strdel);

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
	afx_msg void OnChCB04();
	afx_msg void OnChCB03();
	afx_msg void OnchangeCombo1();
	afx_msg void OnchangeCombo2();
	afx_msg void OnchangeComboF();
	afx_msg void OnButtonSelect();
	afx_msg void OnButtonDeselect();
	afx_msg void OnButtonSelectall();
	afx_msg void OnButtonDeselectall();
	afx_msg void OnButtonSave();
//	afx_msg void OnButtonCANCEL();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBtnADD2();
	afx_msg void OnBtnADD();
	afx_msg void OnBtnDEL();
	afx_msg void OnBtnMOD();
	afx_msg void OnBtnOK();
	afx_msg void OnBtnCANCEL();
    afx_msg void OnClose();
    afx_msg void OnItemChangedList(NMHDR *pNMHDR, LRESULT *pResult);
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SETTINGHOSTDLG_H__92D4ACA8_B152_425C_BBA4_A10384483A86__INCLUDED_)













