
// MfcRtiTestAADlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MfcRtiTestAA.h"
#include "MfcRtiTestAADlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMfcRtiTestAADlg �Ի���




CMfcRtiTestAADlg::CMfcRtiTestAADlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMfcRtiTestAADlg::IDD, pParent)
	, m_pCHitChat(NULL)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
//	m_federateName = _T("");
}

void CMfcRtiTestAADlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
//	DDX_Text(pDX, IDC_EDIT_FederateName, m_federateName);
	DDX_Control(pDX, IDC_EDIT_FederateName, m_edtFederateName);
}

BEGIN_MESSAGE_MAP(CMfcRtiTestAADlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_JoinFederation, &CMfcRtiTestAADlg::OnBnClickedJoinfederation)
	ON_BN_CLICKED(IDC_ExitFederation, &CMfcRtiTestAADlg::OnBnClickedExitfederation)
	ON_BN_CLICKED(IDOK, &CMfcRtiTestAADlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CMfcRtiTestAADlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// CMfcRtiTestAADlg ��Ϣ�������

BOOL CMfcRtiTestAADlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CMfcRtiTestAADlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CMfcRtiTestAADlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CMfcRtiTestAADlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMfcRtiTestAADlg::OnBnClickedJoinfederation()
{
	// TODO: Add your control notification handler code here
	//UpdateData(TRUE);
	char tmp[256];
	m_edtFederateName.GetWindowText(tmp, 256);
	m_pCHitChat = new CHitChat(tmp);
	//UpdateData(FALSE);
	m_pCHitChat->InitFederate();
}


void CMfcRtiTestAADlg::OnBnClickedExitfederation()
{
	// TODO: Add your control notification handler code here
	if(m_pCHitChat != NULL)
	{
		delete m_pCHitChat;
		m_pCHitChat = NULL;
	}
	//m_pCHitChat->~CHitChat();
}


void CMfcRtiTestAADlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	if (m_pCHitChat)
	{
		delete m_pCHitChat;
		m_pCHitChat = NULL;
	}
	CDialogEx::OnOK();
}


void CMfcRtiTestAADlg::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	if (m_pCHitChat)
	{
		delete m_pCHitChat;
		m_pCHitChat = NULL;
	}
	CDialogEx::OnCancel();
}
