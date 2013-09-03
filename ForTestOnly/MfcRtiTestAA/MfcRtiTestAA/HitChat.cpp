#include "StdAfx.h"
#include <afxwin.h>	// for AfxMessageBox
#include <string>
#include "HitChat.h"


CHitChat::CHitChat(const char* szFedName)
{
	//strncpy(m_federateName, (const char*)(LPCTSTR)str, strlen(m_federateName));
	//std::string ss = std::string(CT2CA(str));
	strcpy(m_federateName, szFedName);
	//strcpy(m_federateName, "comcan");
}


CHitChat::~CHitChat(void)
{
	ExitFederation();
}


int CHitChat::InitFederate(void)
{
	int fedHd;
	//////////////////////////////////////////////////////////////////////////
	// Create Federation Execution
	//////////////////////////////////////////////////////////////////////////
	try
	{
		m_rtiAmbassador.createFederationExecution("ChatRoom", "Chat_2.fed");
	}
	catch (RTI::Exception &e)
	{
		AfxMessageBox((LPCTSTR)e._name);
	}

	//////////////////////////////////////////////////////////////////////////
	// Join Federation Execution
	//////////////////////////////////////////////////////////////////////////
	try
	{
		fedHd = m_rtiAmbassador.joinFederationExecution(m_federateName, 
			"ChatRoom", this);
		if (fedHd != 0)
		{
			CString str;
			str.Format(_T("JOIN FEDERATION SUCCESSFULLY, FEDERATE HANDLE IS %d"), fedHd);
			AfxMessageBox(str);
		}
	}
	catch (RTI::Exception &e)
	{
		AfxMessageBox((LPCTSTR)e._name);
	}

	return 0;
}


void CHitChat::ExitFederation(void)
{
	try
	{
		m_rtiAmbassador.resignFederationExecution(RTI::DELETE_OBJECTS_AND_RELEASE_ATTRIBUTES);
	}
	catch (RTI::Exception &e)
	{
		AfxMessageBox((LPCTSTR)e._name);
	}

	try
	{
		m_rtiAmbassador.destroyFederationExecution("ChatRoom");
		AfxMessageBox(_T("Destroy Federation Execution."));
	}
	catch (RTI::FederatesCurrentlyJoined)
	{
		AfxMessageBox(_T("Federate Currently Joined."));
	}
}
