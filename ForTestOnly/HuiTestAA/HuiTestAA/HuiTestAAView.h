
// HuiTestAAView.h : interface of the CHuiTestAAView class
//

#pragma once
#include "TestDlg.h"


class CHuiTestAAView : public CView
{
protected: // create from serialization only
	CHuiTestAAView();
	DECLARE_DYNCREATE(CHuiTestAAView)

// Attributes
public:
	CHuiTestAADoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CHuiTestAAView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnDialog();
private:
	// Create an non-modal window
	CTestDlg* m_pdlg;
};

#ifndef _DEBUG  // debug version in HuiTestAAView.cpp
inline CHuiTestAADoc* CHuiTestAAView::GetDocument() const
   { return reinterpret_cast<CHuiTestAADoc*>(m_pDocument); }
#endif

