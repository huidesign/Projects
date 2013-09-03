#include <Windows.h>
#include <iostream>
using std::cin;
using std::cout;
using std::cerr;
using std::endl;
#include "HuiFederateAmbassador.h"

#define LIMIT_TO_CAL 300

class ChatCCFederate : public HuiFederateAmbassador
{
private:
	RTI::RTIambassador           m_rtiAmbassador;
	RTI::InteractionClassHandle  m_messageId;
	RTI::ParameterHandle         m_parameterIdText;
	RTI::ParameterHandle         m_parameterIdFederateName;

	int  m_bFlag;
	char m_federateName[256];
#ifdef WIN32
	HANDLE m_Handle;	// Handle of the simulation thread
#endif

public:
	ChatCCFederate(const char* federateName)
	{
		strcpy(m_federateName, federateName);
	}

	~ChatCCFederate()
	{
		try
		{
			m_rtiAmbassador.resignFederationExecution(RTI::DELETE_OBJECTS_AND_RELEASE_ATTRIBUTES);
		}
		catch (RTI::Exception &e)
		{
			cout << "Exception:" << e._name << endl;
		}

		try
		{
			m_rtiAmbassador.destroyFederationExecution("ChatRoom");
			cout << "Destroy Federation Execution." << endl;
		}
		catch (RTI::FederatesCurrentlyJoined)
		{
			cerr << "Federate Currently Joined." << endl;
		}
	}

	int init()
	{
		int fedHd;
		cout << "FED_HW: JOINING FEDERATION EXCUTION: " << "Chat2" << endl;

		//////////////////////////////////////////////////////////////////////////
		// Create Federation Execution
		//////////////////////////////////////////////////////////////////////////
		try
		{
			m_rtiAmbassador.createFederationExecution("ChatRoom", "Chat_2.fed");
		}
		catch (RTI::Exception &e)
		{
			cout << "Exception:" << e._name << endl;
		}

		//////////////////////////////////////////////////////////////////////////
		// Join Federation Execution
		//////////////////////////////////////////////////////////////////////////
		try
		{
			fedHd = m_rtiAmbassador.joinFederationExecution(m_federateName, 
				"ChatRoom", this);
		}
		catch (RTI::Exception &e)
		{
			cout << "Exception:" << e._name << endl;
		}

		if (fedHd != 0)
		{
			cout << "JOIN FEDERATION SUCCESSFULLY, FEDERATE HANDLE IS ";
			cout << fedHd << endl;

			//////////////////////////////////////////////////////////////////////////
			// Get Interaction Class Handle
			//////////////////////////////////////////////////////////////////////////
			try
			{
				m_messageId = m_rtiAmbassador.getInteractionClassHandle("Communication");
			}
			catch (RTI::Exception &e)
			{
				cout << "Exception:" << e._name << endl;
			}

			//////////////////////////////////////////////////////////////////////////
			// Get the Parameter Handle of "Message"
			//////////////////////////////////////////////////////////////////////////
			try
			{
				m_parameterIdText = m_rtiAmbassador.getParameterHandle("Message",
					m_messageId);
			}
			catch (RTI::Exception &e)
			{
				cout << "Exception:" << e._name << endl;
			}

			//////////////////////////////////////////////////////////////////////////
			// Get the Parameter Handle of "FederateName"
			//////////////////////////////////////////////////////////////////////////
			try
			{
				m_parameterIdFederateName = m_rtiAmbassador.getParameterHandle("FederateName",
					m_messageId);
			}
			catch (RTI::Exception &e)
			{
				cout << "Exception:" << e._name << endl;
			}

			cout << m_messageId << " : " << m_parameterIdText << " : ";
			cout << m_parameterIdFederateName << endl;

			//////////////////////////////////////////////////////////////////////////
			// Subscribe Interaction Class
			//////////////////////////////////////////////////////////////////////////
			try
			{
				m_rtiAmbassador.subscribeInteractionClass(m_messageId);
			}
			catch (RTI::Exception &e)
			{
				cout << "Exception:" << e._name << endl;
			}

			//////////////////////////////////////////////////////////////////////////
			// Publish Interaction Class
			//////////////////////////////////////////////////////////////////////////
			try
			{
				m_rtiAmbassador.publishInteractionClass(m_messageId);
			}
			catch (RTI::Exception &e)
			{
				cout << "Exception:" << e._name << endl;
			}
			
			return 1;
		}
		else
			return -1;	// Failed to Join
	}

