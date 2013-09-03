
// ChatResearchDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ChatResearch.h"
#include "ChatResearchDlg.h"
#include "afxdialogex.h"
#include "FreeChat.h"
#include "HwFederateAmbassador.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
    CAboutDlg();

    // 对话框数据
    enum { IDD = IDD_ABOUTBOX };

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

    // 实现
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


// CChatResearchDlg 对话框


CChatResearchDlg::CChatResearchDlg(CWnd* pParent /*=NULL*/)
    : CDialogEx(CChatResearchDlg::IDD, pParent)
    , m_pCFreeChat(NULL)
    , m_bCurrentlyJoined(false)
    ,m_uChannel(0)
{
    m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CChatResearchDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_EDIT_FEDNAME, m_tbFederateName);
    DDX_Control(pDX, IDC_COMBO_COLOR, m_cmbColor);
    DDX_Control(pDX, IDC_COMBO_PORTRAIT, m_cmbPortrait);
    DDX_Control(pDX, IDC_COMBO_TARGET, m_cmbTarget);
    DDX_Control(pDX, IDC_RICHEDIT_RECEIVE, m_rtfReceive);
    DDX_Control(pDX, IDC_STATIC_PORTRAIT, m_pctPortrait);
    DDX_Control(pDX, IDC_RICHEDIT_SEND, m_rtfSendMsg);
}

BEGIN_MESSAGE_MAP(CChatResearchDlg, CDialogEx)
    ON_WM_SYSCOMMAND()
    ON_WM_PAINT()
    ON_WM_QUERYDRAGICON()
    ON_BN_CLICKED(IDC_BUTTON_JOIN, &CChatResearchDlg::OnBnClickedButtonJoin)
    ON_BN_CLICKED(IDC_BUTTON_EXIT, &CChatResearchDlg::OnBnClickedButtonExit)
    ON_CBN_SELCHANGE(IDC_COMBO_PORTRAIT, &CChatResearchDlg::OnCbnSelchangeComboPortrait)
    ON_CBN_SELCHANGE(IDC_COMBO_COLOR, &CChatResearchDlg::OnCbnSelchangeComboColor)
    ON_CBN_SELCHANGE(IDC_COMBO_TARGET, &CChatResearchDlg::OnCbnSelchangeComboTarget)
    ON_BN_CLICKED(IDC_BUTTON_SEND, &CChatResearchDlg::OnBnClickedButtonSend)
    ON_BN_CLICKED(IDC_BUTTON_SUBMIT, &CChatResearchDlg::OnBnClickedButtonSubmit)
END_MESSAGE_MAP()


// CChatResearchDlg 消息处理程序

