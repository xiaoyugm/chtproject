// AccountDlg.cpp : implementation file
//

#include "stdafx.h"
#include "GUI_VisualStudio.h"
#include "AddSQLDlg.h"

#include "SettingHostDlg.h"

extern  ADTypeTable	     m_ADTypeTable[9];
// CAccountDlg dialog

IMPLEMENT_DYNAMIC(CAccountDlg, CDialog)

CAccountDlg::CAccountDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAccountDlg::IDD, pParent)
{
  m_bEditMode = FALSE;
  m_pAccountSet = NULL;
  m_pParent = pParent;
  m_pContactSet = NULL;
  m_pMAlocation = NULL;
}

CAccountDlg::CAccountDlg(BOOL bEditMode, CWnd* pParent /*=NULL*/)
	: CDialog(CAccountDlg::IDD, pParent)
{
  m_bEditMode = bEditMode;
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
		  DDX_Text(pDX, IDC_EDIT2, str2);
		  DDX_Text(pDX, IDC_EDIT3, str3);
		  DDX_Text(pDX, IDC_EDIT4, str4);
		  DDX_Text(pDX, IDC_EDIT5, str5);
		  DDX_Text(pDX, IDC_EDIT6, str6);
		  DDX_Text(pDX, IDC_EDIT8, str8);
		  DDX_Text(pDX, IDC_EDIT9, str9);
		  DDX_Control(pDX, IDC_COMBO_D, m_ComBoxD);
	DDX_Control(pDX, IDC_BUT_MUSIC, m_ctlMusic);
	DDX_Control(pDX, IDC_CHECKISALM, m_ISAlm);
	DDX_Control(pDX, IDC_CHECKDALM, m_DAlm);
}

BEGIN_MESSAGE_MAP(CAccountDlg, CDialog)
  ON_BN_CLICKED(IDOK, OnBnClickedOk)
  ON_BN_CLICKED(IDCANCEL, OnBnClickedCancel)
//  ON_EN_KILLFOCUS(IDC_ACCNT_ID, OnKillFocusAccntId)
	ON_CBN_SELCHANGE(IDC_COMBO_D, OnchangeComboD)
	ON_BN_CLICKED(IDC_CHECKISALM, OnchangeISALM)
	ON_BN_CLICKED(IDC_BUT_MUSIC, OnMusicPath)
END_MESSAGE_MAP()


// CAccountDlg message handlers

