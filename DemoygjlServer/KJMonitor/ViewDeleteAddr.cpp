// ViewDeleteAddr.cpp : implementation file
//

#include "stdafx.h"
#include "kjmonitor.h"
#include "ViewDeleteAddr.h"
#include "SQL\\String2DataType.h"
#include  "Sequence\\Spudetailed_me.h"     //  add

#include "comdef.h" 
#include "Others\\Excel9.h" 
#include "CommStatusFM.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CViewDeleteAddr dialog
extern CDatabase	m_Database;


CViewDeleteAddr::CViewDeleteAddr(CWnd* pParent /*=NULL*/)
	: CDialog(CViewDeleteAddr::IDD, pParent)
{
	//{{AFX_DATA_INIT(CViewDeleteAddr)
	m_unEditSearchPoint = 1;
	m_unEditStartPoint = 1;
	m_unEditEndPoint = 1;
	//}}AFX_DATA_INIT
	m_bUnusedAddr=0;
	m_bSearchPoint=FALSE;
	m_unTrunkNo=1;
	m_bExcelInit=false;
}


void CViewDeleteAddr::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CViewDeleteAddr)
	DDX_Control(pDX, IDC_BUTTON_SEQUENCE, m_ctrlBtnSequence);
	DDX_Control(pDX, IDC_BUTTON_ALARM, m_ctrlBtnAlarm);
	DDX_Control(pDX, IDC_BUTTON_DESELECTALL, m_ctrlBtnDeselectAll);
	DDX_Control(pDX, IDC_BUTTON_DESELECT1, m_ctrlBtnDeselect1);
	DDX_Control(pDX, IDC_BUTTON_ADDALL, m_ctrlBtnAddAll);
	DDX_Control(pDX, IDC_BUTTON_ADD1, m_ctrlBtnAdd1);
	DDX_Control(pDX, IDC_BUTTON_REPORT, m_ctrlBtnReport);
	DDX_Control(pDX, IDC_BUTTON_ADD, m_ctrlBtnAdd);
	DDX_Control(pDX, IDC_LIST_REPORTTABLE, m_ctrlListReportTable);
	DDX_Control(pDX, IDC_COMBO_SELECTTRUNK, m_ctrlComboSelectTrunk);
	DDX_Control(pDX, IDC_BUTTON_DELETEADDR, m_ctrlBtnDeleteAddr);
	DDX_Control(pDX, IDC_BUTTON_SEARCHPOINT, m_ctrlBtnSearchPoint);
	DDX_Control(pDX, IDC_BUTTON_DISPUSEDADDR, m_ctrlBtnDispUsedAddr);
	DDX_Control(pDX, IDC_BUTTON_DELETEMULTICONV, m_ctrlBtnDeleteMultiConv);
	DDX_Control(pDX, IDC_BUTTON_DISPUNUSEDADDR, m_ctrlBtnDispUnusedAddr);
	DDX_Control(pDX, IDOK, m_btnOK);
	DDX_Control(pDX, IDC_LIST_ADDR, m_ctrlList);
	DDX_Text(pDX, IDC_EDIT_SEARCHPOINT, m_unEditSearchPoint);
	DDX_Text(pDX, IDC_EDIT_STARTPOINT, m_unEditStartPoint);
	DDX_Text(pDX, IDC_EDIT_ENDPOINT, m_unEditEndPoint);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CViewDeleteAddr, CDialog)
	//{{AFX_MSG_MAP(CViewDeleteAddr)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BUTTON_DISPUSEDADDR, OnButtonDispusedaddr)
	ON_BN_CLICKED(IDC_BUTTON_DISPUNUSEDADDR, OnButtonDispunusedaddr)
///	ON_BN_CLICKED(IDC_BUTTON_DELETEADDR, OnButtonDeleteaddr)
///	ON_BN_CLICKED(IDC_BUTTON_DELETEMULTICONV, OnButtonDeletemulticonv)
	ON_BN_CLICKED(IDC_BUTTON_SEARCHPOINT, OnButtonSearchpoint)
	ON_CBN_SELCHANGE(IDC_COMBO_SELECTTRUNK, OnSelchangeComboSelecttrunk)
///	ON_BN_CLICKED(IDC_BUTTON_REPORT, OnButtonReport)
///	ON_BN_CLICKED(IDC_BUTTON_ADD, OnButtonAdd)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_ADDR, OnDblclkListAddr)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_REPORTTABLE, OnDblclkListReporttable)
	ON_BN_CLICKED(IDC_BUTTON_ADD1, OnButtonAdd1)
	ON_BN_CLICKED(IDC_BUTTON_ADDALL, OnButtonAddall)
	ON_BN_CLICKED(IDC_BUTTON_DESELECT1, OnButtonDeselect1)
	ON_BN_CLICKED(IDC_BUTTON_DESELECTALL, OnButtonDeselectall)
///	ON_BN_CLICKED(IDC_BUTTON_ALARM, OnButtonAlarm)
///	ON_BN_CLICKED(IDC_BUTTON_SEQUENCE, OnButtonSequence)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CViewDeleteAddr message handlers

BOOL CViewDeleteAddr::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	SetButtonStyle();

///	ConnectDB();//�������ݿ�
	if (CoInitialize(NULL)!=0)   //EXCEL
	{ 
		AfxMessageBox("��ʼ��COM֧�ֿ�ʧ��,�޷����EXCEL�������ɽ�����������!");
		m_bExcelInit=false;
		m_ctrlBtnReport.EnableWindow(FALSE);
		m_ctrlBtnSequence.EnableWindow(FALSE);
		m_ctrlBtnAlarm.EnableWindow(FALSE);
	} 
	else
	{
		m_bExcelInit=true;
	}
	
	
	//UpdateData(TRUE);
	if(m_unTrunkNo>0)
		m_ctrlComboSelectTrunk.SetCurSel(m_unTrunkNo-1);
	SetListCtrlTable();
	SetListReportTable();
