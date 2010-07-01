// shixuDlg.cpp : implementation file
//

#include "stdafx.h"
//#include "shixu.h"
#include "..\KJMonitor.h"
#include "shixuDlg.h"

#include "SpuEdit.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
extern CDatabase	m_Database;
/////////////////////////////////////////////////////////////////////////////
// CShixuDlg dialog
//extern UINT		FixReg[48];                //需要修改大小
//extern BOOL StartSequence;
//extern void SeqSchedule();

//extern  BOOL time_feg();
  
//extern Cdialogspumonitor dlg_spumonitor;



//extern BOOL InitSequence();
//extern BOOL EndSequence();

CShixuDlg::CShixuDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CShixuDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CShixuDlg)
	m_new_spu = 0;
	m_new_spu2 = 0;
//	m_test = 0;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
//	m_hIcon = AfxGetApp()->LoadIcon(IIDR_MAINFRAME);


}

void CShixuDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CShixuDlg)
	DDX_Control(pDX, IDC_COMBO1, m_list);
	DDX_Text(pDX, IDC_EDIT1, m_new_spu);
	DDV_MinMaxInt(pDX, m_new_spu, 0, 200);
	DDX_Text(pDX, IDC_EDIT2, m_new_spu2);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CShixuDlg, CDialog)
	//{{AFX_MSG_MAP(CShixuDlg)
	ON_WM_DESTROY()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON2, Onaddnew)
	ON_BN_CLICKED(IDC_Modify, OnModify)
	ON_BN_CLICKED(ID_zidong, Onzidong)
	ON_CBN_SELCHANGE(IDC_COMBO1, OnSelchangeCombol)
	ON_BN_CLICKED(IDC_BUTTON1, Ondelete)
//	ON_BN_CLICKED(IDC_BUTTON5, OnButton5)
//	ON_BN_CLICKED(IDC_BUTTON6, OnButton6)
//	ON_BN_CLICKED(IDC_BUTTON7, OnButton7)
//	ON_BN_CLICKED(IDC_BUTTON4, OnButton4)
//	ON_BN_CLICKED(IDC_BUTTON3, OnButton3)
//	ON_WM_TIMER()
//	ON_BN_CLICKED(IDC_BUTTON8, OnButton8)
//	ON_CBN_DROPDOWN(IDC_COMBO1, OnDropdownCombo1)
	ON_BN_CLICKED(IDC_BUTTON_COPY, OnButtonCopy)
	ON_BN_CLICKED(IDC_BUTTON_PASTE, OnButtonPaste)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CShixuDlg message handlers

BOOL CShixuDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
//	SetIcon(m_hIcon, TRUE);			// Set big icon
//	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
/*    if(!m_Database.IsOpen())
	{
   	try
	{
		m_Database.Open(NULL,FALSE,FALSE,_T("ODBC;DSN=masterdefine;UID=kj86;PWD=kj86;"),FALSE);
	}
	catch(CDBException *e)
	{
		AfxMessageBox("Open Database Failed.");
		e->Delete();
	}
    }*/
	spuinform	 = new SpuInform(&m_Database);
	spuinform_copy	 = new SpuInform(&m_Database);

    spudetailed   =new  Spudetailed_me(&m_Database);
    spudetailed_copy   =new  Spudetailed_me(&m_Database);
  
    //add new information

     CString  temp_information;
	 CString  temp_exit;
	 CString  temp_hang;
     CString  temp_com_num;
	 if (!spuinform->IsOpen() )
	 spuinform->Open(CRecordset::dynaset, "Spu_information");
     if(spuinform->IsBOF())
		 return TRUE;
     spuinform->MoveFirst();
	 while(!spuinform->IsEOF())
	 {
	

		 temp_information.Format("时序 %3d",spuinform->m_ID);
       
		 if(spuinform->m_exit_or_empty)
		 {
			 temp_exit="  存在";
			 
          if(spuinform->m_active_hangup)
			  temp_hang="  已经挂起";
		  else  
              temp_hang="  正在使用";
       
		 }
		 else
		 {
             temp_exit="  为空";
			 temp_hang="  不能使用";

		 } 


		  temp_com_num.Format("    指令数为 %4d 优先级 %4d",spuinform->m_num_of_command,spuinform->m_priority);

		  if((spuinform->m_exit_or_empty&&spuinform->m_num_of_command==0)|| 
			  (!spuinform->m_exit_or_empty&&spuinform->m_num_of_command>0))
           
           m_list.AddString(temp_information+"  错误!!!!");
		  else
		 m_list.AddString(temp_information+temp_exit+temp_com_num+temp_hang);

        spuinform->MoveNext();
	 }
       
     spuinform->Close();

     //开启计时器，xuyingtie

  //   SetTimer(unTimerId,1000,NULL);           

	
