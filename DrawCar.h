// DrawCar.h: interface for the CDrawCar class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DRAWCAR_H__49CFBD5A_5B68_4F6B_8887_6476B152BE9C__INCLUDED_)
#define AFX_DRAWCAR_H__49CFBD5A_5B68_4F6B_8887_6476B152BE9C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DrawObj.h"

class CDrawView;
class CDrawDoc;

class CDrawCar : public CDrawObj  
{
public:
	DECLARE_SERIAL(CDrawCar);
	CDrawCar();
	virtual ~CDrawCar();
	CDrawCar(const CRect& position);

public:
	virtual void Serialize(CArchive& ar);
	virtual void Draw(CDC* pDC);
///	virtual int GetHandleCount();
///	virtual CPoint GetHandle(int nHandle);
///	virtual HCURSOR GetHandleCursor(int nHandle);
///	virtual void MoveHandleTo(int nHandle, CPoint point, CDrawView* pView = NULL);
///	virtual BOOL Intersects(const CRect& rect);
///	virtual CDrawObj* Clone(CDrawDoc* pDoc);
	virtual void Remove();
	virtual void Invalidate();
///	virtual void OnEditProperties();
///	void    AddCarRect(CRect rc);
	void	DrawCarMove();
	void	DrawFill(CDC* pDc,Rect rc);
	void	StartAction();
///	CRect   GetMoveRect();
public:
	CArray<CRect,CRect> m_RectPath;			//记录的所有移动的RECT尺寸
	CarStruct	m_CarStruct;				//小车的结构
	UINT		m_nCarPaths;				//记录的路径点书
	UINT		m_nMoveStep;				//移动的步数
	UINT		m_nPointCount;				//移动的点数
	CRect		m_rectFirst;				//原始尺寸
	UINT		m_nActionRoute;				//旋转的距离
	CString     m_strPicPath;					//指定的图片存放路径
	UINT		m_nCarPathsA;				//A记录的路径点书
	UINT		m_nMoveStepA;				//移动的步数
///	CRect       m_rcMove;
};

#endif // !defined(AFX_DRAWCAR_H__49CFBD5A_5B68_4F6B_8887_6476B152BE9C__INCLUDED_)