///	GetDataFromDB();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CViewDeleteAddr::SetButtonStyle()
{
	m_btnOK.SetThemeHelper(&m_ThemeHelper);
	m_btnOK.SetIcon(IDI_ICON_OK);
	m_btnOK.SetTooltipText(_T("�˳�"));

	m_ctrlBtnDispUsedAddr.SetThemeHelper(&m_ThemeHelper);
	m_ctrlBtnDispUsedAddr.SetIcon(IDI_ICON_LEDON);
	m_ctrlBtnDispUsedAddr.SetTooltipText(_T("�г���ǰ�������������õĵ�ַ������ʾ�õ�ַ�ϵ�ת������Ϣ"));


	m_ctrlBtnDeleteAddr.SetThemeHelper(&m_ThemeHelper);
	m_ctrlBtnDeleteAddr.SetIcon(IDI_ICON_CANCEL);
	m_ctrlBtnDeleteAddr.SetTooltipText(_T("ɾ����ѡ��ַ�ϵ�����ת����������Ƕ๦��ת��������ȫ��ɾ��"));

	m_ctrlBtnDeleteMultiConv.SetThemeHelper(&m_ThemeHelper);
	m_ctrlBtnDeleteMultiConv.SetIcon(IDI_ICON_CANCEL);
	m_ctrlBtnDeleteMultiConv.SetTooltipText(_T("ɾ����ѡ���ϵĴ��������๦��ת�����ϵ���������������"));

//	m_ctrlBtnDispNewTrunk.SetThemeHelper(&m_ThemeHelper);
//	m_ctrlBtnDispNewTrunk.SetIcon(IDI_ICON_NEW);
//	m_ctrlBtnDispNewTrunk.SetTooltipText(_T("��������������µĸ��ߺţ�����˰�ť����ʾ�µĸ����ϵ���ʹ�õĵ�ַ��Ϣ"));

	m_ctrlBtnDispUnusedAddr.SetThemeHelper(&m_ThemeHelper);
	m_ctrlBtnDispUnusedAddr.SetIcon(IDI_ICON_LEDOFF);
	m_ctrlBtnDispUnusedAddr.SetTooltipText(_T("��ʾ��ǰ������û��ʹ�õĵ�ַ�ţ����ĳһ��ַ���Ƕ๦��ת���������˵���õ�ַ���ɼӵĴ���������"));
	

	m_ctrlBtnSearchPoint.SetThemeHelper(&m_ThemeHelper);
	m_ctrlBtnSearchPoint.SetIcon(IDI_ICON_SEARCH);
	m_ctrlBtnSearchPoint.SetTooltipText(_T("���ٲ��ҵ����Ϣ�������������������"));

	m_ctrlBtnAdd.SetThemeHelper(&m_ThemeHelper);
	m_ctrlBtnAdd.SetIcon(IDI_ICON_SINGLE1);
	m_ctrlBtnAdd.SetTooltipText(_T("��������2�༭����������ʼ��ź���ֹ��ţ�����˰���ť���ɽ���ʼ������ֹ��֮�������ѱ༭�ĵ���Ϣ���뱨�������������˫����������Ҳ�ɼ���һ��"));
	m_ctrlBtnAdd.SetColor(0,RGB(000,153,000),TRUE);
	m_ctrlBtnAdd.SetColor(1,RGB(255,255,255),TRUE);

	m_ctrlBtnReport.SetThemeHelper(&m_ThemeHelper);
	m_ctrlBtnReport.SetIcon(IDI_ICON_EXCEL);
	m_ctrlBtnReport.SetTooltipText(_T("�����±��γ�EXCEL��񱨱���EXCEL�пɶԲ����б༭����ӡ�������������WORD���ĵ���ע��MS EXCEL������2000����ߵİ汾"));

	m_ctrlBtnAlarm.SetThemeHelper(&m_ThemeHelper);
	m_ctrlBtnAlarm.SetIcon(IDI_ICON_EXCEL);
	m_ctrlBtnAlarm.SetTooltipText(_T("EXCEL��񱨱���EXCEL�пɶԱ�������б༭����ӡ�������������WORD���ĵ���ע��MS EXCEL������2000����ߵİ汾"));

	m_ctrlBtnSequence.SetThemeHelper(&m_ThemeHelper);
	m_ctrlBtnSequence.SetIcon(IDI_ICON_EXCEL);
	m_ctrlBtnSequence.SetTooltipText(_T("EXCEL��񱨱���EXCEL�пɶ�ʱ����б༭����ӡ�������������WORD���ĵ���ע��MS EXCEL������2000����ߵİ汾"));

	m_ctrlBtnAddAll.SetThemeHelper(&m_ThemeHelper);
	m_ctrlBtnAddAll.SetIcon(IDI_ICON_ADD1);
	m_ctrlBtnAddAll.SetTooltipText(_T("����������е�ȫ������"));
	m_ctrlBtnAddAll.SetColor(0,RGB(000,255,000),TRUE);
	m_ctrlBtnAddAll.SetColor(1,RGB(255,255,255),TRUE);

	m_ctrlBtnAdd1.SetThemeHelper(&m_ThemeHelper);
	m_ctrlBtnAdd1.SetIcon(IDI_ICON_ADDSINGLE);
	m_ctrlBtnAdd1.SetTooltipText(_T("���������ѡ��������У��ٵ�����룬˫����������Ҳ�ɼ���"));
	m_ctrlBtnAdd1.SetColor(0,RGB(000,153,000),TRUE);
	m_ctrlBtnAdd1.SetColor(1,RGB(255,255,255),TRUE);
	
	m_ctrlBtnDeselectAll.SetThemeHelper(&m_ThemeHelper);
	m_ctrlBtnDeselectAll.SetIcon(IDI_ICON_ADDDESELECT);
	m_ctrlBtnDeselectAll.SetTooltipText(_T("���ұ������е��ɾ��"));
	m_ctrlBtnDeselectAll.SetColor(0,RGB(255,000,000),TRUE);
	m_ctrlBtnDeselectAll.SetColor(1,RGB(255,255,255),TRUE);

	m_ctrlBtnDeselect1.SetThemeHelper(&m_ThemeHelper);
	m_ctrlBtnDeselect1.SetIcon(IDI_ICON_ADDDESELECT1);
	m_ctrlBtnDeselect1.SetTooltipText(_T("�����ұ���ѡ��������У��ٵ��ɾ����˫����������Ҳ��ɾ��"));
	m_ctrlBtnDeselect1.SetColor(0,RGB(255,051,051),TRUE);
	m_ctrlBtnDeselect1.SetColor(1,RGB(255,255,255),TRUE);

}

void CViewDeleteAddr::ConnectDB()
{
	try
	{
		m_SQLDirect.Init();
		if(m_SQLDirect.Connect(_T("masterdefine"),_T("kj86"),_T("kj86")))
			AfxMessageBox("AddUser:�޷������û��������ݿ�,��ȷ��SQL SERVER�����Ƿ�����!");
	}
	catch(CDBException *e)
	{
		e->ReportError();
		return;
	}
}

void CViewDeleteAddr::GetDataFromDB()
{
	CString strSQL;
	CString2DataType Str2Data;
	BOOL *bUsedAddrNo;
	bUsedAddrNo=new BOOL[MAX_ADDR_NUMBER];
	for(UINT i=0;i<MAX_ADDR_NUMBER;i++)
		*(bUsedAddrNo+i)=FALSE;
 	try
	{
		if(m_bSearchPoint)
			strSQL.Format("SELECT * FROM uPointProperty WHERE unPointNo = %d",m_unEditSearchPoint);
		else
			strSQL.Format("SELECT * FROM uPointProperty WHERE unTrunkNo = %d",m_unTrunkNo);
		if( m_SQLDirect.ExecuteSQL(strSQL)==SQL_SUCCESS)
		{
			int nRet=m_SQLDirect.Fetch();
			if(nRet)
			{
				CString strtemp;
				if(m_bSearchPoint)
				{
					strtemp.Format("�� %d ��û�б༭������",m_unEditSearchPoint);
					AfxMessageBox(strtemp);
					m_bSearchPoint=FALSE;
				}
				//else
				//	strtemp=_T("��ѡ�����ϻ�û�б༭�㣬���е�ַ������");
				
				delete bUsedAddrNo;
				return;
			}
			int iItem=0;
			while(!nRet)
			{
/*	m_ctrlList.InsertColumn(0, _T("��ַ"),   LVCFMT_CENTER, 20);
	m_ctrlList.InsertColumn(1, _T("���"),   LVCFMT_CENTER, 20);
	m_ctrlList.InsertColumn(2, _T("ת��������"), LVCFMT_CENTER, 20);
	m_ctrlList.InsertColumn(3, _T("ɨ��"),   LVCFMT_CENTER, 20);
	m_ctrlList.InsertColumn(4, _T("Ƶ��"),   LVCFMT_CENTER, 20);
	m_ctrlList.InsertColumn(5, _T("������Ϣ"),   LVCFMT_CENTER, 40);
*/

//strSQL=_T("INSERT INTO uPointProperty (unPointNo, unTrunkNo, unAddress, unScanFreq, bScan, bValueType, unConnectorID, unSamePointNumber, bMultiConv) ");
//strSQL=_T("INSERT INTO uAnologPointProperty (unPointNo, fMeasureMin, fMeasureMax, unBitNumber, unWarnCause, unWarnMode, unWarnMinValue, unWarnMaxValue, strUnit, bPrint) ");

				CString strunPointNo=m_SQLDirect.GetCol(1);
				CString strunTrunkNo=m_SQLDirect.GetCol(2);
				CString strunAddress=m_SQLDirect.GetCol(3);
				CString strunScanFreq=m_SQLDirect.GetCol(4);
				CString strbScan=m_SQLDirect.GetCol(5);
				CString strbValueType=m_SQLDirect.GetCol(6);
				CString strunConnectorID=m_SQLDirect.GetCol(7);
				CString strunSamePointNumber=m_SQLDirect.GetCol(8);
				CString strbMultiConv=m_SQLDirect.GetCol(9);
				CString strunConvIDCH = GetConvName(Str2Data.String2Int(strunConnectorID));
				m_ctrlComboSelectTrunk.SetCurSel(Str2Data.String2Int(strunTrunkNo)-1);
				UpdateData(FALSE);
				if(strbScan=="1")
					strbScan="ɨ��";
				else
					strbScan="��ɨ��";
				if(!m_bUnusedAddr)
				{
					m_ctrlList.InsertItem(iItem, strunAddress, 0);
					m_ctrlList.SetItem(iItem, 1, LVIF_TEXT, strunPointNo, 0, NULL, NULL, NULL);
					m_ctrlList.SetItem(iItem, 2, LVIF_TEXT, strunConvIDCH, 0, NULL, NULL, NULL);
					m_ctrlList.SetItem(iItem, 3, LVIF_TEXT, strunConnectorID, 0, NULL, NULL, NULL);
					m_ctrlList.SetItem(iItem, 4, LVIF_TEXT, strbScan, 0, NULL, NULL, NULL);
					m_ctrlList.SetItem(iItem, 5, LVIF_TEXT, strunScanFreq, 0, NULL, NULL, NULL);
				//	m_ctrlList.SetItem(iItem, 5, LVIF_TEXT, strLogoff, 0, NULL, NULL, NULL);
				}
				*(bUsedAddrNo+Str2Data.String2Int(strunAddress))=TRUE;
				nRet=m_SQLDirect.Fetch();
				iItem++;
			}
		}
		if(m_bUnusedAddr)
		{
			UINT iItem=0;
			for(i=0;i<MAX_ADDR_NUMBER;i++)
			{
				if(!(*(bUsedAddrNo+i)))
				{
					m_ctrlList.InsertItem(iItem, Str2Data.Int2CString(i), 0);
					iItem++;
				}
			}
			m_bUnusedAddr=FALSE;
		}
	}
	catch(CDBException *e){
	e->ReportError();
	delete bUsedAddrNo;
	m_bSearchPoint=FALSE;
	return;
	}

	// initialize the back color picker default colors.
	m_cpBack.SetColor(RGB(0x33,0x66,0xff));
	m_cpBack.SetDefaultColor(m_clrRowBack);

	// initialize the text color picker default colors.
	m_cpText.SetColor(RGB(0xff,0xff,0xff));
	m_cpText.SetDefaultColor(m_clrRowText);

	// set the text and back colors for the list control.
	m_ctrlList.SetRowColors(m_cpText.GetColor(), m_cpBack.GetColor());

	m_ctrlList.AutoSizeColumn ();
	m_bSearchPoint=FALSE;
	delete bUsedAddrNo;
}

