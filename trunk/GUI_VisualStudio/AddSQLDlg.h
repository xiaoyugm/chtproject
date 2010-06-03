#pragma once


//Derived AxLib classes
#include "dbAx\AxAccountSet.hpp"
#include "dbAx\AxContactCmd.hpp"
#include "dbAx\AxContactSet.hpp"
#include "dbAx\CardFileEvents.hpp"
#include "dbAx\AccountSetEvents.hpp"
// CAccountDlg dialog

class CAccountDlg : public CDialog
{
	DECLARE_DYNAMIC(CAccountDlg)

public:
	CAccountDlg(CWnd* pParent = NULL);   // standard constructor
    CAccountDlg(BOOL bEditMode, CWnd* pParent = NULL);
	virtual ~CAccountDlg();

    CString strtable,str1,str2,str3,str4,str5,str6,str7,str8,str9;
    int    acdid;
	CString2DataType m_Str2Data;
// Dialog Data
	enum { IDD = IDD_DIALOG_ADDSQL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

  CWnd           *m_pParent;
  BOOL            m_bEditMode;

  //AxLib class pointers
  CAxAccountSet   *m_pAccountSet;
  CAxContactSet   *m_pContactSet;

	DECLARE_MESSAGE_MAP()
public:
  virtual BOOL OnInitDialog();
  afx_msg void OnBnClickedOk();
  afx_msg void OnBnClickedCancel();

public:
  afx_msg void OnKillFocusAccntId();
};
