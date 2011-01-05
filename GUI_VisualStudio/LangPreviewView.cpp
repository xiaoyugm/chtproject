// LangPreviewView.cpp: Implementierung der Klasse CLangPreviewView.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "LangPreviewView.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Konstruktion/Destruktion
//////////////////////////////////////////////////////////////////////

IMPLEMENT_DYNCREATE(CLangPreviewView, CPreviewView)

BEGIN_MESSAGE_MAP(CLangPreviewView, CPreviewView)
	//{{AFX_MSG_MAP(CLangPreviewView)
	ON_UPDATE_COMMAND_UI(AFX_ID_PREVIEW_NUMPAGE, OnUpdateNumPageChange)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CLangPreviewView::CLangPreviewView()
{
}

CLangPreviewView::~CLangPreviewView()
{

}

void CLangPreviewView::OnActivateView(BOOL bActivate, CView*, CView*)
{
	if (bActivate)
	{
		if (m_pToolBar) {
			m_pToolBar->GetDlgItem(AFX_ID_PREVIEW_PRINT)->SetWindowText( _T("��ӡ(&P)..."));
			m_pToolBar->GetDlgItem(AFX_ID_PREVIEW_NEXT)->SetWindowText(_T("��һҳ(&N)"));
			m_pToolBar->GetDlgItem(AFX_ID_PREVIEW_PREV)->SetWindowText(_T("��һҳ(&V)"));
			//m_pToolBar->GetDlgItem(AFX_ID_PREVIEW_NUMPAGE)->SetWindowText(CDic::GetText(_T("Preview"), _T("NUMPAGE"), _T("")));
			m_pToolBar->GetDlgItem(AFX_ID_PREVIEW_ZOOMIN)->SetWindowText(_T("�Ŵ�(&I)"));
			m_pToolBar->GetDlgItem(AFX_ID_PREVIEW_ZOOMOUT)->SetWindowText(_T("��С(&O)"));
			m_pToolBar->GetDlgItem(AFX_ID_PREVIEW_CLOSE)->SetWindowText(_T("�ر�(&C)"));
		}
	}
/*
//                      English      Italian         French          Spanish        German
AFX_ID_PREVIEW_PRINT	  "&Print..."  "Stam&pa..."    "&Imprimer..."  "&Imprimir..." "&Drucken..."
AFX_ID_PREVIEW_NEXT	    "&Next Page" "Pag. &succes." "&Suivante"     "&Siguiente"   "&N�chste"
AFX_ID_PREVIEW_PREV	    "Pre&v Page" "Pag. p&reced." "&Pr�c�dente"   "&Anterior"    "&Vorherige"
AFX_ID_PREVIEW_NUMPAGE	""
AFX_ID_PREVIEW_ZOOMIN	  "Zoom &In"   "Ingrand&isci"  "Zoom ava&nt"   "Ac&ercar"     "Ver&gr��ern"
AFX_ID_PREVIEW_ZOOMOUT	"Zoom &Out"  "Ri&duci"       "Zoom a&rri�re" "A&lejar"      "Ver&kleinern"
AFX_ID_PREVIEW_CLOSE	  "&Close"     "&Chiudi"       "&Fermer"       "&Cerrar"      "&Schlie�en"

AFX_IDS_ONEPAGE         "&One Page"  "&Una pagina"   "&Une page"     "&Una p�gina"  "&Eine Seite"
AFX_IDS_TWOPAGE         "&Two Page"  "&Due pagine"   "&Deux pages"   "&Dos p�ginas" "&Zwei Seiten"

AFX_IDS_PREVIEWPAGEDESC (GBR) "Page %u\nPages %u-%u\n"
AFX_IDS_PREVIEWPAGEDESC (ITA) "Pagina %u\nPagine %u-%u\n"
AFX_IDS_PREVIEWPAGEDESC (FRA) "Page %u\nPages %u-%u\n"
AFX_IDS_PREVIEWPAGEDESC (ESP) "P�gina %u\nP�ginas %u-%u\n"
AFX_IDS_PREVIEWPAGEDESC (GER) "Seite %u\nSeiten %u-%u\n"
*/
}

void CLangPreviewView::OnUpdateNumPageChange(CCmdUI* pCmdUI)
{
	CPreviewView::OnUpdateNumPageChange(pCmdUI);

	UINT nPages = (m_nZoomState == ZOOM_OUT ? m_nPages : m_nZoomOutPages);
	if (nPages == 1)
		pCmdUI->SetText("��ҳ(&T)");
	else
		pCmdUI->SetText("һҳ(&O)");
}
