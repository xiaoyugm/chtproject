// SetTimeDlg.cpp : implementation file
//

#include "stdafx.h"
#include "GUI_VisualStudio.h"
#include "SetTimeDlg.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern SerialF               m_AFans[MAX_FDS][MAX_CHAN];    //˫�������ȱ��ȱ���
extern SerialF               m_SerialF[MAX_FDS];
ListV   str_list[6];         //�����˹����list
extern  CommonStr             m_CommonStr[20];
extern  ADCbreakE             m_ADCbreakE[MAX_FDS][MAX_CHAN][65];
extern  SlaveStation             m_SlaveStation[MAX_FDS][MAX_CHAN];
/////////////////////////////////////////////////////////////////////////////
// CSetTimeDlg dialog


CSetTimeDlg::CSetTimeDlg(CWnd* pParent /*=NULL*/)
	: CXTResizeDialog(CSetTimeDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSetTimeDlg)
    m_nSecond = 0;
	chcommand = 0x00;
	m_nchangev = 0;
	m_SControlNew = &m_SControl;
	m_nchange=0;
	//}}AFX_DATA_INIT
}


void CSetTimeDlg::DoDataExchange(CDataExchange* pDX)
{
	CXTResizeDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSetTimeDlg)
//	DDX_Text(pDX, IDC_EDIT_SECOND, m_nSecond);
//	DDV_MinMaxUInt(pDX, m_nSecond, 0, 255);
		  DDX_Control(pDX, IDC_COMBO_VERIFYT, m_VERIFYT);
		  DDX_Control(pDX, IDC_COMBO_PORT, m_PORT);
		  DDX_Control(pDX, IDC_COMBO_FUNCTION, m_FUNCTION);
	DDX_Control(pDX, IDC_LIST_C, m_listC);
	DDX_Control(pDX, IDC_LIST_C2, m_listC2);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSetTimeDlg, CXTResizeDialog)
	//{{AFX_MSG_MAP(CSetTimeDlg)
	ON_BN_CLICKED(IDOK_SEND, OnButSend)
	ON_CBN_SELCHANGE(IDC_COMBO_VERIFYT, OnchangeComboD)
	ON_BN_CLICKED(IDCANCEL, OnButCancel)
	ON_BN_CLICKED(IDC_BUT_RES, OnButRES)
	ON_CBN_EDITCHANGE(IDC_COMBO_VERIFYT, OnChCBV)
	ON_CBN_EDITCHANGE(IDC_COMBO_PORT, OnChCBP)
	ON_CBN_EDITCHANGE(IDC_COMBO_FUNCTION, OnChCBF)
	ON_CBN_SELCHANGE(IDC_COMBO_PORT, OnChCBP)
	ON_CBN_SELCHANGE(IDC_COMBO_FUNCTION, OnChCBF)
    ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_C, OnItemChangedList)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSetTimeDlg message handlers
