#include "CurveData.h"

const int   CURVEBORDER = 40;
const int   CURVELINE = 20;   //16
const int   CURVELINETIME = 12;   //30
const short CURVENUM = 8;

typedef struct tagCURVEPROP
{
	unsigned short		point;
	unsigned short		Standard;        //����������
	COLORREF	lineColor;
	char	Type;				///����
    unsigned char WarnMode;
    short unConnectorID;
	double WarningMaxValue;	///�������ֵ
	double WarningMinValue;	///������Сֵ
	double  MaxValue;			///���ֵ
	double  MinValue;			///��Сֵ
	char    StrUnit[50];		///���̵�λ
	
}CURVEPROP,*PCURVEPROP;

#include "Graphic.h"

class CRtCurve:public CGraphic
{
public:
	CRtCurve();
	DECLARE_SERIAL(CRtCurve);   
	void Draw(CDC *pDC);
    virtual void Serialize(CArchive &ar);
	CRect SetRtRect();
	void ShowValue(CPoint &point);
	void InsertHistoryData();
	void GetDate(int &year,int &month,int &day,CString time);
	void GetDate(int &year,int &month,int &day,int &hour,int &minute,int &second,CString time);
	void InsertIntoCurve(int no,unsigned short data,CString len,int lapse);
	void DrawPointInfo(CDC*,int,int);
	void GetCurrentPoint(CPoint &point);
	BOOL ZoomIn(CRect &rect);
	void Restore();
	void Expend(CPoint& point);

private:
	CPoint	m_curCursorPos;
	CRect	m_RectBox;
public:     //����
	short	m_nZoom;		///�Ŵ���
	int		m_curPointIndex;
	CPoint  m_oldPoint;
	CPoint	m_newPoint;
	CRect	m_rect;
	BOOL	m_bModify;
//	DWORD   m_nStartTick;
	COLORREF m_colorLabel;
    CArray<CCurveData,CCurveData> m_curveData[CURVENUM];
	
//	int m_nStandard;
	int m_nTime;
	BOOL	m_bHistory;
	BOOL	m_sCheckGrid;
	unsigned short  m_value[CURVENUM];
	int m_curveYear[CURVENUM];
	int m_curveMonth[CURVENUM];
	int m_curveDay[CURVENUM];
	int m_curveHour[CURVENUM];
	int m_curveMinute[CURVENUM];
	int m_curveSecond[CURVENUM];
	CPoint m_point , m_PointOld;
	SIZE    m_clientSize;
	CString m_strStartDate;
	CString m_strEndDate;

	int mYear,mMonth,mDay,mHour,mMinute,mSecond;
	int aYear,aMonth,aDay,aHour,aMinute,aSecond;
	short   m_sStartHour;
	short   m_sEndHour;
	short   m_sStartMin;
	short   m_sEndMin;
	short   m_sStartSecond;
	short   m_sEndSecond;
	CURVEPROP  m_curveProp[CURVENUM];
	
	CTime m_endDateTime;
	CTime m_startDateTime;
};
