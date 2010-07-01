// shixuDlg.h : header file
//

#if !defined(AFX_SHIXUDLG_H__124E3AE0_1FC0_49DC_AFBB_E46C832DA17B__INCLUDED_)
#define AFX_SHIXUDLG_H__124E3AE0_1FC0_49DC_AFBB_E46C832DA17B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <afxdb.h>
#include "SpuInform.h"
#include  "Spudetailed_me.h"

/////////////////////////////////////////////////////////////////////////////
// CShixuDlg dialog
//#define  unTimerId    1             //  7.6
//#define  unTimerIdxu  2           //  7.6

class CShixuDlg : public CDialog
{
// Construction
public:
	CShixuDlg(CWnd* pParent = NULL);	// standard constructor
    ~CShixuDlg();
// Dialog Data
	//{{AFX_DATA(CShixuDlg)
	enum { IDD = IDD_SHIXU_DIALOG };
	CComboBox	m_list;
    long	m_new_spu;
	int		m_new_spu2;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CShixuDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

	private:    // 
		SpuInform  *spuinform;
        SpuInform  *spuinform_copy;
        Spudetailed_me *spudetailed;
        Spudetailed_me *spudetailed_copy;
        int copy_index; 


// Implementation
protected:
//	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CShixuDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
//	afx_msg void OnPaint();
//	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void Onaddnew();
	afx_msg void OnModify();
	afx_msg void Onzidong();
	afx_msg void OnSelchangeCombol();
	afx_msg void Ondelete();
	virtual void OnOK();
//	afx_msg void OnButton5();
//	afx_msg void OnButton6();
//	afx_msg void OnButton7();
//	afx_msg void OnButton4();
//	afx_msg void OnButton3();
//	afx_msg void OnTimer(UINT nIDEvent);
//	afx_msg void OnButton8();
//	afx_msg void OnDropdownCombo1();
	afx_msg void OnButtonCopy();
	afx_msg void OnButtonPaste();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SHIXUDLG_H__124E3AE0_1FC0_49DC_AFBB_E46C832DA17B__INCLUDED_)
