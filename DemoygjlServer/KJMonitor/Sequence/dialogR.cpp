// dialogR.cpp : implementation file
//

#include "stdafx.h"
#include "..\KJMonitor.h"
#include "dialogR.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern UINT		FixReg[48];                //需要修改大小

/////////////////////////////////////////////////////////////////////////////
// CdialogR dialog


CdialogR::CdialogR(CWnd* pParent /*=NULL*/)
	: CDialog(CdialogR::IDD, pParent)
{
	//{{AFX_DATA_INIT(CdialogR)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CdialogR::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CdialogR)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CdialogR, CDialog)
	    //{{AFX_MSG_MAP(CdialogR)
		// NOTE: the ClassWizard will add message map macros here

		//}}AFX_MSG_MAP


	ON_WM_TIMER()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CdialogR message handlers

BOOL CdialogR::OnInitDialog()
{
   	CDialog::OnInitDialog();
     char  	FText[32];
  int		i, j;
    for (i=IDM_REG33,j=0; i<=IDM_REG80; i++,j++)
	{
			   sprintf(FText,"%u ",FixReg[j]);
			   SetDlgItemText(i,FText);
		   
	}
//	 SetTimer(unTimerId_R,500,NULL);           

		  return(TRUE);
    
    
}



void CdialogR::OnTimer(UINT nIDEvent) 
{
  char  	FText[32];
  int		i, j;
    for (i=IDM_REG33,j=0; i<=IDM_REG80; i++,j++)
	{
			   sprintf(FText,"%u ",FixReg[j]);
			   SetDlgItemText(i,FText);
		   
	}


}