	//////////////////////////////////////////////////////////////////////////
	// Start Simulation
	//////////////////////////////////////////////////////////////////////////
	void start()
	{
		m_bFlag = 1;
		unsigned long ulThreadId;

#ifdef WIN32
		m_Handle = CreateThread(
								NULL,
								0,
								(LPTHREAD_START_ROUTINE)run,
								(LPARAM*)this,
								0,
								&ulThreadId);
#endif // WIN32
	}

	//////////////////////////////////////////////////////////////////////////
	// Terminate Simulation
	//////////////////////////////////////////////////////////////////////////
	void end()
	{
		m_bFlag = 0;
#ifdef WIN32
		WaitForSingleObject(m_Handle, INFINITE);
		CloseHandle(m_Handle);
#endif // WIN32
	}

	//////////////////////////////////////////////////////////////////////////
	// Receive Interaction
	//////////////////////////////////////////////////////////////////////////
	void receiveInteraction (
		RTI::InteractionClassHandle              theInteraction, 
		const RTI::ParameterHandleValuePairSet&  theParameters, 
		const char                               *theTag)
		throw (
		RTI::InteractionClassNotKnown,
		RTI::InteractionParameterNotKnown,
		RTI::FederateInternalError)
	{
		try
		{
			if (theInteraction == m_messageId)
			{
				// message
				char *message = "";

				// Federate Name Who Send This Interaction
				char *federateName = "";
				unsigned long tmpLength = 0;

				// Get Parameters In Order
				message = theParameters.getValuePointer(0, tmpLength);       // 0 is message
				federateName = theParameters.getValuePointer(1, tmpLength);  // 1 is federate
				federateName[tmpLength] = '\0';
				cout << "[" << federateName << "]: ";
				cout << message << endl;
			}
		}
		catch (RTI::ArrayIndexOutOfBounds &e)
		{
			cout << &e << endl;
		}
	}

	//////////////////////////////////////////////////////////////////////////
	// Send Interaction
	//////////////////////////////////////////////////////////////////////////
	void sendCommInteraction(const char* strMessage)
	{
		RTI::ParameterHandleValuePairSet* parameters = RTI::ParameterSetFactory::create(2);

		// Add Parameters In Order
		// 0: message	1: federateName
		const char *newMessage = strMessage;
		parameters->add(m_parameterIdText, newMessage, strlen(newMessage) + 1);
		parameters->add(m_parameterIdFederateName, 
			m_federateName, strlen(m_federateName) + 1);

		try
		{
			m_rtiAmbassador.sendInteraction(m_messageId, *parameters, 0);
		}
		catch (RTI::Exception &e)
		{
			cout << "Exception:" << e._name << endl;
		}

		delete parameters;
	}

#ifdef WIN32
	friend void run(LPARAM lParam)
	{
		ChatCCFederate *pChat = (ChatCCFederate*)lParam;
		while (true)
		{
			pChat->m_rtiAmbassador.tick();
			if (!pChat->m_bFlag)
			{
				break;
			}
			Sleep(1);
		}
	}
#endif // WIN32
};

//////////////////////////////////////////////////////////////////////////
// Main Function Here
//////////////////////////////////////////////////////////////////////////
int main(int argc, char* argv[])
{
	if (argc != 2 || !argv[1])
	{
		cout << "Usage: <chat2> <federateName>" << endl;
		return -1;
	}
	ChatCCFederate *pChatFederate = new ChatCCFederate(argv[1]);

	if (pChatFederate->init() <= 0)
	{
		cout << "JOIN FEDERATION FAIL..." << endl;
		cout << "EXITING..." << endl;
		Sleep(1000);
		delete pChatFederate;
		return -2;
	}

	pChatFederate->start();

	cout << "Type Messages you want to send, Type . <Enter> to exit" << endl;

	const int nMsgLength = 256;
	char strMessage[nMsgLength];
	while (true)
	{
		cout << "> ";
		cout.flush();
		cin.getline(strMessage, nMsgLength);

		if (!strcmp(strMessage, "."))
		{
			break;
		}

		// Send Interaction
		pChatFederate->sendCommInteraction(strMessage);

		Sleep(10);
	}

	pChatFederate->end();
	delete pChatFederate;
	return 1;
}