// KJ86MonitorDoc.h : interface of the CKJ86MonitorDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_KJMONITORDOC_H__982507E4_CF3C_404C_84EE_BE8A13C257B4__INCLUDED_)
#define AFX_KJMONITORDOC_H__982507E4_CF3C_404C_84EE_BE8A13C257B4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CKJMonitorDoc : public CDocument
{
protected: // create from serialization only
	CKJMonitorDoc();
	DECLARE_DYNCREATE(CKJMonitorDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CKJ86MonitorDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CKJMonitorDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CKJ86MonitorDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_KJ86MONITORDOC_H__982507E4_CF3C_404C_84EE_BE8A13C257B4__INCLUDED_)
