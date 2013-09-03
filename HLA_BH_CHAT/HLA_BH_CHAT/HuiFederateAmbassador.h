#pragma once
#ifndef _HUI_FEDERATE_AMBASSADOR_H
#define _HUI_FEDERATE_AMBASSADOR_H

#if defined(_MSC_VER)
#define RTI_USES_STD_FSTREAM
#endif

#include <RTI.hh>
#include <NullFederateAmbassador.hh>

class HuiFederateAmbassador : public NullFederateAmbassador
{
public:

	HuiFederateAmbassador();
	virtual ~HuiFederateAmbassador() 
		throw (RTI::FederateInternalError);
};

#endif