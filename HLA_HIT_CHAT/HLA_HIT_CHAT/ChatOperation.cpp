#include "stdafx.h"
#include <afxwin.h>
#include "ChatOperation.h"

HitChatFederate::HitChatFederate(const char* federateName)
{
	strcpy(m_federateName, federateName);
}

HitChatFederate::~HitChatFederate()
{

}

void HitChatFederate::createMyFederationExcution()
{
	try
	{
		m_rtiAmbassador.createFederationExecution("Chat Room", "Chat_2.fed");
	}
	catch (RTI::Exception &e)
	{
		AfxMessageBox((LPCTSTR)e._name);
	}
}

void HitChatFederate::joinMyFederationExcution(const char* federateName)
{
	try
	{
		m_fedHd = m_rtiAmbassador.joinFederationExecution(m_federateName,
			"ChatRoom", this);
		if (m_fedHd != 0)
		{
			AfxMessageBox(_T("JOIN FEDERATION SUCCESSFULLY!"));		
		}
	}
	catch (RTI::Exception &e)
	{
		AfxMessageBox((LPCTSTR)e._name);
	}
}