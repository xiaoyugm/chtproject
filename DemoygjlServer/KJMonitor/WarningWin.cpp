// WarningWin.cpp : implementation file
//

#include "stdafx.h"
#include "kjmonitor.h"
#include "WarningWin.h"
#include "MainFrm.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWarningWin

IMPLEMENT_DYNCREATE(CWarningWin, CFormView)

CWarningWin::CWarningWin()
	: CFormView(CWarningWin::IDD)
{
	//{{AFX_DATA_INIT(CWarningWin)
	//}}AFX_DATA_INIT
}

CWarningWin::~CWarningWin()
{
}

void CWarningWin::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CWarningWin)
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CWarningWin, CFormView)
	//{{AFX_MSG_MAP(CWarningWin)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWarningWin diagnostics

#ifdef _DEBUG
void CWarningWin::AssertValid() const
{
	CFormView::AssertValid();
}

void CWarningWin::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CWarningWin message handlers

void CWarningWin::OnInitialUpdate() 
{
	CFormView::OnInitialUpdate();
	
	// TODO: Add your specialized code here and/or call the base class
	CMainFrame* pFWnd=(CMainFrame*)AfxGetMainWnd();
	pFWnd->m_pWarningWin=this;	
	m_nShowMsgCount = 100;//两个报警窗口各显示50条信息
	m_RefreshDbElapse = 10;//每出现10条新数据作一次添加操作,10条旧数据作一次删除操作
	m_warnNewDataLen = 10;
//	ConnectDB();
//	ReadWarnMsg();
}

void CWarningWin::AddDispWarnItem(int nAddDeleteInsert, CString strItemText)
{
	switch(nAddDeleteInsert)
	{
	case 0:  
		m_ctrlWarning1.AddString(strItemText,RGB(255,000,000));
		break;
	case 1: 
		m_ctrlWarning1.DeleteString(0);
		m_ctrlWarning1.AddString(strItemText,RGB(255,000,000));
		break;
	case 2:
		m_ctrlWarning1.AddString(strItemText,RGB(000,255,000));
		break;
	default:
		break;
	}
	UpdateData(FALSE);
}

int CWarningWin::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CFormView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
// Define the default style for the output list boxes.
//		CBRS_TOP|WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS 
//		| CBRS_SIZE_DYNAMIC,CBRS_XT_BUTTONS | CBRS_XT_GRIPPER)){

	DWORD dwStyle = CBRS_TOP|CBRS_LEFT | WS_CHILD | WS_VISIBLE | WS_VSCROLL| CBRS_GRIPPER
		| CBRS_TOOLTIPS | WS_TABSTOP | LBS_NOINTEGRALHEIGHT | LBS_OWNERDRAWFIXED | LBS_HASSTRINGS;
	// Create the sheet1 list box.
/*	if (!m_ctrlWarning1.Create( dwStyle, CRect(0,0,200,200), this, IDC_SHEET1 ))
	{
		AfxMessageBox( "Failed to create sheet1.\n" );
		return -1;
	}
	DWORD dwStyle2 = CBRS_LEFT | WS_CHILD | WS_VISIBLE | WS_VSCROLL | WS_TABSTOP | LBS_NOINTEGRALHEIGHT | LBS_OWNERDRAWFIXED | LBS_HASSTRINGS;
	if (!m_ctrlWarning2.Create( dwStyle2, CRect(200,0,500,200), this, IDC_SHEET2 ))	{
		AfxMessageBox( "Failed to create sheet2.\n" );		
		return -1;
	}
*/
	CXTSplitterWnd m_wndSplitter1;
	if (!m_wndSplitter1.CreateStatic(this, 1, 2))
	{
		TRACE0("Failed to create splitter window\n");
		return FALSE;
	}
	/*
	if (!m_wndSplitter1.CreateView(0, 1, RUNTIME_CLASS(CKJ86MonitorView),
		CSize(0, 0), pContext))
	{
		TRACE0("Failed to create CKJ86MonitorView\n"); 
		return FALSE;
	}
	*/
	return 0;
}

void CWarningWin::OnSize(UINT nType, int cx, int cy) 
{
	CFormView::OnSize(nType, cx, cy);	
	//modified by  2003/8/17
///	HWND hwnd= ::GetDlgItem(m_hWnd,IDC_SHEET1);
	RECT rect;
	GetClientRect(&rect);
	rect.right = rect.right / 2;
///	::SetWindowPos(hwnd,HWND_TOP,rect.left,rect.top,rect.right,rect.bottom,SWP_SHOWWINDOW);

///	HWND hwnd2= ::GetDlgItem(m_hWnd,IDC_SHEET2);
	GetClientRect(&rect);
	rect.left = rect.right / 2 ;
	rect.right = rect.right / 2 ;
///	::SetWindowPos(hwnd2,HWND_TOP,rect.left,rect.top,rect.right,rect.bottom,SWP_SHOWWINDOW);

}

