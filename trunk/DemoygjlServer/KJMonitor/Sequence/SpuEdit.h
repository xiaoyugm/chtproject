#if !defined(AFX_SPUEDIT_H__FBDC7731_AB12_4964_A91B_1F6A51DAFA46__INCLUDED_)
#define AFX_SPUEDIT_H__FBDC7731_AB12_4964_A91B_1F6A51DAFA46__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SpuEdit.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSpuEdit dialog
#include "spu_temp.h" 
#include <afxdb.h>
#include "SpuInform.h"
#include  "Spudetailed_me.h"


class CSpuEdit : public CDialog
{
// Construction
public:
	CSpuEdit(CWnd* pParent = NULL);   // standard constructor
 

// Dialog Data
	//{{AFX_DATA(CSpuEdit)
	enum { IDD = IDD_DIALOG1 };
	CComboBox	m_com;
	CListBox	m_list;
	int model;
	BOOL	m_hangup;
	int		m_SPU_num;
	int		m_priority;
	CString	m_para2;
	CString	m_para1;
	CString	m_para3;
	CString	m_para4;
	int		m_com_num;
	int		m_step;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSpuEdit)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation

public:
   ~CSpuEdit();


    SpuInform  *spuinform1;
    Spudetailed_me  *spudetailed;
private:
	int para_num;
    spu_temp spu_temp[2001];
    int com_present;
	int c_j;
    HBRUSH  hBrush;
	HBRUSH  hBrush1;
    HBRUSH  hBrush2;
    HBRUSH  hBrush3;
    CBitmap		m_bitmapGreen;
protected:
    bool   OnJudge(int ,char ,long );
   	BOOL OnInitDialog();
	// Generated message map functions
	//{{AFX_MSG(CSpuEdit)
	afx_msg bool OnInsert();
	afx_msg void OnSelchangeList1();
	afx_msg void OnDoubleclickedInsert();
	afx_msg void OnEmpty();
	afx_msg void Onxiug();
	afx_msg void OnKillfocusEditCommand();
	afx_msg void OnDblclkList1();
	afx_msg void OnChangeEditCommand();
	afx_msg void OnCheck1();
	afx_msg void OnChangeEditPriority();
	virtual void OnOK();
	afx_msg void OnKillfocusEditPa1();
	afx_msg void OnKillfocusEditPa3();
	afx_msg void OnKillfocusEditPara4();
	afx_msg void OnKillfocusEditpara2();
	afx_msg void OnButtonHelp();
	afx_msg void OnButtonKong();
	afx_msg void OnButtonDel();
	afx_msg void OnSelchangeCombo1();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);

	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SPUEDIT_H__FBDC7731_AB12_4964_A91B_1F6A51DAFA46__INCLUDED_)
