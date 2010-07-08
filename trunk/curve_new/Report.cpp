// Report.cpp : implementation file
//

#include "stdafx.h"
#include "curve.h"
#include "Report.h"
#include "Excel9.h" 
#include "comdef.h" 
#include "MainFrm.h"
#include "String2DataType.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CReport dialog


CReport::CReport(CWnd* pParent /*=NULL*/)
	: CDialog(CReport::IDD, pParent)
{
	//{{AFX_DATA_INIT(CReport)
	m_ctrlDefine = _T("");
	m_ctrlStartH = 0;
	m_ctrlEndH = 0;
	m_ctrlEndMin = 0;
	m_ctrlStartMin = 0;
	m_startDateTime = 0;
	m_endDateTime = 0;
	//}}AFX_DATA_INIT
	m_unTrunkNo=1;
	m_bExcelInit=false;
	m_ctrlStartSecond = 0;
	m_ctrlEndSecond = 0;
}


void CReport::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CReport)
	DDX_Control(pDX, IDC_BUT_ADDEDIT, m_ctrlBtnADDEDIT);
	DDX_Control(pDX, IDC_BUT_DEL_COLLUN, m_ctrlBtnDELCOLLUM);
	DDX_Control(pDX, IDC_BUT_ADD_COLLUM, m_ctrlBtnADDCOLLUM);
	DDX_Control(pDX, IDC_LIST_NOWCOLLUM, m_ctrlNowCollum);
	DDX_Control(pDX, IDC_LIST_COLLUM, m_ctrlCollum);
	DDX_Control(pDX, IDC_BUTTON_REPORT, m_ctrlBtnReport);
	DDX_Control(pDX, IDC_BUTTON_DESELECTALL, m_ctrlBtnDeselectAll);
	DDX_Control(pDX, IDC_BUTTON_DESELECT1, m_ctrlBtnDeselect1);
	DDX_Control(pDX, IDC_BUTTON_ADDALL, m_ctrlBtnAddAll);
	DDX_Control(pDX, IDC_BUTTON_ADD1, m_ctrlBtnAdd1);
	DDX_Control(pDX, IDC_COMBO_SELECTTRUNK, m_ctrlComboSelectTrunk);
	DDX_Control(pDX, IDC_LIST_REPORTTABLE, m_ctrlListReportTable);
	DDX_Control(pDX, IDC_LIST_ADDR, m_ctrlList);
	DDX_Text(pDX, IDC_EDIT_DEFINE, m_ctrlDefine);
	DDV_MaxChars(pDX, m_ctrlDefine, 54);
	DDX_Text(pDX, IDC_EDIT_STARTH, m_ctrlStartH);
	DDV_MinMaxUInt(pDX, m_ctrlStartH, 0, 23);
	DDX_Text(pDX, IDC_EDIT_ENDH, m_ctrlEndH);
	DDV_MinMaxUInt(pDX, m_ctrlEndH, 0, 23);
	DDX_Text(pDX, IDC_EDIT_ENDMIN, m_ctrlEndMin);
	DDV_MinMaxUInt(pDX, m_ctrlEndMin, 0, 59);
	DDX_Text(pDX, IDC_EDIT_STARTMIN, m_ctrlStartMin);
	DDV_MinMaxUInt(pDX, m_ctrlStartMin, 0, 59);
	DDX_Control(pDX, IDC_DATETIMEPICKERSTART, m_ctrlStartTime);
	DDX_Control(pDX, IDC_DATETIMEPICKEREND, m_ctrlEndTime);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CReport, CDialog)
	//{{AFX_MSG_MAP(CReport)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BUTTON_DESELECTALL, OnButtonDeselectall)
	ON_BN_CLICKED(IDC_BUTTON_DESELECT1, OnButtonDeselect1)
	ON_BN_CLICKED(IDC_BUTTON_ADDALL, OnButtonAddall)
	ON_BN_CLICKED(IDC_BUTTON_ADD1, OnButtonAdd1)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_ADDR, OnDblclkListAddr)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_REPORTTABLE, OnDblclkListReporttable)
	ON_CBN_SELCHANGE(IDC_COMBO_SELECTTRUNK, OnSelchangeComboSelecttrunk)
	ON_BN_CLICKED(IDC_BUTTON_REPORT, OnButtonReport)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_COLLUM, OnDblclkListCollum)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_NOWCOLLUM, OnDblclkListNowcollum)
	ON_BN_CLICKED(IDC_BUT_ADDEDIT, OnButAddedit)
	ON_BN_CLICKED(IDC_BUT_ADD_COLLUM, OnButAddCollum)
	ON_BN_CLICKED(IDC_BUT_DEL_COLLUN, OnButDelCollun)
	ON_NOTIFY(DTN_CLOSEUP, IDC_DATETIMEPICKERSTART, OnCloseupDatetimepickerstart)
	ON_NOTIFY(DTN_CLOSEUP, IDC_DATETIMEPICKEREND, OnCloseupDatetimepickerend)
	ON_EN_CHANGE(IDC_EDIT_STARTH, OnChangeEditStarth)
	ON_EN_CHANGE(IDC_EDIT_ENDH, OnChangeEditEndh)
	ON_EN_CHANGE(IDC_EDIT_STARTMIN, OnChangeEditStartmin)
	ON_EN_CHANGE(IDC_EDIT_ENDMIN, OnChangeEditEndmin)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CReport message handlers

