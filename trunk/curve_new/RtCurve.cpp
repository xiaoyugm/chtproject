#include "stdafx.h"
#include "RtCurve.h"
#include "SqlDirect.h"
#include "String2DataType.h"
#include "math.h"
//#include "SystemData.h"

#pragma warning (disable : 4244 4018)
IMPLEMENT_SERIAL(CRtCurve,CGraphic,1)

CRtCurve::CRtCurve()
{
	m_colorPen = RGB(0,0,0);     //0126
	m_colorBrush = RGB(0,0,0);
	m_pointArray.SetSize(2);
///	m_nNo = RTCURVE;
	m_nTime = 0;
	m_bModify = TRUE;
	m_colorLabel = RGB(255,0,0);   //25500
//	m_nStartTick = 0;
	m_bHistory = FALSE;
	memset(m_value,-1,sizeof(unsigned short)*CURVENUM);
	memset(m_curveYear,-1,sizeof(int)*CURVENUM);
	memset(m_curveMonth,-1,sizeof(int)*CURVENUM);
	memset(m_curveDay,-1,sizeof(int)*CURVENUM);
	memset(m_curveHour,-1,sizeof(int)*CURVENUM);
	memset(m_curveMinute,-1,sizeof(int)*CURVENUM);
	memset(m_curveSecond,-1,sizeof(int)*CURVENUM);
	memset(m_curveProp,0,sizeof(CURVEPROP)*CURVENUM);
	m_PointOld.x = CURVEBORDER;
	m_clientSize.cx = 0 ;
	m_clientSize.cy = 0 ;
	m_curCursorPos.x = 0;
	m_curCursorPos.y = 0;
	m_curPointIndex = 0;
	m_nZoom = 0;
	m_sStartSecond = 0;
	m_sEndSecond = 0;
    m_sCheckGrid = FALSE;
}

void CRtCurve::Serialize(CArchive &ar)
{
	m_pointArray.Serialize(ar);
	for(int i=0; i<CURVENUM; i++)
		m_curveData[i].Serialize(ar);
	if(ar.IsStoring())
	{
		ar << m_curveProp[i].Standard;
//		ar << m_nStandard;
		ar << m_rect;
		ar << m_colorLabel;
		ar << m_nTime;
		ar << m_bHistory;
		ar << m_strStartDate;
		ar << m_strEndDate;
		ar << m_sStartHour;
		ar << m_sEndHour;
		ar << m_sStartMin;     //0115
		ar << m_sEndMin;

		ar << m_sCheckGrid;
		ar << m_colorPen;     //0115
		ar << m_colorBrush;

		ar.Write(m_curveProp,sizeof(CURVEPROP)*CURVENUM);
	}
	else
	{
		ar >> m_curveProp[i].Standard;
//		ar >> m_nStandard;
		ar >> m_rect;
		ar >> m_colorLabel;
		ar >> m_nTime;
		ar >> m_bHistory;
		ar >> m_strStartDate;
		ar >> m_strEndDate;
		ar >> m_sStartHour;
		ar >> m_sEndHour;
		ar >> m_sStartMin;    //0115
		ar >> m_sEndMin;

		ar >> m_sCheckGrid;
		ar >> m_colorPen;    //0115
		ar >> m_colorBrush;

		ar.Read(m_curveProp,sizeof(CURVEPROP)*CURVENUM);
	}
	CGraphic::Serialize(ar);
}

