#if !defined(AFX_DCH5M_H__B25F58DB_0D54_4DFF_B9BA_C52728FB43C1__INCLUDED_)
#define AFX_DCH5M_H__B25F58DB_0D54_4DFF_B9BA_C52728FB43C1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DCH5m.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDCH5m dialog

class CDCH5m : public CDialog
{
// Construction
public:
	CDCH5m(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDCH5m)
	enum { IDD = IDD_DIA_DCH };
	CXTFlatComboBox	    m_DCHfds;
	CXTFlatComboBox	    m_DCHp;
	CXTListCtrl         m_LDCH;
	CXTHeaderCtrl   m_header;
	CDateTimeCtrl	m_ctrlStartTime;
	CDateTimeCtrl	m_ctrlEndTime;
	//}}AFX_DATA

	CTime m_endDateTime;
	CTime m_startDateTime;
	int n_select;
	int m_success;
	CString strPOINT;
	CSearchDir m_sdir;
	CommonTools C_Ts;

	void DCH5mInitList();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDCH5m)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    virtual BOOL OnInitDialog();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDCH5m)
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnSelchangeDchcbFds();
	afx_msg void OnSelchangeDchcbPoint();
	afx_msg void OnDatetimestart(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDatetimeend(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DCH5M_H__B25F58DB_0D54_4DFF_B9BA_C52728FB43C1__INCLUDED_)
