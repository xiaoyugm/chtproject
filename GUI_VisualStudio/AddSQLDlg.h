#pragma once


//Derived AxLib classes
// CAccountDlg dialog

class CAccountDlg : public CDialog
{
	DECLARE_DYNAMIC(CAccountDlg)

public:
	CAccountDlg(CWnd* pParent = NULL);   // standard constructor
    CAccountDlg(BOOL bEditMode, CWnd* pParent = NULL);
	virtual ~CAccountDlg();

	CButton	            m_ISAlm;
	CButton	            m_DAlm;
	CButton	            m_ctlMusic;
	CXTFlatComboBox     m_ComBoxD;
	CXTFlatComboBox     m_ComBoxD9;
	CXTFlatComboBox     m_ComBoxD5;
	CXTFlatComboBox     m_ComBoxD6;

    float   fstr2,fstr3,fstr4,fstr5,fstr6,fstr9;
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
  CAxMAlocationSet   *m_pMAlocation;

	DECLARE_MESSAGE_MAP()
public:
  virtual BOOL OnInitDialog();
  afx_msg void OnBnClickedOk();
  afx_msg void OnBnClickedCancel();

	afx_msg void OnMusicPath();
	afx_msg void OnchangeComboD();
	afx_msg void OnchangeComboD5();
	afx_msg void OnchangeComboD6();
  afx_msg void OnKillFocusAccntId();
	afx_msg void OnChE();
};
