// SpuEdit.cpp : implementation file
#include "stdafx.h"
#include "..\KJMonitor.h"
#include "SpuEdit.h"
#include "shixuDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CDatabase	m_Database;

//extern LPSTR GetDes(int ,int  );//返回模式号的描述    
//extern int chartoint(char *);
/////////////////////////////////////////////////////////////////////////////
// CSpuEdit dialog

CSpuEdit::CSpuEdit(CWnd* pParent /*=NULL*/)
	: CDialog(CSpuEdit::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSpuEdit)
	m_hangup = FALSE;
	m_SPU_num = 0;
	m_priority = 0;
	m_para2 = _T("");
	m_para1 = _T("");
	m_para3 = _T("");
	m_para4 = _T("");
	m_com_num = 0;
	m_step = 1;
	//}}AFX_DATA_INIT
}

void CSpuEdit::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSpuEdit)
	DDX_Control(pDX, IDC_COMBO1, m_com);
	DDX_Control(pDX, IIDC_LIST1, m_list);
	DDX_Check(pDX, IDC_CHECK1, m_hangup);
	DDX_Text(pDX, IDC_EDIT_SPU, m_SPU_num);
	DDV_MinMaxInt(pDX, m_SPU_num, 0, 200);
	DDX_Text(pDX, IDC_EDIT_PRIORITY, m_priority);
	DDV_MinMaxInt(pDX, m_priority, 0, 999);
	DDX_Text(pDX, ID_EDITPARA2, m_para2);
	DDX_Text(pDX, IDC_EDIT_PA1, m_para1);
	DDX_Text(pDX, IDC_EDIT_PA3, m_para3);
	DDX_Text(pDX, IDC_EDIT_PARA4, m_para4);
	DDX_Text(pDX, IDC_EDIT_COMMAND, m_com_num);
	DDV_MinMaxInt(pDX, m_com_num, 0, 100);
	DDX_Text(pDX, IDC_EDIT_STEP, m_step);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CSpuEdit, CDialog)
	//{{AFX_MSG_MAP(CSpuEdit)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_INSERT, OnInsert)
	ON_LBN_SELCHANGE(IIDC_LIST1, OnSelchangeList1)
	ON_BN_DOUBLECLICKED(IDC_INSERT, OnDoubleclickedInsert)
	ON_BN_CLICKED(IDC_EMPTY, OnEmpty)
	ON_BN_CLICKED(ID_xiug, Onxiug)
	ON_EN_KILLFOCUS(IDC_EDIT_COMMAND, OnKillfocusEditCommand)
	ON_LBN_DBLCLK(IIDC_LIST1, OnDblclkList1)
	ON_EN_CHANGE(IDC_EDIT_COMMAND, OnChangeEditCommand)
	ON_BN_CLICKED(IDC_CHECK1, OnCheck1)
	ON_EN_CHANGE(IDC_EDIT_PRIORITY, OnChangeEditPriority)
	ON_EN_KILLFOCUS(IDC_EDIT_PA1, OnKillfocusEditPa1)
	ON_EN_KILLFOCUS(IDC_EDIT_PA3, OnKillfocusEditPa3)
	ON_EN_KILLFOCUS(IDC_EDIT_PARA4, OnKillfocusEditPara4)
	ON_EN_KILLFOCUS(ID_EDITPARA2, OnKillfocusEditpara2)
	ON_BN_CLICKED(IDC_BUTTON_HELP, OnButtonHelp)
	ON_BN_CLICKED(IDC_BUTTON_KONG, OnButtonKong)
	ON_BN_CLICKED(IDC_BUTTON_DEL, OnButtonDel)
	ON_CBN_SELCHANGE(IDC_COMBO1, OnSelchangeCombo1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSpuEdit message handlers

BOOL CSpuEdit::OnInitDialog()
{
	CDialog::OnInitDialog();
	CKJMonitorApp* pApp=(CKJMonitorApp* )AfxGetApp();
//	pApp->pMPT->RefreshPoint(iTrunk);
	UpdateData(FALSE);
	hBrush = CreateSolidBrush(RGB(0,0,255));
	hBrush2 = CreateSolidBrush(RGB(255,255,255));
	hBrush1= CreateSolidBrush(RGB(123,123,123));
    hBrush3=CreateSolidBrush(RGB(192,220,192));
    HBITMAP hBitmap ;
	
	m_bitmapGreen.LoadBitmap(IDB_BITMAP1);
    hBitmap = 	(HBITMAP) m_bitmapGreen.GetSafeHandle();

	((CButton*)GetDlgItem(IDC_INSERT))->SetBitmap(hBitmap);

	para_num=0;
	CString str;
    CString str_add;
    com_present=0;
	c_j=0;

  //   定义数据集对象

    spudetailed   =new  Spudetailed_me(&m_Database);
    spuinform1	 = new SpuInform(&m_Database);

  //1   完成spu_temp结构的初始化
    int i,step_max;
    step_max=0;  
	for(i=0;i<=2000;i++)
	{
	spu_temp[i].spu_num=0;           //时序号   
    spu_temp[i].step=0;       //步号
    spu_temp[i].command_num=0;             //索引号  
    spu_temp[i].para1=_T("");
    spu_temp[i].para2=_T("");
    spu_temp[i].para3=_T("");
    spu_temp[i].para4=_T("");
	}
   	spu_temp[0].spu_num=-1;           //时序号   
    spu_temp[0].step=-1;       //步号
    spu_temp[0].command_num=-1;             //索引号  
    spu_temp[0].para1=_T("");
    spu_temp[0].para2=_T("");
    spu_temp[0].para3=_T("");
    spu_temp[0].para4=_T("");

    GetDlgItem(ID_xiug)->EnableWindow(FALSE);
	//2      打开纪录表
    
				spudetailed->m_strFilter.Format("spu_num = %d",m_SPU_num);
				if (!spudetailed->IsOpen() )
				{	 
					spudetailed->Open(CRecordset::dynaset);
				}
				else
					spudetailed->Requery();
    //mode1    处理新加的框，如果详细数据库已有，就删除

				if(!spudetailed->IsEOF())
				{
					spudetailed->MoveFirst();
					while(!spudetailed->IsEOF())
					{    
					    if(model==0)  //mode 1
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
						}
						else           //mode 2
						{   
							spu_temp[spudetailed->m_step_num].spu_num=spudetailed->m_spu_num;           //时序号   
                            spu_temp[spudetailed->m_step_num].step=spudetailed->m_step_num;              //步号
                            spu_temp[spudetailed->m_step_num].command_num=spudetailed->m_command_index;       //索引号  
							str=spudetailed->m_para1;
                            str.TrimLeft();
							str.TrimRight();
							if(!str.IsEmpty())
							spu_temp[spudetailed->m_step_num].para1=str;                            
                           	str=spudetailed->m_para2;
							str.TrimLeft();
							str.TrimRight();
							if(!str.IsEmpty())

							spu_temp[spudetailed->m_step_num].para2=str;
							str=spudetailed->m_para3;
						    str.TrimLeft();
							str.TrimRight();
							if(!str.IsEmpty())
							spu_temp[spudetailed->m_step_num].para3=str;

							str=spudetailed->m_para4;
							str.TrimLeft();
							str.TrimRight();
							if(!str.IsEmpty())
							spu_temp[spudetailed->m_step_num].para4=str;
                            
						    str=pApp->pMPT->GetDes(2, spu_temp[spudetailed->m_step_num].command_num);
							 str_add.Format(" 步号%4d  命令号%3d  %5s  %5s  %5s  %5s  %5s    ",
								spu_temp[spudetailed->m_step_num].step,
                                spu_temp[spudetailed->m_step_num].command_num,
								str,
								spu_temp[spudetailed->m_step_num].para1,
								spu_temp[spudetailed->m_step_num].para2,
								spu_temp[spudetailed->m_step_num].para3,
								spu_temp[spudetailed->m_step_num].para4); 
						   step_max=spudetailed->m_step_num;
							m_list.AddString(str_add);
						}
			
						spudetailed->MoveNext();
					}   //wile jieshu
				}
				
				spudetailed->Close();
	
         SetDlgItemInt(  IDC_EDIT_STEP,step_max+1);

		 m_com.AddString("001 END   序列结束");
         m_com.AddString("002 ADDD  加法");
         m_com.AddString("003 SUBD  减法");
         m_com.AddString("004 ANDD  逻辑与");
         m_com.AddString("005 ORLD  逻辑或");
         m_com.AddString("006 XORD  逻辑异或");
         m_com.AddString("007 ADD   加法");
         m_com.AddString("008 SUB   减法");
         m_com.AddString("009 AND   逻辑与");
         m_com.AddString("010 ARL   逻辑或");
         m_com.AddString("011 XOR   逻辑异或");
         m_com.AddString("012 MUL   乘法");
         m_com.AddString("013 DIV   除法");
         m_com.AddString("014 GOTO  转移到本序列某一步号");
         m_com.AddString("015 CALL  调用某一个序列的某一步");
         m_com.AddString("016 GOTOSQ转移到某一个序列的某一步");
         m_com.AddString("017 FILL	赋值给从指定寄存器开始的寄存器");
         m_com.AddString("018 DJNZ	寄存器值减一并在该值非零时转移到指定步");
         m_com.AddString("019 DELAY	按秒数延迟执行");
         m_com.AddString("020 STRSEQ启动序号");
         m_com.AddString("021 ABTSEQ中断序号");
         m_com.AddString("022 LCKSEQ锁定序号或模式号");
         m_com.AddString("023 RDTIME读当前时间到寄存器");
         m_com.AddString("024 RDDATE读当前日期到寄存器");
         m_com.AddString("025 DOUT	数字输出控制");
         m_com.AddString("026 AOUT	模拟输出控制");
         m_com.AddString("027 DROUT	直接控制");
         m_com.AddString("028 IFGTV2  Val1>Val2 转移或调用");
         m_com.AddString("029 IFGEV2  Val1>=Val2 转移或调用");
         m_com.AddString("030 IFEQV2  Val1=Val2 转移或调用");
         m_com.AddString("031 IFLEV2  Val1<=Val2 转移或调用");
         m_com.AddString("032 IFLTV2  Val1<Val2 转移或调用");
         m_com.AddString("033 IFNEV2  Val1<Val2 转移或调用");
         m_com.AddString("034 IFGTCN  Val1>CONS 转移或调用");
         m_com.AddString("035 IFGECN  Val1>=CONS转移或调用");		 
		 m_com.AddString("036 IFEQCN  Val1=CONS 转移或调用");
         m_com.AddString("037 IFLECN  Val1<=CONS 转移或调用");
         m_com.AddString("038 IFLTCN  Val1<CONS  转移或调用");
		 m_com.AddString("040 IFNECN  Val1<>CONS  转移或调用");
		 m_com.AddString("041 IFTIME  是否为当前时间  转移或调用");
		 m_com.AddString("042 HORN 发指定喇叭音");
		 m_com.AddString("043 SNDDL	发送虚拟点 Pt# 状态和测点值到数据链路");
		 m_com.AddString("044 PRPRT	打印报告 报告号 开始项号 结束项号");
		 m_com.AddString("045 HLACTL	模拟高低平均值报告控制");
		 m_com.AddString("046 NOOPR	不操作");

  return TRUE;
}

