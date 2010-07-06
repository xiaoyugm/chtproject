// DrawConduit.h: interface for the CDrawConduit class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DRAWCONDUIT_H__75A68878_E649_49A3_9F00_2052BAE3D35C__INCLUDED_)
#define AFX_DRAWCONDUIT_H__75A68878_E649_49A3_9F00_2052BAE3D35C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DrawObj.h"
#include "Enum.h"

class CDrawView;
class CDrawDoc;
/////////////////////////////////////////////////////////////////////////////

class CDrawConduit : public CDrawObj
{
protected:
	DECLARE_SERIAL(CDrawConduit);
	CDrawConduit();

public:
	CDrawConduit(const CRect& position);

// Operations
	void AddPoint(const CPoint& point, CDrawView* pView = NULL);
	BOOL RecalcBounds(CDrawView* pView = NULL);

// Implementation
public:
	virtual ~CDrawConduit();
	virtual void	Serialize(CArchive& ar);
	virtual void	Draw(CDC* pDC);
	virtual void	MoveTo(const CRect& position, CDrawView* pView = NULL);
	virtual int		GetHandleCount();
	virtual CPoint	GetHandle(int nHandle);
	virtual HCURSOR GetHandleCursor(int nHandle);
	virtual void	MoveHandleTo(int nHandle, CPoint point, CDrawView* pView = NULL);
	virtual BOOL	Intersects(const CRect& rect);
	virtual CDrawObj* Clone(CDrawDoc* pDoc);
	virtual void	OnEditProperties();
			
	BOOL	StartAction();					//开始动作

public:
	int			m_nPoints;
	int			m_nAllocPoints;
	CPoint*		m_points;
	CDrawConduit* m_pDrawObj;
	CArray<POINT, POINT> m_CurvePoints;

	ConduitStruct	m_ConduitStruct;
	BOOL		m_bIsShowMove;


//	friend class CPolyTool;
};

#endif // !defined(AFX_DRAWCONDUIT_H__75A68878_E649_49A3_9F00_2052BAE3D35C__INCLUDED_)
