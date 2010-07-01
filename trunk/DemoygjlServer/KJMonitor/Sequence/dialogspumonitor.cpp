// dialogspumonitor.cpp : implementation file
//

#include "stdafx.h"
#include "..\KJMonitor.h"
#include "dialogspumonitor.h"
//#include "Sequence.h"
#include "SpuInform.h"
#include  "Spudetailed_me.h"
//#include <io.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include "..\MonitorPointThread.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Cdialogspumonitor dialog

//extern HANDLE hCommandList[201];
extern BOOL 		SeqFlag[SEQNUM];
extern WORD		ExecSeq[SEQNUM];	
extern NSEQ FAR 	SSeq[201];       //时序号,运行结构             //需要
extern SEQSTACK	Sequence[SEQNUM];         //修改  需要修改,  根据一个时序是否要调用别的时序

//extern void InsertSeq(int seqnum);

Cdialogspumonitor::Cdialogspumonitor(CWnd* pParent /*=NULL*/)
	: CDialog(Cdialogspumonitor::IDD, pParent)
{
	//{{AFX_DATA_INIT(Cdialogspumonitor)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

void Cdialogspumonitor::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Cdialogspumonitor)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(Cdialogspumonitor, CDialog)
	//{{AFX_MSG_MAP(Cdialogspumonitor)
	ON_BN_CLICKED(IDM_SA_START, OnSaStart)
	ON_BN_CLICKED(IDM_SA_ABORT, OnSaAbort)
	ON_BN_CLICKED(IDOK1, OnOk1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Cdialogspumonitor message handlers

BOOL Cdialogspumonitor::OnInitDialog()
{
	int k;
	CDialog::OnInitDialog();
    id_star=1;
			for (k=0; k<SEQNUM; k++)	
			{
				if (SeqFlag[k])
					sprintf(SeqText," %-3d  运行",  ExecSeq[k]);
				else
					sprintf(SeqText," %-3d  停止", ExecSeq[k]);  // 
				SetDlgItemText(IDM_SA_SQ1+k,SeqText);
			}
			SendDlgItemMessage(IDM_SA_START,EM_SETSEL,NULL,MAKELONG(0,0x7fff));
			GetDlgItem(IDM_SA_START)->SetFocus();

	return TRUE;
}

void Cdialogspumonitor::OnSaStart() 
{
	// TODO: Add your control notification handler code here

	        strcpy(S1Text,"输入启动时序号码 :");
			SetDlgItemText(IBM_SA_NUMBER,S1Text);
			id_star=1;
			GetDlgItem(IDM_SA_NUMBER)->SetFocus();
			SendDlgItemMessage(IDM_SA_NUMBER,EM_SETSEL,0,MAKELONG(0,0x7fff));
            GetDlgItem(IDOK1)->EnableWindow(TRUE);
}

void Cdialogspumonitor::OnSaAbort() 
{
			strcpy(S1Text,"输入终止时序号 :");
			SetDlgItemText(IBM_SA_NUMBER,S1Text);
			id_star=2;
			GetDlgItem(IDM_SA_NUMBER)->SetFocus();
			SendDlgItemMessage(IDM_SA_NUMBER,EM_SETSEL,0,MAKELONG(0,0x7fff));
			GetDlgItem(IDOK1)->EnableWindow(TRUE);
}

void Cdialogspumonitor::OnOk1() 
{
	// TODO: Add your control notification handler code here
	CKJMonitorApp* pApp=(CKJMonitorApp* )AfxGetApp();
//	pApp->pMPT->RefreshPoint(iTrunk);
	   int i;
	   st_Seqnumber=(int)GetDlgItemInt(IDM_SA_NUMBER,NULL,0); /* "OK" box selected? */

	        if ((st_Seqnumber>200)||(st_Seqnumber==0))	
			{
				GetDlgItem(IDM_SA_NUMBER)->SetFocus();
				SendDlgItemMessage(IDM_SA_NUMBER,EM_SETSEL,0,MAKELONG(0,0x7fff));
//				break;
				return;
			}
			if (SSeq[st_Seqnumber].SPUnum<=0) 
			{
                if (id_star==1) 
				{ 			// Start a sequence
 				    strcpy(S1Text,"时序未定,请重新输入启动时序号");
				    SetDlgItemText(IBM_SA_NUMBER,S1Text);
				    SetDlgItemInt(IDM_SA_NUMBER,NULL);
//				    GetDlgItem(IDM_SA_EXIT)->SetFocus();
				}
				else if(id_star==2)
				{			
				     strcpy(S1Text,"时序未定,请重新输入停止时序号");
				     SetDlgItemText(IBM_SA_NUMBER,S1Text);
			      	 SetDlgItemInt(IDM_SA_NUMBER,NULL);
				}
			}

			if(SSeq[st_Seqnumber].SPUnum>0 && SSeq[st_Seqnumber].SPUnum<=200)
			{
			  if (id_star==1) 
			  { 			// Start a sequence
				   pApp->pMPT->InsertSeq(st_Seqnumber);  //人工启动时序   
//				   SetFocus(GetDlgItem(hDlg,IDM_SA_EXIT));
			       GetDlgItem(IDOK1)->EnableWindow(FALSE);
			  }  
		 	  else if (id_star==2)					// Abort a sequence
			  {
//				SetFocus(GetDlgItem(hDlg,IDM_SA_EXIT));
				    for (i=0; i<SEQNUM; i++)
					if ((Sequence[i].ptr>0)&&(ExecSeq[i] == st_Seqnumber))	
					    break;//寻找合适的i  
			        if (i >= SEQNUM)  
					{
					    strcpy(S1Text,"此时序没有运行,请重输");
					    SetDlgItemText(IBM_SA_NUMBER,S1Text);
					    GetDlgItem(IDM_SA_ABORT)->SetFocus();
					}
			        else 
					{
					   Sequence[i].ptr = 0;
				       GetDlgItem(IDOK1)->EnableWindow(FALSE);
					}
			  }
			}
}









  






