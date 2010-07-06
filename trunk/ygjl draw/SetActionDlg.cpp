// SetActionDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Draw.h"
#include "SetActionDlg.h"
#include "SetLineActionDlg.h"
#include "SetFillActionDlg.h"
#include "SetRayActionDlg.h"
#include "SetPercentFillDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSetActionDlg dialog


CSetActionDlg::CSetActionDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSetActionDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSetActionDlg)
	//}}AFX_DATA_INIT
}


void CSetActionDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSetActionDlg)
	DDX_Check(pDX, IDC_CHECK_FILL, m_bIsFillAction);
	DDX_Check(pDX, IDC_CHECK_LINE, m_bIsLineAction);
	DDX_Check(pDX, IDC_CHECK_PERCENT_H, m_bIsPercentHAction);
	DDX_Check(pDX, IDC_CHECK_PERCENT_V, m_bIsPercentVAction);
///	DDX_Check(pDX, IDC_CHECK_RAY, m_bIsRayAction);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSetActionDlg, CDialog)
	//{{AFX_MSG_MAP(CSetActionDlg)
	ON_BN_CLICKED(IDC_BUTTON_LINE, OnButtonLine)
	ON_BN_CLICKED(IDC_BUTTON_FILL, OnButtonFill)
///	ON_BN_CLICKED(IDC_BUTTON_RAY, OnButtonRay)
	ON_BN_CLICKED(IDC_BUTTON_PERCENT_H, OnButtonPercentH)
	ON_BN_CLICKED(IDC_BUTTON_PERCENT_V, OnButtonPercentV)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSetActionDlg message handlers

void CSetActionDlg::OnButtonLine() 
{
	CSetLineActionDlg LineDlg;
	LineDlg.m_clrInLineColor = m_ActionStruct.stcLineChange.clrInLineColor;
	LineDlg.m_clrOutLineColor = m_ActionStruct.stcLineChange.clrOutLineColor;
	LineDlg.m_clrCommErrorLineColor = m_ActionStruct.stcLineChange.clrCommErrorLineColor;
	LineDlg.m_LineWarn_state = m_ActionStruct.stcLineChange.LineWarn_state;
	LineDlg.m_nPointNo = m_ActionStruct.stcLineChange.nPoint;

	if(LineDlg.DoModal() != IDOK)
		return;

	m_ActionStruct.stcLineChange.clrInLineColor = LineDlg.m_clrInLineColor;
	m_ActionStruct.stcLineChange.clrOutLineColor = LineDlg.m_clrOutLineColor;
	m_ActionStruct.stcLineChange.clrCommErrorLineColor = LineDlg.m_clrCommErrorLineColor;
	m_ActionStruct.stcLineChange.LineWarn_state = LineDlg.m_LineWarn_state;
	m_ActionStruct.stcLineChange.nPoint = LineDlg.m_nPointNo;
	
	m_bIsLineAction = TRUE;
	UpdateData(FALSE);
}

void CSetActionDlg::OnButtonFill() 
{
	CSetFillActionDlg Filldlg;
	Filldlg.m_clrInFillColor = m_ActionStruct.stcFillChange.clrInFillColor;
	Filldlg.m_clrOutFillColor = m_ActionStruct.stcFillChange.clrOutFillColor;
	Filldlg.m_clrCommErrorFillColor = m_ActionStruct.stcFillChange.clrCommErrorFillColor;
	Filldlg.m_FillWarn_state = m_ActionStruct.stcFillChange.FillWarn_state;
	Filldlg.m_nPointNo = m_ActionStruct.stcFillChange.nPoint;

	if(Filldlg.DoModal() != IDOK)
		return;

	m_ActionStruct.stcFillChange.clrInFillColor = Filldlg.m_clrInFillColor;
	m_ActionStruct.stcFillChange.clrOutFillColor = Filldlg.m_clrOutFillColor;
	m_ActionStruct.stcFillChange.clrCommErrorFillColor = Filldlg.m_clrCommErrorFillColor;
	m_ActionStruct.stcFillChange.FillWarn_state = Filldlg.m_FillWarn_state;
	m_ActionStruct.stcFillChange.nPoint = Filldlg.m_nPointNo;
	
	m_bIsFillAction = TRUE;
	UpdateData(FALSE);
}

