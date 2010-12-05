// SafeMethod.cpp : implementation file
//

#include "stdafx.h"
#include "GUI_VisualStudio.h"
#include "SafeMethod.h"
#include "MainFrm.h"

//#include "ExcelFormat.h"
//using namespace ExcelFormat;

//#define WIN32_LEAN_AND_MEAN
//#include <windows.h>
//#include <shellapi.h>
//#include <crtdbg.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern ADMainDis         m_ADMainDis[MAX_FDS][MAX_CHAN];          //µ˜”√œ‘ æ
extern SlaveStation             m_SlaveStation[MAX_FDS][MAX_CHAN];
/////////////////////////////////////////////////////////////////////////////
// CSafeMethod dialog
/*
//BasicExcel∑‚◊∞¡À∂¡–¥excelµƒ≤Ÿ◊˜(com)£¨ÀŸ∂»∫‹øÏ£¨≤ªπ˝Õ˘xlsŒƒº˛÷––¥»Î÷–Œƒª·≥ˆœ÷¬“¬Î°£
//‘⁄–¥»Î÷–Œƒ«Æœ»Ω´÷–Œƒ±‡¬Î◊™ªªŒ™unicode»ª∫Û‘⁄–¥»ÎxlsŒƒº˛ø…Ω‚æˆ¬“¬ÎŒ Ã‚
//ÃÌº”“ª∏ˆ∫Ø ˝£¨À˘”–µƒ◊÷∑˚¥Æœ» π”√GB2312ToUnicode◊™ªª“ªœ¬
//»ª∫Û‘Ÿµ˜”√basicexcelµƒset∫Ø ˝º¥ø…

void GB2312ToUnicode(CString str_,WCHAR*& pWStr_)//µ√µΩUnicode◊÷∑˚¥Æ
{
    int count = str_.GetLength()*2+1;
    if(pWStr_ == NULL)
    {
        pWStr_ = new WCHAR[count];
    }
    DWORD UnicodeSize=MultiByteToWideChar(CP_ACP,0,(LPCSTR)str_.GetBuffer(count),count,pWStr_,(DWORD)count); 
}

static void copy_sheet(const char* from, const char* to)
{
	BasicExcel xls;

	xls.Load(from);
	xls.SaveAs(to);
}
*/
CSafeMethod::CSafeMethod(CWnd* pParent /*=NULL*/)
	: CDialog(CSafeMethod::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSafeMethod)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CSafeMethod::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSafeMethod)
		  DDX_Text(pDX, IDC_EDIT_SM, strsm);
//	DDV_MaxChars(pDX, strsm, 20);
		  DDX_Control(pDX, IDC_CB_SAFE_M, m_ComBoxSM);
		  DDX_Control(pDX, IDC_CB_SAFE_M2, m_ComBoxSM2);
	DDX_Control(pDX, IDC_LDCHD, m_LDCH);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSafeMethod, CDialog)
	//{{AFX_MSG_MAP(CSafeMethod)
    ON_BN_CLICKED(IDC_CB_SAFE_M, OnBfds)
//    ON_BN_CLICKED(IDOK, OnBnOkSM)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSafeMethod message handlers