bool CSpuEdit::OnInsert() 
{
	// TODO: Add your control notification handler code here
	CKJMonitorApp* pApp=(CKJMonitorApp* )AfxGetApp();
	UpdateData(TRUE);
	int step_temp;
    step_temp=	GetDlgItemInt(IDC_EDIT_STEP ,NULL,0);   //
     // 判断此命令是否插在最后 就是新插 
     if(m_com_num<=0||step_temp<=0)
         return false;

    int step_max;
	step_max=0;

	while(spu_temp[++step_max].step>0);
    
    step_max--;    //计算出现在已有的数量
  
	//以下代码进行判断输入是否正确
	CString str_judge;

   if(para_num==1)
   {
     str_judge=m_para1;
     str_judge.TrimLeft();
     str_judge.TrimRight();
     if(str_judge.IsEmpty())
		  return false;
   }
   else if(para_num==2)
   {
	  str_judge=m_para1;
      str_judge.TrimLeft();
      str_judge.TrimRight();
      if(str_judge.IsEmpty())
		  return false;
  	  str_judge=m_para2;
      str_judge.TrimLeft();
      str_judge.TrimRight();
      if(str_judge.IsEmpty())
		  return false;
   }
   else if(para_num==3)
   {
	  str_judge=m_para1;
      str_judge.TrimLeft();
      str_judge.TrimRight();
      if(str_judge.IsEmpty())
		  return false;
  	  str_judge=m_para2;
      str_judge.TrimLeft();
      str_judge.TrimRight();
      if(str_judge.IsEmpty())
		  return false;
	  str_judge=m_para3;
      str_judge.TrimLeft();
      str_judge.TrimRight();
      if(str_judge.IsEmpty())
		  return false;
   }
   else if(para_num==4)
   {
	  str_judge=m_para1;
      str_judge.TrimLeft();
      str_judge.TrimRight();
      if(str_judge.IsEmpty())
		  return false;
  	  str_judge=m_para2;
      str_judge.TrimLeft();
      str_judge.TrimRight();
      if(str_judge.IsEmpty())
		  return false;
	  str_judge=m_para3;
      str_judge.TrimLeft();
      str_judge.TrimRight();
      if(str_judge.IsEmpty())
		  return false;
	  str_judge=m_para4;
      str_judge.TrimLeft();
      str_judge.TrimRight();
      if(str_judge.IsEmpty())
		  return false;
   }
   para_num=0;
   
   //修改spu_temp
    spu_temp[step_temp].spu_num=m_SPU_num;           //时序号   
    spu_temp[step_temp].step=step_temp;              //步号
    spu_temp[step_temp].command_num=m_com_num;       //索引号  
    CString str_para("");
    
	str_para=m_para1;
	str_para.TrimLeft();
    str_para.TrimRight();
    if(!str_para.IsEmpty())
	    spu_temp[step_temp].para1=str_para;
    else
	{
		spu_temp[step_temp].para1=_T("");
	}
	str_para=m_para2;
	str_para.TrimLeft();
     str_para.TrimRight();
    if(!str_para.IsEmpty())
	spu_temp[step_temp].para2=str_para;
	else
	{
		spu_temp[step_temp].para2=_T("");
	}
	str_para=m_para3;
    str_para.TrimLeft();
    str_para.TrimRight();
	if(!str_para.IsEmpty())
	    spu_temp[step_temp].para3=str_para;
	else
	{
		spu_temp[step_temp].para3=_T("");
	}
	str_para=m_para4;
    str_para.TrimLeft();
    str_para.TrimRight();
	if(!str_para.IsEmpty())
	    spu_temp[step_temp].para4=str_para;
	else
	{
		spu_temp[step_temp].para4=_T("");
	}

	CString str1,str;
	str=pApp->pMPT->GetDes(2, spu_temp[step_temp].command_num);

	str1.Format(" 步号%4d  命令号%3d  %5s  %5s  %5s  %5s  %5s    ",
								     spu_temp[step_temp].step,
                                spu_temp[step_temp].command_num,  str,
								spu_temp[step_temp].para1,
								spu_temp[step_temp].para2,
								spu_temp[step_temp].para3,
								spu_temp[step_temp].para4); 
     
	if(step_temp<=step_max)    //表示修改
	{
      m_list.DeleteString(step_temp-1);
      m_list.InsertString(step_temp-1,str1);
      SetDlgItemInt(IDC_EDIT_STEP ,step_max+1);
	}
	else
	{
	  m_list.InsertString(step_temp-1,str1);
      SetDlgItemInt(IDC_EDIT_STEP ,step_max+2);
	}
            SetDlgItemText(IDC_EDIT_PA1,_T(""));
			SetDlgItemText(IDC_PARA1,_T(""));
            GetDlgItem(IDC_EDIT_PA1)->EnableWindow(FALSE);

            SetDlgItemText(ID_EDITPARA2,_T(""));
			SetDlgItemText(IDC_PARA2,_T(""));
            GetDlgItem(ID_EDITPARA2)->EnableWindow(FALSE);
    
            SetDlgItemText(IDC_EDIT_PA3,_T(""));
			SetDlgItemText(IDC_PARA3,_T(""));
            GetDlgItem(IDC_EDIT_PA3)->EnableWindow(FALSE);
    
            SetDlgItemText(IDC_EDIT_PARA4,_T(""));
			SetDlgItemText(IDC_PARA4,_T(""));
            GetDlgItem(IDC_EDIT_PARA4)->EnableWindow(FALSE);
//			SetDlgItemText(IDC_EDIT_COMMAND_DES, _T(""));
			m_com.SetCurSel(-1);
	    	SetDlgItemInt(IDC_EDIT_COMMAND, NULL);
            GetDlgItem(IDOK)->EnableWindow(TRUE);

   return TRUE;
}