void CReport::OnButtonReport() 
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
	strXltPath += _T("ReportXLT\\Report.xlt");

	wbMyBook.AttachDispatch(wbsMyBooks.Add(_variant_t(strXltPath))); 
	//得到Worksheets 
	wssMysheets.AttachDispatch(wbMyBook.GetWorksheets(),true); 
	//得到sheet1 
	wsMysheet.AttachDispatch(wssMysheets.GetItem(_variant_t("sheet1")),true); 
	//得到全部Cells，此时,rgMyRge是cells的集合 
	rgMyRge.AttachDispatch(wsMysheet.GetCells(),true); 
	//设置1行1列的单元的值 
	CString strSQL,strPointNo,strNowCollum;
	CString2DataType Str2Data;

				CString strMaxValue =_T("最大值");
				CString strMaxValueTime =_T("最大值时间");
				CString strMinValue =_T("最小值");
				CString strMinValueTime =_T("最小值时间");
				CString strMidValue = _T("平均值");
				CString strAlarmCal =_T("报警次数");
				CString strAlarmTimer =_T("报警时间段");
				CString strSensorstation =_T("探头安装位置");
				CString strRunTimer =_T("设备运行累计时间");
				CString strStartmd1 =_T("开机时间（MD1）");
				CString strStartmd2 =_T("开机时间（MD2）");
				CString strServiceName =_T("设备名称");

        m_strStartTime.Format("%d-%d-%d",m_startDateTime.GetYear(),m_startDateTime.GetMonth(),m_startDateTime.GetDay());
       	m_strEndTime.Format("%d-%d-%d",m_endDateTime.GetYear(),m_endDateTime.GetMonth(),m_endDateTime.GetDay());

	           int sYear,sMonth,sDay,eYear,eMonth,eDay,timelen;

            	GetDateR(eYear,eMonth,eDay,m_strEndTime);
            	GetDateR(sYear,sMonth,sDay,m_strStartTime);

				timelen = (((((eYear - sYear)*12 +(eMonth - sMonth))*30 
                    		+ (eDay - sDay))*24 + (m_ctrlEndH - m_ctrlStartH))*60*60 
	                    	+ (m_ctrlEndMin - m_ctrlStartMin)*60);	

