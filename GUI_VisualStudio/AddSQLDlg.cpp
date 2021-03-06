// AccountDlg.cpp : implementation file
//

#include "stdafx.h"
#include "GUI_VisualStudio.h"
#include "AddSQLDlg.h"
#include "MainFrm.h"

#include "SettingHostDlg.h"

extern  ADTypeTable	     m_ADTypeTable[9];
// CAccountDlg dialog

IMPLEMENT_DYNAMIC(CAccountDlg, CDialog)

CAccountDlg::CAccountDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAccountDlg::IDD, pParent)
{
  m_bEditMode = FALSE;    //新增
  m_pAccountSet = NULL;
  m_pParent = pParent;
  m_pContactSet = NULL;
  m_pMAlocation = NULL;
  str1 ="";  str2="";  str3 ="";  str4 ="";  str5 ="";  str6 ="";  str8 ="";  str9 ="";
  fstr9 =0;  fstr2 =0;  fstr3 =0;  fstr4 =0;  fstr5 =0;  fstr6 =0;
}

CAccountDlg::CAccountDlg(BOOL bEditMode, CWnd* pParent /*=NULL*/)
	: CDialog(CAccountDlg::IDD, pParent)
{
  m_bEditMode = bEditMode;   //修改、编辑 true
  m_pAccountSet = NULL;
  m_pParent = pParent;
  m_pContactSet = NULL;
  m_pMAlocation = NULL;
}

CAccountDlg::~CAccountDlg()
{
}

//Since data buffering occurs in the derived AxLib recordset
//object, we can exchange data directly with the recordset's
//data fields
void CAccountDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
		  DDX_Text(pDX, IDC_EDIT_PATH, str7);
		  DDX_Text(pDX, IDC_EDIT1, str1);
	DDV_MaxChars(pDX, str1, 20);

     if(m_ADTypeTable[0].TableName ==  strtable)   //模拟量
	 {
		  DDX_Text(pDX, IDC_EDIT2, fstr2);
		  DDX_Text(pDX, IDC_EDIT3, fstr3);
		  DDX_Text(pDX, IDC_EDIT4, fstr4);
//	DDV_MinMaxFloat(pDX, fstr4, fstr9, fstr6);
		  DDX_Text(pDX, IDC_EDIT5, fstr5);
		  DDX_Text(pDX, IDC_EDIT6, fstr6);
		  DDX_Text(pDX, IDC_EDIT9, fstr9);
	 }
	 else
	 {
		  DDX_Text(pDX, IDC_EDIT2, str2);
    	DDV_MaxChars(pDX, str2, 20);
		  DDX_Text(pDX, IDC_EDIT3, str3);
    	DDV_MaxChars(pDX, str3, 20);
		  DDX_Text(pDX, IDC_EDIT4, str4);
    	DDV_MaxChars(pDX, str4, 20);
		  DDX_Text(pDX, IDC_EDIT5, str5);
     	DDV_MaxChars(pDX, str5, 20);
		  DDX_Text(pDX, IDC_EDIT6, str6);
     	DDV_MaxChars(pDX, str6, 20);
		  DDX_Text(pDX, IDC_EDIT9, str9);
    	DDV_MaxChars(pDX, str9, 20);
	 }

		  DDX_Text(pDX, IDC_EDIT8, str8);
	DDV_MaxChars(pDX, str8, 10);
		  DDX_Control(pDX, IDC_COMBO_D, m_ComBoxD);
		  DDX_Control(pDX, IDC_COMBO_D9, m_ComBoxD9);
		  DDX_Control(pDX, IDC_COMBO_D5, m_ComBoxD5);
		  DDX_Control(pDX, IDC_COMBO_D6, m_ComBoxD6);
	DDX_Control(pDX, IDC_BUT_MUSIC, m_ctlMusic);
//	DDX_Control(pDX, IDC_CHECKISALM, m_ISAlm);
//	DDX_Control(pDX, IDC_CHECKDALM, m_DAlm);
}

BEGIN_MESSAGE_MAP(CAccountDlg, CDialog)
  ON_BN_CLICKED(IDOK, OnBnClickedOk)
  ON_BN_CLICKED(IDCANCEL, OnBnClickedCancel)
//	ON_EN_CHANGE(IDC_EDIT9, OnChE)
//	ON_EN_UPDATE(IDC_EDIT8, OnChE)
//	ON_EN_CHANGE(IDC_EDIT_PATH, OnChE)
//	ON_EN_CHANGE(IDC_EDIT2, OnChE)
//	ON_EN_CHANGE(IDC_EDIT3, OnChE)
//	ON_EN_CHANGE(IDC_EDIT4, OnChE)
//	ON_EN_CHANGE(IDC_EDIT5, OnChE)
//	ON_EN_CHANGE(IDC_EDIT6, OnChE)
//	ON_EN_CHANGE(IDC_EDIT1, OnChE)
//  ON_EN_KILLFOCUS(IDC_ACCNT_ID, OnKillFocusAccntId)
	ON_CBN_SELCHANGE(IDC_COMBO_D, OnchangeComboD)
	ON_CBN_SELCHANGE(IDC_COMBO_D5, OnchangeComboD5)
	ON_CBN_SELCHANGE(IDC_COMBO_D6, OnchangeComboD6)
	ON_BN_CLICKED(IDC_BUT_MUSIC, OnMusicPath)
END_MESSAGE_MAP()


// CAccountDlg message handlers

