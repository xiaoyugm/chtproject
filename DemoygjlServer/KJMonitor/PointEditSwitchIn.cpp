// PointEditAnologIn.cpp : implementation file
//

#include "stdafx.h"
#include "KJMonitor.h"
#include "PointEditSwitchIn.h"
#include "math.h"
#include "ViewDeleteAddr.h"
#include "Controls\\MABString.h"
#include "Edit12ModeDlg.h"

#include "CommStatusFM.h"
#include "MainFrm.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
/////////////////////////////////////////////////////////////////////////////
// CPointEditSwitchIn dialog


CPointEditSwitchIn::CPointEditSwitchIn(CWnd* pParent /*=NULL*/)
	: CDialog(CPointEditSwitchIn::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPointEditSwitchIn)
	m_unEditPoint =  1;
	m_unEditAddress = 0;
	m_unEditWarnDelay = 0;
	m_strEditOtherExplain = _T("");
	m_strEditPointLabel = _T("");
	m_unEditChannel = 1;
	m_strEditKeepTime = _T("0000/00/00");
	m_unEditWarnDelay=0;
	m_strEditOtherExplain= _T("");
	m_strEditPointLabel= _T("");
	//}}AFX_DATA_INIT

	m_bSave=FALSE;
	m_bSaveSuccess=FALSE;
	m_bGetChangePointInfo=FALSE;
	m_bPointEditChange=FALSE;
}


void CPointEditSwitchIn::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPointEditSwitchIn)
	DDX_Control(pDX, IDC_EDIT_KEEPTIME, m_ctrlEditKeepTime);
	DDX_Control(pDX, IDC_COMBO_RECORD, m_ctrlComboRecord);
	DDX_Control(pDX, IDC_BUTTON_EDIT12MODE, m_ctrlBtnEdit12Mode);
	DDX_Control(pDX, IDC_COMBO_21MODE, m_ctrlCombo21Mode);
	DDX_Control(pDX, IDC_COMBO_APC, m_ctrlComboAPC);
	DDX_Control(pDX, IDC_EDIT_CHANNEL, m_ctrlEditChannel);
	DDX_Control(pDX, IDC_EDIT_ADRESS, m_ctrlEditAddress);
	DDX_Control(pDX, IDC_CHECK_CHANGE, m_ctrlCheckChange);
	DDX_Control(pDX, IDC_BUTTON_DELETE, m_ctrlBtnDelete);
	DDX_Control(pDX, IDC_LIST_CONV, m_ctrlList);
	DDX_Control(pDX, IDC_COMBO_SCANFREQUENCY, m_ctrlComboScanFrequency);
	DDX_Control(pDX, IDC_COMBO_TRUNKNO, m_ctrlComboTrunkNo);
	DDX_Control(pDX, IDC_COMBO_WARNCLASS01, m_ctrlComboWarnClass);
	DDX_Control(pDX, IDC_BUTTON_VIEWDELETEADDRESS, m_ctrlBtnBiewDeleteAddress);
	DDX_Control(pDX, IDC_CHECK_MULTICONV, m_ctrlCheckMultiConv);
	DDX_Control(pDX, IDC_BUTTON_VIEWPOINT, m_ctrlBtnViewPoint);
	DDX_Control(pDX, IDC_BUTTON_VIEWADDR, m_ctrlBtnViewAddr);
	DDX_Control(pDX, IDC_COMBO_BSCAN01, m_ctrlComboBScan);
	DDX_Control(pDX, IDC_COMBO_SENSORNAME, m_ctrlComboSensorName);
	DDX_Control(pDX, IDC_BUTTON_POINTNOBACKWORD, m_btnPOINTNOBACKWORD);
	DDX_Control(pDX, IDC_BUTTON_POINTNOFORWORD, m_btnPOINTNOFORWORD);
	DDX_Control(pDX, IDOK, m_btnOK);
	DDX_Control(pDX, IDCANCEL, m_btnCANCEL);
	DDX_Control(pDX, IDC_BUTTON_ADDEDITANDGOON, m_btnADDEDITANDGOON);
	DDX_Text(pDX, IDC_EDIT_POINTNO01, m_unEditPoint);
	DDX_Control(pDX, IDC_EDIT_POINTNO01, m_ctrlEditPoint);
	DDX_Text(pDX, IDC_EDIT_ADRESS, m_unEditAddress);
	DDX_Text(pDX, IDC_EDIT_WARNDELAY, m_unEditWarnDelay);
	DDX_Text(pDX, IDC_EDIT_OTHEREXPLAIN, m_strEditOtherExplain);
	DDV_MaxChars(pDX, m_strEditOtherExplain, 32);
	DDX_Text(pDX, IDC_EDIT_POINTLABEL, m_strEditPointLabel);
	DDV_MaxChars(pDX, m_strEditPointLabel, 8);
	DDX_Text(pDX, IDC_EDIT_CHANNEL, m_unEditChannel);
	DDX_Text(pDX, IDC_EDIT_KEEPTIME, m_strEditKeepTime);
	DDV_MaxChars(pDX, m_strEditKeepTime, 20);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CPointEditSwitchIn, CDialog)
	//{{AFX_MSG_MAP(CPointEditSwitchIn)
	ON_BN_CLICKED(IDC_BUTTON_POINTNOBACKWORD, OnButtonPointnobackword)
	ON_BN_CLICKED(IDC_BUTTON_POINTNOFORWORD, OnButtonPointnoforword)
	ON_CBN_SELCHANGE(IDC_COMBO_SENSORTYPE, OnSelchangeComboSensortype)
	ON_CBN_SELCHANGE(IDC_COMBO_SENSORNAME, OnSelchangeComboSensorname)
	ON_WM_DESTROY()
///	ON_BN_CLICKED(IDC_BUTTON_ADDEDITANDGOON, OnButtonAddeditandgoon)
	ON_BN_CLICKED(IDC_BUTTON_VIEWPOINT, OnButtonViewpoint)
	ON_BN_CLICKED(IDC_BUTTON_VIEWADDR, OnButtonViewaddr)
	ON_BN_CLICKED(IDC_BUTTON_VIEWDELETEADDRESS, OnButtonViewdeleteaddress)
