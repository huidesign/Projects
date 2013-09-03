
// HLA_HIT_CHATDlg.h : 头文件
//

#pragma once
#include "ChatOperation.h"

// CHLA_HIT_CHATDlg 对话框
class CHLA_HIT_CHATDlg : public CDialogEx
{
// 构造
public:
	CHLA_HIT_CHATDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_HLA_HIT_CHAT_DIALOG };

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
	afx_msg void OnBnClickedCreatefederation();
	CString m_federateName;
private:
	HitChatFederate m_CHitChatFederate;
public:
	afx_msg void OnBnClickedJoinfederation();
};