BOOL CAccountDlg::OnInitDialog()
{
  //Set a pointer to the one instance of the CAxAccountSet
  //member of the main dialog
     if(m_ADTypeTable[1].TableName ==  strtable)//开关量
         m_pAccountSet = &((CSettingHostDlg*) m_pParent)->m_AccountSet;
	 else if(m_ADTypeTable[0].TableName ==  strtable)   //模拟量
          m_pContactSet = &((CSettingHostDlg*) m_pParent)->m_ContactSet;
	 else if(m_ADTypeTable[2].TableName ==  strtable)    //安装地点
          m_pMAlocation = &((CSettingHostDlg*) m_pParent)->m_MAlocation;

  CDialog::OnInitDialog();

        m_ComBoxD.AddString("二态开关量");     //0  ptype
        m_ComBoxD.AddString("分站");           //1
        m_ComBoxD.AddString("控制量");         //2
        m_ComBoxD.AddString("三态开关量");     //3
        m_ComBoxD.AddString("通断量");         //4
		m_ComBoxD.SetCurSel(0);
		//m_pAccountSet->m_szpalms
        m_ComBoxD9.AddString("常开");           //5  控制量
        m_ComBoxD9.AddString("常闭");           //6
        m_ComBoxD9.AddString("电平");           //7
		m_ComBoxD9.SetCurSel(0);
        m_ComBoxD5.AddString("不报警");         //0  
        m_ComBoxD5.AddString("0态报警");        //1
        m_ComBoxD5.AddString("1态报警");        //2
		m_ComBoxD5.SetCurSel(0);
        m_ComBoxD6.AddString("不断电");         //0  
        m_ComBoxD6.AddString("0态断电");        //3
        m_ComBoxD6.AddString("1态断电");        //4
		m_ComBoxD6.SetCurSel(0);

  //If we are editing the record, disable the AccountID edit box
  if ( m_bEditMode )   //修改、编辑 true
  {
	  CString szFind;
//    GetDlgItem(IDC_ACCNT_ID)->EnableWindow(FALSE);
    if(m_ADTypeTable[1].TableName ==  strtable)//开关量
	{
    	  SetWindowText(_T(m_ADTypeTable[1].NameD));
		  m_ComBoxD.SetCurSel(m_pAccountSet->m_szptype);
          GetDlgItem(IDC_COMBO_D)->EnableWindow(FALSE);

			szFind = m_pAccountSet->m_szName;
			szFind.TrimRight();
		  GetDlgItem(IDC_EDIT1)->SetWindowText(szFind);
			 szFind = m_pAccountSet->m_szname0;
			szFind.TrimRight();
		  GetDlgItem(IDC_EDIT2)->SetWindowText(szFind);
			 szFind = m_pAccountSet->m_szname1;
			szFind.TrimRight();
		  GetDlgItem(IDC_EDIT3)->SetWindowText(szFind);
			 szFind = m_pAccountSet->m_szname2;
			szFind.TrimRight();
		  GetDlgItem(IDC_EDIT4)->SetWindowText(szFind);

		  if((m_ComBoxD.GetCurSel() == 0) || (m_ComBoxD.GetCurSel() == 4)||(m_ComBoxD.GetCurSel() == 1))  //二态开关量 通断量 分站
		  {
      		    GetDlgItem(IDC_COMBO_D9)->ShowWindow(SW_HIDE);;
    		  GetDlgItem(IDC_STATIC9)->ShowWindow(SW_HIDE);;
    		  GetDlgItem(IDC_EDIT4)->ShowWindow(SW_HIDE);
	    	  GetDlgItem(IDC_STATIC4)->ShowWindow(SW_HIDE);
	    	  if(m_pAccountSet->m_szpalms == 0) 
			  {
        		GetDlgItem(IDC_EDIT_PATH)->ShowWindow(SW_HIDE);;
        		GetDlgItem(IDC_STATIC7)->ShowWindow(SW_HIDE);;
        		GetDlgItem(IDC_BUT_MUSIC)->ShowWindow(SW_HIDE);;
             	m_ComBoxD5.SetCurSel(0);
	         	m_ComBoxD6.SetCurSel(0);
			  }
			  else if(m_pAccountSet->m_szpalms == 1)
			  {
             		m_ComBoxD5.SetCurSel(1);
	         	  GetDlgItem(IDC_STATIC6)->ShowWindow(SW_HIDE);
      		    GetDlgItem(IDC_COMBO_D6)->ShowWindow(SW_HIDE);;
			  }
			  else if(m_pAccountSet->m_szpalms == 2)
			  {
             		m_ComBoxD5.SetCurSel(2);
	         	  GetDlgItem(IDC_STATIC6)->ShowWindow(SW_HIDE);
      		    GetDlgItem(IDC_COMBO_D6)->ShowWindow(SW_HIDE);;
			  }
			  else if(m_pAccountSet->m_szpalms == 3)
			  {
             		m_ComBoxD6.SetCurSel(1);
	         	  GetDlgItem(IDC_STATIC5)->ShowWindow(SW_HIDE);
      		    GetDlgItem(IDC_COMBO_D5)->ShowWindow(SW_HIDE);;
			  }
			  else if(m_pAccountSet->m_szpalms == 4)
			  {
             		m_ComBoxD6.SetCurSel(2);
	         	  GetDlgItem(IDC_STATIC5)->ShowWindow(SW_HIDE);
      		    GetDlgItem(IDC_COMBO_D5)->ShowWindow(SW_HIDE);;
			  }
			  if(m_ComBoxD.GetCurSel() == 1)
			  {
             		m_ComBoxD5.SetCurSel(2);
                    GetDlgItem(IDC_COMBO_D5)->EnableWindow(FALSE);
	         	  GetDlgItem(IDC_STATIC6)->ShowWindow(SW_HIDE);
         		    GetDlgItem(IDC_COMBO_D6)->ShowWindow(SW_HIDE);;
        		GetDlgItem(IDC_EDIT_PATH)->ShowWindow(SW_SHOW);;
        		GetDlgItem(IDC_STATIC7)->ShowWindow(SW_SHOW);;
        		GetDlgItem(IDC_BUT_MUSIC)->ShowWindow(SW_SHOW);;
			  }

		  }
		  else if(m_ComBoxD.GetCurSel() == 3)     //三态开关量
		  {
      		    GetDlgItem(IDC_COMBO_D9)->ShowWindow(SW_HIDE);;
    		  GetDlgItem(IDC_STATIC9)->ShowWindow(SW_HIDE);;
	    	  if(m_pAccountSet->m_szpalms == 0) 
			  {
        		GetDlgItem(IDC_EDIT_PATH)->ShowWindow(SW_HIDE);;
        		GetDlgItem(IDC_STATIC7)->ShowWindow(SW_HIDE);;
        		GetDlgItem(IDC_BUT_MUSIC)->ShowWindow(SW_HIDE);;
             	m_ComBoxD5.SetCurSel(0);
	         	m_ComBoxD6.SetCurSel(0);
			  }
			  else if(m_pAccountSet->m_szpalms == 1)
			  {
             		m_ComBoxD5.SetCurSel(1);
	         	  GetDlgItem(IDC_STATIC6)->ShowWindow(SW_HIDE);
      		    GetDlgItem(IDC_COMBO_D6)->ShowWindow(SW_HIDE);;
			  }
			  else if(m_pAccountSet->m_szpalms == 2)
			  {
             		m_ComBoxD5.SetCurSel(2);
	         	  GetDlgItem(IDC_STATIC6)->ShowWindow(SW_HIDE);
      		    GetDlgItem(IDC_COMBO_D6)->ShowWindow(SW_HIDE);;
			  }
			  else if(m_pAccountSet->m_szpalms == 3)
			  {
             		m_ComBoxD6.SetCurSel(1);
	         	  GetDlgItem(IDC_STATIC5)->ShowWindow(SW_HIDE);
      		    GetDlgItem(IDC_COMBO_D5)->ShowWindow(SW_HIDE);;
			  }
			  else if(m_pAccountSet->m_szpalms == 4)
			  {
             		m_ComBoxD6.SetCurSel(2);
	         	  GetDlgItem(IDC_STATIC5)->ShowWindow(SW_HIDE);
      		    GetDlgItem(IDC_COMBO_D5)->ShowWindow(SW_HIDE);;
			  }
		  }
		  else if(m_ComBoxD.GetCurSel() == 2)     //控制开关量
		  {
		  GetDlgItem(IDC_STATIC5)->ShowWindow(SW_HIDE);
		  GetDlgItem(IDC_COMBO_D5)->ShowWindow(SW_HIDE);
		  GetDlgItem(IDC_STATIC6)->ShowWindow(SW_HIDE);;
		  GetDlgItem(IDC_COMBO_D6)->ShowWindow(SW_HIDE);
    		  GetDlgItem(IDC_EDIT4)->ShowWindow(SW_HIDE);
	    	  GetDlgItem(IDC_STATIC4)->ShowWindow(SW_HIDE);
//      		    GetDlgItem(IDC_COMBO_D9)->ShowWindow(SW_HIDE);;
        		GetDlgItem(IDC_EDIT_PATH)->ShowWindow(SW_HIDE);;
        		GetDlgItem(IDC_STATIC7)->ShowWindow(SW_HIDE);;
        		GetDlgItem(IDC_BUT_MUSIC)->ShowWindow(SW_HIDE);;
			  if(m_pAccountSet->m_szpalms == 5)
             		m_ComBoxD9.SetCurSel(0);
			  else if(m_pAccountSet->m_szpalms == 6)
             		m_ComBoxD9.SetCurSel(1);
			  else if(m_pAccountSet->m_szpalms == 7)
             		m_ComBoxD9.SetCurSel(2);
		  }
//        		m_ISAlm.SetCheck(1);
//        		m_DAlm.SetCheck(m_pAccountSet->m_szpalms);

			 szFind = m_pAccountSet->m_szfalm;
			szFind.TrimRight();
		  GetDlgItem(IDC_EDIT_PATH)->SetWindowText(szFind);

		  GetDlgItem(IDC_EDIT8)->ShowWindow(SW_HIDE);;
		  GetDlgItem(IDC_STATIC8)->ShowWindow(SW_HIDE);;
		  GetDlgItem(IDC_EDIT5)->ShowWindow(SW_HIDE);;
//		  GetDlgItem(IDC_STATIC5)->ShowWindow(SW_HIDE);;
		  GetDlgItem(IDC_EDIT6)->ShowWindow(SW_HIDE);;
//		  GetDlgItem(IDC_STATIC6)->ShowWindow(SW_HIDE);;
		  GetDlgItem(IDC_EDIT9)->ShowWindow(SW_HIDE);;
		  GetDlgItem(IDC_STATIC9)->SetWindowText("控制量类型");
	}
	else if(m_ADTypeTable[0].TableName ==  strtable)   //模拟量
	{
    	SetWindowText(_T(m_ADTypeTable[0].NameD));
		  szFind = m_pContactSet->m_szName;
		  szFind.TrimRight();
   		  GetDlgItem(IDC_EDIT1)->SetWindowText(szFind);
				  szFind.Format("%.2f",m_pContactSet->m_szltop);
   		  GetDlgItem(IDC_EDIT2)->SetWindowText(szFind);
				  szFind.Format("%.2f",m_pContactSet->m_szlbom);
   		  GetDlgItem(IDC_EDIT3)->SetWindowText(szFind);
				  szFind.Format("%.2f",m_pContactSet->m_szpalmu);
   		  GetDlgItem(IDC_EDIT4)->SetWindowText(szFind);
				  szFind.Format("%.2f",m_pContactSet->m_szpalmd);
   		  GetDlgItem(IDC_EDIT5)->SetWindowText(szFind);
				  szFind.Format("%.2f",m_pContactSet->m_szpbrk);
   		  GetDlgItem(IDC_EDIT6)->SetWindowText(szFind);
				  szFind.Format("%.2f",m_pContactSet->m_szprtn);
   		  GetDlgItem(IDC_EDIT9)->SetWindowText(szFind);
		  szFind = m_pContactSet->m_szpunit;
		  szFind.TrimRight();
   		  GetDlgItem(IDC_EDIT8)->SetWindowText(szFind);
		  szFind = m_pContactSet->m_szfalm;
		  szFind.TrimRight();
   		  GetDlgItem(IDC_EDIT_PATH)->SetWindowText(szFind);
		  GetDlgItem(IDC_STATIC2)->SetWindowText(m_ADTypeTable[0].m_DTypeTFD.ltop);
		  GetDlgItem(IDC_STATIC3)->SetWindowText(m_ADTypeTable[0].m_DTypeTFD.lbom);
		  GetDlgItem(IDC_STATIC4)->SetWindowText(m_ADTypeTable[0].m_DTypeTFD.palmu);
		  GetDlgItem(IDC_STATIC5)->SetWindowText(m_ADTypeTable[0].m_DTypeTFD.palmd);
		  GetDlgItem(IDC_STATIC6)->SetWindowText(m_ADTypeTable[0].m_DTypeTFD.pbrk);
		  GetDlgItem(IDC_COMBO_D)->ShowWindow(SW_HIDE);;
		  GetDlgItem(IDC_STATIC10)->ShowWindow(SW_HIDE);;
		  GetDlgItem(IDC_COMBO_D5)->ShowWindow(SW_HIDE);;
		  GetDlgItem(IDC_COMBO_D6)->ShowWindow(SW_HIDE);;
		  GetDlgItem(IDC_COMBO_D9)->ShowWindow(SW_HIDE);;
	}
    else if(m_ADTypeTable[2].TableName ==  strtable)    //安装地点
	{
    	SetWindowText("修改安装地点");
			szFind = m_pMAlocation->m_szName;
			szFind.TrimRight();
		  GetDlgItem(IDC_EDIT1)->SetWindowText(szFind);
		  GetDlgItem(IDC_EDIT8)->ShowWindow(SW_HIDE);;
		  GetDlgItem(IDC_STATIC8)->ShowWindow(SW_HIDE);;
		  GetDlgItem(IDC_EDIT_PATH)->ShowWindow(SW_HIDE);;
		  GetDlgItem(IDC_STATIC7)->ShowWindow(SW_HIDE);;
		  GetDlgItem(IDC_EDIT6)->ShowWindow(SW_HIDE);;
		  GetDlgItem(IDC_STATIC6)->ShowWindow(SW_HIDE);;
		  GetDlgItem(IDC_EDIT5)->ShowWindow(SW_HIDE);;
		  GetDlgItem(IDC_STATIC5)->ShowWindow(SW_HIDE);;
		  GetDlgItem(IDC_EDIT4)->ShowWindow(SW_HIDE);;
		  GetDlgItem(IDC_STATIC4)->ShowWindow(SW_HIDE);;
		  GetDlgItem(IDC_EDIT3)->ShowWindow(SW_HIDE);;
		  GetDlgItem(IDC_STATIC3)->ShowWindow(SW_HIDE);;
		  GetDlgItem(IDC_EDIT2)->ShowWindow(SW_HIDE);;
		  GetDlgItem(IDC_STATIC2)->ShowWindow(SW_HIDE);;
		  GetDlgItem(IDC_COMBO_D)->ShowWindow(SW_HIDE);;
		  GetDlgItem(IDC_STATIC10)->ShowWindow(SW_HIDE);;
		  GetDlgItem(IDC_BUT_MUSIC)->ShowWindow(SW_HIDE);;
		  GetDlgItem(IDC_EDIT9)->ShowWindow(SW_HIDE);;
		  GetDlgItem(IDC_STATIC9)->ShowWindow(SW_HIDE);;
		  GetDlgItem(IDC_COMBO_D5)->ShowWindow(SW_HIDE);;
		  GetDlgItem(IDC_COMBO_D6)->ShowWindow(SW_HIDE);;
		  GetDlgItem(IDC_COMBO_D9)->ShowWindow(SW_HIDE);;
	}
  }
  else    //新增
  {
    //If this is to be a new record, we need to clear all
    //edit fields in the dialog   IDC_CHECKDALM
    if(m_ADTypeTable[1].TableName ==  strtable)//开关量
	{
        for ( int i = IDC_EDIT1; i <= IDC_EDIT6; i++ )
            SetDlgItemText(i, _T(""));
      SetDlgItemText(IDC_EDIT_PATH, _T(""));
      SetDlgItemText(IDC_EDIT8, _T(""));
      SetDlgItemText(IDC_EDIT9, _T(""));
//		m_ISAlm.SetCheck(1);
    	SetWindowText(_T(m_ADTypeTable[1].NameD));
		  GetDlgItem(IDC_EDIT5)->ShowWindow(SW_HIDE);;
		  GetDlgItem(IDC_EDIT8)->ShowWindow(SW_HIDE);;
		  GetDlgItem(IDC_STATIC8)->ShowWindow(SW_HIDE);;
		  GetDlgItem(IDC_EDIT6)->ShowWindow(SW_HIDE);;
		  GetDlgItem(IDC_EDIT4)->ShowWindow(SW_HIDE);
		  GetDlgItem(IDC_STATIC4)->ShowWindow(SW_HIDE);
		  GetDlgItem(IDC_EDIT9)->ShowWindow(SW_HIDE);;
		  GetDlgItem(IDC_STATIC9)->ShowWindow(SW_HIDE);;
		  GetDlgItem(IDC_COMBO_D9)->ShowWindow(SW_HIDE);;
		  GetDlgItem(IDC_STATIC9)->SetWindowText("控制量类型");
        		GetDlgItem(IDC_EDIT_PATH)->ShowWindow(SW_HIDE);;
        		GetDlgItem(IDC_STATIC7)->ShowWindow(SW_HIDE);;
        		GetDlgItem(IDC_BUT_MUSIC)->ShowWindow(SW_HIDE);;
	}
	else if(m_ADTypeTable[0].TableName ==  strtable)     //模拟量
	{
    	SetWindowText(_T(m_ADTypeTable[0].NameD));
		  GetDlgItem(IDC_STATIC2)->SetWindowText(m_ADTypeTable[0].m_DTypeTFD.ltop);
		  GetDlgItem(IDC_STATIC3)->SetWindowText(m_ADTypeTable[0].m_DTypeTFD.lbom);
		  GetDlgItem(IDC_STATIC4)->SetWindowText(m_ADTypeTable[0].m_DTypeTFD.palmu);
		  GetDlgItem(IDC_STATIC5)->SetWindowText(m_ADTypeTable[0].m_DTypeTFD.palmd);
		  GetDlgItem(IDC_STATIC6)->SetWindowText(m_ADTypeTable[0].m_DTypeTFD.pbrk);
		  GetDlgItem(IDC_COMBO_D)->ShowWindow(SW_HIDE);;
		  GetDlgItem(IDC_STATIC10)->ShowWindow(SW_HIDE);;
		  GetDlgItem(IDC_COMBO_D5)->ShowWindow(SW_HIDE);;
		  GetDlgItem(IDC_COMBO_D6)->ShowWindow(SW_HIDE);;
		  GetDlgItem(IDC_COMBO_D9)->ShowWindow(SW_HIDE);;
	}
    else if(m_ADTypeTable[2].TableName ==  strtable)     //安装地点
	{
    	SetWindowText("添加安装地点");
		  GetDlgItem(IDC_EDIT8)->ShowWindow(SW_HIDE);;
		  GetDlgItem(IDC_STATIC8)->ShowWindow(SW_HIDE);;
		  GetDlgItem(IDC_EDIT_PATH)->ShowWindow(SW_HIDE);;
		  GetDlgItem(IDC_STATIC7)->ShowWindow(SW_HIDE);;
		  GetDlgItem(IDC_EDIT6)->ShowWindow(SW_HIDE);;
		  GetDlgItem(IDC_STATIC6)->ShowWindow(SW_HIDE);;
		  GetDlgItem(IDC_EDIT5)->ShowWindow(SW_HIDE);;
		  GetDlgItem(IDC_STATIC5)->ShowWindow(SW_HIDE);;
		  GetDlgItem(IDC_EDIT4)->ShowWindow(SW_HIDE);;
		  GetDlgItem(IDC_STATIC4)->ShowWindow(SW_HIDE);;
		  GetDlgItem(IDC_EDIT3)->ShowWindow(SW_HIDE);;
		  GetDlgItem(IDC_STATIC3)->ShowWindow(SW_HIDE);;
		  GetDlgItem(IDC_EDIT2)->ShowWindow(SW_HIDE);;
		  GetDlgItem(IDC_STATIC2)->ShowWindow(SW_HIDE);;
		  GetDlgItem(IDC_COMBO_D)->ShowWindow(SW_HIDE);;
		  GetDlgItem(IDC_STATIC10)->ShowWindow(SW_HIDE);;
		  GetDlgItem(IDC_COMBO_D5)->ShowWindow(SW_HIDE);;
		  GetDlgItem(IDC_BUT_MUSIC)->ShowWindow(SW_HIDE);;
		  GetDlgItem(IDC_COMBO_D6)->ShowWindow(SW_HIDE);;
		  GetDlgItem(IDC_EDIT9)->ShowWindow(SW_HIDE);;
		  GetDlgItem(IDC_STATIC9)->ShowWindow(SW_HIDE);;
		  GetDlgItem(IDC_COMBO_D9)->ShowWindow(SW_HIDE);;
	}
    else if("changepoint" ==  strtable)
	{
    	  SetWindowText(_T("改变曲线点号"));
		  GetDlgItem(IDC_STATIC1)->SetWindowText("点号1");
		  GetDlgItem(IDC_STATIC2)->SetWindowText("点号2");
		  GetDlgItem(IDC_STATIC3)->SetWindowText("点号3");
		  GetDlgItem(IDC_STATIC4)->SetWindowText("点号4");
   		  GetDlgItem(IDC_EDIT1)->SetWindowText(str1);
   		  GetDlgItem(IDC_EDIT2)->SetWindowText(str2);
   		  GetDlgItem(IDC_EDIT3)->SetWindowText(str3);
   		  GetDlgItem(IDC_EDIT4)->SetWindowText(str4);
//		  GetDlgItem(IDC_STATIC5)->SetWindowText(m_ADTypeTable[0].m_DTypeTFD.palmd);
//		  GetDlgItem(IDC_STATIC6)->SetWindowText(m_ADTypeTable[0].m_DTypeTFD.pbrk);
		  GetDlgItem(IDC_COMBO_D)->ShowWindow(SW_HIDE);;
		  GetDlgItem(IDC_STATIC10)->ShowWindow(SW_HIDE);;
		  GetDlgItem(IDC_COMBO_D5)->ShowWindow(SW_HIDE);;
		  GetDlgItem(IDC_COMBO_D6)->ShowWindow(SW_HIDE);;
		  GetDlgItem(IDC_STATIC6)->ShowWindow(SW_HIDE);;
		  GetDlgItem(IDC_STATIC5)->ShowWindow(SW_HIDE);;
		  GetDlgItem(IDC_EDIT6)->ShowWindow(SW_HIDE);;
		  GetDlgItem(IDC_EDIT5)->ShowWindow(SW_HIDE);;
		  GetDlgItem(IDC_EDIT8)->ShowWindow(SW_HIDE);;
		  GetDlgItem(IDC_STATIC8)->ShowWindow(SW_HIDE);;
		  GetDlgItem(IDC_EDIT_PATH)->ShowWindow(SW_HIDE);;
		  GetDlgItem(IDC_STATIC7)->ShowWindow(SW_HIDE);;
		  GetDlgItem(IDC_BUT_MUSIC)->ShowWindow(SW_HIDE);;
		  GetDlgItem(IDC_EDIT9)->ShowWindow(SW_HIDE);;
		  GetDlgItem(IDC_STATIC9)->ShowWindow(SW_HIDE);;
		  GetDlgItem(IDC_COMBO_D9)->ShowWindow(SW_HIDE);;
	}
  }

  return TRUE;  // return TRUE unless you set the focus to a control
  // EXCEPTION: OCX Property Pages should return FALSE
}

