#pragma once
#ifndef _FIGHTGAME_SPLAT_H
#define _FIGHTGAME_SPLAT_H
#include <RTI.hh>
#include "Student.h"

class Splat
{
public:
	Splat();
	virtual ~Splat();
	//////////////////////////////////////////////////////////////////////////
	// Methods acting on the RTI
	//////////////////////////////////////////////////////////////////////////
	static void Init(RTI::RTIambassador* rtiAmb);
	void PublishAndSubscribe();
	void Fire(Student* pTarget, double ensuingMess);
	static void SetSendSplat(RTI::Boolean status)
	{
		ms_bSendSplat = status;
	}
	static RTI::InteractionClassHandle GetSplatRtiId()
	{
		return ms_hSplat;
	}
	static RTI::ParameterHandle GetEnsuingMessRtiId()
	{
		return ms_hEnsuingMess;
	}
	static RTI::ParameterHandle GetTargetRtiId()
	{
		return ms_hTarget;
	}
	static RTI::Boolean GetSendSplat()
	{
		return ms_bSendSplat;
	}

private:
	static RTI::RTIambassador          *ms_rtiAmb;
	static RTI::Boolean                ms_bSendSplat;
	static RTI::InteractionClassHandle ms_hSplat;
	static RTI::ParameterHandle        ms_hEnsuingMess;
	static RTI::ParameterHandle        ms_hTarget;
	static char* const                 ms_szSplat;
	static char* const                 ms_szEnsuingMess;
	static char* const                 ms_szTarget;
};
#endif