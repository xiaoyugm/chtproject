// FormDraw.cpp : implementation file
//

#include "stdafx.h"
#include "gui_visualstudio.h"
#include "FormDraw.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFormDraw dialog


CFormDraw::CFormDraw(CWnd* pParent /*=NULL*/)
	: CDialog(CFormDraw::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFormDraw)
	//}}AFX_DATA_INIT
	m_dorf =0;
}


void CFormDraw::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFormDraw)
		  DDX_Text(pDX, IDC_EDITFORM, strsm);
	DDV_MaxChars(pDX, strsm, 20);
		  DDX_Control(pDX, IDC_CBDRAW, m_ComDraw);
	DDX_Control(pDX, IDC_LCFD, m_LCFD);
	DDX_Control(pDX, IDC_LCFDA, m_LCFDA);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CFormDraw, CDialog)
	//{{AFX_MSG_MAP(CFormDraw)
	ON_BN_CLICKED(IDC_BEXCELADD, OnBES)
	ON_BN_CLICKED(IDCANCELEXCEL, OnBED)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFormDraw message handlers

BOOL CFormDraw::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_LCFD.ModifyExtendedStyle(0, LVS_EX_FULLROWSELECT|LVS_SHOWSELALWAYS | LVS_EX_GRIDLINES);
	m_LCFDA.ModifyExtendedStyle(0, LVS_EX_FULLROWSELECT|LVS_SHOWSELALWAYS | LVS_EX_GRIDLINES);

	CString strrsy ,strclm;
	int m_ishave=0;
	int i1=0;
	int i2=0;
    strclm = strMetrics+ ("rsy\\待显示文件");
	m_LCFD.InsertColumn(0,strclm,LVCFMT_LEFT,300);
	m_LCFDA.InsertColumn(0,"需要打开文件",LVCFMT_LEFT,300);

	strrsy = gstrTimeOut + "\\" + strMetrics+ "rsy\\";
		SetWindowText("设置数据显示页");

//	for ( int m = 0 ; m < 2 ; m++ )
	{
     	if (!m_sdir.SetInitDir(strrsy))
		{//\r\n--------------------\r\n
        AfxMessageBox("目录不存在!", MB_OK);
		return 0;
		}
    	m_sdir.m_nFileCount = 0;
    	m_sdir.m_nSubdirCount = 0;
//     	if(m == 0)
         	m_sdir.BeginBrowse("*.rsf");
//      	else if(m ==1)
//         	m_sdir.BeginBrowse("*.rsy");

//                m_LCFD.InsertItem(i1, strclm);
//    			i1++;
/*     		for ( int k = 0 ; k < theApp.m_addfilesy.size() ; k++ )
			{
				strclm = theApp.m_addfilesy[k];
    			strclm.Replace(strrsy,"");
                m_LCFDA.InsertItem(k, strclm);
			}*/
	}
   	if(m_dorf == 2)
	{
      		    GetDlgItem(IDCANCELEXCEL)->ShowWindow(SW_HIDE);;
    		  GetDlgItem(IDC_CBDRAW)->ShowWindow(SW_HIDE);;
		 GetDlgItem(IDC_BEXCELADD)->SetWindowText("改名");
	}
	else if(m_dorf == 1)
    	L2upDB();