void CViewDeleteAddr::OnDestroy() 
{
	CDialog::OnDestroy();
	
	// TODO: Add your message handler code here
	m_SQLDirect.Close();
	if(m_bExcelInit)
		CoUninitialize();  //EXCEL

	
}

/*
#define MS8IN_B38  	      1    //M0  
#define MS5OUT_B25  	  2     //M1
#define MA4IN             3     //M3
#define MP16IN            4     //M4
#define A1IN8BIT_CH4ICO  5      //CH4     
#define A1IN8BIT_A50     6
#define A8IN8BIT_MCA     7
#define A8IN8BIT_MC8     8
#define A1OUT8BIT_C35    9
#define P16IN            10     //pulse 16 channel
#define S8IN_B38  	     11     //M0
#define S8OUT_B48        12     //
#define S5OUT_B25  	     13     //M1
#define MULTICONV        14 
*/

/*
#define MS8IN_B38  	      1     //M0    //��ӦS8IN_B38  -----------11 ����   
#define MS5OUT_B25  	  2     //M1    //��ӦS5OUT_B25  ----------13 ����
#define MA4IN             3     //M3    //��Ӧ4-A50---              3  ����
#define MP16IN            4     //M4    //��ӦP16IN  --------------10 ����
#define A1IN8BIT_CH4ICO  5      //CH4 //1. ICO-�����ͼ���/һ����̼������[8λ1·]    
#define A1IN8BIT_A50     6      //      2. A50-A�͵�·ģ���������ź�ת����[8λ1·]
#define A8IN8BIT_MCA     7      //      3. MCA-8·ģ���������ź�ת����[12λ8·]
#define A8IN8BIT_MC8     8      //      4. MC8-8·ģ���������ź�ת����[8λ8·]
#define A1OUT8BIT_C35    9      //      5. C35-ģ��������ź�ת����(C3-C5)[6λ]
#define P16IN            10     //      6. ��D1-������������ۼ���[16λ]

//#define MA4IN  ͬ3                      7. ��4-A50ģ���������ź�ת����[8λ4·]

#define S8IN_B38  	     11     //M0    1. B38-����������[8·]
#define S8OUT_B48        12     //      2. B48-���������[8·]
#define S5OUT_B25  	     13     //M1    3. B25-���������[5·]

#define MULTICONV        14   
*/


CString CViewDeleteAddr::GetConvName(UINT unConvID)
{
	CString strConvName=_T("");
	switch(unConvID)
	{
	case MS8IN_B38:  //1. B38-����������[8·]
		strConvName=_T("8·����(��)");
		break;
	case MS5OUT_B25:  //2. B25-���������[5·]
		strConvName=_T("5·����(��)");
		break;
	case MA4IN:  //3. 4-A50����
		strConvName=_T("4·8λģ��(��)");
		break;
	case MP16IN:  //4. D1-������������ۼ���[16λ]����
		strConvName=_T("�����������(��)");
		break;
	case A1IN8BIT_CH4ICO:  //5. ICO-�����ͼ���/һ����̼������[8λ1·]����/һ����̼
		strConvName=_T("1·8λICO");
		break;
	case A1IN8BIT_A50:    // 6. A50-A�͵�·ģ���������ź�ת����[8λ1·]
		strConvName=_T("1·8λģ��");
		break;
	case  A8IN8BIT_MCA:    //7. MCA-8·ģ���������ź�ת����[12λ8·]
		strConvName=_T("8·12λģ��");
		break;
	case A8IN8BIT_MC8 :   //8  MC8-8·ģ���������ź�ת����[8λ8·]
		strConvName=_T("8·8λģ��");
		break;
	case A1OUT8BIT_C35 :  //9. C35-ģ��������ź�ת����(C3-C5)[6λ]
		strConvName=_T("1·6λģ��");
		break;
	case A4IN:  //15. 4-A50                                    //  2003/8/12
		strConvName=_T("4·8λģ��");
		break;
	case P16IN :         // 10 ��D1-������������ۼ���[16λ]
		strConvName=_T("�����������");
		break;
	case S8IN_B38:  	   //11. B38-����������[8·]
		strConvName=_T("8·����");
		break;
	case S8OUT_B48:    // 12. B48-���������[8·]
		strConvName=_T("8·����");
		break;
	case S5OUT_B25:  //13 . B25-���������[5·]
		strConvName=_T("5·����");
		break;
	default:
		break;
	}
	return strConvName;
}

//void CViewDeleteAddr::OnButtonDispnewtrunk() 
//{
	// TODO: Add your control notification handler code here

//}

void CViewDeleteAddr::OnButtonDispusedaddr() 
{
	// TODO: Add your control notification handler code here
	OnSelchangeComboSelecttrunk();
}

void CViewDeleteAddr::OnButtonDispunusedaddr() 
{
	// TODO: Add your control notification handler code here
	m_ctrlList.DeleteAllItems();
	m_bUnusedAddr=TRUE;
///	GetDataFromDB();

	// initialize the back color picker default colors.
	m_cpBack.SetColor(RGB(0xFF,0xFF,0xFF));
	m_cpBack.SetDefaultColor(m_clrRowBack);

	// initialize the text color picker default colors.
	m_cpText.SetColor(RGB(0x33,0x66,0xff));
	m_cpText.SetDefaultColor(m_clrRowText);

	// set the text and back colors for the list control.
	m_ctrlList.SetRowColors(m_cpText.GetColor(), m_cpBack.GetColor());

	
}

