
// HuiTestAA.h : main header file for the HuiTestAA application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CHuiTestAAApp:
// See HuiTestAA.cpp for the implementation of this class
//

class CHuiTestAAApp : public CWinAppEx
{
public:
	CHuiTestAAApp();


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	UINT  m_nAppLook;
	BOOL  m_bHiColorIcons;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CHuiTestAAApp theApp;