//            	if(timelen <=0)
//					return;

       	int iExcelRow=3;
       	int iExcelCollum=2; 
		int nItemCount2=m_ctrlNowCollum.GetItemCount();
    	for(int iItem=0; iItem<nItemCount2 - 2; iItem++)
		{
				int nItemCount1=m_ctrlListReportTable.GetItemCount();
                strNowCollum = m_ctrlNowCollum.GetItemText(0,0);
	        	rgMyRge.SetItem(_variant_t((long)1),_variant_t((long)1),_variant_t(strNowCollum)); 
                strNowCollum = _T("点号");
	        	rgMyRge.SetItem(_variant_t((long)2),_variant_t((long)1),_variant_t(strNowCollum)); 
                strNowCollum = m_ctrlNowCollum.GetItemText((nItemCount2 - 1),0);
	        	rgMyRge.SetItem(_variant_t((long)(nItemCount1 + 8)),_variant_t((long)1),_variant_t(strNowCollum)); 
	    		strNowCollum=m_ctrlNowCollum.GetItemText((iItem+1),0); 
				rgMyRge.SetItem(_variant_t((long)2),_variant_t((long)(iItem+2)),_variant_t(strNowCollum)); 
			  if(iItem == 0)
			  {
				int nItemCount1=m_ctrlListReportTable.GetItemCount();
            	for(int iListItem=0; iListItem<nItemCount1; iListItem++)
				{
		        	strPointNo=m_ctrlListReportTable.GetItemText(iListItem,0);
	    	    	rgMyRge.SetItem(_variant_t((long)iExcelRow),_variant_t((long)1),_variant_t(strPointNo)); 
  	         	    iExcelRow++;
				}
                iExcelRow=3;
			  }
		}

        try
		{
         	int nItemCount3=m_ctrlNowCollum.GetItemCount();
        	for(int iItem=0; iItem<nItemCount3-0; iItem++)
			{
	    		strNowCollum=m_ctrlNowCollum.GetItemText((iItem+1),0); 
			  if((strNowCollum==strServiceName)||(strNowCollum==strSensorstation))
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
								if(strNowCollum==strSensorstation){
			        	        	CString strstrLabel=m_SQLDirect.GetCol(10);	//标签名称
		         		        	rgMyRge.SetItem(_variant_t((long)iExcelRow),_variant_t((long)(iItem+2)),_variant_t(strstrLabel)); 
								}
						    	else if(strNowCollum==strServiceName){
     		        		    	CString strstrExplain=m_SQLDirect.GetCol(11); // 说明
		         		        	rgMyRge.SetItem(_variant_t((long)iExcelRow),_variant_t((long)(iItem+2)),_variant_t(strstrExplain)); 
								}
     	         			iExcelRow++;
						}
					}
				}
                iExcelRow=3;
			  }
			  if(strNowCollum==strRunTimer)
			  {
				int nItemCount1=m_ctrlListReportTable.GetItemCount();
            	for(int iListItem=0; iListItem<nItemCount1; iListItem++)
				{
                    CString strbValueType = _T("") ;
		        	strPointNo=m_ctrlListReportTable.GetItemText(iListItem,0);

					strSQL.Format("SELECT * FROM uPointProperty WHERE unPointNo = %s ",strPointNo);
	        		if( m_SQLDirect.ExecuteSQL(strSQL)==SQL_SUCCESS)
					{
		        		int nRet=m_SQLDirect.Fetch();
		        		if(!nRet)
						{
		         			strbValueType=m_SQLDirect.GetCol(6);
						}
					}
   
                    if(strbValueType == "1")
					{
		         			iExcelRow++;
					}
                    else if(strbValueType == "0")
					{
    					strSQL.Format("SELECT * FROM uSwitchPointProperty WHERE unPointNo = %s ",strPointNo);
	        	    	if( m_SQLDirect.ExecuteSQL(strSQL)==SQL_SUCCESS)
						{
		        	    	int nRet=m_SQLDirect.Fetch();
		        	    	if(!nRet)
							{
		        		    	CString strRun=m_SQLDirect.GetCol(8);         // 说明
						        strRun.Insert(4,"天");
					      	    strRun.Insert(8,"小时");
					     	    strRun.Insert(14,"分钟");
		         	      		rgMyRge.SetItem(_variant_t((long)iExcelRow),_variant_t((long)(iItem+2)),_variant_t(strRun)); 
		         	     		iExcelRow++;
							}
						}
					}
				}
                iExcelRow=3;
			  }
			  if((strNowCollum==strMaxValue)||(strNowCollum==strMinValue)||(strNowCollum==strMidValue)||(strNowCollum==strMaxValueTime)||(strNowCollum==strMinValueTime))
			  {
				  int nItemCount1=m_ctrlListReportTable.GetItemCount();
            	for(int iListItem=0; iListItem<nItemCount1; iListItem++)
				{
					CString strMidValueT = _T("");
                    unsigned long TValue =0;
                    unsigned short  MaxValue ,MinValue,TrueValue,MidValue;
                    MaxValue = MinValue = TrueValue = MidValue =0;
                    unsigned short  TCal =0;
                    CString strbValueType = _T("") ;
					strPointNo=m_ctrlListReportTable.GetItemText(iListItem,0);
         
		            strSQL.Format("SELECT * FROM uPointProperty WHERE unPointNo = %s ",strPointNo);
	        		if( m_SQLDirect.ExecuteSQL(strSQL)==SQL_SUCCESS)
					{
		        		int nRet=m_SQLDirect.Fetch();
		        		if(!nRet)
						{
		         			strbValueType=m_SQLDirect.GetCol(6);
						}
					}
   
                    if(strbValueType == "1")
					{
		              strSQL.Format("SELECT * FROM uCollectData WHERE unPointNo = %s ",strPointNo);
	        	   	  if( m_SQLDirect.ExecuteSQL(strSQL) == SQL_SUCCESS)
					  {
		        		int nRet=m_SQLDirect.Fetch();
		        		while(!nRet)
						{
	                     	int nYear,nMonth,nDay,nHour,nMinute,nSecond;
	    			        CString strdata = m_SQLDirect.GetCol(2);
			                CString	CalTime = m_SQLDirect.GetCol(3);
							unsigned short data = Str2Data.String2Int(strdata);
  							GetDateR(nYear,nMonth,nDay,nHour,nMinute,nSecond,CalTime);

				            int lapse = (((((nYear - sYear)*12 + (nMonth - sMonth))*30 + (nDay - sDay))*24 + (nHour - m_ctrlStartH))*60 + nMinute - m_ctrlStartMin)*60 + nSecond;
			         		lapse -= m_ctrlStartSecond;
			        		if((lapse < timelen) && (lapse >=0))
							{
                                 if(strNowCollum==strMaxValue)
								 {
				   				        TCal ++;
										if(TCal ==1)
                                            MaxValue = data;
										else
											if(data > MaxValue)
                                                 MaxValue = data;
                                        TrueValue = MaxValue;
								 }
                                 else if(strNowCollum==strMinValue)
								 {
				   				        TCal ++;
										if(TCal ==1)
                                            MinValue = data;
										else
											if(data < MinValue)
                                                 MinValue = data;
                                        TrueValue = MinValue;
								 }
                                 else if(strNowCollum==strMidValue)
								 {
                                        TValue +=data;
				   				        TCal ++;
                                        MidValue = (unsigned short)(TValue/TCal);
                                        TrueValue = MidValue;
								 }
                                 else if(strNowCollum == strMaxValueTime)
								 {
				   				        TCal ++;
										if(TCal ==1){
                                            MaxValue = data;
                                            strMidValueT = CalTime; 
										}
										else if(data > MaxValue){
                                             MaxValue = data;
                                             strMidValueT = CalTime; 
										}
								 }
                                 else if(strNowCollum == strMinValueTime)
								 {
				   				        TCal ++;
										if(TCal ==1){
                                            MinValue = data;
                                            strMidValueT = CalTime;
										}
										else if(data < MinValue){
                                            MinValue = data;
                                            strMidValueT = CalTime; 
										}
								 }
							}
			         		else if(lapse > timelen) break;
		        	    	nRet = m_SQLDirect.Fetch();
						}
                        if((strNowCollum==strMaxValueTime)||(strNowCollum==strMinValueTime))
		                    rgMyRge.SetItem(_variant_t((long)iExcelRow),_variant_t((long)(iItem+2)),_variant_t(strMidValueT)); 
                        else
						{
		                    strMidValueT=Str2Data.Int2CString(TrueValue); 
		                    rgMyRge.SetItem(_variant_t((long)iExcelRow),_variant_t((long)(iItem+2)),_variant_t(strMidValueT)); 
						}
		                iExcelRow++;
					  }
					}
					else if(strbValueType == "0")
					{
		                iExcelRow++;
					}
                }
                iExcelRow=3;
              }
			  if((strNowCollum==strStartmd1)||(strNowCollum==strStartmd2))
			  {
				int nItemCount1=m_ctrlListReportTable.GetItemCount();
            	for(int iListItem=0; iListItem<nItemCount1; iListItem++)
				{
                    unsigned short  TCal =0;
                    CString strbValueType = _T("") ;
					strPointNo=m_ctrlListReportTable.GetItemText(iListItem,0);
         
		            strSQL.Format("SELECT * FROM uPointProperty WHERE unPointNo = %s ",strPointNo);
	        		if( m_SQLDirect.ExecuteSQL(strSQL)==SQL_SUCCESS)
					{
		        		int nRet=m_SQLDirect.Fetch();
		        		if(!nRet)
						{
		         			strbValueType=m_SQLDirect.GetCol(6);
						}
					}
                    if(strbValueType == "1")
					{
		                iExcelRow++;
					}
					else if(strbValueType == "0")
					{
                      CString strRunT = _T("");
                      unsigned short  TCal =0;
		              strSQL.Format("SELECT * FROM uCollectData WHERE unPointNo = %s ",strPointNo);
	        	   	  if( m_SQLDirect.ExecuteSQL(strSQL) == SQL_SUCCESS)
					  {
		        		int nRet=m_SQLDirect.Fetch();
		        		while(!nRet)
						{
	                     	int nYear,nMonth,nDay,nHour,nMinute,nSecond,alarmT1,alarmT;
	    			        CString strdata = m_SQLDirect.GetCol(2);
			                CString	CalTime = m_SQLDirect.GetCol(3);
  							GetDateR(nYear,nMonth,nDay,nHour,nMinute,nSecond,CalTime);

				            int lapse = (((((nYear - sYear)*12 + (nMonth - sMonth))*30 + (nDay - sDay))*24 + (nHour - m_ctrlStartH))*60 + nMinute - m_ctrlStartMin)*60 + nSecond;
			         		lapse -= m_ctrlStartSecond;
			        		if((lapse < timelen) && (lapse >=0))
							{
    							if(strNowCollum == strStartmd1){
									 if(strdata== "0"){
				   				        TCal ++;
										if(TCal ==1){
            				                alarmT = (((((nYear - sYear)*12 + (nMonth - sMonth))*30 + (nDay - sDay))*24 + (nHour - m_ctrlStartH))*60 + nMinute - m_ctrlStartMin)*60 + nSecond ;
                                            strRunT = CalTime;
										}
										else{
            				                alarmT1 = (((((nYear - sYear)*12 + (nMonth - sMonth))*30 + (nDay - sDay))*24 + (nHour - m_ctrlStartH))*60 + nMinute - m_ctrlStartMin)*60 + nSecond ;
											if(alarmT1 > alarmT) {
		                                      	alarmT = alarmT1;
                                                strRunT = CalTime;
											}
										}
									 }
								}
                                if(strNowCollum == strStartmd2){
									if(strdata == "1"){
				   				        TCal ++;
										if(TCal ==1){
            				                alarmT = (((((nYear - sYear)*12 + (nMonth - sMonth))*30 + (nDay - sDay))*24 + (nHour - m_ctrlStartH))*60 + nMinute - m_ctrlStartMin)*60 + nSecond ;
                                            strRunT = CalTime;
										}
										else{
            				                alarmT1 = (((((nYear - sYear)*12 + (nMonth - sMonth))*30 + (nDay - sDay))*24 + (nHour - m_ctrlStartH))*60 + nMinute - m_ctrlStartMin)*60 + nSecond ;
											if(alarmT1 > alarmT) {
		                                      	alarmT = alarmT1;
                                                strRunT = CalTime;
											}
										}
									}
								}
							}
							else if(lapse > timelen)   break;
		        	    	nRet = m_SQLDirect.Fetch();
						}
		                rgMyRge.SetItem(_variant_t((long)iExcelRow),_variant_t((long)(iItem+2)),_variant_t(strRunT)); 
		                iExcelRow++;
					  }
					}
				}
                iExcelRow=3;
			  }
			  if((strNowCollum==strAlarmCal)||(strNowCollum==strAlarmTimer))
			  {
				int nItemCount1=m_ctrlListReportTable.GetItemCount();
            	for(int iListItem=0; iListItem<nItemCount1; iListItem++)
				{
					CString strAlarmTS = _T("");
                    unsigned short  TCal =0;
                    CString strAlarmTE = _T("") ;
                    CString strAlarm =  _T("");

					strPointNo=m_ctrlListReportTable.GetItemText(iListItem,0);
		            strSQL.Format("SELECT * FROM uWarnCauseRecord WHERE unPointNo = %s ",strPointNo);
	        		if( m_SQLDirect.ExecuteSQL(strSQL)==SQL_SUCCESS)
					{
		        		int nRet=m_SQLDirect.Fetch();
                        if(strNowCollum==strAlarmTimer)
						{
		        	    	while(!nRet)
							{
	                        	int nYear,nMonth,nDay,nHour,nMinute,nSecond,alarmT1,alarmT;
			                    CString	strAlarmTS = m_SQLDirect.GetCol(4);
								CString strAlarmTE=m_SQLDirect.GetCol(5); 
  				    			GetDateR(nYear,nMonth,nDay,nHour,nMinute,nSecond,strAlarmTS);

				                int lapse = (((((nYear - sYear)*12 + (nMonth - sMonth))*30 + (nDay - sDay))*24 + (nHour - m_ctrlStartH))*60 + nMinute - m_ctrlStartMin)*60 + nSecond;
			            		lapse -= m_ctrlStartSecond;
			            		if((lapse < timelen) && (lapse >=0))
								{
				   				        TCal ++;
										if(TCal ==1){
            				                alarmT = (((((nYear - sYear)*12 + (nMonth - sMonth))*30 + (nDay - sDay))*24 + (nHour - m_ctrlStartH))*60 + nMinute - m_ctrlStartMin)*60 + nSecond ;
		                                	strAlarm.Format("%s至%s",strAlarmTS,strAlarmTE);
										}
										else{
            				                alarmT1 = (((((nYear - sYear)*12 + (nMonth - sMonth))*30 + (nDay - sDay))*24 + (nHour - m_ctrlStartH))*60 + nMinute - m_ctrlStartMin)*60 + nSecond ;
			                        		if(alarmT1 > alarmT) 
											{
		                                      	alarmT = alarmT1;
												strAlarm.Format("%s至%s",strAlarmTS,strAlarmTE);
											}
										}
								}
					    		else if(lapse > timelen)   break;

		                	    nRet = m_SQLDirect.Fetch();
							}
						}
                        if(strNowCollum==strAlarmCal)
						{
		        	    	while(!nRet)
							{
	                        	int nYear,nMonth,nDay,nHour,nMinute,nSecond;
			                    CString	CalTime = m_SQLDirect.GetCol(4);
  				    			GetDateR(nYear,nMonth,nDay,nHour,nMinute,nSecond,CalTime);

				                int lapse = (((((nYear - sYear)*12 + (nMonth - sMonth))*30 + (nDay - sDay))*24 + (nHour - m_ctrlStartH))*60 + nMinute - m_ctrlStartMin)*60 + nSecond;
			            		lapse -= m_ctrlStartSecond;
			            		if((lapse < timelen) && (lapse >=0))
								{
				   				       TCal ++;
                                       strAlarm = Str2Data.Int2CString(TCal);
								}
					    		else if(lapse > timelen)   break;
		                	    nRet = m_SQLDirect.Fetch();
							}
						}
		         		rgMyRge.SetItem(_variant_t((long)iExcelRow),_variant_t((long)(iItem+2)),_variant_t(strAlarm)); 
		         	    iExcelRow++;
					}
				}
                iExcelRow=3;
			  }
          }
		}
       	catch(CDBException *e)
		{
             	e->ReportError();
            	return;
		}
	  //打印预览 
	wbMyBook.SetSaved(true); 
	ExcelApp.SetVisible(true); 
