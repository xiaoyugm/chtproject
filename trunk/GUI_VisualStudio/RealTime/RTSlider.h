#if !defined(AFX_RTSLIDER_H__3629C3E5_F472_11D3_85D1_0008C777FFEE__INCLUDED_)
#define AFX_RTSLIDER_H__3629C3E5_F472_11D3_85D1_0008C777FFEE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RTSlider.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRTSlider window

class CRTSlider : public CSliderCtrl
{
// Construction
public:
	CRTSlider();

// Attributes
public:
	enum sType{TICK = 0, PAGE};
	int  m_sType;
	int  m_nCurPos;

// Operations
public:
	void SetType(int type) {m_sType = type;};

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRTSlider)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CRTSlider();

	// Generated message map functions
protected:
	//{{AFX_MSG(CRTSlider)
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RTSLIDER_H__3629C3E5_F472_11D3_85D1_0008C777FFEE__INCLUDED_)
