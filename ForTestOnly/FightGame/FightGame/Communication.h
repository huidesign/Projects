#pragma once
#ifndef _FIGHTGAME_COMMUNICATION_H
#define _FIGHTGAME_COMMUNICATION_H
#include <RTI.hh>

class Communication
{
public:
	Communication();
	virtual ~Communication();

	//////////////////////////////////////////////////////////////////////////
	// Methods acting on the RTI
	//////////////////////////////////////////////////////////////////////////
	static void Init(RTI::RTIambassador* rtiAmb);
	void Publishing();
	void Subcribing();
	void Subcribing(RTI::Region* theRegion);
	void SendCommunication(Communication* myCommunication);
	static void SetSendCommInteractions(RTI::Boolean status)
	{
		ms_bSendCommInteractions = status;
	}
	static RTI::InteractionClassHandle GetCommRtiId()
	{
		return ms_hCommunication;
	}
	static RTI::ParameterHandle GetMessageRtiId()
	{
		return ms_hCommMessage;
	}
	static RTI::Boolean GetSendCommInteractions()
	{
		return ms_bSendCommInteractions;
	}

private:
	static RTI::RTIambassador          *ms_rtiAmb;
	static RTI::Boolean                ms_bSendCommInteractions;
	static RTI::InteractionClassHandle ms_hCommunication;
	static RTI::ParameterHandle        ms_hCommMessage;
	static char* const                 ms_szCommunication;
	static char* const                 ms_szCommMessage;
};
#endif