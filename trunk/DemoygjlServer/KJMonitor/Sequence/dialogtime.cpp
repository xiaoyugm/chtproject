// dialogtime.cpp : implementation file
//

#include "stdafx.h"
#include "..\KJMonitor.h"
#include "dialogtime.h"
//#include "Sequence.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Cdialogtime dialog
extern DAYTIME 	Dytim[100];               //  ÎÞÐëÐÞ¸Ä;

Cdialogtime::Cdialogtime(CWnd* pParent /*=NULL*/)
	: CDialog(Cdialogtime::IDD, pParent)
{
	//{{AFX_DATA_INIT(Cdialogtime)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void Cdialogtime::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(Cdialogtime)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(Cdialogtime, CDialog)
	//{{AFX_MSG_MAP(Cdialogtime)
	ON_BN_CLICKED(IDC_BUTTONSHANGYE, OnButtonshangye)
	ON_BN_CLICKED(IDC_BUTTONXIAYIYE, OnButtonxiayiye)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Cdialogtime message handlers

void Cdialogtime::OnOK() 
{
	// TODO: Add extra validation here
        int i;
        int time;
	    char 	string[4];

	      for (i=0; i<10; i++){
			 time = (int)GetDlgItemInt(IDC_STATIC1+i, NULL, 0)-1;
			 Dytim[time].Hour = GetDlgItemInt(IDC_SHI1+i, NULL, 0);
			 Dytim[time].Minute = GetDlgItemInt(IDC_FENG1+i, NULL, 0);
			 Dytim[time].Month = GetDlgItemInt(IDC_YUE1+i, NULL, 0);
			 Dytim[time].Day = GetDlgItemInt(IDC_RI1+i, NULL, 0);
			 GetDlgItemText(IDC_MEITIAN1+i,string,2);
			 if ((string[0]=='y')||(string[0]=='Y'))
			   Dytim[time].Daily = 'y';
			 else Dytim[time].Daily = 'n';
			 GetDlgItemText(IDC_YOUXIAO1+i,string,2);
			 if ((string[0]=='y')||(string[0]=='Y'))
			   Dytim[time].Active = 'y';
			 else Dytim[time].Active = 'n';
			 Dytim[time].Seqnum = GetDlgItemInt(IDC_SHIXU1+i, NULL, 0);
		   }


	CDialog::OnOK();
}

BOOL Cdialogtime::OnInitDialog()
{
		CDialog::OnInitDialog();
       int i;
  	   TimePage = 0;

	   for (i=0; i<10; i++){
	       SetDlgItemInt(IDC_SHI1+i,Dytim[i].Hour,FALSE);
	       SetDlgItemInt(IDC_FENG1+i,Dytim[i].Minute,FALSE);
	       SetDlgItemInt(IDC_YUE1+i,Dytim[i].Month,FALSE);
	       SetDlgItemInt(IDC_RI1+i,Dytim[i].Day,FALSE);
	       if (Dytim[i].Daily=='y')
		 SetDlgItemText(IDC_MEITIAN1+i,"YES");
	       else
		 SetDlgItemText(IDC_MEITIAN1+i,"NO");
	       if (Dytim[i].Active=='y')
		 SetDlgItemText(IDC_YOUXIAO1+i,"YES");
	       else
                 SetDlgItemText(IDC_YOUXIAO1+i,"NO");
	       SetDlgItemInt(IDC_SHIXU1+i,Dytim[i].Seqnum,FALSE);
	   }
	  GetDlgItem(IDC_BUTTONSHANGYE)-> EnableWindow(FALSE);
	   GetDlgItem(IDC_SHI1)->SetFocus();
	   SendDlgItemMessage(IDC_SHI1,EM_SETSEL,0,MAKELONG(0,0x7fff));
	
	   
	   return TRUE;
  
}





void Cdialogtime::OnButtonshangye() 
{
	// TODO: Add your control notification handler code here
	int time;	   
	    char 	string[4];
		int  firstime;
        int i;
//		int debug;

	   if (TimePage){
		       TimePage--;
				   GetDlgItem(IDC_BUTTONXIAYIYE)->EnableWindow(TRUE);
		       if (!TimePage) 
		       GetDlgItem(IDC_BUTTONSHANGYE)->EnableWindow(FALSE);
		       for (i=0; i<10; i++){//save the current page

			 time = (int)GetDlgItemInt(IDC_STATIC1+i, NULL, 0)-1;
			 Dytim[time].Hour = GetDlgItemInt(IDC_SHI1+i, NULL, 0);	
			 Dytim[time].Minute = GetDlgItemInt(IDC_FENG1+i, NULL, 0);
			 Dytim[time].Month = GetDlgItemInt(IDC_YUE1+i, NULL, 0);
			 Dytim[time].Day = GetDlgItemInt(IDC_RI1+i, NULL, 0);
			 GetDlgItemText(IDC_MEITIAN1+i,string,2);
			 if ((string[0]=='y')||(string[0]=='Y'))
			   Dytim[time].Daily = 'y';
			 else Dytim[time].Daily = 'n';
			 GetDlgItemText(IDC_YOUXIAO1+i,string,2);
			 if ((string[0]=='y')||(string[0]=='Y'))
			   Dytim[time].Active = 'y';
			 else Dytim[time].Active = 'n';
			 Dytim[time].Seqnum = GetDlgItemInt(IDC_SHIXU1+i, NULL, 0);
		       }
		       firstime = 10*TimePage;
		
//		       lastime = firstime+10;
		       for (i=0;i<10;i++){//load the new page
			   SetDlgItemInt(IDC_STATIC1+i,firstime+i+1,FALSE);
	       		   SetDlgItemInt(IDC_SHI1+i,Dytim[firstime+i].Hour,FALSE);
//				   debug=Dytim[firstime+i].Hour;
			   SetDlgItemInt(IDC_FENG1+i,Dytim[firstime+i].Minute,FALSE);
	       		   SetDlgItemInt(IDC_YUE1+i,Dytim[firstime+i].Month,FALSE);
	   		   SetDlgItemInt(IDC_RI1+i,Dytim[firstime+i].Day,FALSE);
	   		   if (Dytim[firstime+i].Daily=='y')
			        SetDlgItemText(IDC_MEITIAN1+i,"YES");
	    		   else
		 		SetDlgItemText(IDC_MEITIAN1+i,"NO");
	       		   if (Dytim[firstime+i].Active=='y')
		 		SetDlgItemText(IDC_YOUXIAO1+i,"YES");
	       		   else
                 		SetDlgItemText(IDC_YOUXIAO1+i,"NO");
	       		   SetDlgItemInt(IDC_SHIXU1+i,Dytim[firstime+i].Seqnum,FALSE);
		       }
                   }
	
}

void Cdialogtime::OnButtonxiayiye() 
{
	// TODO: Add your control notification handler code here
		int time;	   
	    char 	string[4];
		int  firstime;
        int i;
//		int debug;
	if (TimePage<10){
		       TimePage++;
		       GetDlgItem(IDC_BUTTONSHANGYE)->EnableWindow(TRUE);
		       if (TimePage==9) 
				   GetDlgItem(IDC_BUTTONXIAYIYE)->EnableWindow(FALSE);
		       for (i=0; i<10; i++){//save the current paG E
			 time = (int)GetDlgItemInt(IDC_STATIC1+i, NULL, 0)-1;
	

			 Dytim[time].Hour = GetDlgItemInt(IDC_SHI1+i, NULL, 0);
             
	//		 Dytim[0].Hour=10;
			 
	//		 debug=GetDlgItemInt(IDC_SHI1+i, NULL, 0);
			 
			 Dytim[time].Minute = GetDlgItemInt(IDC_FENG1+i, NULL, 0);
			 Dytim[time].Month = GetDlgItemInt(IDC_YUE1+i, NULL, 0);
			 Dytim[time].Day = GetDlgItemInt(IDC_RI1+i, NULL, 0);
			 GetDlgItemText(IDC_MEITIAN1+i,string,2);
			 if ((string[0]=='y')||(string[0]=='Y'))
			   Dytim[time].Daily = 'y';
			 else Dytim[time].Daily = 'n';
			 GetDlgItemText(IDC_YOUXIAO1+i,string,2);
			 if ((string[0]=='y')||(string[0]=='Y'))
			   Dytim[time].Active = 'y';
			 else Dytim[time].Active = 'n';
			 Dytim[time].Seqnum = GetDlgItemInt(IDC_SHIXU1+i, NULL, 0);
		       }
		       firstime = 10*TimePage;
//		       lastime = firstime+10;
		       for (i=0;i<10;i++){//load the new page
			   SetDlgItemInt(IDC_STATIC1+i,firstime+i+1,FALSE);
	       		   SetDlgItemInt(IDC_SHI1+i,Dytim[firstime+i].Hour,FALSE);
			   SetDlgItemInt(IDC_FENG1+i,Dytim[firstime+i].Minute,FALSE);
	       		   SetDlgItemInt(IDC_YUE1+i,Dytim[firstime+i].Month,FALSE);
	   		   SetDlgItemInt(IDC_RI1+i,Dytim[firstime+i].Day,FALSE);
	   		   if (Dytim[firstime+i].Daily=='y')
			        SetDlgItemText(IDC_MEITIAN1+i,"YES");
	    		   else
		 		SetDlgItemText(IDC_MEITIAN1+i,"NO");
	       		   if (Dytim[firstime+i].Active=='y')
		 		SetDlgItemText(IDC_YOUXIAO1+i,"YES");
	       		   else
                 		SetDlgItemText(IDC_YOUXIAO1+i,"NO");
	       		   SetDlgItemInt(IDC_SHIXU1+i,Dytim[firstime+i].Seqnum,FALSE);
		       }
                   }


}



