// ResourceViewPane.cpp : implementation file
//
// This file is a part of the XTREME TOOLKIT PRO MFC class library.
// (c)1998-2009 Codejock Software, All Rights Reserved.
//
// THIS SOURCE FILE IS THE PROPERTY OF CODEJOCK SOFTWARE AND IS NOT TO BE
// RE-DISTRIBUTED BY ANY MEANS WHATSOEVER WITHOUT THE EXPRESSED WRITTEN
// CONSENT OF CODEJOCK SOFTWARE.
//
// THIS SOURCE CODE CAN ONLY BE USED UNDER THE TERMS AND CONDITIONS OUTLINED
// IN THE XTREME TOOLKIT PRO LICENSE AGREEMENT. CODEJOCK SOFTWARE GRANTS TO
// YOU (ONE SOFTWARE DEVELOPER) THE LIMITED RIGHT TO USE THIS SOFTWARE ON A
// SINGLE COMPUTER.
//
// CONTACT INFORMATION:
// support@codejock.com
// http://www.codejock.com
//
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "GUI_VisualStudio.h"
#include "ResourceViewPane.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern SerialF               m_AFans[MAX_FDS][MAX_CHAN];    //双风门主扇备扇报警
extern SerialF       m_ABFlist[MAX_FDS][MAX_CHAN]; //AD have ABF SFSd/aa cfds/ab cchan/af ffds/dab fchan/df
extern ADMainDis             m_ADMainDis[MAX_FDS][MAX_CHAN];          //调用显示
extern ADCbreakE             m_CFeed[MAX_FDS][MAX_CHAN][65];
extern ADCbreakE             m_ADCbreakE[MAX_FDS][MAX_CHAN][65];
extern SlaveStation             m_SlaveStation[MAX_FDS][MAX_CHAN];
/////////////////////////////////////////////////////////////////////////////
// CResourceViewPane

CResourceViewPane::CResourceViewPane()
{
	m_numabf=0;
	B_change = FALSE;
}

CResourceViewPane::~CResourceViewPane()
{
}


BEGIN_MESSAGE_MAP(CResourceViewPane, CWnd)
	//{{AFX_MSG_MAP(CResourceViewPane)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_NCHITTEST()
	//}}AFX_MSG_MAP
	ON_WM_SETFOCUS()
END_MESSAGE_MAP()

static int arColWidths[] = {
	160,
	60,
	130,
	130,
	130,
//	60,
	200,
	240
};
static CString arColLabels[] = {
	_T("安装地点/名称"),
	_T("监测值"),
	_T("报警时刻"),
	_T("断电时刻"),
	_T("复电时刻"),
//	_T("馈电状态"),
	_T("馈电状态/时刻"),
	_T("安全措施/时刻")
};

static int bColWidths[] = {
	160,
	60,
	130,
	240,
	200,
//	60,
//	160,
	240
};
static CString bColLabels[] = {
	_T("安装地点/名称"),
	_T("监测值"),
//	_T("报警时刻"),
	_T("断电时刻"),
	_T("断电区域"),
//	_T("复电时刻"),
//	_T("馈电状态"),
	_T("馈电状态/时刻"),
	_T("安全措施/时刻")
};

static int fColWidths[] = {
	160,
	60,
	130,
	130,
	170,
//	60,
	200,
	240
};
static CString fColLabels[] = {
	_T("安装地点/名称"),
	_T("监测值"),
	_T("报警时刻"),
	_T("断电时刻"),
//	_T("复电时刻"),
	_T("断电区域"),
//	_T("馈电状态"),
	_T("馈电状态/时刻"),
	_T("安全措施/时刻")
};

static int dabColWidths[] = {
	160,
	80,
	130,
	130,
	160,
//	60,
	200,
	300
};
static CString dabColLabels[] = {
	_T("安装地点/名称"),
	_T("状态"),
	_T("报警时刻"),
	_T("断电时刻"),
//	_T("复电时刻"),
	_T("断电区域"),
//	_T("馈电状态"),
	_T("馈电状态/时刻"),
	_T("安全措施/时刻")
};

