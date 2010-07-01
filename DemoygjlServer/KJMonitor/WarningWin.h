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
	int ucID;//���ݿ���
	int flag; //��red/green
	CString msg; //��Ϣ
	CString usDate;//ʱ��
	BOOL bNew; //�Ƿ���������
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
	void FlushNewData(); //���������
	//void RemoveOldData(); //ɾ��������
	BOOL ConnectDB();
	void LoadWarnMsg();

	int m_RefreshDbElapse;//���±�����Ϣ���,�����10��������Ϣ����һ�����ݿ�
	int m_nShowMsgCount; //��ʾ������Ϣ����
	int m_MsgCount; //������Ϣ����
	void AddWarnMsg(CString strItemText,int flag); //���뱨����Ϣ,1��ɫ��0��ɫ
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
	int m_innerDataID;  //���µ��������ڵ��еı��,ע��ڶ���listbox�ı���Ǵ�51��ʼ
	structWARN m_warnQue[MAX_MESSAGE_COUNT * 2];
	int m_warnNewDataLen;//�ȴ����½������ݿ�ı������ݸ���
	int m_MaxWaitDelLen;  //���ļ�����ɾ�������ݵĸ���
	CSQLDirect m_SQLDirect;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WARNINGWIN_H__11092BB5_EA42_4B21_93ED_057B14988E89__INCLUDED_)
