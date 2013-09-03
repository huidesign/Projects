
// ChatResearchDlg.h : ͷ�ļ�
//

#pragma once
#include "resource.h"
class CFreeChat;
//class HwFederateAmbassador;

// CChatResearchDlg �Ի���
class CChatResearchDlg : public CDialogEx
{
    // ����
public:
    CChatResearchDlg(CWnd* pParent = NULL);	// ��׼���캯��

    // �Ի�������
    enum { IDD = IDD_CHATRESEARCH_DIALOG };

protected:
    virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


    // ʵ��
protected:
    HICON m_hIcon;

    // ���ɵ���Ϣӳ�亯��
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