void CSpuEdit::OnSelchangeList1() 
{
	// TODO: Add your control notification handler code here

 //  MessageBox("fuck your wife");
     GetDlgItem(ID_xiug)->EnableWindow(TRUE);
     GetDlgItem(IDC_BUTTON_KONG)->EnableWindow(TRUE);
     GetDlgItem(IDC_BUTTON_DEL)->EnableWindow(TRUE);
}

void CSpuEdit::OnDoubleclickedInsert() 
{
	// TODO: Add your control notification handler code here
}

void CSpuEdit::OnEmpty() 
{
	// TODO: Add your control notification handler code here
}

void CSpuEdit::Onxiug() 
{
	// TODO: Add your control notification handler code here
	CKJMonitorApp* pApp=(CKJMonitorApp* )AfxGetApp();
	int i;
    GetDlgItem(IDC_INSERT)->EnableWindow(TRUE);
    i=m_list.GetCurSel()+1;
    m_para1 = spu_temp[i].para1;
	m_para2 = spu_temp[i].para2;
	m_para3 = spu_temp[i].para3;
	m_para4 = spu_temp[i].para4;
	m_com_num = spu_temp[i].command_num;
	com_present=m_com_num;
	m_step = spu_temp[i].step;

	i=m_com_num;
	CString str;
       if(i>0&&i<=46)
	{
          	str=pApp->pMPT->GetDes(1, i);
            SetDlgItemText(IDC_DISCRIPTION,str);
          	str=pApp->pMPT->GetDes(2, i);
//			SetDlgItemText(IDC_EDIT_COMMAND_DES, str);
           	m_com.SetCurSel(i-1);

		    para_num=0;	
			str=pApp->pMPT->GetDes(3, i);
			
			if(str.IsEmpty())
			{
                        GetDlgItem(IDC_EDIT_PA1)->EnableWindow(FALSE);
			            SetDlgItemText(IDC_PARA1,_T(""));
			}else
			{
			            para_num=1;
		                GetDlgItem(IDC_EDIT_PA1)->EnableWindow(TRUE);
                        SetDlgItemText(IDC_PARA1,str);
			}
			str=pApp->pMPT->GetDes(4, i);
			if(str.IsEmpty())
            {
				        GetDlgItem(ID_EDITPARA2)->EnableWindow(FALSE);
			            SetDlgItemText(IDC_PARA2,_T(""));
			}
			else
			{
                        para_num=2;
				        GetDlgItem(ID_EDITPARA2)->EnableWindow(TRUE);            
                        SetDlgItemText(IDC_PARA2,str);
			}
			str=pApp->pMPT->GetDes(5, i);
			if(str.IsEmpty())
			{
                        GetDlgItem(IDC_EDIT_PA3)->EnableWindow(FALSE);
			            SetDlgItemText(IDC_PARA3,_T(""));
			}
			else
			{
				para_num=3;
		        GetDlgItem(IDC_EDIT_PA3)->EnableWindow(TRUE);
                SetDlgItemText(IDC_PARA3,str);
			}
			str=pApp->pMPT->GetDes(6, i);
			if(str.IsEmpty())
			{
                 GetDlgItem(IDC_EDIT_PARA4)->EnableWindow(FALSE);
			     SetDlgItemText(IDC_PARA4,_T(""));
			}
			else
			{
				 para_num=4;
                 GetDlgItem(IDC_EDIT_PARA4)->EnableWindow(TRUE);
                 SetDlgItemText(IDC_PARA4,str);
			}
	   }
    	UpdateData(FALSE);
}