BOOL CSetTimeDlg::OnInitDialog()
{
  CXTResizeDialog::OnInitDialog();

	CMainFrame* pFWnd=(CMainFrame*)AfxGetMainWnd();
   	pFWnd->m_pSetTimeDlg=this;

	SetResize(IDOK_SEND,                  SZ_BOTTOM_LEFT,   SZ_BOTTOM_LEFT);
	SetResize(IDCANCEL,              SZ_BOTTOM_LEFT,   SZ_BOTTOM_LEFT);
	if(chcommand == 0x43)       //���ò�� 
	{
    	SetResize(IDC_LIST_C,         SZ_TOP_LEFT,    SZ_BOTTOM_CENTER);
    	SetResize(IDC_LIST_C2,         SZ_TOP_CENTER,    SZ_BOTTOM_RIGHT);
	}
	else
    	SetResize(IDC_LIST_C,         SZ_TOP_LEFT,    SZ_BOTTOM_RIGHT);

	// Enable Office XP themes.
	XTThemeManager()->SetTheme(xtThemeOffice2003);



	HWND hWndHeader = m_listC.GetDlgItem(0)->GetSafeHwnd();
	m_header.SubclassWindow(hWndHeader);

	// add bitmap images.
	m_header.SetBitmap(0, IDB_COLUMN_0, FALSE, RGB(0,255,0));
	m_header.SetBitmap(1, IDB_COLUMN_1, FALSE, RGB(0,255,0));
	//m_header.SetBitmap(2, IDB_COLUMN_2, FALSE, RGB(0,255,0));

	// enable auto sizing.
	m_header.EnableAutoSize(TRUE);
	m_header.ResizeColumnsToFit();
	//SortColumn(m_nSortedCol, m_bAscending);

//	m_listCtrl.ModifyExtendedStyle(0, LVS_EX_FULLROWSELECT|LVS_EX_FULLROWSELECT);
	m_listC.ModifyExtendedStyle(0, LVS_EX_GRIDLINES);
	m_listC2.ModifyExtendedStyle(0, LVS_EX_GRIDLINES);

	// insert strings into the size combo box.
	if(chcommand == 0x5A)        //���ϱ���
	{
    	m_FUNCTION.AddString("�ر�");
    	m_FUNCTION.AddString("ʹ��");
	}
	else
	{
    	m_FUNCTION.AddString("����");
    	m_FUNCTION.AddString("�Ͽ�");
	}

	for(int i = 01; i < MAX_FDS; i++)
	{
		CString strItem;
		strItem.Format(_T("%d"), i);
    	m_VERIFYT.AddString(strItem);
		if(i<9)
        	m_PORT.AddString(strItem);
	}
	m_VERIFYT.SetCurSel(0);
	m_PORT.SetCurSel(0);
	m_FUNCTION.SetCurSel(0);

    CString szConnect ;

	if(chcommand == 0x54)         //Уʱ
	{
    	GetDlgItem(IDC_STATICV1)->ShowWindow(SW_HIDE);;
    	GetDlgItem(IDC_STATICV2)->ShowWindow(SW_HIDE);;
    	GetDlgItem(IDC_COMBO_PORT)->ShowWindow(SW_HIDE);;
    	GetDlgItem(IDC_COMBO_FUNCTION)->ShowWindow(SW_HIDE);;
    	GetDlgItem(IDC_LIST_C2)->ShowWindow(SW_HIDE);;
    	GetDlgItem(IDC_BUT_RES)->ShowWindow(SW_HIDE);;
		m_listC.InsertColumn(0,"�������Ϣ",LVCFMT_LEFT,450);
    	GetDlgItem(IDC_STATICV)->ShowWindow(SW_HIDE);;
    	GetDlgItem(IDC_COMBO_VERIFYT)->ShowWindow(SW_HIDE);;
	}
	else if(chcommand == 0x4B)   //�ֶ�����
	{
		m_listC.DeleteAllItems();
    	GetDlgItem(IDC_LIST_C2)->ShowWindow(SW_HIDE);;
		SetWindowText("�ֶ����Ʋ���");

		m_listC.InsertColumn(0,"�������Ϣ",LVCFMT_LEFT,450);
//		m_listC.InsertColumn(1,"������",LVCFMT_LEFT,80);
//		m_listC.InsertColumn(2,"������",LVCFMT_LEFT,80);

/*		int xxx = 0;
		int yyy = 0;
		unsigned char nfds = m_VERIFYT.GetCurSel()+1;
    	for( int iItem = 0; iItem < 8 ; iItem++)
		{
			yyy = xxx;
        	for( int i = 0; i < 64 ; i++)
			{
		      	if(m_ADCbreakE[nfds][iItem+17][i].bFSd != 0)
				{
				  m_listC.InsertItem(i+yyy, m_SlaveStation[nfds][iItem+17].WatchName);
				  m_listC.SetItemText(i+yyy, 1, m_ADCbreakE[nfds][iItem+17][i].cpoint);
				  m_listC.SetItemText(i+yyy, 2, m_ADCbreakE[nfds][iItem+17][i].adpoint);
				  xxx++;
				}
			}
		}
		m_nSecond = xxx;*/
	}
	else if(chcommand == 0x43)       //���ò�� 
	{
    	GetDlgItem(IDC_STATICV1)->ShowWindow(SW_HIDE);;
    	GetDlgItem(IDC_STATICV2)->ShowWindow(SW_HIDE);;
    	GetDlgItem(IDC_COMBO_PORT)->ShowWindow(SW_HIDE);;
    	GetDlgItem(IDC_COMBO_FUNCTION)->ShowWindow(SW_HIDE);;
		SetWindowText("��վ������ò���");
    	GetDlgItem(IDC_BUT_RES)->SetWindowText("��ʼ��");
		m_listC.InsertColumn(0,"�������Ϣ",LVCFMT_LEFT,450);
    	GetDlgItem(IDC_LIST_C2)->ShowWindow(SW_HIDE);
	}
	else if(chcommand == 0x41)        //���÷�վ
	{
		m_SControl.Create();
		m_SControl.CursorType(adOpenDynamic);
		m_SControl.CacheSize(50);
		m_SControl._SetRecordsetEvents(new CAccountSetEvents);
		m_SControl.Open(_T("Select * From specialcontrol"), &theApp.m_Cn);
		m_SControl.MarshalOptions(adMarshalModifiedOnly);

    	GetDlgItem(IDC_LIST_C2)->ShowWindow(SW_HIDE);
		SetWindowText("���÷�վ����");
    	GetDlgItem(IDC_STATICV2)->ShowWindow(SW_HIDE);
    	GetDlgItem(IDC_COMBO_FUNCTION)->ShowWindow(SW_HIDE);
    	GetDlgItem(IDC_STATICV1)->ShowWindow(SW_HIDE);
    	GetDlgItem(IDC_COMBO_PORT)->ShowWindow(SW_HIDE);;
    	GetDlgItem(IDC_COMBO_VERIFYT)->ShowWindow(SW_HIDE);
    	GetDlgItem(IDC_STATICV)->ShowWindow(SW_HIDE);;
//    	GetDlgItem(IDC_STATICV1)->SetWindowText("���ں�");
    	GetDlgItem(IDC_BUT_RES)->ShowWindow(SW_HIDE);;

    	m_listC.InsertHiddenLabelColumn();	// Requires one never uses column 0
    	for(int col = 0; col < 2 ; ++col)
		{
		CString title;  int kkk;
		CGridColumnTrait* pTrait = NULL;
		if (col==0)	// Country
		{
			kkk = 270;
			title ="��վ��";
		}
		if (col==1)	// Year won
		{
			kkk = 90;
			title ="���ں�";
			CGridColumnTraitCombo* pComboTrait = new CGridColumnTraitCombo;
			pComboTrait->AddItem(0, "������");
         	for(int i = 01; i < 100; i++)
			{
         		CString strItem,strtemp;
          		strItem.Format(_T("%d"), i);
              	pComboTrait->AddItem(i, strItem);
			}
			pTrait = pComboTrait;
		}
		m_listC.InsertColumnTrait(col+1, title, LVCFMT_LEFT, kkk, col, pTrait);
		}
		int iItem = 0;
		m_SControl.MoveFirst();
		while ( !m_SControl.IsEOF() )
		{
				  m_listC.InsertItem(iItem, "ͨ��");
				  CString dddd;
				  dddd.Format("%d",m_SControl.m_szSID);
				  m_listC.SetItemText(iItem, 1, dddd);
				  dddd.Format("%d",m_SControl.m_szSerialnum);
				  m_listC.SetItemText(iItem, 2, dddd);
				  iItem++;
			m_SControl.MoveNext();
		}
	}
	else if(chcommand == 0x47)        //ͨѶ����
	{
    	GetDlgItem(IDC_LIST_C2)->ShowWindow(SW_HIDE);;
		SetWindowText("ͨѶ����");
    	GetDlgItem(IDC_STATICV2)->ShowWindow(SW_HIDE);;
    	GetDlgItem(IDC_COMBO_FUNCTION)->ShowWindow(SW_HIDE);;
    	GetDlgItem(IDC_STATICV1)->ShowWindow(SW_HIDE);;
    	GetDlgItem(IDC_COMBO_PORT)->ShowWindow(SW_HIDE);;
    	GetDlgItem(IDC_BUT_RES)->ShowWindow(SW_HIDE);;
		m_listC.InsertColumn(0,"�������Ϣ",LVCFMT_LEFT,450);
	}
	else if(chcommand == 0x5A)        //���ϱ���
	{
    	GetDlgItem(IDC_LIST_C2)->ShowWindow(SW_HIDE);
		SetWindowText("���ϱ�������");
    	GetDlgItem(IDC_STATICV1)->ShowWindow(SW_HIDE);
    	GetDlgItem(IDC_COMBO_PORT)->ShowWindow(SW_HIDE);
    	GetDlgItem(IDC_STATICV2)->SetWindowText("���ϱ���״̬");
    	GetDlgItem(IDC_BUT_RES)->SetWindowText("��ʼ��");

		m_SControl.Create();
		m_SControl.CursorType(adOpenDynamic);
		m_SControl.CacheSize(50);
		m_SControl._SetRecordsetEvents(new CAccountSetEvents);
		m_SControl.Open(_T("Select * From specialcontrol"), &theApp.m_Cn);
		m_SControl.MarshalOptions(adMarshalModifiedOnly);

		m_listC.InsertColumn(0,"��վ��",LVCFMT_LEFT,300);
		m_listC.InsertColumn(1,"���ϱ���״̬",LVCFMT_LEFT,120);
		int iItem = 0;
		m_SControl.MoveFirst();
		while ( !m_SControl.IsEOF() )
		{
				  CString dddd;
				  dddd.Format("%d",m_SControl.m_szSID);
				  m_listC.InsertItem(iItem, dddd);
				  if(m_SControl.m_szSpeCtrol)
    				  m_listC.SetItemText(iItem, 1, "ʹ��");
				  else
    				  m_listC.SetItemText(iItem, 1, "�ر�");
				  iItem++;
			m_SControl.MoveNext();
		}
		m_nSecond = 64;
	}
	else if(chcommand == 0x46)        //�����˹����
	{
    	GetDlgItem(IDC_LIST_C2)->ShowWindow(SW_HIDE);
		SetWindowText("�����˹��������");
    	GetDlgItem(IDC_STATICV1)->ShowWindow(SW_HIDE);
    	GetDlgItem(IDC_COMBO_PORT)->ShowWindow(SW_HIDE);
    	GetDlgItem(IDC_STATICV2)->ShowWindow(SW_HIDE);
    	GetDlgItem(IDC_COMBO_FUNCTION)->ShowWindow(SW_HIDE);
    	GetDlgItem(IDC_BUT_RES)->SetWindowText("��ʼ��");
		InitWGas(0);
	}
	else if(chcommand == 0xf0)        //˫���š����ȱ��ȱ���
	{
		m_Records1.clear();
		m_Records2.clear();
    	GetDlgItem(IDC_LIST_C2)->ShowWindow(SW_HIDE);
		SetWindowText("˫�豸�����߼�����");
    	GetDlgItem(IDOK_SEND)->SetWindowText("���");
    	GetDlgItem(IDC_BUT_RES)->SetWindowText("ɾ��");
    	GetDlgItem(IDC_STATICV1)->SetWindowText("������1");
    	GetDlgItem(IDC_STATICV2)->SetWindowText("������2");
    	GetDlgItem(IDC_STATICV)->SetWindowText(_T("����̬"));
//    	GetDlgItem(IDC_COMBO_VERIFYT)->ShowWindow(SW_HIDE);
	 	    m_PORT.ResetContent();
	 	    m_FUNCTION.ResetContent();
			m_VERIFYT.ResetContent();
			m_VERIFYT.AddString(_T("0̬"));
			m_VERIFYT.AddString(_T("1̬"));
          	m_VERIFYT.SetCurSel(0);

		m_Fans.Create();
		m_Fans.CursorType(adOpenDynamic);
		m_Fans.CacheSize(50);
		m_Fans._SetRecordsetEvents(new CAccountSetEvents);
		m_Fans.Open(_T("Select * From fanscon"), &theApp.m_Cn);
		m_Fans.MarshalOptions(adMarshalModifiedOnly);

    	int ptype;	CString dddd;
		for(int i = 1; i < MAX_FDS;i++ )
		{
			for(int j = 0; j < MAX_CHAN;j++ )
			{
       			ptype = m_SlaveStation[i][j].ptype;
       			if((ptype == 10 || ptype == 13 ||ptype == 14) && m_SlaveStation[i][j].WatchName !="")
				{
    				dddd = m_SlaveStation[i][j].strPN + "|"+m_SlaveStation[i][j].WatchName;
	        	    m_PORT.AddString(dddd);
	        	    m_FUNCTION.AddString(dddd);
				}
			}
		}
	     	    m_PORT.SetCurSel(0);
	    	    m_FUNCTION.SetCurSel(0);
		m_listC.InsertColumn(0,"������1",LVCFMT_LEFT,60);
		m_listC.InsertColumn(1,"��װ�ص�/����1",LVCFMT_LEFT,200);
		m_listC.InsertColumn(2,"������2",LVCFMT_LEFT,60);
		m_listC.InsertColumn(3,"��װ�ص�/����2",LVCFMT_LEFT,200);
		m_listC.InsertColumn(4,"����״̬",LVCFMT_LEFT,60);
//		m_listC.InsertColumn(5,"ID",LVCFMT_LEFT,30);
		int iItem = 0;
		m_Fans.MoveFirst();
		while ( !m_Fans.IsEOF() )
		{
				  CString dddd = m_Fans.m_szpointnum1;
    		dddd.TrimRight();
				  m_listC.InsertItem(iItem, dddd);
				  m_Records1.push_back(dddd);
				  dddd = m_Fans.m_szName1;
    		dddd.TrimRight();
    			  m_listC.SetItemText(iItem, 1, dddd);
				  dddd = m_Fans.m_szpointnum2;
    		dddd.TrimRight();
    			  m_listC.SetItemText(iItem, 2, dddd);
				  m_Records2.push_back(dddd);
				  dddd = m_Fans.m_szName2;
    		dddd.TrimRight();
    			  m_listC.SetItemText(iItem, 3, dddd);
            dddd.Format(_T("%d̬"), m_Fans.m_szAStatus);
    			  m_listC.SetItemText(iItem, 4, dddd);
 			m_nSecond = m_Fans.m_szFansID+1;
//            dddd.Format(_T("%d"), m_nSecond-1);
//    			  m_listC.SetItemText(iItem, 5, dddd);
			iItem++;
			m_Fans.MoveNext();
		}
	}
	else if(chcommand == 0xf1)            //������ʾҳ����
	{
		m_Records1.clear();
    	GetDlgItem(IDC_LIST_C2)->ShowWindow(SW_HIDE);
		SetWindowText("������ʾҳ����");
    	GetDlgItem(IDOK_SEND)->SetWindowText("����");
    	GetDlgItem(IDC_BUT_RES)->ShowWindow(SW_HIDE);
    	GetDlgItem(IDC_STATICV1)->SetWindowText("�ļ���");
    	GetDlgItem(IDC_STATICV2)->SetWindowText("�б�");
    	GetDlgItem(IDC_STATICV)->SetWindowText(_T("���"));
    	GetDlgItem(IDC_COMBO_VERIFYT)->EnableWindow(FALSE);

		CString strPointNo,cccc,strrsy,strrsy1;
    	strrsy = gstrTimeOut + "\\" + strMetrics+ "rsy\\";
	 	    m_PORT.ResetContent();
	 	    m_FUNCTION.ResetContent();
			m_VERIFYT.ResetContent();

        for(int i =0; i < theApp.m_addfilesy.size() ;i++)
		{
    		strPointNo = theApp.m_addfilesy[i];
       		int m_ishave = strPointNo.GetLength();
    		cccc = strPointNo.Mid(m_ishave-3,3);
    		strPointNo.Replace(strrsy,"");
    		if(cccc =="rsf")
			{
				m_Records1.push_back(strPointNo);
    			m_PORT.AddString(strPointNo);
			}
		}
//          	m_VERIFYT.SetCurSel(0);
        for(int k =1; k < 4 ;k++)
		{
	    		cccc.Format("%d",k);
    	 	    m_FUNCTION.AddString(cccc);
            	m_FUNCTION.SetCurSel(0);
		}

	// Give better margin to editors
     	m_listC.SetCellMargin(1.2);
    	CGridRowTraitXP* pRowTrait = new CGridRowTraitXP;
    	m_listC.SetDefaultRowTrait(pRowTrait);
	// Create Columns
     	m_listC.InsertHiddenLabelColumn();	// Requires one never uses column 0
    	for(int col = 0; col < 2 ; ++col)
		{
    		CString title;  int kkk;
			CGridColumnTrait* pTrait = NULL;
      		if (col==0)	// Country
			{
		    	kkk = 350;
	    		title ="������ʾҳ����";
			}
	    	if (col==1)	// City
			{
		    	kkk = 100;
	    		title ="����(����)";
      			pTrait = new CGridColumnTraitEdit;
			}
    		m_listC.InsertColumnTrait(col+1, title, LVCFMT_LEFT, kkk, col, pTrait);
		}
		CString strl[35];
//		strl[0] = "�Ƿ�ɼ�(1�ɼ�|0����)";		strl[1] = "����ͷ����(1��0)";
//		strl[2] = "�б����϶���x����";
//		strl[3] = "�б���";		strl[4] = "�б�߶�";		strl[5] = "��һ������";
//		strl[6] = "��һ�п��";		strl[7] = "�ڶ�������";		strl[8] = "�ڶ��п��";
//		strl[9] = "����������";		strl[10] = "�����п��";		strl[11] = "����";
		strl[0] = "�Ƿ�ɼ�(1�ɼ�|0����)";		strl[1] = "����ͷ����(1��0)";
		strl[2] = "�б����϶���x����";
		strl[3] = "�б���";		strl[4] = "�б�߶�";		strl[5] = "��һ�п��";
		strl[6] = "�ڶ��п��";
		strl[7] = "�����п��";		//strl[8] = "����";

		strl[8] = "���ֵ�п��";		strl[9] = "��Сֵ�п��";		strl[10] = "ƽ��ֵ�п��";
		strl[11] = "�ϵ�ֵ�п��";		strl[12] = "����ֵ�п��";		strl[13] = "���������п��";
		strl[14] = "���������п��";		strl[15] = "���̸�ֵ�п��";		strl[16] = "���̵�ֵ�п��";
		strl[17] = "�ϵ�ʱ���п��";		strl[18] = "����ʱ���п��";		strl[19] = "����ʱ���п��";
		strl[20] = "����״̬��ʱ���п��";		strl[21] = "�ϵ緶Χ�п��";		strl[22] = "��ͣ�����п��";	
		strl[23] = "����ʱ���п��";
		for( k =0; k < 22 ;k++)
		{
				  m_listC.InsertItem(k, "ͨ��");
				  m_listC.SetItemText(k, 1, strl[k]);
				  m_listC.SetItemText(k, 2, "");
		}
	}

  return TRUE;  // return TRUE unless you set the focus to a control
  // EXCEPTION: OCX Property Pages should return FALSE
}

