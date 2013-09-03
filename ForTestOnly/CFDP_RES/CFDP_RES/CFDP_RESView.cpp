
// CFDP_RESView.cpp : implementation of the CCFDP_RESView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "CFDP_RES.h"
#endif

#include "CFDP_RESDoc.h"
#include "CFDP_RESView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CCFDP_RESView

IMPLEMENT_DYNCREATE(CCFDP_RESView, CView)

BEGIN_MESSAGE_MAP(CCFDP_RESView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CCFDP_RESView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CCFDP_RESView construction/destruction

CCFDP_RESView::CCFDP_RESView()
{
	// TODO: add construction code here

}

CCFDP_RESView::~CCFDP_RESView()
{
}

BOOL CCFDP_RESView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CCFDP_RESView drawing

void CCFDP_RESView::OnDraw(CDC* /*pDC*/)
{
	CCFDP_RESDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
}


// CCFDP_RESView printing


void CCFDP_RESView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CCFDP_RESView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CCFDP_RESView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CCFDP_RESView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CCFDP_RESView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CCFDP_RESView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CCFDP_RESView diagnostics

#ifdef _DEBUG
void CCFDP_RESView::AssertValid() const
{
	CView::AssertValid();
}

void CCFDP_RESView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CCFDP_RESDoc* CCFDP_RESView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCFDP_RESDoc)));
	return (CCFDP_RESDoc*)m_pDocument;
}
#endif //_DEBUG


// CCFDP_RESView message handlers
