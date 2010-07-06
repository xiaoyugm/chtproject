// DrawCar.cpp: implementation of the CDrawCar class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Draw.h"
#include "DrawCar.h"
#include "DrawDoc.h"
#include <math.h>
#include "CarSetDlg.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
IMPLEMENT_SERIAL(CDrawCar, CDrawObj, 0)
CDrawCar::CDrawCar()
{

}

CDrawCar::CDrawCar(const CRect& position)
	: CDrawObj(position)
{
	ASSERT_VALID(this);
///	m_bIsRun	= FALSE;
	m_CarStruct.clrLineColor = m_clrLineColor;
	m_CarStruct.clrFillColor = m_clrFillColor;
}

CDrawCar::~CDrawCar()
{
	if(m_RectPath.GetSize() > 0)
	{
		m_RectPath.RemoveAll();
	}
}

void CDrawCar::Serialize(CArchive& ar)
{
	ASSERT_VALID(this);

	CDrawObj::Serialize(ar);
	m_RectPath.Serialize(ar);
	if (ar.IsStoring())
	{
		ar.Write(&m_CarStruct,sizeof(CarStruct));
		ar<< m_strPicPath;
	}
	else
	{
//		WORD wTemp;
		ar.Read(&m_CarStruct,sizeof(CarStruct));
		ar >> m_strPicPath;

		m_nCarPaths = 0;
		m_nMoveStep = 0;
		m_nPointCount = m_RectPath.GetSize();
/*		if(m_bIsRun)
		{
			CRect rect = m_RectPath.GetAt(0);
			m_position = rect;
			m_rectAction = m_position;
		}*/
	}
}

void CDrawCar::Remove()
{
	delete this;
}

void CDrawCar::Draw(CDC* pDC)
{
	ASSERT_VALID(this);

	CRect rect = m_position;
	rect.NormalizeRect();
	Rect GdiRect (rect.TopLeft().x,rect.TopLeft().y,rect.Size().cx,rect.Size().cy); 
	
	Normallize(GdiRect);				//坐标转换
	
///	if(m_bIsRun)                   //0415
///	{
///		DrawCarMove();
///	}
///	else
	{
		Color  MoveLineColor(200,0,0,200);
		Pen pen(MoveLineColor,1);
		Graphics graphics(pDC->m_hDC);
		int nPoint = m_RectPath.GetSize();
		PointF *points = new PointF[nPoint+1];
		
		for (int i=0;i<nPoint;i++)
		{
			points[i].X = m_RectPath.GetAt(i).CenterPoint().x;
			points[i].Y = m_RectPath.GetAt(i).CenterPoint().y;
		}
		
		points[0].X++;
		points[0].Y++;
		
		graphics.DrawLines(&pen, points, nPoint);
	}

	DrawFill(pDC, GdiRect);
	
}

void CDrawCar::DrawFill(CDC *pDC, Rect rc)
{
	Color clrLineColor, clrFillColor;
	clrLineColor.SetFromCOLORREF(m_CarStruct.clrLineColor);
	clrFillColor.SetFromCOLORREF(m_CarStruct.clrFillColor);
	
	Pen pen(clrLineColor, 1);
	SolidBrush solidBrush(clrFillColor); 
	Graphics graphics(pDC->m_hDC);

/*	if(m_nActionRoute != 0)           //0415
	{
		CRect rcRoute = m_position;
		rcRoute.NormalizeRect();
		PointF ptF;
		ptF.X = rcRoute.CenterPoint().x;
		ptF.Y = rcRoute.CenterPoint().y;
		Matrix transformMatrix;
		transformMatrix.RotateAt(m_nActionRoute,ptF);

		graphics.SetTransform(&transformMatrix);

	}
*/
	if(m_strPicPath.IsEmpty())
	{
		graphics.FillRectangle(&solidBrush,rc);
		graphics.DrawRectangle(&pen,rc);
	}
	else
	{	
		BSTR strPicPath = _com_util::ConvertStringToBSTR(m_strPicPath);
		Image m_pimage(strPicPath);
       	m_pimage.RotateFlip(Rotate180FlipX);
		graphics.DrawImage(&m_pimage, rc);
		graphics.DrawRectangle(&pen,rc);
	}
	graphics.ReleaseHDC(pDC->m_hDC);
}

int CDrawCar::GetHandleCount()
{
	ASSERT_VALID(this);
	return CDrawObj::GetHandleCount();
}

// returns center of handle in logical coordinates
CPoint CDrawCar::GetHandle(int nHandle)
{
	ASSERT_VALID(this);
	return CDrawObj::GetHandle(nHandle);
}

HCURSOR CDrawCar::GetHandleCursor(int nHandle)
{
	ASSERT_VALID(this);
	return CDrawObj::GetHandleCursor(nHandle);
}

void CDrawCar::MoveHandleTo(int nHandle, CPoint point, CDrawView* pView)
{
	ASSERT_VALID(this);
	CDrawObj::MoveHandleTo(nHandle, point, pView);
}