void CWarningWin::AddWarnMsg(CString strItemText, int flag)
{
	//write string to listbox
	AddDispWarnStr(strItemText, flag);
	//获得当前的时间
	CTime curTime = CTime::GetCurrentTime();
	CString strTime = curTime.Format("%A-%B-%D %H:%M:%S");
	if (m_warnNewDataLen < m_RefreshDbElapse) {
		m_warnNewDataLen++;
		m_MsgCount++;
		m_warnQue[m_MsgCount - 1].msg = strItemText;
		m_warnQue[m_MsgCount - 1].flag = flag;
		m_warnQue[m_MsgCount - 1].ucID = -1;
		m_warnQue[m_MsgCount - 1].usDate = strTime;
		m_warnQue[m_MsgCount - 1].bNew = TRUE;
	}
	else{
		//将信息输入数据库，清空队列
///		FlushNewData();
		m_warnNewDataLen = 0;		
	}
	if (m_MsgCount > MAX_MESSAGE_COUNT){ 
		if (m_MsgCount - MAX_MESSAGE_COUNT > m_RefreshDbElapse){
			//删除数据
///			RemoveOldData();
///			ReadWarnMsg();
		}		
	}
}

void CWarningWin::LoadWarnMsg()
{
	//从数据库读入报警信息
	m_MsgCount = 0;
	CString strSQL;
	strSQL = "select * from uWarnMessage where ucStatus=1"; //1代表是报警信息警报信息 
	if(m_SQLDirect.ExecuteSQL(strSQL)==SQL_SUCCESS)
	{
		int nRet=m_SQLDirect.Fetch();//
		while(!nRet){
			m_innerDataID = atoi(m_SQLDirect.GetCol("ucID"));
			int flag = atoi(m_SQLDirect.GetCol("ucStatus")); //标志			
			CString strMsg = m_SQLDirect.GetCol("usMessage");
			CString strDate = m_SQLDirect.GetCol("ucDate");
			strMsg = "[" + strDate + "]: " + strMsg;
			AddDispWarnStr(strMsg, flag);
		}		
	}
}

BOOL CWarningWin::ConnectDB()
{
	BOOL flag = TRUE;
	try
	{
		m_SQLDirect.Init();
		if(m_SQLDirect.Connect(_T("masterdefine"),_T("kj86"),_T("kj86"))){
			AfxMessageBox("AddUser:无法连接用户参数数据库,请确定SQL SERVER服务是否运行!");
			flag = FALSE;
		}
	}
	catch(CDBException *e)
	{
		e->ReportError();
		return FALSE;
	}
	return TRUE;
}

/*将等待队列中的新的报警数据写入数据库*/
void CWarningWin::FlushNewData()
{
	//获取数据库中最小ID,
	//如果最小ID大于MAX_MESSAGE_COUNT,则更新所有的ID = ID - 500
	//if (!ConnectDB()) return;
	//获取数据库中最大的ID,则ID + 1,ID + 2,...为将要插入数据库的Id值
	UINT maxID;
	CString strSQL = "select max(ucID) from uWarnMessage";
	if(m_SQLDirect.ExecuteSQL(strSQL)==SQL_SUCCESS)
	{
		int nRet=m_SQLDirect.Fetch();//
		if (!nRet) //get success
		{
			if (m_SQLDirect.GetCol(1) == "")
				maxID = 0;
			else
				maxID = atoi(m_SQLDirect.GetCol(1));
		}
		else
			maxID = 0;
	}
	for(int i = 0; i <=	m_warnNewDataLen - 1; i ++){
		CString strSQL;
		m_warnQue[m_MsgCount - m_warnNewDataLen + i].ucID = maxID + i + 1;
		strSQL.Format("insert into uWarnMessage (ucID,ucStatus,usMessage,ucDate) values(%d,%d,'%s','%s')",
			m_warnQue[m_MsgCount - m_warnNewDataLen + i].ucID, m_warnQue[m_MsgCount - m_warnNewDataLen + i].flag, 
			m_warnQue[m_MsgCount - m_warnNewDataLen + i].msg, m_warnQue[m_MsgCount - m_warnNewDataLen + i].usDate);
		try{
			if(m_SQLDirect.ExecuteSQL(strSQL)==SQL_SUCCESS){}
			else{
				AfxMessageBox("向表格uWarnMessage添加数据失败!");}
			}
			catch(CException e){e.ReportError();}
	}
	//CloseDB();
}