void CSpuEdit::OnKillfocusEditCommand() 
{
	// TODO: Add your control notification handler code here
	CKJMonitorApp* pApp=(CKJMonitorApp* )AfxGetApp();

    int i;
	CString str;
    i=   	GetDlgItemInt(IDC_EDIT_COMMAND ,NULL,0);   //
 	
	if(i>0&&i<=46)
	{
		m_com.SetCurSel(i-1);
		    c_j=0;
			 
		    com_present=i;
          	str=pApp->pMPT->GetDes(1, i);
            SetDlgItemText(IDC_DISCRIPTION,str);
          	str=pApp->pMPT->GetDes(2, i);
//			SetDlgItemText(IDC_EDIT_COMMAND_DES, str);
            			para_num=0;
 		    	
			str=pApp->pMPT->GetDes(3, i);
			if(str.IsEmpty())
			{
                      GetDlgItem(IDC_EDIT_PA1)->EnableWindow(FALSE);
			          SetDlgItemText(IDC_PARA1,_T(""));
                      SetDlgItemText(IDC_EDIT_PA1,_T(""));
			}
			else
			{
			     para_num=1;
		         GetDlgItem(IDC_EDIT_PA1)->EnableWindow(TRUE);
                 SetDlgItemText(IDC_EDIT_PA1,_T(""));
                 SetDlgItemText(IDC_PARA1,str);
			}
			str=pApp->pMPT->GetDes(4, i);
			if(str.IsEmpty())
            {
				 GetDlgItem(ID_EDITPARA2)->EnableWindow(FALSE);
			     SetDlgItemText(IDC_PARA2,_T(""));
		      	 SetDlgItemText(ID_EDITPARA2,_T(""));
			}
			else
			{
                 para_num=2;
			     GetDlgItem(ID_EDITPARA2)->EnableWindow(TRUE);      
		         SetDlgItemText(ID_EDITPARA2,_T(""));
                 SetDlgItemText(IDC_PARA2,str);
			}
 			str=pApp->pMPT->GetDes(5, i);
			if(str.IsEmpty())
			{
                 GetDlgItem(IDC_EDIT_PA3)->EnableWindow(FALSE);
			     SetDlgItemText(IDC_PARA3,_T(""));
		         SetDlgItemText(IDC_EDIT_PA3,_T(""));
			}
			else
			{
				para_num=3;
		        GetDlgItem(IDC_EDIT_PA3)->EnableWindow(TRUE);
			    SetDlgItemText(IDC_EDIT_PA3,_T(""));
                SetDlgItemText(IDC_PARA3,str);
			}
 			str=pApp->pMPT->GetDes(6, i);
			if(str.IsEmpty())
			{
                GetDlgItem(IDC_EDIT_PARA4)->EnableWindow(FALSE);
			    SetDlgItemText(IDC_PARA4,_T(""));
                SetDlgItemText(IDC_EDIT_PARA4,_T(""));
			}
			else
			{
				para_num=4;
                GetDlgItem(IDC_EDIT_PARA4)->EnableWindow(TRUE);
		        SetDlgItemText(IDC_EDIT_PARA4,_T(""));
                SetDlgItemText(IDC_PARA4,str);
			}
//			   	UpdateData(TRUE);
 	            GetDlgItem(IDC_INSERT)->EnableWindow(TRUE);
	}
}