void CRtCurve::Draw(CDC *pDC)
{
	if(m_bModify) //&& !m_bHistory)
	{
		SetRtRect();
		m_bModify = FALSE;
	}
	else if(m_bHistory)
		SetRtRect();
	
	CPen   pen(PS_SOLID,m_nPenWidth,m_colorPen);
	CBrush brush(m_colorBrush);
	CBrush *pOldBrush = pDC->SelectObject(&brush);
	CPen   *pOldPen = pDC->SelectObject(&pen);
	pDC->Rectangle(m_pointArray[0].x,m_pointArray[0].y,m_pointArray[1].x,m_pointArray[1].y);
	pDC->SelectObject(pOldPen);
	pDC->SelectObject(pOldBrush);   //0126
//	graphics.FillRectangle(&BGBrush,m_pointArray[0].x,m_pointArray[0].y,m_pointArray[1].x,m_pointArray[1].y);
	
	CRect rect = GetRealRect();
	CRect tmpRect = rect;
	tmpRect.left = CURVEBORDER;
	tmpRect.top = CURVEBORDER;
	tmpRect.bottom = rect.bottom ;
	if(m_bHistory)
		rect.right -= CURVEBORDER;

	int width = rect.right - rect.left;
	int height = rect.bottom - rect.top;
	if(width < CURVEBORDER*2 || height < CURVEBORDER*2 )
		return;

	int i,xinter,yinter,xvalue,value;
	double value1;
	CString text;

	CRect rectText;
	rectText.top = rect.top - CURVEBORDER;
	rectText.left = rect.left;
	rectText.right = rect.left + CURVEBORDER;
	rectText.bottom = rect.top + 20;
	xinter = (width - CURVEBORDER*2) / CURVELINETIME;
	yinter = (height - CURVEBORDER*2) / CURVELINE;

	xvalue = (int)((m_nTime / CURVELINETIME)*1.0 );
	if(xvalue < 1)
		xvalue = 1;
//	yvalue = m_nStandard / CURVELINE;yvalue
	
	CPen *pOldPenline;        /*penline,*/
	//penline.CreatePen(PS_SOLID,2,RGB(0,0,0));
///	pen.CreatePen(PS_SOLID,1,RGB(0,0,0));
	//	pOldPen = pDC->SelectObject(&pen);
	pDC->SetTextColor(m_colorLabel);
	CFont  font;
	font.CreateFont(15,5,0,0,FW_NORMAL,0,0,0,ANSI_CHARSET,0,0,0,0,"Times New Roman");  //13,6
	CFont *pOldFont = pDC->SelectObject(&font);    //0126
	int oldmode = pDC->SetBkMode(TRANSPARENT);
	int bkmode;

////////////////////画网格/////////////////////////////////////////
	if((m_nZoom == 0) ){
		GetDate(aYear,aMonth,aDay,m_strStartDate);
        aHour = (int)m_sStartHour ;
        aMinute = (int)m_sStartMin ;
        aSecond = (int)m_sStartSecond ;
	}
    CTime time(aYear,aMonth,aDay,aHour,aMinute,aSecond);
	CTimeSpan span(0,0,0,xvalue);

	for(i=0; i<=CURVELINETIME; i++)
	{
		value = xvalue * i;
		/////时间///////////////
			if(m_nTime == 0)
				time += span;
		text.Format("%02d:%02d:%02d:%02d",time.GetDay(),time.GetHour(),time.GetMinute(),time.GetSecond());
		rectText.top = rect.bottom - CURVEBORDER;
		rectText.bottom = rect.bottom;
		rectText.left = rect.left + CURVEBORDER + xinter*i;
		rectText.right = rectText.left + 60;
		//	pDC->ExtTextOut(rectText.left,rectText.top,ETO_CLIPPED,rectText,text,NULL);
		CRect tmp = rectText;
		tmp.left -= 11;
		tmp.right -= 11;
		pDC->DrawText(text,tmp,DT_LEFT|DT_BOTTOM);
		time += span;
		
		bkmode = pDC->SetROP2(R2_NOT);	
		
		//////////////竖线///////////////////R2_NOT
		if(i == 0)
		{
			CPen mypen(PS_SOLID,1,RGB(255,0,0));
			pOldPenline = pDC->SelectObject(&mypen);
			pDC->MoveTo(CURVEBORDER,CURVEBORDER + 4);  //3
			pDC->LineTo(CURVEBORDER,rect.bottom - CURVEBORDER );
			pDC->SelectObject(pOldPenline);
	//		graphics.DrawLine(&LinePen,CURVEBORDER,CURVEBORDER,CURVEBORDER,rect.bottom - CURVEBORDER);
		}
		else if(i == CURVELINETIME)
		{
			CPen mypen(PS_SOLID,1,RGB(255,0,0));
			pOldPenline = pDC->SelectObject(&mypen);
			pDC->MoveTo(rectText.left,rectText.top);
			pDC->LineTo(rectText.left,rect.top + CURVEBORDER +4);  //3
			pDC->SelectObject(pOldPenline);
		}
		else
		{
			if(m_sCheckGrid)
			{
			CPen mypen(PS_DOT,1,RGB(255,0,0));
			pOldPenline = pDC->SelectObject(&mypen);
			pDC->MoveTo(rectText.left,rectText.top);
			pDC->LineTo(rectText.left,rect.top + CURVEBORDER +4);  //3
			pDC->SelectObject(pOldPenline);
			}
			else
			{
			CPen mypen(PS_NULL,1,RGB(0,0,0));
			pOldPenline = pDC->SelectObject(&mypen);
			pDC->MoveTo(rectText.left,rectText.top);
			pDC->LineTo(rectText.left,rect.top + CURVEBORDER +4);  //3
			pDC->SelectObject(pOldPenline);
			}
		//raphics.DrawLine(&LinePen,rectText.left,rectText.top,rectText.left,rect.top + CURVEBORDER);
		}
		pDC->SetROP2(bkmode);
	}
	for(i=0; i<=CURVELINE; i++)
	{
		/////////百分数/////////////////////////
		/////////数字/////////////////////////
    		double MaxValue = m_curveProp[m_curPointIndex].MaxValue;
    		double MinValue = m_curveProp[m_curPointIndex].MinValue;
		if(i == CURVELINE){
			value = 100;
			value1 = MaxValue;
		}
		else{
			value1 = ((MaxValue-MinValue)/CURVELINE)*i + MinValue;
			value = 5*i ;
		}
		text.Format("%d",value);
        text+="% ";
		rectText.bottom = rect.bottom - yinter*i - CURVEBORDER ;
		rectText.top = rectText.bottom -20;  // - 20;  
		rectText.left = rect.left;
		rectText.right = rect.left + CURVEBORDER - 0;   //1
		CRect tmp = rectText;
		if(value == 0)
		{
			tmp.top += 8;    //8
			tmp.bottom+=8;    //8
		}
		else 
		{
			tmp.top+=13;     //13
			tmp.bottom+=20;  //13
		}
		pDC->DrawText(text,tmp,DT_RIGHT|DT_BOTTOM);
		
		char Type = m_curveProp[m_curPointIndex].Type;
		if(Type==1)
		{
		CRect rectvalue;
		text.Format("%4.2f",value1);
		rectvalue.bottom = rect.bottom - yinter*i - CURVEBORDER ;
		rectvalue.top = rectText.bottom -20;  // - 20;  
		rectvalue.right = rect.right + 0;
		rectvalue.left = rect.right - CURVEBORDER + 2;   //1
		CRect tmp1 = rectvalue;
	    	if(value1 == 0.00)
			{
		    	tmp1.top += 8;    //8
		    	tmp1.bottom+=8;    //8
			}
	    	else 
			{
		    	tmp1.top+=13;     //13
		     	tmp1.bottom+=20;  //13
			}
		pDC->DrawText(text,tmp1,DT_RIGHT|DT_BOTTOM);
		}
		bkmode = pDC->SetROP2(R2_NOT);
		
		////////////////横线///////////////////////
		if(i == 0)
		{
			CPen mypen(PS_SOLID,1,RGB(255,0,0));    //0126
			pOldPenline = pDC->SelectObject(&mypen);
			pDC->MoveTo(rectText.right,rectText.bottom);
			pDC->LineTo(rect.right - CURVEBORDER,rectText.bottom);
			pDC->SelectObject(pOldPenline);
		//graphics.DrawLine(&LinePen,rectText.right,rectText.bottom,rect.right - CURVEBORDER-3,rect.bottom);
			tmpRect.right = rect.right - CURVEBORDER-3;
		}
		else if(i == CURVELINE)
		{
			CPen mypen(PS_SOLID,1,RGB(255,0,0));
			pOldPenline = pDC->SelectObject(&mypen);
			pDC->MoveTo(rectText.right,rectText.bottom);
			pDC->LineTo(rect.right - CURVEBORDER,rectText.bottom);
			pDC->SelectObject(pOldPenline);
		//	graphics.DrawLine(&LinePen,rectText.right,rectText.bottom,rect.right - CURVEBORDER-3,rectText.bottom);
		}
		else
		{
			if(m_sCheckGrid)
			{
			CPen mypen(PS_DOT,1,RGB(255,0,0));
			pOldPenline = pDC->SelectObject(&mypen);
			pDC->MoveTo(rectText.right,rectText.bottom);
			pDC->LineTo(rect.right - CURVEBORDER,rectText.bottom);
			pDC->SelectObject(pOldPenline);
		//	graphics.DrawLine(&LinePen,rectText.right,rectText.bottom,rect.right - CURVEBORDER-3,rectText.bottom);
			}
			else
			{
			CPen mypen(PS_NULL,1,RGB(0,0,0));
			pOldPenline = pDC->SelectObject(&mypen);
			pDC->MoveTo(rectText.right,rectText.bottom);
			pDC->LineTo(rect.right - CURVEBORDER,rectText.bottom);
			pDC->SelectObject(pOldPenline);
			}
		}

		pDC->SetROP2(bkmode);
	}

///	pDC->SelectObject(pOldPen);
///	font.DeleteObject();
	pDC->SelectObject(pOldFont);
	pDC->SetBkMode(oldmode);
////////////////画连线////////////////////////////////////////////
	for(i=0; i<CURVENUM; i++)
	{
		int size = m_curveData[i].GetSize();
		if(size)
		{
			CPen curvePen(PS_SOLID,1,m_curveProp[i].lineColor);
//			curvePen.CreatePen(PS_SOLID,1,m_curveProp[i].lineColor);
			CPen   *pOldPen = pDC->SelectObject(&curvePen);
			CPoint point;
			CCurveData dd = m_curveData[i].GetAt(0);
			point.x = dd.x;
			point.y = dd.y;
			pDC->MoveTo(point);
			pDC->Ellipse(point.x-2,point.y-2,point.x+2,point.y+2);  //0115  2
			for(int j=1; j<size; j++)
			{
				dd = m_curveData[i].GetAt(j);
				point.x = dd.x;
				point.y = dd.y;
				pDC->LineTo(point);
				pDC->Ellipse(point.x-2,point.y-2,point.x+2,point.y+2);  //0115  2
			}
			pDC->SelectObject(pOldPen);
		}
	}
///	font.DeleteObject();
	font.CreateFont(15,6,0,0,FW_NORMAL,0,0,0,ANSI_CHARSET,0,0,0,0,"Times New Roman");
	CFont *pOldFont1 = pDC->SelectObject(&font);
	if(m_bHistory)
	{
		if(PtInRect(tmpRect,m_point) == FALSE)
		{
			m_point = m_PointOld;
		}
		else 
		{
			m_PointOld = m_point;	
			int minValue =1024;
			int maxValue = 0;
			for(int i = 0; i < CURVENUM; i++)
			{
				int size =m_curveData[i].GetSize();
				if(size > 0)
				{
					if(m_curveData[i].GetAt(0).x < minValue)
						minValue = m_curveData[i].GetAt(0).x;
					if(m_curveData[i].GetAt(size -1).x > maxValue)
						maxValue = m_curveData[i].GetAt(size - 1).x;
				}
			}
			if((m_point.x <= maxValue) && (m_point.x >= minValue))///标尺在有数据的线上
			{
				//////////////画选择线//////////////
    		double MaxValue = m_curveProp[m_curPointIndex].MaxValue;
    		double MinValue = m_curveProp[m_curPointIndex].MinValue;
    		double WarnMaxValue = m_curveProp[m_curPointIndex].WarningMaxValue;
    		double WarnMinValue = m_curveProp[m_curPointIndex].WarningMinValue;
    		unsigned char WarnMode = m_curveProp[m_curPointIndex].WarnMode;
	    	char Type = m_curveProp[m_curPointIndex].Type;
	        unsigned short Standard =m_curveProp[m_curPointIndex].Standard;        //最大二进制数
			double anolog=m_value[m_curPointIndex]*(MaxValue-MinValue)/Standard +MinValue;
		    
    		CPen mypen(PS_SOLID,1,RGB(255,127,127));
			pOldPenline = pDC->SelectObject(&mypen);
			pDC->MoveTo(rectText.right,m_point.y);
			pDC->LineTo(rect.right - CURVEBORDER,m_point.y);
			pDC->SelectObject(pOldPenline);

		if(Type==1)
		{
			CPen mypen1(PS_SOLID,1,RGB(255,0,0));
			pOldPenline = pDC->SelectObject(&mypen1);
//		    rectText.bottom = rect.bottom - yinter*((WarnMaxValue-MinValue)/(MaxValue-MinValue))*20 - CURVEBORDER ;
		    int bottommax = rect.bottom - yinter*((WarnMaxValue-MinValue)/(MaxValue-MinValue))*20 - CURVEBORDER ;
			pDC->MoveTo(rectText.right, bottommax);
			pDC->LineTo(rect.right - CURVEBORDER, bottommax);
			pDC->SelectObject(pOldPenline);

			CPen mypen2(PS_SOLID,1,RGB(255,0,0));
			pOldPenline = pDC->SelectObject(&mypen2);
		    int bottommin = rect.bottom - yinter*((WarnMinValue-MinValue)/(MaxValue-MinValue))*20 - CURVEBORDER ;
			pDC->MoveTo(rectText.right,bottommin);
			pDC->LineTo(rect.right - CURVEBORDER,bottommin);
			pDC->SelectObject(pOldPenline);

            if(WarnMode == 0)
			{
				pen.CreatePen(PS_SOLID,1,RGB(255,255,127));
				pOldPen = pDC->SelectObject(&pen);
				pDC->MoveTo(m_point.x,rect.top +CURVEBORDER+5 );
				pDC->LineTo(m_point.x,rect.bottom -CURVEBORDER );
				pDC->SelectObject(pOldPen);
			}
            if(WarnMode == 1)
			{
				pen.CreatePen(PS_SOLID,1,RGB(255,0,0));
				pOldPen = pDC->SelectObject(&pen);
				pDC->MoveTo(m_point.x,rect.top +CURVEBORDER+5 );
				pDC->LineTo(m_point.x,bottommax );
				pDC->SelectObject(pOldPen);
				pen.CreatePen(PS_SOLID,1,RGB(0,255,0));
				pOldPen = pDC->SelectObject(&pen);
				pDC->MoveTo(m_point.x,bottommax );
				pDC->LineTo(m_point.x,bottommin );
				pDC->SelectObject(pOldPen);
				pen.CreatePen(PS_DOT,1,RGB(255,128,0));
				pOldPen = pDC->SelectObject(&pen);
				pDC->MoveTo(m_point.x,bottommin );
				pDC->LineTo(m_point.x,rect.bottom -CURVEBORDER );
				pDC->SelectObject(pOldPen);
			}
            if(WarnMode == 2)
			{
				pen.CreatePen(PS_SOLID,1,RGB(255,0,0));
				pOldPen = pDC->SelectObject(&pen);
				pDC->MoveTo(m_point.x,rect.top +CURVEBORDER+5 );
				pDC->LineTo(m_point.x,bottommax );
				pDC->SelectObject(pOldPen);
				pen.CreatePen(PS_DOT,1,RGB(255,128,0));
				pOldPen = pDC->SelectObject(&pen);
				pDC->MoveTo(m_point.x,bottommax );
				pDC->LineTo(m_point.x,bottommin );
				pDC->SelectObject(pOldPen);
				pen.CreatePen(PS_SOLID,1,RGB(0,255,0));
				pOldPen = pDC->SelectObject(&pen);
				pDC->MoveTo(m_point.x,bottommin );
				pDC->LineTo(m_point.x,rect.bottom -CURVEBORDER );
				pDC->SelectObject(pOldPen);
			}
            if(WarnMode == 3)
			{
				pen.CreatePen(PS_SOLID,1,RGB(0,255,0));
				pOldPen = pDC->SelectObject(&pen);
				pDC->MoveTo(m_point.x,rect.top +CURVEBORDER+5 );
				pDC->LineTo(m_point.x,bottommax );
				pDC->SelectObject(pOldPen);
				pen.CreatePen(PS_SOLID,1,RGB(255,0,0));
				pOldPen = pDC->SelectObject(&pen);
				pDC->MoveTo(m_point.x,bottommax );
				pDC->LineTo(m_point.x,bottommin );
				pDC->SelectObject(pOldPen);
				pen.CreatePen(PS_DOT,1,RGB(255,128,0));
				pOldPen = pDC->SelectObject(&pen);
				pDC->MoveTo(m_point.x,bottommin );
				pDC->LineTo(m_point.x,rect.bottom -CURVEBORDER );
				pDC->SelectObject(pOldPen);
			}

		}
        else
		{
				pen.CreatePen(PS_SOLID,1,RGB(255,255,127));
				pOldPen = pDC->SelectObject(&pen);
				//	oldmode = pDC->SetROP2(R2_NOT);CURVEBORDER
				pDC->MoveTo(m_point.x,rect.top +CURVEBORDER+5 );
				pDC->LineTo(m_point.x,rect.bottom -CURVEBORDER );
				//	pDC->SetROP2(oldmode);
				pDC->SelectObject(pOldPen);
				//	Pen pen(Color(255,255,255,127));
				//	graphics.DrawLine(&pen,m_point.x,rect.top,m_point.x,rect.bottom);
		}		
		        int size = m_curveData[m_curPointIndex].GetSize();
				if(size > 0)
				{
					if((m_point.x >= m_curveData[m_curPointIndex].GetAt(0).x) &&
						(m_point.x <= m_curveData[m_curPointIndex].GetAt(size - 1).x))
					{
						DrawPointInfo(pDC,m_curCursorPos.x,m_curCursorPos.y);
					}
				}
		/////////////////////////////////////
        		for(i=0; i<CURVENUM; i++)
				{
    	    		if(m_value[i]!=-1)
					{
				CRect rectvalue;
				rectvalue.left = rect.left + 113*i + CURVEBORDER;  //2
				rectvalue.right = rectvalue.left + 113 ;//2
				rectvalue.top = rect.top + 15 ;
				rectvalue.bottom = rect.top + 35;
				CBrush textbrush,*pOldTextBrush;

				textbrush.CreateSolidBrush(m_curveProp[i].lineColor);
				pOldTextBrush = pDC->SelectObject(&textbrush);

				pDC->Rectangle(rectvalue);
				m_RectBox = rectvalue;
				pDC->SelectObject(pOldTextBrush);

				CString strValue;
				strValue.Format("曲线%d:%d(%d)",i+1,m_value[i],m_curveProp[i].Standard);
				oldmode = pDC->SetBkMode(TRANSPARENT);
			//	bkmode = pDC->SetROP2(R2_NOT);
				//pDC->ExtTextOut(rectvalue.left,rectvalue.top,ETO_CLIPPED,rectvalue,strValue,NULL);
				pDC->SetTextColor(RGB(0,0,0));
				pDC->DrawText(strValue,rectvalue,DT_CENTER);
			//	pDC->SetROP2(bkmode);
				pDC->SetBkMode(oldmode);
					}
				}
			}
		}
	}

	if(m_bSelect)
	{
		DrawSelect(pDC);
	}
	pDC->SelectObject(pOldFont1);   //0126
///	pDC->SelectObject(pOldPen);
///	pDC->SelectObject(pOldBrush);
}