//	m_LCFD.InsertItem(0, _T("hhh"), 0);
//	GetDlgItemText(IDC_EDIT_DIR,dirName,100);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CFormDraw::OnBES() 
{
	CString strrsy ,strclm,strclm1;
    CString strSQL,strSQL1,strrsy1;
	strrsy = gstrTimeOut + "\\" + strMetrics+ "rsy\\";
	strrsy1 ="dispoint"+strMetrics;

	int n_is=0;
	UpdateData(TRUE);           //Exchange dialog data
	if(strsm == "")
	{
        AfxMessageBox("请输入文件名！");
		return;
	}
	strclm = strrsy +_T( "实时数据.rsf");
	strclm1 = strrsy + strsm +_T( ".rsf");
	for(int i=0;i<theApp.m_addfilesy.size();i++)
	{
		strSQL1 = theApp.m_addfilesy[i];
		if(strSQL1 == strclm1)
		{
           AfxMessageBox("文件名重复，请重新输入！");
		   n_is =100;
		   break;
		}
	}
	if(n_is == 100)
		return;
	CopyFile(strclm,strclm1,FALSE);//FALSE表示D:\copy.txt要是存在就覆盖,看返回值
	CppSQLite3Query q;
   	if(m_dorf == 2)
	{
		DeleteFile(strrsy + m_result);
	    	strSQL.Format("select * from '%s' WHERE DISID=1;",strrsy1);
            q = theApp.db3.execQuery(strSQL);
        for(int k =2; k < 21 ;k++)//替换原文件在dispoint中第一行的信息
		{
            strclm = q.getStringField(k);
			strclm.TrimRight();
			if(strclm == m_result)
			{
	    		strSQL1.Format("LP%d",k-1);
				strSQL.Format("UPDATE '%s' SET '%s'='%s' WHERE DISID =1;",
					strrsy1,strSQL1,strsm +_T( ".rsf"));
                q = theApp.db3.execQuery(strSQL);
				break;
			}
		}
			strclm1.Format("select * from '%s' WHERE DISID<100;",strrsy1);
            q = theApp.db3.execQuery(strclm1); 
            while (!q.eof())//替换原文件在dispoint中第一列的信息
			{
				n_is = q.getIntField(0);
                strclm = q.getStringField(1);
	    		strclm.TrimRight();
	      		if(strclm == strrsy + m_result)
				{
			    	strSQL.Format("UPDATE '%s' SET LP0='%s' WHERE DISID =%d;",
			     		strrsy1,strrsy +strsm +_T( ".rsf"),n_is);
                    q = theApp.db3.execQuery(strSQL);
			    	break;
				}
                q.nextRow();
			}
	}
	else if(m_dorf == 1)
	{
		n_is =0;
	    	strSQL.Format("select * from '%s' WHERE DISID=1;",strrsy1);
            q = theApp.db3.execQuery(strSQL);
        for(int k =2; k < 21 ;k++)//在dispoint中第一行的信息中寻找同名文件位置
		{
            strclm = q.getStringField(k);
			strclm.TrimRight();
			if(strclm == strsm +_T( ".rsf"))
			{
				n_is = 11;
				break;
			}
		}
		if(n_is != 11)
		{
            for(int k =2; k < 21 ;k++)//在dispoint中第一行的信息中寻找空的位置
			{
                strclm = q.getStringField(k);
		    	strclm.TrimRight();
	    		if(strclm == "")
				{
	    			n_is = 1;
	    		strSQL1.Format("LP%d",k-1);
				strSQL.Format("UPDATE '%s' SET '%s'='%s' WHERE DISID =1;",
					strrsy1,strSQL1,strsm +_T( ".rsf"));
                q = theApp.db3.execQuery(strSQL);
		    		break;
				}
			}
		}
		if(n_is == 0)
           AfxMessageBox("请删除" +strrsy +"目录下无用的*.rsf文件，重新输入！");

    	int nItem = theApp.m_addfilesy.size()+1;
				strSQL.Format("UPDATE '%s' SET LP0='%s' WHERE DISID=%d;",
					strrsy1,strclm1,nItem);
             q = theApp.db3.execQuery(strSQL);
	}
		q.finalize();

	theApp.DocNum = 1;
	theApp.InitSQLite3();
	theApp.m_RTDM.InitDisplay();

/*	BOOL bExist;
	int nItemCount=m_LCFD.GetItemCount();
    for(int nItem=0;nItem<nItemCount;nItem++)
	{
		if(m_LCFD.GetItemState(nItem,LVIS_SELECTED) & LVIS_SELECTED)
		{
			CString strP1=m_LCFD.GetItemText(nItem,0);
			int nItemCount1=m_LCFDA.GetItemCount();
			bExist=FALSE;
			for(int j=0; j<nItemCount1; j++)
			{
				if(strP1==m_LCFDA.GetItemText(j,0))
				{
					bExist=TRUE;
					break;
				}
			}
			if(!bExist)
			{
    			m_LCFD.DeleteItem(nItem);
				m_LCFDA.InsertItem(nItemCount1, strP1);
			}
		}
	}*/
}

