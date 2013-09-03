#include <Windows.h>
#include "HwFederateAmbassador.h"

class HitChatFederate : public HwFederateAmbassador
{
private:
	RTI::RTIambassador            m_rtiAmbassador;
	RTI::ParameterHandle          m_parameterIdText;
	RTI::ParameterHandle          m_parameterIdFederateName;
	RTI::ParameterHandle          m_parameterIdFederateHead;

	RTI::ObjectClassHandle        ms_ballTypeId;
	RTI::AttributeHandle          ms_ballColor;
	RTI::AttributeHandle          ms_ballName;
	RTI::ObjectHandle             ms_instanceId;
	RTI::InteractionClassHandle   ms_commTypeId;

	char m_federateName[256];
	int  m_fedHd;
public:
	HitChatFederate(const char*);
	~HitChatFederate();

	void createMyFederationExcution();
	void joinMyFederationExcution(const char*);
	void resignMyFederationExcution();
	void destroyMyFederationExecution();

	//void sendResignMsg(char *fedName);
};