CRect CRtCurve::SetRtRect()
{
	if(m_clientSize.cx ==0)
	{
		m_clientSize.cx = m_pointArray[1].x;
		m_clientSize.cy = m_pointArray[1].y;
		m_rect.top = min(m_pointArray[0].y,m_pointArray[1].y) + CURVEBORDER;
		m_rect.bottom = max(m_pointArray[0].y,m_pointArray[1].y) - CURVEBORDER;
		m_rect.left = min(m_pointArray[0].x,m_pointArray[1].x) + CURVEBORDER;
		m_rect.right = max(m_pointArray[0].x,m_pointArray[1].x) - CURVEBORDER;
		if(m_bHistory)
			m_rect.right -= CURVEBORDER;
	}
	return m_rect;
}

void CRtCurve::ShowValue(CPoint &point)
{
///	if(!m_bLock)
///		return;
	m_point = point;
	m_curCursorPos = point;
//	CRect rect = GetRealRect();
	CPoint point1,point2;
	point1.x = point2.x = 0;
//	short tmpdata;
	for(int i=0; i<CURVENUM; i++)
	{
		int size = m_curveData[i].GetSize();
		if(size)
		{
			CCurveData cvdata;
			for(int j=0; j<size; j++)
			{
				cvdata = m_curveData[i].GetAt(j);
				if(cvdata.x >= point.x)
				{
					if(j <=0)
						break;
					if(cvdata.x == point.x)
					{
						m_value[i] = cvdata.data;
                 	    m_curveYear[i] = cvdata.StartYear;
	                    m_curveMonth[i] = cvdata.StartMonth;
	                    m_curveDay[i] = cvdata.StartDay;
                        m_curveHour[i] = cvdata.StartHour;
                        m_curveMinute[i] = cvdata.StartMinute;
                        m_curveSecond[i] = cvdata.StartSecond;
						break;
					}
				}
			}
		}
	}
}