static int dfColWidths[] = {
	160,
	80,
	130,
	130,
	160,
//	60,
	200,
	300
};
static CString dfColLabels[] = {
	_T("安装地点/名称"),
	_T("状态"),
	_T("报警时刻"),
	_T("断电时刻"),
//	_T("复电时刻"),
	_T("断电区域"),
//	_T("馈电状态"),
	_T("馈电状态/时刻"),
	_T("安全措施/时刻")
};

//开关量状态变动显示

/*
设备故障记录
static CString arColLabels[] = {
	_T("安装地点/名称"),
	_T("故障状态"),
	_T("故障时间"),
	_T("安全措施及处理时刻")
};


模拟量调用显示
static CString arColLabels[] = {
	_T("安装地点/名称"),
	_T("监测值"),
	_T("单位"),
	_T("报警门限"),
	_T("断电门限"),
	_T("复电门限"),
	_T("最后一次统计的最大值")
	_T("平均值"),
	_T("最后一次报警时刻"),
	_T("最后一次解除报警时刻"),
	_T("最后一次断电时刻"),
	_T("最后一次复电时刻")
};
开关量调用显示
static CString arColLabels[] = {
	_T("设备状态/时刻"),
	_T("断电/报警状态"),
	_T("断电/报警及时刻"),
	_T("断电区域"),
	_T("安全措施及处理时刻")
};
*/

//设备状态   
/////////////////////////////////////////////////////////////////////////////
// CResourceViewPane message handlers

int CResourceViewPane::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

//	SetWindowLong(m_hWnd, GWL_STYLE, GetWindowLong(m_hWnd, GWL_STYLE) & ~WS_THICKFRAME);

	// Define the default style for the output list controls.
	DWORD dwStyle = LVS_REPORT | LVS_NOSORTHEADER | LVS_SHOWSELALWAYS |
		WS_CHILD | WS_VSCROLL | WS_TABSTOP|WS_VISIBLE;

	// Create the list control.
	if (!m_listCtrl.Create( dwStyle, CRect(3,0,1022,165), this, 0xff ))
	{
		TRACE0( "Failed to create list control.\n" );
		return FALSE;
	}

	// initialize the list control.
	InitListControl();

/*	if (m_wndResourceView.GetSafeHwnd() == 0)
	{
		if (!m_wndResourceView.Create( WS_VISIBLE | TVS_HASLINES | TVS_LINESATROOT | TVS_HASBUTTONS | TVS_SHOWSELALWAYS,
			CRect(0,0,0,0), this, 0xFF ))
		{
			TRACE0( "Unable to create tree control.\n" );
			return 0;
		}
		m_wndResourceView.ModifyStyleEx(0, WS_EX_STATICEDGE);

		// load the tree images bitmap and add it to the image list.
		if (!CreateImageList(m_ilResourceView, IDB_RESTREE))
			return 0;

		// Set the image list for the tree control.
		m_wndResourceView.SetImageList( &m_ilResourceView, TVSIL_NORMAL );

		// add the parent item
		HTREEITEM htItem = m_wndResourceView.InsertItem(_T("XtremeDemo resources"), 0, 1);
		m_wndResourceView.SetItemState(htItem, TVIS_BOLD, TVIS_BOLD);

		HTREEITEM hti = m_wndResourceView.InsertItem(_T("Accelerator"), 0, 1, htItem);
		m_wndResourceView.InsertItem(_T("IDR_MAINFRAME"), 2, 2, hti);
		m_wndResourceView.Expand(hti, TVE_EXPAND);

		hti = m_wndResourceView.InsertItem(_T("Dialog"), 0, 1, htItem);
		m_wndResourceView.InsertItem(_T("IDD_ABOUTBOX"), 3, 3, hti);
		m_wndResourceView.Expand(hti, TVE_EXPAND);

		hti = m_wndResourceView.InsertItem(_T("Icon"), 0, 1, htItem);
		m_wndResourceView.InsertItem(_T("IDR_MAINFRAME"), 4, 4, hti);
		m_wndResourceView.InsertItem(_T("IDR_XTREMETYPE"), 4, 4, hti);
		m_wndResourceView.Expand(hti, TVE_EXPAND);

		hti = m_wndResourceView.InsertItem(_T("Menu"), 0, 1, htItem);
		m_wndResourceView.InsertItem(_T("IDR_MAINFRAME"), 5, 5, hti);
		m_wndResourceView.InsertItem(_T("IDR_XTREMETYPE"), 5, 5, hti);

		hti = m_wndResourceView.InsertItem(_T("String Table"), 0, 1, htItem);
		m_wndResourceView.InsertItem(_T("String Table"), 6, 6, hti);

		hti = m_wndResourceView.InsertItem(_T("Toolbar"), 0, 1, htItem);
		m_wndResourceView.InsertItem(_T("IDR_MAINFRAME"), 7, 7, hti);

		hti = m_wndResourceView.InsertItem(_T("Version"), 0, 1, htItem);
		m_wndResourceView.InsertItem(_T("VS_VERSION_INFO"), 8, 8, hti);

		m_wndResourceView.Expand (htItem, TVE_EXPAND);
	}*/

	return 0;
}