BOOL CSafeMethod::OnInitDialog()
{
  CDialog::OnInitDialog();

	HWND hWndHeader = m_LDCH.GetDlgItem(0)->GetSafeHwnd();
	m_header.SubclassWindow(hWndHeader);

	// add bitmap images.
//	m_header.SetBitmap(0, IDB_COLUMN_0, FALSE, RGB(0,255,0));
//	m_header.SetBitmap(1, IDB_COLUMN_1, FALSE, RGB(0,255,0));
	//m_header.SetBitmap(2, IDB_COLUMN_2, FALSE, RGB(0,255,0));

	// enable auto sizing.
//	m_header.EnableAutoSize(TRUE);
	m_header.ResizeColumnsToFit();
	//SortColumn(m_nSortedCol, m_bAscending);

//	m_listCtrl.ModifyExtendedStyle(0, LVS_EX_FULLROWSELECT|LVS_EX_FULLROWSELECT);
	m_LDCH.ModifyExtendedStyle(0, LVS_EX_GRIDLINES);
//	m_listC2.ModifyExtendedStyle(0, LVS_EX_GRIDLINES);


	for(int i = 01; i < MAX_FDS; i++)
	{
		CString strItem;
		strItem.Format(_T("%d"), i);
    	m_ComBoxSM.AddString(strItem);
	}
	m_ComBoxSM.SetCurSel(0);

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
		m_PointDes.Create();
		m_PointDes.CursorType(adOpenDynamic);
		m_PointDes.CacheSize(50);
		m_PointDes._SetRecordsetEvents(new CAccountSetEvents);
		m_PointDes.Open(_T("Select * From pointdescription WHERE fdel=0"), &m_Cn);
		m_PointDes.MarshalOptions(adMarshalModifiedOnly);


  }
  catch ( dbAx::CAxException *e )
  {
    AfxMessageBox(e->m_szErrorDesc,  MB_OK);
    delete e;
    return (FALSE);
  }
	CString strstartTime,strname,dddd;
	int eYear;
		int iItem = 0;
		m_PointDes.MoveFirst();
		while ( !m_PointDes.IsEOF() )
		{
			eYear = m_PointDes.m_szptype;
			if((eYear < 3) || (eYear > 12)||(eYear == 10))
			{
             		int nfds = m_PointDes.m_szfds;
              		int nchan = m_PointDes.m_szchan;
				strname = m_SlaveStation[nfds][nchan].WatchName;
				strstartTime = m_PointDes.m_szpointnum;
				strstartTime.TrimRight();
				dddd = strstartTime + strname;
               	m_ComBoxSM.AddString(dddd);
   		       iItem++;
			}
			m_PointDes.MoveNext();
		}

  return TRUE;  // return TRUE unless you set the focus to a control
  // EXCEPTION: OCX Property Pages should return FALSE
}

void CSafeMethod::OnClose()
{
  //Closing of library objects is ensured as each object
  //goes out of scope, but doing a manual shutdown doesnít hurt.

  try
  {
    if ( m_PointDes._IsOpen() )
      m_PointDes.Close();
    if ( m_Realtimedata._IsOpen() )
      m_Realtimedata.Close();

    m_Cn.Close();

    //Cleanup the AxLib library
    dbAx::Term();
  }
  catch ( CAxException *e )
  {
    MessageBox(e->m_szErrorDesc, _T("BJygjl Message"), MB_OK);
    delete e;
  }
}

//BOOL CSafeMethod::DestroyWindow() 
//{
//	OnClose();
//	return CDialog::DestroyWindow();
//}

void CSafeMethod::OnBnOkSM()
{
    CMainFrame* pFWnd=(CMainFrame*)AfxGetMainWnd();
	CString strItem, strf,strc;
    CString strstartTime,strname,dddd;
			UpdateData(TRUE);           //Exchange dialog data
	int  kkkk = m_ComBoxSM.GetCurSel();
	if(kkkk == -1 || strsm == "")
	{
        AfxMessageBox("«Î—°‘Ò≤‚µ„∫Õ ‰»Î∞≤»´¥Î ©£°");
		return;
	}
	m_ComBoxSM.GetLBText(kkkk,strname);
	strname = strname.Mid(0,5);
    		strf = strname.Mid(0,2);
    		strc = strname.Mid(3);
		int afds = m_Str2Data.String2Int(strf);
		int achan = m_Str2Data.String2Int(strc);
//		strItem = _T("Select * From realtimedata WHERE ");
//		strname.Format("fds=%d and chan=%d",nfds,nchan);

			COleDateTime CTime;
//			CString strCTime;
//			strCTime.Format("%d-%d-%d %d:%d:%d",CTime.GetYear(),CTime.GetMonth(),CTime.GetDay(),CTime.GetHour(),CTime.GetMinute(),CTime.GetSecond());
	//		strNormalTime.Format("%d-%d-%d %d:%d:%d",NormalTime.GetYear(),NormalTime.GetMonth(),NormalTime.GetDay(),NormalTime.GetHour(),NormalTime.GetMinute(),NormalTime.GetSecond());
            				try
							{
	         				 m_RealtimedataNew->m_szRTID  = 1;
		      			     m_RealtimedataNew->m_szPID = m_SlaveStation[afds][achan].m_PID;
							 int m_nptype = m_SlaveStation[afds][achan].ptype;
		    			     m_RealtimedataNew->m_szptype = m_nptype;
    						 m_RealtimedataNew->m_szfds = afds;
     						 m_RealtimedataNew->m_szchan = achan;
					theApp.m_resnum = 10;
					m_SlaveStation[afds][achan].strSafe = strsm;
					m_SlaveStation[afds][achan].ValueTime = CTime.GetCurrentTime();
							 if(m_nptype >3)
							 {
							m_ADMainDis[afds][achan].NTime = CTime.GetCurrentTime();
    						      m_RealtimedataNew->m_szCDValue = m_SlaveStation[afds][achan].CValue;
     				   		      m_RealtimedataNew->m_szAValue = 0;
                                  pFWnd->m_wndResourceView4.InitLDAB(afds,achan);
							 }
							 else
							 {
    						      m_RealtimedataNew->m_szCDValue = 0;
     				   		      m_RealtimedataNew->m_szAValue = m_SlaveStation[afds][achan].AValue;
                                  pFWnd->m_wndResourceView.InitLC(afds,achan);
							 }
    						 m_RealtimedataNew->m_szADStatus = m_SlaveStation[afds][achan].Channel_state;
    						 m_RealtimedataNew->m_szrecdate = CTime.GetCurrentTime();
     						 m_RealtimedataNew->m_szUseridadd = theApp.curuser;
//    						 m_RealtimedataNew->m_szsafemdate = CTime.GetCurrentTime();
    						 m_RealtimedataNew->m_szsafemtext = strsm;
      						m_RealtimedataNew->AddNew();  //Add a new, blank record
					   	    m_RealtimedataNew->Update();    //Update the recordset
							//If this is a new record, requery the database table
							//otherwise we may out-of-sync
						    m_RealtimedataNew->Requery();
							}
		     			    catch (CAxException *e)
							{
					        	AfxMessageBox(e->m_szErrorDesc, MB_OK);
				        		delete e;
							}
	OnClose();
    EndDialog(IDOK);
}