void CFormDraw::OnBED() 
{
	CString strrsy ,strclm,strclm1;
    CString strSQL,strSQL1,strrsy1;
	strrsy = gstrTimeOut + "\\" + strMetrics+ "rsy\\";
	strrsy1 ="dispoint"+strMetrics;
		CppSQLite3Query q;

	int m_ishave=0;
	UpdateData(TRUE);           //Exchange dialog data

	CString strname;
	int  kkkk = m_ComDraw.GetCurSel();
	if(kkkk == -1)
	{
        AfxMessageBox("请选择数据显示页！");
		return;
	}
	m_ComDraw.GetLBText(kkkk,strname);
	strclm1 = strrsy+strname;
		for ( int i = 0 ; i < m_sdir.m_dirs.size() ; i++ )
		{
			strclm = m_sdir.m_dirs[i];
				if(strclm == strclm1)
				{
					m_ishave =100;
					break;
				}
				else
					m_ishave =0;
		}
			if(m_ishave ==0)
			{
        AfxMessageBox("请选择数据显示页！");
		return;
			}

	int nItem = theApp.m_addfilesy.size()+1;
				strSQL.Format("UPDATE '%s' SET LP0='%s' WHERE DISID = %d;",
					strrsy1,strclm1,nItem);
             q = theApp.db3.execQuery(strSQL);

	    	strSQL.Format("select * from '%s' WHERE DISID=1;",strrsy1);
            q = theApp.db3.execQuery(strSQL);
            for(int k =2; k < 21 ;k++)//在dispoint中第一行的信息中寻找空的位置
			{
                strclm = q.getStringField(k);
		    	strclm.TrimRight();
	    		if(strclm == "")
				{
				strSQL.Format("UPDATE '%s' SET LP%d='%s' WHERE DISID =1;",
					strrsy1,k-1,strname);
                q = theApp.db3.execQuery(strSQL);
		    		break;
				}
			}

		q.finalize();

			theApp.DocNum = 1;
			theApp.InitSQLite3();
	theApp.m_RTDM.InitDisplay();

	L2upDB();

/*	int nItemCount1=m_LCFD.GetItemCount();
	int nItemCount=m_LCFDA.GetItemCount();
    for(int nItem=nItemCount-1;nItem>=0;nItem--)
	{
		if(m_LCFDA.GetItemState(nItem,LVIS_SELECTED) & LVIS_SELECTED)
		{
			CString strP1=m_LCFDA.GetItemText(nItem,0);
				m_LCFD.InsertItem(nItemCount1, strP1);
			m_LCFDA.DeleteItem(nItem);
		}
	}*/
}

void CFormDraw::L2upDB() 
{
	CString strclm,strrsy;
	strrsy = gstrTimeOut + "\\" + strMetrics+ "rsy\\";
				m_ComDraw.ResetContent();
	 int m_ishave=0;
		for (int  i = 0 ; i < m_sdir.m_dirs.size() ; i++ )
		{
			strclm = m_sdir.m_dirs[i];
     		for ( int k = 0 ; k < theApp.m_addfilesy.size() ; k++ )
			{
				if(strclm == theApp.m_addfilesy[k])
				{
					m_ishave =100;
					break;
				}
				else
					m_ishave =0;
			}
    			strclm.Replace(strrsy,"");
			if(m_ishave ==0)
				m_ComDraw.AddString(strclm);
		}
		m_ComDraw.SetCurSel(0);

}

void CFormDraw::OnOK() 
{
	
	CDialog::OnOK();
}

void CFormDraw::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}