///	ON_BN_CLICKED(IDC_BUTTON_DELETE, OnButtonDelete)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_CONV, OnDblclkListConv)
	ON_BN_CLICKED(IDC_CHECK_CHANGE, OnCheckChange)
	ON_BN_CLICKED(IDC_BUTTON_EDIT12MODE, OnButtonEdit12mode)
	ON_CBN_SELCHANGE(IDC_COMBO_RECORD, OnSelchangeComboRecord)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPointEditSwitchIn message handlers

BOOL CPointEditSwitchIn::OnInitDialog() 
{
	CDialog::OnInitDialog();
	// TODO: Add extra initialization here
	m_btnOK.SetThemeHelper(&m_ThemeHelper);
	m_btnOK.SetIcon(IDI_ICON_OK);
	m_btnOK.SetTooltipText(_T("ȷ����ǰ�༭����������������뵽���������ݿ��ļ��У�Ȼ���˳�"));
	m_btnCANCEL.SetThemeHelper(&m_ThemeHelper);
	m_btnCANCEL.SetIcon(IDI_ICON_EXIT);
	m_btnCANCEL.SetTooltipText(_T("ȡ�����б༭��������������棬�˳��༭��"));
		
	m_btnADDEDITANDGOON.SetThemeHelper(&m_ThemeHelper);
	m_btnADDEDITANDGOON.SetIcon(IDI_ICON_OK);
	m_btnADDEDITANDGOON.SetTooltipText(_T("ȷ�����б༭��������������뵽���������ݿ��ļ��У������༭��һ��������"));
	m_btnPOINTNOBACKWORD.SetThemeHelper(&m_ThemeHelper);
	m_btnPOINTNOBACKWORD.SetIcon(IDI_ICON_RIGHTARROW);
	m_btnPOINTNOBACKWORD.SetTooltipText(_T("��Ű���������ռ�����������һҳ"));
	m_btnPOINTNOFORWORD.SetThemeHelper(&m_ThemeHelper);
	m_btnPOINTNOFORWORD.SetIcon(IDI_ICON_LEFTARROW);
	m_btnPOINTNOFORWORD.SetTooltipText(_T("��Ű���������ռ���������Сһҳ"));

	m_ctrlBtnViewPoint.SetThemeHelper(&m_ThemeHelper);
	m_ctrlBtnViewPoint.SetIcon(IDI_ICON_SEARCH);
	m_ctrlBtnViewPoint.SetTooltipText(_T("�鿴�������������ĵ���Ƿ�ռ��"));

	m_ctrlBtnViewAddr.SetThemeHelper(&m_ThemeHelper);
	m_ctrlBtnViewAddr.SetIcon(IDI_ICON_SEARCH);
	m_ctrlBtnViewAddr.SetTooltipText(_T("�鿴�������������ĵ�ַ���Ƿ�ռ��,������ַ��Ϣ��ʾ�ڱ���У�����ַΪ�๦��ת���������ȰѶ๦��ת����ѡ��ѡ��"));

	m_ctrlBtnBiewDeleteAddress.SetThemeHelper(&m_ThemeHelper);
	m_ctrlBtnBiewDeleteAddress.SetIcon(IDI_ICON_SEARCH);
	m_ctrlBtnBiewDeleteAddress.SetTooltipText(_T("�鿴��ǰ����(���ߺ��ڱ༭��������)�ĵ�ַ��ʹ����������Խ�������Ҫ�ĵ�ַ(�����)��Ϣɾ��"));
	
	m_ctrlBtnDelete.SetThemeHelper(&m_ThemeHelper);
	m_ctrlBtnDelete.SetIcon(IDI_ICON_CANCEL);
	m_ctrlBtnDelete.SetTooltipText(_T("�����������������ѡ��Ҫɾ����ͨ����Ȼ�����˰�ť����ɾ��"));
    
	m_ctrlBtnEdit12Mode.SetThemeHelper(&m_ThemeHelper);
	m_ctrlBtnEdit12Mode.SetIcon(IDI_ICON_SEARCH);
	m_ctrlBtnEdit12Mode.SetTooltipText(_T("�༭��鿴1/2ģʽ��"));
	
///	ConnectDB(); //Connect  DataBase
	m_ctrlComboSensorName.SetCurSel(0);
	//m_ctrlComboSensorType.SetCurSel(7);
	m_ctrlComboScanFrequency.SetCurSel(0);
//	m_ctrlComboProcessType.SetCurSel(0);
	m_ctrlComboTrunkNo.SetCurSel(0);
	m_ctrlComboWarnClass.SetCurSel(0);
	m_ctrlComboBScan.SetCurSel(1);
	//m_ctrlComboPrintYN.SetCurSel(0);
	m_ctrlComboAPC.SetCurSel(3);     
	m_ctrlCombo21Mode.SetCurSel(1);  
	m_ctrlCheckChange.SetCheck(0);
	//�Ƿ��¼����ʱ��
	m_ctrlComboRecord.SetCurSel(0);
	OnSelchangeComboRecord();
	SetListHead();
	//OnSelchangeComboSensorname();  //modify by 2003/8/14
	UpdateData(FALSE);
   
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}



void CPointEditSwitchIn::OnButtonPointnoforword() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if(m_unEditPoint<1)
		m_unEditPoint=1;
	else	
		m_unEditPoint -= 1;
	if(m_unEditPoint<1)
		m_unEditPoint=1;
	UpdateData(FALSE);
}

void CPointEditSwitchIn::OnButtonPointnobackword() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if(m_unEditPoint>MAX_POINT_NUMBER-1)
	{
		m_unEditPoint=MAX_POINT_NUMBER-1;
	}
	else
		m_unEditPoint += 1;
	UpdateData(FALSE);
}

void CPointEditSwitchIn::OnSelchangeComboSensortype() 
{
	
}



