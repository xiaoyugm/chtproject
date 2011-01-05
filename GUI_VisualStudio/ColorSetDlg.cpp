// ColorSetDlg.cpp : implementation file
//

#include "stdafx.h"
#include "GUI_VisualStudio.h"
#include "ColorSetDlg.h"
//#include "MainFrm.h"
//#include "DrawView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CommonStr             m_CommonStr[20];
/////////////////////////////////////////////////////////////////////////////
// CColorSetDlg property page

IMPLEMENT_DYNCREATE(CColorSetDlg, CDialog)

CColorSetDlg::CColorSetDlg() : CDialog(CColorSetDlg::IDD)
{
	//{{AFX_DATA_INIT(CButtonSetDlg)
//	m_color1 = RGB(0x00,0xff,0x00);  //65280
//	m_color2 = RGB(0xff,0x00,0x00);  //255
//	m_color3 = RGB(0x00,0x00,0xff);  //16711680
//	m_color9 = 65535; //RGB(0xff,0xff,0x00);
	m_ColorsetNew = &m_Colorset;
	m_ntrans = 0;
	m_nlist = 0;
	//}}AFX_DATA_INIT
}

CColorSetDlg::~CColorSetDlg()
{
}

void CColorSetDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CButtonSetDlg)
	DDX_Control(pDX, IDC_BUTCOL1, m_ctlColor1);
	DDX_Control(pDX, IDC_BUTCOL2, m_ctlColor2);
	DDX_Control(pDX, IDC_BUTCOL3, m_ctlColor3);
	DDX_Control(pDX, IDC_BUTCOL4, m_ctlColor4);
	DDX_Control(pDX, IDC_BUTCOL5, m_ctlColor5);
	DDX_Control(pDX, IDC_BUTCOL6, m_ctlColor6);
	DDX_Control(pDX, IDC_BUTCOL7, m_ctlColor7);
	DDX_Control(pDX, IDC_BUTCOL8, m_ctlColor8);
	DDX_Control(pDX, IDC_BUTCOL9, m_ctlColor9);
//	DDX_Text(pDX, IDC_EDIT_TEXT, m_strButton);
//	DDV_MaxChars(pDX, m_strButton, 100);
//	DDX_Text(pDX, IDC_EDIT_FONTSIZE, m_fontSize);
//	DDV_MinMaxByte(pDX, m_fontSize, 1, 72);
//	DDX_Text(pDX, IDC_EDIT_LINK_VIEW, m_strLinkViewName);
	//}}AFX_DATA_MAP
	DDX_XTColorPicker(pDX, IDC_BUTCOL1, m_color1);
	DDX_XTColorPicker(pDX, IDC_BUTCOL2, m_color2);
	DDX_XTColorPicker(pDX, IDC_BUTCOL3, m_color3);
	DDX_XTColorPicker(pDX, IDC_BUTCOL4, m_color4);
	DDX_XTColorPicker(pDX, IDC_BUTCOL5, m_color5);
	DDX_XTColorPicker(pDX, IDC_BUTCOL6, m_color6);
	DDX_XTColorPicker(pDX, IDC_BUTCOL7, m_color7);
	DDX_XTColorPicker(pDX, IDC_BUTCOL8, m_color8);
	DDX_XTColorPicker(pDX, IDC_BUTCOL9, m_color9);
}


BEGIN_MESSAGE_MAP(CColorSetDlg, CDialog)
	//{{AFX_MSG_MAP(CButtonSetDlg)
//	ON_CBN_SELENDOK(IDC_COMBO_STYLE, OnSelendokComboStyle)
//	ON_CBN_SELENDOK(IDC_COMBO_BORDER, OnSelendokComboBorder)
//	ON_CBN_SELENDOK(IDC_COMBO_FONT, OnSelendokComboFont)
//	ON_CBN_SELENDOK(IDC_COMBO_POSITION, OnSelendokComboPosition)
	ON_BN_CLICKED(IDOK_CSEND, OnButSend)
	ON_WM_DESTROY()
//	ON_BN_CLICKED(IDC_BUTTON_PATH, OnButtonPath)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CButtonSetDlg message handlers

