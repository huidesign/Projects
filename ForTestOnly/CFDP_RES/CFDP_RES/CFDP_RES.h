
// CFDP_RES.h : main header file for the CFDP_RES application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CCFDP_RESApp:
// See CFDP_RES.cpp for the implementation of this class
//

class CCFDP_RESApp : public CWinAppEx
{
public:
	CCFDP_RESApp();


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

extern CCFDP_RESApp theApp;
