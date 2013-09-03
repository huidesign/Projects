#pragma once
#include "afxwin.h"


// CTestDlg dialog

class CTestDlg : public CDialog
{
	DECLARE_DYNAMIC(CTestDlg)

public:
	CTestDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CTestDlg();

// Dialog Data
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnClickedAdd();
private:
	CButton m_btn;
	bool m_blsCreate;
public:
	afx_msg void OnClickedStaticOne();
	int m_num1;
	int m_num2;
	int m_num3;
	CEdit m_edit1;
	CEdit m_edit2;
	CEdit m_edit3;
	afx_msg void OnBnClickedShrink();
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
};