void CPointEditSwitchIn::OnSelchangeComboSensorname() 
{
	// TODO: Add your control notification handler code here

	UINT untemp;
	untemp=m_ctrlComboSensorName.GetCurSel();
	switch(untemp)
	{
	case 0:  //1.������������[8·]  unConvID=11
		if(!m_bGetChangePointInfo)
		{
			if(AfxMessageBox("���ڶ๦��ת��������", MB_ICONQUESTION |MB_OKCANCEL)==IDOK)
				m_ctrlCheckMultiConv.SetCheck(1);
			else
				m_ctrlCheckMultiConv.SetCheck(0);
		}
		//m_ctrlComboSensorType.SetCurSel(7);   //mod by liy
		break;
	case 1:  //���������[5·] unConvID=13
		if(!m_bGetChangePointInfo)
		{
			if(AfxMessageBox("���ڶ๦��ת��������", MB_ICONQUESTION |MB_OKCANCEL)==IDOK)
				m_ctrlCheckMultiConv.SetCheck(1);
			else
				m_ctrlCheckMultiConv.SetCheck(0);
		}

		//m_ctrlComboSensorType.SetCurSel(4);
		break;
	case 2:  //���������[8·] unConvID=12
		m_ctrlCheckMultiConv.SetCheck(0);
		//m_ctrlComboSensorType.SetCurSel(7);
		break;
	case 3: //����������[16·] unConvID = 14
		//		m_ctrlCheck
		m_ctrlCheckMultiConv.SetCheck(0);
		break;
	default:
		break;
	}

	if(!m_bGetChangePointInfo)
		OnButtonViewaddr();
//	SetEditBoxStyle(m_ctrlComboSensorType.GetCurSel()+1);
}

void CPointEditSwitchIn::GetChnagePointInfo()
{
	BOOL bAnyPoint=0;
	CString strbValueType,strSQL;
	try
	{
		strSQL.Format("SELECT * FROM uPointProperty WHERE unPointNo=%d",m_unEditPoint);
		if( m_SQLDirect.ExecuteSQL(strSQL)==SQL_SUCCESS)
		{
			if(!m_SQLDirect.Fetch())
			{
				CString strunPointNo=m_SQLDirect.GetCol(1);     //���
				UINT unTrunkNo=m_String2DataType.String2Int(m_SQLDirect.GetCol(2));      //����
				m_unEditAddress=m_String2DataType.String2Int(m_SQLDirect.GetCol(3));       //��ַ
				unsigned char ucScanFrequency=m_String2DataType.String2Int(m_SQLDirect.GetCol(4));      //Ѳ��Ƶ��
				BOOL bScan=m_String2DataType.Str2Bool(m_SQLDirect.GetCol(5));               //�Ƿ�ɨ��
				strbValueType=m_SQLDirect.GetCol(6);         //1:����ģ����   0����������
				UINT unConnectorID=m_String2DataType.String2Int(m_SQLDirect.GetCol(7));  //ת����ID��: ���ж๦��ת�����а�ʵ�ʽ���Ĵ���������ѡ��
				CString strunSamePointNumber=m_SQLDirect.GetCol(8);  //��ͬһ��ַ����ͬ���ʵĵ������
				CString strbMultiConv=m_SQLDirect.GetCol(9);
				m_strEditPointLabel=m_SQLDirect.GetCol(10);            //��ǩ����
				m_strEditOtherExplain=m_SQLDirect.GetCol(11);         //��������˵��
				m_unEditChannel=m_String2DataType.String2Int(m_SQLDirect.GetCol(12));

				m_ctrlComboTrunkNo.SetCurSel(unTrunkNo-1);
				unsigned char ucScanFreq[7]={1,2,4,8,16,32,64};
				for(int i=0;i<7;i++)
				{
					if(ucScanFrequency!=ucScanFreq[i]) continue;
					ucScanFrequency=i;
				}
				m_ctrlComboScanFrequency.SetCurSel(ucScanFrequency);
				m_ctrlComboBScan.SetCurSel(bScan);
				switch(unConnectorID)
				{
				case 1:   
					m_ctrlCheckMultiConv.SetCheck(1); 
					m_ctrlComboSensorName.SetCurSel(0);
					break;
				case 11:
					m_ctrlCheckMultiConv.SetCheck(0); 
					m_ctrlComboSensorName.SetCurSel(0);
					break;
				case 2:   
					m_ctrlCheckMultiConv.SetCheck(1); 
					m_ctrlComboSensorName.SetCurSel(1);
					break;
				case 13:
					m_ctrlCheckMultiConv.SetCheck(0); 
					m_ctrlComboSensorName.SetCurSel(1);
					break;
				case 12:
					m_ctrlCheckMultiConv.SetCheck(0); 
					m_ctrlComboSensorName.SetCurSel(2);
					break;
				case 16:
					m_ctrlCheckMultiConv.SetCheck(0); 
					m_ctrlComboSensorName.SetCurSel(3);
					break;
				default: 
					m_ctrlCheckMultiConv.SetCheck(0); 
					break;
				}
				UpdateData(FALSE);
				m_bGetChangePointInfo=TRUE;
				OnSelchangeComboSensorname();
				m_bGetChangePointInfo=FALSE;

				bAnyPoint=1;
			}
		}
		if((bAnyPoint)&&(strbValueType=="0"))
		{
			    
				strSQL.Format("SELECT * FROM uSwitchPointProperty WHERE unPointNo=%d",m_unEditPoint);
				if( m_SQLDirect.ExecuteSQL(strSQL)==SQL_SUCCESS)
				{
					if(!m_SQLDirect.Fetch())
					{
						CString strunPointNo= m_SQLDirect.GetCol("unPointNo");     //1 ���
						UINT unAC= m_String2DataType.String2Int(m_SQLDirect.GetCol("unAC"));         
						UINT unWarnCause= m_String2DataType.String2Int(m_SQLDirect.GetCol("unWarnCause"));     //5. unWarnCause(unsigned int);�����๲Ϊ8�֣�ԭ���������룬����¼��P22
						UINT un21mode= m_String2DataType.String2Int(m_SQLDirect.GetCol("un21mode")); 
						m_unEditWarnDelay= m_String2DataType.String2Int(m_SQLDirect.GetCol("unWarnDelay"));      //13. unWarnDelay;�����ӳ�
						int bRecordKTime = m_String2DataType.String2Int(m_SQLDirect.GetCol("unRecordKTime"));  //�Ƿ��¼����ʱ��
						//m_ctrlComboPrintYN.SetCurSel(bPrint);
						m_ctrlComboWarnClass.SetCurSel(unWarnCause);
						m_ctrlComboAPC.SetCurSel(unAC);     //*
						m_ctrlCombo21Mode.SetCurSel(un21mode);  //*
						m_ctrlComboRecord.SetCurSel(bRecordKTime);
						OnSelchangeComboRecord();
						m_strEditKeepTime = m_SQLDirect.GetCol("unSetKTime");
						m_strEditKeepTime.Insert(4,'/');
						m_strEditKeepTime.Insert(7,'/');
					}
					else{
						m_ctrlComboWarnClass.SetCurSel(0);
						m_ctrlComboAPC.SetCurSel(0);     //*
						m_ctrlCombo21Mode.SetCurSel(0);  //*
						m_ctrlComboRecord.SetCurSel(0);
						OnSelchangeComboRecord();
						m_strEditKeepTime = "0000/00/00";
					}
				}
			}
	}
	catch(CDBException *e){
	e->ReportError();
	EndWaitCursor();
	return;
	}
	// size to fit the columns
	//m_ctrlList.AutoSizeColumn();
	UpdateData(FALSE);
}

