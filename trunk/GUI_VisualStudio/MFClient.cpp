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
//	ConnectDB();
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
//        		AfxMessageBox(m_fileDownload.GetFileName());
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
	theApp.m_RTDM.Initdrawfile();

}
//实时更新菜单
void CMFClient::SyncMenu(CNDKMessage& message)
{
	theApp.m_RTDM.Initdrawfile();
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
	CloseConnection();
}

//第一次连接如需要，可以更新
void CMFClient::GetFiles(CNDKMessage& message)
{
	CString strddd ;
//	char buf[BUFFER_SIZE];
	LPCTSTR ggg="hhh" ;
//	char filter[] = "";
//	int nYear,nMonth;
	message.GetAt(0,ggg);
//	strddd = ggg;
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

//读id的数据，图像文件
void CMFClient::GetTableData(int nline)
{
	LPCTSTR str1 = "",str2 = "",str3 = "";
	CString strTable,strrsy,strDate;
	int m_ishave =0;
	strrsy = theApp.m_strms[18].strl + strMetrics+ "rsy\\";
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
//		int unPointNo,unCollectData ;
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
        		m_ishave = strDate.GetLength();
        		strDate = strDate.Mid(m_ishave-3,3);
        		if(strDate =="rsy")
         			v_disdrawf.push_back(strrsy +str1);
				else
        			v_disdrawf.push_back(theApp.m_strms[18].strl +"Image\\" +str1);
     			strDate=str2; if(strDate == "") break;
        		m_ishave = strDate.GetLength();
        		strDate = strDate.Mid(m_ishave-3,3);
        		if(strDate =="rsy")
         			v_disdrawf.push_back(strrsy +str2);
				else
        			v_disdrawf.push_back(theApp.m_strms[18].strl +"Image\\" +str2);
      			strDate=str3; if(strDate == "") break;
        		m_ishave = strDate.GetLength();
        		strDate = strDate.Mid(m_ishave-3,3);
        		if(strDate =="rsy")
         			v_disdrawf.push_back(strrsy +str3);
				else
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

void CMFClient::SaveFileS3()
{
				m_vdf = 0;    CString strItem,strpo;
				CString strrsy1 ="dispoint"+strMetrics;
               	for ( int i = 0 ; i < 100 ; i++ )
				{
					strItem =theApp.m_RTDM.m_strdfall[theApp.m_RTDM.Initfbl(strMetrics)][i].strl;
                    strpo.Format("UPDATE '%s' SET LP0='%s' WHERE DISID=%d;",
			    	     strrsy1,strItem ,i+200);
	         		theApp.db3.execDML(strpo);
				}
                theApp.m_senddata =true;//更新菜单
}