void CSpuEdit::OnDblclkList1() 
{
	// TODO: Add your control notification handler code here
	CKJMonitorApp* pApp=(CKJMonitorApp* )AfxGetApp();
	GetDlgItem(IDC_INSERT)->EnableWindow(TRUE);
	int i;
	CString str;
    i=m_list.GetCurSel()+1;
    m_para1 = spu_temp[i].para1;
	m_para2 = spu_temp[i].para2;
	m_para3 = spu_temp[i].para3;
	m_para4 = spu_temp[i].para4;
	m_com_num = spu_temp[i].command_num;
	com_present=m_com_num;
	m_step = spu_temp[i].step;
 	i=m_com_num;
    if(i>0&&i<=46)
	{
          	str=pApp->pMPT->GetDes(1, i);
            SetDlgItemText(IDC_DISCRIPTION,str);
          	str=pApp->pMPT->GetDes(2, i);
//			SetDlgItemText(IDC_EDIT_COMMAND_DES, str);
           	m_com.SetCurSel(i-1);
 		    para_num=0;
 			str=pApp->pMPT->GetDes(3, i);
			if(str.IsEmpty())
			{
                GetDlgItem(IDC_EDIT_PA1)->EnableWindow(FALSE);
	            SetDlgItemText(IDC_PARA1,_T(""));
			}else
			{
			     para_num=1;
		         GetDlgItem(IDC_EDIT_PA1)->EnableWindow(TRUE);
                 SetDlgItemText(IDC_PARA1,str);
			}
			str=pApp->pMPT->GetDes(4, i);
			if(str.IsEmpty())
            {
				GetDlgItem(ID_EDITPARA2)->EnableWindow(FALSE);
			    SetDlgItemText(IDC_PARA2,_T(""));
			}
			else
			{
                para_num=2;
				GetDlgItem(ID_EDITPARA2)->EnableWindow(TRUE);            
                SetDlgItemText(IDC_PARA2,str);
			}
			str=pApp->pMPT->GetDes(5, i);
			if(str.IsEmpty())
			{
                GetDlgItem(IDC_EDIT_PA3)->EnableWindow(FALSE);
			    SetDlgItemText(IDC_PARA3,_T(""));
			}
			else
			{
				para_num=3;
		        GetDlgItem(IDC_EDIT_PA3)->EnableWindow(TRUE);
                SetDlgItemText(IDC_PARA3,str);
			}
			str=pApp->pMPT->GetDes(6, i);
			if(str.IsEmpty())
			{
                GetDlgItem(IDC_EDIT_PARA4)->EnableWindow(FALSE);
			    SetDlgItemText(IDC_PARA4,_T(""));
			}
			else
			{
				para_num=4;
                GetDlgItem(IDC_EDIT_PARA4)->EnableWindow(TRUE);
                SetDlgItemText(IDC_PARA4,str);
			}
	}
   	UpdateData(FALSE);
}

void CSpuEdit::OnChangeEditCommand() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	// TODO: Add your control notification handler code here
/*
	m_para1=_T("");
	m_para2=_T("");
	m_para3=_T("");
	m_para4=_T("");
*/
	            GetDlgItem(IDC_INSERT)->EnableWindow(FALSE);
}

void CSpuEdit::OnCheck1() 
{
	// TODO: Add your control notification handler code here
		            GetDlgItem(IDOK)->EnableWindow(TRUE);
					if(m_hangup==TRUE)
						m_hangup=FALSE;
					else 
						m_hangup=TRUE;
}

void CSpuEdit::OnChangeEditPriority() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	// TODO: Add your control notification handler code here
		            GetDlgItem(IDOK)->EnableWindow(TRUE);
}

void CSpuEdit::OnOK() 
{
	// TODO: Add extra validation here
	//写入总表
    UpdateData(TRUE);
	int step_max;
	step_max=0;
	while(spu_temp[++step_max].step>0);
	      step_max--;
	int i=step_max;
    if(step_max<=0)
	{
		 CDialog::OnOK();
	}
	else
	{
     //写入  spuinform    
  //       spuinform1->m_strFilter.Empty();
         spuinform1->m_strFilter.Format("ID = %d",m_SPU_num);
         if (!spuinform1->IsOpen() )
  	         spuinform1->Open();
     	 else
     	     spuinform1->Requery();
 	     if(!spuinform1->IsEOF())
		 {  //if(!spuinform->IsEOF())  kaishi
			spuinform1->MoveLast();
//	     	m_Database.BeginTrans();
			    try
				{
              		spuinform1->Edit();
                    spuinform1->m_exit_or_empty=TRUE;
                    spuinform1->m_num_of_command=step_max;
                    spuinform1->m_priority=m_priority;
			        spuinform1->m_active_hangup=m_hangup;
                     spuinform1->Update();
				}
				catch(CException *e)
				{
					delete spuinform1; 
					e->Delete();
				}
		 }
       // 写入spudetailed
	      //先删除除
	  	 spudetailed->m_strFilter.Format("spu_num = %d",m_SPU_num);
		 if (!spudetailed->IsOpen() )
		 {	 
			  spudetailed->Open(CRecordset::dynaset );
		 }
		 else
			  spudetailed->Requery();
		 if(!spudetailed->IsEOF())
		 {
			  spudetailed->MoveFirst();
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
			  }
					//wile jieshu
		 }  
	       //写入新的数据
		 spudetailed->m_strFilter.Empty();
	  	 if (!spudetailed->IsOpen() )
		 {	 
			  spudetailed->Open(CRecordset::dynaset  );
		 }
		 else
			  spudetailed->Requery();
		 int ii;
	         ii=1;
	     while(spu_temp[ii].step>0)
		 {
			  try
			  {
                spudetailed->AddNew();
                spudetailed->m_spu_num = spu_temp[ii].spu_num;
	            spudetailed->m_step_num = spu_temp[ii].step;
	            spudetailed->m_command_index = spu_temp[ii].command_num;
               	spudetailed->m_para1 = spu_temp[ii].para1;
	            spudetailed->m_para2 = spu_temp[ii].para2;
	            spudetailed->m_para3 = spu_temp[ii].para3;
	            spudetailed->m_para4 = spu_temp[ii].para4;
            	spudetailed->Update();
			  }
	          catch(CDBException *e)
			  {
			 	e->Delete();
			  }	
	          ii=ii+1;
		 }
          //跟新前 对话框
	      CString temp_information,temp_exit,temp_hang,temp_com_num;

			 temp_information.Format("时序 %3d",m_SPU_num);
			 temp_exit="  存在";
			 
          if(m_hangup)
			  temp_hang="  已经挂起";
		  else  
              temp_hang="  正在使用";

		  temp_com_num.Format("    指令数为 %4d 优先级 %4d",step_max,m_priority);

//  ((CShixuDlg*)AfxGetApp()->m_pMainWnd)->m_list.DeleteString(m_SPU_num-1);
 // ((CShixuDlg*)AfxGetApp()->m_pMainWnd)->m_list.InsertString(m_SPU_num-1,temp_information+temp_exit+temp_com_num+temp_hang);
          extern CShixuDlg dlgshixu;
	      dlgshixu.m_list.DeleteString(m_SPU_num-1);
          dlgshixu.m_list.InsertString(m_SPU_num-1,temp_information+temp_exit+temp_com_num+temp_hang);
	      CDialog::OnOK();
    }
}

