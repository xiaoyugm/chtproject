// CurveProp.cpp : implementation file
//

#include "stdafx.h"
#include "Curve.h"
#include "CurveProp.h"
#include "datetime.h"
#include "MainFrm.h"
//#include "SystemData.h"
//Support for AxLib library
//#include "dbAx\AxLib.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCurveProp dialog


CCurveProp::CCurveProp(CWnd* pParent /*=NULL*/)
	: CDialog(CCurveProp::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCurveProp)
	m_sPoint = 0;
	m_sEndHour = 0;
	m_sStartHour = 0;
	m_endDate = 0;
	m_startDate = 0;
	m_endMin = 59;
	m_startMin = 0;
//	m_colorBg = RGB(0,0,0);
//	m_colorCurve = RGB(0,255,0);
	         	m_Bgcolor=RGB(  0,   0,   0);
				m_Ccolor =RGB(  0, 255,   0);
		    	m_Maxc =RGB(255,   0, 255);
				m_Meanc=RGB(  0, 255, 255);
				m_Minc =RGB(128, 128, 0);
	//}}AFX_DATA_INIT
	m_pCurveProp = NULL;
    m_sCheckGrid = TRUE;
}


void CCurveProp::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCurveProp)
	DDX_Control(pDX, IDC_CURVE_BGCOLOR, m_ctlBgColor);
	DDX_XTColorPicker(pDX, IDC_CURVE_BGCOLOR, m_Bgcolor);
	DDX_Control(pDX, IDC_CURVE_COLOR, m_ctlCColor);
	DDX_XTColorPicker(pDX, IDC_CURVE_COLOR, m_Ccolor);
	DDX_Control(pDX, IDC_CURVE_MAX, m_MaxColor);
	DDX_XTColorPicker(pDX, IDC_CURVE_MAX, m_Maxc);
	DDX_Control(pDX, IDC_CURVE_MEAN, m_MeanColor);
	DDX_XTColorPicker(pDX, IDC_CURVE_MEAN, m_Meanc);
	DDX_Control(pDX, IDC_CURVE_MIN, m_MinColor);
	DDX_XTColorPicker(pDX, IDC_CURVE_MIN, m_Minc);
	DDX_Control(pDX, IDC_CHECK_GRID, m_ctrlCheckGrid);
	DDX_Control(pDX, IDC_CHECK_MAX, m_BCheckMax);
	DDX_Control(pDX, IDC_CHECK_MEAN, m_BCheckMean);
	DDX_Control(pDX, IDC_CHECK_MIN, m_BCheckMin);
	DDX_Control(pDX, IDC_CURVE_STARTDATEPICKER, m_startDateCtrl);
	DDX_Control(pDX, IDC_CURVE_ENDDATEPICKER, m_endDateCtrl);
	DDX_Control(pDX, IDC_CURVE_COMBO, m_comboNo);
//	DDX_Control(pDX, IDC_CURVE_COLOR, m_btnCurveColor);
//	DDX_Control(pDX, IDC_CURVE_BGCOLOR, m_btnBgColor);
//	DDX_Text(pDX, IDC_CURVE_POINT, m_sPoint);
	DDX_Text(pDX, IDC_CURVE_ENDHOUR, m_sEndHour);
	DDX_Text(pDX, IDC_CURVE_STARTHOUR, m_sStartHour);
//	DDX_Text(pDX, IDC_CURVE_ENDMIN, m_endMin);
//	DDV_MinMaxInt(pDX, m_endMin, 0, 60);
//	DDX_Text(pDX, IDC_CURVE_STARTMIN, m_startMin);
//	DDV_MinMaxInt(pDX, m_startMin, 0, 59);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCurveProp, CDialog)
	//{{AFX_MSG_MAP(CCurveProp)
	ON_CBN_SELCHANGE(IDC_CURVE_COMBO, OnSelchangeCurveCombo)
	ON_BN_CLICKED(IDC_CURVE_SAVE, OnCurveSave)