void CSetTimeDlg::OnClose()
{
  //Closing of library objects is ensured as each object
  //goes out of scope, but doing a manual shutdown doesn�t hurt.

/*    if ( m_AccountSet._IsOpen() )
      m_AccountSet.Close();
    if ( m_ContactSet._IsOpen() )
      m_ContactSet.Close();
    if ( m_Control._IsOpen() )
      m_Control.Close();*/
    if ( m_SControl._IsOpen() )
      m_SControl.Close();
    if ( m_Fans._IsOpen() )
      m_Fans.Close();
    if ( m_CommonSet._IsOpen() )
       m_CommonSet.Close();

//  CDialog::OnClose();
}

void CSetTimeDlg::OnChCBF() 
{
	UpdateData(TRUE);
		CString cccc;
	if(chcommand == 0xf1)            //������ʾҳ����
	{
    	int  mp = m_FUNCTION.GetCurSel()+1;
//		GetDlgItem(IDC_COMBO_FUNCTION)->GetWindowText(cccc);
//		nfds3 = m_Str2Data.String2Int(cccc);
		 if(mp ==1)
		 {
            for(int k =0; k < 25 ;k++)
			{
			 if(k < 8)
    			m_listC.SetItemText(k, 2, m_CommonStr[m_nSecond].strc[k+1]);
			 else
    			m_listC.SetItemText(k, 2, m_CommonStr[m_nSecond].strc[k+2]);
			}
		 }
		 else if(mp ==2)
		 {
            for(int k =0; k < 25 ;k++)
			{
			 if(k < 8)
    			m_listC.SetItemText(k, 2, m_CommonStr[m_nSecond].strc[k+31]);
			 else
    			m_listC.SetItemText(k, 2, m_CommonStr[m_nSecond].strc[k+32]);
			}
		 }
		 else if(mp ==3)
		 {
            for(int k =0; k < 25 ;k++)
			{
			 if(k < 8)
    			m_listC.SetItemText(k, 2, m_CommonStr[m_nSecond].strc[k+61]);
			 else
    			m_listC.SetItemText(k, 2, m_CommonStr[m_nSecond].strc[k+62]);
			}
		 }
	}
}