void CSetActionDlg::OnButtonRay() 
{
	CSetRayActionDlg   Raydlg;
	Raydlg.m_clrEndColor = m_ActionStruct.stcRayChange.clrRayEndColor;
	Raydlg.m_clrStartColor = m_ActionStruct.stcRayChange.clrRayStartColor;
	Raydlg.m_nMax = m_ActionStruct.stcRayChange.nMax;
	Raydlg.m_nMin = 	m_ActionStruct.stcRayChange.nMin;
	Raydlg.m_nPointNo = m_ActionStruct.stcRayChange.nPoint;

	if(m_ActionStruct.stcRayChange.bRayType)
		Raydlg.m_strType = "或隐或现";
	else
		Raydlg.m_strType = "颜色变换";

	if(m_ActionStruct.stcRayChange.nRaySpeed == 20)
		Raydlg.m_strSpeed = "慢速";
	if(m_ActionStruct.stcRayChange.nRaySpeed == 50)
		Raydlg.m_strSpeed = "中速";
	if(m_ActionStruct.stcRayChange.nRaySpeed == 80)
		Raydlg.m_strSpeed = "快速";

	if(Raydlg.DoModal() != IDOK)
		return;

	m_ActionStruct.stcRayChange.clrRayEndColor = Raydlg.m_clrEndColor;
	m_ActionStruct.stcRayChange.clrRayStartColor = Raydlg.m_clrStartColor;
	m_ActionStruct.stcRayChange.nMax = Raydlg.m_nMax;
	m_ActionStruct.stcRayChange.nMin = Raydlg.m_nMin;
	m_ActionStruct.stcRayChange.nPoint = Raydlg.m_nPointNo;

	if(Raydlg.m_strType == "或隐或现")
		m_ActionStruct.stcRayChange.bRayType = TRUE;
	else
		m_ActionStruct.stcRayChange.bRayType = FALSE;

	m_ActionStruct.stcRayChange.nRaySpeed = 20;
	if(Raydlg.m_strSpeed == "慢速")
		m_ActionStruct.stcRayChange.nRaySpeed = 20;
	if(Raydlg.m_strSpeed == "中速")
		m_ActionStruct.stcRayChange.nRaySpeed = 50;
	if(Raydlg.m_strSpeed == "快速")
		m_ActionStruct.stcRayChange.nRaySpeed = 80;

	m_bIsRayAction = TRUE;
	UpdateData(FALSE);
}

void CSetActionDlg::OnButtonPercentH() 
{
	CSetPercentFillDlg percentDlg;
	percentDlg.m_bIsH = TRUE;
	percentDlg.m_clrFillColor = m_ActionStruct.stcPHChange.clrFillColor;
	percentDlg.m_pufdata = m_ActionStruct.stcPHChange.pufdata;
	percentDlg.m_nPointNo = m_ActionStruct.stcPHChange.nPoint;

	if(m_ActionStruct.stcPHChange.ReferencePoint == LEFT)
		percentDlg.m_strReferencePoint = "左边";
	if(m_ActionStruct.stcPHChange.ReferencePoint == RIGHT)
		percentDlg.m_strReferencePoint = "右边";

	if(percentDlg.DoModal() != IDOK)
		return;

	m_ActionStruct.stcPHChange.clrFillColor = percentDlg.m_clrFillColor;
	m_ActionStruct.stcPHChange.pufdata = percentDlg.m_pufdata;
	m_ActionStruct.stcPHChange.nPoint = percentDlg.m_nPointNo;

	if(percentDlg.m_strReferencePoint == "左边")
		m_ActionStruct.stcPHChange.ReferencePoint = LEFT;
	if(percentDlg.m_strReferencePoint == "右边")
		m_ActionStruct.stcPHChange.ReferencePoint = RIGHT;

	m_bIsPercentHAction = TRUE;
	UpdateData(FALSE);
}

void CSetActionDlg::OnButtonPercentV() 
{
	CSetPercentFillDlg percentDlg;
	percentDlg.m_bIsH = FALSE;
	percentDlg.m_clrFillColor = m_ActionStruct.stcPVChange.clrFillColor;
	percentDlg.m_pufdata = m_ActionStruct.stcPVChange.pufdata;
	percentDlg.m_nPointNo = m_ActionStruct.stcPVChange.nPoint;

	if(m_ActionStruct.stcPVChange.ReferencePoint == TOP)
		percentDlg.m_strReferencePoint = "下面";
	if(m_ActionStruct.stcPVChange.ReferencePoint == BOTTOM)
		percentDlg.m_strReferencePoint = "上面";

	if(percentDlg.DoModal() != IDOK)
		return;

	m_ActionStruct.stcPVChange.clrFillColor = percentDlg.m_clrFillColor;
	m_ActionStruct.stcPVChange.pufdata = percentDlg.m_pufdata;
	m_ActionStruct.stcPVChange.nPoint = percentDlg.m_nPointNo;

	if(percentDlg.m_strReferencePoint == "下面")
		m_ActionStruct.stcPVChange.ReferencePoint = TOP;
	if(percentDlg.m_strReferencePoint == "上面")
		m_ActionStruct.stcPVChange.ReferencePoint = BOTTOM;

	m_bIsPercentVAction = TRUE;
	UpdateData(FALSE);

}

BOOL CSetActionDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_bIsFillAction = m_ActionStruct.bIsFillColorChange;
	m_bIsLineAction = m_ActionStruct.bIsLineColorChange;
	m_bIsPercentHAction = m_ActionStruct.bIsPencentFillH;
	m_bIsPercentVAction = m_ActionStruct.bIsPencentFillV;
	m_bIsRayAction = m_ActionStruct.bIsRayChange;

	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CSetActionDlg::OnOK() 
{
	UpdateData();
	m_ActionStruct.bIsFillColorChange = m_bIsFillAction;
	m_ActionStruct.bIsLineColorChange = m_bIsLineAction;
	m_ActionStruct.bIsPencentFillH = m_bIsPercentHAction;
	m_ActionStruct.bIsPencentFillV = m_bIsPercentVAction;
	m_ActionStruct.bIsRayChange = m_bIsRayAction;

	CDialog::OnOK();
}

