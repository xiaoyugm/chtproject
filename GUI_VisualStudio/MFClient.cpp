// MFClient.cpp: implementation of the CMQClient class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "GUI_VisualStudio.h"
#include "MFClient.h"
//#include <io.h>
#include "MainFrm.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMFClient::CMFClient()
{
//		m_ndkSend=NULL;
//	ConnectDB();
//	m_nodialog = true;
	m_vdf = 0;
	m_bIsDownloading = FALSE;
	m_nFileSize      = 0;
}

CMFClient::~CMFClient()
{

}

//向主机发送信息
BOOL CMFClient::SendMessage(CNDKMessage &message)
{
	if(SendMessageToServer(message))
	{
		return TRUE;
	}
	return FALSE;
}

//连接主机
BOOL CMFClient::ConnectServer(CString strIp,UINT lPort)
{
	if(OpenConnection(strIp, lPort))
	{
		ConnectTime = CTime::GetCurrentTime();
		return TRUE;
	}
	return FALSE;
}

BOOL CMFClient::Ping()
{
	return FALSE;
}

//响应服务器发来的消息
void CMFClient::OnMessage(CNDKMessage& message)
{
	switch(message.GetId())
	{
	case SERVER_FILES:
		GetFiles(message);
		break;
	case DISDRAWMENU:
		SyncMenu(message);
		break;

/*	case SERVER_FILES:
		{
			// Add the file name in the list
			for (int nFileIndex = 0; nFileIndex < message.GetNbElements(); nFileIndex++)
			{
				CString strFileName;

				message.GetAt(nFileIndex, strFileName);

//				m_listServerFiles.AddString(strFileName);
			}

//			UpdateUI();
		}
		break;*/

	case START_TRANSFERT:
		{
			message.GetAt(0, m_nFileSize);
			
//			m_progressDownload.SetRange32(0, m_nFileSize);
			
			// Ask the server for the first file part
			message.SetId(REQUEST_NEXT_FILE_PART);
			SendMessageToServer(message);
		}
		break;

	case NEXT_FILE_PART:
		{
			message.GetAt(0, m_byteBuffer, m_unBufferLength);

			m_fileDownload.Write(m_byteBuffer, m_unBufferLength);

//			m_progressDownload.OffsetPos(m_unBufferLength);

			// Ask the server for the first file part
			CNDKMessage requestMessage(REQUEST_NEXT_FILE_PART);
			SendMessageToServer(requestMessage);
		}
		break;

	case TRANSFERT_COMPLETED:
		{
    		m_fileDownload.Close();
    		m_bIsDownloading = FALSE;
	    	if(m_vdf <v_disdrawf.size())
			{
	        	Syncdown(m_vdf);
    	    	m_vdf++;
			}
			else
			{//更新后存本地数据库
				SaveFileS3();
			}
		}
//		AfxMessageBox(IDS_FILE_DOWNLOADED_SUCCESSFULLY);

		break;
	default:
		break;
	}
}

void CMFClient::OnPing(long lNbMilliseconds)
{

}

void CMFClient::OnDisconnect(NDKClientDisconnection disconnectionType)
{

	if (m_bIsDownloading)
	{
		m_fileDownload.Close();

		m_bIsDownloading = FALSE;

//		m_progressDownload.SetPos(0);
	}

}

