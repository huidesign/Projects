
// HLA_HIT_CHATDlg.h : ͷ�ļ�
//

#pragma once
#include "ChatOperation.h"

// CHLA_HIT_CHATDlg �Ի���
class CHLA_HIT_CHATDlg : public CDialogEx
{
// ����
public:
	CHLA_HIT_CHATDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_HLA_HIT_CHAT_DIALOG };

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
	afx_msg void OnBnClickedCreatefederation();
	CString m_federateName;
private:
	HitChatFederate m_CHitChatFederate;
public:
	afx_msg void OnBnClickedJoinfederation();
};
