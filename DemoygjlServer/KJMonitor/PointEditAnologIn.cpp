// PointEditAnologIn.cpp : implementation file
//

#include "stdafx.h"
#include "KJMonitor.h"
#include "PointEditAnologIn.h"
#include "math.h"
#include "ViewDeleteAddr.h"
#include "CommStatusFM.h"
#include "MainFrm.h"
#include "Controls\\MABString.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPointEditAnologIn dialog


CPointEditAnologIn::CPointEditAnologIn(CWnd* pParent /*=NULL*/)
	: CDialog(CPointEditAnologIn::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPointEditAnologIn)
	m_unEditPoint =  1;
	m_unEditAddress = 0;
	m_dfEditMeaScopeMin=0.0;
	m_dfEditMeaScopeMax=0.0;
	m_strEditUnit = _T("");
	m_unEditWarnDelay = 0;
	m_strEditOtherExplain = _T("");
	m_strEditPointLabel = _T("");
	m_unEditChannel = 1;
	m_unEditWarnDelay=0;
	m_strEditOtherExplain= _T("");
	m_strEditPointLabel= _T("");
	m_unEditWarnMax = 0.0;
	m_unEditWarnMin = 0.0;
	//}}AFX_DATA_INIT

	m_bSave=FALSE;
	m_bSaveSuccess=FALSE;
	m_bGetChangePointInfo=FALSE;
	m_bPointEditChange=FALSE;
}


void CPointEditAnologIn::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPointEditAnologIn)
	DDX_Control(pDX, IDC_EDIT_CHANNEL, m_ctrlEditChannel);
	DDX_Control(pDX, IDC_EDIT_ADRESS, m_ctrlEditAddress);
	DDX_Control(pDX, IDC_CHECK_CHANGE, m_ctrlCheckChange);
	DDX_Control(pDX, IDC_BUTTON_DELETE, m_ctrlBtnDelete);
	DDX_Control(pDX, IDC_LIST_CONV, m_ctrlList);
	DDX_Control(pDX, IDC_COMBO_PRECISION, m_ctrlComboPrecision);
	DDX_Control(pDX, IDC_COMBO_PROCESSTYPE, m_ctrlComboProcessType);
	DDX_Control(pDX, IDC_COMBO_SCANFREQUENCY, m_ctrlComboScanFrequency);
	DDX_Control(pDX, IDC_COMBO_TRUNKNO, m_ctrlComboTrunkNo);
	DDX_Control(pDX, IDC_COMBO_WARNCLASS01, m_ctrlComboWarnClass);
	DDX_Control(pDX, IDC_BUTTON_VIEWDELETEADDRESS, m_ctrlBtnBiewDeleteAddress);
	DDX_Control(pDX, IDC_CHECK_MULTICONV, m_ctrlCheckMultiConv);
	DDX_Control(pDX, IDC_BUTTON_VIEWPOINT, m_ctrlBtnViewPoint);
	DDX_Control(pDX, IDC_BUTTON_VIEWADDR, m_ctrlBtnViewAddr);
	DDX_Control(pDX, IDC_COMBO_BSCAN01, m_ctrlComboBScan);
	DDX_Control(pDX, IDC_COMBO_SENSOR_ACCURACY, m_ctrlComboSensorAccuracy);
	DDX_Control(pDX, IDC_COMBO_SENSORNAME, m_ctrlComboSensorName);
	DDX_Control(pDX, IDC_BUTTON_POINTNOBACKWORD, m_btnPOINTNOBACKWORD);
	DDX_Control(pDX, IDC_BUTTON_POINTNOFORWORD, m_btnPOINTNOFORWORD);
	DDX_Control(pDX, IDOK, m_btnOK);
	DDX_Control(pDX, IDCANCEL, m_btnCANCEL);
	DDX_Control(pDX, IDC_BUTTON_ADDEDITANDGOON, m_btnADDEDITANDGOON);
	DDX_Control(pDX, IDC_COMBO_WARN01, m_ctrlComboWarn);
	DDX_Control(pDX, IDC_COMBO_SENSORTYPE, m_ctrlComboSensorType);
	DDX_Text(pDX, IDC_EDIT_POINTNO01, m_unEditPoint);
	DDX_Control(pDX, IDC_EDIT_POINTNO01, m_ctrlEditPoint);
	DDX_Text(pDX, IDC_EDIT_ADRESS, m_unEditAddress);
	DDX_Text(pDX, IDC_EDIT_MEASCOPEMIN01, m_dfEditMeaScopeMin);
	DDX_Text(pDX, IDC_EDIT_MEASCOPEMAX01, m_dfEditMeaScopeMax);
	DDX_Text(pDX, IDC_EDIT_UINT01, m_strEditUnit);
	DDV_MaxChars(pDX, m_strEditUnit, 8);
	DDX_Text(pDX, IDC_EDIT_WARNDELAY, m_unEditWarnDelay);
	DDX_Text(pDX, IDC_EDIT_OTHEREXPLAIN, m_strEditOtherExplain);
	DDV_MaxChars(pDX, m_strEditOtherExplain, 32);
	DDX_Text(pDX, IDC_EDIT_POINTLABEL, m_strEditPointLabel);
	DDV_MaxChars(pDX, m_strEditPointLabel, 8);
	DDX_Text(pDX, IDC_EDIT_CHANNEL, m_unEditChannel);
	DDX_Text(pDX, IDC_EDIT_WARNMAX01, m_unEditWarnMax);
	DDX_Text(pDX, IDC_EDIT_WARNMIN01, m_unEditWarnMin);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPointEditAnologIn, CDialog)
	//{{AFX_MSG_MAP(CPointEditAnologIn)
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
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPointEditAnologIn message handlers