BOOL CChatResearchDlg::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    // 将“关于...”菜单项添加到系统菜单中。
    m_cmbTarget.AddString(_T("Chat Room"));
    m_cmbTarget.AddString(_T("Channel_1"));
    m_cmbTarget.AddString(_T("Channel_2"));
    m_cmbTarget.AddString(_T("Channel_3"));
    m_cmbTarget.AddString(_T("Channel_4"));
    m_cmbTarget.AddString(_T("Channel_5"));
    m_cmbTarget.AddString(_T("Channel_6"));
    m_cmbTarget.AddString(_T("Channel_7"));
    m_cmbTarget.AddString(_T("Channel_8"));
    m_cmbTarget.AddString(_T("Channel_9"));
    m_cmbTarget.SetCurSel(9);

    m_cmbColor.AddString(_T("Red"));
    m_cmbColor.AddString(_T("Green"));
    m_cmbColor.AddString(_T("Blue"));
    m_cmbColor.AddString(_T("Yellow"));
    m_cmbColor.SetCurSel(0);

    m_cmbPortrait.AddString(_T("Gentle Man"));
    m_cmbPortrait.AddString(_T("Chococat"));
    m_cmbPortrait.AddString(_T("Classic Kitty"));
    m_cmbPortrait.AddString(_T("Kitty Angel"));
    m_cmbPortrait.AddString(_T("Penguin"));
    m_cmbPortrait.AddString(_T("Keroppi"));
    m_cmbPortrait.SetCurSel(0);

    // IDM_ABOUTBOX 必须在系统命令范围内。
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

    // 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
    //  执行此操作
    SetIcon(m_hIcon, TRUE);			// 设置大图标
    SetIcon(m_hIcon, FALSE);		// 设置小图标

    // TODO: 在此添加额外的初始化代码

    return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CChatResearchDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CChatResearchDlg::OnPaint()
{
    if (IsIconic())
    {
        CPaintDC dc(this); // 用于绘制的设备上下文

        SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

        // 使图标在工作区矩形中居中
        int cxIcon = GetSystemMetrics(SM_CXICON);
        int cyIcon = GetSystemMetrics(SM_CYICON);
        CRect rect;
        GetClientRect(&rect);
        int x = (rect.Width() - cxIcon + 1) / 2;
        int y = (rect.Height() - cyIcon + 1) / 2;

        // 绘制图标
        dc.DrawIcon(x, y, m_hIcon);
    }
    else
    {
        CDialogEx::OnPaint();
    }
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CChatResearchDlg::OnQueryDragIcon()
{
    return static_cast<HCURSOR>(m_hIcon);
}

void CChatResearchDlg::OnBnClickedButtonJoin()
{
    // TODO: Add your control notification handler code here
    static HwFederateAmbassador fedAmb;
    if (!m_bCurrentlyJoined)
    {
        CString str;
        m_tbFederateName.GetWindowText(str);
        m_pCFreeChat = new CFreeChat;
        fedAmb.SetCChatResearchDlgPointer(this);
        m_pCFreeChat->JoinFreeChat(&fedAmb);
        m_bCurrentlyJoined = true;
    }
}


void CChatResearchDlg::OnBnClickedButtonExit()
{
    // TODO: Add your control notification handler code here
    if (m_bCurrentlyJoined)
    {
        if (m_pCFreeChat)
        {
            m_pCFreeChat->ExitFreeChat();
            m_bCurrentlyJoined = false;
            delete m_pCFreeChat;
            m_pCFreeChat = NULL;
        }
    }
}


void CChatResearchDlg::OnCbnSelchangeComboPortrait()
{
    CString portrait;
    m_cmbPortrait.GetLBText(m_cmbPortrait.GetCurSel(), portrait);
    if (portrait == _T("Gentle Man"))
    {
        SetPortrait(IDB_BITMAP_GENTLEMAN);
    }
    else if (portrait == _T("Chococat"))
    {
        SetPortrait(IDB_BITMAP_CHOCOCAT);
    }
    else if (portrait == _T("Classic Kitty"))
    {
        SetPortrait(IDB_BITMAP_CLASSICKITTY);
    }
    else if (portrait == _T("Kitty Angel"))
    {
        SetPortrait(IDB_BITMAP_KITTYANGEL);
    }
    else if (portrait == _T("Penguin"))
    {
        SetPortrait(IDB_BITMAP_PENGUIN);
    }
    else if (portrait == _T("Keroppi"))
    {
        SetPortrait(IDB_BITMAP_KEROPPI);
    }
}


void CChatResearchDlg::OnCbnSelchangeComboColor()
{
    // TODO: Add your control notification handler code here
    int ballColor;
    CString color;
    m_cmbColor.GetLBText(m_cmbColor.GetCurSel(), color);
    if (color == "Red")
    {
        ballColor = 1;
        m_rtfReceive.SetWindowText(_T("Red!"));
    }
    else if (color == "Green")
    {
        ballColor = 2;
        m_rtfReceive.SetWindowText(_T("Green!"));
    }
    else if (color == _T("Blue"))
    {
        ballColor = 3;
    }
    else if (color == _T("Yellow"))
    {
        ballColor = 4;
    }
}


void CChatResearchDlg::OnCbnSelchangeComboTarget()
{
    // TODO: Add your control notification handler code here
    CString channel;
    m_cmbTarget.GetLBText(m_cmbTarget.GetCurSel(), channel);
    if (channel == _T("Channel_1"))
    {
        m_uChannel = 1;
    }
    else if (channel == _T("Channel_2"))
    {
        m_uChannel = 2;
    }
    else if (channel == _T("Channel_3"))
    {
        m_uChannel = 3;
    }
    else if (channel == _T("Channel_4"))
    {
        m_uChannel = 4;
    }
    else if (channel == _T("Channel_5"))
    {
        m_uChannel = 5;
    }
    else if (channel == _T("Channel_6"))
    {
        m_uChannel = 6;
    }
    else if (channel == _T("Channel_7"))
    {
        m_uChannel = 7;
    }
    else if (channel == _T("Channel_8"))
    {
        m_uChannel = 8;
    }
    else if (channel == _T("Channel_9"))
    {
        m_uChannel = 9;
    }
    else if (channel == _T("Chat Room"))
    {
        m_uChannel = 0;
    }
}


// Show portrait to make you look beauty!
void CChatResearchDlg::SetPortrait(UINT uBmpResource)
{
    HBITMAP hBitmap;
    hBitmap = (HBITMAP)LoadImage(AfxGetInstanceHandle(),
        MAKEINTRESOURCE(uBmpResource),
        IMAGE_BITMAP, 0, 0,
        LR_LOADMAP3DCOLORS);
    m_pctPortrait.ModifyStyle(0xF, SS_BITMAP | SS_CENTERIMAGE);
    m_pctPortrait.SetBitmap(hBitmap);
}


void CChatResearchDlg::OnBnClickedButtonSend()
{
    // TODO: Add your control notification handler code here
    if (m_bCurrentlyJoined)
    {
        CString str;
        m_rtfSendMsg.GetWindowText(str);
        m_pCFreeChat->SendChatMsg(str, m_uChannel);
        m_rtfSendMsg.SetWindowText(NULL);
        m_rtfSendMsg.GetFocus();
    }
}


void CChatResearchDlg::OnBnClickedButtonSubmit()
{
    // TODO: Add your control notification handler code here
}

void CChatResearchDlg::ReceiveCommMsg(const char *msg)
{
    m_rtfReceive.SetWindowText((CString)msg);
}