void CSetTimeDlg::OnChCBV() 
{
	UpdateData(TRUE);
		CString cccc; int nfds3;
		GetDlgItem(IDC_COMBO_VERIFYT)->GetWindowText(cccc);
		nfds3 = m_Str2Data.String2Int(cccc);
		if(nfds3 <1 || nfds3>60)
		{
          	AfxMessageBox("��վ����1-60��ѡ��", MB_OK);
    		GetDlgItem(IDC_COMBO_VERIFYT)->SetWindowText("1");
	    	  return;
		}

	if(chcommand == 0x46)          //�����˹����
	{
		InitWGas(nfds3);
	}
	else if(chcommand == 0x4B)   //�ֶ�����
	{
     	m_listC.DeleteAllItems();
//	    for (int iItem1 = 2; iItem1 >= 0; iItem1--)
//    		m_listC.DeleteColumn(iItem1);
/*		int xxx = 0;		int yyy = 0;		unsigned char nfds = nfds3;
    	for( int iItem = 0; iItem < 8 ; iItem++)
		{
			yyy = xxx;
        	for( int i = 0; i < 64 ; i++)
			{
		      	if(m_ADCbreakE[nfds][iItem+17][i].bFSd != 0)
				{
				  m_listC.InsertItem(i+yyy, m_SlaveStation[nfds][iItem+17].WatchName);
				  m_listC.SetItemText(i+yyy, 1, m_ADCbreakE[nfds][iItem+17][i].cpoint);
				  m_listC.SetItemText(i+yyy, 2, m_ADCbreakE[nfds][iItem+17][i].adpoint);
				  xxx++;
				}
			}
		}
		m_nSecond = xxx;*/
	}
	UpdateData(FALSE);
}

void CSetTimeDlg::OnChCBP() 
{
	UpdateData(TRUE);
		CString cccc;
		GetDlgItem(IDC_COMBO_PORT)->GetWindowText(cccc);
		int nfds3 = m_Str2Data.String2Int(cccc);
	if(chcommand != 0xf1)            //������ʾҳ����
	{
		if(nfds3 <1 || nfds3>8)
		{
          	AfxMessageBox("ͨ������1-8��ѡ��", MB_OK);
    		GetDlgItem(IDC_COMBO_PORT)->SetWindowText("1");
	    	  return;
		}
	}
	if(chcommand == 0xf1)            //������ʾҳ����
	{
		m_VERIFYT.ResetContent();
    	int  mp = m_PORT.GetCurSel();
		cccc = m_Records1[mp];
//    	GetDlgItem(IDC_COMBO_VERIFYT)->EnableWindow(TRUE);
    	CString strPointNo,strrsy,strrsy1;
    	strrsy = gstrTimeOut + "\\" + strMetrics+ "rsy\\";
		int ishave=0;

		strrsy1 ="dispoint"+strMetrics;
		CppSQLite3Query q;
				strPointNo.Format("select * from '%s' WHERE DISID=1;",strrsy1);
         q = theApp.db3.execQuery(strPointNo);

        for(int k =2; k < 21 ;k++)
		{
            strPointNo = q.getStringField(k);
			strPointNo.TrimRight();
			if(cccc == strPointNo)
			{
				m_nSecond =k-1;
				ishave =k;
	    		cccc.Format("%d",k-1);
    	 	    m_VERIFYT.AddString(cccc);
            	m_VERIFYT.SetCurSel(0);
				break;
			}
		}
		if(ishave == 0)
		{
           for(int k =2; k < 21 ;k++)
		   {
            strPointNo = q.getStringField(k);
			strPointNo.TrimRight();
			if(strPointNo == "")
			{
				m_nSecond =k-1;
	    		cccc.Format("%d",k-1);
    	 	    m_VERIFYT.AddString(cccc);
            	m_VERIFYT.SetCurSel(0);
				break;
			}
		   }
		}
		m_FUNCTION.SetCurSel(0);
//		GetDlgItem(IDC_COMBO_FUNCTION)->GetWindowText(cccc);
//		nfds3 = m_Str2Data.String2Int(cccc);
//		 if(cccc =="1")
//	        m_cChWT.SetCheck(m_Str2Data.String2Int(m_CommonStr[m_ntrans].strc[105+20*(m_nlist-1)]));
         for( k =0; k < 25 ;k++)
		 {
			 if(k < 8)
    			m_listC.SetItemText(k, 2, m_CommonStr[m_nSecond].strc[k+1]);
			 else
    			m_listC.SetItemText(k, 2, m_CommonStr[m_nSecond].strc[k+2]);
		 }
/*		 else if(cccc =="2")
		 strPointNo.Format("select * from '%s' WHERE DISID>110 and DISID<120;",strrsy1);
    				  m_listC.SetItemText(ishave-111, 2, strPointNo);
		 strPointNo.Format("select * from '%s' WHERE DISID>210 and DISID<220;",strrsy1);
    				  m_listC.SetItemText(ishave-211, 2, strPointNo);
		 }*/
		q.finalize();
	}

	UpdateData(FALSE);
}

void CSetTimeDlg::OnchangeComboD() 
{
	if(chcommand == 0x46)          //�����˹����
	{
		InitWGas(0);
	}
	else if(chcommand == 0x4B)   //�ֶ�����
	{
     	m_listC.DeleteAllItems();
//	    for (int iItem1 = 2; iItem1 >= 0; iItem1--)
//    		m_listC.DeleteColumn(iItem1);
/*		int xxx = 0;
		int yyy = 0;
		unsigned char nfds = m_VERIFYT.GetCurSel()+1;
    	for( int iItem = 0; iItem < 8 ; iItem++)
		{
			yyy = xxx;
        	for( int i = 0; i < 64 ; i++)
			{
		      	if(m_ADCbreakE[nfds][iItem+17][i].bFSd != 0)
				{
				  m_listC.InsertItem(i+yyy, m_SlaveStation[nfds][iItem+17].WatchName);
				  m_listC.SetItemText(i+yyy, 1, m_ADCbreakE[nfds][iItem+17][i].cpoint);
				  m_listC.SetItemText(i+yyy, 2, m_ADCbreakE[nfds][iItem+17][i].adpoint);
				  xxx++;
				}
			}
		}
		m_nSecond = xxx;*/
	}
}

