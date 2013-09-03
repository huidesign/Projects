
// ChatResearchDlg.h : 头文件
//

#pragma once
#include "resource.h"
class CFreeChat;
//class HwFederateAmbassador;

// CChatResearchDlg 对话框
class CChatResearchDlg : public CDialogEx
{
    // 构造
public:
    CChatResearchDlg(CWnd* pParent = NULL);	// 标准构造函数

    // 对话框数据
    enum { IDD = IDD_CHATRESEARCH_DIALOG };

protected:
    virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


    // 实现
protected:
    HICON m_hIcon;

    // 生成的消息映射函数
    virtual BOOL OnInitDialog();
    afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
    afx_msg void OnPaint();
    afx_msg HCURSOR OnQueryDragIcon();
    DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnBnClickedButtonJoin();
    afx_msg void OnBnClickedButtonExit();
    afx_msg void OnBnClickedButtonSend();
    afx_msg void OnCbnSelchangeComboPortrait();
    afx_msg void OnCbnSelchangeComboColor();
    afx_msg void OnCbnSelchangeComboTarget();
    afx_msg void OnBnClickedButtonSubmit();
    void ReceiveCommMsg(const char *msg);
protected:
    CFreeChat *m_pCFreeChat;
private:
    bool m_bCurrentlyJoined;
    unsigned long m_uChannel;
public:
    CComboBox m_cmbColor;
    CComboBox m_cmbPortrait;
    CComboBox m_cmbTarget;
    CEdit m_tbFederateName;
    CStatic m_pctPortrait;
    CRichEditCtrl m_rtfReceive;
    CRichEditCtrl m_rtfSendMsg;
private:
    // Show portrait to make you look beauty!
    void SetPortrait(UINT uBmpResource);
};
