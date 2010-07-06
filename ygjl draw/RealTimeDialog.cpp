// RealTimeDialog.cpp : implementation file
//

#include "stdafx.h"
#include "Draw.h"
#include "RealTimeDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRealTimeDialog dialog


CRealTimeDialog::CRealTimeDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CRealTimeDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CRealTimeDialog)
	m_nXMin = 0;
	m_nXMax = 0;
	m_nYMax = 0;
	m_nYMin = 0;
	m_nPoint1 = 0;
	m_nPoint3 = 0;
	m_nPoint4 = 0;
	m_nPoint2 = 0;
	m_nTimeSpan = 60;
	//}}AFX_DATA_INIT
}


void CRealTimeDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRealTimeDialog)
	DDX_Control(pDX, IDC_BUTTON_COLOR_LINE7, m_line7);
	DDX_Control(pDX, IDC_BUTTON_COLOR_LINE5, m_line5);
	DDX_Control(pDX, IDC_BUTTON_COLOR_LINE3, m_line3);
	DDX_Control(pDX, IDC_BUTTON_COLOR_LINE1, m_line1);
	DDX_Control(pDX, IDC_BUTTON_BACKCOLOR, m_backcolor);
	DDX_Text(pDX, IDC_EDIT_X_MIN, m_nXMin);
	DDV_MinMaxUInt(pDX, m_nXMin, 0, 1000);
	DDX_Text(pDX, IDC_EDIT_X_MAX, m_nXMax);
	DDV_MinMaxUInt(pDX, m_nXMax, 0, 1000);
	DDX_Text(pDX, IDC_EDIT_Y_MAX, m_nYMax);
	DDV_MinMaxUInt(pDX, m_nYMax, 0, 1000);
	DDX_Text(pDX, IDC_EDIT_Y_MIN, m_nYMin);
	DDV_MinMaxUInt(pDX, m_nYMin, 0, 1000);
	DDX_Text(pDX, IDC_EDIT_POINT1, m_nPoint1);
	DDV_MinMaxUInt(pDX, m_nPoint1, 0, 15000);
	DDX_Text(pDX, IDC_EDIT_POINT3, m_nPoint3);
	DDV_MinMaxUInt(pDX, m_nPoint3, 0, 15000);
	DDX_Text(pDX, IDC_EDIT_POINT4, m_nPoint4);
	DDV_MinMaxUInt(pDX, m_nPoint4, 0, 15000);
	DDX_Text(pDX, IDC_EDIT_POINT2, m_nPoint2);
	DDV_MinMaxUInt(pDX, m_nPoint2, 0, 15000);
	DDX_Text(pDX, IDC_EDIT_TIMESPAN, m_nTimeSpan);
	DDV_MinMaxUInt(pDX, m_nTimeSpan, 60, 3600);
	//}}AFX_DATA_MAP
	DDX_XTColorPicker(pDX, IDC_BUTTON_BACKCOLOR, m_clrBackColor);
	DDX_XTColorPicker(pDX, IDC_BUTTON_COLOR_LINE1, m_clrLine1);
//	DDX_XTColorPicker(pDX, IDC_BUTTON_COLOR_LINE2, m_clrLine2);
	DDX_XTColorPicker(pDX, IDC_BUTTON_COLOR_LINE3, m_clrLine2);
//	DDX_XTColorPicker(pDX, IDC_BUTTON_COLOR_LINE4, m_clrLine4);
	DDX_XTColorPicker(pDX, IDC_BUTTON_COLOR_LINE5, m_clrLine3);
//	DDX_XTColorPicker(pDX, IDC_BUTTON_COLOR_LINE6, m_clrLine6);
	DDX_XTColorPicker(pDX, IDC_BUTTON_COLOR_LINE7, m_clrLine4);
//	DDX_XTColorPicker(pDX, IDC_BUTTON_COLOR_LINE8, m_clrLine8);

}


BEGIN_MESSAGE_MAP(CRealTimeDialog, CDialog)
	//{{AFX_MSG_MAP(CRealTimeDialog)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRealTimeDialog message handlers
