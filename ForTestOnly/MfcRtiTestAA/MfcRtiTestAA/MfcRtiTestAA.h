
// MfcRtiTestAA.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CMfcRtiTestAAApp:
// �йش����ʵ�֣������ MfcRtiTestAA.cpp
//

class CMfcRtiTestAAApp : public CWinApp
{
public:
	CMfcRtiTestAAApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CMfcRtiTestAAApp theApp;