//	wbMyBook.PrintPreview(_variant_t(false)); 
	//释放对象 
	rgMyRge.ReleaseDispatch(); 
	wsMysheet.ReleaseDispatch(); 
	wssMysheets.ReleaseDispatch(); 
	wbMyBook.ReleaseDispatch(); 
	wbsMyBooks.ReleaseDispatch(); 
	ExcelApp.ReleaseDispatch(); 
}

BOOL CReport::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	SetButtonStyle();

	ConnectDB();//连接数据库
	if (CoInitialize(NULL)!=0)   //EXCEL
	{ 
		AfxMessageBox("初始化COM支持库失败,无法输出EXCEL报表，但可进行其它操作!");
		m_bExcelInit=false;
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
    SetListCollum();
    SetListNowCollum();

	GetDataFromDB();	
    GetCollumHead();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CReport::ConnectDB()
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

void CReport::GetDataFromDB()
{
	CString strSQL;
	CString2DataType Str2Data;
	BOOL *bUsedAddrNo;
	bUsedAddrNo=new BOOL[MAX_ADDR_NUMBER];
	for(UINT i=0;i<MAX_ADDR_NUMBER;i++)
		*(bUsedAddrNo+i)=FALSE;
 	try
	{
		strSQL.Format("SELECT * FROM uPointProperty WHERE unTrunkNo = %d",m_unTrunkNo);
		if( m_SQLDirect.ExecuteSQL(strSQL)==SQL_SUCCESS)
		{
			int nRet=m_SQLDirect.Fetch();
			int iItem=0;
			while(!nRet)
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
				CString strunConvIDCH = GetConvName(Str2Data.String2Int(strunConnectorID));
				m_ctrlComboSelectTrunk.SetCurSel(Str2Data.String2Int(strunTrunkNo)-1);
				UpdateData(FALSE);
				if(strbScan=="1")
					strbScan="扫描";
				else
					strbScan="不扫描";

				    m_ctrlList.InsertItem(iItem, strunAddress, 0);
					m_ctrlList.SetItem(iItem, 1, LVIF_TEXT, strunPointNo, 0, NULL, NULL, NULL);
					m_ctrlList.SetItem(iItem, 2, LVIF_TEXT, strunConvIDCH, 0, NULL, NULL, NULL);
					m_ctrlList.SetItem(iItem, 3, LVIF_TEXT, strunConnectorID, 0, NULL, NULL, NULL);
					m_ctrlList.SetItem(iItem, 4, LVIF_TEXT, strbScan, 0, NULL, NULL, NULL);
					m_ctrlList.SetItem(iItem, 5, LVIF_TEXT, strunScanFreq, 0, NULL, NULL, NULL);
				//	m_ctrlList.SetItem(iItem, 5, LVIF_TEXT, strLogoff, 0, NULL, NULL, NULL);

				*(bUsedAddrNo+Str2Data.String2Int(strunAddress))=TRUE;
				nRet=m_SQLDirect.Fetch();
				iItem++;
			}
		}
	}
	catch(CDBException *e){
	e->ReportError();
	delete bUsedAddrNo;
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
	delete bUsedAddrNo;
}

void CReport::SetButtonStyle()
{
	m_ctrlBtnReport.SetThemeHelper(&m_ThemeHelper);
	m_ctrlBtnReport.SetIcon(IDI_ICON_EXCEL);
	m_ctrlBtnReport.SetTooltipText(_T("注意：右表第一行是报表表头、标题；右表最后一行是表尾、签名"));

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

	m_ctrlBtnADDCOLLUM.SetThemeHelper(&m_ThemeHelper);
	m_ctrlBtnADDCOLLUM.SetIcon(IDI_ICON_ADDSINGLE);
	m_ctrlBtnADDCOLLUM.SetTooltipText(_T("先在左表中选择行，再点击加入，双击点所在行也可加入"));
	m_ctrlBtnADDCOLLUM.SetColor(0,RGB(000,153,000),TRUE);
	m_ctrlBtnADDCOLLUM.SetColor(1,RGB(255,255,255),TRUE);

	m_ctrlBtnDELCOLLUM.SetThemeHelper(&m_ThemeHelper);
	m_ctrlBtnDELCOLLUM.SetIcon(IDI_ICON_ADDDESELECT1);
	m_ctrlBtnDELCOLLUM.SetTooltipText(_T("先在右表中选择行，再点击删除，双击点所在行也可删除"));
	m_ctrlBtnDELCOLLUM.SetColor(0,RGB(255,051,051),TRUE);
	m_ctrlBtnDELCOLLUM.SetColor(1,RGB(255,255,255),TRUE);

	m_ctrlBtnADDEDIT.SetThemeHelper(&m_ThemeHelper);
	m_ctrlBtnADDEDIT.SetIcon(IDI_ICON_ADDEDIT);
	m_ctrlBtnADDEDIT.SetTooltipText(_T("添加用户自定义列"));
	m_ctrlBtnADDEDIT.SetColor(0,RGB(000,153,000),TRUE);
	m_ctrlBtnADDEDIT.SetColor(1,RGB(255,255,255),TRUE);
}


CString CReport::GetAppPath()
{
	CString sModFileName;
	CString str1;
	GetModuleFileName(NULL, sModFileName.GetBuffer(MAX_PATH), MAX_PATH);
	sModFileName.ReleaseBuffer();
	str1=sModFileName;
	str1.MakeReverse();
	return(sModFileName.Left(sModFileName.GetLength() - str1.Find('\\')));
}

void CReport::OnDestroy() 
{
	CDialog::OnDestroy();

	m_SQLDirect.Close();
	if(m_bExcelInit)
		CoUninitialize();  //EXCEL
	// TODO: Add your message handler code here
}

CString CReport::GetConvName(UINT unConvID)
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

void CReport::SetListCtrlTable()
{
	m_ctrlList.InsertColumn(0, _T("地址"), LVCFMT_CENTER,20);
	m_ctrlList.InsertColumn(1, _T("点号"), LVCFMT_CENTER,20);
	m_ctrlList.InsertColumn(2, _T("转接器类型"), LVCFMT_CENTER, 72);

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

void CReport::SetListReportTable()
{
	m_ctrlListReportTable.InsertColumn(0, _T("点号"), LVCFMT_CENTER, 20);

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

BOOL CReport::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult) 
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

void CReport::OnButtonDeselectall() 
{
	// TODO: Add your control notification handler code here
	m_ctrlListReportTable.DeleteAllItems();
}

void CReport::OnButtonDeselect1() 
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

void CReport::OnButtonAddall() 
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
		}
	}	
}

