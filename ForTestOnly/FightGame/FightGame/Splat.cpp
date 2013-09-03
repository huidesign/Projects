#include "Splat.h"
#include <iostream>
using std::cout;
using std::cerr;
using std::endl;

Splat::Splat()
{

}

Splat::~Splat()
{

}

void Splat::Init(RTI::RTIambassador* rtiAmb)
{
	ms_rtiAmb = rtiAmb;

	if (ms_rtiAmb)
	{
		try
		{
			ms_hSplat       = ms_rtiAmb->getInteractionClassHandle(ms_szSplat);
			ms_hEnsuingMess = ms_rtiAmb->getParameterHandle(ms_szEnsuingMess,
				ms_hSplat);
			ms_hTarget      = ms_rtiAmb->getParameterHandle(ms_szTarget,
				ms_hSplat);
		}
		catch (RTI::Exception& e)
		{
			cout << &e << endl;
			exit(1);
		}
	}
}

void Splat::PublishAndSubscribe()
{
	if (ms_rtiAmb)
	{
		try
		{
			ms_rtiAmb->publishInteractionClass(ms_hSplat);
		}
		catch (RTI::Exception& e)
		{
			cout << &e << endl;
			exit(1);
		}

		try
		{
			ms_rtiAmb->subscribeInteractionClass(ms_hSplat);
		}
		catch (RTI::Exception& e)
		{
			cout << &e << endl;
			exit(1);
		}
	}
}

void Splat::Fire(Student* pTarget, double ensuingMess)
{
	// Build the Parameter Set
	RTI::ParameterHandleValuePairSet *theParams = NULL;
	try
	{
		theParams = RTI::ParameterSetFactory::create(2);
		theParams->add(Splat::GetTargetRtiId(), 
			(char*)pTarget->GetName(),
			strlen(pTarget->GetName()) + 1);
		theParams->add(Splat::GetEnsuingMessRtiId(),
			(char*)&ensuingMess,
			sizeof(ensuingMess));
	}
	catch (RTI::Exception& e)
	{
		cout << &e << endl;
		exit(1);
	}

	// Send the interaction
	try
	{
		if (gRegulating)
		{
			ms_rtiAmb->queryLookahead(gLookahead);
			ms_rtiAmb->sendInteraction(Splat::GetSplatRtiId(),
				*theParams, gCurrentTime + gLookahead,
				"SPLAT!!!");
			ms_rtiAmb->tick(0.1, 1.0);
		}
		else
		{
			ms_rtiAmb->sendInteraction(Splat::GetSplatRtiId(),
				*theParams, "SPLAT!!!");
			ms_rtiAmb->tick(0.1, 1.0);
		}
		cout << "*** Shoot at " << pTarget->GetName() << endl;
	}
	catch (RTI::Exception& e)
	{
		cout << &e << endl;
		exit(1);
	}
	if (theParams)
	{
		theParams->empty();
		delete theParams;
	}

	return;
}