//KillFocus allows the application to check for any duplicate
//records before an attempt is made to actually add the record
//to the database and possibly get an exception thrown by the
//data provider
void CAccountDlg::OnKillFocusAccntId()
{
  //If we are adding a new account, check to see if
  //an existing record already exists.
/*  if ( !m_bEditMode )
  {
    CString szAccntID;
    GetDlgItemText(IDC_ACCNT_ID, szAccntID);

    if ( GetFocus() != GetDlgItem(IDC_CANCEL) && szAccntID.IsEmpty() )
    {
      if ( !szAccntID.IsEmpty() )
      {
        CString szFind;
        szFind.Format(_T("AccountID = '%s'"), szAccntID);
        if ( m_pAccountSet->Find(szFind) )
        {
          AfxMessageBox(_T("Account already exists."), MB_OK);
          GetDlgItem(IDC_ACCNT_ID)->SetFocus();
        }
      }
      else
      {
        AfxMessageBox(_T("Account ID is required"), MB_OK);
        GetDlgItem(IDC_ACCNT_ID)->SetFocus();
      }
    }
  }*/
}

//Add a new record or Update and existing record's info
void CAccountDlg::OnBnClickedOk()
{
  try
  {
	 CString strItem,strab;     strab=strItem ="";
   	if(m_ADTypeTable[1].TableName ==  strtable)  //开关量
    {
			COleDateTime CTime;
			UpdateData(TRUE);           //Exchange dialog data
		  m_pAccountSet->m_szName = str1;
		  if(str1 == "")
		  {
              AfxMessageBox(m_ADTypeTable[1].m_DTypeTFD.Name+"不能为空，请重新输入", MB_OK);
			  return;
		  }

//        if((m_ComBoxD.GetCurSel() == 3)||(m_ComBoxD.GetCurSel() == 0)||(m_ComBoxD.GetCurSel() == 4)||(m_ComBoxD.GetCurSel() == 2)||(m_ComBoxD.GetCurSel() == 1))

		  m_pAccountSet->m_szname0 = str2;
		  if(str2 == "")
		  {
              AfxMessageBox(m_ADTypeTable[1].m_DTypeTFD.name0+"不能为空，请重新输入", MB_OK);
			  return;
		  }
		  m_pAccountSet->m_szname1 = str3;
		  if(str3 == "")
		  {
              AfxMessageBox(m_ADTypeTable[1].m_DTypeTFD.name1+"不能为空，请重新输入", MB_OK);
			  return;
		  }
		  int D5 = m_ComBoxD5.GetCurSel();
		  int D6 = m_ComBoxD6.GetCurSel();
		  if((D5==0)&&(D6==0))  //不报警
		  {
			  strab ="不报警,不断电";
    		  m_pAccountSet->m_szpalms = 0;
    		  m_pAccountSet->m_szfalm = "";  //报警音乐
		  }
		  else if(D6 ==0)
		  {
			  if(D5 == 1)              strab ="0态报警";
			  else if(D5 == 2)         strab ="1态报警";
    		  m_pAccountSet->m_szpalms = D5;
    		  m_pAccountSet->m_szfalm = str7;  //报警音乐
    		  if(str7 == "")
			  {
              AfxMessageBox(m_ADTypeTable[1].m_DTypeTFD.falm+"不能为空，请重新输入", MB_OK);
			  return;
			  }
		  }
		  else if(D5 ==0)
		  {   
			  if(D6 == 1)              strab ="0态断电";
			  else if(D6 == 2)         strab ="1态断电";
    		  m_pAccountSet->m_szpalms = D6 +2;
    		  m_pAccountSet->m_szfalm = str7;
    		  if(str7 == "")
			  {
              AfxMessageBox(m_ADTypeTable[1].m_DTypeTFD.falm+"不能为空，请重新输入", MB_OK);
			  return;
			  }
		  }
          if(m_ComBoxD.GetCurSel() == 2)//控制量
		  {
			  int D9 = m_ComBoxD9.GetCurSel();
			  if(D9 == 0)              strab ="常开";
			  else if(D9 == 1)         strab ="常闭";
			  else if(D9 == 2)         strab ="电平";
    		  m_pAccountSet->m_szpalms = 5 + D9;
		  }

		  if(m_ComBoxD.GetCurSel() == 3)//三态
		  {
    		  m_pAccountSet->m_szname2 = str4;
    		  if(str4 == "")
			  {
              AfxMessageBox(m_ADTypeTable[1].m_DTypeTFD.name2+"不能为空，请重新输入", MB_OK);
			  return;
			  }
		  }
		  else
    		  m_pAccountSet->m_szname2 = "";

		  m_pAccountSet->m_szptype = m_ComBoxD.GetCurSel();
		  m_pAccountSet->m_szrecdate = CTime.GetCurrentTime();
		  m_pAccountSet->m_szUseridadd = theApp.curuser;
		  if((D5==0)&&(D6==0))  //不报警
		strItem =str1 +" 0态:" +str2 +" 1态:"+str3 +" 2态:"+str4 +" 报警类型、状态:"+strab +"||"+ theApp.curuser;
		  else
		strItem =str1 +" 0态:" +str2 +" 1态:"+str3 +" 2态:"+str4 +" 报警类型、状态:"+strab+" 报警音乐:"+str7 +"||"+ theApp.curuser;
          if(m_ComBoxD.GetCurSel() == 2)//控制量
		strItem =str1 +" 0态:" +str2 +" 1态:"+str3 +" 2态:"+str4 +" 控制量类型:"+strab +"||"+ theApp.curuser;

			if ( !m_bEditMode )
			{
      g_Log.StatusOut("增加开关量类型：" + strItem );
			  m_pAccountSet->m_szDID = acdid;
			  m_pAccountSet->AddNew();  //Add a new, blank record  theApp
			}
			else
      g_Log.StatusOut("修改开关量类型：" + strItem );
			m_pAccountSet->Update();    //Update the recordset
			//If this is a new record, requery the database table
			//otherwise we may out-of-sync
			if ( !m_bEditMode )
			  m_pAccountSet->Requery();
	}
	else if(m_ADTypeTable[0].TableName ==  strtable)   //模拟量
	{
			COleDateTime CTime;
		UpdateData(TRUE);           //Exchange dialog data
		  if(str1 == "")
		  {
              AfxMessageBox("名字不能为空，请重新输入", MB_OK);
			  return;
		  }
		  if(fstr9>fstr6)
		  {
              AfxMessageBox("复电值不能大于断电值，请重新输入", MB_OK);
			  return;
		  }
		  if(fstr6>fstr2)
		  {
              AfxMessageBox("断电值不能大于量程高值，请重新输入", MB_OK);
			  return;
		  }
		  if(fstr6<fstr4)
		  {
              AfxMessageBox("报警上限不能大于断电值，请重新输入", MB_OK);
			  return;
		  }
		  if(str8 == "")
		  {
              AfxMessageBox("单位不能为空，请重新输入", MB_OK);
			  return;
		  }
		  if(str7 == "")
		  {
              AfxMessageBox("报警音乐不能为空，请重新输入", MB_OK);
			  return;
		  }
		  if(fstr9<0.001)
		  {
              AfxMessageBox("复电值不能为零，请重新输入", MB_OK);
			  return;
		  }
		  m_pContactSet->m_szName = str1;
		  m_pContactSet->m_szltop = fstr2;
		  strab.Format(" 量程高值：%.2f",fstr2);
		  strItem += strab;
		  m_pContactSet->m_szlbom = fstr3;
		  strab.Format(" 量程低值：%.2f",fstr3);
		  strItem += strab;
		  m_pContactSet->m_szpalmu = fstr4;
		  strab.Format(" 报警上限：%.2f",fstr4);
		  strItem += strab;
		  m_pContactSet->m_szpalmd = fstr5;
		  strab.Format(" 报警下限：%.2f",fstr5);
		  strItem += strab;
		  m_pContactSet->m_szpbrk = fstr6;
		  strab.Format(" 断电值：%.2f",fstr6);
		  strItem += strab;
		  m_pContactSet->m_szprtn = fstr9;
		  strab.Format(" 复电值：%.2f",fstr9);
		  strItem += strab;
		  m_pContactSet->m_szrecdate = CTime.GetCurrentTime();
		  m_pContactSet->m_szpunit = str8;
		  m_pContactSet->m_szfalm = str7;
		  m_pContactSet->m_szUseridadd = theApp.curuser;
		strItem =str1 +strItem+" 单位：" +str8 +" 报警音乐：" +str7 + "||" +theApp.curuser;

		if ( !m_bEditMode )
		{
      g_Log.StatusOut("增加模拟量类型：" + strItem );
//		  m_pContactSet->m_szAID = acdid;
		  m_pContactSet->AddNew();  //Add a new, blank record
		}
		else
      g_Log.StatusOut("修改模拟量类型：" + strItem );
		m_pContactSet->Update();    //Update the recordset
		//If this is a new record, requery the database table
		//otherwise we may out-of-sync
		if ( !m_bEditMode )
		  m_pContactSet->Requery();
	}
	else if(m_ADTypeTable[2].TableName ==  strtable)   //安装地点
	{
    	CMainFrame* pFWnd=(CMainFrame*)AfxGetMainWnd();
   		UpdateData(TRUE);           //Exchange dialog data
		if ( !m_bEditMode )
         	pFWnd->m_pSetHostDlg->SetFocus();
        for ( int i = 0; i < theApp.m_Lstr.size(); i++)//安装地点
		{
		    	if(str1 == theApp.m_Lstr[i])
				{
                AfxMessageBox("安装地点名称已存在，请重新输入！", MB_OK);
		    	return;
				}
		}

//		CWnd* pWnd=GetDlgItem(IDD_DIALOG_HOST_SETTING);
		if ( !m_bEditMode )
		{
    		  pFWnd->m_pSetHostDlg->m_MAlocation.m_szlocationID = acdid;
    		  pFWnd->m_pSetHostDlg->m_MAlocation.AddNew();
//    		  m_pMAlocation->AddNew();  //Add a new, blank record
    		  pFWnd->m_pSetHostDlg->m_MAlocation.m_szName = str1;
       		pFWnd->m_pSetHostDlg->m_MAlocation.Update();    //Update the recordset
    		acdid++;
		}
		else
		{
    		  m_pMAlocation->m_szName = acdid;
    		  m_pMAlocation->m_szName = str1;
       		  m_pMAlocation->Update();    //Update the recordset
		}
				  strItem =str1 +"||" + theApp.curuser;

		//If this is a new record, requery the database table
		//otherwise we may out-of-sync
		if ( !m_bEditMode )
		{
    		  pFWnd->m_pSetHostDlg->m_MAlocation.Requery();
            g_Log.StatusOut("增加安装地点：" + strItem );
		}
		else
           g_Log.StatusOut("修改安装地点：" + strItem );

		if (m_bEditMode )
		{
             MessageBeep(MB_OK);
             EndDialog(IDOK);
		}
       		theApp.InitData();
			pFWnd->m_pSetHostDlg->BuildAccountList();
	}
    else if("changepoint" ==  strtable)
	{
		UpdateData(TRUE);           //Exchange dialog data
	}
  }
  catch (CAxException *e)
  {
    AfxMessageBox(e->m_szErrorDesc, MB_OK);
    delete e;
  }

  if(m_ADTypeTable[2].TableName !=  strtable)
  {
     MessageBeep(MB_OK);
     EndDialog(IDOK);
  }
//  else
//	  ((CSettingHostDlg*) m_pParent)->PointDesid =100;

}