//	ON_BN_CLICKED(IDC_CURVE_BGCOLOR, OnCurveBgcolor)
//	ON_BN_CLICKED(IDC_CURVE_COLOR, OnCurveColor)
	ON_NOTIFY(UDN_DELTAPOS, IDC_CURVE_SPINSTART, OnDeltaposCurveSpinstart)
	ON_NOTIFY(UDN_DELTAPOS, IDC_CURVE_SPINEND, OnDeltaposCurveSpinend)
	ON_NOTIFY(DTN_CLOSEUP, IDC_CURVE_ENDDATEPICKER, OnCloseupCurveEnddatepicker)
	ON_NOTIFY(DTN_CLOSEUP, IDC_CURVE_STARTDATEPICKER, OnCloseupCurveStartdatepicker)
//	ON_EN_CHANGE(IDC_CURVE_STARTMIN, OnChangeCurveStartmin)
	ON_BN_CLICKED(IDC_CHECK_GRID, OnCheckGrid)
//	ON_NOTIFY(DTN_DATETIMECHANGE, IDC_CURVE_STARTDATEPICKER, OnDatetimechangeCurveStartdatepicker)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCurveProp message handlers

BOOL CCurveProp::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
//	UpdateData(TRUE);  //0115
//    m_btnBgColor.SetColorFace(m_colorBg);
//	m_btnCurveColor.SetColorFace(m_colorCurve);
	m_comboNo.SetCurSel(0);

    if(m_sCheckGrid)
    	m_ctrlCheckGrid.SetCheck(1);
	else
    	m_ctrlCheckGrid.SetCheck(0);

    	m_BCheckMax.SetCheck(1);
    	m_BCheckMean.SetCheck(1);
    	m_BCheckMin.SetCheck(1);
//	if(m_pCurveProp != NULL)
//	{
///		m_colorCurve = RGB(0,255,0);
//		m_colorCurve = m_pCurveProp->lineColor;
///		m_btnCurveColor.SetColorFace(m_colorCurve);
///		m_sPoint = m_pCurveProp->point;   //200;//
///	}
///	UpdateData(FALSE);
///	Invalidate();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CCurveProp::OnSelchangeCurveCombo() 
{
  	UpdateData(TRUE);  //0115
//    int no = m_comboNo.GetCurSel();

//    m_sPoint = (m_pCurveProp+no)->point;
//    m_colorCurve = (m_pCurveProp+no)->lineColor;
//    m_btnCurveColor.SetColorFace(m_colorCurve);

    UpdateData(FALSE);
    Invalidate();
}

void CCurveProp::OnCurveSave() 
{
	UpdateData(TRUE);
	int no = m_comboNo.GetCurSel();
	memset((m_pCurveProp+no),0,sizeof(CURVEPROP));

	(m_pCurveProp+no)->point = m_sPoint;
//	(m_pCurveProp+no)->lineColor = m_colorCurve;

	CMainFrame *pMainFrame = (CMainFrame *)(AfxGetApp()->m_pMainWnd);
	if(pMainFrame)
	{
       	StructPoint struPoint;
		if(pMainFrame->m_PointMap.Lookup(m_sPoint,struPoint))
		{
        	(m_pCurveProp+no)->Standard = struPoint.Standard;
         	(m_pCurveProp+no)->unConnectorID = struPoint.unConnectorID;
        	(m_pCurveProp+no)->Type = struPoint.Type;
			(m_pCurveProp+no)->WarningMaxValue = struPoint.m_StruSimulate.WarningMaxValue;
			(m_pCurveProp+no)->WarningMinValue = struPoint.m_StruSimulate.WarningMinValue;
			(m_pCurveProp+no)->MaxValue = struPoint.m_StruSimulate.MaxValue;
			(m_pCurveProp+no)->MinValue = struPoint.m_StruSimulate.MinValue;
			if((m_pCurveProp+no)->Type ==1)
	    		(m_pCurveProp+no)->WarnMode = struPoint.m_StruSimulate.WarnMode;
			else
	    		(m_pCurveProp+no)->WarnMode = struPoint.m_StruSwitch.WarnMode;
            CString str2 = struPoint.m_StruSimulate.StrUnit;
			_tcscpy((m_pCurveProp+no)->StrUnit,str2);
		}
	}
	UpdateData(FALSE);  //0115
}


