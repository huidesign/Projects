
// HLA_HIT_CHAT.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CHLA_HIT_CHATApp:
// �йش����ʵ�֣������ HLA_HIT_CHAT.cpp
//

class CHLA_HIT_CHATApp : public CWinApp
{
public:
	CHLA_HIT_CHATApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CHLA_HIT_CHATApp theApp;