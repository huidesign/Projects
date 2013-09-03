#include <afxwin.h>
#include "RulerApp.h"

CMyApp myApp;

/************************************************************************/
/* CMyApp Member Function                                               */
/************************************************************************/

BOOL CMyApp::InitInstance()
{
	m_pMainWnd = new CMainWindow;
	m_pMainWnd->ShowWindow(m_nCmdShow);
	m_pMainWnd->UpdateWindow();
	return TRUE;
}

/************************************************************************/
/* CMainWindow Message Map and Member Function                          */
/************************************************************************/

BEGIN_MESSAGE_MAP (CMainWindow, CFrameWnd)
	ON_WM_PAINT()
END_MESSAGE_MAP()

CMainWindow::CMainWindow()
{
	Create(NULL, _T("Ruler"), WS_OVERLAPPEDWINDOW | WS_VSCROLL);
}

void CMainWindow::OnPaint()
{
	CPaintDC dc(this);

	/************************************************************************/
	/* Initialize the device                                                */
	/************************************************************************/
	dc.SetMapMode(MM_LOENGLISH);
	dc.SetTextAlign(TA_CENTER | TA_BOTTOM);
	dc.SetBkMode(TRANSPARENT);

	/************************************************************************/
	/* Draw the body of the ruler                                           */
	/************************************************************************/
	CBrush brush(RGB(255, 255, 0));
	CBrush* pOldBrush = dc.SelectObject(&brush);
	dc.Rectangle(0, 0, 1200, -100);

	/************************************************************************/
	/* Draw the tick marks and labels.                                      */
	/************************************************************************/
	for(int i = 25; i < 1200; i += 25) {
		dc.MoveTo(i, -92);
		dc.LineTo(i, -100);
	}

	for(int i = 50; i < 1200; i += 50) {
		dc.MoveTo(i, -84);
		dc.LineTo(i, -100);
	}

	for(int i = 100; i < 1200; i += 100) {
		dc.MoveTo(i, -75);
		dc.LineTo(i, -100);

		CString string;
		string.Format(_T("%d"), (i / 100) - 1);
		dc.TextOutW(i, -75, string);
	}
}