void CRtCurve::InsertHistoryData()
{
	CSQLDirect sql;
	CString   strSql ;
	CString2DataType convert;

	if(m_nZoom == 0) {
		GetDate(aYear,aMonth,aDay,m_strStartDate);
        aHour = (int)m_sStartHour ;
        aMinute = (int)m_sStartMin ;
        aSecond = (int)m_sStartSecond ;
		GetDate(mYear,mMonth,mDay,m_strEndDate);
        mHour = (int)m_sEndHour ;
        mMinute = (int)m_sEndMin ;
        mSecond = (int)m_sEndSecond ;
	}

	for(int i=0; i<CURVENUM ;i++)
		m_curveData[i].RemoveAll();

	int	timelen = (((((mYear - aYear)*12 +(mMonth - aMonth))*30 
		+ (mDay - aDay))*24 + (mHour - aHour))*60*60 
		+ (mMinute - aMinute)*60) + mSecond - aSecond;

	if(timelen <=0)
		return;
	m_nTime = timelen;

      try
	  {
		sql.Init();
		if(sql.Connect(_T("masterdefine"),_T("kj86"),_T("kj86")))
			AfxMessageBox("AddUser:无法连接用户参数数据库,请确定SQL SERVER服务是否运行!");
        for(i=0; i<CURVENUM; i++)
		{
		strSql.Format("SELECT * FROM uCollectData WHERE unPointNo = %d",m_curveProp[i].point);
		if(sql.ExecuteSQL(strSql) == SQL_SUCCESS)
		{
			int nYear,nMonth,nDay,nHour,nMinute,nSecond ,lapse ;
            unsigned short	data,point;

			CString date ;
			int ret = sql.Fetch();
			while(!ret)
			{
				point = convert.String2Int(sql.GetCol(1));
				data = convert.String2Int(sql.GetCol(2));
				date = sql.GetCol(3);

				int no = i;
				if(no >=0)
				{
					GetDate(nYear,nMonth,nDay,nHour,nMinute,nSecond,date);

	    			lapse = (((((nYear - aYear)*12 + (nMonth - aMonth))*30 + (nDay - aDay))*24 + (nHour - aHour))*60 + nMinute - aMinute)*60 + nSecond - aSecond;
	
					if((lapse < timelen) && (lapse >=0))
					{
						InsertIntoCurve(no,data,date,lapse);
					}
					else if(lapse > timelen) break;
				}
				ret = sql.Fetch();
			}	
		}
		else
			AfxMessageBox("数据库表uCollectData查询失败");
		}
		sql.Close();

	  }
	  catch(CDBException *e)
	  {
		e->ReportError();
		return;
	  }

}