BOOL CAccountDlg::OnInitDialog()
{
  //Set a pointer to the one instance of the CAxAccountSet
  //member of the main dialog
     if(m_ADTypeTable[1].TableName ==  strtable)
         m_pAccountSet = &((CSettingHostDlg*) m_pParent)->m_AccountSet;
	 else if(m_ADTypeTable[0].TableName ==  strtable)
          m_pContactSet = &((CSettingHostDlg*) m_pParent)->m_ContactSet;
	 else if(m_ADTypeTable[2].TableName ==  strtable)
          m_pMAlocation = &((CSettingHostDlg*) m_pParent)->m_MAlocation;

  CDialog::OnInitDialog();

        m_ComBoxD.AddString("二态开关量");     //0
        m_ComBoxD.AddString("分站");       //1
        m_ComBoxD.AddString("控制开关量");     //2
        m_ComBoxD.AddString("三态开关量");     //3
		m_ComBoxD.SetCurSel(0);

  //If we are editing the record, disable the AccountID edit box
  if ( m_bEditMode )
  {
	  CString szFind;
//    GetDlgItem(IDC_ACCNT_ID)->EnableWindow(FALSE);
    if(m_ADTypeTable[1].TableName ==  strtable)
	{
    	SetWindowText(_T(m_ADTypeTable[1].NameD));

		  m_ComBoxD.SetCurSel(m_pAccountSet->m_szptype);

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

		  if(m_ComBoxD.GetCurSel() < 3)
		  {
    		  GetDlgItem(IDC_EDIT4)->ShowWindow(SW_HIDE);
	    	  GetDlgItem(IDC_STATIC4)->ShowWindow(SW_HIDE);
		  }
		  if(m_pAccountSet->m_szpalms == 3)
		  {
        		m_ISAlm.SetCheck(0);
        		GetDlgItem(IDC_CHECKDALM)->ShowWindow(SW_HIDE);;
		  }
		  else
		  {
        		m_ISAlm.SetCheck(1);
        		m_DAlm.SetCheck(m_pAccountSet->m_szpalms);
		  }

			 szFind = m_pAccountSet->m_szfalm;
			szFind.TrimRight();
		  GetDlgItem(IDC_EDIT_PATH)->SetWindowText(szFind);

		  GetDlgItem(IDC_EDIT8)->ShowWindow(SW_HIDE);;
		  GetDlgItem(IDC_STATIC8)->ShowWindow(SW_HIDE);;
		  GetDlgItem(IDC_EDIT5)->ShowWindow(SW_HIDE);;
		  GetDlgItem(IDC_STATIC5)->ShowWindow(SW_HIDE);;
		  GetDlgItem(IDC_EDIT6)->ShowWindow(SW_HIDE);;
		  GetDlgItem(IDC_STATIC6)->ShowWindow(SW_HIDE);;
		  GetDlgItem(IDC_EDIT9)->ShowWindow(SW_HIDE);;
		  GetDlgItem(IDC_STATIC9)->ShowWindow(SW_HIDE);;
	}
	else if(m_ADTypeTable[0].TableName ==  strtable)
	{
    	SetWindowText(_T(m_ADTypeTable[0].NameD));
		  szFind = m_pContactSet->m_szName;
		  szFind.TrimRight();
   		  GetDlgItem(IDC_EDIT1)->SetWindowText(szFind);
				  szFind.Format("%.4f",m_pContactSet->m_szltop);
   		  GetDlgItem(IDC_EDIT2)->SetWindowText(szFind);
				  szFind.Format("%.4f",m_pContactSet->m_szlbom);
   		  GetDlgItem(IDC_EDIT3)->SetWindowText(szFind);
				  szFind.Format("%.4f",m_pContactSet->m_szpalmu);
   		  GetDlgItem(IDC_EDIT4)->SetWindowText(szFind);
				  szFind.Format("%.4f",m_pContactSet->m_szpalmd);
   		  GetDlgItem(IDC_EDIT5)->SetWindowText(szFind);
				  szFind.Format("%.4f",m_pContactSet->m_szpbrk);
   		  GetDlgItem(IDC_EDIT6)->SetWindowText(szFind);
				  szFind.Format("%.4f",m_pContactSet->m_szprtn);
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
		  GetDlgItem(IDC_CHECKDALM)->ShowWindow(SW_HIDE);;
		  GetDlgItem(IDC_CHECKISALM)->ShowWindow(SW_HIDE);;
	}
    else if(m_ADTypeTable[2].TableName ==  strtable)
	{
    	SetWindowText(_T(m_ADTypeTable[2].NameD));
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
		  GetDlgItem(IDC_CHECKDALM)->ShowWindow(SW_HIDE);;
		  GetDlgItem(IDC_BUT_MUSIC)->ShowWindow(SW_HIDE);;
		  GetDlgItem(IDC_CHECKISALM)->ShowWindow(SW_HIDE);;
		  GetDlgItem(IDC_EDIT9)->ShowWindow(SW_HIDE);;
		  GetDlgItem(IDC_STATIC9)->ShowWindow(SW_HIDE);;
	}
  }
  else
  {
    //If this is to be a new record, we need to clear all
    //edit fields in the dialog   IDC_CHECKDALM
    for ( int i = IDC_EDIT1; i <= IDC_EDIT6; i++ )
      SetDlgItemText(i, _T(""));
      SetDlgItemText(IDC_EDIT_PATH, _T(""));
      SetDlgItemText(IDC_EDIT8, _T(""));
      SetDlgItemText(IDC_EDIT9, _T(""));
    if(m_ADTypeTable[1].TableName ==  strtable)
	{
		m_ISAlm.SetCheck(1);
		m_DAlm.SetCheck(0);
    	SetWindowText(_T(m_ADTypeTable[1].NameD));
		  GetDlgItem(IDC_EDIT5)->ShowWindow(SW_HIDE);;
		  GetDlgItem(IDC_STATIC5)->ShowWindow(SW_HIDE);;
		  GetDlgItem(IDC_EDIT8)->ShowWindow(SW_HIDE);;
		  GetDlgItem(IDC_STATIC8)->ShowWindow(SW_HIDE);;
		  GetDlgItem(IDC_EDIT6)->ShowWindow(SW_HIDE);;
		  GetDlgItem(IDC_STATIC6)->ShowWindow(SW_HIDE);;
		  GetDlgItem(IDC_EDIT4)->ShowWindow(SW_HIDE);
		  GetDlgItem(IDC_STATIC4)->ShowWindow(SW_HIDE);
		  GetDlgItem(IDC_EDIT9)->ShowWindow(SW_HIDE);;
		  GetDlgItem(IDC_STATIC9)->ShowWindow(SW_HIDE);;
	}
	else if(m_ADTypeTable[0].TableName ==  strtable)
	{
    	SetWindowText(_T(m_ADTypeTable[0].NameD));
		  GetDlgItem(IDC_STATIC2)->SetWindowText(m_ADTypeTable[0].m_DTypeTFD.ltop);
		  GetDlgItem(IDC_STATIC3)->SetWindowText(m_ADTypeTable[0].m_DTypeTFD.lbom);
		  GetDlgItem(IDC_STATIC4)->SetWindowText(m_ADTypeTable[0].m_DTypeTFD.palmu);
		  GetDlgItem(IDC_STATIC5)->SetWindowText(m_ADTypeTable[0].m_DTypeTFD.palmd);
		  GetDlgItem(IDC_STATIC6)->SetWindowText(m_ADTypeTable[0].m_DTypeTFD.pbrk);
		  GetDlgItem(IDC_COMBO_D)->ShowWindow(SW_HIDE);;
		  GetDlgItem(IDC_STATIC10)->ShowWindow(SW_HIDE);;
		  GetDlgItem(IDC_CHECKDALM)->ShowWindow(SW_HIDE);;
		  GetDlgItem(IDC_CHECKISALM)->ShowWindow(SW_HIDE);;
	}
    else if(m_ADTypeTable[2].TableName ==  strtable)
	{
    	SetWindowText(_T(m_ADTypeTable[2].NameD));
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
		  GetDlgItem(IDC_CHECKDALM)->ShowWindow(SW_HIDE);;
		  GetDlgItem(IDC_BUT_MUSIC)->ShowWindow(SW_HIDE);;
		  GetDlgItem(IDC_CHECKISALM)->ShowWindow(SW_HIDE);;
		  GetDlgItem(IDC_EDIT9)->ShowWindow(SW_HIDE);;
		  GetDlgItem(IDC_STATIC9)->ShowWindow(SW_HIDE);;
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
   	if(m_ADTypeTable[1].TableName ==  strtable)  //开关量
    {
			COleDateTime CTime;
//			CString strCTime;
//			strCTime.Format("%d-%d-%d %d:%d:%d",CTime.GetYear(),CTime.GetMonth(),CTime.GetDay(),CTime.GetHour(),CTime.GetMinute(),CTime.GetSecond());
	//		strNormalTime.Format("%d-%d-%d %d:%d:%d",NormalTime.GetYear(),NormalTime.GetMonth(),NormalTime.GetDay(),NormalTime.GetHour(),NormalTime.GetMinute(),NormalTime.GetSecond());
			UpdateData(TRUE);           //Exchange dialog data
		  m_pAccountSet->m_szName = str1;
		  if(str1 == "")
		  {
              AfxMessageBox(m_ADTypeTable[1].m_DTypeTFD.Name+"不能为空，请重新输入", MB_OK);
			  return;
		  }
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
		  if(m_ComBoxD.GetCurSel() == 3)
		  {
    		  m_pAccountSet->m_szname2 = str4;
    		  if(str4 == "")
			  {
              AfxMessageBox(m_ADTypeTable[1].m_DTypeTFD.name2+"不能为空，请重新输入", MB_OK);
			  return;
			  }
		  }

		  if(m_ISAlm.GetCheck())
		  {
    		  m_pAccountSet->m_szpalms = m_DAlm.GetCheck();
    		  m_pAccountSet->m_szfalm = str7;
    		  if(str7 == "")
			  {
              AfxMessageBox(m_ADTypeTable[1].m_DTypeTFD.falm+"不能为空，请重新输入", MB_OK);
			  return;
			  }
		  }
		  else
    		  m_pAccountSet->m_szpalms = 3;
		  m_pAccountSet->m_szptype = m_ComBoxD.GetCurSel();
		  m_pAccountSet->m_szrecdate = CTime.GetCurrentTime();
		  m_pAccountSet->m_szUseridadd = theApp.curuser;

			if ( !m_bEditMode )
			{
			  m_pAccountSet->m_szDID = acdid;
			  m_pAccountSet->AddNew();  //Add a new, blank record  theApp
			}
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
		  m_pContactSet->m_szName = str1;
		  if(str1 == "")
		  {
              AfxMessageBox(m_ADTypeTable[0].m_DTypeTFD.Name+"不能为空，请重新输入", MB_OK);
			  return;
		  }
		  m_pContactSet->m_szltop = m_Str2Data.String2Double(str2);
		  m_pContactSet->m_szlbom = m_Str2Data.String2Double(str3);
		  m_pContactSet->m_szpalmu = m_Str2Data.String2Double(str4);
		  m_pContactSet->m_szpalmd = m_Str2Data.String2Double(str5);
		  m_pContactSet->m_szpbrk = m_Str2Data.String2Double(str6);
		  m_pContactSet->m_szprtn = m_Str2Data.String2Double(str9);
		  m_pContactSet->m_szrecdate = CTime.GetCurrentTime();
		  m_pContactSet->m_szpunit = str8;
		  m_pContactSet->m_szfalm = str7;
		  m_pContactSet->m_szUseridadd = theApp.curuser;
		  if(str8 == "")
		  {
              AfxMessageBox(m_ADTypeTable[0].m_DTypeTFD.punit+"不能为空，请重新输入", MB_OK);
			  return;
		  }
		  if(str7 == "")
		  {
              AfxMessageBox(m_ADTypeTable[0].m_DTypeTFD.falm+"不能为空，请重新输入", MB_OK);
			  return;
		  }

		if ( !m_bEditMode )
		{
//		  m_pContactSet->m_szAID = acdid;
		  m_pContactSet->AddNew();  //Add a new, blank record
		}
		m_pContactSet->Update();    //Update the recordset
		//If this is a new record, requery the database table
		//otherwise we may out-of-sync
		if ( !m_bEditMode )
		  m_pContactSet->Requery();
	}
	else if(m_ADTypeTable[2].TableName ==  strtable)   //安装地点
	{
		if ( !m_bEditMode )
		{
		  m_pMAlocation->m_szlocationID = acdid;
		  m_pMAlocation->AddNew();  //Add a new, blank record
		}
		UpdateData(TRUE);           //Exchange dialog data
		  m_pMAlocation->m_szName = str1;
		m_pMAlocation->Update();    //Update the recordset

		//If this is a new record, requery the database table
		//otherwise we may out-of-sync
		if ( !m_bEditMode )
		  m_pMAlocation->Requery();
	}

  }
  catch (CAxException *e)
  {
    AfxMessageBox(e->m_szErrorDesc, MB_OK);
    delete e;
  }

  MessageBeep(MB_OK);
  EndDialog(IDOK);
}

void CAccountDlg::OnBnClickedCancel()
{
  EndDialog(IDCANCEL);
}

void CAccountDlg::OnchangeISALM() 
{
	if(m_ISAlm.GetCheck())
		  GetDlgItem(IDC_CHECKDALM)->ShowWindow(SW_SHOW);
	else
		  GetDlgItem(IDC_CHECKDALM)->ShowWindow(SW_HIDE);
}

void CAccountDlg::OnchangeComboD() 
{
//	m_ComBoxD.GetWindowText(m_strsel);
	if(m_ComBoxD.GetCurSel() == 3)
	{
		  GetDlgItem(IDC_EDIT4)->ShowWindow(SW_SHOW);
		  GetDlgItem(IDC_STATIC4)->ShowWindow(SW_SHOW);
	}
	else
	{
		  GetDlgItem(IDC_EDIT4)->ShowWindow(SW_HIDE);
		  GetDlgItem(IDC_STATIC4)->ShowWindow(SW_HIDE);
	}
}

void CAccountDlg::OnMusicPath() 
{
		UpdateData(TRUE);
	char filter[] = "音乐文件(*.wav,*.mp3,*.mid)|*.wav;*.mp3;*.mid|所有文件(*.*)|*.*||";
	CFileDialog filedlg(TRUE,NULL,NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,filter,NULL);
	if(filedlg.DoModal() == IDOK)
	{
		str7 = filedlg.GetPathName();
		UpdateData(FALSE);
	}
}
