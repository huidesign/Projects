
// ChatResearch.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CChatResearchApp:
// �йش����ʵ�֣������ ChatResearch.cpp
//

class CChatResearchApp : public CWinApp
{
public:
    CChatResearchApp();

    // ��д
public:
    virtual BOOL InitInstance();

    // ʵ��

    DECLARE_MESSAGE_MAP()
};

extern CChatResearchApp theApp;