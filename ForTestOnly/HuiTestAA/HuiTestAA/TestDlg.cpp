// TestDlg.cpp : implementation file
//

#include "stdafx.h"
#include "HuiTestAA.h"
#include "TestDlg.h"
#include "afxdialogex.h"


// CTestDlg dialog

IMPLEMENT_DYNAMIC(CTestDlg, CDialog)

CTestDlg::CTestDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTestDlg::IDD, pParent)
	, m_blsCreate(false)
{
	m_num1 = 0;
	m_num2 = 0;
	m_num3 = 0;	
}

CTestDlg::~CTestDlg()
{
}

void CTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_NUM1, m_num1);
	DDX_Text(pDX, IDC_NUM2, m_num2);
	DDX_Text(pDX, IDC_NUM3, m_num3);
	DDX_Control(pDX, IDC_NUM1, m_edit1);
	DDX_Control(pDX, IDC_NUM2, m_edit2);
	DDX_Control(pDX, IDC_NUM3, m_edit3);
}


BEGIN_MESSAGE_MAP(CTestDlg, CDialog)
	ON_BN_CLICKED(IDC_ADD, &CTestDlg::OnClickedAdd)
	ON_STN_CLICKED(IDC_STATIC_ONE, &CTestDlg::OnClickedStaticOne)
	ON_BN_CLICKED(IDC_SHRINK, &CTestDlg::OnBnClickedShrink)
	ON_BN_CLICKED(IDOK, &CTestDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CTestDlg message handlers


void CTestDlg::OnClickedAdd()
{
	// TODO: Add your control notification handler code here
	/*if (m_blsCreate == false)
	{
		m_btn.Create(_T("Huidesign"), BS_DEFPUSHBUTTON | WS_VISIBLE | WS_CHILD, 
			CRect(0, 0, 100, 100), this, 123);
		m_blsCreate = true;
	}
	else
	{
		m_btn.DestroyWindow();
		m_blsCreate = false;
	}

	if (m_btn.m_hWnd)
		m_btn.DestroyWindow();
	m_btn.Create(_T("Huidesign"), BS_DEFPUSHBUTTON | WS_VISIBLE | WS_CHILD, 
		CRect(0, 0, 100, 100), this, 123);*/

	//int num1, num2, num3;
	//CString str1, str2, str3;

	//GetDlgItem(IDC_NUM1)->GetWindowText(str1);
	//GetDlgItem(IDC_NUM2)->GetWindowText(str2);

// 	num1 = _ttoi(str1);
// 	num2 = _ttoi(str2);
// 	num3 = num1 + num2;
// 	_itoa(num3, str3.GetBuffer(10), 10);
// 	str3.ReleaseBuffer();
	//GetDlgItem(IDC_NUM3)->SetWindowText(str3);

// 	GetDlgItemText(IDC_NUM1, str1);
// 	GetDlgItemText(IDC_NUM2, str2);
// 	num1 = _ttoi(str1);
// 	num2 = _ttoi(str2);
// 	num3 = num1 + num2;
// 	_itoa(num3, str3.GetBuffer(10), 10);
// 	str3.ReleaseBuffer();
// 	SetDlgItemText(IDC_NUM3, str3);
	//SetWindowText(str3);	// This is funny!

	/*UpdateData();
	m_num3 = m_num1 + m_num2;
	UpdateData(FALSE);*/


	char ch1[10], ch2[10], ch3[10];
	m_edit1.GetWindowText(ch1, 10);
	m_edit2.GetWindowText(ch2, 10);

	int num1 = atoi(ch1);
	int num2 = atoi(ch2);
	int num3 = num1 + num2;
	itoa(num3, ch3, 10);

	m_edit3.SetWindowText(ch3);

	/*char ch1[10], ch2[10], ch3[10];

	::SendMessage(GetDlgItem(IDC_NUM1)->m_hWnd, WM_GETTEXT, 10, (LPARAM)ch1);
	//::SendMessage(m_edit1.m_hWnd, WM_GETTEXT, 10, (LPARAM)ch1);
	//GetDlgItem(IDC_NUM1)->SendMessage(WM_GETTEXT, 10, (LPARAM)ch1);
	m_edit1.SendMessage(WM_GETTEXT, 10, (LPARAM)ch1);
	m_edit2.SendMessage(WM_GETTEXT, 10, (LPARAM)ch2);

	int num1 = atoi(ch1);
	int num2 = atoi(ch2);
	int num3 = num1 + num2;
	itoa(num3, ch3, 10);

	m_edit3.SendMessage(WM_SETTEXT, 0, (LPARAM)ch3);*/

	/*char ch1[10], ch2[10], ch3[10];
	SendDlgItemMessage(IDC_NUM1, WM_GETTEXT, 10, (LPARAM)ch1);
	SendDlgItemMessage(IDC_NUM2, WM_GETTEXT, 10, (LPARAM)ch2);
	int num1 = atoi(ch1);
	int num2 = atoi(ch2);
	int num3 = num1 + num2;
	itoa(num3, ch3, 10);
	SendDlgItemMessage(IDC_NUM3, WM_SETTEXT, 0, (LPARAM)ch3);
	SendDlgItemMessage(IDC_NUM3, EM_SETSEL, 0, -1);
	m_edit3.SetFocus();*/
}


void CTestDlg::OnClickedStaticOne()
{
	// TODO: Add your control notification handler code here
	CString str;
	if(GetDlgItem(IDC_STATIC_ONE)->GetWindowText(str),
		str == _T("Number 1:"))
	{
		GetDlgItem(IDC_STATIC_ONE)->SetWindowText(_T("ÊýÖµ1£º"));
	}
	else
	{
		GetDlgItem(IDC_STATIC_ONE)->SetWindowText(_T("Number 1:"));
	}
}


void CTestDlg::OnBnClickedShrink()
{
	// TODO: Add your control notification handler code here
	CString str;
	if (GetDlgItemText(IDC_SHRINK, str), str == _T("Shrink<<"))
	{
		SetDlgItemText(IDC_SHRINK, _T("Expand>>"));
	}
	else
	{
		SetDlgItemText(IDC_SHRINK, _T("Shrink<<"));
	}

	static CRect rectLarge;
	static CRect rectSmall;

	if (rectLarge.IsRectNull())
	{
		CRect rectSeparator;
		GetWindowRect(&rectLarge);
		GetDlgItem(IDC_SEPERATOR)->GetWindowRect(&rectSeparator);

		rectSmall.left   = rectLarge.left;
		rectSmall.top    = rectLarge.top;
		rectSmall.right  = rectLarge.right;
		rectSmall.bottom = rectSeparator.bottom;
	}
	if (str == _T("Shrink<<"))
	{
		SetWindowPos(NULL, 0, 0, rectSmall.Width(), rectSmall.Height(),
			SWP_NOMOVE | SWP_NOZORDER);
	}
	else
	{
		SetWindowPos(NULL, 0, 0, rectLarge.Width(), rectLarge.Height(),
			SWP_NOMOVE | SWP_NOZORDER);
	}
}


void CTestDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	//GetDlgItem(IDC_NUM1)->GetNextWindow()->SetFocus();
	//GetFocus()->GetNextWindow()->SetFocus();
	//GetFocus()->GetWindow(GW_HWNDNEXT)->SetFocus();
	GetNextDlgTabItem(GetFocus())->SetFocus();
	//CDialog::OnOK();
}

WNDPROC prevPorc;	// Need Multi_line option checked.
LRESULT CALLBACK WinHuiProc (
	HWND   hwnd,
	UINT   uMsg,
	WPARAM wParam,
	LPARAM lParam)
{
	if (uMsg == WM_CHAR && wParam == 0x0d)
	{
		//::SetFocus(::GetNextWindow(hwnd, GW_HWNDNEXT));
		//::SetFocus(::GetWindow(hwnd, GW_HWNDNEXT));
		::SetFocus(::GetNextDlgTabItem(::GetParent(hwnd), hwnd, FALSE));
		return 1;
	}
	else
	{
		return prevPorc(hwnd, uMsg, wParam, lParam);
	}
}

BOOL CTestDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	prevPorc = (WNDPROC)SetWindowLong(GetDlgItem(IDC_NUM1)->m_hWnd, 
		GWL_WNDPROC, (LONG)WinHuiProc);
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
