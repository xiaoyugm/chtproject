// DrawCar.cpp: implementation of the CDrawCar class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "GUI_VisualStudio.h"
#include "DrawCar.h"
#include "DrawDoc.h"
#include <math.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

extern CPointInfo m_CPointInfo[MAX_POINT_NUMBER];
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
}

CDrawCar::~CDrawCar()
{
	if(m_RectPath.GetSize() > 0)
	{
		m_RectPath.RemoveAll();
	}
///	Remove();
}

void CDrawCar::Serialize(CArchive& ar)
{
	ASSERT_VALID(this);

	CDrawObj::Serialize(ar);
	m_RectPath.Serialize(ar);
	if (ar.IsStoring())
	{
	}
	else
	{
		ar.Read(&m_CarStruct,sizeof(CarStruct));
		ar >> m_strPicPath;

		m_nCarPaths = 0;
		m_nCarPathsA = 0;
		m_nMoveStep = 0;
		m_nMoveStepA = 0;
		m_nPointCount = m_RectPath.GetSize();
		
		CRect rect = m_RectPath.GetAt(0);
		m_position = rect;
		m_rectFirst = m_position;
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
	Normallize(GdiRect);				//����ת��
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

	if(m_nActionRoute != 0)
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

	if(m_strPicPath.GetLength() < 3)
	{
		graphics.FillRectangle(&solidBrush,rc);
		graphics.DrawRectangle(&pen,rc);
	}
	else
	{	
        		BSTR strPicPath = m_strPicPath.AllocSysString();
///		BSTR strPicPath = _com_util::ConvertStringToBSTR(m_strPicPath);
		Image m_pimage(strPicPath);
       	SysFreeString(strPicPath);
       	m_pimage.RotateFlip(Rotate180FlipX);
		graphics.DrawImage(&m_pimage, rc);
		graphics.DrawRectangle(&pen,rc);
	}
	graphics.ReleaseHDC(pDC->m_hDC);
}
/*
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

	ASSERT_VALID(pClone);           HINT_UPDATE_WINDOW
	return pClone;
}
*/
void CDrawCar::Invalidate()
{
	ASSERT_VALID(this);
///	if(m_nActionRoute ==0)          
///    	m_pDocument->UpdateAllViews(NULL, HINT_UPDATE_DRAWOBJ, this);
///	else
///		m_pDocument->UpdateAllViews(NULL, HINT_UPDATE_CAR, this);
		m_pDocument->UpdateAllViews(NULL, HINT_UPDATE_WINDOW, this);
}
/*
void CDrawCar::AddCarRect(CRect rc)
{
	ASSERT_VALID(this);

	m_RectPath.Add(rc);
	m_pDocument->SetModifiedFlag();

}

void CDrawCar::OnEditProperties()
{
	ASSERT_VALID(this);
	Invalidate();
	m_pDocument->SetModifiedFlag();
}
*/
//��С�����˶�
void CDrawCar::DrawCarMove()
{
	int nSize = m_nPointCount;
	CRect rect = m_rectFirst;
	if(nSize < 1)
	{
		return;
	}

	if(m_nCarPaths >= nSize-1)				//ȷ��Ŀ��ԭʼλ�����ĵ�Ϊ��¼��ĵ�һ����nSize-1
	{
		m_nCarPaths = 0;
		m_nActionRoute = 0;
///		m_ActionStruct.stcRotary.ReferencePoint = CENTER;
		m_position = m_RectPath.GetAt(nSize-1);
///    	Invalidate();
		return;
	}

	m_rectAction = m_RectPath.GetAt(m_nCarPaths);
	
	CPoint  ptStart, ptEnd;					//ÿ������·���Ŀ�ʼ����������
	CRect   EndRect;
	ptStart = m_RectPath.GetAt(m_nCarPaths).CenterPoint();
	EndRect = m_RectPath.GetAt(m_nCarPaths+1);
	if(m_nCarPaths < nSize - 1)
		ptEnd = m_RectPath.GetAt(m_nCarPaths+1).CenterPoint();
	else
		ptEnd = ptStart;	
	
	double nMoveLen ,nXlen ,nYlen;	                	//��������·���ĳ�
       	  nXlen = (ptStart.x - ptEnd.x);	//ÿ��·������X���곤    abs
	      nYlen = (ptStart.y - ptEnd.y);	//ÿ��·������Y���곤
	      nMoveLen = sqrt(nXlen*nXlen + nYlen*nYlen);		//������
	double nAngle = (atan(nXlen/nYlen))*180/3.14159265;		//����ʱ�ĽǶ�
	
	if(nMoveLen == 0)
	{
		m_nMoveStep = 0;
		m_nCarPaths++;
		return;
	}

	double nXSinAngle = nXlen / nMoveLen;
	double nYSinAngle = nYlen / nMoveLen;

	if(ptEnd.x > ptStart.x && ptEnd.y < ptStart.y )      
		m_nActionRoute = 270 - nAngle   ;
	if(ptEnd.x < ptStart.x && ptEnd.y > ptStart.y )
		m_nActionRoute = 270 - nAngle;
	if(ptEnd.x > ptStart.x && ptEnd.y > ptStart.y )      
		m_nActionRoute = 90 - nAngle;
	if(ptEnd.x < ptStart.x && ptEnd.y < ptStart.y )
		m_nActionRoute = 90 - nAngle;

///	m_ActionStruct.stcRotary.ReferencePoint = CENTER;		//ȷ��Ŀ��Χ�����ĵ���ת
	
	double MoveX = (m_nMoveStep * m_CarStruct.nSpeed) * nXSinAngle;		//�������е�X���곤���ۼƣ�
	double MoveY= (m_nMoveStep * m_CarStruct.nSpeed) * nYSinAngle;		//�������е�Y���곤���ۼƣ�
	double len = sqrt((MoveX)*(MoveX) + (MoveY)*(MoveY));				//�������еĳ��ȣ��ۼƣ�
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
		m_position.left = ptCenter.x - rect.Width()/2;		//�����ƶ��������ػ�Ŀ��
		m_position.top = ptCenter.y-rect.Height()/2;
		m_position.right = ptCenter.x + rect.Width()/2;
		m_position.bottom = ptCenter.y+rect.Height()/2;

		m_nMoveStep++;
	}
	else
	{
		m_nMoveStep = 0;
		m_nCarPaths++;
	}
	Invalidate();
}
//ģ����
void CDrawCar::StartAction()
{
	int nSize = m_nPointCount;
	CRect rect = m_rectFirst;
	if(nSize < 1)
		return;

	int pnValue = m_CPointInfo[m_CarStruct.nPoint].pnValue *100 ;
	if( pnValue == 0 )				//ȷ��Ŀ��ԭʼλ�����ĵ�Ϊ��¼��ĵ�һ����
	{
		m_nCarPaths = 0;
		m_nActionRoute = 0;
///		m_ActionStruct.stcRotary.ReferencePoint = CENTER;
		m_position = m_RectPath.GetAt(0);
		return;
	}

	CPoint  ptStart, ptEnd, ptCenter;					//ÿ������·���Ŀ�ʼ����������
    	double nMoveLen ,nXlen ,nYlen ,nMoveLenV,nMoveLenL ,MoveV,nAngle ,nMoveLenH ,MoveVH;
		nMoveLen =nXlen=nYlen =nMoveLenV=nMoveLenL=MoveV=nAngle =nMoveLenH=MoveVH= 0.0;

	for(int j=0; j< (nSize-1);j++)
	{
    	ptStart = m_RectPath.GetAt(j).CenterPoint();
		ptEnd = m_RectPath.GetAt(j+1).CenterPoint();
    	  nXlen = (ptStart.x - ptEnd.x);	//ÿ��·������X���곤    abs
	      nYlen = (ptStart.y - ptEnd.y);	//ÿ��·������Y���곤
	     nMoveLenL += sqrt(nXlen*nXlen + nYlen*nYlen) ;	
	}
	     nMoveLenV = nMoveLenL * m_CPointInfo[m_CarStruct.nPoint].pnValue ;		//ģ����
	for(int k=0; k< (nSize-1);k++)
	{
       	ptStart = m_RectPath.GetAt(k).CenterPoint();
		ptEnd = m_RectPath.GetAt(k+1).CenterPoint();
    	  nXlen = (ptStart.x - ptEnd.x);	//ÿ��·������X���곤    abs
	      nYlen = (ptStart.y - ptEnd.y);	//ÿ��·������Y���곤
	     nMoveLenH += sqrt(nXlen*nXlen + nYlen*nYlen) ;	
		 if(nMoveLenH >= nMoveLenV)
		 {
	         MoveV = nMoveLenH - nMoveLenV  ;		//ģ����
			 m_nCarPathsA = k ;
			 break ;
		 }
	}

	m_nMoveStepA = 0;
	for(int i=0; i <= m_nCarPathsA ;i++)
	{
    	ptStart = m_RectPath.GetAt(i).CenterPoint();
     	ptEnd = m_RectPath.GetAt(i+1).CenterPoint();
        nXlen = (ptStart.x - ptEnd.x);	//ÿ��·������X���곤    abs
        nYlen = (ptStart.y - ptEnd.y);	//ÿ��·������Y���곤
        nMoveLen = sqrt(nXlen*nXlen + nYlen*nYlen) ;		
        MoveVH = nMoveLen       ;		//·����
    	nAngle = (atan(nXlen/nYlen))*180/3.14159265;		//����ʱ�ĽǶ�
	
		if(nMoveLen != 0)
		{
    		if(i == (m_nCarPathsA))
        	      MoveVH = nMoveLen - MoveV  ;		//ģ����

         	double nXSinAngle = nXlen / nMoveLen;
        	double nYSinAngle = nYlen / nMoveLen;

        	if(ptEnd.x > ptStart.x && ptEnd.y < ptStart.y )      
            		m_nActionRoute = 270 - nAngle   ;
         	if(ptEnd.x < ptStart.x && ptEnd.y > ptStart.y )
            		m_nActionRoute = 270 - nAngle;
         	if(ptEnd.x > ptStart.x && ptEnd.y > ptStart.y )      
	            	m_nActionRoute = 90 - nAngle;
        	if(ptEnd.x < ptStart.x && ptEnd.y < ptStart.y )
            		m_nActionRoute = 90 - nAngle;

///          	m_ActionStruct.stcRotary.ReferencePoint = CENTER;		//ȷ��Ŀ��Χ�����ĵ���ת
	
			for( m_nMoveStepA=0; m_nMoveStepA <= 1000 ;m_nMoveStepA++)
			{
            	double MoveX = (m_nMoveStepA * m_CarStruct.nSpeed) * nXSinAngle;		//�������е�X���곤���ۼƣ�
                double MoveY= (m_nMoveStepA * m_CarStruct.nSpeed) * nYSinAngle;		//�������е�Y���곤���ۼƣ�
            	double len = sqrt((MoveX)*(MoveX) + (MoveY)*(MoveY));				//�������еĳ��ȣ��ۼƣ�
            	if(len < MoveVH)
				{
            		ptCenter = ptStart;
	            	if(ptEnd.x > ptStart.x)
	            		ptCenter.x += abs(MoveX);
	            	else
	             		ptCenter.x -= abs(MoveX);
	             	if(ptEnd.y > ptStart.y)
	             		ptCenter.y += abs(MoveY);
	            	else
	            		ptCenter.y -= abs(MoveY);
	            	m_position.left = ptCenter.x - rect.Width()/2;		//�����ƶ��������ػ�Ŀ��
	             	m_position.top = ptCenter.y-rect.Height()/2;
	            	m_position.right = ptCenter.x + rect.Width()/2;
	            	m_position.bottom = ptCenter.y+rect.Height()/2;
				}
            	else
				{
            		m_nMoveStepA = 0;
	     			break ;
				}
			}
		}
	}
	Invalidate();
}
/*
CRect CDrawCar::GetMoveRect()
{
	m_rcMove.NormalizeRect();
	int nWidth = m_rcMove.Width() ;
	int nHeight = m_rcMove.Height() ;

	m_rcMove.left -= nWidth;
	m_rcMove.right += nWidth;
	m_rcMove.top -= nHeight;
	m_rcMove.bottom += nHeight;

	return m_rcMove;

}*/