int CWarningWin::GetFlag(int nIndex)
{
	COLORREF rgb;
/*	if (nIndex < m_nShowMsgCount / 2)
		rgb = m_ctrlWarning1.getColor(nIndex);
	else
		rgb = m_ctrlWarning2.getColor(nIndex - m_nShowMsgCount / 2);
	if (rgb == RGB(255,0,0))
		return 1;
	else
		return 0;*/
	if (nIndex <= m_nShowMsgCount / 2)
		rgb = m_ctrlWarning1.getColor(nIndex);
	else
		rgb = m_ctrlWarning2.getColor(nIndex );
	if (rgb == RGB(255,0,0))
		return 1;
	else
		return 0;
}

void CWarningWin::CloseDB()
{
	try
	{	m_SQLDirect.Close();}
	catch(CException e){	
		e.ReportError();
	}
}



void CWarningWin::RemoveOldData()
{
	int nID = -1;
	for(int i = 0; i < m_MsgCount - MAX_MESSAGE_COUNT; i++){
		if (nID < m_warnQue[i + MAX_MESSAGE_COUNT].ucID)
			nID = m_warnQue[i + MAX_MESSAGE_COUNT].ucID;
	}
	CString strSQL;
	strSQL.Format("delete from uWarnMessage where ucID <=%d", nID);
	if(m_SQLDirect.ExecuteSQL(strSQL)==SQL_SUCCESS)
	{	
		strSQL = "select min(ucID) from uWarnMessage";
		int minID = 0;
		if(m_SQLDirect.ExecuteSQL(strSQL)==SQL_SUCCESS){
			int nRet = m_SQLDirect.Fetch();
			if (!nRet){
				if (m_SQLDirect.GetCol(1) != "")
					minID = atoi(m_SQLDirect.GetCol(1));
			}
			if (minID > MAX_MESSAGE_COUNT){
				strSQL.Format("update uWarnMessage set ucID = ucID - %d",MAX_MESSAGE_COUNT); 
				m_SQLDirect.ExecuteSQL(strSQL);
			}
		}
	}
	else{
		AfxMessageBox("更新表uWarnMessage失败");
		return;
	}
}

void CWarningWin::AddDispWarnStr(CString strItemText, int flag)
{
	//update 界面
	COLORREF rgb;
	//添加一行
	if(flag)
		rgb = RGB(255,0,0);
	else
		rgb = RGB(0, 255, 0);
		//添加到首行
	m_ctrlWarning1.InsertString(0, strItemText, rgb);
	//获得列表长度
	int nItemCount = m_ctrlWarning1.GetCount();
	if (nItemCount >  m_nShowMsgCount / 2){ //left overflow

        int flag1 = GetFlag(nItemCount-1);
		char buf[256];
		m_ctrlWarning1.GetText(nItemCount-1 ,buf);
		CString strtemp = buf;
		m_ctrlWarning1.DeleteString(nItemCount-1 );
		if (flag1)
			rgb = RGB(255,0,0);
		else
			rgb = RGB(0, 255, 0);

		m_ctrlWarning2.InsertString(0, strtemp,rgb);
		int nItemCount = m_ctrlWarning2.GetCount();
		if (nItemCount > m_nShowMsgCount / 2)  //right over flow		
			m_ctrlWarning2.DeleteString(nItemCount-1 );
		
	}
}

void CWarningWin::OnDestroy() 
{
	CFormView::OnDestroy();
	CloseDB();	
	// TODO: Add your message handler code here
	
}

void CWarningWin::ReadWarnMsg()
{
//从数据库读入报警信息
	m_MsgCount = 0;
	CString strSQL;
	strSQL = "select * from uWarnMessage order by ucID"; //1代表是报警信息警报信息 
	if(m_SQLDirect.ExecuteSQL(strSQL)==SQL_SUCCESS)
	{
		int nRet=m_SQLDirect.Fetch();//
		while(!nRet){
			int flag = atoi(m_SQLDirect.GetCol("ucStatus")); //标志			
			CString strMsg = m_SQLDirect.GetCol("usMessage");
			CString strDate = m_SQLDirect.GetCol("ucDate");
			m_warnQue[m_MsgCount++].bNew = FALSE;
			m_warnQue[m_MsgCount - 1].flag = atoi(m_SQLDirect.GetCol("ucStatus"));
			m_warnQue[m_MsgCount - 1].msg = strMsg;
			m_warnQue[m_MsgCount - 1].ucID = atoi(m_SQLDirect.GetCol("ucID"));
			m_warnQue[m_MsgCount - 1].usDate = m_SQLDirect.GetCol("ucDate");
			nRet=m_SQLDirect.Fetch();//
		}		
	}
}
