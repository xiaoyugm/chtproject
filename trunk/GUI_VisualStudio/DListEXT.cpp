// DListEXT.cpp : implementation file
//

#include "stdafx.h"
#include "gui_visualstudio.h"
#include "DListEXT.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CommonStr             m_CommonStr[20];
/////////////////////////////////////////////////////////////////////////////
// CDListEXT dialog


CDListEXT::CDListEXT(CWnd* pParent /*=NULL*/)
	: CDialog(CDListEXT::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDListEXT)
	m_ntrans = 0;
	m_nlist = 0;
	//}}AFX_DATA_INIT
}


void CDListEXT::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDListEXT)
	DDX_Control(pDX, IDC_CHECKMAX, m_cChMAX);
	DDX_Control(pDX, IDC_CHECKMIN, m_cChMIN);
	DDX_Control(pDX, IDC_CHECKMEAN, m_cChMEAN);
	DDX_Control(pDX, IDC_CHECKB, m_cChB);
	DDX_Control(pDX, IDC_CHECKR, m_cChR);
	DDX_Control(pDX, IDC_CHECKAH, m_cChAH);
	DDX_Control(pDX, IDC_CHECKAL, m_cChAL);
	DDX_Control(pDX, IDC_CHECKSH, m_cChSH);
	DDX_Control(pDX, IDC_CHECKSL, m_cChSL);
	DDX_Control(pDX, IDC_CHECKBT, m_cChBT);
	DDX_Control(pDX, IDC_CHECKRT, m_cChRT);
	DDX_Control(pDX, IDC_CHECKAT, m_cChAT);
	DDX_Control(pDX, IDC_CHECKFDT, m_cChFDT);
	DDX_Control(pDX, IDC_CHECKBS, m_cChBS);
	DDX_Control(pDX, IDC_CHECKWN, m_cChWN);
	DDX_Control(pDX, IDC_CHECKWT, m_cChWT);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDListEXT, CDialog)
	//{{AFX_MSG_MAP(CDListEXT)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDListEXT message handlers

BOOL CDListEXT::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	        m_cChMAX.SetCheck(m_Str2Data.String2Int(m_CommonStr[m_ntrans].strc[90+20*(m_nlist-1)]));
	        m_cChMIN.SetCheck(m_Str2Data.String2Int(m_CommonStr[m_ntrans].strc[91+20*(m_nlist-1)]));
	        m_cChMEAN.SetCheck(m_Str2Data.String2Int(m_CommonStr[m_ntrans].strc[92+20*(m_nlist-1)]));
	        m_cChB.SetCheck(m_Str2Data.String2Int(m_CommonStr[m_ntrans].strc[93+20*(m_nlist-1)]));
	        m_cChR.SetCheck(m_Str2Data.String2Int(m_CommonStr[m_ntrans].strc[94+20*(m_nlist-1)]));
	        m_cChAH.SetCheck(m_Str2Data.String2Int(m_CommonStr[m_ntrans].strc[95+20*(m_nlist-1)]));
	        m_cChAL.SetCheck(m_Str2Data.String2Int(m_CommonStr[m_ntrans].strc[96+20*(m_nlist-1)]));
	        m_cChSH.SetCheck(m_Str2Data.String2Int(m_CommonStr[m_ntrans].strc[97+20*(m_nlist-1)]));
	        m_cChSL.SetCheck(m_Str2Data.String2Int(m_CommonStr[m_ntrans].strc[98+20*(m_nlist-1)]));
	        m_cChBT.SetCheck(m_Str2Data.String2Int(m_CommonStr[m_ntrans].strc[99+20*(m_nlist-1)]));
	        m_cChRT.SetCheck(m_Str2Data.String2Int(m_CommonStr[m_ntrans].strc[100+20*(m_nlist-1)]));
	        m_cChAT.SetCheck(m_Str2Data.String2Int(m_CommonStr[m_ntrans].strc[101+20*(m_nlist-1)]));
	        m_cChFDT.SetCheck(m_Str2Data.String2Int(m_CommonStr[m_ntrans].strc[102+20*(m_nlist-1)]));
	        m_cChBS.SetCheck(m_Str2Data.String2Int(m_CommonStr[m_ntrans].strc[103+20*(m_nlist-1)]));
	        m_cChWN.SetCheck(m_Str2Data.String2Int(m_CommonStr[m_ntrans].strc[104+20*(m_nlist-1)]));
	        m_cChWT.SetCheck(m_Str2Data.String2Int(m_CommonStr[m_ntrans].strc[105+20*(m_nlist-1)]));
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDListEXT::OnOK() 
{
	UpdateData();	
		int coxx =0;

	CString strrsy ,strclm,strclm1;
    CString strSQL,strSQL1,strrsy1;
	strrsy = gstrTimeOut + "\\" + strMetrics+ "rsy\\";
	strrsy1 ="dispoint"+strMetrics;

		for(int i=50+100*(m_nlist-1);i<66+100*(m_nlist-1);i++ )
		{
			if(i ==50+100*(m_nlist-1))				coxx = m_cChMAX.GetCheck();
			else if(i ==51+100*(m_nlist-1))				coxx = m_cChMIN.GetCheck();
			else if(i ==52+100*(m_nlist-1))				coxx = m_cChMEAN.GetCheck();
			else if(i ==53+100*(m_nlist-1))				coxx = m_cChB.GetCheck();
			else if(i ==54+100*(m_nlist-1))				coxx = m_cChR.GetCheck();
			else if(i ==55+100*(m_nlist-1))				coxx = m_cChAH.GetCheck();
			else if(i ==56+100*(m_nlist-1))				coxx = m_cChAL.GetCheck();
			else if(i ==57+100*(m_nlist-1))				coxx = m_cChSH.GetCheck();
			else if(i ==58+100*(m_nlist-1))				coxx = m_cChSL.GetCheck();
			else if(i ==59+100*(m_nlist-1))				coxx = m_cChBT.GetCheck();
			else if(i ==60+100*(m_nlist-1))				coxx = m_cChRT.GetCheck();
			else if(i ==61+100*(m_nlist-1))				coxx = m_cChAT.GetCheck();
			else if(i ==62+100*(m_nlist-1))				coxx = m_cChFDT.GetCheck();
			else if(i ==63+100*(m_nlist-1))				coxx = m_cChBS.GetCheck();
			else if(i ==64+100*(m_nlist-1))				coxx = m_cChWN.GetCheck();
			else if(i ==65+100*(m_nlist-1))				coxx = m_cChWT.GetCheck();
            strSQL.Format("UPDATE '%s' SET LP%d='%d' WHERE DISID=%d;",
			    	     strrsy1, m_ntrans ,coxx , i );
			theApp.db3.execDML(strSQL);
		}
        theApp.InitSQLite3();
    	theApp.InitDisplay();

	CDialog::OnOK();
}

void CDListEXT::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}