void CCurveProp::OnCurveBgcolor() 
{
	CColorDialog color;
	if(color.DoModal() == IDOK)
	{
//		m_colorBg = color.GetColor();
//		m_btnBgColor.SetColorFace(m_colorBg);
		Invalidate();
	}
}

void CCurveProp::OnCurveColor() 
{
   CColorDialog color;
   if(color.DoModal() == IDOK)
   {
//	   m_colorCurve = color.GetColor();
//	   m_btnCurveColor.SetColorFace(m_colorCurve);
	   Invalidate();
   }
}

/*void CCurveProp::OnCurveSelstart() 
{
	CDatetime dt;
	if(dt.DoModal() == IDOK)
	{
		m_strStartTime.Format("%d-%d-%d",dt.m_time.GetYear(),dt.m_time.GetMonth(),dt.m_time.GetDay());
		UpdateData(FALSE);
	}
	
}

void CCurveProp::OnCurveSelend() 
{
	CDatetime dt;
	if(dt.DoModal() == IDOK)
	{
		m_strEndTime.Format("%d-%d-%d",dt.m_time.GetYear(),dt.m_time.GetMonth(),dt.m_time.GetDay());
		UpdateData(FALSE);
	}	
}
*/

void CCurveProp::OnDeltaposCurveSpinstart(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);    //0115
	m_sStartHour += pNMUpDown->iDelta;
	if(m_sStartHour < 0)
		m_sStartHour = 23;
	else if(m_sStartHour > 23)
		m_sStartHour = 0;
	UpdateData(FALSE);
	*pResult = 0;
}

void CCurveProp::OnDeltaposCurveSpinend(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);  //0115
	m_sEndHour += pNMUpDown->iDelta;
	if(m_sEndHour < 0)
		m_sEndHour = 23;
	else if(m_sEndHour > 23)
		m_sEndHour = 0;
	UpdateData(FALSE);
	*pResult = 0;
}

void CCurveProp::OnCloseupCurveEnddatepicker(NMHDR* pNMHDR, LRESULT* pResult) 
{
	UpdateData(TRUE);  //0115
     m_endDateCtrl.GetTime(m_endDate);	
	UpdateData(FALSE);
	*pResult = 0;
}

void CCurveProp::OnCloseupCurveStartdatepicker(NMHDR* pNMHDR, LRESULT* pResult) 
{
	UpdateData(TRUE);  //0115
	m_startDateCtrl.GetTime(m_startDate);
	UpdateData(FALSE);
	*pResult = 0;
}

BOOL CCurveProp::DestroyWindow() 
{
	UpdateData(TRUE);  //0115
//	m_endDateCtrl.GetTime(m_endDate);	
//	m_startDateCtrl.GetTime(m_startDate);
	UpdateData(FALSE);
//	   Invalidate();

	return CDialog::DestroyWindow();
}

void CCurveProp::OnChangeCurveStartmin() 
{
//	UpdateData(TRUE);//0115
	m_endMin = m_startMin +1;
	if(m_endMin >= 60)
		m_endMin = 0;
//	UpdateData(FALSE);
}

void CCurveProp::OnCheckGrid() 
{
	// TODO: Add your control notification handler code here
    if(m_ctrlCheckGrid.GetCheck() == 1)
    	m_sCheckGrid = TRUE;
	else
    	m_sCheckGrid = FALSE;
}

void CCurveProp::OnDatetimechangeCurveStartdatepicker(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
//	m_startDateCtrl.GetTime(m_startDate);

	*pResult = 0;
}
