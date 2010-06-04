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
		  DDX_Text(pDX, IDC_EDIT1, str1);
		  DDX_Text(pDX, IDC_EDIT2, str2);
		  DDX_Text(pDX, IDC_EDIT3, str3);
		  DDX_Text(pDX, IDC_EDIT4, str4);
		  DDX_Text(pDX, IDC_EDIT5, str5);
		  DDX_Text(pDX, IDC_EDIT6, str6);
		  DDX_Text(pDX, IDC_EDIT7, str7);
		  DDX_Text(pDX, IDC_EDIT8, str8);
		  DDX_Text(pDX, IDC_EDIT9, str9);
/*  DDX_Text(pDX, IDC_EDIT1, m_pAccountSet->m_szName);
  DDX_Text(pDX, IDC_EDIT2, m_pAccountSet->m_szname0);
  DDX_Text(pDX, IDC_EDIT3, m_pAccountSet->m_szname1);
  DDX_Text(pDX, IDC_EDIT4, m_pAccountSet->m_szname2);
  DDX_Text(pDX, IDC_EDIT5, m_pAccountSet->m_szpalms);
  DDX_Text(pDX, IDC_EDIT6, m_pAccountSet->m_szptype);
  DDX_Text(pDX, IDC_EDIT7, m_pAccountSet->m_szfalm);*/
}

BEGIN_MESSAGE_MAP(CAccountDlg, CDialog)
  ON_BN_CLICKED(IDOK, OnBnClickedOk)
  ON_BN_CLICKED(IDCANCEL, OnBnClickedCancel)
