// DrawRotary.h: interface for the CDrawRotary class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DRAWROTARY_H__733301A9_74AB_4519_9AEB_2564863E0688__INCLUDED_)
#define AFX_DRAWROTARY_H__733301A9_74AB_4519_9AEB_2564863E0688__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DrawObj.h"

class CDrawView;
class CDrawDoc;

class CDrawRotary : public CDrawObj  
{
public:
	DECLARE_SERIAL(CDrawRotary);
	CDrawRotary();
	virtual ~CDrawRotary();
	CDrawRotary(const CRect& position);
public:
	virtual void	Serialize(CArchive& ar);
	virtual void	Draw(CDC* pDC);
///	virtual int		GetHandleCount();
///	virtual CPoint	GetHandle(int nHandle);
///	virtual HCURSOR GetHandleCursor(int nHandle);
///	virtual void	MoveHandleTo(int nHandle, CPoint point, CDrawView* pView = NULL);
///	virtual BOOL	Intersects(const CRect& rect);
///	virtual CDrawObj* Clone(CDrawDoc* pDoc);
///	virtual void	Remove();
///	virtual void Invalidate();
///	virtual void OnEditProperties();
	void    StartAction();
public:
	RotaryStruct    m_RotaryStruct;
	BOOL			m_bIsAction;			//是否有动作产生
};

#endif // !defined(AFX_DRAWROTARY_H__733301A9_74AB_4519_9AEB_2564863E0688__INCLUDED_)
