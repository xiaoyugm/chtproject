// DynamicMenu.cpp: implementation of the CDynamicMenu class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "GUI_VisualStudio.h"
#include "DynamicMenu.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDynamicMenu::CDynamicMenu()
{
 m_bMenu = new CMenu;
 m_bMenuItem = new CMenu;
}

CDynamicMenu::~CDynamicMenu()
{
 if( m_bMenu != NULL)
  m_bMenu = NULL;
 if( m_bMenuItem != NULL)
  m_bMenuItem = NULL;
 delete m_bMenu;
 delete m_bMenuItem;

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
//add new menu item child
void CDynamicMenu::createMenuItemChild()
{
 m_bMenuItemChild = new CMenu;
 m_bMenuItemChild->CreatePopupMenu();
}
//delete menu item child
void CDynamicMenu::deleteMenuItemChild()
{
 if(m_bMenuItemChild != NULL)
  m_bMenuItemChild = NULL;
 delete m_bMenuItemChild;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////
void CDynamicMenu::appendMenuItem(int m_iItemID, CString m_strItemText)
{
 m_bMenuItemChild->AppendMenu(MF_STRING, m_iItemID, m_strItemText);
}
//add new menu
void CDynamicMenu::appenMenu(int m_nMenuPosition, CString m_strMenuText)
{
 m_bMenu->InsertMenu(m_nMenuPosition, MF_BYPOSITION | MF_POPUP,(UINT)m_bMenuItemChild->m_hMenu, m_strMenuText);
 deleteMenuItemChild();

}
/////////////////////////////////////////////////////////////////////////////////////////////////////////
//setting menu enable 
void CDynamicMenu::setEnable(CString m_strMenu, int m_iItemID, int m_enable)
{
 int m_iPos;
 m_iPos = FindMenuItem(m_bMenu, m_strMenu);
 getMenuItem(m_iPos);
 m_bMenuItem->EnableMenuItem(m_iItemID,m_enable);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
//delete menu 
void CDynamicMenu::deleteMenu()
{
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////
//add menu 
void CDynamicMenu::addMenu(CString m_strMenu, int m_iPosition, int m_iMenuID)
{
 ASSERT_VALID(m_bMenu);
 ASSERT(m_strMenu);
 m_bMenu->InsertMenu(m_iPosition, MF_STRING | MF_ENABLED | MF_BYPOSITION, m_iMenuID, m_strMenu);
}
//add menu 
void CDynamicMenu::addMenu(CString m_strMenu,CString m_strAddMenu, int m_iMenuID)
{
 int m_iPos;
 m_iPos = FindMenuItem(m_bMenu, m_strMenu);
 appenMenu(m_iPos + 1, m_strAddMenu);
 //addMenu(m_strAddMenu, m_iPos + 1, m_iMenuID);
}
//add menu item
void CDynamicMenu::addMenuItem(CString m_strMenu, int m_iPosition, int m_iMenuID)
{
 ASSERT_VALID(m_bMenuItem);
 ASSERT(m_strMenu);
 m_bMenuItem->InsertMenu(m_iPosition, MF_STRING | MF_ENABLED | MF_BYPOSITION, m_iMenuID, m_strMenu);
}

//add menu item 
void CDynamicMenu::addMenuItem(CString m_strMenu, CString m_strMenuItem, int m_iMenuItemID)
{
 /*int m_iPos;
 getMenu();
 m_iPos = this->FindMenuItem(m_bMenu, m_strMenu);
 getMenuItem(m_iPos);
 addMenuItem(m_strMenuItem, getMenuItemCount(m_bMenuItem),m_iMenuItemID);*/
}

//add menu item
void CDynamicMenu::addMenuItem(CString m_strMenu, CString m_strMenuItem, CString m_strMenuPosition, int m_iMenuItemID)
{
 int m_iPos, m_iItemPos;
 getMenu();
 m_iPos = FindMenuItem(m_bMenu, m_strMenu);
 getMenuItem(m_iPos);
    m_iItemPos = FindMenuItem(m_bMenuItem, m_strMenuPosition);
 addMenuItem(m_strMenuItem, m_iItemPos + 1,m_iMenuItemID);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////
//modify menu item 
void CDynamicMenu::modifyMenuItem(CString m_strMneu, int m_iMenuItemID)
{
 m_bMenu->ModifyMenu(m_iMenuItemID, MF_BYCOMMAND, m_iMenuItemID, m_strMneu);
}
//modify menu item
void CDynamicMenu::modifyMenuItem(CString m_strMenu, CString m_strMenuItem, CString m_strModiyText)
{
 int m_iPos;
 getMenu();
 m_iPos = FindMenuItem(m_bMenu, m_strMenu);
    getMenuItem(m_iPos);
 m_iPos = FindMenuItem(m_bMenuItem, m_strMenuItem);
 int id = m_bMenuItem->GetMenuItemID(m_iPos);
 modifyMenuItem(m_strModiyText, id);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////
CMenu* CDynamicMenu::getMenuItem(int m_iPosition)
{
 m_bMenuItem = m_bMenu->GetSubMenu(m_iPosition);
 ASSERT(m_bMenuItem);
 return m_bMenuItem;
}

int CDynamicMenu::FindMenuItem(CMenu* Menu, LPCTSTR MenuString)
{
   CString m_strMenu;
   ASSERT(Menu);
   ASSERT(::IsMenu(Menu->GetSafeHmenu()));

   int count = getMenuItemCount(Menu);
   for (int i = 0; i < count; i++)
   {
      if(Menu->GetMenuString(i, m_strMenu, MF_BYPOSITION) && 
   (strcmp(m_strMenu, MenuString) == 0))
         return i;
   }
   return -1;
}

int CDynamicMenu::getMenuItemCount(CMenu* Menu)
{
 if(Menu != NULL)
  return Menu->GetMenuItemCount();
 else 
  return 0;
}

void CDynamicMenu::setMenu()
{
 ASSERT(m_bMenu);
 ASSERT(::IsMenu(m_bMenu->GetSafeHmenu()));
 AfxGetMainWnd()->SetMenu(m_bMenu);
}

CMenu* CDynamicMenu::getMenu()
{ 
 m_bMenu = AfxGetMainWnd()->GetMenu();
    ASSERT_VALID(m_bMenu);
 return m_bMenu;
}

void CDynamicMenu::drawMenuBar()
{
 AfxGetMainWnd()->DrawMenuBar();
}

void CDynamicMenu::createMenu()
{
 m_bMenu->CreateMenu();
 ASSERT_VALID(m_bMenu);
}

void CDynamicMenu::createMenuItem()
{
 VERIFY(m_bMenuItem->CreateMenu());
 ASSERT_VALID(m_bMenuItem);
}
////////////////////////////////
/////////////////// ²âÊÔ´úÂëÈçÏÂ //////////////////////////