CSpuEdit::~CSpuEdit()
{
	    delete spuinform1;
		delete spudetailed;
}

bool CSpuEdit::OnJudge(int mode,char a,long num) 
{
	switch(com_present)
	{
	case 1:
		return true;
		break;
	case 2:
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
    case 10:
    case 11:
    case 12:
    case 13:
		if(a=='P'||a=='p')
		{
			if(num>0&&num<=15000)
				return true;
			else 
				return false;
		}
		else if(a=='R'||a=='r')
		{	
			if(num>0&&num<=48)
				return true;
			else 
				return false;
		}
		else if(a=='X'||a=='x')
		{	
			if(num>0&&num<=64)
				return true;
			else 
				return false;
		}
		else if((a>=48&&a<=57)||a=='#') 
		{
			  if(mode==1)
				return false;
			  else 
				return true;
		}
		else 
		       return false;
		break;
    case 14:
		if((a>=48&&a<=57)||a=='#') 
		{ if(num>0&&num<=2000)
		     return true;
		  else
		     return false;
		}
		else 
			return false;
        break;
	case 15:
	case 16:
		if(mode==1)
		{	
			if((a>=48&&a<=57)||a=='#') 
			{ if(num>0&&num<=200)
		        return true;
		     else
		        return false;
			}
		    else 
			    return false;
		}
		else if(mode==2)
		{
			if((a>=48&&a<=57)||a=='#') 
			{ if(num>0&&num<=2000)
		        return true;
		     else
		        return false;
			}
		    else 
			   return false;
		}
		else 
			return false;
         break;
	case 17:

		  if(mode==1)
		 {
			 if((a=='R'||a=='r')&&num>0&&num<=48)
				 return true;
			 else 
				 return false;
		 }
		 else if(mode==2)
		 {			
			 if((a>=48&&a<=57)||a=='#') 
			{ if(num>0&&num<=65535)
		         return true;
		     else
		         return false;
			 }
			 else 
				 return false;
		 }
		 else if(mode==3)
		 {			 
			 if((a>=48&&a<=57)||a=='#') 
			{ if(num>0&&num<=48)
		          return true;
		     else
		          return false;
			 }
			 else 
				 return false;
		 }
    case 18:
        if(mode==1)
		 {
			 if((a=='R'||a=='r')&&num>0&&num<=48)
				 return true;
			 else 
				 return false;
		 }
		 else if(mode==2)
		 {			
			 if((a>=48&&a<=57)||a=='#') 
			{ if(num>0&&num<=2000)
		         return true;
		     else
		         return false;
			}
		    else 
			     return false;
		 }
		 break;
	case 19:
			if((a>=48&&a<=57)||a=='#') 
			{ if(num>0&&num<=3600)
		         return true;
		     else
		         return false;
			}
		    else 
			    return false;
            break;
    case 20:
    case 21:
		if(a=='R'||a=='r')
		{	
			if(num>0&&num<=48)
				return true;
			else 
				return false;
		}
		else if(a=='X'||a=='x')
		{	
			if(num>0&&num<=64)
				return true;
			else 
				return false;
		}
		else if((a>=48&&a<=57)||a=='#') 
		{
			if(num>0&&num<=200)
		     return true;
		     else
		     return false;
		}
		else 
			return false;
		break;
    case 22:
		if(mode==1)
		{
		if(a=='R'||a=='r')
		{	
			if(num>0&&num<=48)
				return true;
			else 
				return false;
		}
		else if(a=='X'||a=='x')
		{	
			if(num>0&&num<=64)
				return true;
			else 
				return false;
		}
		else if((a>=48&&a<=57)||a=='#') 
		{
			if(num>0&&num<=200)
		     return true;
		     else
		     return false;
		}
		else 
			return false;
		}
		else if(mode==2)
		{
			if((a>=48&&a<=57)||a=='#') 
			{
				if(num==0&&num==1)
		        return true;
		        else
		         return false;
			}
		}
		break;
	case 23:
	case 24:
		if(a=='R'||a=='r')
		{	
			if(num>0&&num<=48)
				return true;
			else 
				return false;
		}
		else
			return false;
        break;
    case 25:
		if(mode==1)
		{ 		
			if(a=='P'||a=='p')
			{
			if(num>0&&num<=15000)
				return true;
			else 
				return false;
			}
			else
				return false;
		}
		else if(mode==2)
		{
			if((a>=48&&a<=57)||a=='#')
			{
			   if(num==1||num==2||num==40||num==42||num==32||num==34||num==98)
				   return true;
			   else return false;
			}else if (a=='R'||a=='r')
			{
				if(num>0||num<=48)
					return true;
				else 
					return false ;
			}
			else if(a=='X'||a=='x')
			{
				if(num>0||num<=64)
					return true;
				else
					return false;
			}
			else 
				return false;
		}
		else if(mode==3)
		{	if((a>=48&&a<=57)||a=='#')
			{
			   if(num>=0&&num<=3600)
				   return true;
			   else return false;
			}
		    else
				return false;
		}
		else if(mode==4)
		{
			if(a=='1'||a=='2'||a=='3')
				return true;
			else 
				return false;
		}
      break;
     case 26:
	 case 27:
		if(mode==1)
		{ 		
			if(a=='P'||a=='p')
			{
			if(num>0&&num<=15000)
				return true;
			else 
				return false;
			}
			else
				return false;
		}
		else if(mode==2)
		{
			if((a>=48&&a<=57)||a=='#')
			{
				   return true;
			}else if (a=='R'||a=='r')
			{
				if(num>0||num<=48)
					return true;
				else 
					return false ;
			}
			else if(a=='X'||a=='x')
			{
				if(num>0||num<=64)
					return true;
				else
					return false;
			}
			else 
				return false;
		}
		else if(mode==3)
		{	if((a>=48&&a<=57)||a=='#')
			{
			   if(num>=0&&num<=3600)
				   return true;
			   else return false;
			}
		    else
				return false;
		}
		else if(mode==4)
		{
			if(a=='1'||a=='2'||a=='3')
				return true;
			else 
				return false;
		}

      break;
	 case 28:
	 case 29:
	 case 30:
	 case 31:
	 case 32:
	 case 33:
	 case 34:
	 case 35:
	 case 36:
	 case 37:
	 case 38:
	 case 39:
     case 40:
      if(mode==1||mode==2)
	  {
		 if(a=='P'||a=='p')
		{
			if(num>0&&num<=15000)
				return true;
			else 
				return false;
		}
		else if(a=='R'||a=='r')
		{	
			if(num>0&&num<=48)
				return true;
			else 
				return false;
		}
		else if(a=='X'||a=='x')
		{	
			if(num>0&&num<=64)
				return true;
			else 
				return false;
		}
		else if((a>=48&&a<=57)||a=='#')
		{
			if(mode==1&&com_present!=40)
				return false;
			else if(mode==1&&com_present==40)
			{
				if(num>=0&&num<=12)
					return true;
				else 
					return false;
			}
			else if(mode==2&&com_present!=40)
			{
				if(com_present>=34&&com_present<=39)
					return true;
				else 
					return false;
			}
			else if(mode==2&&com_present==40)
			{
					if(num>=0&&num<60)
					    return true;
				    else 
					    return false;
			}
			else 
				return false;
		}
	  }
	  else if(mode==3)
	  {
		  if(a=='J'||a=='j')
          {   c_j=1;
			  return true;
		  }
		  else if(a=='C'||a=='c')
          {   c_j=2;
			  return true;
		  }
		  else 
			  return false;
	  }
	  else if(mode==4)
	  {
		  if(a=='#'||a>=48&&a<=57)
		  {
			  if(c_j==1&&num>0&&num<=2000)
				  return true;
			  else if(c_j==2&&num>0&&num<=200)
				  return true;
			  else 
				  return false;
		  }
	  }
      break;
	 case 41:
		 if(a=='#'||(a>48&&a<=57))
		 {
			 if(num>0&&num<256)
				 return true;
			 else
				 return false;
		 }
		 else if(a=='R'||a=='r')
		 {
			 if(num>0&&num<=48)
				 return true;
			 else 
				 return false;
		 }
		 else if(a=='X'||a=='x')
		 {
			 if(num>0&&num<=64)
				 return true;
			 else
				 return false;
		 }
		 else 
			 false;
        break;
	 case 42:
		 if(a=='p'||a=='P')
		 {
			 if(num>0&&num<15000)
				 return true;
			 else
				 return false;
		 }
		 else if(a=='R'||a=='r')
		 {
			 if(num>0&&num<=48)
				 return true;
			 else 
				 return false;
		 }
		 else if(a=='X'||a=='x')
		 {
			 if(num>0&&num<=64)
				 return true;
			 else
				 return false;
		 }
		 else 
			 return false;
         break;
	 case 43:
		 if((a>=48&&a<=57)||a=='#')
			 return true;
		 else 
			 return false;
		 break;
	 case 44:
		 if((a>=48&&a<=57)||a=='#')
		 {
			 if(num==0||num==1)
				 return true;
			 else 
				 return false;
		 }
		 else 
			 return false;
        break;
	 case 45:
		 return true;
		 break;
	 default:
		 return false;
         break;  
	}
	return false;
}

