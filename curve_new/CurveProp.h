#if !defined(AFX_CURVEPROP_H__3EC1607C_54FD_4C9C_ABA0_13AB21D230AB__INCLUDED_)
#define AFX_CURVEPROP_H__3EC1607C_54FD_4C9C_ABA0_13AB21D230AB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CurveProp.h : header file
//

//#include "dbAx\AxSControl.hpp"
//#include "dbAx\AxContactCmd.hpp"
//#include "dbAx\CardFileEvents.hpp"
//#include "dbAx\AccountSetEvents.hpp"
/////////////////////////////////////////////////////////////////////////////
// CCurveProp dialog
#include "RtCurve.h"

class CCurveProp : public CDialog
{
	// Construction
public:
	CCurveProp(CWnd* pParent = NULL);   // standard constructor
	CRtCurve *m_pRtCurve;
	BOOL	m_sCheckGrid;
	
	// Dialog Data
	//{{AFX_DATA(CCurveProp)
	enum { IDD = IDD_DLG_RTCURVE };
	CButton	m_ctrlCheckGrid;
	CButton	m_BCheckMax;
	CButton	m_BCheckMean;
	CButton	m_BCheckMin;
	CDateTimeCtrl	m_startDateCtrl;
	CDateTimeCtrl	m_endDateCtrl;
	CComboBox	m_comboNo;
//	CXTButton	m_btnCurveColor;
//	CXTButton	m_btnBgColor;
	CXTColorPicker	m_ctlBgColor;
	CXTColorPicker	m_ctlCColor;
	CXTColorPicker	m_MaxColor;
	CXTColorPicker	m_MeanColor;
	CXTColorPicker	m_MinColor;
	COLORREF			m_Bgcolor;
	COLORREF			m_Ccolor;
	COLORREF			m_Maxc;
	COLORREF			m_Meanc;
	COLORREF			m_Minc;
	short	m_sPoint;
	short	m_sEndHour;
	short	m_sStartHour;
	CTime	m_endDate;
	CTime	m_startDate;
	short	m_endMin;
	short	m_startMin;
	//}}AFX_DATA
//	COLORREF	m_colorCurve;
//	COLORREF	m_colorBg;
	PCURVEPROP	m_pCurveProp;
	//	CString		m_strStartDate;
	//	CString		m_strEndDate;
	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCurveProp)
public:
	virtual BOOL DestroyWindow();
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
	
	// Implementation
protected:
	
	// Generated message map functions
	//{{AFX_MSG(CCurveProp)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeCurveCombo();
	afx_msg void OnCurveSave();
	afx_msg void OnCurveBgcolor();
	afx_msg void OnCurveColor();
	afx_msg void OnDeltaposCurveSpinstart(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDeltaposCurveSpinend(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnCloseupCurveEnddatepicker(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnCloseupCurveStartdatepicker(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnChangeCurveStartmin();
	afx_msg void OnCheckGrid();
	afx_msg void OnDatetimechangeCurveStartdatepicker(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CURVEPROP_H__1B41837A_6BD5_476E_BD8F_C002D80BCF5F__INCLUDED_)