//  ON_EN_KILLFOCUS(IDC_ACCNT_ID, OnKillFocusAccntId)
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

  //If we are editing the record, disable the AccountID edit box
  if ( m_bEditMode )
  {
	  CString szFind;
//    GetDlgItem(IDC_ACCNT_ID)->EnableWindow(FALSE);
    if(m_ADTypeTable[1].TableName ==  strtable)
	{
    	SetWindowText(_T(m_ADTypeTable[1].NameD));
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
		  szFind.Format("%d",m_pAccountSet->m_szpalms);
//			szFind.TrimRight();
		  GetDlgItem(IDC_EDIT5)->SetWindowText(szFind);
			 szFind = m_pAccountSet->m_szptype;
			szFind.TrimRight();
		  GetDlgItem(IDC_EDIT6)->SetWindowText(szFind);
			 szFind = m_pAccountSet->m_szfalm;
			szFind.TrimRight();
		  GetDlgItem(IDC_EDIT7)->SetWindowText(szFind);
		  GetDlgItem(IDC_EDIT8)->ShowWindow(SW_HIDE);;
		  GetDlgItem(IDC_STATIC8)->ShowWindow(SW_HIDE);;
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
   		  GetDlgItem(IDC_EDIT7)->SetWindowText(szFind);
		  szFind = m_pContactSet->m_szpunit;
		  szFind.TrimRight();
   		  GetDlgItem(IDC_EDIT8)->SetWindowText(szFind);
		  GetDlgItem(IDC_STATIC2)->SetWindowText(m_ADTypeTable[0].m_DTypeTFD.ltop);
		  GetDlgItem(IDC_STATIC3)->SetWindowText(m_ADTypeTable[0].m_DTypeTFD.lbom);
		  GetDlgItem(IDC_STATIC4)->SetWindowText(m_ADTypeTable[0].m_DTypeTFD.palmu);
		  GetDlgItem(IDC_STATIC5)->SetWindowText(m_ADTypeTable[0].m_DTypeTFD.palmd);
		  GetDlgItem(IDC_STATIC6)->SetWindowText(m_ADTypeTable[0].m_DTypeTFD.pbrk);
		  GetDlgItem(IDC_STATIC7)->SetWindowText(m_ADTypeTable[0].m_DTypeTFD.prtn);
	}
    else if(m_ADTypeTable[2].TableName ==  strtable)
	{
    	SetWindowText(_T(m_ADTypeTable[2].NameD));
			szFind = m_pMAlocation->m_szName;
			szFind.TrimRight();
		  GetDlgItem(IDC_EDIT1)->SetWindowText(szFind);
		  GetDlgItem(IDC_EDIT8)->ShowWindow(SW_HIDE);;
		  GetDlgItem(IDC_STATIC8)->ShowWindow(SW_HIDE);;
		  GetDlgItem(IDC_EDIT7)->ShowWindow(SW_HIDE);;
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
	}

  }
  else
  {
    //If this is to be a new record, we need to clear all
    //edit fields in the dialog
    for ( int i = IDC_EDIT1; i <= IDC_EDIT7; i++ )
      SetDlgItemText(i, _T(""));
      SetDlgItemText(IDC_EDIT8, _T(""));
    if(m_ADTypeTable[1].TableName ==  strtable)
	{
    	SetWindowText(_T(m_ADTypeTable[1].NameD));
		  GetDlgItem(IDC_EDIT8)->ShowWindow(SW_HIDE);;
		  GetDlgItem(IDC_STATIC8)->ShowWindow(SW_HIDE);;
	}
	else if(m_ADTypeTable[0].TableName ==  strtable)
	{
    	SetWindowText(_T(m_ADTypeTable[0].NameD));
		  GetDlgItem(IDC_STATIC2)->SetWindowText(m_ADTypeTable[0].m_DTypeTFD.ltop);
		  GetDlgItem(IDC_STATIC3)->SetWindowText(m_ADTypeTable[0].m_DTypeTFD.lbom);
		  GetDlgItem(IDC_STATIC4)->SetWindowText(m_ADTypeTable[0].m_DTypeTFD.palmu);
		  GetDlgItem(IDC_STATIC5)->SetWindowText(m_ADTypeTable[0].m_DTypeTFD.palmd);
		  GetDlgItem(IDC_STATIC6)->SetWindowText(m_ADTypeTable[0].m_DTypeTFD.pbrk);
		  GetDlgItem(IDC_STATIC7)->SetWindowText(m_ADTypeTable[0].m_DTypeTFD.prtn);
	}
    else if(m_ADTypeTable[2].TableName ==  strtable)
	{
    	SetWindowText(_T(m_ADTypeTable[2].NameD));
		  GetDlgItem(IDC_EDIT8)->ShowWindow(SW_HIDE);;
		  GetDlgItem(IDC_STATIC8)->ShowWindow(SW_HIDE);;
		  GetDlgItem(IDC_EDIT7)->ShowWindow(SW_HIDE);;
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
   	if(m_ADTypeTable[1].TableName ==  strtable)
    {
			COleDateTime CTime;
//			CString strCTime;
//			strCTime.Format("%d-%d-%d %d:%d:%d",CTime.GetYear(),CTime.GetMonth(),CTime.GetDay(),CTime.GetHour(),CTime.GetMinute(),CTime.GetSecond());
	//		strNormalTime.Format("%d-%d-%d %d:%d:%d",NormalTime.GetYear(),NormalTime.GetMonth(),NormalTime.GetDay(),NormalTime.GetHour(),NormalTime.GetMinute(),NormalTime.GetSecond());
			if ( !m_bEditMode )
			{
			  m_pAccountSet->m_szDID = acdid;
			  m_pAccountSet->AddNew();  //Add a new, blank record
			}
			UpdateData(TRUE);           //Exchange dialog data

		  m_pAccountSet->m_szName = str1;
		  m_pAccountSet->m_szname0 = str2;
		  m_pAccountSet->m_szname1 = str3;
		  m_pAccountSet->m_szname2 = str4;
		  m_pAccountSet->m_szpalms = m_Str2Data.String2Int(str5);
		  m_pAccountSet->m_szptype = str6;
		  m_pAccountSet->m_szfalm = str7;
		  m_pAccountSet->m_szrecdate = CTime.GetCurrentTime();

			m_pAccountSet->Update();    //Update the recordset

			//If this is a new record, requery the database table
			//otherwise we may out-of-sync
			if ( !m_bEditMode )
			  m_pAccountSet->Requery();
	}
	else if(m_ADTypeTable[0].TableName ==  strtable)
	{
			COleDateTime CTime;
			CString strCTime;
			strCTime.Format("%d-%d-%d %d:%d:%d",CTime.GetYear(),CTime.GetMonth(),CTime.GetDay(),CTime.GetHour(),CTime.GetMinute(),CTime.GetSecond());
	//		strNormalTime.Format("%d-%d-%d %d:%d:%d",NormalTime.GetYear(),NormalTime.GetMonth(),NormalTime.GetDay(),NormalTime.GetHour(),NormalTime.GetMinute(),NormalTime.GetSecond());
		  m_pContactSet->m_szrecdate = CTime.GetCurrentTime();

		if ( !m_bEditMode )
		{
		  m_pContactSet->m_szAID = acdid;
		  m_pContactSet->AddNew();  //Add a new, blank record
		}
		UpdateData(TRUE);           //Exchange dialog data

		  m_pContactSet->m_szName = str1;
		  m_pContactSet->m_szltop = m_Str2Data.String2Double(str2);
		  m_pContactSet->m_szlbom = m_Str2Data.String2Double(str3);
		  m_pContactSet->m_szpalmu = m_Str2Data.String2Double(str4);
		  m_pContactSet->m_szpalmd = m_Str2Data.String2Double(str5);
		  m_pContactSet->m_szpbrk = m_Str2Data.String2Double(str6);
		  m_pContactSet->m_szprtn = m_Str2Data.String2Double(str7);
		  m_pContactSet->m_szrecdate = CTime.GetCurrentTime();
		  m_pContactSet->m_szpunit = str8;

		m_pContactSet->Update();    //Update the recordset

		//If this is a new record, requery the database table
		//otherwise we may out-of-sync
		if ( !m_bEditMode )
		  m_pContactSet->Requery();
	}
	else if(m_ADTypeTable[2].TableName ==  strtable)
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
