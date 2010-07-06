// DrawChart.h: interface for the CDrawChart class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DRAWCHART_H__0129F3CE_D69F_4194_BB21_AE438A8DAD58__INCLUDED_)
#define AFX_DRAWCHART_H__0129F3CE_D69F_4194_BB21_AE438A8DAD58__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DrawObj.h"
#include <mmsystem.h>

#include <RealTime.h>
#pragma comment(lib,"CurveT.lib")

class CDrawView;
class CDrawDoc;

class CDrawChart : public CDrawObj  
{
public:
	DECLARE_SERIAL(CDrawChart);
	CDrawChart();
	virtual ~CDrawChart();

public:
	CDrawChart(const CRect& position);
public:
	virtual void Serialize(CArchive& ar);
	virtual void Draw(CDC* pDC);
	virtual int GetHandleCount();
	virtual CPoint GetHandle(int nHandle);
	virtual HCURSOR GetHandleCursor(int nHandle);
	virtual void MoveHandleTo(int nHandle, CPoint point, CDrawView* pView = NULL);
	virtual BOOL Intersects(const CRect& rect);
	virtual CDrawObj* Clone(CDrawDoc* pDoc);
	virtual void OnEditProperties();

	void OnTimer();						//ʱ����Ϣ
	BOOL StartRealTime();				//��ʼ����ʵʱ����
	void Init();						//��ʼ��

public:
	CRealTime	m_Graph;					//ʵʱ������
	DWORD		m_nStartTime;				//��ʼʱ��
	UINT		m_nTimeSpan;				//ʱ��粽
	DWORD		MaxSeconds;					//�������
	double		CyclesPerSec;		

	int			SpeedLevel;					//�ٶ�

	COLORREF	m_ctlBackColor;				//������ɫ
	int			nMinx,nMiny,nMaxx,nMaxy;	//ȡֵ��Χ
	COLORREF    m_clrLine1,					//������ɫ
				m_clrLine2,
				m_clrLine3,
				m_clrLine4;

	
	BOOL        m_IsRealTime;
	BOOL		m_bTimeOn;
	BOOL		m_nIsStartRealTime;
	BOOL		CanTicks;
	WORD		m_nTicks;
	DWORD		CurrentTime;
	DWORD		mSec;
	UINT		nTimerIDChart;
	UINT		m_nPoint1,m_nPoint2,m_nPoint3,m_nPoint4;
};

#endif // !defined(AFX_DRAWCHART_H__0129F3CE_D69F_4194_BB21_AE438A8DAD58__INCLUDED_)