void CReport::OnButtonAdd1() 
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
				}
			}

			if(!bExist)
			{
				m_ctrlListReportTable.InsertItem(nItemCount1, strPointNo, 0);
			}
		}
	}	
}

void CReport::OnDblclkListAddr(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	OnButtonAdd1() ;
	*pResult = 0;
}

void CReport::OnDblclkListReporttable(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	OnButtonDeselect1();
	*pResult = 0;
}

void CReport::OnSelchangeComboSelecttrunk() 
{
	// TODO: Add your control notification handler code here
	m_ctrlList.DeleteAllItems();
	UpdateData(TRUE);
	m_unTrunkNo=m_ctrlComboSelectTrunk.GetCurSel()+1;
	GetDataFromDB();
	
}


void CReport::OnDblclkListCollum(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
    OnButAddCollum();	
	*pResult = 0;
}

void CReport::OnDblclkListNowcollum(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
    OnButDelCollun();	
	*pResult = 0;
}

void CReport::OnButAddedit() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

			BOOL bExist=FALSE;
			CString strAddedit=m_ctrlDefine;   

			int nItemCount1=m_ctrlNowCollum.GetItemCount();
			for(int j=0; j<nItemCount1; j++)
			{
				if(strAddedit==m_ctrlNowCollum.GetItemText(j,0))
				{
					bExist=TRUE;
					break;
				}
			}
			if(!bExist)
			{
				m_ctrlNowCollum.InsertItem(nItemCount1, strAddedit, 0);
			}
	UpdateData(FALSE);
}

