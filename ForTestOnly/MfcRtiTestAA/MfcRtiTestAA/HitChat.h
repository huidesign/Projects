#pragma once
#include "HwFederateAmbassador.h"
class CHitChat :
	public HwFederateAmbassador
{
private:
	RTI::RTIambassador           m_rtiAmbassador;
	char m_federateName[256];
public:
	CHitChat(const char*);
	virtual ~CHitChat(void);
	int InitFederate(void);
	void ExitFederation(void);
};

