// NotifyCombo.h : header file
//
#if !defined(__NOTIFYCOMBO_H__)
#define __NOTIFYCOMBO_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CNotifyCombo - Helper template that allows for sending notification messages
// to the combo box owner when certain keys are pressed.
//
template<class BASE_CLASS>
class CNotifyCombo : public BASE_CLASS
{
public:
	
	CNotifyCombo()
	{
	}
	
	virtual ~CNotifyCombo()
	{
	}

	void NotifyOwner(UINT nCode)
	{
		NMHDR nm;
		nm.hwndFrom = m_hWnd;
		nm.idFrom = GetDlgCtrlID();
		nm.code = nCode;

		CWnd* pWndOwner = GetOwner();
		if ( pWndOwner )
		{
			pWndOwner->SendMessage( WM_NOTIFY, nm.idFrom, ( LPARAM )&nm );
		}
	}

	virtual BOOL PreTranslateMessage(MSG* pMsg)
	{
		if ( pMsg->message == WM_KEYDOWN )
		{
			switch (pMsg->wParam)
			{
			case VK_ESCAPE:
			case VK_RETURN:
				if ( GetDroppedState( ) == TRUE )
				{
					ShowDropDown( false );
				}
				NotifyOwner( NM_RETURN );
				return TRUE;
				
			case VK_UP:
			case VK_DOWN:
				if ( ( ::GetKeyState( VK_MENU ) >= 0 ) &&
					( ::GetKeyState( VK_CONTROL ) >= 0 ) && 
					( GetDroppedState( ) == FALSE ) )
				{
					ShowDropDown( true );
					return TRUE;
				}
			}
		}
		
		return BASE_CLASS::PreTranslateMessage(pMsg);
	}
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(__NOTIFYCOMBO_H__)
