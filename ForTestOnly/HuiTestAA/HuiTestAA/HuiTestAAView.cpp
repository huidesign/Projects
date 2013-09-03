
// HuiTestAAView.cpp : implementation of the CHuiTestAAView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "HuiTestAA.h"
#endif

#include "HuiTestAADoc.h"
#include "HuiTestAAView.h"
#include "TestDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CHuiTestAAView

IMPLEMENT_DYNCREATE(CHuiTestAAView, CView)

BEGIN_MESSAGE_MAP(CHuiTestAAView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CHuiTestAAView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(IDM_DIALOG, &CHuiTestAAView::OnDialog)
END_MESSAGE_MAP()

// CHuiTestAAView construction/destruction

CHuiTestAAView::CHuiTestAAView()
	: m_pdlg(NULL)
{
	// TODO: add construction code here

}

CHuiTestAAView::~CHuiTestAAView()
{
	delete m_pdlg;
}

BOOL CHuiTestAAView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CHuiTestAAView drawing

void CHuiTestAAView::OnDraw(CDC* /*pDC*/)
{
	CHuiTestAADoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
}


// CHuiTestAAView printing


void CHuiTestAAView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CHuiTestAAView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CHuiTestAAView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CHuiTestAAView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CHuiTestAAView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CHuiTestAAView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CHuiTestAAView diagnostics

#ifdef _DEBUG
void CHuiTestAAView::AssertValid() const
{
	CView::AssertValid();
}

void CHuiTestAAView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CHuiTestAADoc* CHuiTestAAView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CHuiTestAADoc)));
	return (CHuiTestAADoc*)m_pDocument;
}
#endif //_DEBUG


// CHuiTestAAView message handlers


void CHuiTestAAView::OnDialog()
{
	// TODO: Add your command handler code here
	//CTestDlg dlg;
	//dlg.DoModal();

	m_pdlg = new CTestDlg;
	m_pdlg->Create(IDD_DIALOG1, this);
	m_pdlg->ShowWindow(SW_SHOW);
}
