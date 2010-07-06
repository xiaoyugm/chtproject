// DrawWarn.h: interface for the CDrawWarn class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DRAWWARN_H__76F721A0_6682_4B54_8C92_C52B005473E8__INCLUDED_)
#define AFX_DRAWWARN_H__76F721A0_6682_4B54_8C92_C52B005473E8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DrawObj.h"

class CDrawView;
class CDrawDoc;

class CDrawWarn : public CDrawObj  
{
public:
	DECLARE_SERIAL(CDrawWarn);
	CDrawWarn();
	CDrawWarn(const CRect& position);
	virtual ~CDrawWarn();
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

	virtual void DrawCell(CDC *pDC, Rect rect, int nCol, int nRow);
	void AddWarn(CString strPoint, CString strDate, CString strTime, CString strText, CString strWarn);
public:
	COLORREF	m_ctlBackColor;			//背景颜色
	COLORREF	m_ctlLineColor;			//线条颜色
	COLORREF	m_ctlTextColor;			//字体颜色
	COLORREF	m_ctlTitleColor;

	int			m_nCellWidth;
	int         m_nCellHeight;
	int         m_nRowCount, m_nColCount;
	CRect       m_CellRect;
	BOOL		m_bIsAutoSize;

	CString				m_fontName;
	BYTE				m_fontSize;
	FontStyle           m_fontStyle;
	StringTrimming		m_trimmingSyle;
	StringFormatFlags   m_format;
	StringAlignment     m_fontAlignment;
	typedef struct{
		CString strPoint;
		CString strDate;
		CString strTime;
		CString strText;
		CString strWarn;
	}STRWARN;
	STRWARN	*pStrWarn;
	UINT	*m_nPercent;
};

#endif // !defined(AFX_DRAWWARN_H__76F721A0_6682_4B54_8C92_C52B005473E8__INCLUDED_)
