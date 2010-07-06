// DrawCar.h: interface for the CDrawCar class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DRAWCAR_H__49CFBD5A_5B68_4F6B_8887_6476B152BE9C__INCLUDED_)
#define AFX_DRAWCAR_H__49CFBD5A_5B68_4F6B_8887_6476B152BE9C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DrawObj.h"
#include "Enum.h"

class CDrawView;
class CDrawDoc;

class CDrawCar : public CDrawObj  
{
public:
	DECLARE_SERIAL(CDrawCar);
	CDrawCar();
	CDrawCar(const CRect& position);
	virtual ~CDrawCar();

public:
	virtual void Serialize(CArchive& ar);
	virtual void Draw(CDC* pDC);
	virtual int GetHandleCount();
	virtual CPoint GetHandle(int nHandle);
	virtual HCURSOR GetHandleCursor(int nHandle);
	virtual void MoveHandleTo(int nHandle, CPoint point, CDrawView* pView = NULL);
	virtual BOOL Intersects(const CRect& rect);
	virtual CDrawObj* Clone(CDrawDoc* pDoc);
	virtual void Remove();
	virtual void Invalidate();
	virtual void OnEditProperties();
	void    AddCarRect(CRect rc);
	void	DrawCarMove();
	void	DrawFill(CDC* pDc,Rect rc);
public:
	CArray<CRect,CRect> m_RectPath;			//��¼�������ƶ���RECT�ߴ�
	CarStruct	m_CarStruct;				//С���Ľṹ
	UINT		m_nCarPaths;				//��¼��·������
	UINT		m_nMoveStep;				//�ƶ��Ĳ���
	UINT		m_nPointCount;				//�ƶ��ĵ���
//	BOOL		m_bIsRun;					//�Ƿ�Ϊ����״̬
	CRect		m_rectAction;				//ԭʼ�ߴ�
	UINT		m_nActionRoute;				//��ת�ľ���
	CString     m_strPicPath;					//ָ����ͼƬ���·��
};

#endif // !defined(AFX_DRAWCAR_H__49CFBD5A_5B68_4F6B_8887_6476B152BE9C__INCLUDED_)