LRESULT CResourceViewPane::OnNcHitTest(CPoint point)
{
	if (CWnd::OnNcHitTest(point) == HTRIGHT || CWnd::OnNcHitTest(point) == HTLEFT 
		|| CWnd::OnNcHitTest(point) == HTTOP || CWnd::OnNcHitTest(point) == HTBOTTOM)
	return HTCLIENT;
	return CWnd::OnNcHitTest(point);
}


BOOL CResourceViewPane::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	if( !CWnd::PreCreateWindow(cs) )
		return FALSE;

	cs.style |= WS_CLIPCHILDREN;
	
	cs.style = WS_CHILD | WS_VISIBLE //| WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU
		| FWS_ADDTOTITLE | WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX 
    ;

//	cs.style   &=~   (LONG)   FWS_PREFIXTITLE;
//	cs.style &= ~WS_MAXIMIZEBOX;
//	cs.style &= ~WS_THICKFRAME;
//   cs.style   &=~WS_VSCROLL;     FWS_ADDTOTITLE

/*
cs.style = WS_OVERLAPPED | WS_SYSMENU | WS_MINIMIZEBOX;// | WS_THICKFRAME;
cs.style &= ~WS_BORDER;
cs.dwExStyle &= ~WS_EX_CLIENTEDGE;
int iWinBorderX = GetSystemMetrics(SM_CXBORDER);
int iWinBorderY = GetSystemMetrics(SM_CYBORDER);
int iCaptionY = GetSystemMetrics(SM_CYCAPTION);
int iMenuY = GetSystemMetrics(SM_CYMENU);
int iStausY = GetSystemMetrics(SM_CYMENU);
cs.cx = 510 + iWinBorderX ;
cs.cy = 530 + iWinBorderY + iCaptionY + iStausY + iMenuY;*/

	return TRUE;
}



void CResourceViewPane::OnSize(UINT nType, int cx, int cy)
{
	CWnd::OnSize(nType, cx, cy);

//	if (m_wndResourceView.GetSafeHwnd())
	{
//		m_wndResourceView.MoveWindow(0, 0, 200, 200);
	}
//		m_wndSolutionView.MoveWindow(0, nTop, cx, cy - nTop);
//	m_listCtrl.MoveWindow(0, 0, cx, 170);
}

void CResourceViewPane::OnSetFocus(CWnd* /*pOldWnd*/)
{
//	m_wndResourceView.SetFocus();
//	InitLC();
//	m_listCtrl.SetFocus();
}

