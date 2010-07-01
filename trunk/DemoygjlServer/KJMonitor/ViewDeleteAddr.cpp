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

///	ConnectDB();//连接数据库
	if (CoInitialize(NULL)!=0)   //EXCEL
	{ 
		AfxMessageBox("初始化COM支持库失败,无法输出EXCEL报表，但可进行其它操作!");
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
	m_btnOK.SetTooltipText(_T("退出"));

	m_ctrlBtnDispUsedAddr.SetThemeHelper(&m_ThemeHelper);
	m_ctrlBtnDispUsedAddr.SetIcon(IDI_ICON_LEDON);
	m_ctrlBtnDispUsedAddr.SetTooltipText(_T("列出当前干线上所有已用的地址，并显示该地址上的转接器信息"));


	m_ctrlBtnDeleteAddr.SetThemeHelper(&m_ThemeHelper);
	m_ctrlBtnDeleteAddr.SetIcon(IDI_ICON_CANCEL);
	m_ctrlBtnDeleteAddr.SetTooltipText(_T("删除所选地址上的所有转接器，如果是多功能转接器，将全部删除"));

	m_ctrlBtnDeleteMultiConv.SetThemeHelper(&m_ThemeHelper);
	m_ctrlBtnDeleteMultiConv.SetIcon(IDI_ICON_CANCEL);
	m_ctrlBtnDeleteMultiConv.SetTooltipText(_T("删除所选行上的传感器，多功能转接器上的其它传感器保留"));

//	m_ctrlBtnDispNewTrunk.SetThemeHelper(&m_ThemeHelper);
//	m_ctrlBtnDispNewTrunk.SetIcon(IDI_ICON_NEW);
//	m_ctrlBtnDispNewTrunk.SetTooltipText(_T("在上面框中输入新的干线号，点击此按钮将显示新的干线上的已使用的地址信息"));

	m_ctrlBtnDispUnusedAddr.SetThemeHelper(&m_ThemeHelper);
	m_ctrlBtnDispUnusedAddr.SetIcon(IDI_ICON_LEDOFF);
	m_ctrlBtnDispUnusedAddr.SetTooltipText(_T("显示当前干线上没有使用的地址号，如果某一地址上是多功能转接器，则会说明该地址还可加的传感器类型"));
	

	m_ctrlBtnSearchPoint.SetThemeHelper(&m_ThemeHelper);
	m_ctrlBtnSearchPoint.SetIcon(IDI_ICON_SEARCH);
	m_ctrlBtnSearchPoint.SetTooltipText(_T("快速查找点号信息，请在上面框中输入点号"));

	m_ctrlBtnAdd.SetThemeHelper(&m_ThemeHelper);
	m_ctrlBtnAdd.SetIcon(IDI_ICON_SINGLE1);
	m_ctrlBtnAdd.SetTooltipText(_T("先在上面2编辑框中填入起始点号和终止点号，点击此按按钮即可将起始点与终止点之间所有已编辑的点信息加入报表，或者在左表中双击点所在行也可加入一点"));
	m_ctrlBtnAdd.SetColor(0,RGB(000,153,000),TRUE);
	m_ctrlBtnAdd.SetColor(1,RGB(255,255,255),TRUE);

	m_ctrlBtnReport.SetThemeHelper(&m_ThemeHelper);
	m_ctrlBtnReport.SetIcon(IDI_ICON_EXCEL);
	m_ctrlBtnReport.SetTooltipText(_T("根据下表形成EXCEL风格报表，在EXCEL中可对测点进行编辑、打印、拷贝、或插入WORD等文档，注意MS EXCEL必须是2000或更高的版本"));

	m_ctrlBtnAlarm.SetThemeHelper(&m_ThemeHelper);
	m_ctrlBtnAlarm.SetIcon(IDI_ICON_EXCEL);
	m_ctrlBtnAlarm.SetTooltipText(_T("EXCEL风格报表，在EXCEL中可对报警点进行编辑、打印、拷贝、或插入WORD等文档，注意MS EXCEL必须是2000或更高的版本"));

	m_ctrlBtnSequence.SetThemeHelper(&m_ThemeHelper);
	m_ctrlBtnSequence.SetIcon(IDI_ICON_EXCEL);
	m_ctrlBtnSequence.SetTooltipText(_T("EXCEL风格报表，在EXCEL中可对时序进行编辑、打印、拷贝、或插入WORD等文档，注意MS EXCEL必须是2000或更高的版本"));

	m_ctrlBtnAddAll.SetThemeHelper(&m_ThemeHelper);
	m_ctrlBtnAddAll.SetIcon(IDI_ICON_ADD1);
	m_ctrlBtnAddAll.SetTooltipText(_T("将左表中所有点全部加入"));
	m_ctrlBtnAddAll.SetColor(0,RGB(000,255,000),TRUE);
	m_ctrlBtnAddAll.SetColor(1,RGB(255,255,255),TRUE);

	m_ctrlBtnAdd1.SetThemeHelper(&m_ThemeHelper);
	m_ctrlBtnAdd1.SetIcon(IDI_ICON_ADDSINGLE);
	m_ctrlBtnAdd1.SetTooltipText(_T("先在左表中选择点所在行，再点击加入，双击点所在行也可加入"));
	m_ctrlBtnAdd1.SetColor(0,RGB(000,153,000),TRUE);
	m_ctrlBtnAdd1.SetColor(1,RGB(255,255,255),TRUE);
	
	m_ctrlBtnDeselectAll.SetThemeHelper(&m_ThemeHelper);
	m_ctrlBtnDeselectAll.SetIcon(IDI_ICON_ADDDESELECT);
	m_ctrlBtnDeselectAll.SetTooltipText(_T("将右表中所有点均删除"));
	m_ctrlBtnDeselectAll.SetColor(0,RGB(255,000,000),TRUE);
	m_ctrlBtnDeselectAll.SetColor(1,RGB(255,255,255),TRUE);

	m_ctrlBtnDeselect1.SetThemeHelper(&m_ThemeHelper);
	m_ctrlBtnDeselect1.SetIcon(IDI_ICON_ADDDESELECT1);
	m_ctrlBtnDeselect1.SetTooltipText(_T("先在右表中选择点所在行，再点击删除，双击点所在行也可删除"));
	m_ctrlBtnDeselect1.SetColor(0,RGB(255,051,051),TRUE);
	m_ctrlBtnDeselect1.SetColor(1,RGB(255,255,255),TRUE);

}