//连接数据库
void CMFClient::ConnectDB()
{
    CString szConnect = _T("Provider=SQLOLEDB.1;Persist Security Info=True;\
                          User ID=sa;Password=sunset;\
                          Data Source=") +strDBname+ _T(";Initial Catalog=BJygjl");
//All calls to the AxLib should be wrapped in a try / catch block
  try
  {
    dbAx::Init();
    m_Cn.Create();
//    m_Cn._SetConnectionEvents(new CCardFileEvents);
    m_Cn.CursorLocation(adUseClient);
    m_Cn.Open((LPCTSTR)szConnect);

	Initdrawfile();

//	    m_ndkRTD = new unsigned char[6];
  }
  catch ( dbAx::CAxException *e )
  {
		AfxMessageBox(e->m_szErrorDesc +  _T("BJygjl Message"));
//    MessageBox(e->m_szErrorDesc, _T("BJygjl Message"), MB_OK);
    delete e;
    return ;
  }

}
//实时更新菜单
void CMFClient::SyncMenu(CNDKMessage& message)
{
	Initdrawfile();
	if(theApp.C_Ts.m_osIP[0] != theApp.m_strms[17].strl || (gstrTimeOut + "\\") != theApp.m_strms[18].strl)
	{
    	m_vdf = 0;
		if(m_vdf <v_disdrawf.size())
		{
	    	Syncdown(m_vdf);
    		m_vdf++;
		}
	}
	else if(theApp.C_Ts.m_osIP[0] == theApp.m_strms[17].strl && (gstrTimeOut + "\\") == theApp.m_strms[18].strl)
	{
		SaveFileS3();
	}
}

//将收到的SQL语句写入到数据库中
void CMFClient::WriteSQL(CNDKMessage& message)
{
	CString strSql;
//	message.GetAt(0,strSql);
//	if(!strSql.IsEmpty())
//		m_SQLDirect.ExecuteSQL(strSql);
}

//根据NowTime 和 MessageTime,检查主机的状态
void CMFClient::HostStateCheck()
{
	if(!PingServer())
	{
		//此时备机做主机启动
		AfxMessageBox("与主机的通讯联系失败,请检查!");
	}
}

//关闭到主机的连接
void CMFClient::Close()
{
  try
  {
/*    if ( m_AccountSet._IsOpen() )
      m_AccountSet.Close();
    if ( m_ContactSet._IsOpen() )
      m_ContactSet.Close();
    if ( m_MAlocation._IsOpen() )
      m_MAlocation.Close();
    if ( m_PointDes._IsOpen() )
      m_PointDes.Close();
    if ( m_Control._IsOpen() )
      m_Control.Close();*/
    if ( m_Drawfile._IsOpen() )
      m_Drawfile.Close();

    m_Cn.Close();
    //Cleanup the AxLib library
    dbAx::Term();
  }
  catch ( CAxException *e )
  {
		AfxMessageBox(e->m_szErrorDesc +  _T("BJygjl Message"));
 //    MessageBox(e->m_szErrorDesc, _T("BJygjl Message"), MB_OK);
    delete e;
  }
	CloseConnection();
}

//第一次连接如需要，可以更新
void CMFClient::GetFiles(CNDKMessage& message)
{
	CString strddd ;
	char buf[BUFFER_SIZE];
	LPCTSTR ggg="hhh" ;
	char filter[] = "";
	int nYear,nMonth;
	message.GetAt(0,ggg);
	strddd = ggg;
//	message.GetAt(1,nMonth);
//	message.GetAt(2,nDay);
//	message.GetAt(3,nHour);
//	message.GetAt(4,nMinute);
//	message.GetAt(5,nSecond);
//	CTime time(nYear, nMonth, nDay, nHour, nMinute, nSecond);
//	StartTime = time;
//	gggg.Format("%d  %d  %d  %d  %d  ",nYear,nMonth,nDay,nHour,nMinute);
//		AfxMessageBox(gggg);
//	C_Ts.GetPCNameIP();
//主机 在线服务器 不同 or 目录不同
	if(theApp.C_Ts.m_osIP[0] != theApp.m_strms[17].strl || (gstrTimeOut + "\\") != theApp.m_strms[18].strl)
	{
		if(m_vdf <v_disdrawf.size())
		{
	    	Syncdown(m_vdf);
    		m_vdf++;
		}
	}
	else if(theApp.C_Ts.m_osIP[0] == theApp.m_strms[17].strl && (gstrTimeOut + "\\") == theApp.m_strms[18].strl)
	{
		SaveFileS3();
	}
}

void CMFClient::Syncdown(int n_files)
{
//    	for ( int k = 0 ; k < v_disdrawf.size() ; k++ )
//	LPCTSTR str1 = "",str2 = "",str3 = "";
			CString strFileName = v_disdrawf[n_files];
//     	m_Str2Data.SplittoCString(strFileName,str1,str2,str3);
//		strFileName= str1;
		downdfiles(strFileName);
}