void CRtCurve::GetDate(int &year,int &month,int &day,CString time)
{
	CString2DataType convert;
	int index;
	CString value;

	index = time.Find('-');
	value = time.Mid(0,index);
	year = convert.String2Int(value);

	time = time.Mid(index+1);
	index = time.Find('-');
	value = time.Mid(0,index);
	month = convert.String2Int(value);

	time = time.Mid(index+1);
//	index = time.Find(' ');
//	value = time.Mid(0,index);
	day = convert.String2Int(time);

}

void CRtCurve::GetDate(int &year,int &month,int &day,int &hour,int &minute,int &second,CString time)
{
	GetDate(year,month,day,time);
	CString2DataType convert;
	CString value;
	int index = time.Find(' ');
	time = time.Mid(index+1);

	index = time.Find(':');
	value = time.Mid(0,index);
	hour = convert.String2Int(value);

	time = time.Mid(index+1);
	index = time.Find(':');
	value = time.Mid(0,index);
	minute = convert.String2Int(value);
	
	time = time.Mid(index+1);
//	index = time.Find(':');
//	value = time.Mid(0,index);
	second = convert.String2Int(time);
}

void CRtCurve::InsertIntoCurve(int no,unsigned short data,CString len,int lapse)
{
    int nYear,nMonth,nDay,nHour,nMinute,nSecond , xvalue;
	CCurveData curveData;
	GetDate(nYear,nMonth,nDay,nHour,nMinute,nSecond,len);

	curveData.data = data;
    curveData.StartYear = nYear;
    curveData.StartMonth = nMonth;
    curveData.StartDay = nDay;
    curveData.StartHour = nHour;
    curveData.StartMinute = nMinute;
    curveData.StartSecond = nSecond;

    double vrate;
	static int oldx = 0;
    if((m_curveProp[no].unConnectorID==4)||(m_curveProp[no].unConnectorID==10))
    	vrate =  fabs((data*1.0)/((m_curveProp[no].Standard+768)*1.00)+0.001) ;
//     	vrate = fabs(log(data)/log(2)/CURVELINE);
	else if(m_curveProp[no].unConnectorID==7)
    	vrate =  fabs((data*1.0)/((m_curveProp[no].Standard+48)*1.00)+0.001) ;
    else if(m_curveProp[no].unConnectorID==9)
    	vrate =  fabs((data*1.0)/((m_curveProp[no].Standard+3)*1.00)+0.001) ;
    else if((m_curveProp[no].unConnectorID==3)||(m_curveProp[no].unConnectorID==5)||(m_curveProp[no].unConnectorID==6)||(m_curveProp[no].unConnectorID==8)||(m_curveProp[no].unConnectorID==15))
    	vrate =  fabs((data*1.0)/((m_curveProp[no].Standard+3)*1.00)+0.001) ;
    else 
    	vrate =  fabs((data*1.0)/1.01+0.001) ;//data/(double)(m_nStandard-1);

	double hrate = fabs(lapse/(double) (60));

	curveData.y = m_rect.bottom - (m_rect.bottom - m_rect.top) * vrate;
//	curveData.x = m_rect.left + (m_rect.right - m_rect.left) * hrate;

	    xvalue = (int)((m_nTime*1.0 / CURVELINETIME) );
	if(xvalue < 1)
		xvalue = 1;

	curveData.x = m_rect.left + (lapse*1.0 / xvalue) * (m_rect.Width() * 1.0 / CURVELINETIME);
	if(m_rect.PtInRect(curveData))
	{		
		if(curveData.x != oldx)
		{
			m_curveData[no].Add(curveData);
			oldx = curveData.x;
		}
	}
}

