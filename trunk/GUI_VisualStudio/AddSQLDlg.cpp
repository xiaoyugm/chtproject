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
  m_bEditMode = FALSE;    //����
  m_pAccountSet = NULL;
  m_pParent = pParent;
  m_pContactSet = NULL;
  m_pMAlocation = NULL;
  str1 ="";
  fstr9 =0;
  fstr2 =0;
  fstr3 =0;
  fstr4 =0;
  fstr5 =0;
  fstr6 =0;
}

CAccountDlg::CAccountDlg(BOOL bEditMode, CWnd* pParent /*=NULL*/)
	: CDialog(CAccountDlg::IDD, pParent)
{
  m_bEditMode = bEditMode;   //�޸ġ��༭ true
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

     if(m_ADTypeTable[0].TableName ==  strtable)   //ģ����
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
     if(m_ADTypeTable[1].TableName ==  strtable)//������
         m_pAccountSet = &((CSettingHostDlg*) m_pParent)->m_AccountSet;
	 else if(m_ADTypeTable[0].TableName ==  strtable)   //ģ����
          m_pContactSet = &((CSettingHostDlg*) m_pParent)->m_ContactSet;
	 else if(m_ADTypeTable[2].TableName ==  strtable)    //��װ�ص�
          m_pMAlocation = &((CSettingHostDlg*) m_pParent)->m_MAlocation;

  CDialog::OnInitDialog();

        m_ComBoxD.AddString("��̬������");     //0  ptype
        m_ComBoxD.AddString("��վ");           //1
        m_ComBoxD.AddString("������");         //2
        m_ComBoxD.AddString("��̬������");     //3
        m_ComBoxD.AddString("ͨ����");         //4
		m_ComBoxD.SetCurSel(0);
		//m_pAccountSet->m_szpalms
        m_ComBoxD9.AddString("����");           //5  ������
        m_ComBoxD9.AddString("����");           //6
        m_ComBoxD9.AddString("��ƽ");           //7
		m_ComBoxD9.SetCurSel(0);
        m_ComBoxD5.AddString("������");         //0  
        m_ComBoxD5.AddString("0̬����");        //1
        m_ComBoxD5.AddString("1̬����");        //2
		m_ComBoxD5.SetCurSel(0);
        m_ComBoxD6.AddString("���ϵ�");         //0  
        m_ComBoxD6.AddString("0̬�ϵ�");        //3
        m_ComBoxD6.AddString("1̬�ϵ�");        //4
		m_ComBoxD6.SetCurSel(0);

  //If we are editing the record, disable the AccountID edit box
  if ( m_bEditMode )   //�޸ġ��༭ true
  {
	  CString szFind;
//    GetDlgItem(IDC_ACCNT_ID)->EnableWindow(FALSE);
    if(m_ADTypeTable[1].TableName ==  strtable)//������
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

		  if((m_ComBoxD.GetCurSel() == 0) || (m_ComBoxD.GetCurSel() == 4)||(m_ComBoxD.GetCurSel() == 1))  //��̬������ ͨ���� ��վ
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
		  else if(m_ComBoxD.GetCurSel() == 3)     //��̬������
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
		  else if(m_ComBoxD.GetCurSel() == 2)     //���ƿ�����
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
		  GetDlgItem(IDC_STATIC9)->SetWindowText("����������");
	}
	else if(m_ADTypeTable[0].TableName ==  strtable)   //ģ����
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
    else if(m_ADTypeTable[2].TableName ==  strtable)    //��װ�ص�
	{
    	SetWindowText("�޸İ�װ�ص�");
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
  else    //����
  {
    //If this is to be a new record, we need to clear all
    //edit fields in the dialog   IDC_CHECKDALM
    if(m_ADTypeTable[1].TableName ==  strtable)//������
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
		  GetDlgItem(IDC_STATIC9)->SetWindowText("����������");
        		GetDlgItem(IDC_EDIT_PATH)->ShowWindow(SW_HIDE);;
        		GetDlgItem(IDC_STATIC7)->ShowWindow(SW_HIDE);;
        		GetDlgItem(IDC_BUT_MUSIC)->ShowWindow(SW_HIDE);;
	}
	else if(m_ADTypeTable[0].TableName ==  strtable)     //ģ����
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
    else if(m_ADTypeTable[2].TableName ==  strtable)     //��װ�ص�
	{
    	SetWindowText("��Ӱ�װ�ص�");
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
    	  SetWindowText(_T("�ı����ߵ��"));
		  GetDlgItem(IDC_STATIC1)->SetWindowText("���1");
		  GetDlgItem(IDC_STATIC2)->SetWindowText("���2");
		  GetDlgItem(IDC_STATIC3)->SetWindowText("���3");
		  GetDlgItem(IDC_STATIC4)->SetWindowText("���4");
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
   	if(m_ADTypeTable[1].TableName ==  strtable)  //������
    {
			COleDateTime CTime;
			UpdateData(TRUE);           //Exchange dialog data
		  m_pAccountSet->m_szName = str1;
		  if(str1 == "")
		  {
              AfxMessageBox(m_ADTypeTable[1].m_DTypeTFD.Name+"����Ϊ�գ�����������", MB_OK);
			  return;
		  }

//        if((m_ComBoxD.GetCurSel() == 3)||(m_ComBoxD.GetCurSel() == 0)||(m_ComBoxD.GetCurSel() == 4)||(m_ComBoxD.GetCurSel() == 2)||(m_ComBoxD.GetCurSel() == 1))

		  m_pAccountSet->m_szname0 = str2;
		  if(str2 == "")
		  {
              AfxMessageBox(m_ADTypeTable[1].m_DTypeTFD.name0+"����Ϊ�գ�����������", MB_OK);
			  return;
		  }
		  m_pAccountSet->m_szname1 = str3;
		  if(str3 == "")
		  {
              AfxMessageBox(m_ADTypeTable[1].m_DTypeTFD.name1+"����Ϊ�գ�����������", MB_OK);
			  return;
		  }
		  int D5 = m_ComBoxD5.GetCurSel();
		  int D6 = m_ComBoxD6.GetCurSel();
		  if((D5==0)&&(D6==0))  //������
    		  m_pAccountSet->m_szpalms = 0;
		  else if(D6 ==0)
		  {   
    		  m_pAccountSet->m_szpalms = D5;
    		  m_pAccountSet->m_szfalm = str7;  //��������
    		  if(str7 == "")
			  {
              AfxMessageBox(m_ADTypeTable[1].m_DTypeTFD.falm+"����Ϊ�գ�����������", MB_OK);
			  return;
			  }
		  }
		  else if(D5 ==0)
		  {   
    		  m_pAccountSet->m_szpalms = D6 +2;
    		  m_pAccountSet->m_szfalm = str7;
    		  if(str7 == "")
			  {
              AfxMessageBox(m_ADTypeTable[1].m_DTypeTFD.falm+"����Ϊ�գ�����������", MB_OK);
			  return;
			  }
		  }
          if(m_ComBoxD.GetCurSel() == 2)//������
    		  m_pAccountSet->m_szpalms = 5 + m_ComBoxD9.GetCurSel();

		  if(m_ComBoxD.GetCurSel() == 3)//��̬
		  {
    		  m_pAccountSet->m_szname2 = str4;
    		  if(str4 == "")
			  {
              AfxMessageBox(m_ADTypeTable[1].m_DTypeTFD.name2+"����Ϊ�գ�����������", MB_OK);
			  return;
			  }
		  }

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
	else if(m_ADTypeTable[0].TableName ==  strtable)   //ģ����
	{
			COleDateTime CTime;
		UpdateData(TRUE);           //Exchange dialog data
		  if(str1 == "")
		  {
              AfxMessageBox("���ֲ���Ϊ�գ�����������", MB_OK);
			  return;
		  }
		  if(fstr9>fstr6)
		  {
              AfxMessageBox("����ֵ���ܴ��ڶϵ�ֵ������������", MB_OK);
			  return;
		  }
		  if(fstr6>fstr2)
		  {
              AfxMessageBox("�ϵ�ֵ���ܴ������̸�ֵ������������", MB_OK);
			  return;
		  }
		  if(fstr6<fstr4)
		  {
              AfxMessageBox("�������޲��ܴ��ڶϵ�ֵ������������", MB_OK);
			  return;
		  }
		  if(str8 == "")
		  {
              AfxMessageBox("��λ����Ϊ�գ�����������", MB_OK);
			  return;
		  }
		  if(str7 == "")
		  {
              AfxMessageBox("�������ֲ���Ϊ�գ�����������", MB_OK);
			  return;
		  }
		  if(fstr9<0.001)
		  {
              AfxMessageBox("����ֵ����Ϊ�㣬����������", MB_OK);
			  return;
		  }
		  m_pContactSet->m_szName = str1;
		  m_pContactSet->m_szltop = fstr2;
		  m_pContactSet->m_szlbom = fstr3;
		  m_pContactSet->m_szpalmu = fstr4;
		  m_pContactSet->m_szpalmd = fstr5;
		  m_pContactSet->m_szpbrk = fstr6;
		  m_pContactSet->m_szprtn = fstr9;
		  m_pContactSet->m_szrecdate = CTime.GetCurrentTime();
		  m_pContactSet->m_szpunit = str8;
		  m_pContactSet->m_szfalm = str7;
		  m_pContactSet->m_szUseridadd = theApp.curuser;

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
	else if(m_ADTypeTable[2].TableName ==  strtable)   //��װ�ص�
	{
    	CMainFrame* pFWnd=(CMainFrame*)AfxGetMainWnd();
    	pFWnd->m_pSetHostDlg->SetFocus();
//		CWnd* pWnd=GetDlgItem(IDD_DIALOG_HOST_SETTING);
		if ( !m_bEditMode )
		{
    		  pFWnd->m_pSetHostDlg->m_MAlocation.m_szlocationID = acdid;
    		  pFWnd->m_pSetHostDlg->m_MAlocation.AddNew();
//    		  m_pMAlocation->AddNew();  //Add a new, blank record
		}
		UpdateData(TRUE);           //Exchange dialog data
		  pFWnd->m_pSetHostDlg->m_MAlocation.m_szName = str1;
		pFWnd->m_pSetHostDlg->m_MAlocation.Update();    //Update the recordset

		//If this is a new record, requery the database table
		//otherwise we may out-of-sync
		if ( !m_bEditMode )
    		  pFWnd->m_pSetHostDlg->m_MAlocation.Requery();
		acdid++;

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
	   DestroyWindow(); //���ٶԻ��� 
  }
  else*/
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
//	char filter[] = "�����ļ�(*.wav,*.mp3,*.mid)|*.wav;*.mp3;*.mid|�����ļ�(*.*)|*.*||";
	char filter[] = "�����ļ�(*.wav,*.mp3,*.mid)|*.wav;*.mp3;*.mid|";
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
              AfxMessageBox("���������ļ���ʽ����ȷ������������", MB_OK);
		}
		UpdateData(FALSE);
	}
}

void CAccountDlg::OnChE() 
{
	UpdateData(TRUE);
	UpdateData(FALSE);
}