void CSetTimeDlg::OnButSend() 
{
//        swprintf(pTTTW->szText,L"%s",strB); 
 //      swprintf((wchar_t *)pTTTW->szText,L"%s",tooltip.AllocSysString()); 
//			 _stprintf((LPTSTR)word,_T("%s"),strB);  

//	m_ndkSend = new  unsigned char[200]; 
//		GetDlgItem(IDC_COMBO_VERIFYT)->GetWindowText(cccc);
	CString strPointNo,cccc,strim2;
	UpdateData(TRUE);
		GetDlgItem(IDC_COMBO_VERIFYT)->GetWindowText(cccc);
		unsigned char nfds3 = m_Str2Data.String2Int(cccc);
		GetDlgItem(IDC_COMBO_PORT)->GetWindowText(cccc);
		int nfdsP = m_Str2Data.String2Int(cccc);
	unsigned char nfds =nfds3;

	if(chcommand == 0x54)   //Уʱ
	{
//	GetSystemMenu(FALSE)->EnableMenuItem(SC_CLOSE ,MF_DISABLED);
//	GetDlgItem(IDOK_SEND)-> EnableWindow(FALSE);
//	GetDlgItem(IDCANCEL)-> EnableWindow(FALSE);
        m_ndkSend = new  unsigned char[11];
    	CMainFrame* pFWnd=(CMainFrame*)AfxGetMainWnd();
		pFWnd->n_timer60 =1;
	}
	else if(chcommand == 0x4B)            //�ֶ�����
	{
      	m_ndkSend = new  unsigned char[6];
		            m_ndkSend[0] = 0x7E;
		            m_ndkSend[1] = nfds3;
		            m_ndkSend[2] = chcommand;
		            m_ndkSend[3] = nfdsP;
					nfds = m_FUNCTION.GetCurSel();
					if(nfds >1)
					{
          	AfxMessageBox("��ѡ�����ϡ��򡰶Ͽ�����", MB_OK);
			m_FUNCTION.SetCurSel(0);
         	delete m_ndkSend;
			return;
					}
		            m_ndkSend[4] = nfds;
		            m_ndkSend[5] = 0x21;
    	CNDKMessage message1(MANUALCONTROL);
					message1.Add(m_ndkSend , 200);
					theApp.Sync(message1,1);
					if(nfds ==0)
						cccc ="����";
					else if(nfds ==1)
						cccc ="�Ͽ�";

					m_nchangev = chcommand;
        GetDlgItem(IDC_BUT_RES)->ShowWindow(SW_SHOW);
					strim2.Format("%d�ŷ�վ�ֶ����ƣ��˿�%d|%s",nfds3,nfdsP,cccc);
       g_Log.StatusOut(strim2);
	}
	else if(chcommand == 0x43)       //���ò��
	{
        	CString strSQL;
		if(m_SerialF[nfds].SFSd ==0)
		{
        	strSQL.Format("%d�ŷ�վû��Ѳ�죡",nfds3);
            AfxMessageBox(strSQL, MB_OK);
			return;
		}
      	m_ndkSend = new  unsigned char[166];
		theApp.m_RTDM.SendPP(nfds3);
	}
	else if(chcommand == 0x41)            //���÷�վ
	{
      	m_ndkSend = new  unsigned char[64];
		int n_fen;
		            m_ndkSend[0] = 0x7E;
		            m_ndkSend[1] = 0x01;
		            m_ndkSend[2] = chcommand;
        for(int nItem=0;nItem<60;nItem++)
		{
    		strPointNo=m_listC.GetItemText(nItem,2);
			n_fen = m_Str2Data.String2Int(strPointNo);
			if(n_fen >99 || n_fen <0)
				break;
			if(n_fen == 0)//������������ʱ��Ҳ��0  ������Ϊ0
	      		m_listC.SetItemText(nItem,2,"0");
              m_ndkSend[nItem+3] = n_fen;
		}
		if(n_fen >99 || n_fen <0)
		{
          	AfxMessageBox("���ں���0-99��ѡ��", MB_OK);
			m_listC.SetItemText(nItem,2,"0"); //������Ϊ0
         	delete m_ndkSend;
			return;
		}
		            m_ndkSend[63] = 0x21;
    	CNDKMessage message1(INFODEFINE);
					message1.Add(m_ndkSend , 64);
					theApp.Sync(message1,1);
        for( nItem=0;nItem<60;nItem++)
		{
            				try
							{
                             m_SControl.AbsolutePosition(nItem + 1);
         					 m_SControlNew->m_szSID = nItem+1;
	         				 m_SControlNew->m_szSerialnum = m_ndkSend[nItem+3];
					   	     m_SControlNew->Update();    //Update the recordset
							}
		     			    catch (CAxException *e)
							{
					        	AfxMessageBox(e->m_szErrorDesc, MB_OK);
				        		delete e;
							}
					strPointNo.Format("%d�ŷ�վ,�䴮��%d  ",nItem+1,m_ndkSend[nItem+3]);
					strim2 +=strPointNo;
		}//for
		theApp.InitData();
       g_Log.StatusOut("���÷�վ��" +strim2);
          	AfxMessageBox("���÷�վ����ͳɹ���", MB_OK);
	}
	else if(chcommand == 0x47)            //ͨѶ����
	{
      	m_ndkSend = new  unsigned char[4];
		            m_ndkSend[0] = 0x7E;
		            m_ndkSend[1] = nfds3;
		            m_ndkSend[2] = chcommand;
		            m_ndkSend[3] = 0x21;
    	CNDKMessage message1(TESTCOMMUNICATION);
					message1.Add(m_ndkSend , 200);
					theApp.Sync(message1,1);
 	  strim2.Format("ͨѶ����:%d�ŷ�վ",nfds3);
      g_Log.StatusOut(strim2);
	}
	else if(chcommand == 0x5A)            //���ϱ���
	{
		if(m_SerialF[nfds3].SFSd ==0)
		{
        	strim2.Format("%d�ŷ�վû��Ѳ�죡",nfds3);
            AfxMessageBox(strim2, MB_OK);
			return;
		}
      	m_ndkSend = new  unsigned char[5];
				    m_ndkSend[0] = 0x7E;
		            m_ndkSend[1] = nfds3;
		            m_ndkSend[2] = chcommand;
					nfds = m_FUNCTION.GetCurSel();
					if(nfds >1)
					{
          	AfxMessageBox("��ѡ��ʹ�ܡ��򡰹رա���", MB_OK);
			m_FUNCTION.SetCurSel(0);
         	delete m_ndkSend;
			return;
					}
		            m_ndkSend[3] = nfds;
		            m_ndkSend[4] = 0x21;
    	CNDKMessage message1(FAULTATRESIA);
					message1.Add(m_ndkSend , 200);
					theApp.Sync(message1,1);
					theApp.n_temp =nfds;

/*            				try
							{
                             m_SControl.AbsolutePosition(m_ndkSend[1]);
         					 m_SControlNew->m_szSID = m_ndkSend[1];
	         				 m_SControlNew->m_szSpeCtrol = (bool)m_ndkSend[3];
					   	     m_SControlNew->Update();    //Update the recordset
							}
		     			    catch (CAxException *e)
							{
					        	AfxMessageBox(e->m_szErrorDesc, MB_OK);
				        		delete e;
							}*/
 	  strim2.Format("%d��վ,���ϱ�����Ϊ:",nfds3);
			if(nfds ==0)
				strim2 +="�ر�";
			else if(nfds ==1)
				strim2 +="ʹ��";
// 	  strim2.Format("%x||%x",nfds3,m_ndkSend[3]);
      g_Log.StatusOut(strim2);
	}
	else if(chcommand == 0x46)            //�����˹����
	{
		if(m_SerialF[nfds3].SFSd ==0)
		{
        	strim2.Format("%d�ŷ�վû��Ѳ�죡",nfds3);
            AfxMessageBox(strim2, MB_OK);
			return;
		}
		for(int i =0; i < 6 ;i++)//�����˹������ϵ����Ĳ������ʱ���Գ�ʼ�����޸�
		{
			if(str_list[i].strl =="")
				break;
        	CString strf,strc,strSQL;
		    strf = str_list[i].strl.Mid(0,2);
    		strc = str_list[i].strl.Mid(3,2);
    		int nfds = m_Str2Data.String2Int(strf);
     		int nchan = m_Str2Data.String2Int(strc);
			unsigned char nstatus = m_SlaveStation[nfds][nchan].Channel_state;
			if(nstatus == 0x10 || nstatus == 0x20 || nstatus == 0xa0)
			{
            	strSQL.Format("%d�ŷ�վ%s״̬Ϊ%s�������޸ģ�",nfds,str_list[i].strl,theApp.m_RTDM.strstatus(nstatus));
                AfxMessageBox(strSQL, MB_OK);
	    		return;
			}
		}

      	m_ndkSend = new  unsigned char[10];
		bool b_gas =true;
		            m_ndkSend[0] = 0x7E;
		            m_ndkSend[1] = nfds3;
		            m_ndkSend[2] = chcommand;
        for(int nItem=0;nItem<6;nItem++)
		{
    		strPointNo=m_listC.GetItemText(nItem,2);
			if(strPointNo == "")
			{
				b_gas =false;
				break;
			}
			strPointNo = strPointNo.Mid(3,2);
			nfds = m_Str2Data.String2Int(strPointNo);
	        		m_ndkSend[nItem+3] = nfds;
		}
		if(b_gas)
		{
		            m_ndkSend[9] = 0x21;
                	CNDKMessage message1(WINDGASATRESIA);
					message1.Add(m_ndkSend , 200);
					theApp.Sync(message1,1);

        	for(int i =0;i<6;i++)
        		str_list[i].strl=m_listC.GetItemText(i,2);
        	strim2.Format("����%d�ŷ�վ�����˹������",nfds3);
            AfxMessageBox(strim2);
            g_Log.StatusOut(strim2);
		}
		else
		{
        	delete m_ndkSend;
			strPointNo.Format("��%d���Ϊ�գ�",nItem+1);
            AfxMessageBox(strPointNo);
	    	return;
		}
	}
	else if(chcommand == 0xf0)            //˫���š����ȱ��ȱ���
	{
      	m_ndkSend = new  unsigned char[11];
       	LPCTSTR str1 = "",str2 = "",str3 = "";
      	CString  m_strsel,m_strsel2 ,str11,str12;
		int kkk=0;
            				try
							{
         					 m_Fans.m_szFansID = m_nSecond;
							 m_PORT.GetWindowText(m_strsel);
           	m_Str2Data.SplittoCString(m_strsel,str1,str2,str3);
			str11 =str1;
			m_strsel =str2;
			m_strsel +="|";
			m_strsel +=str3;
	         				 m_Fans.m_szName1 = m_strsel;
	         				 m_Fans.m_szpointnum1 = str11 ;
							 m_FUNCTION.GetWindowText(m_strsel2);
           	m_Str2Data.SplittoCString(m_strsel2,str1,str2,str3);
			str12 =str1;
			m_strsel2 =str2;
			m_strsel2 +="|";
			m_strsel2 +=str3;
	         				 m_Fans.m_szName2 = m_strsel2;
	         				 m_Fans.m_szpointnum2 = str12;
				if(str11 == str12)
				{
                 	AfxMessageBox("��Ų�����ͬ������ѡ��", MB_OK);
                   	delete m_ndkSend;
          			return;
				}
				for ( int i = 0 ; i < m_Records1.size() ; i++ )
				{
    				if((str11 == m_Records1[i])&&(str12 == m_Records2[i]))
					{
						kkk =100;
                    	AfxMessageBox("��������Ѷ��壬����ѡ��", MB_OK);
                     	delete m_ndkSend;
           	    		break;
					}
				}
				if(kkk == 100)
           	    		return;

				kkk = m_Records1.size();
				  m_listC.InsertItem(kkk, str11);
    			  m_listC.SetItemText(kkk, 1, m_strsel);
    			  m_listC.SetItemText(kkk, 2, str12);
    			  m_listC.SetItemText(kkk, 3, m_strsel2);
		strim2 = str11 +" "+m_strsel+"   "+str12 + " "+m_strsel2+ "   ";  
            m_strsel.Format(_T("%d̬"), m_VERIFYT.GetCurSel());
			strim2 += m_strsel+"   "+theApp.curuser;
    			  m_listC.SetItemText(kkk, 4, m_strsel);
            m_strsel.Format(_T("%d"), m_nSecond);
    			  m_listC.SetItemText(kkk, 5, m_strsel);

				  m_Records1.push_back(str11);
				  m_Records2.push_back(str12);
	
				m_Fans.m_szAStatus = m_VERIFYT.GetCurSel();

      						m_Fans.AddNew();  //Add a new, blank record
					   	    m_Fans.Update();    //Update the recordset
						    m_Fans.Requery();
							m_nSecond++;
							}
		     			    catch (CAxException *e)
							{
					        	AfxMessageBox(e->m_szErrorDesc, MB_OK);
				        		delete e;
							}
		theApp.InitData();

      g_Log.StatusOut("˫�豸������ϵ��ӣ�" +strim2);
	}
	else if(chcommand == 0xf1)            //������ʾҳ����
	{
      	m_ndkSend = new  unsigned char[11];
		if(m_nSecond <1)
		{
                 	AfxMessageBox("��ѡ���ļ�����", MB_OK);
          			return;
		}
    	CString strPointNo,strrsy,strrsy1,strSQL;
		int ishave=0;
		strrsy1 ="dispoint"+strMetrics;
		strrsy.Format("LP%d",m_nSecond);
		CppSQLite3Query q;
		GetDlgItem(IDC_COMBO_PORT)->GetWindowText(cccc);
//				strSQL.Format("UPDATE '%s' SET LP1='' WHERE DISID =0;",
//					strrsy1);
				strSQL.Format("UPDATE '%s' SET '%s'='%s' WHERE DISID =1;",
					strrsy1,strrsy,cccc);
             q = theApp.db3.execQuery(strSQL);
		GetDlgItem(IDC_COMBO_FUNCTION)->GetWindowText(cccc);

		 if(cccc =="1")
		 {
           for(int m =0; m < 25 ;m++)
		   {
			   if(m < 8)
				strSQL.Format("UPDATE '%s' SET '%s'='%s' WHERE DISID = %d;",
					strrsy1,strrsy,m_listC.GetItemText(m,2),m+11);
			   else
				strSQL.Format("UPDATE '%s' SET '%s'='%s' WHERE DISID = %d;",
					strrsy1,strrsy,m_listC.GetItemText(m,2),m+12);
                q = theApp.db3.execQuery(strSQL);
		   }
		 }
		 else if(cccc =="2")
		 {
           for(int m =0; m < 25 ;m++)
		   {
			   if(m < 8)
				strSQL.Format("UPDATE '%s' SET '%s'='%s' WHERE DISID = %d;",
					strrsy1,strrsy,m_listC.GetItemText(m,2),m+111);
			   else
				strSQL.Format("UPDATE '%s' SET '%s'='%s' WHERE DISID = %d;",
					strrsy1,strrsy,m_listC.GetItemText(m,2),m+112);
             q = theApp.db3.execQuery(strSQL);
		   }
		 }
		 else if(cccc =="3")
		 {
           for(int m =0; m < 25 ;m++)
		   {
			   if(m < 8)
				strSQL.Format("UPDATE '%s' SET '%s'='%s' WHERE DISID = %d;",
					strrsy1,strrsy,m_listC.GetItemText(m,2),m+211);
			   else
				strSQL.Format("UPDATE '%s' SET '%s'='%s' WHERE DISID = %d;",
					strrsy1,strrsy,m_listC.GetItemText(m,2),m+212);
             q = theApp.db3.execQuery(strSQL);
		   }
		 }
    	q.finalize();
       AfxMessageBox("����ɹ���", MB_OK);
		m_nchange =1000;
	}
	delete m_ndkSend;
}