void CRtCurve::DrawPointInfo(CDC *pDC,int x,int y)
{
	if((m_curPointIndex >= 0) && (m_curPointIndex < CURVENUM))	
	{
		unsigned short point = m_curveProp[m_curPointIndex].point;
		COLORREF color = m_curveProp[m_curPointIndex].lineColor;
	    unsigned short Standard =m_curveProp[m_curPointIndex].Standard;        //最大二进制数
		double MaxValue = m_curveProp[m_curPointIndex].MaxValue;
		double MinValue = m_curveProp[m_curPointIndex].MinValue;
		char Type = m_curveProp[m_curPointIndex].Type;
		double WarnMaxValue = m_curveProp[m_curPointIndex].WarningMaxValue;
		double WarnMinValue = m_curveProp[m_curPointIndex].WarningMinValue;

		CBrush LineBrush(color);
		CBrush BlueBrush(RGB(0,0,255));
		CBrush RedBrush(RGB(255,0,0));
		CBrush GreenBrush(RGB(0,255,0)),*pOldBrush;
		CString str;
		CRect rect(x,y,x+100,y+20);
	
		pDC->SetBkMode(TRANSPARENT);
		pDC->SetTextColor(RGB(0,0,0));

		pOldBrush = pDC->SelectObject(&LineBrush);
		pDC->Rectangle(rect);
		str.Format("点号：%d",point);
		pDC->DrawText(str,rect,DT_CENTER);//点号
		pDC->SelectObject(pOldBrush);
		
    		pOldBrush = pDC->SelectObject(&LineBrush);
	    	rect.top += 20;
	    	rect.bottom += 20;
	     	pDC->Rectangle(rect);
	    	str.Format("%d年%d月%d日",m_curveYear[m_curPointIndex],m_curveMonth[m_curPointIndex],m_curveDay[m_curPointIndex]);
	    	pDC->DrawText(str,rect,DT_CENTER);//
	    	pDC->SelectObject(pOldBrush);

    		pOldBrush = pDC->SelectObject(&LineBrush);
	    	rect.top += 20;
	    	rect.bottom += 20;
	     	pDC->Rectangle(rect);
	    	str.Format("%d时%d分%d秒",m_curveHour[m_curPointIndex],m_curveMinute[m_curPointIndex],m_curveSecond[m_curPointIndex]);
	    	pDC->DrawText(str,rect,DT_CENTER);//
	    	pDC->SelectObject(pOldBrush);

		if(Type == 1)///模拟量
		{	
            if((m_curveProp[m_curPointIndex].unConnectorID==4)||(m_curveProp[m_curPointIndex].unConnectorID==10))
			{
            CString StrUnit=m_curveProp[m_curPointIndex].StrUnit;
               unsigned short anologd=m_value[m_curPointIndex];
			pOldBrush = pDC->SelectObject(&BlueBrush);
	    	rect.top += 20;
	    	rect.bottom += 20;
	    	pDC->Rectangle(rect);
	    	str.Format("实际值：%d%s",anologd,StrUnit);
    		pDC->DrawText(str,rect,DT_CENTER);//实际值
    		pDC->SelectObject(pOldBrush);

//		    pOldBrush = pDC->SelectObject(&GreenBrush);
//			rect.top += 20;
//			rect.bottom += 20;
//			pDC->Rectangle(rect);
//			str.Format("%d--%d%s",(unsigned short)MinValue,(unsigned short)MaxValue,StrUnit);
//			pDC->DrawText(str,rect,DT_CENTER);//最大值%08.2lf最小值
//	    	pDC->SelectObject(pOldBrush);
			}
			else
			{
            CString StrUnit=m_curveProp[m_curPointIndex].StrUnit;
			double anolog=m_value[m_curPointIndex]*(MaxValue-MinValue)/Standard +MinValue;

			pOldBrush = pDC->SelectObject(&BlueBrush);
	    	rect.top += 20;
	    	rect.bottom += 20;
	    	pDC->Rectangle(rect);
	    	str.Format("实际值：%4.2f%s",anolog,StrUnit);
    		pDC->DrawText(str,rect,DT_CENTER);//实际值
    		pDC->SelectObject(pOldBrush);

//		    pOldBrush = pDC->SelectObject(&GreenBrush);
//			rect.top += 20;
//			rect.bottom += 20;
//			pDC->Rectangle(rect);
//			str.Format("%4.2f--%4.2f %s",MinValue,MaxValue,StrUnit);
//			pDC->DrawText(str,rect,DT_CENTER);//最大值%08.2lf最小值
//	    	pDC->SelectObject(pOldBrush);
			
//			pOldBrush = pDC->SelectObject(&RedBrush);
//			rect.top += 20;
//			rect.bottom += 20;
//			pDC->Rectangle(rect);
//			str.Format("%4.2f--%4.2f %s",WarnMinValue,WarnMaxValue,StrUnit);
//			pDC->DrawText(str,rect,DT_CENTER);//报警最大值报警最小值
//	    	pDC->SelectObject(pOldBrush);
			}
		}
		else
		{
    		pOldBrush = pDC->SelectObject(&BlueBrush);
	    	rect.top += 20;
	    	rect.bottom += 20;
	     	pDC->Rectangle(rect);
	    	str.Format("%d",m_value[m_curPointIndex]);
	    	pDC->DrawText(str,rect,DT_CENTER);//实际值
	    	pDC->SelectObject(pOldBrush);

		}
	}
}

