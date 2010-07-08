
const int   RADIUS=3;
const int   SELECTLINE=1;

const int   RECTANGLE=3;
const int   RTCURVE=8;
/*
typedef struct tagPOINTDATA
{
	short point;
	short data;
	char  state;
}POINTDATA,*PPOINTDATA;
*/
class CGraphic : public CObject
{
public:
	CGraphic();
	~CGraphic();
	virtual void Draw(CDC *pDC)=0;
	virtual void Serialize(CArchive &ar);
	virtual CGraphic* Select(CPoint &pointx,CPoint &pointy,BOOL falg=false);
	virtual UINT  ChangeCursor(CPoint &point);
	virtual void  ModifyShape(CPoint &pointOrigin,CPoint &point);
	virtual CGraphic* CreateSameOne();
	virtual CRect GetRect();
	virtual CRect GetRealRect();
	virtual void DrawSelect(CDC *pDC);
	virtual void DragGraphic(int x,int y);
//protected:
	DECLARE_DYNAMIC(CGraphic)
	UINT    m_nPenWidth;
	COLORREF m_colorPen,m_colorBrush;
	CArray <CPoint,CPoint> m_pointArray;
	BOOL	m_bSelect;
///	BOOL	m_bFill;
///	UINT    m_nShapeMode;
///	int		m_nNo;
///	int		m_nLineStyle;
///	short	m_FillStyle;///modified by xizheng
///	POINTDATA m_ptdata;
///	BOOL	m_bLock;
///	int		m_nUnion;
///	UINT	m_timespan;///modified by xizheng
///	UINT	m_RoundWidth;///modified by xizheng
///	UINT	m_RoundHeight;///modified by xizheng
	HWND	m_hWnd;///modified by xizheng
};
