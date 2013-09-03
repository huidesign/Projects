#pragma once
#ifndef _COUNTRY_H
#define _COUNTRY_H

#if defined(_MSC_VER)
#define RTI_USES_STD_FSTREAM
#endif	//defined(_MSC_VER)
#include <RTI.hh>
#if defined(RTI_USES_STD_FSTREAM)
using std::ostream;
#endif
#include <fedtime.hh>
#include "RWLock.h"
#define MAX_HELLOWORLD_FEDERATES	500

/************************************************************************/
/* Forward Declaration                                                  */
/************************************************************************/
class Country;

/************************************************************************/
/* Typedefs                                                             */
/************************************************************************/
typedef Country* CountryPtr;

/************************************************************************/
// CLASS:
//     Country
//
// PURPOSE:
//     The purpose of instances of class Country is to demonstrate
//     the proper usage of the RTI C++ API.  Instances can update
//     their state on the local machine (actually simulate the 
//     population) or from reflections provided by the RTI
//     (ghosting).                                                                     */
/************************************************************************/
class Country
{
public:
	Country();
	Country(const char* name, const char* populationStr);
	Country(const char* name, const double& population);
	Country(RTI::ObjectHandle id);
	virtual ~Country();

	/************************************************************************/
	/* Method action on the RTI                                             */
	/************************************************************************/
	static Country* Find(RTI::ObjectHandle objectId);
	static void init(RTI::RTIambassador* rtiAmb);
	void PublishAndSubscribe();
	void Register();
	void Update(RTIfedTime& newTime);
	void Update(const RTI::AttributeHandleValuePairSet& theAttributes);
	void deleteObjectInstance();

	/************************************************************************/
	/* Friend of Country                                                    */
	/************************************************************************/
	friend ostream& operator<< (ostream &s, Country &v);
	friend ostream& operator<< (ostream &s, Country *v);

	/************************************************************************/
	/* Accessor Methods                                                     */
	/************************************************************************/
	RTIfedTime GetLastTime()
	{
		return m_lastTime;
	}
	const char* GetName()
	{
		return m_name;
	}
	double& GetPopulation()
	{
		return m_population;
	}
	RTI::OrderingHandle& GetInstanceId()
	{
		return m_instanceId;
	}
	// Static Accessor Methods
	static RTI::ObjectClassHandle GetCountryRtiId()
	{
		return ms_countryTypeId;
	}
	static RTI::AttributeHandle GetNameRtiId()
	{
		return ms_nameTypeId;
	}
	static RTI::AttributeHandle GetPopulationRtiId()
	{
		return ms_popTypeId;
	}
	static RTI::InteractionClassHandle GetCommRtiId()
	{
		return ms_commTypeId;
	}
	static RTI::ParameterHandle GetMessageRtiId()
	{
		return ms_commMsgTypeId;
	}
	static RTIfedTime GetLookahead()
	{
		return ms_lookahead;
	}

	/************************************************************************/
	/* Mutator Methods                                                      */
	/************************************************************************/
	void SetLastTime(RTIfedTime& time)
	{
		m_lastTime = (RTI::FedTime&) time;
	}
	void SetName(const char*);
	void SetPopulation(const double&);
	void SetUpdateControl(RTI::Boolean status, 
		const RTI::AttributeHandleValuePairSet& attrs);
	// Static Mutator Methods
	static void SetInteractionControl(RTI::Boolean status,
		RTI::InteractionClassHandle theClass);
	static void SetRegistration(RTI::Boolean status)
	{
		ms_doRegistry = status;
	}
	static void SetLookahead(RTIfedTime& time)
	{
		ms_lookahead = (RTI::FedTime&) time;
	}

	/************************************************************************/
	/* Static Members                                                       */
	/************************************************************************/
	static const double     ms_growthRate;
	// Extent data members
	static CountryPtr       ms_countryExtent[MAX_HELLOWORLD_FEDERATES + 1];
	static unsigned int     ms_extentCardinality;	//现有Country数量

protected:
	RTI::AttributeHandleValuePairSet* CreateNVPSet();

private:
	char*                   m_name;
	double                  m_population;
	RTI::OrderingHandle     m_instanceId;
	RTIfedTime              m_lastTime;

public:
	static RTI::RTIambassador* ms_rtiAmb;
	static RWLock ms_lockCountry;

private:
	// Change flags for attributes values (dirty bits)
	RTI::Boolean hasNameChanged;
	RTI::Boolean hasPopulationChanged;
	// Update Control flags for instances
	RTI::Boolean m_sendNameAttrUpdates;
	RTI::Boolean m_sendPopulationAttrUpdates;

	/************************************************************************/
	/* Static Member Data                                                   */
	/************************************************************************/
	// Registeration Control flags for class
	static RTI::Boolean ms_doRegistry;
	static RTI::Boolean ms_sendCommInteractions;
	// Run-Time Type Identification data
	static RTI::ObjectClassHandle      ms_countryTypeId;
	static RTI::AttributeHandle        ms_nameTypeId;
	static RTI::AttributeHandle        ms_popTypeId;
	static RTI::InteractionClassHandle ms_commTypeId;
	static RTI::ParameterHandle        ms_commMsgTypeId;
	// Names for querying RTI values
	static char* const                 ms_countryTypeStr;
	static char* const                 ms_nameTypeStr;
	static char* const                 ms_popTypeStr;
	static char* const                 ms_commTypeStr;
	static char* const                 ms_commMsgTypeStr;
	// Lookahead Time Value
	static RTIfedTime                  ms_lookahead;
};

#endif