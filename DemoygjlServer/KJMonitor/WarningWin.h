#if !defined(AFX_WARNINGWIN_H__11092BB5_EA42_4B21_93ED_057B14988E89__INCLUDED_)
#define AFX_WARNINGWIN_H__11092BB5_EA42_4B21_93ED_057B14988E89__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// WarningWin.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CWarningWin form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif
#define MAX_MESSAGE_COUNT 500
#include "FlatTab\\ColorListBox.h"
#include "SQL\\sqldirect.h"

struct structWARN{
	int ucID;//数据库标记
	int flag; //是red/green
	CString msg; //消息
	CString usDate;//时间
	BOOL bNew; //是否是新数据
};
class CWarningWin : public CFormView
{
protected:
	CWarningWin();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CWarningWin)

// Form Data
public:
	CColorListBox m_ctrlWarning1;
	CColorListBox m_ctrlWarning2;
	//{{AFX_DATA(CWarningWin)
	enum { IDD = IDD_DLG_WARNINGWIN };
	//}}AFX_DATA

// Attributes
public:

// Operations
public:
	void ReadWarnMsg();
	void AddDispWarnStr(CString strItemText, int flag);
	void RemoveOldData();
	void CloseDB();
	int GetFlag(int nIndex);
	void FlushNewData(); //添加新数据
	//void RemoveOldData(); //删除旧数据
	BOOL ConnectDB();
	void LoadWarnMsg();

	int m_RefreshDbElapse;//更新报警信息间隔,如加入10条报警信息更新一次数据库
	int m_nShowMsgCount; //显示报警信息数量
	int m_MsgCount; //报警信息数量
	void AddWarnMsg(CString strItemText,int flag); //加入报警信息,1绿色，0红色
	//CColorListBox		m_sheet1;
	//CColorListBox		m_sheet2;
	void AddDispWarnItem(int nAddDeleteInsert, CString strItemText);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWarningWin)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CWarningWin();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
	//{{AFX_MSG(CWarningWin)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	int m_innerDataID;  //更新的数据所在的行的标号,注意第二个listbox的标号是从51开始
	structWARN m_warnQue[MAX_MESSAGE_COUNT * 2];
	int m_warnNewDataLen;//等待更新进入数据库的报警数据个数
	int m_MaxWaitDelLen;  //最大的即将被删除的数据的个数
	CSQLDirect m_SQLDirect;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WARNINGWIN_H__11092BB5_EA42_4B21_93ED_057B14988E89__INCLUDED_)
