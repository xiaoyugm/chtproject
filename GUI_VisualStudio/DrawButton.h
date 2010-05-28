// DrawButton.h: interface for the CDrawButton class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DRAWBUTTON_H__00666BA7_3CE6_4E18_A002_80275C956797__INCLUDED_)
#define AFX_DRAWBUTTON_H__00666BA7_3CE6_4E18_A002_80275C956797__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DrawObj.h"

class CDrawView;
class CDrawDoc;

class CDrawButton : public CDrawObj  
{
protected:
	DECLARE_SERIAL(CDrawButton);
	CDrawButton();
	virtual ~CDrawButton();

public:
	CDrawButton(const CRect& position);
public:
	virtual void Serialize(CArchive& ar);
	virtual void Draw(CDC* pDC);
///	virtual int GetHandleCount();
///	virtual CPoint GetHandle(int nHandle);
///	virtual HCURSOR GetHandleCursor(int nHandle);
///	virtual void MoveHandleTo(int nHandle, CPoint point, CDrawView* pView = NULL);
///	virtual BOOL Intersects(const CRect& rect);
///	virtual CDrawObj* Clone(CDrawDoc* pDoc);
//	virtual void OnEditProperties();
	virtual void Invalidate();
	void    StartAction();

	enum Shape {
		        button,
				text,
				picture                   //ͼƬ
				};
	Shape m_nShape;

/*	enum ButtonState{
				NONE,
				MOVE,
				CLIECK};
	ButtonState m_nButtonState;

public:
	BOOL SetState(ButtonState nState);					//���ð�ť��״̬
*/
public:
	COLORREF			m_color;
	Color				m_fontColor;
	CString				m_fontName;
	BYTE				m_fontSize;
	FontStyle           m_fontStyle;
	StringTrimming		m_trimmingSyle;
	StringFormatFlags   m_format;
	StringAlignment     m_fontAlignment;
	CString             m_strButton;

	COLORREF			m_TrueColor;			//����ʱ��ɫ
	COLORREF			m_ErrorColor;			//ͨѶʧ��ʱ��ɫ
	COLORREF			m_FalseColor;
	COLORREF			m_TempColor;
	UINT				m_nPointNo;				//��Ӧ���
	BOOL				m_bIsRunShowValue;		//�Ƿ�������ʱ��ʾ��ŵ�ֵ
	BOOL				m_blsDispTrue;		//������ʾ�ı�

	CString             m_strLinkViewName;
	BOOL				m_bIsChangeHide;	
	CString	            m_strPictureName;
};

#endif // !defined(AFX_DRAWBUTTON_H__00666BA7_3CE6_4E18_A002_80275C956797__INCLUDED_)