BOOL CPointEditAnologIn::OnInitDialog() 
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

///	ConnectDB(); //Connect  DataBase
	m_ctrlComboSensorName.SetCurSel(3);
	m_ctrlComboSensorType.SetCurSel(7);
	m_ctrlComboSensorAccuracy.SetCurSel(7);
	m_ctrlComboScanFrequency.SetCurSel(0);
	m_ctrlComboPrecision.SetCurSel(0);
	m_ctrlComboProcessType.SetCurSel(0);
//	m_ctrlComboProcessType2.SetCurSel(0);
	m_ctrlComboTrunkNo.SetCurSel(0);
	m_ctrlComboWarnClass.SetCurSel(0);
	m_ctrlComboBScan.SetCurSel(1);
	m_ctrlComboWarn.SetCurSel(0);
//	m_ctrlComboPrintYN.SetCurSel(0);
	m_ctrlCheckChange.SetCheck(0);

	SetListHead();
	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CPointEditAnologIn::OnButtonPointnoforword() 
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

void CPointEditAnologIn::OnButtonPointnobackword() 
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

void CPointEditAnologIn::OnSelchangeComboSensortype() 
{
	
}

void CPointEditAnologIn::OnSelchangeComboSensorname() 
{
	// TODO: Add your control notification handler code here

	UINT untemp;
	untemp=m_ctrlComboSensorName.GetCurSel();
	switch(untemp)
	{
	case 0:  //1. ICO-�����ͼ���/һ����̼������[8λ1·]
		m_ctrlComboSensorType.SetCurSel(0);
		m_ctrlComboSensorAccuracy.SetCurSel(7);
		m_ctrlCheckMultiConv.SetCheck(0);
		break;
	case 1:  //2. A50-A�͵�·ģ���������ź�ת����[8λ]
		m_ctrlComboSensorType.SetCurSel(0);
		m_ctrlComboSensorAccuracy.SetCurSel(7);
		m_ctrlCheckMultiConv.SetCheck(0);
		break;
	case 2:  //3. MCA-8·ģ���������ź�ת����[12λ]
		m_ctrlComboSensorType.SetCurSel(7);
		m_ctrlComboSensorAccuracy.SetCurSel(11);
		m_ctrlCheckMultiConv.SetCheck(0);
		break;
	case 3:  //4. *MC8-8·ģ���������ź�ת����[8λ]
		m_ctrlComboSensorType.SetCurSel(7);
		m_ctrlComboSensorAccuracy.SetCurSel(7);
		m_ctrlCheckMultiConv.SetCheck(0);
		break;
	case 4:  //5. C3-ģ��������ź�ת����(C3-C5)[6λ]
		m_ctrlComboSensorType.SetCurSel(0);
		m_ctrlComboSensorAccuracy.SetCurSel(5);
		m_ctrlCheckMultiConv.SetCheck(0);
		break;
	case 5:  //*6. D1-���������ۼ���[16λ]
		if(!m_bGetChangePointInfo)
		{
		if(AfxMessageBox("���ڶ๦��ת��������", MB_ICONQUESTION |MB_OKCANCEL)==IDOK)
			m_ctrlCheckMultiConv.SetCheck(1);
		else
			m_ctrlCheckMultiConv.SetCheck(0);
		}
		//modified 2003/8/30
		m_ctrlComboSensorType.SetCurSel(1);
		m_ctrlComboSensorAccuracy.SetCurSel(15);
		break;
	case 6:      //ģ���ź�ת����[8λ4·]
		if(!m_bGetChangePointInfo)
		{
		if(AfxMessageBox("4·ģ��ת����[8λ],�๦��", MB_ICONQUESTION |MB_OKCANCEL)==IDOK)
			m_ctrlCheckMultiConv.SetCheck(1);
		else
			m_ctrlCheckMultiConv.SetCheck(0);
		}
		m_ctrlComboSensorType.SetCurSel(3);
		m_ctrlComboSensorAccuracy.SetCurSel(7);
		break;
	default:
		break;
	}
	if(!m_bGetChangePointInfo)
		OnButtonViewaddr();
//	SetEditBoxStyle(m_ctrlComboSensorType.GetCurSel()+1);
}