void CSetTimeDlg::OnButRES() 
{
	m_ndkSend = new  unsigned char[166];
    if(chcommand == 0x4B)   //�ֶ�����
	{
		            m_ndkSend[0] = 0x7E;
		     unsigned char nfds = m_VERIFYT.GetCurSel()+1;
		            m_ndkSend[1] = nfds;
		            m_ndkSend[2] = chcommand;
		            m_ndkSend[3] = 0xff;
		            m_ndkSend[4] = 0x02;
		            m_ndkSend[5] = 0x21;
    	CNDKMessage message1(MANUALCONTROL);
					message1.Add(m_ndkSend , 100);
					theApp.Sync(message1,1);
//		m_nchangev = 0;
	}
    else if(chcommand == 0xf0)   //˫���š����ȱ��ȱ���
	{
			CString  dddd ="";
    	int nItemCount=m_listC.GetItemCount();
        for(int nItem=0;nItem<nItemCount;nItem++)
		{
    		if(m_listC.GetItemState(nItem,LVIS_SELECTED) & LVIS_SELECTED)
			{
				dddd = m_listC.GetItemText(nItem,0) +" "+m_listC.GetItemText(nItem,1) +"   " +m_listC.GetItemText(nItem,2) 
					      +" "+m_listC.GetItemText(nItem,3) +"   "+m_listC.GetItemText(nItem,4)+"   "+theApp.curuser;
            	CString strf,strc;
     		    strf = dddd.Mid(0,2);
          		strc = dddd.Mid(3,2);
          		int nfds = m_Str2Data.String2Int(strf);
        		int nchan = m_Str2Data.String2Int(strc);
				int n_fans = m_AFans[nfds][nchan].fchan;
    			if(n_fans == 1)
				{
					nItemCount =666;
	        		break;
				}
	    	   	  m_listC.DeleteItem(nItem);
//       			nItem = m_Str2Data.String2Int(strPointNo);
                  g_Log.StatusOut("˫�豸������ϵɾ����" + dddd);
    	     		break;
			}
		}
        CString strSQL;
		if(dddd =="")
		{
            AfxMessageBox("��ѡ��Ҫɾ�����豸��", MB_OK);
         	delete m_ndkSend;
			return;
		}
		if(nItemCount == 666)
		{
        	strSQL.Format("%s:�豸����������ɾ����",dddd);
            AfxMessageBox(strSQL, MB_OK);
         	delete m_ndkSend;
			return;
		}
		else
    		m_Fans.Delete();

        if ( m_Fans._IsOpen() )
             m_Fans.Close();
		m_Records1.clear();
		m_Records2.clear();
		m_listC.DeleteAllItems();

		m_Fans.Create();
		m_Fans.CursorType(adOpenDynamic);
		m_Fans.CacheSize(50);
		m_Fans._SetRecordsetEvents(new CAccountSetEvents);
		m_Fans.Open(_T("Select * From fanscon"), &theApp.m_Cn);
		m_Fans.MarshalOptions(adMarshalModifiedOnly);

		int iItem = 0;
		m_Fans.MoveFirst();
		while ( !m_Fans.IsEOF() )
		{
				  CString dddd = m_Fans.m_szpointnum1;
    		dddd.TrimRight();
				  m_listC.InsertItem(iItem, dddd);
				  m_Records1.push_back(dddd);
				  dddd = m_Fans.m_szName1;
    		dddd.TrimRight();
    			  m_listC.SetItemText(iItem, 1, dddd);
				  dddd = m_Fans.m_szpointnum2;
    		dddd.TrimRight();
    			  m_listC.SetItemText(iItem, 2, dddd);
				  m_Records2.push_back(dddd);
				  dddd = m_Fans.m_szName2;
    		dddd.TrimRight();
    			  m_listC.SetItemText(iItem, 3, dddd);
            dddd.Format(_T("%d̬"), m_Fans.m_szAStatus);
    			  m_listC.SetItemText(iItem, 4, dddd);
 			m_nSecond = m_Fans.m_szFansID+1;
//            dddd.Format(_T("%d"), m_nSecond-1);
//    			  m_listC.SetItemText(iItem, 5, dddd);
			iItem++;
			m_Fans.MoveNext();
		}
		theApp.InitData();
	}
    else if(chcommand == 0x46)   //�����˹������ʼ��
	{
		     unsigned char nfds = m_VERIFYT.GetCurSel()+1;
        	CString strSQL;
		if(m_SerialF[nfds].SFSd ==0)
		{
        	strSQL.Format("%d�ŷ�վû��Ѳ�죡",nfds);
            AfxMessageBox(strSQL, MB_OK);
         	delete m_ndkSend;
			return;
		}
		for(int i =0; i < 6 ;i++)//�����˹������ϵ����Ĳ������ʱ���Գ�ʼ�����޸�
		{
        	CString strf,strc;
			if(str_list[i].strl =="")
				break;
		    strf = str_list[i].strl.Mid(0,2);
    		strc = str_list[i].strl.Mid(3,2);
    		int nfds = m_Str2Data.String2Int(strf);
     		int nchan = m_Str2Data.String2Int(strc);
			unsigned char nstatus = m_SlaveStation[nfds][nchan].Channel_state;
			if(nstatus == 0x10 || nstatus == 0x20 || nstatus == 0xa0)
			{
            	strSQL.Format("%d�ŷ�վ%s״̬Ϊ%s�����ܳ�ʼ����",nfds,str_list[i].strl,theApp.m_RTDM.strstatus(nstatus));
                AfxMessageBox(strSQL, MB_OK);
            	delete m_ndkSend;
	    		return;
			}
		}
			strSQL.Format("%d�ŷ�վ�����˹������ʼ�����˲�����ɾ��%d�ŷ�վ�����˹�������ã��Ƿ����������",nfds,nfds);
           int Reply = AfxMessageBox(strSQL, MB_YESNO);
           if ( Reply != IDYES )
		   {
            	delete m_ndkSend;
        		return;
		   }
		            m_ndkSend[0] = 0x7E;
		            m_ndkSend[1] = nfds;
		            m_ndkSend[2] = chcommand;
		            m_ndkSend[3] = 0xff;     m_ndkSend[4] = 0xff;     m_ndkSend[5] = 0xff;
		            m_ndkSend[6] = 0xff;     m_ndkSend[7] = 0xff;     m_ndkSend[8] = 0xff;
		            m_ndkSend[9] = 0x21;
                	CNDKMessage message1(WINDGASATRESIA);
					message1.Add(m_ndkSend , 100);
					theApp.Sync(message1,1);

            	for( i =0;i<6;i++)
             		str_list[i].strl="";
            	strSQL.Format("����%d�ŷ�վ�����˹������ʼ����",nfds);
                AfxMessageBox(strSQL, MB_OK);
                g_Log.StatusOut(strSQL);
	}
    else if(chcommand == 0x5A)   //���ϱ�����ʼ��
	{
        	CString strSQL;
			strSQL.Format("���ϱ�����ʼ�����˲�����ɾ��60����վ���ϱ������ã��Ƿ����������");
           int Reply = AfxMessageBox(strSQL, MB_YESNO);
           if ( Reply != IDYES )
		   {
            	delete m_ndkSend;
        		return;
		   }
    	CMainFrame* pFWnd=(CMainFrame*)AfxGetMainWnd();
		pFWnd->n_derr60 =1;
	}
	else if(chcommand == 0x43)       //���ò���ʼ��
	{
		     unsigned char nfds = m_VERIFYT.GetCurSel()+1;
     	CString strim2;
		if(m_SerialF[nfds].SFSd ==0)
		{
        	strim2.Format("%d�ŷ�վû��Ѳ�죡",nfds);
            AfxMessageBox(strim2, MB_OK);
         	delete m_ndkSend;
			return;
		}
			strim2.Format("%d�ŷ�վ������ó�ʼ�����˲�����ɾ��%d�ŷ�վ������ã��Ƿ����������",nfds,nfds);
           int Reply = AfxMessageBox(strim2, MB_YESNO);
           if ( Reply != IDYES )
		   {
            	delete m_ndkSend;
        		return;
		   }
		            m_ndkSend[0] = 0x7E;
		            m_ndkSend[1] = nfds;
		            m_ndkSend[2] = 0x43;
					strim2.Format("%x|%x|%x",m_ndkSend[0],m_ndkSend[1],m_ndkSend[2]);
				ComDisMes(strim2);

        for(int i=1;i<17 ;i++)
		{
		            m_ndkSend[i*10-7] = 0xff;
		            m_ndkSend[i*10-6] = 0xff;      //
		            m_ndkSend[i*10-5] = 0xff;
		            m_ndkSend[i*10-4] = 0xff;      //
		            m_ndkSend[i*10-3] = 0xff;
		            m_ndkSend[i*10-2] = 0xff;      //
		            m_ndkSend[i*10-1] = 0xff;
		            m_ndkSend[i*10] = 0xff;     //
		            m_ndkSend[i*10+1] = 0xff;
		            m_ndkSend[i*10+2] = 0xff;      //

			strim2.Format("%x|%x|%x|%x|%x|%x|%x|%x|%x|%x    %d|%d|%d|%d|%d|%d|%d|%d|%d|%d",m_ndkSend[i*10-7],m_ndkSend[i*10-6],m_ndkSend[i*10-5],m_ndkSend[i*10-4],m_ndkSend[i*10-3],m_ndkSend[i*10-2],m_ndkSend[i*10-1],
				m_ndkSend[i*10],m_ndkSend[i*10+1],m_ndkSend[i*10+2],
				m_ndkSend[i*10-7],m_ndkSend[i*10-6],m_ndkSend[i*10-5],m_ndkSend[i*10-4],m_ndkSend[i*10-3],m_ndkSend[i*10-2],m_ndkSend[i*10-1],
				m_ndkSend[i*10],m_ndkSend[i*10+1],m_ndkSend[i*10+2]);
			ComDisMes(strim2);
		}
		            m_ndkSend[163] = 0xff;      //����������
		            m_ndkSend[164] = 0xff;      //
		            m_ndkSend[165] = 0x21;      //
					strim2.Format("%x|%x|%x",m_ndkSend[163],m_ndkSend[164],m_ndkSend[165]);
    	CNDKMessage message1(SENDCONFIG);
					message1.Add(m_ndkSend , 200);
					theApp.Sync(message1,1);
				ComDisMes(strim2);
		strim2.Format("%d�ŷ�վ����ʼ����",nfds);
        AfxMessageBox(strim2, MB_OK);
       g_Log.StatusOut( strim2 );
	}
	delete m_ndkSend;
}