void CMFClient::downdfiles(CString strfile)
{
			// Retrieve the file name with the extension
			char szFileName[_MAX_FNAME];
			char szExtension[_MAX_EXT];
			_splitpath(strfile, NULL, NULL, szFileName, szExtension);
        	CString strrsy = gstrTimeOut + "\\" + strMetrics+ "rsy\\";
        	CString strrsy1 = gstrTimeOut + "\\Image\\";
           //	strrsy1 ="dispoint"+strMetrics;
			CString strFileNameToCreate,strex;
			strex = szExtension;
			if(strex == ".rsy")
    			::PathCombine(strFileNameToCreate.GetBuffer(_MAX_PATH), strrsy, CString(szFileName) + szExtension);
			else//图像文件
    			::PathCombine(strFileNameToCreate.GetBuffer(_MAX_PATH), strrsy1, CString(szFileName) + szExtension);
			strFileNameToCreate.ReleaseBuffer();
			// Open the file
			if (m_fileDownload.Open(strFileNameToCreate, CFile::modeCreate | CFile::modeWrite))
			{
				m_bIsDownloading = TRUE;
				// Ask the server to start the download
				CNDKMessage message(REQUEST_FILE);
				message.Add(strfile);
				SendMessageToServer(message);
//				UpdateUI();
			}
}