BOOL CPointEditSwitchIn::DisplayConvInfoInAddr()
{

	BOOL bMultiConv=0;
	BOOL bAnyPoint=0;
	UINT unChannelPointNo[MAX_CHANNEL_NUMBER];
	for(int i=0;i<MAX_CHANNEL_NUMBER;i++)
		unChannelPointNo[i]=0;
	CString strSQL,strtemp,strbValueType;
	CString strstrExplain;
	CViewDeleteAddr viewdelteaddr;
	UINT unbMultiConv;

	if(m_ctrlCheckMultiConv.GetCheck()) 
		unbMultiConv=1;
	else
		unbMultiConv=0;
	switch(m_ctrlComboSensorName.GetCurSel())
	{
	case 0:
		if(unbMultiConv)
			m_unConvID=1;
		else
			m_unConvID=11;
		break;
	case 1:
		if(unbMultiConv)
			m_unConvID=2;
		else
			m_unConvID=13;
		break;
	case 2:
		m_unConvID=12;
		if(unbMultiConv)
		{
			AfxMessageBox("�๦��ת������֧�ִ˴���������,��ȥ���๦��ת����ѡ��");
			return FALSE;
		}
		break;
//modify  
	case 3:
		//m_
	default:
		break;
	}

	try
	{
		strSQL.Format("SELECT * FROM uPointProperty WHERE (unTrunkNo=%d) AND (unAddress=%d)",
			m_ctrlComboTrunkNo.GetCurSel()+1, m_unEditAddress);
		if(m_ctrlCheckMultiConv.GetCheck())
		{
			CString strSQLplus;
			strSQLplus.Format(" AND (unConnectorID=%d)",m_unConvID);
			strSQL+=strSQLplus;
		}

		if( m_SQLDirect.ExecuteSQL(strSQL)==SQL_SUCCESS)
		{
			int nRet=m_SQLDirect.Fetch();
			while(!nRet)
			{
				CString strunPointNo=m_SQLDirect.GetCol(1);     //���
				CString strunTrunkNo=m_SQLDirect.GetCol(2);      //����
				CString strunAddress=m_SQLDirect.GetCol(3);       //��ַ
				CString strunScanFreq=m_SQLDirect.GetCol(4);      //Ѳ��Ƶ��
				CString strbScan=m_SQLDirect.GetCol(5);               //�Ƿ�ɨ��
				strbValueType=m_SQLDirect.GetCol(6);         //1:����ģ����   0����������
				UINT unConnectorID=m_String2DataType.String2Int(m_SQLDirect.GetCol(7));  //ת����ID��: ���ж๦��ת�����а�ʵ�ʽ���Ĵ���������ѡ��
				CString strunSamePointNumber=m_SQLDirect.GetCol(8);  //��ͬһ��ַ����ͬ���ʵĵ������
				CString strbMultiConv=m_SQLDirect.GetCol(9);
				CString strstrLabel=m_SQLDirect.GetCol(10);            //��ǩ����
				CString strstrExplain=m_SQLDirect.GetCol(11);         //��������˵��
				CString strunChannel=m_SQLDirect.GetCol(12);

				UINT unChannel=m_String2DataType.String2Int(strunChannel);          //��ת�����ϵ�ͨ����
				if(strbScan=="1") strbScan="��"; else strbScan="��";
				CString strConvName=viewdelteaddr.GetConvName(unConnectorID);
				if(unChannel>0)
					unChannelPointNo[unChannel-1]=m_String2DataType.String2Int(strunPointNo);
			
				m_ctrlList.SetItem(unChannel-1, 1, LVIF_TEXT, strunPointNo, 0, NULL, NULL, NULL);
				m_ctrlList.SetItem(unChannel-1, 2, LVIF_TEXT, strstrLabel, 0, NULL, NULL, NULL);
				m_ctrlList.SetItem(unChannel-1, 3, LVIF_TEXT, strConvName, 0, NULL, NULL, NULL);
				m_ctrlList.SetItem(unChannel-1, 4, LVIF_TEXT, strunScanFreq, 0, NULL, NULL, NULL);
				m_ctrlList.SetItem(unChannel-1, 5, LVIF_TEXT, strbScan, 0, NULL, NULL, NULL);
				m_ctrlList.SetItem(unChannel-1, 12, LVIF_TEXT, strstrExplain, 0, NULL, NULL, NULL);
				bAnyPoint=TRUE;
				nRet=m_SQLDirect.Fetch();
			}
		}
		if((bAnyPoint)&&(strbValueType=="0"))
			for(int iChannel=0; iChannel < GetChanelCount();iChannel++)
			{
				if(!unChannelPointNo[iChannel]) continue;
				strSQL.Format("SELECT * FROM uSwitchPointProperty WHERE unPointNo=%d",unChannelPointNo[iChannel]);
				if( m_SQLDirect.ExecuteSQL(strSQL)==SQL_SUCCESS)
				{
					int nRet=m_SQLDirect.Fetch();
					if(!nRet)
					{
						CString strunPointNo=m_SQLDirect.GetCol("unPointNo");     //1 ���
						UINT unAPC=m_String2DataType.String2Int(m_SQLDirect.GetCol("unAC"));         
						UINT unWarnCause = m_String2DataType.String2Int(m_SQLDirect.GetCol("unWarnCause")) + 1;
						CString strunWarnCause;     //5. unWarnCause(unsigned int);�����๲Ϊ8�֣�ԭ���������룬����¼��P22
						strunWarnCause.Format("%d",unWarnCause);
						CString strun21mode; 
						UINT un21mode = m_String2DataType.String2Int(m_SQLDirect.GetCol("un21mode")) + 1;
						strun21mode.Format("%d",un21mode);	
						CString strunWarnDelay=m_SQLDirect.GetCol("unWarnDelay");      //13. unWarnDelay;�����ӳ�
						CString strunAPC;
						switch(unAPC)
						{
						case 0: strunAPC="AC"; break;
						case 1: strunAPC="AO"; break;
						case 2: strunAPC="NC"; break;
						case 3: strunAPC="NO"; break;
						default: 
							strunAPC="NN";
							break;
						}
						CString strunRecordKTime = m_SQLDirect.GetCol("unRecordKTime");
						if(strunRecordKTime == "1")
							strunRecordKTime = "��";
						else
							strunRecordKTime = "��";						
						CString unKTime = m_SQLDirect.GetCol("unSetKTime");												
						unKTime.Insert(4,'/');
						unKTime.Insert(7,'/');

						m_ctrlList.SetItem(iChannel, 6, LVIF_TEXT, strunAPC, 0, NULL, NULL, NULL);
						m_ctrlList.SetItem(iChannel, 7, LVIF_TEXT, strun21mode, 0, NULL, NULL, NULL);
						m_ctrlList.SetItem(iChannel, 8, LVIF_TEXT, strunWarnCause, 0, NULL, NULL, NULL);
						m_ctrlList.SetItem(iChannel, 9, LVIF_TEXT, strunWarnDelay, 0, NULL, NULL, NULL);
						m_ctrlList.SetItem(iChannel, 10, LVIF_TEXT, strunRecordKTime, 0, NULL, NULL, NULL);
						m_ctrlList.SetItem(iChannel, 11, LVIF_TEXT, unKTime, 0, NULL, NULL, NULL);
					}
				}

			}
	}
	catch(CDBException *e){
	e->ReportError();
	EndWaitCursor();
	return FALSE;
	}
	return TRUE;
}

