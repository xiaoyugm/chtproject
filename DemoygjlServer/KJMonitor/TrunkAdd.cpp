// TrunkAdd.cpp : implementation file
//

#include "stdafx.h"
#include "kjmonitor.h"
#include "TrunkAdd.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTrunkAdd

IMPLEMENT_DYNCREATE(CTrunkAdd, CFormView)

CTrunkAdd::CTrunkAdd()
	: CFormView(CTrunkAdd::IDD)
{
	//{{AFX_DATA_INIT(CTrunkAdd)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CTrunkAdd::~CTrunkAdd()
{
}

void CTrunkAdd::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTrunkAdd)
	DDX_Control(pDX, IDC_STATICNOUSE, m_NoUse);
	DDX_Control(pDX, IDC_STATICUSE, m_Use);
	DDX_Control(pDX, IDC_BO_TRUNK, m_ctrlboTrunk);
	DDX_Control(pDX, IDC_ICONLIST, m_ListCtrl);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTrunkAdd, CFormView)
	//{{AFX_MSG_MAP(CTrunkAdd)
	ON_WM_DESTROY()
	ON_CBN_SELCHANGE(IDC_BO_TRUNK, OnSelchangeBoTrunk)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTrunkAdd diagnostics

#ifdef _DEBUG
void CTrunkAdd::AssertValid() const
{
	CFormView::AssertValid();
}

void CTrunkAdd::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CTrunkAdd message handlers

void CTrunkAdd::OnInitialUpdate() 
{
	CFormView::OnInitialUpdate();
	
	Address = 256 ;
    Dispicon = 256 ;
///    ConnectDB() ;
	m_ctrlboTrunk.SetCurSel(0);

	m_hHalloween1  = AfxGetApp()->LoadIcon(IDI_ICONHalloween1);
	m_hHalloween2  = AfxGetApp()->LoadIcon(IDI_ICONHalloween2);

    m_NoUse.SetIcon(m_hHalloween1);	
    m_Use.SetIcon(m_hHalloween2);	

	// Create the image list that is attached to the list control
	InitImageList();

	// Insert the default dummy items
	InsertItems();

}

void CTrunkAdd::OnDestroy() 
{
	CFormView::OnDestroy();
	
	m_SQLDirect.Close();
}

void CTrunkAdd::ConnectDB()
{
	try
	{
		m_SQLDirect.Init();
		if(m_SQLDirect.Connect(_T("masterdefine"),_T("kj86"),_T("kj86")))
			AfxMessageBox("AddUser:无法连接用户参数数据库,请确定SQL SERVER服务是否运行!");
	}
	catch(CDBException *e)
	{
		e->ReportError();
		return;
	}
}

void CTrunkAdd::InitImageList()
{
	HIMAGELIST hList = ImageList_Create(32,32, ILC_COLOR8 |ILC_MASK , 2, 1);
	m_cImageListNormal.Attach(hList);

	// Load the 1 icons
	m_cImageListNormal.Add(m_hHalloween1);

	// Load the 2 icons
	m_cImageListNormal.Add(m_hHalloween2);

	// Attach them
	m_ListCtrl.SetImageList(&m_cImageListNormal, LVSIL_NORMAL);
}

void CTrunkAdd::InsertItems()
{
	// Delete the current contents
	m_ListCtrl.DeleteAllItems();

	// Use the LV_ITEM structure to insert the items
	LVITEM lvi;
	CString strItem;
	for (int i = 0; i < 128; i++)
	{
		// Insert the first item
		lvi.mask =  LVIF_IMAGE | LVIF_TEXT;
		strItem.Format(_T("%i"), i);
	
		lvi.iItem = i;
		lvi.iSubItem = 0;
		lvi.pszText = (LPTSTR)(LPCTSTR)(strItem);

		Address = i ;
///		GetDataFromDBPoint() ;

		if(i < 8)
    		lvi.iImage =  1;
		else
     		lvi.iImage =  0;		// There are 8 images in the image list
		m_ListCtrl.SetIconSpacing(54,54);
		m_ListCtrl.InsertItem(&lvi);


		// Set subitem 2
///		strItem.Format(_T("%s"), COleDateTime::GetCurrentTime().Format(_T("Created: %I:%M:%S %p, %m/%d/%Y")));
	}
}

void CTrunkAdd::OnSelchangeBoTrunk() 
{
	m_ListCtrl.DeleteAllItems();
	InitImageList();
	InsertItems();
}

void CTrunkAdd::GetDataFromDBPoint()
{
	CString strSQL;
 	try
	{        
		strSQL.Format("SELECT * FROM uPointProperty WHERE (unAddress = %d)  AND (unTrunkNo = %d)", Address ,m_ctrlboTrunk.GetCurSel()+1 );  //**change subscript
		if( m_SQLDirect.ExecuteSQL(strSQL)==SQL_SUCCESS)
		{
			int nRet=m_SQLDirect.Fetch();
			int iItem=0;
			while(!nRet)
			{
				iItem++;
				nRet=m_SQLDirect.Fetch();
			}
			if(iItem != 0)
                Dispicon =1 ;
			else
                Dispicon =0 ;
		}
	}
	catch(CDBException *e){
       	e->ReportError();
      	return;
	}
}