void CViewDeleteAddr::OnButtonDeleteaddr() 
{
	BOOL bDelete=0;
	CString2DataType Str2Data;
	UINT unPointNumonAddr[MAX_POINT_ON_ADDR],bPointValue[MAX_POINT_ON_ADDR],unPointNum;
	for(UINT i=0;i<MAX_POINT_ON_ADDR;i++)
	{
		unPointNumonAddr[i]=0;
		bPointValue[i]=0;
	}
	unPointNum=0;
	int nItemCount=m_ctrlList.GetItemCount();
    for(int nItem=0;nItem<nItemCount;nItem++)
	{
		if(m_ctrlList.GetItemState(nItem,LVIS_SELECTED) & LVIS_SELECTED)
		{
			CString strSQL,strtemp,strMessage,strSQL1;
			strtemp=m_ctrlList.GetItemText(nItem,0);
			strMessage.Format("�϶�Ҫ�ӵ�ַ��ɾ����ַ %s ��?�����ȷ����ʹ�øõ�ַ������ת������Ϣ����Ӳ�������ɾ����",strtemp);
			if(AfxMessageBox(strMessage, MB_ICONQUESTION |MB_OKCANCEL)==IDCANCEL)
			{
				return;
			}
			try
			{
				strSQL.Format("SELECT * FROM uPointProperty WHERE  (unTrunkNo=%d) AND (unAddress =%s)",m_unTrunkNo,strtemp);
				if( m_SQLDirect.ExecuteSQL(strSQL)==SQL_SUCCESS)
				{
					int nRet=m_SQLDirect.Fetch();
					while(!nRet)
					{
						unPointNumonAddr[unPointNum]=Str2Data.String2Int(m_SQLDirect.GetCol(1));
						bPointValue[unPointNum]=Str2Data.Str2Bool(m_SQLDirect.GetCol(6));
						unPointNum++;
						nRet=m_SQLDirect.Fetch();
					}
				}
//				CString strnn;
//				strnn.Format("unPointNum=%d",unPointNum);
//				AfxMessageBox(strnn);
				for(UINT i=0;i<unPointNum;i++)
				{
					if(bPointValue[i])
						strSQL1.Format("DELETE FROM uAnologPointProperty WHERE unPointNo=%d",unPointNumonAddr[i]);
					else
						strSQL1.Format("DELETE FROM uSwitchPointProperty WHERE unPointNo=%d",unPointNumonAddr[i]);
					if(m_SQLDirect.ExecuteSQL(strSQL1)!=SQL_SUCCESS)
					{
						AfxMessageBox("ɾ��ʧ�ܣ���ͨ��SQL SERVER ��ҵ�������鿴����");
					}
					else
					{
						//��ӵĴ��루һ�У�
						theApp.OnSendSQL(strSQL1);
						strSQL1.Format("DELETE FROM uMonitorPointEdit WHERE (unPointNo = %d)",unPointNumonAddr[i]);
						if(m_SQLDirect.ExecuteSQL(strSQL1)!=SQL_SUCCESS)
						{
							AfxMessageBox("ɾ��uMonitorPointEditʧ�ܣ���ͨ��SQL SERVER ��ҵ�������鿴����");
						}
						else	//��ӵĴ���
							theApp.OnSendSQL(strSQL1);
					}
				}
				strSQL.Format("DELETE FROM uPointProperty WHERE (unTrunkNo=%d) AND (unAddress =%s)",m_unTrunkNo,strtemp);
				if(m_SQLDirect.ExecuteSQL(strSQL)!=SQL_SUCCESS)
				{
					AfxMessageBox("ɾ��ʧ�ܣ���ͨ��SQL SERVER ��ҵ�������鿴����");
				}
				else
				{
					//��ӵĴ���
					theApp.OnSendSQL(strSQL);
					RebuildScanQue();
				}
			}
			catch(CDBException *e){
			e->ReportError();
			return;
			}
			bDelete=1;
			break;
		}
	}
	if(!bDelete)
		AfxMessageBox("��û��ѡ��Ҫɾ�����û�(��ʾ�������/���̷����ѡ��Ҫɾ������)");
	else
	{
		m_ctrlList.DeleteAllItems();
///		GetDataFromDB();
	}
}

void CViewDeleteAddr::OnButtonDeletemulticonv() 
{
	// TODO: Add your control notification handler code here
	BOOL bDelete=0;
	CString2DataType Str2Data;
	UINT unPointNumonAddr[MAX_POINT_ON_ADDR],bPointValue[MAX_POINT_ON_ADDR],unPointNum;
	for(UINT i=0;i<MAX_POINT_ON_ADDR;i++)
	{
		unPointNumonAddr[i]=0;
		bPointValue[i]=0;
	}
	unPointNum=0;
	int nItemCount=m_ctrlList.GetItemCount();
    for(int nItem=0;nItem<nItemCount;nItem++)
	{
		if(m_ctrlList.GetItemState(nItem,LVIS_SELECTED) & LVIS_SELECTED)
		{
			CString strSQL,strtemp,strtemp1,strtemp2,strMessage,strSQL1;
			strtemp=m_ctrlList.GetItemText(nItem,0);
			strtemp1=m_ctrlList.GetItemText(nItem,2);
			strtemp2=m_ctrlList.GetItemText(nItem,3);
			strMessage.Format("�϶�Ҫ�ӵ�ַ��ɾ��λ�ڵ�ַ %s �϶๦��ת�����ϵ� %s ��?�����ȷ��������Ϣ����Ӳ�������ɾ����",strtemp,strtemp1);
			if(AfxMessageBox(strMessage, MB_ICONQUESTION |MB_OKCANCEL)==IDCANCEL)
			{
				return;
			}
			try
			{
				strSQL.Format("SELECT * FROM uPointProperty WHERE  (unTrunkNo=%d) AND (unAddress =%s) AND (unConnectorID=%s)",m_unTrunkNo,strtemp,strtemp2);
				if( m_SQLDirect.ExecuteSQL(strSQL)==SQL_SUCCESS)
				{
					int nRet=m_SQLDirect.Fetch();
					while(!nRet)
					{
						unPointNumonAddr[unPointNum]=Str2Data.String2Int(m_SQLDirect.GetCol(1));
						bPointValue[unPointNum]=Str2Data.Str2Bool(m_SQLDirect.GetCol(6));
						unPointNum++;
						nRet=m_SQLDirect.Fetch();
					}
				}
				//CString strnn;
				//strnn.Format("unPointNum=%d",unPointNum);
				//AfxMessageBox(strnn);
				for(UINT i=0;i<unPointNum;i++)
				{
					if(bPointValue[i])
						strSQL1.Format("DELETE FROM uAnologPointProperty WHERE unPointNo=%d",unPointNumonAddr[i]);
					else
						strSQL1.Format("DELETE FROM uSwitchPointProperty WHERE unPointNo=%d",unPointNumonAddr[i]);
					if(m_SQLDirect.ExecuteSQL(strSQL1)!=SQL_SUCCESS)
					{
						AfxMessageBox("ɾ��uAnologPointProperty/uSwitchPointPropertyʧ�ܣ���ͨ��SQL SERVER ��ҵ�������鿴����");
					}
					else
					{
						//��ӵĴ���
						theApp.OnSendSQL(strSQL1);
						strSQL1.Format("DELETE FROM uMonitorPointEdit WHERE (unPointNo = %d)",unPointNumonAddr[i]);
						if(m_SQLDirect.ExecuteSQL(strSQL1)!=SQL_SUCCESS)
						{
							AfxMessageBox("ɾ��uMonitorPointEditʧ�ܣ���ͨ��SQL SERVER ��ҵ�������鿴����");
						}
						else		//��ӵĴ���
							theApp.OnSendSQL(strSQL1);
					}
				}
				strSQL.Format("DELETE FROM uPointProperty WHERE (unTrunkNo=%d) AND (unAddress =%s) AND (unConnectorID=%s)",m_unTrunkNo,strtemp,strtemp2);
				if(m_SQLDirect.ExecuteSQL(strSQL)!=SQL_SUCCESS)
				{
					AfxMessageBox("ɾ��uPointPropertyʧ�ܣ���ͨ��SQL SERVER ��ҵ�������鿴����");
				}
				else
				{
					//��ӵĴ���
					theApp.OnSendSQL(strSQL);
					RebuildScanQue();
				}
			}
			catch(CDBException *e){
			e->ReportError();
			return;
			}
			bDelete=1;
			break;
		}
	}
	if(!bDelete)
		AfxMessageBox("��û��ѡ��Ҫɾ�����û�(��ʾ�������/���̷����ѡ��Ҫɾ������)");
	else
	{
		m_ctrlList.DeleteAllItems();
///		GetDataFromDB();
	}

	
}