void CViewDeleteAddr::ConnectDB()
{
	try
	{
		m_SQLDirect.Init();
		if(m_SQLDirect.Connect(_T("masterdefine"),_T("kj86"),_T("kj86")))
			AfxMessageBox("AddUser:无法连接用户参数数据库,请确定SQL SERVER服务是否运行!");
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
					strtemp.Format("点 %d 还没有编辑，可用",m_unEditSearchPoint);
					AfxMessageBox(strtemp);
					m_bSearchPoint=FALSE;
				}
				//else
				//	strtemp=_T("所选干线上还没有编辑点，所有地址均可用");
				
				delete bUsedAddrNo;
				return;
			}
			int iItem=0;
			while(!nRet)
			{
/*	m_ctrlList.InsertColumn(0, _T("地址"),   LVCFMT_CENTER, 20);
	m_ctrlList.InsertColumn(1, _T("点号"),   LVCFMT_CENTER, 20);
	m_ctrlList.InsertColumn(2, _T("转接器类型"), LVCFMT_CENTER, 20);
	m_ctrlList.InsertColumn(3, _T("扫描"),   LVCFMT_CENTER, 20);
	m_ctrlList.InsertColumn(4, _T("频率"),   LVCFMT_CENTER, 20);
	m_ctrlList.InsertColumn(5, _T("其它信息"),   LVCFMT_CENTER, 40);
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
					strbScan="扫描";
				else
					strbScan="不扫描";
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
#define MS8IN_B38  	      1     //M0    //相应S8IN_B38  -----------11 命令   
#define MS5OUT_B25  	  2     //M1    //相应S5OUT_B25  ----------13 命令
#define MA4IN             3     //M3    //相应4-A50---              3  命令
#define MP16IN            4     //M4    //相应P16IN  --------------10 命令
#define A1IN8BIT_CH4ICO  5      //CH4 //1. ICO-智能型甲烷/一氧化碳传感器[8位1路]    
#define A1IN8BIT_A50     6      //      2. A50-A型单路模拟量输入信号转接器[8位1路]
#define A8IN8BIT_MCA     7      //      3. MCA-8路模拟量输入信号转接器[12位8路]
#define A8IN8BIT_MC8     8      //      4. MC8-8路模拟量输入信号转接器[8位8路]
#define A1OUT8BIT_C35    9      //      5. C35-模拟量输出信号转接器(C3-C5)[6位]
#define P16IN            10     //      6. ◆D1-脉冲计数输入累加器[16位]

//#define MA4IN  同3                      7. ◆4-A50模拟量输入信号转接器[8位4路]

#define S8IN_B38  	     11     //M0    1. B38-开关量输入[8路]
#define S8OUT_B48        12     //      2. B48-开关量输出[8路]
#define S5OUT_B25  	     13     //M1    3. B25-开关量输出[5路]

#define MULTICONV        14   
*/


CString CViewDeleteAddr::GetConvName(UINT unConvID)
{
	CString strConvName=_T("");
	switch(unConvID)
	{
	case MS8IN_B38:  //1. B38-开关量输入[8路]
		strConvName=_T("8路开入(多)");
		break;
	case MS5OUT_B25:  //2. B25-开关量输出[5路]
		strConvName=_T("5路开出(多)");
		break;
	case MA4IN:  //3. 4-A50功能
		strConvName=_T("4路8位模入(多)");
		break;
	case MP16IN:  //4. D1-脉冲计数输入累加器[16位]功能
		strConvName=_T("脉冲计数输入(多)");
		break;
	case A1IN8BIT_CH4ICO:  //5. ICO-智能型甲烷/一氧化碳传感器[8位1路]甲烷/一氧化碳
		strConvName=_T("1路8位ICO");
		break;
	case A1IN8BIT_A50:    // 6. A50-A型单路模拟量输入信号转接器[8位1路]
		strConvName=_T("1路8位模入");
		break;
	case  A8IN8BIT_MCA:    //7. MCA-8路模拟量输入信号转接器[12位8路]
		strConvName=_T("8路12位模入");
		break;
	case A8IN8BIT_MC8 :   //8  MC8-8路模拟量输入信号转接器[8位8路]
		strConvName=_T("8路8位模入");
		break;
	case A1OUT8BIT_C35 :  //9. C35-模拟量输出信号转接器(C3-C5)[6位]
		strConvName=_T("1路6位模出");
		break;
	case A4IN:  //15. 4-A50                                    //  2003/8/12
		strConvName=_T("4路8位模入");
		break;
	case P16IN :         // 10 ◆D1-脉冲计数输入累加器[16位]
		strConvName=_T("脉冲计数输入");
		break;
	case S8IN_B38:  	   //11. B38-开关量输入[8路]
		strConvName=_T("8路开入");
		break;
	case S8OUT_B48:    // 12. B48-开关量输出[8路]
		strConvName=_T("8路开出");
		break;
	case S5OUT_B25:  //13 . B25-开关量输出[5路]
		strConvName=_T("5路开出");
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
			strMessage.Format("肯定要从地址中删除地址 %s 吗?，如果确定，使用该地址的所有转接器信息都会从参数库中删除。",strtemp);
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
						AfxMessageBox("删除失败，请通过SQL SERVER 企业管理器查看数据");
					}
					else
					{
						//添加的代码（一行）
						theApp.OnSendSQL(strSQL1);
						strSQL1.Format("DELETE FROM uMonitorPointEdit WHERE (unPointNo = %d)",unPointNumonAddr[i]);
						if(m_SQLDirect.ExecuteSQL(strSQL1)!=SQL_SUCCESS)
						{
							AfxMessageBox("删除uMonitorPointEdit失败，请通过SQL SERVER 企业管理器查看数据");
						}
						else	//添加的代码
							theApp.OnSendSQL(strSQL1);
					}
				}
				strSQL.Format("DELETE FROM uPointProperty WHERE (unTrunkNo=%d) AND (unAddress =%s)",m_unTrunkNo,strtemp);
				if(m_SQLDirect.ExecuteSQL(strSQL)!=SQL_SUCCESS)
				{
					AfxMessageBox("删除失败，请通过SQL SERVER 企业管理器查看数据");
				}
				else
				{
					//添加的代码
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
		AfxMessageBox("还没有选择要删除的用户(提示：用鼠标/键盘方向键选择要删除的行)");
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
			strMessage.Format("肯定要从地址中删除位于地址 %s 上多功能转接器上的 %s 吗?，如果确定，其信息都会从参数库中删除。",strtemp,strtemp1);
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
						AfxMessageBox("删除uAnologPointProperty/uSwitchPointProperty失败，请通过SQL SERVER 企业管理器查看数据");
					}
					else
					{
						//添加的代码
						theApp.OnSendSQL(strSQL1);
						strSQL1.Format("DELETE FROM uMonitorPointEdit WHERE (unPointNo = %d)",unPointNumonAddr[i]);
						if(m_SQLDirect.ExecuteSQL(strSQL1)!=SQL_SUCCESS)
						{
							AfxMessageBox("删除uMonitorPointEdit失败，请通过SQL SERVER 企业管理器查看数据");
						}
						else		//添加的代码
							theApp.OnSendSQL(strSQL1);
					}
				}
				strSQL.Format("DELETE FROM uPointProperty WHERE (unTrunkNo=%d) AND (unAddress =%s) AND (unConnectorID=%s)",m_unTrunkNo,strtemp,strtemp2);
				if(m_SQLDirect.ExecuteSQL(strSQL)!=SQL_SUCCESS)
				{
					AfxMessageBox("删除uPointProperty失败，请通过SQL SERVER 企业管理器查看数据");
				}
				else
				{
					//添加的代码
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
		AfxMessageBox("还没有选择要删除的用户(提示：用鼠标/键盘方向键选择要删除的行)");
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
		strtemp.Format("点号应定义在0--%d之间，请重新输入",MAX_POINT_NUMBER-1);
		AfxMessageBox(strtemp);
		return;
	}
	m_bSearchPoint=TRUE;