void CReport::OnButAddCollum() 
{
	// TODO: Add your control notification handler code here
	int nItemCount=m_ctrlCollum.GetItemCount();
    for(int nItem=0;nItem<nItemCount;nItem++)
	{
		if(m_ctrlCollum.GetItemState(nItem,LVIS_SELECTED) & LVIS_SELECTED)
		{
			CString strAddCollum=m_ctrlCollum.GetItemText(nItem,0);   //1
			int nItemCount1=m_ctrlNowCollum.GetItemCount();
			BOOL bExist=FALSE;
			for(int j=0; j<nItemCount1; j++)
			{
				if(strAddCollum==m_ctrlNowCollum.GetItemText(j,0))
				{
					bExist=TRUE;
					break;
				}
			}
			if(!bExist)
			{
				m_ctrlNowCollum.InsertItem(nItemCount1, strAddCollum, 0);
			}
		}
	}		
}

void CReport::OnButDelCollun() 
{
	// TODO: Add your control notification handler code here
	int nItemCount=m_ctrlNowCollum.GetItemCount();
    for(int nItem=0;nItem<nItemCount;nItem++)
	{
		if(m_ctrlNowCollum.GetItemState(nItem,LVIS_SELECTED) & LVIS_SELECTED)
		{
			m_ctrlNowCollum.DeleteItem(nItem);
		}
	}
	
}