void CViewDeleteAddr::OnButtonSearchpoint() 
{
	// TODO: Add your control notification handler code here
	m_ctrlList.DeleteAllItems();
	
	UpdateData(TRUE);
	if((m_unEditSearchPoint<1)||(m_unEditSearchPoint>MAX_POINT_NUMBER-1))
	{
		CString strtemp;
		strtemp.Format("���Ӧ������0--%d֮�䣬����������",MAX_POINT_NUMBER-1);
		AfxMessageBox(strtemp);
		return;
	}
	m_bSearchPoint=TRUE;
///	GetDataFromDB();
}
/*	m_ctrlList.InsertColumn(0, _T("��ַ"),   LVCFMT_CENTER, 20);
	m_ctrlList.InsertColumn(1, _T("���"),   LVCFMT_CENTER, 20);
	m_ctrlList.InsertColumn(2, _T("ת��������"), LVCFMT_CENTER, 20);
	m_ctrlList.InsertColumn(3, _T("ɨ��"),   LVCFMT_CENTER, 20);
	m_ctrlList.InsertColumn(4, _T("Ƶ��"),   LVCFMT_CENTER, 20);
	m_ctrlList.InsertColumn(5, _T("������Ϣ"),   LVCFMT_CENTER, 40);
*/





void CViewDeleteAddr::SetListCtrlTable()
{
	m_ctrlList.InsertColumn(0, _T("��ַ"),   LVCFMT_CENTER, 20);
	m_ctrlList.InsertColumn(1, _T("���"),   LVCFMT_CENTER, 20);
	m_ctrlList.InsertColumn(2, _T("ת��������"), LVCFMT_CENTER, 40);
	m_ctrlList.InsertColumn(3, _T("ID"), LVCFMT_CENTER, 10);
	m_ctrlList.InsertColumn(4, _T("ɨ��"),   LVCFMT_CENTER, 10);
	m_ctrlList.InsertColumn(5, _T("Ƶ��"),   LVCFMT_CENTER, 10);
	m_ctrlList.InsertColumn(6, _T("������Ϣ"),   LVCFMT_CENTER, 40);
	// set some extnded styles
	m_ctrlList.SetExtendedStyle (LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT|LVS_EX_FLATSB);

	// Get the windows handle to the header control for the
	// list control then subclass the control.
	HWND hWndHeader = m_ctrlList.GetDlgItem(IDC_LIST_ADDR)->GetSafeHwnd();
	m_flatHeader.SubclassWindow (hWndHeader);

//	if (m_bSaveColumnWidth)
//		m_ctrlList.LoadColumnWidths();

	// size to fit the columns
	m_ctrlList.AutoSizeColumn ();

	// initialize the back color picker default colors.
	m_cpBack.SetColor(RGB(0x33,0x66,0xff));
	m_cpBack.SetDefaultColor(m_clrRowBack);

	// initialize the text color picker default colors.
	m_cpText.SetColor(RGB(0xff,0xff,0xff));
	m_cpText.SetDefaultColor(m_clrRowText);

	// set the text and back colors for the list control.
	m_ctrlList.SetRowColors(m_cpText.GetColor(), m_cpBack.GetColor());

	m_bAscending=TRUE;
	m_nSortedCol=0;

	m_flatHeader.SetSortImage (m_nSortedCol, m_bAscending);

			// TODO: Add your sorting code here.
	CXTSortClass csc (&m_ctrlList, m_nSortedCol);
	csc.Sort (m_bAscending ? true : false, DT_INT);



}

void CViewDeleteAddr::SetListReportTable()
{
	m_ctrlListReportTable.InsertColumn(0, _T("���"),   LVCFMT_CENTER, 20);
	m_ctrlListReportTable.InsertColumn(1, _T("����"),   LVCFMT_CENTER, 20);
	m_ctrlListReportTable.InsertColumn(2, _T("��ַ"), LVCFMT_CENTER, 40);
	// set some extnded styles
	m_ctrlListReportTable.SetExtendedStyle (LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT|LVS_EX_FLATSB);

	// Get the windows handle to the header control for the
	// list control then subclass the control.
	HWND hWndHeader = m_ctrlListReportTable.GetDlgItem(IDC_LIST_REPORTTABLE)->GetSafeHwnd();
	m_flatHeader.SubclassWindow (hWndHeader);

//	if (m_bSaveColumnWidth)
//		m_ctrlListReportTable.LoadColumnWidths();

	// size to fit the columns
	m_ctrlListReportTable.AutoSizeColumn ();

	// initialize the back color picker default colors.
	m_cpBack.SetColor(RGB(255,255,204));
	m_cpBack.SetDefaultColor(m_clrRowBack);

	// initialize the text color picker default colors.
	m_cpText.SetColor(RGB(0x00,0x00,0x00));
	m_cpText.SetDefaultColor(m_clrRowText);

	// set the text and back colors for the list control.
	m_ctrlListReportTable.SetRowColors(m_cpText.GetColor(), m_cpBack.GetColor());

	m_bAscending=TRUE;
	m_nSortedCol=0;

	m_flatHeader.SetSortImage (m_nSortedCol, m_bAscending);

			// TODO: Add your sorting code here.
	CXTSortClass csc (&m_ctrlListReportTable, m_nSortedCol);
	csc.Sort (m_bAscending ? true : false, DT_INT);

}


void CViewDeleteAddr::OnSelchangeComboSelecttrunk() 
{
	// TODO: Add your control notification handler code here
	  
	m_ctrlList.DeleteAllItems();
	UpdateData(TRUE);
	m_unTrunkNo=m_ctrlComboSelectTrunk.GetCurSel()+1;
///	GetDataFromDB();
	
}


BOOL CViewDeleteAddr::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult) 
{
	// TODO: Add your specialized code here and/or call the base class
	HD_NOTIFY *pHDNotify = (HD_NOTIFY*)lParam;

	switch( pHDNotify->hdr.code )
	{
	case HDN_ITEMCLICKA:
	case HDN_ITEMCLICKW:
		{
			// left mouse button.
			if (pHDNotify->iButton == 0)
			{
				if (pHDNotify->iItem == m_nSortedCol) 
				{
					m_bAscending = !m_bAscending;
				}
				else 
				{
					m_bAscending = true;
				}
			}

			// right mouse button.
			else if (pHDNotify->iButton == 1) 	
			{
				m_bAscending = m_flatHeader.GetAscending();
			}

			else 
			{
				break;
			}

			// set sort image for header.
			m_nSortedCol = pHDNotify->iItem;
			m_flatHeader.SetSortImage (m_nSortedCol, m_bAscending);

			// TODO: Add your sorting code here.
			CXTSortClass csc (&m_ctrlList, m_nSortedCol);
			if((m_nSortedCol==4)||(m_nSortedCol==2))
				csc.Sort (m_bAscending ? true : false, DT_STRING);
			else
				csc.Sort (m_bAscending ? true : false, DT_INT);

			CXTSortClass csc1 (&m_ctrlListReportTable, m_nSortedCol);
			csc1.Sort (m_bAscending ? true : false, DT_INT);
		}
	}

	
	return CDialog::OnNotify(wParam, lParam, pResult);
}