BOOL CColorSetDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

		m_Colorset.Create();
		m_Colorset.CursorType(adOpenDynamic);
		m_Colorset.CacheSize(50);
		m_Colorset._SetRecordsetEvents(new CAccountSetEvents);
		m_Colorset.Open(_T("Select * From colorset"), &theApp.m_Cn);
		m_Colorset.MarshalOptions(adMarshalModifiedOnly);

		int coxx,vcolor;
		int iItem = 0;
		m_Colorset.MoveFirst();
		while ( !m_Colorset.IsEOF() )
		{
			coxx = m_Colorset.m_szColorID;
			vcolor = m_Colorset.m_szColorrefset;
			if(coxx == 0)
            	m_color1 = vcolor;  //65280
			if(coxx == 16)
        	m_color2 = vcolor;  //255
			if(coxx == 32)
        	m_color3 = vcolor;  //16711680
			if(coxx == 64)
          	m_color4 = vcolor;
			if(coxx == 80)
          	m_color5 = vcolor;
			if(coxx == 96)
        	m_color6 = vcolor;
			if(coxx == 112)
          	m_color7 = vcolor;
			if(coxx == 128)
          	m_color8 = vcolor;
			if(coxx == 144)
           	m_color9 = vcolor; //RGB(0xff,0xff,0x00);
//				  iItem++;
			m_Colorset.MoveNext();
		}

  if(m_ntrans >0)
  {
     	GetDlgItem(IDC_STATICN)->SetWindowText(_T("列表"));
	  if(m_nlist == 1)
          m_color1 = m_Str2Data.String2Int(m_CommonStr[m_ntrans].strc[9]);  //65280
	  if(m_nlist == 2)
          m_color1 = m_Str2Data.String2Int(m_CommonStr[m_ntrans].strc[39]);  //65280
	  if(m_nlist == 3)
          m_color1 = m_Str2Data.String2Int(m_CommonStr[m_ntrans].strc[69]);  //65280
        MoveWindow(CRect(400,300,700,400));
     	GetDlgItem(IDOK_CSEND)->MoveWindow(30,40,80  ,25);
     	GetDlgItem(IDCANCEL)->MoveWindow(160,40,80  ,25);
    	GetDlgItem(IDC_STATICA)->ShowWindow(SW_HIDE);;
    	GetDlgItem(IDC_BUTCOL2)->ShowWindow(SW_HIDE);;
    	GetDlgItem(IDC_STATICB)->ShowWindow(SW_HIDE);;
    	GetDlgItem(IDC_BUTCOL3)->ShowWindow(SW_HIDE);;
  }

	UpdateData(FALSE);	

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE

}

void CColorSetDlg::OnSelEndOkClr()
{
	UpdateData();	
}

void CColorSetDlg::OnSelendokComboStyle() 
{

}

void CColorSetDlg::OnSelendokComboBorder() 
{


}

void CColorSetDlg::OnSelendokComboFont() 
{
//	 m_ctlFontCombo.GetSelFont(m_fontName);
}

void CColorSetDlg::OnSelendokComboPosition() 
{

}

void CColorSetDlg::OnDestroy() 
{
    if ( m_Colorset._IsOpen() )
      m_Colorset.Close();
  CDialog::OnDestroy();	
}

void CColorSetDlg::OnButSend() 
{
	UpdateData();	
		int coxx;
	if(m_ntrans == 0)
	{
		for(int i=0;i<12;i=i++ )
		{
			coxx = i*16;
            				try
							{
                             m_Colorset.AbsolutePosition(i+1);
         					 m_ColorsetNew->m_szColorID = coxx;

			if(coxx == 0)
	         	m_ColorsetNew->m_szColorrefset = m_color1;
			if(coxx == 16)
	         	m_ColorsetNew->m_szColorrefset = m_color2;
			if(coxx == 32)
	         	m_ColorsetNew->m_szColorrefset = m_color3;
			if(coxx == 64)
	         	m_ColorsetNew->m_szColorrefset = m_color4;
			if(coxx == 80)
	         	m_ColorsetNew->m_szColorrefset = m_color5;
			if(coxx == 96)
	         	m_ColorsetNew->m_szColorrefset = m_color6;
			if(coxx == 112)
	         	m_ColorsetNew->m_szColorrefset = m_color7;
			if(coxx == 128)
	         	m_ColorsetNew->m_szColorrefset = m_color8;
			if(coxx == 144)
	         	m_ColorsetNew->m_szColorrefset = m_color9;

					   	     m_ColorsetNew->Update();    //Update the recordset
							}
		     			    catch (CAxException *e)
							{
					        	AfxMessageBox(e->m_szErrorDesc, MB_OK);
				        		delete e;
							}
		}//for
		theApp.InitData();
	}
	else
	{
	CString strrsy ,strclm,strclm1;
    CString strSQL,strSQL1,strrsy1;
	strrsy = gstrTimeOut + "\\" + strMetrics+ "rsy\\";
	strrsy1 ="dispoint"+strMetrics;
	  if(m_nlist == 1)
          coxx = 19;  //65280
	  if(m_nlist == 2)
          coxx = 119;  //65280
	  if(m_nlist == 3)
		  coxx = 219;

            strSQL.Format("UPDATE '%s' SET LP%d='%d' WHERE DISID=%d;",
			    	     strrsy1, m_ntrans ,m_color1 , coxx );
			theApp.db3.execDML(strSQL);
        theApp.InitSQLite3();
    	theApp.m_RTDM.InitDisplay();
	}
        EndDialog(IDOK);
}

void CColorSetDlg::InitSelectViewCombo()
{
/*	CMainFrame *pMainFrame = (CMainFrame *)AfxGetApp()->m_pMainWnd;
	POSITION pos = pMainFrame->m_wndTabDockBar.m_wndTreeCtrl.m_map.GetStartPosition();
	while (pos != NULL)
	{	
		CDrawView *pView;
		CString strTemp;
		pMainFrame->m_wndTabDockBar.m_wndTreeCtrl.m_map.GetNextAssoc(pos,strTemp,pView);
		m_ctlLinkView.AddString(strTemp);
	}*/
}

void CColorSetDlg::OnButtonPath() 
{
/*	char filter[] = "文件(*.rsy)|*.rsy||";
	CFileDialog filedlg(TRUE,NULL,NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,filter,NULL);
	if(filedlg.DoModal() == IDOK)
	{
		m_strLinkViewName = filedlg.GetPathName();
		UpdateData(FALSE);
	}*/
}