void CRtCurve::GetCurrentPoint(CPoint &point)
{
	for(int i=0; i<CURVENUM; i++)
	{
		if(m_value[i]!=-1)
		{
			CRect rectvalue;
			CRect rect = GetRealRect();
				rectvalue.left = rect.left + 113*i + CURVEBORDER;  //2
				rectvalue.right = rectvalue.left + 113 ;//2
				rectvalue.top = m_RectBox.top  ;
				rectvalue.bottom = m_RectBox.bottom  ;
			if(PtInRect(rectvalue,point) == TRUE)
			{
				m_curPointIndex = i;
				break;
			}
		}
	}
}

BOOL CRtCurve::ZoomIn(CRect &rect)
{
//	rect.NormalizeRect();
	if((rect.Width() > 0 ) && (rect.Height() > 0 ))
	{	
		if(m_nTime > 0)
		{
        	CRect rect = GetRealRect();

        	double ratio =  ((m_oldPoint.x *1.0) /(rect.right*1.0) ) ;
        	double ratiom =  (((m_newPoint.x - m_oldPoint.x )*1.0) /(rect.right*1.0) ) ;
            int	mxvalue = (int)((m_nTime * ratiom)*1.0 );
            int	xvalue = (int)((m_nTime * ratio)*1.0 );
         	if(xvalue < 1)
        		xvalue = 1;

            CTime time(aYear,aMonth,aDay,aHour,aMinute,aSecond);
        	CTimeSpan span(0,0,0,xvalue);
        	time += span;
            aYear = (int) time.GetYear();
            aMonth = (int)time.GetMonth() ;
            aDay = (int)time.GetDay();
            aHour = (int)time.GetHour() ;
            aMinute = (int)time.GetMinute();
            aSecond = (int)time.GetSecond();

          	CTimeSpan mspan(0,0,0,mxvalue);
        	time += mspan;
			mYear = (int) time.GetYear();
            mMonth = (int)time.GetMonth() ;
            mDay = (int)time.GetDay();
            mHour = (int)time.GetHour() ;
            mMinute = (int)time.GetMinute();
            mSecond = (int)time.GetSecond();

    		m_nZoom++;
			InsertHistoryData();
			return TRUE;
		}
	}
   	return FALSE;
}