void CResourceViewPane::InitListControl()
{
	// Insert the columns.
	if(m_numabf == 1)
       	m_listCtrl.BuildColumns(_countof(arColWidths), arColWidths, arColLabels);
	else if(m_numabf == 2)
       	m_listCtrl.BuildColumns(_countof(bColWidths), bColWidths, bColLabels);
	else if(m_numabf == 3)
       	m_listCtrl.BuildColumns(_countof(fColWidths), fColWidths, fColLabels);
	else if(m_numabf == 4)
       	m_listCtrl.BuildColumns(_countof(dabColWidths), dabColWidths, dabColLabels);
	else if(m_numabf == 5)
       	m_listCtrl.BuildColumns(_countof(dfColWidths), dfColWidths, dfColLabels);
//	else if(m_numabf == 6)
//       	m_listCtrl.BuildColumns(_countof(dchColWidths), dchColWidths, dchColLabels);
	// Subclass the flat header control.
	m_listCtrl.SubclassHeader();

	// lock the first two colums from sizing operations.
//	CXTFlatHeaderCtrl* pHeaderCtrl = m_listCtrl.GetFlatHeaderCtrl( );
//	if ( pHeaderCtrl != NULL )
	{
//		pHeaderCtrl->FreezeColumn(0);
//		pHeaderCtrl->FreezeColumn(1);
//		pHeaderCtrl->FreezeColumn(2);
		// enable autosizing for columns.
//		pHeaderCtrl->EnableAutoSize();
//		pHeaderCtrl->SetBitmap(2, IDB_HEADER, HDF_STRING);
	}
	ListView_SetExtendedListViewStyle(
		m_listCtrl.m_hWnd, LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT );

	m_listCtrl.EnableUserSortColor(true);
	m_listCtrl.EnableUserListColor(true);
	m_listCtrl.EnableUserRowColor(true);

    for(int i=0;i<500;i++)
	{
    	m_listCtrl.InsertItem(i, NULL, 0);
    	m_listCtrl.SetItemText(i, 0, "");
        m_listCtrl.SetRowColor(i, RGB(255,0,0), RGB(255,255,255));
	}
	m_cpstr.clear();
}

void CResourceViewPane::InitAA(unsigned char  afds, unsigned char  achan)
{
    //Highlight the first item
//    LV_ITEM lvi;
//		lvi.mask = LVIF_TEXT;
//		lvi.iItem = m_listnum;
//		lvi.iSubItem = 0;
//	  lvi.stateMask = LVIS_SELECTED | LVIS_FOCUSED;
//	  lvi.state = LVIS_SELECTED | LVIS_FOCUSED;
//		lvi.pszText = "";
//		lvi.pszText = (LPSTR)(LPCTSTR)m_SlaveStation[afds][achan].WatchName;
//		lvi.iImage = 0;
//		lvi.iIndent = 0;
//		lvi.cchTextMax = 50;

//	  for(int i =0; i<theApp.idis+1; i++)
	  {
//		  if(i == m_listnum)
//        	    m_listCtrl.SetItemState(m_listnum,LVIS_SELECTED,LVIS_SELECTED);
//             m_listCtrl.SetItemState(lvi.iItem, &lvi);
//		  else
		  {
//    	    m_listCtrl.SetItemState(i,NULL,NULL);
		  }
	  }

//	PostMessage(WM_VSCROLL,SB_LINEDOWN,0);
}

