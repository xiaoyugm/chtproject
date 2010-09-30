// DynamicMenu.h: interface for the CDynamicMenu class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DYNAMICMENU_H__69C5595A_B3B2_4C21_B34C_156FCE65304F__INCLUDED_)
#define AFX_DYNAMICMENU_H__69C5595A_B3B2_4C21_B34C_156FCE65304F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CDynamicMenu  
{
public:
 CDynamicMenu();
 virtual ~CDynamicMenu();
//protected:
 void appendMenuItem(int m_iItemID, CString m_strItemText);
 void appenMenu(int m_nMenuPosition, CString m_strMenuText);
 void setEnable(CString m_strMenu, int m_iItemID, int m_enable);
 void deleteMenu();
 void addMenu(CString m_strMenu, int m_iPosition, int m_iMenuID);
 void addMenu(CString m_strMenu,CString m_strAddMenu, int m_iMenuID);
 void addMenuItem(CString m_strMenu, int m_iPosition, int m_iMenuID);
 void addMenuItem(CString m_strMenu, CString m_strMenuItem, int m_iMenuItemID);
 void addMenuItem(CString m_strMenu, CString m_strMenuItem, CString m_strMenuPosition, int m_iMenuItemID);
 void modifyMenuItem(CString m_strMneu, int m_iMenuItemID);
 void modifyMenuItem(CString m_strMenu, CString m_strMenuItem, CString m_strModiyText);
 void createMenuItemChild();
 void deleteMenuItemChild();
//private:
 void setMenu();
 void createMenu();
 void createMenuItem();
 void drawMenuBar();
 CMenu* getMenuItem(int m_iPosition);
 int  FindMenuItem(CMenu* Menu, LPCTSTR MenuString);
 int getMenuItemCount(CMenu* Menu);
 CMenu* getMenu();
private:
 CMenu* m_bMenu;
 CMenu* m_bMenuItem;
 CMenu* m_bMenuItemChild;
 int i;
};
#endif // !defined(AFX_DYNAMICMENU_H__69C5595A_B3B2_4C21_B34C_156FCE65304F__INCLUDED_)