void CRtCurve::Restore()
{
	m_nZoom = 0;
	InsertHistoryData();
}

void CRtCurve::Expend(CPoint &point)
{
	CRect rect = GetRealRect();

	double ratio =  ((point.x *1.0) /(rect.right*1.0) ) ;
    int	mxvalue = (int)((m_nTime /2 * (1 - ratio) )*1.0 );
    int	xvalue = (int)((m_nTime * ratio)*1.0 );
	if(xvalue < 1)
		xvalue = 1;

        CTime time(aYear,aMonth,aDay,aHour,aMinute,aSecond);
    	CTimeSpan span(0,0,0,xvalue);
    	time += span;
        aYear = (int) time.GetYear();
        aMonth = (int)time.GetMonth() ;
        aDay = (int)time.GetDay();
        aHour = (int)time.GetHour() ;
        aMinute = (int)time.GetMinute();
        aSecond = (int)time.GetSecond();

     	CTimeSpan mspan(0,0,0,mxvalue);
    	time += mspan;
        mYear = (int) time.GetYear();
        mMonth = (int)time.GetMonth() ;
        mDay = (int)time.GetDay();
        mHour = (int)time.GetHour() ;
        mMinute = (int)time.GetMinute();
        mSecond = (int)time.GetSecond();

		m_nZoom++;
    	InsertHistoryData();
}