void CPointEditSwitchIn::ConnectDB()
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

void CPointEditSwitchIn::OnDestroy() 
{
	CDialog::OnDestroy();
	
	// TODO: Add your message handler code here
	m_SQLDirect.Close();
}

void CPointEditSwitchIn::OnButtonAddeditandgoon()   //save then go on
{	
	// TODO: Add your control notification handler code here
	UINT unbScan,unbMultiConv,unSamePointNum=0,unbValueType;
	unsigned char ucScanFreq[7]={1,2,4,8,16,32,64};
	CString strtemp;
	m_bSave=TRUE;
	m_bSaveSuccess=FALSE;
	UpdateData(TRUE);
	if(!IsWarnMinMaxRight())
		return;
///	if((m_ctrlComboRecord.GetCurSel()) && (!CheckKeepTimeFormat()))
///		return;

	if(m_ctrlCheckMultiConv.GetCheck()) 
		unbMultiConv=1;
	else
		unbMultiConv=0;
	switch(m_ctrlComboSensorName.GetCurSel())
	{
	case 0:
		if(unbMultiConv)
			m_unConvID=1;
		else
			m_unConvID=11;
		break;
	case 1:
		if(unbMultiConv)
			m_unConvID=2;
		else
			m_unConvID=13;
		break;
	case 2:
		m_unConvID=12;
		if(unbMultiConv)
		{
			AfxMessageBox("�๦��ת������֧�ִ˴���������,��ȥ���๦��ת����ѡ��");
			return;
		}
		break;
	case 3:
		m_unConvID = S16IN;
		break;
	default:
		break;
	}

	if(!m_ctrlCheckChange.GetCheck())
	{
///		if((!FindAddrConvChanInfo())||(!FindPointInfo()))
///			return;
		if((m_unEditChannel<1)||(m_unEditChannel> (UINT)GetChanelCount()))
		{
			strtemp.Format("ͨ����Ӧ��1~%d֮�䣬����������", GetChanelCount());
			AfxMessageBox(strtemp);
			return;
		}
	}
	unbValueType=0; //1:anolog 0:switch

	try
	{
		CString strSQL,strtemp;
		unbScan=m_ctrlComboBScan.GetCurSel();
		//unbPrint=m_ctrlComboPrintYN.GetCurSel();
		//save uPointProperty
		if(!m_ctrlCheckChange.GetCheck())
		{
			strtemp.Format(" VALUES(%d, %d, %d, %d, %d, %d, %d, %d, %d,'%s','%s',%d)",
				m_unEditPoint,
				m_ctrlComboTrunkNo.GetCurSel()+1,
				m_unEditAddress,
				ucScanFreq[m_ctrlComboScanFrequency.GetCurSel()],
				unbScan,
				unbValueType,
				m_unConvID,
				unSamePointNum,
				unbMultiConv,
				m_strEditPointLabel,
				m_strEditOtherExplain,
				m_unEditChannel);
			strSQL=_T("INSERT INTO uPointProperty (unPointNo, unTrunkNo, unAddress, unScanFreq, bScan, bValueType, unConnectorID, unSamePointNumber, bMultiConv,strLabel,strExplain,unChannel) ");
			strSQL+=strtemp;
		}
		else
		{
			strSQL.Format("UPDATE uPointProperty SET unScanFreq=%d, bScan=%d, bValueType=%d, unConnectorID=%d, unSamePointNumber=%d,bMultiConv=%d,strLabel='%s',strExplain='%s',unChannel=%d WHERE unPointNo=%d",
				ucScanFreq[m_ctrlComboScanFrequency.GetCurSel()],
				unbScan,
				unbValueType,
				m_unConvID,
				unSamePointNum,
				unbMultiConv,
				m_strEditPointLabel,
				m_strEditOtherExplain,
				m_unEditChannel,
				m_unEditPoint);

		}
		if( m_SQLDirect.ExecuteSQL(strSQL)!=SQL_SUCCESS)
		{
			AfxMessageBox("uPointProperty����ʧ�ܣ���������ݿ�ԭ��");
			m_bSaveSuccess=FALSE;
			return;
		}
		else		//��ӵĴ���
			theApp.OnSendSQL(strSQL);
        //save uSwitchPointProperty
		//��ѯ���ݿ����Ƿ��иõ�ļ�¼
    	strSQL.Format("select count(*) from uSwitchPointProperty WHERE unPointNo=%d",m_unEditPoint);
		int flag = 0;
		if( m_SQLDirect.ExecuteSQL(strSQL)==SQL_SUCCESS)
			if(!m_SQLDirect.Fetch())
				flag = m_String2DataType.String2Int(m_SQLDirect.GetCol(1));
		CString keeptime = m_strEditKeepTime;
		keeptime.Delete(4);
		keeptime.Delete(6);
		if (flag)
		{
			CString sql = "UPDATE uSwitchPointProperty SET unAC=%d,unWarnCause=%d,	un21mode=%d,";
			sql = sql + "unWarnDelay=%d,unRecordKTime=%d,unSetKTime='%s' WHERE unPointNo=%d";
			strSQL.Format(sql,
				m_ctrlComboAPC.GetCurSel(),     //*
				m_ctrlComboWarnClass.GetCurSel(),
				m_ctrlCombo21Mode.GetCurSel(),
//				m_ctrlComboProcessType.GetCurSel(),unProcessType=%d,
				m_unEditWarnDelay,
				m_ctrlComboRecord.GetCurSel(),
				keeptime,
				m_unEditPoint);
		}
		else
		{
			strtemp.Format(" VALUES(%d, %d, %d, %d,  %d,%d,'%s')",
				m_unEditPoint,
				m_ctrlComboAPC.GetCurSel(),     //*
				m_ctrlComboWarnClass.GetCurSel(),
				m_ctrlCombo21Mode.GetCurSel(),
//				m_ctrlComboProcessType.GetCurSel(),, unProcessType%d,
				m_unEditWarnDelay,
				m_ctrlComboRecord.GetCurSel(),
			    keeptime);
			    strSQL=_T("INSERT INTO uSwitchPointProperty (unPointNo, unAC, unWarnCause, un21mode, unWarnDelay,unRecordKTime,unSetKTime) ");
			    strSQL+=strtemp;
		}
		if( m_SQLDirect.ExecuteSQL(strSQL)!=SQL_SUCCESS)
		{
			AfxMessageBox("uSwitchPointProperty����ʧ�ܣ���������ݿ�ԭ��");
			m_bSaveSuccess=FALSE;
			return;
		}
		else		//��ӵĴ���
			theApp.OnSendSQL(strSQL);
		AfxMessageBox("����ɹ���",MB_ICONINFORMATION);
///		if(unbScan)
			m_bPointEditChange=TRUE;
		RebuildScanQue();  //���½���ɨ�����

		m_bSaveSuccess=TRUE;
		OnButtonViewaddr();
	}
	catch(CDBException *e){
	e->ReportError();
	EndWaitCursor();
	return;
	}
}