void CPointEditAnologIn::GetChnagePointInfo()
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
				case 3: unConnectorID=15;	m_ctrlCheckMultiConv.SetCheck(1); break;  //11
				case 4:	unConnectorID=10;	m_ctrlCheckMultiConv.SetCheck(1); break;
				default: m_ctrlCheckMultiConv.SetCheck(0); break;
				}
				m_ctrlComboSensorName.SetCurSel(unConnectorID-4-1);
				UpdateData(FALSE);
				m_bGetChangePointInfo=TRUE;
				OnSelchangeComboSensorname();
				m_bGetChangePointInfo=FALSE;

				bAnyPoint=1;
			}
		}
		if((bAnyPoint)&&(strbValueType=="1"))
		{
				strSQL.Format("SELECT * FROM uAnologPointProperty WHERE unPointNo=%d",m_unEditPoint);
				if( m_SQLDirect.ExecuteSQL(strSQL)==SQL_SUCCESS)
				{
					if(!m_SQLDirect.Fetch())
					{
						CString strunPointNo=m_SQLDirect.GetCol(1);     //1 ���
						m_dfEditMeaScopeMin=m_String2DataType.String2Double(m_SQLDirect.GetCol(2));  //2 fMeasureMinֵ��Χ����Сֵ
						m_dfEditMeaScopeMax=m_String2DataType.String2Double(m_SQLDirect.GetCol(3));  //3. fMeasureMax(float);ֵ��Χ�����ֵ
						UINT unBitNumber=m_String2DataType.String2Int(m_SQLDirect.GetCol(4));     //4. unBitNumber(unsigned int);ת����λ����6,8,12,16 Vmax�ֱ�Ϊ: 63(6) 255(8) 4095(12) 65535(16)
						UINT unWarnCause=m_String2DataType.String2Int(m_SQLDirect.GetCol(5));     //5. unWarnCause(unsigned int);�����๲Ϊ8�֣�ԭ���������룬����¼��P22
						UINT unWarnMode=m_String2DataType.String2Int(m_SQLDirect.GetCol(6));      //6. unWarnMode(unsigned int);P18�������ޡ��������޵����÷���P18
						m_unEditWarnMin=m_String2DataType.String2Double(m_SQLDirect.GetCol(7));  //7. unWarnMinValue(unsigned int);��������
						m_unEditWarnMax=m_String2DataType.String2Double(m_SQLDirect.GetCol(8));  //8. unWarnMaxValue(unsigned int);��������
						m_strEditUnit=m_SQLDirect.GetCol(9) ;        //9. strUnit (CString); ���̵�λ
						UINT unProcessType=m_String2DataType.String2Int(m_SQLDirect.GetCol(11));   //11. unProcessType;��������
						UINT unPrecision=m_String2DataType.String2Int(m_SQLDirect.GetCol(12));      //12. unPrecision;����λ��
						m_unEditWarnDelay=m_String2DataType.String2Int(m_SQLDirect.GetCol(13));      //13. unWarnDelay;�����ӳ�

						m_ctrlComboPrecision.SetCurSel(unPrecision);
						m_ctrlComboProcessType.SetCurSel(unProcessType);

						m_ctrlComboWarnClass.SetCurSel(unWarnCause);
						m_ctrlComboWarn.SetCurSel(unWarnMode);   //mode
						
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

BOOL CPointEditAnologIn::DisplayConvInfoInAddr()
{
	BOOL bMultiConv=0;
	BOOL bAnyPoint=0;
	UINT unChannelPointNo[MAX_CHANNEL_NUMBER];
	for(int i=0;i<MAX_CHANNEL_NUMBER;i++)
		unChannelPointNo[i]=0;
	CString strSQL,strtemp,strbValueType;
	CViewDeleteAddr viewdelteaddr;

	if(m_ctrlComboSensorName.GetCurSel()==6)
     	m_unConvID=m_ctrlComboSensorName.GetCurSel()+1+8;
	else
     	m_unConvID=m_ctrlComboSensorName.GetCurSel()+1+4;

	if(m_ctrlCheckMultiConv.GetCheck()) 
	{
		switch(m_unConvID)
		{
		case 15:   //11
			m_unConvID=3;
			break;
		case 10:
			m_unConvID=4;
			break;
		default:
			AfxMessageBox("�๦��ת������֧�ִ˴���������,��ȥ���๦��ת����ѡ��");
			return FALSE;
			break;
		}
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
				m_ctrlList.SetItem(unChannel-1, 16, LVIF_TEXT, strstrExplain, 0, NULL, NULL, NULL);

				bAnyPoint=TRUE;
				nRet=m_SQLDirect.Fetch();
			}
		}
		if((bAnyPoint)&&(strbValueType=="1"))
			for(int iChannel=0;iChannel<m_ctrlComboSensorType.GetCurSel()+1;iChannel++)
			{
				if(!unChannelPointNo[iChannel]) continue;
				strSQL.Format("SELECT * FROM uAnologPointProperty WHERE unPointNo=%d",unChannelPointNo[iChannel]);
				if( m_SQLDirect.ExecuteSQL(strSQL)==SQL_SUCCESS)
				{
					int nRet=m_SQLDirect.Fetch();
					if(!nRet)
					{
						CString strunPointNo=m_SQLDirect.GetCol(1);     //1 ���
						double fMeasureMin = m_String2DataType.String2Double(m_SQLDirect.GetCol(2));    //2 fMeasureMinֵ��Χ����Сֵ
						double fMeasureMax = m_String2DataType.String2Double(m_SQLDirect.GetCol(3));      //3. fMeasureMax(float);ֵ��Χ�����ֵ
						CString strfMeasureMin,strfMeasureMax;
						strfMeasureMin.Format("%.3f",fMeasureMin);    
						strfMeasureMax.Format("%.3f",fMeasureMax);
						CString strunBitNumber=m_SQLDirect.GetCol(4);     //4. unBitNumber(unsigned int);ת����λ����6,8,12,16 Vmax�ֱ�Ϊ: 63(6) 255(8) 4095(12) 65535(16)
						UINT unWarnCause =  m_String2DataType.String2Int(m_SQLDirect.GetCol(5)) + 1;
						CString strunWarnCause;
						strunWarnCause.Format("%d", unWarnCause);     //5. unWarnCause(unsigned int);�����๲Ϊ8�֣�ԭ���������룬����¼��P22
						UINT ucWarnMode = m_String2DataType.String2Int(m_SQLDirect.GetCol(6)); //6. unWarnMode(unsigned int);P18�������ޡ��������޵����÷���P18
						CString strunWarnMode;
						strunWarnMode.Format("%d",ucWarnMode);
						double unWarnMinValue = m_String2DataType.String2Double(m_SQLDirect.GetCol(7));
						double unWarnMaxValue = m_String2DataType.String2Double(m_SQLDirect.GetCol(8));
						CString strunWarnMinValue,strunWarnMaxValue;
						strunWarnMinValue.Format("%.3f",unWarnMinValue);    //7. unWarnMinValue(unsigned int);��������
						strunWarnMaxValue.Format("%.3f",unWarnMaxValue);    //8. unWarnMaxValue(unsigned int);��������
						CString strstrUnit=m_SQLDirect.GetCol(9) ;        //9. strUnit (CString); ���̵�λ
						CString strbPrint=m_SQLDirect.GetCol(10);        //10. bPrint(BOOL 1/0);�Ƿ��ӡ 1����ӡ 0������ӡ
						CString strunProcessType=m_SQLDirect.GetCol(11);   //11. unProcessType;��������
						CString strunPrecision=m_SQLDirect.GetCol(12);      //12. unPrecision;����λ��
						CString strunWarnDelay=m_SQLDirect.GetCol(13);      //13. unWarnDelay;�����ӳ�
						if(strunProcessType=="0") strunProcessType="������";
						else if(strunProcessType=="1") strunProcessType="5��ȡ��";
						else if(strunProcessType=="2") strunProcessType="3��ȡ��";
						CStringEx xstring1(strfMeasureMin);
						CStringEx xstring2(strfMeasureMax);
						CString strf1,strf2;
						strf1.Format("%.3f",xstring1.GetFloat());
						strf2.Format("%.3f",xstring2.GetFloat());
						m_ctrlList.SetItem(iChannel, 6, LVIF_TEXT, strf1, 0, NULL, NULL, NULL);
						m_ctrlList.SetItem(iChannel, 7, LVIF_TEXT, strf2, 0, NULL, NULL, NULL);
						m_ctrlList.SetItem(iChannel, 8, LVIF_TEXT, strstrUnit, 0, NULL, NULL, NULL);
						m_ctrlList.SetItem(iChannel, 9, LVIF_TEXT, strunPrecision, 0, NULL, NULL, NULL);
						m_ctrlList.SetItem(iChannel, 10, LVIF_TEXT, strunProcessType, 0, NULL, NULL, NULL);
						m_ctrlList.SetItem(iChannel, 11, LVIF_TEXT, strunWarnCause, 0, NULL, NULL, NULL);
						m_ctrlList.SetItem(iChannel, 12, LVIF_TEXT, strunWarnMinValue, 0, NULL, NULL, NULL);
						m_ctrlList.SetItem(iChannel, 13, LVIF_TEXT, strunWarnMaxValue, 0, NULL, NULL, NULL);
						m_ctrlList.SetItem(iChannel, 14, LVIF_TEXT, strunWarnMode, 0, NULL, NULL, NULL);
						m_ctrlList.SetItem(iChannel, 15, LVIF_TEXT, strunWarnDelay, 0, NULL, NULL, NULL);
					}
				}
			}
	}
	catch(CDBException *e){
	e->ReportError();
	EndWaitCursor();
	return FALSE;
	}
	// size to fit the columns
	//m_ctrlList.AutoSizeColumn();
	return TRUE;
}

void CPointEditAnologIn::ConnectDB()
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

void CPointEditAnologIn::OnDestroy() 
{
	CDialog::OnDestroy();
	
	// TODO: Add your message handler code here
	m_SQLDirect.Close();
}

void CPointEditAnologIn::OnButtonAddeditandgoon()   //save then go on
{	
	// TODO: Add your control notification handler code here,unbPrint
	UINT unbScan,unbMultiConv,unSamePointNum=0,unbValueType;
	unsigned char ucScanFreq[7]={1,2,4,8,16,32,64};
	CString strtemp;
	m_bSave=TRUE;
	m_bSaveSuccess=FALSE;
	UpdateData(TRUE);
	if(!IsWarnMinMaxRight())
		return;
	if(m_ctrlCheckMultiConv.GetCheck()) 
		unbMultiConv=1;
	else
		unbMultiConv=0;

	if(m_ctrlComboSensorName.GetCurSel()==6)
     	m_unConvID=m_ctrlComboSensorName.GetCurSel()+1+8;
	else
     	m_unConvID=m_ctrlComboSensorName.GetCurSel()+1+4;

	if(unbMultiConv)
	{
		switch(m_unConvID)
		{
		case 15:    //11
			m_unConvID=3;
			break;
		case 10:
			m_unConvID=4;
			break;
		default:
			m_bSaveSuccess=FALSE;
			AfxMessageBox("�๦��ת������֧�ִ˴���������");
			return;
			break;
		}
	}
	if(!m_ctrlCheckChange.GetCheck())
	{
///		if((!FindAddrConvChanInfo())||(!FindPointInfo()))
///			return;
		if((m_unEditChannel<1)||(m_unEditChannel>((unsigned int)m_ctrlComboSensorType.GetCurSel()+1)))
		{
			strtemp.Format("ͨ����Ӧ��1~%d֮�䣬����������",m_ctrlComboSensorType.GetCurSel()+1);
			AfxMessageBox(strtemp);
			return;
		}
	}
	unbValueType=1; //1:anolog 0:switch

	try
	{
		CString strSQL,strtemp;
		unbScan=m_ctrlComboBScan.GetCurSel();
//		unbPrint=m_ctrlComboPrintYN.GetCurSel();
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

		if(m_ctrlCheckChange.GetCheck())
		{
			strSQL.Format("UPDATE uAnologPointProperty SET fMeasureMin=%.4f, fMeasureMax=%.4f, unBitNumber=%d,unWarnCause=%d,	unWarnMode=%d,unWarnMinValue=%f, unWarnMaxValue=%f,	strUnit='%s', unProcessType=%d,unPrecision= %d,unWarnDelay=%d WHERE unPointNo=%d",
				m_dfEditMeaScopeMin,
				m_dfEditMeaScopeMax,
				m_ctrlComboSensorAccuracy.GetCurSel(),
				m_ctrlComboWarnClass.GetCurSel(),
				m_ctrlComboWarn.GetCurSel(),
				m_unEditWarnMin,
				m_unEditWarnMax,
				m_strEditUnit,
//				m_ctrlComboPrintYN.GetCurSel(),,unProcessType2=%dbPrint=%d,
				m_ctrlComboProcessType.GetCurSel(),
				m_ctrlComboPrecision.GetCurSel(),
				m_unEditWarnDelay,
//				m_ctrlComboProcessType2.GetCurSel(),
				m_unEditPoint);
		}
		else
		{
			strtemp.Format(" VALUES(%d, %.4f, %.4f, %d, %d, %d, %f, %f, '%s', %d, %d, %d)",
				m_unEditPoint,
				m_dfEditMeaScopeMin,
				m_dfEditMeaScopeMax,
				m_ctrlComboSensorAccuracy.GetCurSel(),
				m_ctrlComboWarnClass.GetCurSel(),
				m_ctrlComboWarn.GetCurSel(),
				m_unEditWarnMin,
				m_unEditWarnMax,
				m_strEditUnit,
//				m_ctrlComboPrintYN.GetCurSel(),
				m_ctrlComboProcessType.GetCurSel(),
				m_ctrlComboPrecision.GetCurSel(),
				m_unEditWarnDelay);  //,
//				m_ctrlComboProcessType2.GetCurSel());,unProcessType2, bPrint,%d %d,
			strSQL=_T("INSERT INTO uAnologPointProperty (unPointNo, fMeasureMin, fMeasureMax, unBitNumber, unWarnCause, unWarnMode, unWarnMinValue, unWarnMaxValue, strUnit,unProcessType,unPrecision,unWarnDelay) ");
			strSQL+=strtemp;
		}
		//AfxMessageBox(strSQL);
		if( m_SQLDirect.ExecuteSQL(strSQL)!=SQL_SUCCESS)
		{
			AfxMessageBox("uAnologPointProperty����ʧ�ܣ���������ݿ�ԭ��");
			m_bSaveSuccess=FALSE;
			return;
		}
		else	//��ӵĴ���
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

void CPointEditAnologIn::OnOK()    //save then exit 
{
	// TODO: Add extra validation here
///	OnButtonAddeditandgoon();
	if(!m_bSaveSuccess)
		return;
	//RebuildScanQue();
	CDialog::OnOK();
}

void CPointEditAnologIn::OnCancel() 
{
	// TODO: Add extra cleanup here
	//RebuildScanQue();
	CDialog::OnCancel();
}

void CPointEditAnologIn::RebuildScanQue()
{
	CMainFrame* pFWnd=(CMainFrame*)AfxGetMainWnd();
	CCommStatusFM *pCommStatusFM=pFWnd->m_pCommStatusFM;
	if(m_bPointEditChange)            //&&(pCommStatusFM->m_bStartScan))   //11/14
			pCommStatusFM->m_bStartScan=FALSE;
}

void CPointEditAnologIn::DispConvChannel()
{
	m_ctrlList.DeleteAllItems();
	for(int iItem=0;iItem<m_ctrlComboSensorType.GetCurSel()+1;iItem++)
	{
		CString strItem;
		strItem.Format("%d",iItem+1);
		m_ctrlList.InsertItem(iItem,strItem,0);
		m_ctrlList.SetItem(iItem, 1, LVIF_TEXT,"", 0, NULL, NULL, NULL);
	}
}

void CPointEditAnologIn::SetListHead()
{
	//m_ctrlListConv
	m_ctrlList.InsertColumn(0, _T("ͨ��"),   LVCFMT_CENTER, 36);
	m_ctrlList.InsertColumn(1, _T("���"),   LVCFMT_CENTER, 36);
	m_ctrlList.InsertColumn(2, _T("��ǩ"),   LVCFMT_CENTER, 60);
	m_ctrlList.InsertColumn(3, _T("ת��������"), LVCFMT_CENTER, 72);
	m_ctrlList.InsertColumn(4, _T("Ƶ��"), LVCFMT_CENTER, 36);
	m_ctrlList.InsertColumn(5, _T("ɨ��"),   LVCFMT_CENTER, 36);
	m_ctrlList.InsertColumn(6, _T("ֵ����Сֵ"),   LVCFMT_CENTER, 72);
	m_ctrlList.InsertColumn(7, _T("ֵ�����ֵ"),   LVCFMT_CENTER, 72);
	m_ctrlList.InsertColumn(8, _T("��λ"),   LVCFMT_CENTER, 36);
	m_ctrlList.InsertColumn(9, _T("����"),   LVCFMT_CENTER, 36);
	m_ctrlList.InsertColumn(10, _T("��������"),   LVCFMT_CENTER, 60);
	m_ctrlList.InsertColumn(11, _T("������"),   LVCFMT_CENTER, 48);
	m_ctrlList.InsertColumn(12, _T("��������"),   LVCFMT_CENTER, 60);
	m_ctrlList.InsertColumn(13, _T("��������"),   LVCFMT_CENTER, 60);
	m_ctrlList.InsertColumn(14, _T("����ģʽ"),   LVCFMT_CENTER, 60);
	m_ctrlList.InsertColumn(15, _T("�����ӳ�"),   LVCFMT_CENTER, 60);
	m_ctrlList.InsertColumn(16, _T("����˵��"),   LVCFMT_CENTER, 90);

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

BOOL CPointEditAnologIn::FindAddrConvChanInfo(void)
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

BOOL CPointEditAnologIn::FindPointInfo()
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

void CPointEditAnologIn::OnButtonViewpoint() 
{
	// TODO: Add your control notification handler code here
	m_bSave=FALSE;
///	FindPointInfo();
}

void CPointEditAnologIn::OnButtonViewaddr() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	DispConvChannel();
///	DisplayConvInfoInAddr();
}




BOOL CPointEditAnologIn::IsWarnMinMaxRight()
{
	if(m_unEditWarnDelay>=60)
	{
		AfxMessageBox("�����ӳٱ�����(0~60s)֮�䣬����������");
		return FALSE;
	}
	return TRUE;
}

void CPointEditAnologIn::OnButtonViewdeleteaddress() 
{
	// TODO: Add your control notification handler code here
	CViewDeleteAddr dlgViewDeleteAddr;
	UpdateData(TRUE);
//	dlgViewDeleteAddr.m_unTrunkNo=m_unEditGanxian;
	dlgViewDeleteAddr.DoModal();
}

void CPointEditAnologIn::OnButtonDelete() 
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
							AfxMessageBox("ɾ��ʧ�ܣ���ͨ��SQL SERVER ��ҵ�������鿴��uAnologPointProperty���uSwitchPointProperty������");
						}
						else		//��ӵĴ���
							theApp.OnSendSQL(strSQL1);

						strSQL.Format("DELETE FROM uPointProperty WHERE unPointNo=%s",strpoint);
						if(m_SQLDirect.ExecuteSQL(strSQL)!=SQL_SUCCESS)
						{
							AfxMessageBox("ɾ��ʧ�ܣ���ͨ��SQL SERVER ��ҵ�������鿴���ݣ�������ɵĲ�����б�Ǹ");
						}
						else		//��ӵĴ���
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
		AfxMessageBox("����û��ѡ��Ҫɾ���ĵ�/ͨ��(��ʾ�������/���̷����ѡ��Ҫɾ������)");
	else
	{
		DispConvChannel();
///		DisplayConvInfoInAddr();

	}
}

void CPointEditAnologIn::OnDblclkListConv(NMHDR* pNMHDR, LRESULT* pResult) 
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
		m_ctrlComboSensorType.EnableWindow(FALSE);
		m_ctrlComboSensorName.EnableWindow(FALSE);
		m_ctrlComboSensorAccuracy.EnableWindow(FALSE);
		m_ctrlCheckMultiConv.EnableWindow(FALSE);
		m_ctrlCheckChange.SetCheck(1);
	}
	SetUpdateInfo();
	*pResult = 0;
}

void CPointEditAnologIn::OnCheckChange() 
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
			m_ctrlComboSensorType.EnableWindow(FALSE);
			m_ctrlComboSensorName.EnableWindow(FALSE);
			m_ctrlComboSensorAccuracy.EnableWindow(FALSE);
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
			m_ctrlComboSensorType.EnableWindow(TRUE);
			m_ctrlComboSensorName.EnableWindow(TRUE);
			m_ctrlComboSensorAccuracy.EnableWindow(TRUE);
			m_ctrlCheckMultiConv.EnableWindow(TRUE);
	}
}

void CPointEditAnologIn::SetUpdateInfo()
{
	CString strPoint;
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
///	GetChnagePointInfo();
	UpdateData(FALSE);

}