void CViewDeleteAddr::OnButtonReport() 
{
	// TODO: Add your control notification handler code here
	if(!m_bExcelInit)
	{
		AfxMessageBox("�޷���ʼ��EXCEL������ȷ���Ƿ�װ��MS EXCEL[2000���ϰ汾]");
		return;
	}

	_Application ExcelApp; 
	Workbooks wbsMyBooks; 
	_Workbook wbMyBook; 
	Worksheets wssMysheets; 
	_Worksheet wsMysheet; 
	Range rgMyRge; 
	//����Excel 2000������(����Excel) 
 
	if (!ExcelApp.CreateDispatch("Excel.Application",NULL)) 
	{ 
		AfxMessageBox("����Excel����ʧ��!"); 
		return; 
	} 
	//����ģ���ļ��������ĵ� 
	wbsMyBooks.AttachDispatch(ExcelApp.GetWorkbooks(),true); 

	//�õ������·��

	CString strXltPath;
	strXltPath=GetAppPath();
	//AfxMessageBox(strXltPath);

	strXltPath+="ReportXLT\\template1.xlt";
	//CreateDirectory( str1, NULL );
//	if(!SetCurrentDirectory(str1))
//		AfxMessageBox("����template1.xlt�ļ���ʧ�� setcurrentdirectory");

	wbMyBook.AttachDispatch(wbsMyBooks.Add(_variant_t(strXltPath))); 
	//�õ�Worksheets 
	wssMysheets.AttachDispatch(wbMyBook.GetWorksheets(),true); 
	//�õ�sheet1 
	wsMysheet.AttachDispatch(wssMysheets.GetItem(_variant_t("sheet1")),true); 
	//�õ�ȫ��Cells����ʱ,rgMyRge��cells�ļ��� 
	rgMyRge.AttachDispatch(wsMysheet.GetCells(),true); 

	//����1��1�еĵ�Ԫ��ֵ 

	int iExcelRow=1;
	int iExcelCollum=0; 

	CString strSQL,strPointNo;
	CString2DataType Str2Data;
 	try
	{
		int nItemCount1=m_ctrlListReportTable.GetItemCount();
		for(int iListItem=0; iListItem<nItemCount1; iListItem++)
		{
			strPointNo=m_ctrlListReportTable.GetItemText(iListItem,0);
			strSQL.Format("SELECT * FROM uPointProperty WHERE unPointNo = %s ",strPointNo);
			
			if( m_SQLDirect.ExecuteSQL(strSQL)==SQL_SUCCESS)
			{
				int nRet=m_SQLDirect.Fetch();
				if(!nRet)
				{
					CString strunPointNo=m_SQLDirect.GetCol(1);
					CString strunTrunkNo=m_SQLDirect.GetCol(2);
					CString strunAddress=m_SQLDirect.GetCol(3);
					CString strunScanFreq=m_SQLDirect.GetCol(4);
					CString strbScan=m_SQLDirect.GetCol(5);
					CString strbValueType=m_SQLDirect.GetCol(6);
					CString strunConnectorID=m_SQLDirect.GetCol(7);
					CString strunSamePointNumber=m_SQLDirect.GetCol(8);
					CString strbMultiConv=m_SQLDirect.GetCol(9);
					CString strstrLabel=m_SQLDirect.GetCol(10);            //��ǩ����
					CString strstrExplain=m_SQLDirect.GetCol(11);         //��������˵��
					CString strunChannel=m_SQLDirect.GetCol(12);          //ͨ����

					CString strunConvIDCH = GetConvName(Str2Data.String2Int(strunConnectorID));
					
					if(strbScan=="1")
						strbScan="ɨ��";
					else
						strbScan="��ɨ��";

					iExcelRow++;
					//1     2           3       4       5           6       7       8           9
					//���	��ǩ	����	��ַ	ת��������	ͨ��	ɨ��	Ƶ��	������Ϣ
					rgMyRge.SetItem(_variant_t((long)iExcelRow),_variant_t((long)1),_variant_t(strunPointNo)); 
					rgMyRge.SetItem(_variant_t((long)iExcelRow),_variant_t((long)2),_variant_t(strstrLabel)); 
					rgMyRge.SetItem(_variant_t((long)iExcelRow),_variant_t((long)3),_variant_t(strstrExplain)); 
					rgMyRge.SetItem(_variant_t((long)iExcelRow),_variant_t((long)4),_variant_t(strunTrunkNo)); 
					rgMyRge.SetItem(_variant_t((long)iExcelRow),_variant_t((long)5),_variant_t(strunAddress)); 
					rgMyRge.SetItem(_variant_t((long)iExcelRow),_variant_t((long)6),_variant_t(strunConvIDCH)); 
					rgMyRge.SetItem(_variant_t((long)iExcelRow),_variant_t((long)7),_variant_t(strunChannel)); 
					rgMyRge.SetItem(_variant_t((long)iExcelRow),_variant_t((long)8),_variant_t(strbScan)); 
					rgMyRge.SetItem(_variant_t((long)iExcelRow),_variant_t((long)9),_variant_t(strunScanFreq)); 
					//rgMyRge.SetItem(_variant_t((long)iExcelRow),_variant_t((long)9),_variant_t(strunAddress)); 
					//rgMyRge.SetItem(_variant_t((long)iExcelRow),_variant_t((long)10),_variant_t(strunScanFreq)); 
				}
							
			}
		}
	}
	catch(CDBException *e){
	e->ReportError();
	return;
	}

	//rgMyRge.SetItem(_variant_t((long)2),_variant_t((long)1),_variant_t("����ΰ")); 
	//rgMyRge.SetItem(_variant_t((long)20),_variant_t((long)3),_variant_t("ewerwr")); 
	//�õ����е��� 
/*	rgMyRge.AttachDispatch(wsMysheet.GetColumns(),true); 
	//�õ���һ�� 
	for(int iCollum=1;iCollum<=9;iCollum++)
	{
		int iWidth;
		if(iCollum==5)
			iWidth=20;
		else
			iWidth=10;
		rgMyRge.AttachDispatch(rgMyRge.GetItem(_variant_t((long)iCollum),vtMissing).pdispVal,true); 
		//�����п� 
		rgMyRge.SetColumnWidth(_variant_t((long)iWidth)); 
	}
*/
	/*
	//����ģ����Ԥ�ȴ�ŵĺ� 
	ExcelApp.Run(_variant_t("CopyRow"),_variant_t((long)10),vtMissing,vtMissing, 
	vtMissing,vtMissing,vtMissing,vtMissing,vtMissing,vtMissing,vtMissing, 
	vtMissing,vtMissing,vtMissing,vtMissing,vtMissing,vtMissing,vtMissing, 
	vtMissing,vtMissing,vtMissing,vtMissing,vtMissing,vtMissing,vtMissing, 
	vtMissing,vtMissing,vtMissing,vtMissing,vtMissing,vtMissing); 
	*/
	  //��ӡԤ�� 
	wbMyBook.SetSaved(true); 
	ExcelApp.SetVisible(true); 
	//wbMyBook.PrintPreview(_variant_t(false)); 
	//�ͷŶ��� 
	rgMyRge.ReleaseDispatch(); 
	wsMysheet.ReleaseDispatch(); 
	wssMysheets.ReleaseDispatch(); 
	wbMyBook.ReleaseDispatch(); 
	wbsMyBooks.ReleaseDispatch(); 
	ExcelApp.ReleaseDispatch(); 

}

