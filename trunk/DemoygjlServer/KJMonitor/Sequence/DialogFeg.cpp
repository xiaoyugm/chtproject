// DialogFeg.cpp : implementation file
//

#include "stdafx.h"
#include "..\KJMonitor.h"
#include "DialogFeg.h"
#include "..\MonitorPointThread.h"
//#include  "Sequence.h "
//#include "dialogspumonitor.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDialogFeg dialog

TRIG FAR TrigSeq[100];  //100 11/1
//extern aValue  lpPointValue[MAX_POINT_NUMBER];  


CDialogFeg::CDialogFeg(CWnd* pParent /*=NULL*/)
	: CDialog(CDialogFeg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDialogFeg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDialogFeg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDialogFeg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDialogFeg, CDialog)
	//{{AFX_MSG_MAP(CDialogFeg)
	ON_BN_CLICKED(IDB_PGDN, OnPgdn)
	ON_BN_CLICKED(IDB_PGUP, OnPgup)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDialogFeg message handlers


BOOL CDialogFeg::OnInitDialog()
{
	 CDialog::OnInitDialog();
	 //test
       int i;
	   TrigPage = 0;
	   for (i=0; i<10; i++)
	   {
	       SetDlgItemInt(IDE_PT1+i,TrigSeq[i].Point,FALSE);
	       SetDlgItemInt(IDE_SEQ1+i,TrigSeq[i].Seq,FALSE);
	       SetDlgItemInt(IDE_CON1+i,(UINT)TrigSeq[i].Condition,FALSE);
	   }
  	   GetDlgItem(IDB_PGUP)-> EnableWindow(FALSE);
	   GetDlgItem(IDE_PT1)->SetFocus();
	   SendDlgItemMessage(IDE_PT1,EM_SETSEL,0,MAKELONG(0,0x7fff));

	   return TRUE;
}

void CDialogFeg::OnPgdn() 
{
	// TODO: Add your control notification handler code here
	   int i;
	   int trig;
	   int firsttrig;
	if (TrigPage<10)
	{
	   TrigPage++;
	   GetDlgItem(IDB_PGUP)->EnableWindow(TRUE);
	   if (TrigPage==9) 
		   GetDlgItem(IDB_PGDN)->EnableWindow(FALSE);
	   for (i=0; i<10; i++)
	   {//save the current page
		         trig = (int)GetDlgItemInt(IDS1+i, NULL, 0)-1;
		         TrigSeq[trig].Point = (int)GetDlgItemInt(IDE_PT1+i, NULL, 0);
		         TrigSeq[trig].Seq = (int)GetDlgItemInt(IDE_SEQ1+i, NULL, 0);
			     TrigSeq[trig].Condition = (int)GetDlgItemInt(IDE_CON1+i, NULL, 0);
                 TrigSeq[trig].PntStat = 0x00;  //lpPointValue[TrigSeq[trig].Point].Pstate; 
	   }
	   firsttrig = 10*TrigPage;
//                       lasttrig = firsttrig+10;
	   for (i=0;i<10;i++)
	   {//load the new page
               SetDlgItemInt(IDS1+i,firsttrig+i+1,FALSE);
			   SetDlgItemInt(IDE_PT1+i,TrigSeq[firsttrig+i].Point,FALSE);
	       	   SetDlgItemInt(IDE_SEQ1+i,TrigSeq[firsttrig+i].Seq,FALSE);
			   SetDlgItemInt(IDE_CON1+i,(UINT)TrigSeq[firsttrig+i].Condition,FALSE);
	   }
	}
}

void CDialogFeg::OnPgup() 
{
	// TODO: Add your control notification handler code here
	int i;
	int trig;
	int firsttrig;

	if (TrigPage)
	{
	    TrigPage--;
		GetDlgItem(IDB_PGDN)->EnableWindow(TRUE);
		if (!TrigPage) 
		    GetDlgItem(IDB_PGUP)->EnableWindow(FALSE);  
			   //如果为0，向上翻转不动
		for (i=0; i<10; i++)
		{//save the current page
		     trig = (int)GetDlgItemInt(IDS1+i, NULL, 0)-1;          
				 //返回触发时序数组号
		     TrigSeq[trig].Point = (int)GetDlgItemInt(IDE_PT1+i, NULL, 0);
		     TrigSeq[trig].Seq = (int)GetDlgItemInt(IDE_SEQ1+i, NULL, 0);
			 TrigSeq[trig].Condition = (int)GetDlgItemInt(IDE_CON1+i, NULL, 0);
			 TrigSeq[trig].PntStat = 0x00;   ///lpPointValue[TrigSeq[trig].Point].Pstate; 
		}
		firsttrig = 10*TrigPage;
//                       lasttrig = firsttrig+10;
		for (i=0;i<10;i++)
		{//load the new page
			 SetDlgItemInt(IDS1+i,firsttrig+i+1,FALSE);
			 SetDlgItemInt(IDE_PT1+i,TrigSeq[firsttrig+i].Point,FALSE);
	       	 SetDlgItemInt(IDE_SEQ1+i,TrigSeq[firsttrig+i].Seq,FALSE);
	       	 SetDlgItemInt(IDE_CON1+i,(UINT)TrigSeq[firsttrig+i].Condition,FALSE);
		}
	}
}

void CDialogFeg::OnOK() 
{
            int i;
			int trig;
//			BYTE debug;
	for (i=0; i<10; i++)
	{
		 trig = (int)GetDlgItemInt(IDS1+i, NULL, 0)-1;
		 TrigSeq[trig].Point = (int)GetDlgItemInt(IDE_PT1+i, NULL, 0);
//		 debug=TrigSeq[trig].Point;
		 TrigSeq[trig].Seq = (int)GetDlgItemInt(IDE_SEQ1+i, NULL, 0);
		 TrigSeq[trig].Condition = (int)GetDlgItemInt(IDE_CON1+i, NULL, 0);
		     
		 TrigSeq[trig].PntStat =0x00;     //lpPointValue[TrigSeq[trig].Point].Pstate;  
	}
	CDialog::OnOK();
}