void CAccountDlg::OnBnClickedCancel()
{
    	CMainFrame* pFWnd=(CMainFrame*)AfxGetMainWnd();
/*  if(m_ADTypeTable[2].TableName ==  strtable)
  {
	  pFWnd->m_pSetHostDlg->m_bADD = false;
	   DestroyWindow(); //销毁对话框 
  }
  else*/
  if("changepoint" !=  strtable)
	  pFWnd->m_pSetHostDlg->m_bADD = false;
       EndDialog(IDCANCEL);
}

void CAccountDlg::OnchangeComboD() 
{
//	m_ComBoxD.GetWindowText(m_strsel);
	if(m_ComBoxD.GetCurSel() == 3)
	{
			  m_ComBoxD5.SetCurSel(0);
              GetDlgItem(IDC_COMBO_D5)->EnableWindow(TRUE);
		  GetDlgItem(IDC_EDIT2)->ShowWindow(SW_SHOW);
		  GetDlgItem(IDC_STATIC2)->ShowWindow(SW_SHOW);
		  GetDlgItem(IDC_EDIT3)->ShowWindow(SW_SHOW);
		  GetDlgItem(IDC_STATIC3)->ShowWindow(SW_SHOW);
		  GetDlgItem(IDC_EDIT4)->ShowWindow(SW_SHOW);
		  GetDlgItem(IDC_STATIC4)->ShowWindow(SW_SHOW);
		  GetDlgItem(IDC_STATIC5)->ShowWindow(SW_SHOW);
		  GetDlgItem(IDC_COMBO_D5)->ShowWindow(SW_SHOW);
		  GetDlgItem(IDC_STATIC6)->ShowWindow(SW_SHOW);;
		  GetDlgItem(IDC_COMBO_D6)->ShowWindow(SW_SHOW);
		  GetDlgItem(IDC_COMBO_D9)->ShowWindow(SW_HIDE);;
		  GetDlgItem(IDC_STATIC9)->ShowWindow(SW_HIDE);;
        		GetDlgItem(IDC_EDIT_PATH)->ShowWindow(SW_HIDE);;
        		GetDlgItem(IDC_STATIC7)->ShowWindow(SW_HIDE);;
        		GetDlgItem(IDC_BUT_MUSIC)->ShowWindow(SW_HIDE);;
	}
	else if(m_ComBoxD.GetCurSel() == 2)
	{
			  m_ComBoxD5.SetCurSel(0);
              GetDlgItem(IDC_COMBO_D5)->EnableWindow(TRUE);
		  GetDlgItem(IDC_EDIT4)->ShowWindow(SW_HIDE);
		  GetDlgItem(IDC_STATIC4)->ShowWindow(SW_HIDE);
		  GetDlgItem(IDC_STATIC9)->ShowWindow(SW_SHOW);
		  GetDlgItem(IDC_COMBO_D9)->ShowWindow(SW_SHOW);
        		GetDlgItem(IDC_EDIT_PATH)->ShowWindow(SW_HIDE);;
        		GetDlgItem(IDC_STATIC7)->ShowWindow(SW_HIDE);;
        		GetDlgItem(IDC_BUT_MUSIC)->ShowWindow(SW_HIDE);;
		  GetDlgItem(IDC_STATIC5)->ShowWindow(SW_HIDE);
		  GetDlgItem(IDC_COMBO_D5)->ShowWindow(SW_HIDE);
		  GetDlgItem(IDC_STATIC6)->ShowWindow(SW_HIDE);;
		  GetDlgItem(IDC_COMBO_D6)->ShowWindow(SW_HIDE);
	}
	else
	{
			  m_ComBoxD5.SetCurSel(0);
              GetDlgItem(IDC_COMBO_D5)->EnableWindow(TRUE);
		  GetDlgItem(IDC_EDIT2)->ShowWindow(SW_SHOW);
		  GetDlgItem(IDC_STATIC2)->ShowWindow(SW_SHOW);
		  GetDlgItem(IDC_EDIT3)->ShowWindow(SW_SHOW);
		  GetDlgItem(IDC_STATIC3)->ShowWindow(SW_SHOW);
		  GetDlgItem(IDC_STATIC5)->ShowWindow(SW_SHOW);
		  GetDlgItem(IDC_COMBO_D5)->ShowWindow(SW_SHOW);
		  GetDlgItem(IDC_STATIC6)->ShowWindow(SW_SHOW);;
		  GetDlgItem(IDC_COMBO_D6)->ShowWindow(SW_SHOW);

		  GetDlgItem(IDC_EDIT4)->ShowWindow(SW_HIDE);
		  GetDlgItem(IDC_STATIC4)->ShowWindow(SW_HIDE);
		  GetDlgItem(IDC_COMBO_D9)->ShowWindow(SW_HIDE);
		  GetDlgItem(IDC_STATIC9)->ShowWindow(SW_HIDE);
        		GetDlgItem(IDC_EDIT_PATH)->ShowWindow(SW_HIDE);;
        		GetDlgItem(IDC_STATIC7)->ShowWindow(SW_HIDE);;
        		GetDlgItem(IDC_BUT_MUSIC)->ShowWindow(SW_HIDE);;
		  if(m_ComBoxD.GetCurSel() == 1)
		  {
			  m_ComBoxD5.SetCurSel(2);
              GetDlgItem(IDC_COMBO_D5)->EnableWindow(FALSE);
    		  GetDlgItem(IDC_STATIC6)->ShowWindow(SW_HIDE);;
    		  GetDlgItem(IDC_COMBO_D6)->ShowWindow(SW_HIDE);
        		GetDlgItem(IDC_EDIT_PATH)->ShowWindow(SW_SHOW);;
        		GetDlgItem(IDC_STATIC7)->ShowWindow(SW_SHOW);;
        		GetDlgItem(IDC_BUT_MUSIC)->ShowWindow(SW_SHOW);;
		  }
	}
}