void CSetTimeDlg::OnItemChangedList(NMHDR *pNMHDR, LRESULT *pResult)
{
  LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);

   CString sTemp;          
  *pResult = 0;

  if ( pNMLV->uNewState == 3 )
  {
	  if(chcommand == 0xf0 && !m_Fans._IsEmpty() ) //
           m_Fans.AbsolutePosition(pNMLV->iItem + 1);
  }
}

void CSetTimeDlg::OnButRESre()
{
    GetDlgItem(IDC_BUT_RES)->ShowWindow(SW_HIDE);
}

void CSetTimeDlg::Save46()
{
}

void CSetTimeDlg::Init5A()
{
     	m_listC.DeleteAllItems();
        if ( m_SControl._IsOpen() )
            m_SControl.Close();
		m_SControl.Create();
		m_SControl.CursorType(adOpenDynamic);
		m_SControl.CacheSize(50);
		m_SControl._SetRecordsetEvents(new CAccountSetEvents);
		m_SControl.Open(_T("Select * From specialcontrol"), &theApp.m_Cn);
		m_SControl.MarshalOptions(adMarshalModifiedOnly);
		int iItem = 0;
		m_SControl.MoveFirst();
		while ( !m_SControl.IsEOF() )
		{
				  CString dddd;
				  dddd.Format("%d",m_SControl.m_szSID);
				  m_listC.InsertItem(iItem, dddd);
				  if(m_SControl.m_szSpeCtrol)
    				  m_listC.SetItemText(iItem, 1, "ʹ��");
				  else
    				  m_listC.SetItemText(iItem, 1, "�ر�");
				  iItem++;
			m_SControl.MoveNext();
		}
		theApp.InitData();
}