void CPointEditSwitchIn::OnOK()    //save then exit 
{
	// TODO: Add extra validation here
///	OnButtonAddeditandgoon();
	if(!m_bSaveSuccess)
		return;
	//RebuildScanQue();
	CDialog::OnOK();
}

void CPointEditSwitchIn::OnCancel() 
{
	// TODO: Add extra cleanup here
	//RebuildScanQue();
	CDialog::OnCancel();
}

void CPointEditSwitchIn::RebuildScanQue()
{
	CMainFrame* pFWnd=(CMainFrame*)AfxGetMainWnd();
	CCommStatusFM *pCommStatusFM=pFWnd->m_pCommStatusFM;
	if(m_bPointEditChange)            
	{
			pCommStatusFM->m_bStartScan=FALSE;
	}
}

void CPointEditSwitchIn::DispConvChannel()
{
	m_ctrlList.DeleteAllItems();
	//��ʾͨ������
	int unChannelCount = GetChanelCount();
	
	for(int iItem=0; iItem < unChannelCount; iItem++)
	{
		CString strItem;
		strItem.Format("%d",iItem+1);
		m_ctrlList.InsertItem(iItem,strItem,0);
		m_ctrlList.SetItem(iItem, 1, LVIF_TEXT,"", 0, NULL, NULL, NULL);
	}
}

