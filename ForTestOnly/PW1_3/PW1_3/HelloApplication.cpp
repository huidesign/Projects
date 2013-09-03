#include <afxwin.h>
#include "HelloApplication.h"
#define _AFXDLL
#define HUI_USE_BRUSH

#ifdef HUI_USE_POLYLINE
#include <cmath>
#define SEGMENTS 500
#define PI 3.1415926
#endif

#ifdef HUI_USE_PIECHART
#include <cmath>
#define PI 3.1415926
#endif

CMyApp myApp;

/************************************************************************/
/* CMyApp member functions                                              */
/************************************************************************/

BOOL CMyApp::InitInstance()
{
	m_pMainWnd = new CMainWindow;

	m_pMainWnd->ShowWindow(m_nCmdShow);
	m_pMainWnd->UpdateWindow();
	return TRUE;
}

/************************************************************************/
/* CMainWindow message map and member functions                         */
/************************************************************************/

BEGIN_MESSAGE_MAP(CMainWindow, CFrameWnd)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
//	ON_MESSAGE(WM_SETTEXT, OnSetText)
END_MESSAGE_MAP()

CMainWindow::CMainWindow()
{
	Create(NULL, L"The Hello Application");
}

void CMainWindow::OnPaint()
{
	/************************************************************************/
	/* Common Sectioon                                                      */
	/************************************************************************/
	CPaintDC dc(this);	// Can be used only in this function
	CRect rect;
	GetClientRect(&rect);

	/************************************************************************/
	/* I Miss You, Haili!                                                   */
	/************************************************************************/
#if defined(HUI_LOVE_HAILI)
	CFont font;
	//font.CreatePointFont(360, _T("Castellar"));
	LOGFONT lf;
	::ZeroMemory (&lf, sizeof (lf));
	lf.lfHeight = 360;
	lf.lfWeight = FW_BOLD;
	lf.lfItalic = TRUE;
	::lstrcpy (lf.lfFaceName, _T ("Castellar"));
	font.CreatePointFontIndirect (&lf);
	dc.SelectObject(&font);
	dc.SetBkMode(TRANSPARENT);

	CString string = _T("Haili I Miss You!");

	rect.OffsetRect(16, 16);	// Move Left 16, Bottom 16
	dc.SetTextColor(RGB(192, 192, 192));
	dc.DrawTextW(string, &rect, 
		DT_SINGLELINE | DT_CENTER | DT_VCENTER);

	rect.OffsetRect(-16, -16);	// Move Back
	dc.SetTextColor(RGB(0, 0, 0));
	dc.DrawTextW(string, &rect, 
		DT_SINGLELINE | DT_CENTER | DT_VCENTER);
#endif

	/************************************************************************/
	/* Use Rotated Text                                                     */
	/************************************************************************/
#if defined(HUI_USE_ROTATEXT)
	dc.SetViewportOrg(rect.Width() / 2, rect.Height() / 2);
	dc.SetBkMode(TRANSPARENT);

	for (int i = 0; i < 3600; i += 150) {
		LOGFONT lf;
		::ZeroMemory (&lf, sizeof(lf));
		lf.lfHeight = 160;
		lf.lfWeight = FW_BOLD;
		lf.lfEscapement = i;
		lf.lfOrientation = i;
		::lstrcpy (lf.lfFaceName, _T("Arial"));

		CFont font;
		font.CreatePointFontIndirect(&lf);

		dc.SelectObject(&font);
		//CFont *pOldFont = dc.SelectObject(&font);
		dc.TextOutW (0, 0, CString (_T ("          Hello, Haili")));
		//dc.SelectObject(pOldFont);	// Store and Restore the Original Font Setting For What???
	}
#endif

	/************************************************************************/
	/* Use GetTextExtent and SetTextJustification                           */
	/************************************************************************/
#if defined(HUI_USE_DRAWFUNC)
	CString string = _T ("Now is The Time");
	CSize size = dc.GetTextExtent(string);
	dc.SetTextJustification(rect.Width() - size.cx, 3);
	dc.TextOutW (0, 100, string);
#endif

	/************************************************************************/
	/* Draw a Sinusoidal Line                                                                  */
	/************************************************************************/
#if defined(HUI_USE_POLYLINE)
	int nWidth = rect.Width();
	int nHeight = rect.Height();

	CPoint aPoint[SEGMENTS];

	for(int i = 0; i < SEGMENTS; i++) {
		aPoint[i].x = (i * nWidth) / SEGMENTS;
		aPoint[i].y = (int) ((nHeight / 2) * 
			(1 - sin ((2 * PI * i) / SEGMENTS)));
	}
	dc.Polyline(aPoint, SEGMENTS);
#endif

	/************************************************************************/
	/* »­NIKE±ê¼Ç                                                           */
	/************************************************************************/
#if defined(HUI_USE_POLYBEZIER)
	POINT aPoint1[4] = { 120, 100, 120, 200, 250, 150, 500, 40 };
	POINT aPoint2[4] = { 120, 100,  50, 350, 250, 200, 500, 40 };
	dc.PolyBezier (aPoint1, 4);
	dc.PolyBezier (aPoint2, 4);
#endif

	/************************************************************************/
	/* Draw a pie chart                                                     */
	/************************************************************************/
#if defined(HUI_USE_PIECHART)
	int nRevenues[4] = {125, 376, 252, 184};
	dc.SetViewportOrg(rect.Width() / 2, rect.Height() / 2);

	int nTotal = 0;
	for (int i = 0; i < 4; i++)
		nTotal += nRevenues[i];

	int x1 = 0;
	int y1 = -1000;
	int nSum = 0;

	for (int i = 0; i < 3; i++) {
		nSum += nRevenues[i];
		double rad = ((double) (nSum * 2 * PI) / (double) nTotal) + PI;
		int x2 = (int) (sin (rad) * 1000);
		int y2 = (int) (cos (rad) * 1000 * 3) / 4;
		dc.Pie(-200, -150, 200, 150, x1, y1, x2, y2);
		x1 = x2;
		y1 = y2;
	}
#endif 

	/************************************************************************/
	/* Extended Pens                                                                    */
	/************************************************************************/
#if defined(HUI_USE_EXTPENS)
	LOGBRUSH lb;
	lb.lbStyle = BS_SOLID;
	lb.lbColor = RGB(0, 0, 255);
	CPen pen (PS_GEOMETRIC | PS_SOLID | PS_ENDCAP_FLAT |
		PS_JOIN_ROUND, 16, &lb);

	dc.BeginPath();
	dc.MoveTo(0, 0);
	dc.LineTo(100, 200);
	dc.LineTo(200, 100);
	dc.CloseFigure();
	dc.EndPath();
	dc.StrokePath();
#endif

	/************************************************************************/
	/* Use GDI Brushes and the CBrush Class                                 */
	/************************************************************************/
#if defined(HUI_USE_BRUSH)
	// First Solution
	//CPen pen (PS_NULL, 0, (RGB (0, 0, 0)));
	//dc.SelectObject(&pen);
	//CBrush brush (RGB (192, 192, 192));
	//dc.SelectObject(&brush);

	// Second Solution
	//dc.SelectStockObject(NULL_PEN);
	//dc.SelectStockObject(LTGRAY_BRUSH);

	// Third Solution
	CPen pen;
	pen.CreateStockObject (NULL_PEN);
	dc.SelectObject (&pen);

	CBrush brush;
	brush.CreateStockObject (LTGRAY_BRUSH);
	dc.SelectObject (&brush);

	dc.Ellipse(0, 0, 1000, 500);
#endif
}

void CMainWindow::OnLButtonDown(UINT nFlags, CPoint point)
{
	MessageBoxW(_T("LButtonDown!"));
}