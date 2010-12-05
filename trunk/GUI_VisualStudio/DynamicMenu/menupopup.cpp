#include "stdafx.h"
#include "MenuPopup.h"
#include "../resource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


MenuPopup::MenuPopup()
{}

MenuPopup::~MenuPopup()
{}

void MenuPopup::Create(std::list<MenuItem>& _List)
{
	m_Items= _List;
}

CMenu* MenuPopup::GetPopup()
{
	CMenu* pTempMenu;
	CMenu* pMenu= new CMenu();

	if(pMenu && pMenu->LoadMenu(IDR_DYNAMIC_POPUP)){
		pTempMenu= pMenu->GetSubMenu(0);
		if(pTempMenu){
			_FillMenu(pTempMenu);
		}
	}
	return pMenu;
}

void MenuPopup::AddToMenu(CMenu* _pMenu)
{
	_FillMenu(_pMenu);
}

void MenuPopup::_FillMenu(CMenu* _pMenu)
{
	ASSERT(_pMenu);
	if(_pMenu)
	{
		int iPos;
		for (iPos = _pMenu->GetMenuItemCount()-1; iPos >= 0; --iPos){
			_pMenu->DeleteMenu(iPos, MF_BYPOSITION);
		}


		std::list<MenuItem>::const_iterator Iter;
		UINT nID;
		MENUITEMINFO info;
		CString sName;
		info.cbSize = sizeof (MENUITEMINFO); // must fill up this field

		for(Iter= m_Items.begin(); Iter!= m_Items.end(); ++Iter)
		{
			nID= (*Iter).GetCommandID();
			if(ID_SEPARATOR==nID){
				_pMenu->AppendMenu(MF_SEPARATOR);
			}
			else
			{
				sName.Format(_T(" %s"),(*Iter).GetDisplayName());	//add space char to avoid sticking the icon
				_pMenu->AppendMenu(MF_STRING, nID, sName);

				info.fMask=		MIIM_BITMAP;
				info.hbmpItem=	_LoadBitmap((*Iter).GetIconFileName());
				_pMenu->SetMenuItemInfo(nID, &info);
			}
		}
	}
}


HBITMAP MenuPopup::_LoadBitmap(const CString& _sName)
{
	HBITMAP hBitmap= (HBITMAP)::LoadImage( NULL,
                _sName,
                IMAGE_BITMAP,
                0,
                0,
                LR_LOADFROMFILE | LR_LOADMAP3DCOLORS 
                );
	return hBitmap;
}