void CViewDeleteAddr::OnButtonAdd() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if(m_unEditStartPoint>m_unEditEndPoint)
	{
		AfxMessageBox("��ʼ��Ų��ܴ�����ֹ���");
		return;
	}
	if((m_unEditStartPoint<1)||(m_unEditEndPoint>MAX_POINT_NUMBER-1))
	{
		CString str;
		str.Format("��ʼ��Ų���С��1����ֹ��Ų��ܴ���%d",MAX_POINT_NUMBER-1);
		AfxMessageBox(str);
		return;
	}

	CString strSQL;
	CString2DataType Str2Data;
 	try
	{
		strSQL.Format("SELECT * FROM uPointProperty WHERE (unPointNo >= %d) AND (unPointNo <= %d)",
			m_unEditStartPoint,m_unEditEndPoint);
		if( m_SQLDirect.ExecuteSQL(strSQL)==SQL_SUCCESS)
		{
			int nRet=m_SQLDirect.Fetch();
			int iItem=m_ctrlListReportTable.GetItemCount();
			//int iItem=0;
			while(!nRet)
			{
				CString strunPointNo=m_SQLDirect.GetCol(1);
				/*CString strunTrunkNo=m_SQLDirect.GetCol(2);
				CString strunAddress=m_SQLDirect.GetCol(3);
				CString strunScanFreq=m_SQLDirect.GetCol(4);
				CString strbScan=m_SQLDirect.GetCol(5);
				CString strbValueType=m_SQLDirect.GetCol(6);
				CString strunConnectorID=m_SQLDirect.GetCol(7);
				CString strunSamePointNumber=m_SQLDirect.GetCol(8);
				CString strbMultiConv=m_SQLDirect.GetCol(9);
				CString strunConvIDCH = GetConvName(Str2Data.String2Int(strunConnectorID));
				
				if(strbScan=="1")
					strbScan="ɨ��";
				else
					strbScan="��ɨ��";*/
				BOOL bExist=FALSE;
				for(int j=0; j<iItem; j++)
				{
					if(strunPointNo==m_ctrlListReportTable.GetItemText(j,0))
					{
						bExist=TRUE;
						break;
					}
				}
				if(!bExist)
					m_ctrlListReportTable.InsertItem(iItem, strunPointNo, 0);
				//m_ctrlListReportTable.SetItem(iItem, 1, LVIF_TEXT, strunPointNo, 0, NULL, NULL, NULL);
				//m_ctrlListReportTable.SetItem(iItem, 2, LVIF_TEXT, strunConvIDCH, 0, NULL, NULL, NULL);
				//m_ctrlListReportTable.SetItem(iItem, 3, LVIF_TEXT, strunConnectorID, 0, NULL, NULL, NULL);
				//m_ctrlListReportTable.SetItem(iItem, 4, LVIF_TEXT, strbScan, 0, NULL, NULL, NULL);
				//m_ctrlListReportTable.SetItem(iItem, 5, LVIF_TEXT, strunScanFreq, 0, NULL, NULL, NULL);
				nRet=m_SQLDirect.Fetch();
				iItem++;
			}
		}
	}
	catch(CDBException *e){
	e->ReportError();
	return;
	}

}

void CViewDeleteAddr::OnDblclkListAddr(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	OnButtonAdd1() ;
	*pResult = 0;
}

void CViewDeleteAddr::OnDblclkListReporttable(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	OnButtonDeselect1();
	*pResult = 0;
}

void CViewDeleteAddr::OnButtonAdd1() 
{
	// TODO: Add your control notification handler code here
	int nItemCount=m_ctrlList.GetItemCount();
	//CString2DataType Str2Data;
    for(int nItem=0;nItem<nItemCount;nItem++)
	{
		if(m_ctrlList.GetItemState(nItem,LVIS_SELECTED) & LVIS_SELECTED)
		{
			CString strPointNo=m_ctrlList.GetItemText(nItem,1);

			int nItemCount1=m_ctrlListReportTable.GetItemCount();
			BOOL bExist=FALSE;
			for(int j=0; j<nItemCount1; j++)
			{
				if(strPointNo==m_ctrlListReportTable.GetItemText(j,0))
				{
					bExist=TRUE;
					break;
					//CString strtemp;
					//strtemp.Format("�� %s �Ѿ��ڿ��Ʊ���",strPointNo);
					//AfxMessageBox(strtemp);
					//return;
				}
			}

			if(!bExist)
			{
				m_ctrlListReportTable.InsertItem(nItemCount1, strPointNo, 0);
			//	CString strExplain=m_ctrlList.GetItemText(nItem,4);
			//	m_ctrlListReportTable.SetItem(nItemCount1, 1, LVIF_TEXT, strExplain, NULL, NULL,NULL,NULL);//NULL, NULL, NULL);
			//	m_ctrlListReportTable.SetItemText(nItemCount1, 1,strExplain);

			}
		}
	}
}

void CViewDeleteAddr::OnButtonAddall() 
{
	// TODO: Add your control notification handler code here
	int nItemCount=m_ctrlList.GetItemCount();
	//CString2DataType Str2Data;
    for(int nItem=0;nItem<nItemCount;nItem++)
	{
		CString strPointNo=m_ctrlList.GetItemText(nItem,1);
		int nItemCount1=m_ctrlListReportTable.GetItemCount();
		BOOL bExist=FALSE;
		for(int j=0; j<nItemCount1; j++)
		{
			if(strPointNo==m_ctrlListReportTable.GetItemText(j,0))
			{
				bExist=TRUE;
				break;
			}
		}
		if(!bExist)
		{
			m_ctrlListReportTable.InsertItem(nItemCount1, strPointNo, 0);
			//CString strExplain=m_ctrlListAllPoint.GetItemText(nItem,4);
			//m_ctrlListReportTable.SetItem(nItemCount1, 1, LVIF_TEXT, strExplain, 0, NULL, NULL, NULL);
		}
	}
}

void CViewDeleteAddr::OnButtonDeselect1() 
{
	// TODO: Add your control notification handler code here
	int nItemCount=m_ctrlListReportTable.GetItemCount();
    for(int nItem=0;nItem<nItemCount;nItem++)
	{
		if(m_ctrlListReportTable.GetItemState(nItem,LVIS_SELECTED) & LVIS_SELECTED)
		{
			m_ctrlListReportTable.DeleteItem(nItem);
		}
	}

}

void CViewDeleteAddr::OnButtonDeselectall() 
{
	// TODO: Add your control notification handler code here
	
	m_ctrlListReportTable.DeleteAllItems();
	
}

CString CViewDeleteAddr::GetAppPath()
{
	CString sModFileName;
	CString str1;
	GetModuleFileName(NULL, sModFileName.GetBuffer(MAX_PATH), MAX_PATH);
	sModFileName.ReleaseBuffer();
	str1=sModFileName;
	str1.MakeReverse();
	return(sModFileName.Left(sModFileName.GetLength() - str1.Find('\\')));
}

void CViewDeleteAddr::RebuildScanQue()
{
	CMainFrame* pFWnd=(CMainFrame*)AfxGetMainWnd();
	CCommStatusFM *pCommStatusFM=pFWnd->m_pCommStatusFM;

			pCommStatusFM->m_bStartScan=FALSE;
}

