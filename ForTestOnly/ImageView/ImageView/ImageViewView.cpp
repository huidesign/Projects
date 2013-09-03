
// ImageViewView.cpp : implementation of the CImageViewView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "ImageView.h"
#endif

#include "ImageViewDoc.h"
#include "ImageViewView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CImageViewView

IMPLEMENT_DYNCREATE(CImageViewView, CView)

BEGIN_MESSAGE_MAP(CImageViewView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CImageViewView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CImageViewView construction/destruction

CImageViewView::CImageViewView()
{
	// TODO: add construction code here

}

CImageViewView::~CImageViewView()
{
}

BOOL CImageViewView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CImageViewView drawing

void CImageViewView::OnDraw(CDC* /*pDC*/)
{
	CImageViewDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
}


// CImageViewView printing


void CImageViewView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CImageViewView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CImageViewView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CImageViewView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CImageViewView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CImageViewView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CImageViewView diagnostics

#ifdef _DEBUG
void CImageViewView::AssertValid() const
{
	CView::AssertValid();
}

void CImageViewView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CImageViewDoc* CImageViewView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CImageViewDoc)));
	return (CImageViewDoc*)m_pDocument;
}
#endif //_DEBUG


// CImageViewView message handlers