void CPointEditSwitchIn::SetListHead()
{
	//m_ctrlListConv
	m_ctrlList.InsertColumn(0, _T("ͨ��"),   LVCFMT_CENTER, 36);
	m_ctrlList.InsertColumn(1, _T("���"),   LVCFMT_CENTER, 36);
	m_ctrlList.InsertColumn(2, _T("��ǩ"),   LVCFMT_CENTER, 60);
	m_ctrlList.InsertColumn(3, _T("ת��������"), LVCFMT_CENTER, 72);
	m_ctrlList.InsertColumn(4, _T("Ƶ��"), LVCFMT_CENTER, 36);
	m_ctrlList.InsertColumn(5, _T("ɨ��"),   LVCFMT_CENTER, 36);
	m_ctrlList.InsertColumn(6, _T("AC"),   LVCFMT_CENTER, 24);
	m_ctrlList.InsertColumn(7, _T("1/2ģʽ��"),   LVCFMT_CENTER, 66);
	m_ctrlList.InsertColumn(8, _T("������"),   LVCFMT_CENTER, 48);
	m_ctrlList.InsertColumn(9, _T("�����ӳ�"),   LVCFMT_CENTER, 60);
	m_ctrlList.InsertColumn(10, _T("�Ƿ��¼"),   LVCFMT_CENTER, 60);
	m_ctrlList.InsertColumn(11, _T("����ʱ��"),   LVCFMT_CENTER, 72);
	m_ctrlList.InsertColumn(12, _T("˵    ��"),   LVCFMT_CENTER, 86);
	// set some extnded styles
	m_ctrlList.SetExtendedStyle (LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT|LVS_EX_FLATSB);

	// Get the windows handle to the header control for the
	// list control then subclass the control.
	HWND hWndHeader = m_ctrlList.GetDlgItem(0)->GetSafeHwnd();
	m_flatHeader.SubclassWindow (hWndHeader);

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

BOOL CPointEditSwitchIn::FindAddrConvChanInfo(void)
{
	UpdateData(TRUE);
	BOOL bSameConv=0;
	unsigned char ucConvChannel;

	if((m_unEditAddress<0)||(m_unEditAddress>=MAX_ADDR_NUMBER))
	{
		AfxMessageBox("��ַ�ű�����0~127֮��ѡ��");
		return FALSE;
	}
	try
	{
		CString strSQL,strtemp;
		strSQL.Format("SELECT * FROM uPointProperty WHERE (unAddress = %d) AND (unTrunkNo =%d)",
			m_unEditAddress,m_ctrlComboTrunkNo.GetCurSel()+1);
		if( m_SQLDirect.ExecuteSQL(strSQL)==SQL_SUCCESS)
		{
			int nRet=m_SQLDirect.Fetch();
			while(!nRet)
			{
				UINT unConvID=m_String2DataType.String2Int(m_SQLDirect.GetCol(7));
				BOOL bMultiConv=m_String2DataType.Str2Bool(m_SQLDirect.GetCol(9));
				ucConvChannel=m_String2DataType.String2Int(m_SQLDirect.GetCol(12));
				if((bMultiConv)&&(m_ctrlCheckMultiConv.GetCheck()))
				{
					//if(m_ctrlCheckMultiConv.GetCheck())
					if(m_unConvID==unConvID) 
					{
						bSameConv=TRUE;
						break;
					}
				}
				else
				{
					if(m_unConvID!=unConvID)
					{
						strtemp.Format("����%d�ϵ�ַ%d�ѱ�ռ��",m_ctrlComboTrunkNo.GetCurSel()+1,m_unEditAddress );
						AfxMessageBox(strtemp,MB_ICONINFORMATION);
						return FALSE;
					}
					else
					{
						bSameConv=TRUE;
						break;
					}
				}
				nRet=m_SQLDirect.Fetch();
			}

			if(bSameConv) //ifthe same conv,to find if the channel is defined
			{
				strSQL.Format("SELECT * FROM uPointProperty WHERE (unAddress = %d) AND (unTrunkNo =%d) AND (unConnectorID=%d) AND (unChannel=%d)",
					m_unEditAddress,m_ctrlComboTrunkNo.GetCurSel()+1,m_unConvID,m_unEditChannel);
				if( m_SQLDirect.ExecuteSQL(strSQL)==SQL_SUCCESS)
				{
					if(!m_SQLDirect.Fetch())
					{
						CString strtemp;
						strtemp.Format("ͨ��%d �ѱ�ռ�ã���ѡ������ͨ�� ������ɾ���Ѷ���ĵ�",m_unEditChannel);
						AfxMessageBox(strtemp);
						return FALSE;
					}
				}
			}
			else
			{
				return TRUE;
			}
		}
	}
	catch(CDBException *e){
	e->ReportError();
	return FALSE;
	}
	return TRUE;
}

BOOL CPointEditSwitchIn::FindPointInfo()
{
	UpdateData(TRUE);
	try
	{
		CString strSQL,strtemp;
		BOOL flag=FALSE;
		if((m_unEditPoint<1)||(m_unEditPoint>MAX_POINT_NUMBER-1))
		{
			strtemp.Format("��ű�����1~%d֮��ѡ��",MAX_POINT_NUMBER-1);
			AfxMessageBox(strtemp);
			return FALSE;
		}
		strSQL.Format("SELECT * FROM uPointProperty WHERE unPointNo = %d",m_unEditPoint);
		if( m_SQLDirect.ExecuteSQL(strSQL)==SQL_SUCCESS)
		{
			int nRet=m_SQLDirect.Fetch();
			if(!nRet)
				flag=TRUE;
		}
		if(flag)
		{
			strtemp.Format("��� %d ��ռ��",m_unEditPoint);
			AfxMessageBox(strtemp,MB_ICONINFORMATION);
			return FALSE;
		}
		else
		{
			if(!m_bSave)
			{
				strtemp.Format("��� %d ����",m_unEditPoint);
				AfxMessageBox(strtemp,MB_ICONINFORMATION);
			}
			return TRUE;
		}

	}
	catch(CDBException *e){
	e->ReportError();
	EndWaitCursor();
	return FALSE;
	}
}

void CPointEditSwitchIn::OnButtonViewpoint() 
{
	// TODO: Add your control notification handler code here
	m_bSave=FALSE;
///	FindPointInfo();
}

void CPointEditSwitchIn::OnButtonViewaddr() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	DispConvChannel();
///	DisplayConvInfoInAddr();
}

BOOL CPointEditSwitchIn::IsWarnMinMaxRight()
{
	if((m_unEditWarnDelay>=60) ) 
	{
		AfxMessageBox("�����ӳٱ�����(0~60s)֮�䣬����������");
		return FALSE;
	}
	return TRUE;
}

void CPointEditSwitchIn::OnButtonViewdeleteaddress() 
{
	// TODO: Add your control notification handler code here
	CViewDeleteAddr dlgViewDeleteAddr;
	UpdateData(TRUE);
	dlgViewDeleteAddr.DoModal();
}

void CPointEditSwitchIn::OnButtonDelete() 
{
	// TODO: Add your control notification handler code here
	BOOL bDelete=0;
	CString2DataType Str2Data;
	int nItemCount=m_ctrlList.GetItemCount();
    for(int nItem=0;nItem<nItemCount;nItem++)
	{
		if(m_ctrlList.GetItemState(nItem,LVIS_SELECTED) & LVIS_SELECTED)
		{
			CString strSQL,strtemp,strpoint,strMessage,strSQL1,strbValueType;
			strtemp=m_ctrlList.GetItemText(nItem,0);
			strpoint=m_ctrlList.GetItemText(nItem,1);
			if(strpoint=="")
			{
				strMessage.Format("ͨ�� %s ��ǰû�е㣬����ɾ��",strtemp);
				AfxMessageBox(strMessage);
				return;
			}
			strMessage.Format("ȷ��Ҫɾ��ͨ�� %s ��?�����ȷ����ʹ�ø�ͨ���ĵ� %s ���Ӳ�������ɾ����",strtemp,strpoint);
			if(AfxMessageBox(strMessage, MB_ICONQUESTION |MB_OKCANCEL)==IDCANCEL)
			{
				return;
			}
			try
			{
				strSQL.Format("SELECT * FROM uPointProperty WHERE unPointNo=%s",strpoint);
				if( m_SQLDirect.ExecuteSQL(strSQL)==SQL_SUCCESS)
				{
					if(!m_SQLDirect.Fetch())
					{
						strbValueType=m_SQLDirect.GetCol(6);
						if(strbValueType=="1")
							strSQL1.Format("DELETE FROM uAnologPointProperty WHERE unPointNo=%s",strpoint);
						else if(strbValueType=="0")
							strSQL1.Format("DELETE FROM uSwitchPointProperty WHERE unPointNo=%s",strpoint);
						if(m_SQLDirect.ExecuteSQL(strSQL1)!=SQL_SUCCESS)
						{
							AfxMessageBox("ɾ��ʧ�ܣ���ͨ��SQL SERVER ��ҵ�������鿴��uSwitchPointProperty���uSwitchPointProperty������");
						}
						else	//��ӵĴ���
							theApp.OnSendSQL(strSQL1);

						strSQL.Format("DELETE FROM uPointProperty WHERE unPointNo=%s",strpoint);
						if(m_SQLDirect.ExecuteSQL(strSQL)!=SQL_SUCCESS)
						{
							AfxMessageBox("ɾ��ʧ�ܣ���ͨ��SQL SERVER ��ҵ�������鿴���ݣ�������ɵĲ�����б�Ǹ");
						}
						else	//��ӵĴ���
							theApp.OnSendSQL(strSQL);

						m_bPointEditChange=TRUE;
						RebuildScanQue();
						bDelete=1;
					}
				}
			}
			catch(CDBException *e){
			e->ReportError();
			EndWaitCursor();
			return;
			}
			break;
		}
	}
	if(!bDelete)
		AfxMessageBox("����û��ѡ��Ҫɾ����ͨ��(��ʾ�������/���̷����ѡ��Ҫɾ������)");
	else
	{
		DispConvChannel();
///		DisplayConvInfoInAddr();

	}
}