void CReport::SetListCollum()
{
	m_ctrlCollum.InsertColumn(0, _T("  可选报表列头"), LVCFMT_CENTER,20);

	m_ctrlCollum.SetExtendedStyle (LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT|LVS_EX_FLATSB);

	HWND hWndHeader = m_ctrlCollum.GetDlgItem(IDC_LIST_COLLUM)->GetSafeHwnd();
	m_flatHeader.SubclassWindow (hWndHeader);

	m_ctrlCollum.AutoSizeColumn ();

	m_cpBack.SetColor(RGB(0x33,0x66,0xff));
	m_cpBack.SetDefaultColor(m_clrRowBack);

	m_cpText.SetColor(RGB(0xff,0xff,0xff));
	m_cpText.SetDefaultColor(m_clrRowText);

	m_ctrlCollum.SetRowColors(m_cpText.GetColor(), m_cpBack.GetColor());

	m_bAscending=TRUE;
	m_nSortedCol=0;

	m_flatHeader.SetSortImage (m_nSortedCol, m_bAscending);

			// TODO: Add your sorting code here.
	CXTSortClass csc (&m_ctrlCollum, m_nSortedCol);
	csc.Sort (m_bAscending ? true : false, DT_INT);
}

void CReport::SetListNowCollum()
{
	m_ctrlNowCollum.InsertColumn(0, _T("   报表头/列/尾 "), LVCFMT_CENTER, 20);

	m_ctrlNowCollum.SetExtendedStyle (LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT|LVS_EX_FLATSB);

	HWND hWndHeader = m_ctrlNowCollum.GetDlgItem(IDC_LIST_NOWCOLLUM)->GetSafeHwnd();
	m_flatHeader.SubclassWindow (hWndHeader);

	m_ctrlNowCollum.AutoSizeColumn ();

	m_cpBack.SetColor(RGB(255,255,204));
	m_cpBack.SetDefaultColor(m_clrRowBack);

	m_cpText.SetColor(RGB(0x00,0x00,0x00));
	m_cpText.SetDefaultColor(m_clrRowText);

	m_ctrlNowCollum.SetRowColors(m_cpText.GetColor(), m_cpBack.GetColor());

	m_bAscending=TRUE;
	m_nSortedCol=0;

	m_flatHeader.SetSortImage (m_nSortedCol, m_bAscending);

			// TODO: Add your sorting code here.
	CXTSortClass csc (&m_ctrlNowCollum, m_nSortedCol);
	csc.Sort (m_bAscending ? true : false, DT_INT);
}