void CSafeMethod::OnCancel() 
{
	// TODO: Add extra cleanup here
	OnClose();
	CDialog::OnCancel();
}

void CSafeMethod::OnBfds() 
{
	CString strItem, strf,strc;
    CString strstartTime,strname,dddd;
			UpdateData(TRUE);           //Exchange dialog data
	int  kkkk = m_ComBoxSM.GetCurSel();
	if(kkkk == -1 || strsm == "")
	{
        AfxMessageBox("«Î—°‘Ò≤‚µ„∫Õ ‰»Î∞≤»´¥Î ©£°");
		return;
	}
	m_ComBoxSM.GetLBText(kkkk,strname);
	strname = strname.Mid(0,5);

}

/*
static void example1(const char* path)
{
	BasicExcel xls;

	 // create sheet 1 and get the associated BasicExcelWorksheet pointer
	xls.New(1);
	BasicExcelWorksheet* sheet = xls.GetWorksheet((size_t)0);

	XLSFormatManager fmt_mgr(xls);


	 // Create a table containing an header row in bold and four rows below.

	ExcelFont font_bold;
	font_bold._weight = FW_BOLD; // 700

	CellFormat fmt_bold(fmt_mgr);
	fmt_bold.set_font(font_bold);

	size_t col, row = 0;

	for(col=0; col<10; ++col) {
		BasicExcelCell* cell = sheet->Cell(row, col);

		cell->Set("TITLE");
		cell->SetFormat(fmt_bold);
	}

	while(++row < 4) {
		for(size_t col=0; col<10; ++col)
			sheet->Cell(row, col)->Set("text");
	}


	++row;

	ExcelFont font_red_bold;
	font_red_bold._weight = FW_BOLD;
	font_red_bold._color_index = EGA_RED;

	CellFormat fmt_red_bold(fmt_mgr, font_red_bold);
	fmt_red_bold.set_color1(COLOR1_PAT_SOLID);			// solid background
	fmt_red_bold.set_color2(MAKE_COLOR2(EGA_BLUE,0));	// blue background

	CellFormat fmt_green(fmt_mgr, ExcelFont().set_color_index(EGA_GREEN));

	for(col=0; col<10; ++col) {
		BasicExcelCell* cell = sheet->Cell(row, col);

		cell->Set("xxx");
		cell->SetFormat(fmt_red_bold);

		cell = sheet->Cell(row, ++col);
		cell->Set("yyy");
		cell->SetFormat(fmt_green);
	}


	xls.SaveAs(path);
}


static void example2(const char* path)
{
	BasicExcel xls;

	 // create sheet 1 and get the associated BasicExcelWorksheet pointer
	xls.New(1);
	BasicExcelWorksheet* sheet = xls.GetWorksheet((size_t)0);

	XLSFormatManager fmt_mgr(xls);

	ExcelFont font_header;
	font_header.set_weight(FW_BOLD);
	font_header.set_underline_type(EXCEL_UNDERLINE_SINGLE);
	font_header.set_font_name(L"Times New Roman");
	font_header.set_color_index(EGA_BLUE);
	font_header._options = EXCEL_FONT_STRUCK_OUT;

	CellFormat fmt_header(fmt_mgr, font_header);
	fmt_header.set_rotation(30); // rotate the header cell text 30∞ to the left

	size_t row = 0;

	for(size_t col=0; col<10; ++col) {
		BasicExcelCell* cell = sheet->Cell(row, col);

		cell->Set("TITLE");
		cell->SetFormat(fmt_header);
	}

	char buffer[100];

	while(++row < 10) {
		for(size_t col=0; col<10; ++col) {
			sprintf(buffer, "text "FMT_SIZE_T"/"FMT_SIZE_T, row, col);

			sheet->Cell(row, col)->Set(buffer);
		}
	}

	xls.SaveAs(path);
}


static void example3(const char* path)
{
	BasicExcel xls;

	 // create sheet 1 and get the associated BasicExcelWorksheet pointer
	xls.New(1);
	BasicExcelWorksheet* sheet = xls.GetWorksheet((size_t)0);

	XLSFormatManager fmt_mgr(xls);
	CellFormat fmt(fmt_mgr);
	BasicExcelCell* cell;


	 // row 1

	fmt.set_format_string(XLS_FORMAT_INTEGER);
	cell = sheet->Cell(0, 0);
	cell->Set(1.);
	cell->SetFormat(fmt);

	fmt.set_format_string(XLS_FORMAT_DECIMAL);
	cell = sheet->Cell(0, 1);
	cell->Set(2.);
	cell->SetFormat(fmt);

	fmt.set_format_string(XLS_FORMAT_DATE);
	fmt.set_font(ExcelFont().set_weight(FW_BOLD));
	cell = sheet->Cell(0, 2);
	cell->Set("03.03.2000");
	cell->SetFormat(fmt);


	 // row 2

	fmt.set_font(ExcelFont().set_weight(FW_NORMAL));
	fmt.set_format_string(XLS_FORMAT_GENERAL);
	cell = sheet->Cell(1, 0);
	cell->Set("normal");
	cell->SetFormat(fmt);

	fmt.set_format_string(XLS_FORMAT_TEXT);
	cell = sheet->Cell(1, 1);
	cell->Set("Text");
	cell->SetFormat(fmt);

	fmt.set_format_string(XLS_FORMAT_GENERAL);
	fmt.set_font(ExcelFont().set_weight(FW_BOLD));
	cell = sheet->Cell(1, 2);
	cell->Set("bold");
	cell->SetFormat(fmt);


	xls.SaveAs(path);
}


static void example_read_write(const char* from, const char* to)
{
	cout << "read " << from << endl;
	BasicExcel xls(from);

	XLSFormatManager fmt_mgr(xls);
	BasicExcelWorksheet* sheet = xls.GetWorksheet((size_t)0);

	CellFormat fmt_general(fmt_mgr);

	fmt_general.set_format_string("0.000");

	for(int y=0; y<2; ++y) {
		for(int x=0; x<2; ++x) {
			cout << y << "/" << x;

			BasicExcelCell* cell = sheet->Cell(y, x);

			CellFormat fmt(fmt_mgr, cell);

//			cout << " - xf_idx=" << cell->GetXFormatIdx();

			const Workbook::Font& font = fmt_mgr.get_font(fmt);
			string font_name = stringFromSmallString(font.name_);
			cout << "  font name: " << font_name;

			const wstring& fmt_string = fmt.get_format_string();
			cout << "  format: " << narrow_string(fmt_string);

			cell->SetFormat(fmt_general);

			cout << endl;
		}
	}

	cout << "write: " << from << endl;
	xls.SaveAs(to);
}
*/