void CViewDeleteAddr::OnButtonAlarm() 
{
	// TODO: Add your control notification handler code here

	if(!m_bExcelInit)
	{
		AfxMessageBox("�޷���ʼ��EXCEL������ȷ���Ƿ�װ��MS EXCEL[2000���ϰ汾]");
		return;
	}

	_Application ExcelApp; 
	Workbooks wbsMyBooks; 
	_Workbook wbMyBook; 
	Worksheets wssMysheets; 
	_Worksheet wsMysheet; 
	Range rgMyRge; 
	//����Excel 2000������(����Excel) 
 
	if (!ExcelApp.CreateDispatch("Excel.Application",NULL)) 
	{ 
		AfxMessageBox("����Excel����ʧ��!"); 
		return; 
	} 
	//����ģ���ļ��������ĵ� 
	wbsMyBooks.AttachDispatch(ExcelApp.GetWorkbooks(),true); 

	//�õ������·��

	CString strXltPath;
	strXltPath=GetAppPath();

	strXltPath+="ReportXLT\\template2.xlt";

	wbMyBook.AttachDispatch(wbsMyBooks.Add(_variant_t(strXltPath))); 
	//�õ�Worksheets 
	wssMysheets.AttachDispatch(wbMyBook.GetWorksheets(),true); 
	//�õ�sheet1 
	wsMysheet.AttachDispatch(wssMysheets.GetItem(_variant_t("sheet1")),true); 
	//�õ�ȫ��Cells����ʱ,rgMyRge��cells�ļ��� 
	rgMyRge.AttachDispatch(wsMysheet.GetCells(),true); 

	//����1��1�еĵ�Ԫ��ֵ 

	int iExcelRow=1;
	int iExcelCollum=0; 

	CString strSQL,strPointNo;
	CString2DataType Str2Data;
 	try
	{
	
		int nItemCount1=m_ctrlListReportTable.GetItemCount();
		for(int iListItem=0; iListItem<nItemCount1; iListItem++)
		{
			strPointNo=m_ctrlListReportTable.GetItemText(iListItem,0);
			strSQL.Format("SELECT * FROM uWarnCauseRecord WHERE unPointNo = %s ",strPointNo);
			
			if( m_SQLDirect.ExecuteSQL(strSQL)==SQL_SUCCESS)
			{
				int nRet=m_SQLDirect.Fetch();
				if(!nRet)
				{
					CString strunPointNo=m_SQLDirect.GetCol(1);
					CString strExplain=m_SQLDirect.GetCol(2);
					CString strWarnCause=m_SQLDirect.GetCol(3);
					CString strWarnTime=m_SQLDirect.GetCol(4);
					CString strNormalTime=m_SQLDirect.GetCol(5);
					CString bConfirm=m_SQLDirect.GetCol(6);

					iExcelRow++;
					//1     2           3       4       5           6       7       8           9
					//���	��ǩ	����	��ַ	ת��������	ͨ��	ɨ��	Ƶ��	������Ϣ
					rgMyRge.SetItem(_variant_t((long)iExcelRow),_variant_t((long)1),_variant_t(strunPointNo)); 
					rgMyRge.SetItem(_variant_t((long)iExcelRow),_variant_t((long)2),_variant_t(strExplain)); 
					rgMyRge.SetItem(_variant_t((long)iExcelRow),_variant_t((long)3),_variant_t(strWarnCause)); 
					rgMyRge.SetItem(_variant_t((long)iExcelRow),_variant_t((long)4),_variant_t(strWarnTime)); 
					rgMyRge.SetItem(_variant_t((long)iExcelRow),_variant_t((long)5),_variant_t(strNormalTime)); 
					rgMyRge.SetItem(_variant_t((long)iExcelRow),_variant_t((long)6),_variant_t(bConfirm)); 

				}
			}
		}
	}
	catch(CDBException *e){
	e->ReportError();
	return;
	}

	wbMyBook.SetSaved(true); 
	ExcelApp.SetVisible(true); 
	//wbMyBook.PrintPreview(_variant_t(false)); 
	//�ͷŶ��� 
	rgMyRge.ReleaseDispatch(); 
	wsMysheet.ReleaseDispatch(); 
	wssMysheets.ReleaseDispatch(); 
	wbMyBook.ReleaseDispatch(); 
	wbsMyBooks.ReleaseDispatch(); 
	ExcelApp.ReleaseDispatch(); 	
}

void CViewDeleteAddr::OnButtonSequence() 
{
	// TODO: Add your control notification handler code here
     if(!m_Database.IsOpen())
	{
     	try
		{
	    	m_Database.Open(NULL,FALSE,FALSE,_T("ODBC;DSN=masterdefine;UID=kj86;PWD=kj86;"),FALSE);
		}
    	catch(CDBException *e)
		{
		AfxMessageBox("Open Database Failed.");
		e->Delete();
		}
    }
        Spudetailed_me *spudetailed;
        spudetailed   =new  Spudetailed_me(&m_Database);

	if(!m_bExcelInit)
	{
		AfxMessageBox("�޷���ʼ��EXCEL������ȷ���Ƿ�װ��MS EXCEL[2000���ϰ汾]");
		return;
	}

	_Application ExcelApp; 
	Workbooks wbsMyBooks; 
	_Workbook wbMyBook; 
	Worksheets wssMysheets; 
	_Worksheet wsMysheet; 
	Range rgMyRge; 
	//����Excel 2000������(����Excel) 
 
	if (!ExcelApp.CreateDispatch("Excel.Application",NULL)) 
	{ 
		AfxMessageBox("����Excel����ʧ��!"); 
		return; 
	} 
	//����ģ���ļ��������ĵ� 
	wbsMyBooks.AttachDispatch(ExcelApp.GetWorkbooks(),true); 

	//�õ������·��
    int i,k;
	i=k=0;
	CString strXltPath;
	strXltPath=GetAppPath();

	strXltPath+="ReportXLT\\template3.xlt";

	wbMyBook.AttachDispatch(wbsMyBooks.Add(_variant_t(strXltPath))); 
	//�õ�Worksheets 
	wssMysheets.AttachDispatch(wbMyBook.GetWorksheets(),true); 
	//�õ�sheet1 
	wsMysheet.AttachDispatch(wssMysheets.GetItem(_variant_t("sheet1")),true); 
	//�õ�ȫ��Cells����ʱ,rgMyRge��cells�ļ��� 
	rgMyRge.AttachDispatch(wsMysheet.GetCells(),true); 

	//����1��1�еĵ�Ԫ��ֵ 

	int iExcelRow=1;
	int iExcelCollum=0; 

	CString str,Para1,Para2,Para3, Para4;
	CString2DataType Str2Data;

	spudetailed->Open(CRecordset::snapshot);

		 if(spudetailed->IsBOF())
	      	 return  ;
         spudetailed->MoveFirst();
         
		 while(!spudetailed->IsEOF())
		 {
			 i=spudetailed->m_spu_num;
             k=spudetailed->m_step_num;
			 if(i>0 && i<=200 && k>0 && k<=2000  )
			 { 
					CString spu_num=Str2Data.Int2CString(i);
					CString step_num=Str2Data.Int2CString(k);
					CString command_index=Str2Data.Int2CString(spudetailed->m_command_index);

					CString Para1=spudetailed->m_para1;
					CString Para2=spudetailed->m_para2;
					CString Para3=spudetailed->m_para3;
					CString Para4=spudetailed->m_para4;

				 iExcelRow++;
					//1     2           3       4       5           6       7       8           9
					//���	��ǩ	����	��ַ	ת��������	ͨ��	ɨ��	Ƶ��	������Ϣ
					rgMyRge.SetItem(_variant_t((long)iExcelRow),_variant_t((long)1),_variant_t(spu_num)); 
					rgMyRge.SetItem(_variant_t((long)iExcelRow),_variant_t((long)2),_variant_t(step_num)); 
					rgMyRge.SetItem(_variant_t((long)iExcelRow),_variant_t((long)3),_variant_t(command_index)); 
					rgMyRge.SetItem(_variant_t((long)iExcelRow),_variant_t((long)4),_variant_t(Para1)); 
					rgMyRge.SetItem(_variant_t((long)iExcelRow),_variant_t((long)5),_variant_t(Para2)); 
					rgMyRge.SetItem(_variant_t((long)iExcelRow),_variant_t((long)6),_variant_t(Para3)); 
					rgMyRge.SetItem(_variant_t((long)iExcelRow),_variant_t((long)7),_variant_t(Para4)); 
							
			 }
			 spudetailed->MoveNext();

		 }

	delete spudetailed;

	wbMyBook.SetSaved(true); 
	ExcelApp.SetVisible(true); 
	//wbMyBook.PrintPreview(_variant_t(false)); 
	//�ͷŶ��� 
	rgMyRge.ReleaseDispatch(); 
	wsMysheet.ReleaseDispatch(); 
	wssMysheets.ReleaseDispatch(); 
	wbMyBook.ReleaseDispatch(); 
	wbsMyBooks.ReleaseDispatch(); 
	ExcelApp.ReleaseDispatch(); 	
}