void CSpuEdit::OnKillfocusEditPa1() 
{
	// TODO: Add your control notification handler code here
	CKJMonitorApp* pApp=(CKJMonitorApp* )AfxGetApp();
//	pApp->pMPT->RefreshPoint(iTrunk);
  char buffer[8];
  long i; 
  GetDlgItemText(IDC_EDIT_PA1,buffer,8);

  i=pApp->pMPT->chartoint(buffer);
  
  if(!OnJudge( 1,buffer[0],i))
  {
	  SetDlgItemText(IDC_EDIT_PA1,"");
//	  GetDlgItem(IDC_EDIT_PA1)->SetFocus();
  }
}

void CSpuEdit::OnKillfocusEditPa3() 
{
	// TODO: Add your control notification handler code here
	CKJMonitorApp* pApp=(CKJMonitorApp* )AfxGetApp();
  char buffer[8];
  long i; 
  GetDlgItemText(IDC_EDIT_PA3,buffer,8);

  i=pApp->pMPT->chartoint(buffer);
  
  if(!OnJudge( 3,buffer[0],i))
  {
	  SetDlgItemText(IDC_EDIT_PA3,"");
//	  GetDlgItem(IDC_EDIT_PA3)->SetFocus();
  }
}

void CSpuEdit::OnKillfocusEditPara4() 
{
	// TODO: Add your control notification handler code here
	CKJMonitorApp* pApp=(CKJMonitorApp* )AfxGetApp();
				
  char buffer[8];
  long i; 
  GetDlgItemText(IDC_EDIT_PARA4,buffer,8);

  i=pApp->pMPT->chartoint(buffer);
   
  if(!OnJudge( 4,buffer[0],i))
  {
	  SetDlgItemText(IDC_EDIT_PARA4,"");
//	  GetDlgItem(IDC_EDIT_PARA4)->SetFocus();
  }
}