BOOL CDrawCar::Intersects(const CRect& rect)
{
	ASSERT_VALID(this);

	CRect rectT = rect;
	rectT.NormalizeRect();

	CRect fixed = m_position;
	fixed.NormalizeRect();
	if ((rectT & fixed).IsRectEmpty())
		return FALSE;
	return TRUE;
}

CDrawObj* CDrawCar::Clone(CDrawDoc* pDoc)
{
	ASSERT_VALID(this);

	CDrawCar* pClone = new CDrawCar(m_position);

	ASSERT_VALID(pClone);

	if (pDoc != NULL)
		pDoc->Add(pClone);

	ASSERT_VALID(pClone);
	return pClone;
}

void CDrawCar::Invalidate()
{
	ASSERT_VALID(this);
	CDrawObj::Invalidate();
}

void CDrawCar::AddCarRect(CRect rc)
{
	ASSERT_VALID(this);

	m_RectPath.Add(rc);
	m_pDocument->SetModifiedFlag();

}

void CDrawCar::OnEditProperties()
{
	ASSERT_VALID(this);
	CCarSetDlg dlg;
	dlg.m_clrFillColor	= m_CarStruct.clrFillColor;
	dlg.m_clrLineColor	= m_CarStruct.clrLineColor;
	dlg.m_nPointNo		= m_CarStruct.nPoint;
	dlg.m_nSpeed		= m_CarStruct.nSpeed;
	dlg.m_strPath		= m_strPicPath;
	if(dlg.DoModal() != IDOK)
		return;
	m_CarStruct.clrFillColor	= dlg.m_clrFillColor;
	m_CarStruct.clrLineColor	= dlg.m_clrLineColor;
	m_CarStruct.nPoint			= dlg.m_nPointNo;
	m_CarStruct.nSpeed			= dlg.m_nSpeed;
	m_strPicPath	        	= dlg.m_strPath;

	Invalidate();
	m_pDocument->SetModifiedFlag();
}

//画小车的运动
void CDrawCar::DrawCarMove()
{
	unsigned int nSize = m_nPointCount;
	CRect rect = m_rectAction;

	if(nSize < 1)
	{
		return;
	}

	if(m_nCarPaths >= (nSize-1))				//确定目标原始位置中心点为记录点的第一个点
	{
		m_nActionRoute = 0;
		m_position = m_RectPath.GetAt(nSize-1);
		return;
	}
	
	CPoint  ptStart, ptEnd;					//每个运行路径的开始与结束坐标点
	CRect   EndRect;
	ptStart = m_RectPath.GetAt(m_nCarPaths).CenterPoint();
	EndRect = m_RectPath.GetAt(m_nCarPaths+1);
	if(m_nCarPaths < (nSize-1))
		ptEnd = m_RectPath.GetAt(m_nCarPaths+1).CenterPoint();
	else
		ptEnd = ptStart;	
	
	double nXlen = abs(ptStart.x - ptEnd.x);	//每个路径运行X坐标长
	double nYlen = abs(ptStart.y - ptEnd.y);	//每个路径运行Y坐标长
	double nMoveLen = sqrt(nXlen*nXlen + nYlen*nYlen);		//整个运行路径的长
	double nAngle = (atan(nXlen/nYlen))*180/3.14159265;		//运行时的角度
	
	double nXSinAngle = nXlen / nMoveLen;
	double nYSinAngle = nYlen / nMoveLen;

	if(ptEnd.x > ptStart.x && ptEnd.y < ptStart.y )
		m_nActionRoute = nAngle;
	if(ptEnd.x < ptStart.x && ptEnd.y > ptStart.y )
		m_nActionRoute = 180+nAngle;
	if(ptEnd.x > ptStart.x && ptEnd.y > ptStart.y )
		m_nActionRoute = 180-nAngle;
	if(ptEnd.x < ptStart.x && ptEnd.y < ptStart.y )
		m_nActionRoute = 180-nAngle;

	
	double MoveX = (m_nMoveStep * m_CarStruct.nSpeed) * nXSinAngle;		//单步运行的X坐标长（累计）
	double MoveY= (m_nMoveStep * m_CarStruct.nSpeed) * nYSinAngle;		//单步运行的Y坐标长（累计）
	double len = sqrt((MoveX)*(MoveX) + (MoveY)*(MoveY));				//单步运行的长度（累计）
	if(len < nMoveLen)
	{
		CPoint ptCenter = ptStart;
		if(ptEnd.x > ptStart.x)
			ptCenter.x += abs(MoveX);
		else
			ptCenter.x -= abs(MoveX);
		if(ptEnd.y > ptStart.y)
			ptCenter.y += abs(MoveY);
		else
			ptCenter.y -= abs(MoveY);
		m_position.left = ptCenter.x - rect.Width()/2;		//计算移动的区域重画目标
		m_position.top = ptCenter.y-rect.Height()/2;
		m_position.right = ptCenter.x + rect.Width()/2;
		m_position.bottom = ptCenter.y+rect.Height()/2;
		
		m_nMoveStep++;
	}
	else
	{
		m_nMoveStep = 0;
		m_nCarPaths++;
		m_nActionRoute = 0;
	}
}
