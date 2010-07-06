// DrawButton.h: interface for the CDrawButton class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DRAWBUTTON_H__00666BA7_3CE6_4E18_A002_80275C956797__INCLUDED_)
#define AFX_DRAWBUTTON_H__00666BA7_3CE6_4E18_A002_80275C956797__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DrawObj.h"
#include "Enum.h"

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
	virtual int GetHandleCount();
	virtual CPoint GetHandle(int nHandle);
	virtual HCURSOR GetHandleCursor(int nHandle);
	virtual void MoveHandleTo(int nHandle, CPoint point, CDrawView* pView = NULL);
	virtual BOOL Intersects(const CRect& rect);
	virtual CDrawObj* Clone(CDrawDoc* pDoc);
	virtual void OnEditProperties();

public:
	enum Shape {                          //不同的类型
                button,                   //按钮
				text,                      //文本
				picture                   //图片
				};
	Shape m_nShape;
/*                                            //暂不支持 0415
	enum ButtonState{
				NONE,
				MOVE,
				CLIECK};
	ButtonState m_nButtonState;
*/
///public:
///	BOOL SetState(ButtonState nState);					//设置按钮的状态0415

///public:
	COLORREF			m_color;				//字体颜色
	Color				m_fontColor;			
	CString				m_fontName;				//字体名称
	BYTE				m_fontSize;				//字体大小
	FontStyle           m_fontStyle;			//字体风格
	StringTrimming		m_trimmingSyle;			//对齐风格
	StringFormatFlags   m_format;				//字体格式
	StringAlignment     m_fontAlignment;		
	CString             m_strButton;			//文本内容
///0415
	COLORREF			m_TrueColor;			//正常时颜色
	COLORREF			m_ErrorColor;			//通讯失败时颜色
	COLORREF			m_FalseColor;
	UINT				m_nPointNo;				//对应点号
	BOOL				m_bIsRunShowValue;		//是否在运行时显示点号的值
	BOOL				m_blsDispTrue;		//正常显示文本

	CString             m_strLinkViewName;		//连接的窗口名称
	BOOL				m_bIsChangeHide;		

	CString	            m_strPictureName;

};

#endif // !defined(AFX_DRAWBUTTON_H__00666BA7_3CE6_4E18_A002_80275C956797__INCLUDED_)