BOOL CMFClient::Initdrawfile()
{
			for(int i = 0; i < 11;i++ )
		    	for(int j = 0; j < 101;j++ )
				{
			    		m_strdf[i][j].strl = "";  //
			    		m_strdfall[i][j].strl = "";  //
						m_s3draw[j].strl = "";
						m_iddf[i][j].n_iddf =0;
				}

    if ( m_Drawfile._IsOpen() )
      m_Drawfile.Close();
		m_Drawfile.Create();
		m_Drawfile.CursorType(adOpenDynamic);
		m_Drawfile.CacheSize(50);
		m_Drawfile._SetRecordsetEvents(new CAccountSetEvents);
		m_Drawfile.Open(_T("Select * From drawfile WHERE DRAWID<100"), &m_Cn);
		m_Drawfile.MarshalOptions(adMarshalModifiedOnly);

            	CString  strf,strc,strItem;
	LPCTSTR str1 = "",str2 = "",str3 = "";
	    if ( !m_Drawfile._IsEmpty() )
		{
	    	m_Drawfile.MoveFirst();
    		while ( !m_Drawfile.IsEOF() )//读文件信息
			{
	        	int nfds = m_Drawfile.m_szDRAWID; 
        		strItem = m_Drawfile.m_szD1024;
       			strItem.TrimRight();
				m_strdfall[0][nfds].strl =strItem;//全文件 id ver
				str1 = "",str2 = "",str3 = "";
     	m_Str2Data.SplittoCString(strItem,str1,str2,str3);
        		strItem = str1;
				m_strdf[0][nfds].strl =strItem;  //文件名
        		strItem = str2;
				m_iddf[0][nfds].n_iddf = m_Str2Data.String2Int(strItem);
//				Isdfdel(0 ,strItem ,nfds);
     			strItem = m_Drawfile.m_szD1280;
       			strItem.TrimRight();
				m_strdfall[1][nfds].strl =strItem;
				str1 = "",str2 = "",str3 = "";
     	m_Str2Data.SplittoCString(strItem,str1,str2,str3);
        		strItem = str1;
				m_strdf[1][nfds].strl =strItem;
        		strItem = str2;
				m_iddf[1][nfds].n_iddf = m_Str2Data.String2Int(strItem);
//				Isdfdel(1 ,strItem,nfds);
     			strItem = m_Drawfile.m_szD1360;
       			strItem.TrimRight();
				m_strdfall[2][nfds].strl =strItem;
				str1 = "",str2 = "",str3 = "";
     	m_Str2Data.SplittoCString(strItem,str1,str2,str3);
        		strItem = str1;
				m_strdf[2][nfds].strl =strItem;
        		strItem = str2;
				m_iddf[2][nfds].n_iddf = m_Str2Data.String2Int(strItem);
//				Isdfdel(2 ,strItem,nfds);
     			strItem = m_Drawfile.m_szD1366;
       			strItem.TrimRight();
				m_strdfall[3][nfds].strl =strItem;
				str1 = "",str2 = "",str3 = "";
     	m_Str2Data.SplittoCString(strItem,str1,str2,str3);
        		strItem = str1;
				m_strdf[3][nfds].strl =strItem;
        		strItem = str2;
				m_iddf[3][nfds].n_iddf = m_Str2Data.String2Int(strItem);
//				Isdfdel(3 ,strItem,nfds);
     			strItem = m_Drawfile.m_szD1400;
       			strItem.TrimRight();
				m_strdfall[4][nfds].strl =strItem;
				str1 = "",str2 = "",str3 = "";
     	m_Str2Data.SplittoCString(strItem,str1,str2,str3);
        		strItem = str1;
				m_strdf[4][nfds].strl =strItem;
        		strItem = str2;
				m_iddf[4][nfds].n_iddf = m_Str2Data.String2Int(strItem);
//				Isdfdel(4 ,strItem,nfds);
     			strItem = m_Drawfile.m_szD1440;
       			strItem.TrimRight();
				m_strdfall[5][nfds].strl =strItem;
				str1 = "",str2 = "",str3 = "";
     	m_Str2Data.SplittoCString(strItem,str1,str2,str3);
        		strItem = str1;
				m_strdf[5][nfds].strl =strItem;
        		strItem = str2;
				m_iddf[5][nfds].n_iddf = m_Str2Data.String2Int(strItem);
//				Isdfdel(5 ,strItem,nfds);
     			strItem = m_Drawfile.m_szD1600;
       			strItem.TrimRight();
				m_strdfall[6][nfds].strl =strItem;
				str1 = "",str2 = "",str3 = "";
     	m_Str2Data.SplittoCString(strItem,str1,str2,str3);
        		strItem = str1;
				m_strdf[6][nfds].strl =strItem;
        		strItem = str2;
				m_iddf[6][nfds].n_iddf = m_Str2Data.String2Int(strItem);
//				Isdfdel(6 ,strItem,nfds);
     			strItem = m_Drawfile.m_szD1680;
       			strItem.TrimRight();
				m_strdfall[7][nfds].strl =strItem;
				str1 = "",str2 = "",str3 = "";
     	m_Str2Data.SplittoCString(strItem,str1,str2,str3);
        		strItem = str1;
				m_strdf[7][nfds].strl =strItem;
        		strItem = str2;
				m_iddf[7][nfds].n_iddf = m_Str2Data.String2Int(strItem);
//				Isdfdel(7 ,strItem,nfds);
     			strItem = m_Drawfile.m_szD1920;
       			strItem.TrimRight();
				m_strdfall[8][nfds].strl =strItem;
				str1 = "",str2 = "",str3 = "";
     	m_Str2Data.SplittoCString(strItem,str1,str2,str3);
        		strItem = str1;
				m_strdf[8][nfds].strl =strItem;
        		strItem = str2;
				m_iddf[8][nfds].n_iddf = m_Str2Data.String2Int(strItem);
//				Isdfdel(8 ,strItem,nfds);
     			strItem = m_Drawfile.m_szD2048;
       			strItem.TrimRight();
				m_strdfall[9][nfds].strl =strItem;
				str1 = "",str2 = "",str3 = "";
     	m_Str2Data.SplittoCString(strItem,str1,str2,str3);
        		strItem = str1;
				m_strdf[9][nfds].strl =strItem;
        		strItem = str2;
				m_iddf[9][nfds].n_iddf = m_Str2Data.String2Int(strItem);
//				Isdfdel(9 ,strItem,nfds);
     			strItem = m_Drawfile.m_szD2560;
       			strItem.TrimRight();
				m_strdfall[10][nfds].strl =strItem;
				str1 = "",str2 = "",str3 = "";
     	m_Str2Data.SplittoCString(strItem,str1,str2,str3);
        		strItem = str1;
		    		m_strdf[10][nfds].strl =strItem;
        		strItem = str2;
				m_iddf[10][nfds].n_iddf = m_Str2Data.String2Int(strItem);
//    				Isdfdel(10 ,strItem,nfds);
				m_Drawfile.MoveNext();
			}
		}

	CString strrsy ,strrsy1,strclm;
	strrsy = gstrTimeOut + "\\" + strMetrics+ "rsy\\";
	strrsy1 ="dispoint"+strMetrics;
    	int m_ishave =0;
		CppSQLite3Query q;
		v_disdrawf.clear();
			strItem.Format("select * from '%s' WHERE DISID<300 and DISID>199;",strrsy1);
            q = theApp.db3.execQuery(strItem);
            while (!q.eof())
			{
//            	int m_del =0;
				m_ishave = q.getIntField(0);
                strclm = q.getStringField(1);
	    		strclm.TrimRight(); 
				if(strclm == "")
					break;
				m_s3draw[m_ishave-200].strl=strclm;
                q.nextRow();
			}
          	for ( int k = 0 ; k < 100 ; k++ )
			{
				m_ishave =0;
				strclm = m_strdfall[theApp.Initfbl(strMetrics)][k].strl;
				if(strclm == "")
					break;
               	for ( int i = 0 ; i < 100 ; i++ )//比较文件是否修改
				{
					strItem =m_s3draw[i].strl;
					if(strItem == "")
						break;
					if(strItem == strclm)
					{
						m_ishave =100;
			    		break;
					}
				}
				if(m_ishave ==0)//修改或无文件
				{
					strclm = m_strdf[theApp.Initfbl(strMetrics)][k].strl;
					v_disdrawf.push_back(strclm);//需要下载的文件
					strclm = theApp.SplitPath(strclm);
					CloseDrawfile(strclm);//关闭正在打开文件
					GetTableData(m_iddf[theApp.Initfbl(strMetrics)][k].n_iddf);
				}
			}
/*			for(int i=0;i<theApp.m_addfilesy.size();i++)
			{
                	strclm = theApp.m_addfilesy[i];
             		int m_ishave = strclm.GetLength();
             		strclm = strclm.Mid(m_ishave-3,3);
		         if(strclm == "rsy")
				 {
                  	for ( int i = 0 ; i < 100 ; i++ )//比较文件是否存在
					{
			    		strItem =m_strdf[theApp.Initfbl(strMetrics)][i].strl;
			    		if(strItem == "")
						break;
				     	if(strItem == strclm)
						{
						m_ishave =100;
			    		break;
						}
					}
				 }
			}*/
//			m_ishave =v_disdrawf.size();
    if(v_disdrawf.size() == 0)
           theApp.m_senddata =true;
	else
	{
//            strSQL.Format("UPDATE '%s' SET LP%d='%d' WHERE DISID=%d;",
//			    	     strrsy1, m_ntrans ,m_color1 , coxx );
//			theApp.db3.execDML(strSQL);
	}

    return TRUE;
}
//读id的数据，图像文件
void CMFClient::GetTableData(int nline)
{
	LPCTSTR str1 = "",str2 = "",str3 = "";
	CString strTable;
	CString strDate;
	_bstr_t Explain;
	strTable.Format("SELECT * FROM drawjpg%s WHERE JPGID=%d",strMetrics,nline);

    CString strDBLink = _T("Provider=SQLOLEDB.1;Persist Security Info=True;\
                          User ID=sa;Password=sunset;\
                          Data Source=") +strDBname+ _T(";Initial Catalog=BJygjl");

	::CoInitialize(NULL);
//	CString strDBLink = "Provider=SQLOLEDB.1;Persist Security Info=False;User ID=kj86;Password=kj86;Initial Catalog=masterdefine;Data Source="
//					+ gstrIP;
	try
	{
		ADOCust::_RecordsetPtr pRS;
		pRS.CreateInstance(__uuidof(ADOCust::Recordset));
		pRS->Open(_bstr_t(strTable),_bstr_t(strDBLink), ADOCust::adOpenStatic ,ADOCust::adLockReadOnly , ADOCust::adCmdText );
		int unPointNo,unCollectData ;
		COleDateTime BeginTime,EndTime;
		CString strBeginTime,strEndTime;

		while(!pRS->EndOfFile)
		{
          	for ( int k = 0 ; k < 100 ; k++ )
			{
				strDate.Format("J%d",k);
    			Explain = pRS->Fields->Item[_variant_t(strDate)]->Value;
    			strDate.Format("%s",(char *)Explain); 	strDate.TrimRight();
     			str1 = "",str2 = "",str3 = "";
            	m_Str2Data.SplittoCString(strDate,str1,str2,str3);
    			strDate=str1; if(strDate == "") break;
     			v_disdrawf.push_back(theApp.m_strms[18].strl +"Image\\" +str1);
     			strDate=str2; if(strDate == "") break;
    			v_disdrawf.push_back(theApp.m_strms[18].strl +"Image\\" +str2);
      			strDate=str3; if(strDate == "") break;
    			v_disdrawf.push_back(theApp.m_strms[18].strl +"Image\\" +str3);
			}
//			unCollectData = pRS->Fields->Item["J1"]->Value.lVal;
//			strBeginTime.Format("%d-%d-%d %d:%d:%d",BeginTime.GetYear(),BeginTime.GetMonth(),BeginTime.GetDay(),BeginTime.GetHour(),BeginTime.GetMinute(),BeginTime.GetSecond());
//			strSQL.Format("INSERT INTO uCollectData VALUES(%d,%d,'%s','%s')",unPointNo,unCollectData,strBeginTime,strEndTime);
			pRS->MoveNext();
		}
		pRS->Close();
	}
	catch(_com_error &e)
	{
		AfxMessageBox(e.ErrorMessage());
	}
	::CoUninitialize();

}
//关闭打开文件
void CMFClient::CloseDrawfile(CString dfile)
{
	CString strrsy = gstrTimeOut + "\\" + strMetrics+ "rsy\\" ;
	CString strTemp1 =strrsy+dfile;
            	CMDIFrameWnd *pFrame = (CMDIFrameWnd*)AfxGetApp()->m_pMainWnd;
              	CMDIChildWnd *pChild = (CMDIChildWnd *) pFrame->GetActiveFrame();
				CDrawView *pView = (CDrawView*)pChild->GetActiveView();	
//     			if(!pView->IsKindOf(RUNTIME_CLASS(CDrawView)))
//            		return;

		        CString strTemp; 
				for(int i=0;i<theApp.m_addfilesy.size()+2;i++)
				{
    	        		if(m_ViewPos != NULL)
						{
			            	theApp.m_map.GetNextAssoc(m_ViewPos,strTemp,pView);
							if(strTemp == strTemp1)
							{
//       		            	if(pView != NULL)
                        		pView->GetParentFrame()->ActivateFrame();
								pChild = (CMDIChildWnd *) pFrame->GetActiveFrame();
                    			CDrawDoc* pThisOne = (CDrawDoc *)pChild->GetActiveDocument() ;
                    			pThisOne->OnCloseDocument();
								break;
							}
						}
		            	else 
		    	        	m_ViewPos = theApp.m_map.GetStartPosition() ;     //0415
				}
}

void CMFClient::SaveFileS3()
{
				m_vdf = 0;    CString strItem,strpo;
				CString strrsy1 ="dispoint"+strMetrics;
               	for ( int i = 0 ; i < 100 ; i++ )
				{
					strItem =m_strdfall[theApp.Initfbl(strMetrics)][i].strl;
                    strpo.Format("UPDATE '%s' SET LP0='%s' WHERE DISID=%d;",
			    	     strrsy1,strItem ,i+200);
	         		theApp.db3.execDML(strpo);
				}
                theApp.m_senddata =true;//更新菜单
}