void CReport::GetCollumHead()
{
	m_ctrlCollum.DeleteAllItems();

				CString strMaxValue =_T("最大值");
				CString strMaxValueTime =_T("最大值时间");
				CString strMinValue =_T("最小值");
				CString strMinValueTime =_T("最小值时间");
				CString strMidValue = _T("平均值");
				CString strAlarmCal =_T("报警次数");
				CString strAlarmTimer =_T("报警时间段");
				CString strRunTimer =_T("设备运行累计时间");
				CString strStartmd1 =_T("开机时间（MD1）");
				CString strStartmd2 =_T("开机时间（MD2）");
				CString strSensorstation =_T("探头安装位置");
				CString strServiceName =_T("设备名称");

				m_ctrlCollum.InsertItem(0, strMaxValueTime, 0);
				m_ctrlCollum.InsertItem(0, strMaxValue, 0);
				m_ctrlCollum.InsertItem(0, strMinValueTime, 0);
				m_ctrlCollum.InsertItem(0, strMinValue, 0);
				m_ctrlCollum.InsertItem(0, strMidValue, 0);
				m_ctrlCollum.InsertItem(0, strAlarmTimer, 0);
				m_ctrlCollum.InsertItem(0, strAlarmCal, 0);
				m_ctrlCollum.InsertItem(0, strRunTimer, 0);
				m_ctrlCollum.InsertItem(0, strStartmd1, 0);
				m_ctrlCollum.InsertItem(0, strStartmd2, 0);
				m_ctrlCollum.InsertItem(0, strSensorstation, 0);
				m_ctrlCollum.InsertItem(0, strServiceName, 0);

	// initialize the back color picker default colors.
	m_cpBack.SetColor(RGB(0x33,0x66,0xff));
	m_cpBack.SetDefaultColor(m_clrRowBack);

	// initialize the text color picker default colors.
	m_cpText.SetColor(RGB(0xff,0xff,0xff));
	m_cpText.SetDefaultColor(m_clrRowText);

	// set the text and back colors for the list control.
	m_ctrlCollum.SetRowColors(m_cpText.GetColor(), m_cpBack.GetColor());

}

void CReport::OnCloseupDatetimepickerstart(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_ctrlStartTime.GetTime(m_startDateTime);
	UpdateData(FALSE);
	*pResult = 0;
}

void CReport::OnCloseupDatetimepickerend(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	m_ctrlEndTime.GetTime(m_endDateTime);
	*pResult = 0;
}

void CReport::GetDateR(int &year, int &month, int &day, CString time)
{
	CString2DataType convert;
	int index;
	CString value;

	index = time.Find('-');
	value = time.Mid(0,index);
	year = convert.String2Int(value);

	time = time.Mid(index+1);
	index = time.Find('-');
	value = time.Mid(0,index);
	month = convert.String2Int(value);

	time = time.Mid(index+1);
	day = convert.String2Int(time);
}

void CReport::GetDateR(int &year, int &month, int &day, int &hour, int &minute, int &second, CString time)
{
	GetDateR(year,month,day,time);
	CString2DataType convert;
	CString value;
	int index = time.Find(' ');
	time = time.Mid(index+1);

	index = time.Find(':');
	value = time.Mid(0,index);
	hour = convert.String2Int(value);

	time = time.Mid(index+1);
	index = time.Find(':');
	value = time.Mid(0,index);
	minute = convert.String2Int(value);
	
	time = time.Mid(index+1);
	second = convert.String2Int(time);
}

BOOL CReport::DestroyWindow() 
{
	// TODO: Add your specialized code here and/or call the base class
	UpdateData(TRUE);  //0115
	m_ctrlEndTime.GetTime(m_endDateTime);	
	m_ctrlStartTime.GetTime(m_startDateTime);
	UpdateData(FALSE);
	
	return CDialog::DestroyWindow();
}

void CReport::Serialize(CArchive& ar) 
{
	if (ar.IsStoring())
	{	// storing code
		ar << m_strStartTime;
		ar << m_strEndTime;
		ar << m_ctrlStartH;
		ar << m_ctrlEndH;
		ar << m_ctrlEndMin;    
		ar << m_ctrlStartMin;
	}
	else
	{	// loading code
		ar >> m_strStartTime;
		ar >> m_strEndTime;
		ar >> m_ctrlStartH;
		ar >> m_ctrlEndH;
		ar >> m_ctrlEndMin;    //0115
		ar >> m_ctrlStartMin;
	}
}

void CReport::OnChangeEditStarth() 
{
	UpdateData(TRUE);
//	m_strEditAddrHEX.Format("%02X",m_unEditAddrDEC);
	UpdateData(FALSE);
	// TODO: Add your control notification handler code here
}

void CReport::OnChangeEditEndh() 
{
	UpdateData(TRUE);
	UpdateData(FALSE);
	// TODO: Add your control notification handler code here
}

void CReport::OnChangeEditStartmin() 
{
	UpdateData(TRUE);
	UpdateData(FALSE);
	// TODO: Add your control notification handler code here
	
}

void CReport::OnChangeEditEndmin() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	UpdateData(TRUE);
	UpdateData(FALSE);
	// TODO: Add your control notification handler code here
	
}