///	GetDataFromDB();
}
/*	m_ctrlList.InsertColumn(0, _T("地址"),   LVCFMT_CENTER, 20);
	m_ctrlList.InsertColumn(1, _T("点号"),   LVCFMT_CENTER, 20);
	m_ctrlList.InsertColumn(2, _T("转接器类型"), LVCFMT_CENTER, 20);
	m_ctrlList.InsertColumn(3, _T("扫描"),   LVCFMT_CENTER, 20);
	m_ctrlList.InsertColumn(4, _T("频率"),   LVCFMT_CENTER, 20);
	m_ctrlList.InsertColumn(5, _T("其它信息"),   LVCFMT_CENTER, 40);
*/





void CViewDeleteAddr::SetListCtrlTable()
{
	m_ctrlList.InsertColumn(0, _T("地址"),   LVCFMT_CENTER, 20);
	m_ctrlList.InsertColumn(1, _T("点号"),   LVCFMT_CENTER, 20);
	m_ctrlList.InsertColumn(2, _T("转接器类型"), LVCFMT_CENTER, 40);
	m_ctrlList.InsertColumn(3, _T("ID"), LVCFMT_CENTER, 10);
	m_ctrlList.InsertColumn(4, _T("扫描"),   LVCFMT_CENTER, 10);
	m_ctrlList.InsertColumn(5, _T("频率"),   LVCFMT_CENTER, 10);
	m_ctrlList.InsertColumn(6, _T("其它信息"),   LVCFMT_CENTER, 40);
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
	m_ctrlListReportTable.InsertColumn(0, _T("点号"),   LVCFMT_CENTER, 20);
	m_ctrlListReportTable.InsertColumn(1, _T("干线"),   LVCFMT_CENTER, 20);
	m_ctrlListReportTable.InsertColumn(2, _T("地址"), LVCFMT_CENTER, 40);
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
		AfxMessageBox("无法初始化EXCEL报表，请确定是否安装了MS EXCEL[2000以上版本]");
		return;
	}

	_Application ExcelApp; 
	Workbooks wbsMyBooks; 
	_Workbook wbMyBook; 
	Worksheets wssMysheets; 
	_Worksheet wsMysheet; 
	Range rgMyRge; 
	//创建Excel 2000服务器(启动Excel) 
 
	if (!ExcelApp.CreateDispatch("Excel.Application",NULL)) 
	{ 
		AfxMessageBox("创建Excel服务失败!"); 
		return; 
	} 
	//利用模板文件建立新文档 
	wbsMyBooks.AttachDispatch(ExcelApp.GetWorkbooks(),true); 

	//得到程序的路径

	CString strXltPath;
	strXltPath=GetAppPath();
	//AfxMessageBox(strXltPath);

	strXltPath+="ReportXLT\\template1.xlt";
	//CreateDirectory( str1, NULL );