//	 SetTimer(unTimerIdxu,60000,NULL);     




	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CShixuDlg::OnDestroy()
{
	WinHelp(0L, HELP_QUIT);
	CDialog::OnDestroy();
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.
/*
void CShixuDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}
*/
// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
/*
HCURSOR CShixuDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}
*/
void CShixuDlg::Onaddnew() 
{
	//system query new spu num 
     

	//
		UpdateData(TRUE);
		BOOL exit;

	if (m_new_spu>0)
	{
        spuinform->m_strFilter.Format("ID = %d",m_new_spu);
    	if (!spuinform->IsOpen() )
		    spuinform->Open(CRecordset::dynaset, "Spu_information");
	    else
		     spuinform->Requery();

       	if (!spuinform->IsEOF())
		{
           spuinform->MoveLast();
		   exit=spuinform->m_exit_or_empty;
           spuinform->Close();
           if(!exit)    
		   {
		      
			  CSpuEdit Dlg;
			  Dlg.m_SPU_num=m_new_spu;

			  Dlg.model=0;
			  Dlg.DoModal();
		   }
		   else
	       AfxMessageBox(_T("  SPU  已经存在"));

		}
		else
		{
		AfxMessageBox(_T("你输入的号码已越界"));
		 spuinform->Close();

		}

	}
	else
		AfxMessageBox(_T(" you can not add new SPU"));
	
}

void CShixuDlg::OnModify() 
{
	 UpdateData(TRUE);
     BOOL exit1=0;
	 int prioty_temp;
	 BOOL  hang_up;
	 		

	if (m_new_spu2>0)
	{
		//对m_new_spu2对应的点进行判断
         spuinform->m_strFilter.Format("ID = %d",m_new_spu2);
    	if (!spuinform->IsOpen() )
		    spuinform->Open(CRecordset::dynaset, "Spu_information");
	    else
		     spuinform->Requery();
        
       	if (!spuinform->IsEOF())
		{
           spuinform->MoveLast();
		   exit1=(BOOL)spuinform->m_exit_or_empty;
		   prioty_temp=spuinform->m_priority;
		   hang_up=spuinform->m_active_hangup;
           spuinform->Close();
		   
           if(exit1)
		   {
       	   CSpuEdit Dlg ;
	       Dlg.m_SPU_num=m_new_spu2;
		   Dlg.model=1;
		   Dlg.m_priority=prioty_temp;
		   Dlg.m_hangup=hang_up;
//		Dlg.m_hangup.SetCheck(!hang_up);
//    	Dlg.m_pOwner = this;
		Dlg.DoModal();
		}
		else
         AfxMessageBox(_T(" 输入 SPU不存在"));

		}
		else          
			spuinform->Close();
					


		//
	}
	else
		AfxMessageBox(_T(" you can not modify the SPU"));
	
}

void CShixuDlg::Onzidong() 
{
	// TODO: Add your control notification handler code here
//    	int i;
	 if (!spuinform->IsOpen() )
	 {
		spuinform->m_strFilter.Empty();

		   	    if (!spuinform->IsOpen() )			
			   {	 
				   spuinform->Open(CRecordset::dynaset  );
			   }
			   else      
				   spuinform->Requery();
	 }
	 if(!spuinform->IsEOF())
	 {		
		 spuinform->MoveFirst();
	 }
    	
	 while (!spuinform->IsEOF())
		
	 {
			
            if(!spuinform->m_exit_or_empty)
			{
				m_new_spu=spuinform->m_ID;
               	UpdateData(FALSE);
				break;

			}
	  TRACE(" query");
       spuinform->MoveNext();
          		
	 }
  
      if (spuinform->IsOpen() )
	   spuinform->Close();
     
}



void CShixuDlg::OnSelchangeCombol() 
{
	// TODO: Add your control notification handler code here
	int ii;
	ii=m_list.GetCurSel();

        spuinform->m_strFilter.Format("ID = %d",ii+1);
    	if (!spuinform->IsOpen() )
		    spuinform->Open(CRecordset::dynaset, "Spu_information");
	    else
		     spuinform->Requery();
		
		if(!spuinform->IsEOF())
		{
          spuinform->MoveLast();
		  if(spuinform->m_exit_or_empty)
		  {m_new_spu2=ii+1;
           m_new_spu=0;
            GetDlgItem(IDC_BUTTON_COPY)->EnableWindow(TRUE);
		  }
		  else
		  {
		   m_new_spu=ii+1;
           m_new_spu2=0;
		   GetDlgItem(IDC_BUTTON_COPY)->EnableWindow(FALSE);

		  }
		   UpdateData(FALSE);

		}  
     
         spuinform->Close();

}
CShixuDlg::~CShixuDlg()
{
   delete spuinform;
   delete spudetailed;
   delete spudetailed_copy;
   delete spuinform_copy;
}
void CShixuDlg::Ondelete() 
{
	// TODO: Add your control notification handler code here
     	BOOL exit1;
     	UpdateData(TRUE); 
    if (m_new_spu2>0)
    {
	  if(AfxMessageBox(" 真的删除此时序",MB_OKCANCEL )==IDOK)
	  {
        spuinform->m_strFilter.Format("ID = %d",m_new_spu2);
    	if (!spuinform->IsOpen() )
		    spuinform->Open(CRecordset::dynaset, "Spu_information");
	    else
		    spuinform->Requery();

		if(!spuinform->IsEOF())
		{  //if(!spuinform->IsEOF())  kaishi
			spuinform->MoveLast();
		    exit1=(BOOL)spuinform->m_exit_or_empty;
            if(exit1)
			{
			//修改spuinform表中数据开始
				try
				{
              		spuinform->Edit();
                    spuinform-> m_active_hangup=FALSE;
                    spuinform->m_exit_or_empty=FALSE;
                    spuinform->m_num_of_command=0;
                    spuinform->m_priority=0;
                   	 spuinform->Update();
				}
				catch(CException *e)
				{
					delete spuinform;
					e->Delete();
				}
				//修改spuinform表中数据结束
       
		    
				//删除spudetailed表中相应的数据
				spudetailed->m_strFilter.Format("spu_num = %d",m_new_spu2);
				if (!spudetailed->IsOpen() )
				{	 
					spudetailed->Open(CRecordset::dynaset  );
				}
				else
					spudetailed->Requery();
				if(!spudetailed->IsEOF())
				{
					spudetailed->MoveFirst();
					m_Database.BeginTrans();
					while(!spudetailed->IsEOF())
					{    
						try
						{
							spudetailed->Delete();
						}
						catch(CException *e)
						{
							delete spudetailed;
							e->Delete();	
						}
						spudetailed->MoveNext();
					}   //wile jieshu
					m_Database.CommitTrans();;
				}  
				//          if(!spudetailed->IsEOF())  jishu
				//删除spudetailed表中相应的数据

                
                m_list.DeleteString(m_new_spu2-1);
				CString  str1;
				str1.Format("时序 %3d  已经删除  ",m_new_spu2);
                m_list.InsertString(m_new_spu2-1,str1);
                   

			}
			else
				MessageBox("你所删除的时序已不存在");
			//    if(exit1)     结束
		}//ifjieshu
	  }
	}
}

void CShixuDlg::OnOK() 
{
	// TODO: Add extra validation here
	
	CDialog::OnOK();
}



//void CShixuDlg::OnDropdownCombo1() 
//{
	// TODO: Add your control notification handler code here
	
//}

void CShixuDlg::OnButtonCopy() 
{
	// TODO: Add your control notification handler code here
    copy_index=m_list.GetCurSel();

	GetDlgItem(IDC_BUTTON_PASTE)->EnableWindow(TRUE);
}

void CShixuDlg::OnButtonPaste() 
{
	// TODO: Add your control notification handler code here
	//  
	int ii=m_list.GetCurSel();
    if(ii==copy_index)
		return ;
   


            spuinform->m_strFilter.Format("ID = %d",ii+1);
    	if (!spuinform->IsOpen() )
		    spuinform->Open(CRecordset::dynaset, "Spu_information");
	    else
		     spuinform->Requery();
		
		if(!spuinform->IsEOF())
		{
          spuinform->MoveLast();
		  if(spuinform->m_exit_or_empty)
		  {
			  
			  MessageBox("对于一个已经存在的时序不能覆盖");
			  return;
		  }
		  else
		  {
			  //取得原来的信息

          spuinform_copy->m_strFilter.Format("ID = %d",copy_index+1);
    	  if (!spuinform_copy->IsOpen() )
		    spuinform_copy->Open(CRecordset::snapshot, "Spu_information");
	      else
		     spuinform_copy->Requery();


		  if(!spuinform_copy->IsEOF())
		  {
			  spuinform_copy->MoveLast();
             			try
						{
              		      spuinform->Edit();
                          spuinform-> m_active_hangup=spuinform_copy-> m_active_hangup;
                          spuinform->m_exit_or_empty=spuinform_copy->m_exit_or_empty;
                          spuinform->m_num_of_command=spuinform_copy->m_num_of_command;
                          spuinform->m_priority=spuinform_copy->m_priority;
                   	       spuinform->Update();					
						}
						catch(CException *e)
						{
							delete spudetailed;
							e->Delete();	
						}
               

		  }
          spuinform_copy->Close();
               
		  //主要数据库更新

		       if (!spudetailed->IsOpen() )
				{	 
					spudetailed->Open(CRecordset::dynaset  );
				}
				else
					spudetailed->Requery();
              

              spudetailed_copy->m_strFilter.Format("spu_num = %d",copy_index+1);
		       if (!spudetailed_copy->IsOpen() )
				{	 
					spudetailed_copy->Open(CRecordset::snapshot  );
				}
				else
					spudetailed_copy->Requery();

				if(!spudetailed_copy->IsBOF())
                     spudetailed_copy->MoveFirst();    
 
                 while(!spudetailed_copy->IsEOF())
				 {
					 		try
				
							{
                             spudetailed->AddNew();
                             spudetailed->m_spu_num = ii+1 ;
	                         spudetailed->m_step_num = spudetailed_copy->m_step_num ;
	                         spudetailed->m_command_index = spudetailed_copy->m_command_index;
               	             spudetailed->m_para1 = spudetailed_copy->m_para1;
	                         spudetailed->m_para2 = spudetailed_copy->m_para2;
	                         spudetailed->m_para3 = spudetailed_copy->m_para3;
	                         spudetailed->m_para4 = spudetailed_copy->m_para4;
            	              spudetailed->Update();

							}
	
	                       catch(CDBException *e)
						   {
				        	e->Delete();
			
						   }	
    
					 



                    spudetailed_copy->MoveNext();

				 }

				 spudetailed->Close();
                 spudetailed_copy->Close();
           //更新显示
                m_list.DeleteString(ii);
				CString  str1;
				str1.Format("时序 %3d  已经被时序%3d复制 请修改 ",(ii+1),(copy_index+1));
                m_list.InsertString(ii,str1);




               

		  }

		}  
     
         spuinform->Close();
    
    
}