void CSetTimeDlg::OnButCancel() 
{
	CMainFrame* pFWnd=(CMainFrame*)AfxGetMainWnd();
   	pFWnd->m_pSetTimeDlg=NULL;
	if(m_nchangev == 0)
	{
		OnClose();
		if(m_nchange == 1000)
		{
			theApp.InitSQLite3();
        	theApp.m_RTDM.InitDisplay();
		}
        EndDialog(IDCANCEL);
	}
	else
        AfxMessageBox("���ȵ�������ť");
}

void CSetTimeDlg::ComDisMes(CString strmes)
{
//        	 m_listC.DeleteAllItems();
        m_listC.InsertItem(m_nSecond, strmes);
//		if(chcommand == 0x46)            //�����˹����
        	m_listC.SetItemText(m_nSecond, 1, strmes);
		m_nSecond++;
}

void CSetTimeDlg::InitWGas(int gasfds)
{
    if ( m_CommonSet._IsOpen() )
       m_CommonSet.Close();
		m_nSecond =  6;
		m_CommonSet.Create();
		m_CommonSet.CursorType(adOpenDynamic);
		m_CommonSet.CacheSize(50);
		m_CommonSet._SetRecordsetEvents(new CAccountSetEvents);
		m_CommonSet.Open(_T("Select * From commonset"), &theApp.m_Cn);
		m_CommonSet.MarshalOptions(adMarshalModifiedOnly);
		unsigned char nfds;
		if(gasfds == 0)
    		nfds= m_VERIFYT.GetCurSel()+1;
		else
    		nfds= gasfds;

		m_CommonSet.MoveFirst();
		while ( !m_CommonSet.IsEOF() )
		{
			int sfds = m_CommonSet.m_szCommonID;
			if(sfds >(nfds*6) && sfds <( (nfds+1)*6+1 ) )
			{
        		CString dddd = m_CommonSet.m_szstrc30;
				dddd.TrimRight();
				str_list[sfds-nfds*6-1].strl = dddd;
			}
			m_CommonSet.MoveNext();
		}

     	m_listC.DeleteAllItems();
	    for (int iItem1 = 2; iItem1 >= 0; iItem1--)
    		m_listC.DeleteColumn(iItem1);

    	m_listC.InsertHiddenLabelColumn();	// Requires one never uses column 0
    	for(int col = 0; col < 2 ; ++col)
		{
		CString title;  int kkk;
		CGridColumnTrait* pTrait = NULL;
		if (col==0)	// Country
		{
			kkk = 200;
			title ="������λ��";
		}
		if (col==1)	// Year won
		{
			int k=0;
			kkk = 250;
			title ="ͨ����";
			CGridColumnTraitCombo* pComboTrait = new CGridColumnTraitCombo;
         	for(int i = 01; i < MAX_CHAN; i++)
			{
         		CString strfds,strtemp,strchan;
				strtemp = m_SlaveStation[nfds][i].WatchName;
				if(strtemp != "")
				{
					int n=i;
					if(i>16)
						n = i-16;
                	strfds.Format(_T("%02d"), nfds);
                	strchan.Format(_T("%02d"), n);
					int n_ptype = m_SlaveStation[nfds][i].ptype;
					if(n_ptype < 3)
					{
                    	pComboTrait->AddItem(k, strfds+"A"+strchan+"|"+strtemp);
					    k++;
					}
					else if(n_ptype==10 || n_ptype==13 ||n_ptype==14)
					{
                    	pComboTrait->AddItem(k, strfds+"D"+strchan+"|"+strtemp);
					    k++;
					}
					else if(n_ptype == 12)
					{
                    	pComboTrait->AddItem(k, strfds+"C"+strchan+"|"+strtemp);
					    k++;
					}
				}
			}
			pTrait = pComboTrait;
		}
		m_listC.InsertColumnTrait(col+1, title, LVCFMT_LEFT, kkk, col, pTrait);
		}

    	for( int iItem = 0; iItem < 6 ; iItem++)
		{
				  m_listC.InsertItem(iItem, "ͨ��");
				  m_listC.SetItemText(iItem, 2, str_list[iItem].strl);
		}
				  m_listC.SetItemText(0, 1, "������˹");
				  m_listC.SetItemText(1, 1, "�ط���˹");
				  m_listC.SetItemText(2, 1, "����ͨ��");
				  m_listC.SetItemText(3, 1, "����");
				  m_listC.SetItemText(4, 1, "��Ͳ����");
				  m_listC.SetItemText(5, 1, "������ͨ��");
}