void CPointEditSwitchIn::OnDblclkListConv(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	CString strMessage;
	strMessage.Format("Ҫ�޸ĵ�ǰ�����Ϣ��");
	if(AfxMessageBox(strMessage, MB_ICONQUESTION |MB_OKCANCEL)==IDOK)
	{
		m_ctrlEditChannel.SetReadOnly(TRUE);
		m_ctrlEditAddress.SetReadOnly(TRUE);
		m_ctrlEditPoint.SetReadOnly(TRUE);
		m_ctrlComboTrunkNo.EnableWindow(FALSE);
		//m_ctrlComboSensorType.EnableWindow(FALSE);
		m_ctrlComboSensorName.EnableWindow(FALSE);
		//m_ctrlComboSensorAccuracy.EnableWindow(FALSE);
		m_ctrlCheckMultiConv.EnableWindow(FALSE);
		m_ctrlCheckChange.SetCheck(1);
	}
	SetUpdateInfo();

	*pResult = 0;
}

void CPointEditSwitchIn::OnCheckChange() 
{
	// TODO: Add your control notification handler code here
	if(m_ctrlCheckChange.GetCheck())
	{
		CString strMessage;
		strMessage.Format("Ҫ�޸ĵ�ǰ�����Ϣ��");
		if(AfxMessageBox(strMessage, MB_ICONQUESTION |MB_OKCANCEL)==IDOK)
		{
			m_ctrlEditChannel.SetReadOnly(TRUE);
			m_ctrlEditAddress.SetReadOnly(TRUE);
			m_ctrlEditPoint.SetReadOnly(TRUE);
			m_ctrlComboTrunkNo.EnableWindow(FALSE);
			//m_ctrlComboSensorType.EnableWindow(FALSE);
			m_ctrlComboSensorName.EnableWindow(FALSE);
			//m_ctrlComboSensorAccuracy.EnableWindow(FALSE);
			m_ctrlCheckMultiConv.EnableWindow(FALSE);
		}
		SetUpdateInfo();
	}
	else
	{
			m_ctrlEditChannel.SetReadOnly(FALSE);
			m_ctrlEditAddress.SetReadOnly(FALSE);
			m_ctrlEditPoint.SetReadOnly(FALSE);
			m_ctrlComboTrunkNo.EnableWindow(TRUE);
			//m_ctrlComboSensorType.EnableWindow(TRUE);
			m_ctrlComboSensorName.EnableWindow(TRUE);
			//m_ctrlComboSensorAccuracy.EnableWindow(TRUE);
			m_ctrlCheckMultiConv.EnableWindow(TRUE);
	}
}

void CPointEditSwitchIn::SetUpdateInfo()
{
	//modified  
	//SendMessage(IDC_LIST_CONV,WM_LBUTTONDBLCLK);	
	CString strPoint;
	//modified  	
	int nItemCount=m_ctrlList.GetItemCount();
    for(int nItem=0;nItem<nItemCount;nItem++)
	{
		if(m_ctrlList.GetItemState(nItem,LVIS_SELECTED) & LVIS_SELECTED)
		{
				strPoint=m_ctrlList.GetItemText(nItem,1);
				break;
		}
	}
	if(strPoint=="")
	{
		AfxMessageBox("��ͨ����û�е�");
		return;
	}
	m_unEditPoint=m_String2DataType.String2Int(strPoint);
//	UpdateData(FALSE);
///	GetChnagePointInfo();
	UpdateData(FALSE);	
}

void CPointEditSwitchIn::OnButtonEdit12mode() 
{
	// TODO: Add your control notification handler code here
	CEdit12ModeDlg dlg;
	dlg.DoModal();
	
}

void CPointEditSwitchIn::OnSelchangeComboRecord() 
{
	// TODO: Add your control notification handler code here
	if (m_ctrlComboRecord.GetCurSel() == 1){
       m_ctrlEditKeepTime.EnableWindow(TRUE);
	}
	else
	   m_ctrlEditKeepTime.EnableWindow(FALSE);	
}

int CPointEditSwitchIn::GetChanelCount()
{
	int unChannelCount = 0;
	switch(m_ctrlComboSensorName.GetCurSel()){
	case 0 : unChannelCount = 8; break;
	case 1 : unChannelCount = 5; break;
	case 2 : unChannelCount = 8; break;
	case 3 : unChannelCount = 16; break;
	}
	return unChannelCount;
}

BOOL CPointEditSwitchIn::CheckKeepTimeFormat()
{
	BOOL result = TRUE;
	UpdateData(TRUE);
	CString temp = m_strEditKeepTime;
	if (temp.GetLength() != 10) 
		result = FALSE;
	else{
		if (temp.GetAt(4) != '/'){
			result = FALSE;
		}
		else if (temp.GetAt(7) != '/'){
		    result = FALSE;
		}
		else
		try{
			int yy = m_String2DataType.String2Int(temp.Left(4));
			int mm = m_String2DataType.String2Int(temp.Mid(5,2));
			if (mm > 23) 
				result = FALSE;
			else {
				int dd = m_String2DataType.String2Int(temp.Right(2));
				if (dd > 59)
					result = FALSE;
			}
		}
		catch(CException e){
			result = FALSE;
			e.Delete();
		}
	}
	if (result == FALSE)
		AfxMessageBox("���ڸ�ʽΪyyyy(0-9999)/mm(0-23)/dd(0-59)");
	return result;
}