void CResourceViewPane::InitFBA(unsigned char  abfnum)
{
    int nItemCount= 0;    //列表位置id
	if(abfnum == 3)
	{//全部正常的点，清除 af
    	for(vector<CString>::iterator iter=m_cpstr.begin(); iter!=m_cpstr.end(); )
		{
			nItemCount= 0;
            	CString  strf,strc,dddd,d4;
	    		dddd = *iter;
           		strf = dddd.Mid(0,2);
        		strc = dddd.Mid(3);
    	    	int nfds = theApp.m_Str2Data.String2Int(strf);
	        	int nchan = theApp.m_Str2Data.String2Int(strc);
				int n_fans = m_AFans[nfds][nchan].fchan;
			if(n_fans == 1)
				nItemCount = 7;
    		for(int j=0; j<65; j++)
			{
		    	if(m_ADCbreakE[nfds][nchan][j].bFSd ==0)
		       		break;
    	    	int cfds = m_ADCbreakE[nfds][nchan][j].bFSd;
	        	int cchan = m_ADCbreakE[nfds][nchan][j].bchanel;
          		for(int k=0; k<65; k++)
				{
	        		//断电关联馈电
	    	     	if(m_CFeed[cfds][cchan][k].bFSd ==0)
		         		break;
    	            int ffds = m_CFeed[cfds][cchan][k].bFSd;
	             	int fchan = m_CFeed[cfds][cchan][k].bchanel;
					if(m_ABFlist[ffds][fchan].cchan == 1)
					{
						nItemCount = 7;
	    	       		break;
					}
				}
				if(nItemCount == 7)
	    	       		break;
			}//int j=0; j<65; j++)
			if(nItemCount == 0)
			{
	        		iter = m_cpstr.erase(iter);
					m_ABFlist[nfds][nchan].cchan =0;
					B_change = TRUE;
			}
	    	else
			    	iter++;

		}//i=m_cpstr.size()-1; i>=0; i--)
	}//if(abfnum == 3)
    nItemCount= 0;
	if(abfnum == 5)
	{//全部正常的点，清除 af
    	for(vector<CString>::iterator iter=m_cpstr.begin(); iter!=m_cpstr.end(); )
		{
			nItemCount= 0;
            	CString  strf,strc,dddd,d4;
	    		dddd = *iter;
           		strf = dddd.Mid(0,2);
        		strc = dddd.Mid(3);
    	    	int nfds = theApp.m_Str2Data.String2Int(strf);
	        	int nchan = theApp.m_Str2Data.String2Int(strc);
    		for(int j=0; j<65; j++)
			{
		    	if(m_ADCbreakE[nfds][nchan][j].bFSd ==0)
		       		break;
    	    	int cfds = m_ADCbreakE[nfds][nchan][j].bFSd;
	        	int cchan = m_ADCbreakE[nfds][nchan][j].bchanel;
          		for(int k=0; k<65; k++)
				{
	    	     	if(m_CFeed[cfds][cchan][k].bFSd ==0)
		         		break;
    	            int ffds = m_CFeed[cfds][cchan][k].bFSd;
	             	int fchan = m_CFeed[cfds][cchan][k].bchanel;
					if(m_ABFlist[ffds][fchan].fchan == 1)
					{
						nItemCount = 7;
	    	       		break;
					}
				}
				if(nItemCount == 7)
	    	       		break;
			}//int j=0; j<65; j++)
			if(nItemCount == 0)
			{
	        		iter = m_cpstr.erase(iter);
					m_ABFlist[nfds][nchan].fchan =0;
					B_change = TRUE;
			}
	    	else
			    	iter++;

		}//i=m_cpstr.size()-1; i>=0; i--)
	}//if(abfnum == 5)

	if(B_change)
		BuildList(abfnum);
    UpList( abfnum);
}

void CResourceViewPane::BuildList(int abfnum)
{
    m_listCtrl.DeleteAllItems();
    int nItemCount= 0;
	for(int i=m_cpstr.size()-1; i>=0; i--)
	{
            	CString  strf,strc,dddd,d4;
				dddd = m_cpstr[i];
           		strf = dddd.Mid(0,2);
        		strc = dddd.Mid(3);
    	    	int nfds = theApp.m_Str2Data.String2Int(strf);
	        	int nchan = theApp.m_Str2Data.String2Int(strc);
		for(int j=0; j<65; j++)
		{
			if(m_ADCbreakE[nfds][nchan][j].bFSd ==0)
				break;
    	    	int cfds = m_ADCbreakE[nfds][nchan][j].bFSd;
	        	int cchan = m_ADCbreakE[nfds][nchan][j].bchanel;
    		for(int k=0; k<65; k++)
			{
		     	if(m_CFeed[cfds][cchan][k].bFSd ==0)
		     		break;
    	m_listCtrl.InsertItem(nItemCount, m_SlaveStation[nfds][nchan].WatchName+"|"+m_SlaveStation[nfds][nchan].strPN, 0);
        m_listCtrl.SetRowColor(nItemCount, RGB(255,0,0), RGB(255,255,255));
		       	nItemCount++;
			}
			if(k == 0)
			{
    	m_listCtrl.InsertItem(nItemCount, m_SlaveStation[nfds][nchan].WatchName+"|"+m_SlaveStation[nfds][nchan].strPN, 0);
        m_listCtrl.SetRowColor(nItemCount, RGB(255,0,0), RGB(255,255,255));
    			nItemCount++;
			}
		}
			if(j == 0)
			{
    	m_listCtrl.InsertItem(nItemCount, m_SlaveStation[nfds][nchan].WatchName+"|"+m_SlaveStation[nfds][nchan].strPN, 0);
        m_listCtrl.SetRowColor(nItemCount, RGB(255,0,0), RGB(255,255,255));
    			nItemCount++;
			}
	}
	B_change = FALSE;
}