//	if(!SetCurrentDirectory(str1))
//		AfxMessageBox("设置template1.xlt文件夹失败 setcurrentdirectory");

	wbMyBook.AttachDispatch(wbsMyBooks.Add(_variant_t(strXltPath))); 
	//得到Worksheets 
	wssMysheets.AttachDispatch(wbMyBook.GetWorksheets(),true); 
	//得到sheet1 
	wsMysheet.AttachDispatch(wssMysheets.GetItem(_variant_t("sheet1")),true); 
	//得到全部Cells，此时,rgMyRge是cells的集合 
	rgMyRge.AttachDispatch(wsMysheet.GetCells(),true); 

	//设置1行1列的单元的值 

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
					CString strstrLabel=m_SQLDirect.GetCol(10);            //标签名称
					CString strstrExplain=m_SQLDirect.GetCol(11);         //其它附加说明
					CString strunChannel=m_SQLDirect.GetCol(12);          //通道号

					CString strunConvIDCH = GetConvName(Str2Data.String2Int(strunConnectorID));
					
					if(strbScan=="1")
						strbScan="扫描";
					else
						strbScan="不扫描";

					iExcelRow++;
					//1     2           3       4       5           6       7       8           9
					//点号	标签	干线	地址	转接器类型	通道	扫描	频率	其它信息
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

	//rgMyRge.SetItem(_variant_t((long)2),_variant_t((long)1),_variant_t("龚建伟")); 
	//rgMyRge.SetItem(_variant_t((long)20),_variant_t((long)3),_variant_t("ewerwr")); 
	//得到所有的列 