void CSpuEdit::OnKillfocusEditpara2() 
{
	// TODO: Add your control notification handler code here
	CKJMonitorApp* pApp=(CKJMonitorApp* )AfxGetApp();
	
  char buffer[8];
  long i; 
  GetDlgItemText(ID_EDITPARA2,buffer,8);

  i=pApp->pMPT->chartoint(buffer);
  
  if(!OnJudge( 2,buffer[0],i))
  {
	  SetDlgItemText(ID_EDITPARA2,"");
//	  GetDlgItem(ID_EDITPARA2)->SetFocus();
  }
}

void CSpuEdit::OnButtonHelp() 
{
	// TODO: Add your control notification handler code here
	AfxGetApp()->WinHelp(101);
}

void CSpuEdit::OnButtonKong() 
{
	// TODO: Add your control notification handler code here
	CKJMonitorApp* pApp=(CKJMonitorApp* )AfxGetApp();
	int k;
	CString str,str_add;
	k=m_list.GetCurSel();
		if(k==-1)
		return;

    //执行插入空事件
   // 取得最大值
	int step_max;
	step_max=0;

	while(spu_temp[++step_max].step>0);
	step_max--;
    
	while(step_max>=(k+1))
	{
		spu_temp[step_max+1]=spu_temp[step_max];
        spu_temp[step_max+1].step++;
		m_list.DeleteString(step_max);
        step_max--;
	} 
    spu_temp[k+2].step=k+2;       //步号
    spu_temp[k+2].command_num=45;             //索引号  
    spu_temp[k+2].para1=_T("");
    spu_temp[k+2].para2=_T("");
    spu_temp[k+2].para3=_T("");
    spu_temp[k+2].para4=_T("");

                           while((spu_temp[k+2].step>0))
						   {
						    str=pApp->pMPT->GetDes(2, spu_temp[k+2].command_num);
							 str_add.Format(" 步号%4d  命令号%3d  %5s  %5s  %5s  %5s  %5s    ",
								spu_temp[k+2].step,
                                spu_temp[k+2].command_num,
								str,
								spu_temp[k+2].para1,
								spu_temp[k+2].para2,
								spu_temp[k+2].para3,
								spu_temp[k+2].para4); 
//						   step_max=spudetailed->m_step_num;
							m_list.AddString(str_add);
                              k++;
                           }
	  GetDlgItem(IDOK)->EnableWindow(TRUE);
 }

void CSpuEdit::OnButtonDel() 
{
	// TODO: Add your control notification handler code here
	CKJMonitorApp* pApp=(CKJMonitorApp* )AfxGetApp();
	int k;
	CString str,str_add;
	k=m_list.GetCurSel();

	if(k==-1)
		return;
    //执行插入空事件
   // 取得最大值
	int step_max;
	step_max=0;

	while(spu_temp[++step_max].step>0);
	step_max--;
    int i;
	i=k+1;
	while(spu_temp[i].step>0)
	{
		spu_temp[i]=spu_temp[i+1];
        spu_temp[i].step--;
//		m_list.DeleteString(k);
        m_list.DeleteString(k);
        i++;
	} 
                          while((spu_temp[k+1].step>0))
						   {
						    str=pApp->pMPT->GetDes(2, spu_temp[k+1].command_num);
							 str_add.Format(" 步号%4d  命令号%3d  %5s  %5s  %5s  %5s  %5s    ",
								spu_temp[k+1].step,
                                spu_temp[k+1].command_num,
								str,
								spu_temp[k+1].para1,
								spu_temp[k+1].para2,
								spu_temp[k+1].para3,
								spu_temp[k+1].para4); 
//						   step_max=spudetailed->m_step_num;
							m_list.AddString(str_add);
                              k++;
                           }
     GetDlgItem(IDOK)->EnableWindow(TRUE);
}

void CSpuEdit::OnSelchangeCombo1() 
{
	// TODO: Add your control notification handler code here
	   	SetDlgItemInt(IDC_EDIT_COMMAND ,(m_com.GetCurSel()+1),FALSE);   //
        GetDlgItem(IDC_EDIT_COMMAND)->SetFocus();
        OnKillfocusEditCommand() ;  
}

HBRUSH CSpuEdit::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
   if(nCtlColor==CTLCOLOR_DLG)
   {
	   pDC->SetBkColor(RGB(192,220,192));  //YELLOW
//	   pDC->SetTextColor(RGB(255,255,255));
	   return hBrush3;
   }
   if(nCtlColor==CTLCOLOR_STATIC)
   {
	   pDC->SetBkColor(RGB(192,220,192));  //YELLOW
//	   pDC->SetTextColor(RGB(255,255,255));
	   return hBrush3;
   }
   if(nCtlColor==CTLCOLOR_EDIT)
   {
	   pDC->SetBkColor(RGB(0,0,255));  //YELLOW
	   pDC->SetTextColor(RGB(255,255,255));
	   return hBrush;
   }
   if(nCtlColor==CTLCOLOR_LISTBOX)
   {
	   pDC->SetBkColor(RGB(255,255,255));  //YELLOW
	   pDC->SetTextColor(RGB(0,0,255));
	   return hBrush2;
   }
   return CDialog::OnCtlColor(pDC,pWnd,nCtlColor);

}