void CResourceViewPane::UpList(int abfnum)
{
	int nItemCount= 0;
	for(int i=m_cpstr.size()-1; i>=0; i--)
	{
            	CString  strf,strc,dddd,d4;
				dddd = m_cpstr[i];
           		strf = dddd.Mid(0,2);
        		strc = dddd.Mid(3);
    	    	int nfds = theApp.m_Str2Data.String2Int(strf);
	        	int nchan = theApp.m_Str2Data.String2Int(strc);

	CString strtempA,strtempv,strtemp2,strtempB,strtempS,strtempN;
	strtemp2="";
	unsigned char	nstatus = m_SlaveStation[nfds][nchan].Channel_state;
				  COleDateTime oleDateTime=m_ADMainDis[nfds][nchan].ATime ;
	strtempA = oleDateTime.Format(_T("%Y-%m-%d %H:%M:%S")); 
	oleDateTime=m_ADMainDis[nfds][nchan].BTime ;
	strtempB = oleDateTime.Format(_T("%Y-%m-%d %H:%M:%S")); 
	if(oleDateTime.GetYear() == 1900)
		strtempB ="";
	oleDateTime=m_ADMainDis[nfds][nchan].NTime ;
	strtempN = oleDateTime.Format(_T("%Y-%m-%d %H:%M:%S")); 
	if(oleDateTime.GetYear() == 1900)
		strtempN ="";
	  oleDateTime=m_SlaveStation[nfds][nchan].ValueTime;
	strtempS = oleDateTime.Format(_T("%Y-%m-%d %H:%M:%S")); 

	int	ufData6 = m_SlaveStation[nfds][nchan].ptype;
	     			  if( ufData6<3)
					  {
						  if(m_SlaveStation[nfds][nchan].AValue > m_SlaveStation[nfds][nchan].m_RangeH)
						  {}
				    	  else
						  {
							  if(ufData6 == 2)
            					  strtempv.Format("%.0f",m_SlaveStation[nfds][nchan].AValue);
							  else
    	     			    	  strtempv.Format("%.2f",m_SlaveStation[nfds][nchan].AValue);
							  strtempv += m_SlaveStation[nfds][nchan].m_Unit;
						  }
					  }
			    	  else
					  {
				    	  int nstatus1 = m_SlaveStation[nfds][nchan].CValue;
					     if(nstatus1 == 0)
						  strtempv= m_SlaveStation[nfds][nchan].ZeroState;
					     else if(nstatus1 == 1)
						  strtempv= m_SlaveStation[nfds][nchan].OneState;
				     	  else if(nstatus1 == 2)
						  strtempv= m_SlaveStation[nfds][nchan].TwoState;
					  }
					  if((nstatus == 0x40)||(nstatus == 0x50)||(nstatus == 0x80)||(nstatus == 0x70)||(nstatus == 0x90)|| (nstatus == 0xa0) || (nstatus == 0xa1))
				    		  strtempv= theApp.m_RTDM.strstatus(nstatus);

		for(int j=0; j<65; j++)
		{
			if(m_ADCbreakE[nfds][nchan][j].bFSd ==0)
				break;
    	    	int cfds = m_ADCbreakE[nfds][nchan][j].bFSd;
	        	int cchan = m_ADCbreakE[nfds][nchan][j].bchanel;
    		for(int k=0; k<65; k++)
			{
		     	if(m_CFeed[cfds][cchan][k].bFSd ==0)
		     		break;
    	        int ffds = m_CFeed[cfds][cchan][k].bFSd;
	        	int fchan = m_CFeed[cfds][cchan][k].bchanel;
				if(abfnum == 1)//aa
				{
                	m_listCtrl.SetItemText(nItemCount, 1, strtempv);
                	m_listCtrl.SetItemText(nItemCount, 2, strtempA);
                	m_listCtrl.SetItemText(nItemCount, 3, strtempB);
                	m_listCtrl.SetItemText(nItemCount, 4, strtempN);
                	m_listCtrl.SetItemText(nItemCount, 5, m_SlaveStation[ffds][fchan].strPN+"|"+m_SlaveStation[ffds][fchan].FeedState+"|"+m_ADMainDis[ffds][fchan].RTime.Format(_T("%Y-%m-%d %H:%M:%S")));
		    		if(m_SlaveStation[nfds][nchan].strSafe !="")
		    			strtemp2 =m_SlaveStation[nfds][nchan].strSafe+"|"+m_ADMainDis[nfds][nchan].AMaxTime.Format(_T("%Y-%m-%d %H:%M:%S"));
                 	m_listCtrl.SetItemText(nItemCount, 6, strtemp2);
				}
				else if(abfnum == 2)//ab
				{
                	m_listCtrl.SetItemText(nItemCount, 1, strtempv);
                	m_listCtrl.SetItemText(nItemCount, 2, strtempB);
                	m_listCtrl.SetItemText(nItemCount, 3, m_SlaveStation[nfds][nchan].strBS);
                	m_listCtrl.SetItemText(nItemCount, 4, m_SlaveStation[ffds][fchan].strPN+"|"+m_SlaveStation[ffds][fchan].FeedState+"|"+m_ADMainDis[ffds][fchan].RTime.Format(_T("%Y-%m-%d %H:%M:%S")));
		    		if(m_SlaveStation[nfds][nchan].strSafe !="")
		    			strtemp2 =m_SlaveStation[nfds][nchan].strSafe+"|"+m_ADMainDis[nfds][nchan].AMaxTime.Format(_T("%Y-%m-%d %H:%M:%S"));
                 	m_listCtrl.SetItemText(nItemCount, 5, strtemp2);
				}
				else if(abfnum == 3 || abfnum == 4 || abfnum == 5)//af dab  df
				{
                    	m_listCtrl.SetItemText(nItemCount, 1, strtempv);
                    	m_listCtrl.SetItemText(nItemCount, 2, strtempA);
                	m_listCtrl.SetItemText(nItemCount, 3, strtempB);
                	m_listCtrl.SetItemText(nItemCount, 4, m_SlaveStation[nfds][nchan].strBS);
                	m_listCtrl.SetItemText(nItemCount, 5, m_SlaveStation[ffds][fchan].strPN+"|"+m_SlaveStation[ffds][fchan].FeedState+"|"+m_ADMainDis[ffds][fchan].RTime.Format(_T("%Y-%m-%d %H:%M:%S")));
		        		if(m_SlaveStation[nfds][nchan].strSafe !="")
		        			strtemp2 =m_SlaveStation[nfds][nchan].strSafe+"|"+m_ADMainDis[nfds][nchan].AMaxTime.Format(_T("%Y-%m-%d %H:%M:%S"));
                    	m_listCtrl.SetItemText(nItemCount, 6, strtemp2);
				}
		       	nItemCount++;
			}//for(int k=0; k<65; k++)
			if(k == 0)
			{
				if(abfnum == 1)//aa
				{
                	m_listCtrl.SetItemText(nItemCount, 1, strtempv);
                	m_listCtrl.SetItemText(nItemCount, 2, strtempA);
                 	m_listCtrl.SetItemText(nItemCount, 3, strtempB);
                 	m_listCtrl.SetItemText(nItemCount, 4, strtempN);
                 	m_listCtrl.SetItemText(nItemCount, 5, "");
		    		if(m_SlaveStation[nfds][nchan].strSafe !="")
	    				strtemp2 =m_SlaveStation[nfds][nchan].strSafe+"|"+m_ADMainDis[nfds][nchan].AMaxTime.Format(_T("%Y-%m-%d %H:%M:%S"));
                	m_listCtrl.SetItemText(nItemCount, 6, strtemp2);
				}
				else if(abfnum == 2)//ab
				{
                	m_listCtrl.SetItemText(nItemCount, 1, strtempv);
                	m_listCtrl.SetItemText(nItemCount, 2, strtempB);
                	m_listCtrl.SetItemText(nItemCount, 3, m_SlaveStation[nfds][nchan].strBS);
                	m_listCtrl.SetItemText(nItemCount, 4, "");
		    		if(m_SlaveStation[nfds][nchan].strSafe !="")
		    			strtemp2 =m_SlaveStation[nfds][nchan].strSafe+"|"+m_ADMainDis[nfds][nchan].AMaxTime.Format(_T("%Y-%m-%d %H:%M:%S"));
                 	m_listCtrl.SetItemText(nItemCount, 5, strtemp2);
				}
				else if(abfnum == 4)// dab
				{
                    	m_listCtrl.SetItemText(nItemCount, 1, strtempv);
                    	m_listCtrl.SetItemText(nItemCount, 2, strtempA);
                	m_listCtrl.SetItemText(nItemCount, 3, strtempB);
                	m_listCtrl.SetItemText(nItemCount, 4, m_SlaveStation[nfds][nchan].strBS);
                	m_listCtrl.SetItemText(nItemCount, 5, "");
		        		if(m_SlaveStation[nfds][nchan].strSafe !="")
		        			strtemp2 =m_SlaveStation[nfds][nchan].strSafe+"|"+m_ADMainDis[nfds][nchan].AMaxTime.Format(_T("%Y-%m-%d %H:%M:%S"));
                    	m_listCtrl.SetItemText(nItemCount, 6, strtemp2);
				}
    			nItemCount++;
			}
		}//for(int j=0; j<65; j++)
			if(j == 0)
			{
				if(abfnum == 1)//aa
				{
                 	m_listCtrl.SetItemText(nItemCount, 1, strtempv);
                	m_listCtrl.SetItemText(nItemCount, 2, strtempA);
                	m_listCtrl.SetItemText(nItemCount, 3, strtempB);
                	m_listCtrl.SetItemText(nItemCount, 4, strtempN);
                	m_listCtrl.SetItemText(nItemCount, 5, "");
    				if(m_SlaveStation[nfds][nchan].strSafe !="")
	    				strtemp2 =m_SlaveStation[nfds][nchan].strSafe+"|"+m_ADMainDis[nfds][nchan].AMaxTime.Format(_T("%Y-%m-%d %H:%M:%S"));
                	m_listCtrl.SetItemText(nItemCount, 6, strtemp2);
				}
				else if(abfnum == 2)//ab
				{
                	m_listCtrl.SetItemText(nItemCount, 1, strtempv);
                	m_listCtrl.SetItemText(nItemCount, 2, strtempB);
                	m_listCtrl.SetItemText(nItemCount, 3, m_SlaveStation[nfds][nchan].strBS);
                	m_listCtrl.SetItemText(nItemCount, 4, "");
		    		if(m_SlaveStation[nfds][nchan].strSafe !="")
		    			strtemp2 =m_SlaveStation[nfds][nchan].strSafe+"|"+m_ADMainDis[nfds][nchan].AMaxTime.Format(_T("%Y-%m-%d %H:%M:%S"));
                 	m_listCtrl.SetItemText(nItemCount, 5, strtemp2);
				}
				else if(abfnum == 4)// dab
				{
                    	m_listCtrl.SetItemText(nItemCount, 1, strtempv);
                    	m_listCtrl.SetItemText(nItemCount, 2, strtempA);
                	m_listCtrl.SetItemText(nItemCount, 3, strtempB);
                	m_listCtrl.SetItemText(nItemCount, 4, m_SlaveStation[nfds][nchan].strBS);
                	m_listCtrl.SetItemText(nItemCount, 5, "");
		        		if(m_SlaveStation[nfds][nchan].strSafe !="")
		        			strtemp2 =m_SlaveStation[nfds][nchan].strSafe+"|"+m_ADMainDis[nfds][nchan].AMaxTime.Format(_T("%Y-%m-%d %H:%M:%S"));
                    	m_listCtrl.SetItemText(nItemCount, 6, strtemp2);
				}
       			nItemCount++;
			}
	}//for(int i=m_cpstr.size()-1; i>=0; i--)
}