/*	rgMyRge.AttachDispatch(wsMysheet.GetColumns(),true); 
	//得到第一列 
	for(int iCollum=1;iCollum<=9;iCollum++)
	{
		int iWidth;
		if(iCollum==5)
			iWidth=20;
		else
			iWidth=10;
		rgMyRge.AttachDispatch(rgMyRge.GetItem(_variant_t((long)iCollum),vtMissing).pdispVal,true); 
		//设置列宽 
		rgMyRge.SetColumnWidth(_variant_t((long)iWidth)); 
	}
*/
	/*
	//调用模板中预先存放的宏 
	ExcelApp.Run(_variant_t("CopyRow"),_variant_t((long)10),vtMissing,vtMissing, 
	vtMissing,vtMissing,vtMissing,vtMissing,vtMissing,vtMissing,vtMissing, 
	vtMissing,vtMissing,vtMissing,vtMissing,vtMissing,vtMissing,vtMissing, 
	vtMissing,vtMissing,vtMissing,vtMissing,vtMissing,vtMissing,vtMissing, 
	vtMissing,vtMissing,vtMissing,vtMissing,vtMissing,vtMissing); 
	*/
	  //打印预览 
	wbMyBook.SetSaved(true); 
	ExcelApp.SetVisible(true); 
	//wbMyBook.PrintPreview(_variant_t(false)); 
	//释放对象 
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
		AfxMessageBox("起始点号不能大于终止点号");
		return;
	}
	if((m_unEditStartPoint<1)||(m_unEditEndPoint>MAX_POINT_NUMBER-1))
	{
		CString str;
		str.Format("起始点号不能小于1或终止点号不能大于%d",MAX_POINT_NUMBER-1);
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
					strbScan="扫描";
				else
					strbScan="不扫描";*/
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
					//strtemp.Format("点 %s 已经在控制表中",strPointNo);
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
		AfxMessageBox("无法初始化EXCEL报表，请确定是否安装了MS EXCEL[2000以上版本]");
		return;
	}

	_Application ExcelApp; 
	Workbooks wbsMyBooks; 
	_Workbook wbMyBook; 
	Worksheets wssMysheets; 
	_Worksheet wsMysheet; 
	Range rgMyRge; 
	//创建Excel 2000服务器(启动Excel) 
 
	if (!ExcelApp.CreateDispatch("Excel.Application",NULL)) 
	{ 
		AfxMessageBox("创建Excel服务失败!"); 
		return; 
	} 
	//利用模板文件建立新文档 
	wbsMyBooks.AttachDispatch(ExcelApp.GetWorkbooks(),true); 

	//得到程序的路径

	CString strXltPath;
	strXltPath=GetAppPath();

	strXltPath+="ReportXLT\\template2.xlt";

	wbMyBook.AttachDispatch(wbsMyBooks.Add(_variant_t(strXltPath))); 
	//得到Worksheets 
	wssMysheets.AttachDispatch(wbMyBook.GetWorksheets(),true); 
	//得到sheet1 
	wsMysheet.AttachDispatch(wssMysheets.GetItem(_variant_t("sheet1")),true); 
	//得到全部Cells，此时,rgMyRge是cells的集合 
	rgMyRge.AttachDispatch(wsMysheet.GetCells(),true); 

	//设置1行1列的单元的值 

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
					//点号	标签	干线	地址	转接器类型	通道	扫描	频率	其它信息
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
	//释放对象 
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
		AfxMessageBox("无法初始化EXCEL报表，请确定是否安装了MS EXCEL[2000以上版本]");
		return;
	}

	_Application ExcelApp; 
	Workbooks wbsMyBooks; 
	_Workbook wbMyBook; 
	Worksheets wssMysheets; 
	_Worksheet wsMysheet; 
	Range rgMyRge; 
	//创建Excel 2000服务器(启动Excel) 
 
	if (!ExcelApp.CreateDispatch("Excel.Application",NULL)) 
	{ 
		AfxMessageBox("创建Excel服务失败!"); 
		return; 
	} 
	//利用模板文件建立新文档 
	wbsMyBooks.AttachDispatch(ExcelApp.GetWorkbooks(),true); 

	//得到程序的路径
    int i,k;
	i=k=0;
	CString strXltPath;
	strXltPath=GetAppPath();

	strXltPath+="ReportXLT\\template3.xlt";

	wbMyBook.AttachDispatch(wbsMyBooks.Add(_variant_t(strXltPath))); 
	//得到Worksheets 
	wssMysheets.AttachDispatch(wbMyBook.GetWorksheets(),true); 
	//得到sheet1 
	wsMysheet.AttachDispatch(wssMysheets.GetItem(_variant_t("sheet1")),true); 
	//得到全部Cells，此时,rgMyRge是cells的集合 
	rgMyRge.AttachDispatch(wsMysheet.GetCells(),true); 

	//设置1行1列的单元的值 

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
					//点号	标签	干线	地址	转接器类型	通道	扫描	频率	其它信息
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
	//释放对象 
	rgMyRge.ReleaseDispatch(); 
	wsMysheet.ReleaseDispatch(); 
	wssMysheets.ReleaseDispatch(); 
	wbMyBook.ReleaseDispatch(); 
	wbsMyBooks.ReleaseDispatch(); 
	ExcelApp.ReleaseDispatch(); 	
}
