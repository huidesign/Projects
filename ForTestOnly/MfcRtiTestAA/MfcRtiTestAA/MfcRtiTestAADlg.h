
// MfcRtiTestAADlg.h : ͷ�ļ�
//

#pragma once
#include "HitChat.h"


// CMfcRtiTestAADlg �Ի���
class CMfcRtiTestAADlg : public CDialogEx
{
// ����
public:
	CMfcRtiTestAADlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_MFCRTITESTAA_DIALOG };

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
//	CString m_federateName;
	CHitChat* m_pCHitChat;
	afx_msg void OnBnClickedJoinfederation();
	afx_msg void OnBnClickedExitfederation();
	CEdit m_edtFederateName;
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
};
