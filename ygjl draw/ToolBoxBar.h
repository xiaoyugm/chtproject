// ToolBoxBar.h: interface for the CToolBoxBar class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TOOLBOXBAR_H__E542DF03_6EDE_4F1A_95AD_C0540A40B283__INCLUDED_)
#define AFX_TOOLBOXBAR_H__E542DF03_6EDE_4F1A_95AD_C0540A40B283__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CToolBoxBar : public CXTToolBar
{
	DECLARE_DYNAMIC(CToolBoxBar)

// Construction / destruction
public:

	// Constructs a CToolBoxBar object.
	CToolBoxBar();

	// Destroys a CToolBoxBar object, handles cleanup and de-allocation.
	virtual ~CToolBoxBar();

// Member variables
protected:
	UINT m_nColumns;

// Member functions
public:
	void SetColumns(UINT nColumns);
	UINT GetColumns() const;

	//{{AFX_VIRTUAL(CToolBoxBar)
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CToolBoxBar)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#endif // !defined(AFX_TOOLBOXBAR_H__E542DF03_6EDE_4F1A_95AD_C0540A40B283__INCLUDED_)