void CAccountDlg::OnchangeComboD5() 
{
	if(m_ComBoxD5.GetCurSel() == 0)
	{
        		GetDlgItem(IDC_EDIT_PATH)->ShowWindow(SW_HIDE);;
        		GetDlgItem(IDC_STATIC7)->ShowWindow(SW_HIDE);;
        		GetDlgItem(IDC_BUT_MUSIC)->ShowWindow(SW_HIDE);;
		  GetDlgItem(IDC_STATIC6)->ShowWindow(SW_SHOW);;
		  GetDlgItem(IDC_COMBO_D6)->ShowWindow(SW_SHOW);
	}
	else
	{
		  GetDlgItem(IDC_STATIC6)->ShowWindow(SW_HIDE);;
		  GetDlgItem(IDC_COMBO_D6)->ShowWindow(SW_HIDE);
        		GetDlgItem(IDC_EDIT_PATH)->ShowWindow(SW_SHOW);;
        		GetDlgItem(IDC_STATIC7)->ShowWindow(SW_SHOW);;
        		GetDlgItem(IDC_BUT_MUSIC)->ShowWindow(SW_SHOW);;
	}
}

void CAccountDlg::OnchangeComboD6() 
{
	if(m_ComBoxD6.GetCurSel() == 0)
	{
        		GetDlgItem(IDC_EDIT_PATH)->ShowWindow(SW_HIDE);;
        		GetDlgItem(IDC_STATIC7)->ShowWindow(SW_HIDE);;
        		GetDlgItem(IDC_BUT_MUSIC)->ShowWindow(SW_HIDE);;
		  GetDlgItem(IDC_STATIC5)->ShowWindow(SW_SHOW);
		  GetDlgItem(IDC_COMBO_D5)->ShowWindow(SW_SHOW);
	}
	else
	{
		  GetDlgItem(IDC_STATIC5)->ShowWindow(SW_HIDE);
		  GetDlgItem(IDC_COMBO_D5)->ShowWindow(SW_HIDE);
        		GetDlgItem(IDC_EDIT_PATH)->ShowWindow(SW_SHOW);;
        		GetDlgItem(IDC_STATIC7)->ShowWindow(SW_SHOW);;
        		GetDlgItem(IDC_BUT_MUSIC)->ShowWindow(SW_SHOW);;
	}
}

void CAccountDlg::OnMusicPath() 
{
		UpdateData(TRUE);
//	char filter[] = "音乐文件(*.wav,*.mp3,*.mid)|*.wav;*.mp3;*.mid|所有文件(*.*)|*.*||";
	char filter[] = "音乐文件(*.wav,*.mp3,*.mid)|*.wav;*.mp3;*.mid|";
	CFileDialog filedlg(TRUE,NULL,NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,filter,NULL);
	if(filedlg.DoModal() == IDOK)
	{
        CString strmid;
		str7 = filedlg.GetPathName();
		strmid = str7.Right(4);
		if(strmid == ".wav" ||strmid == ".mp3" ||strmid == ".mid")
    		str7 = filedlg.GetPathName();
		else
		{
    		str7 = "";
              AfxMessageBox("报警音乐文件格式不正确，请重新输入", MB_OK);
		}
		UpdateData(FALSE);
	}
}

void CAccountDlg::OnChE() 
{
	UpdateData(TRUE);
	UpdateData(FALSE);
}