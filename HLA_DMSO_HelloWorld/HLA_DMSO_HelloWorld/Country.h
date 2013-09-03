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

#define MAX_HELLOWORLD_FEDERATES 21

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
	static Country*  Find(RTI::ObjectHandle objectId);
	static void      Init(RTI::RTIambassador* rtiAmb);
	void             PublishAndSubscribe();
	void             Register();
	void             Update(RTI::FedTime& newTime);
	void             Update(const RTI::AttributeHandleValuePairSet& theAttributes);
	static void      Update(RTI::InteractionClassHandle theInteraction,
		                    const RTI::ParameterHandleValuePairSet& theParameters);

	/************************************************************************/
	/* Friend of Country                                                    */
	/************************************************************************/
	friend ostream& operator<< (ostream &s, Country &v);
	friend ostream& operator<< (ostream &s, Country *v);

	/************************************************************************/
	/* Accessor Methods                                                     */
	/************************************************************************/
	RTI::FedTime const& GetLastTime() {
		return m_lastTime;
	}

	RTI::FedTime const& GetLastTimePlusLookahead() {
		m_timePlusLookahead = m_lastTime;
		m_timePlusLookahead += ms_lookahead;
		return m_timePlusLookahead;
	}

	const char* GetName() {
		return m_name;
	}

	double& GetPopulation() {
		return m_population;
	}

	RTI::ObjectHandle& GetInstanceId() {
		return m_instanceId;
	}

	// Static Accessor Methods
	static RTI::ObjectClassHandle GetCountryRtiId() {
		return ms_countryTypeId;
	}

	static RTI::AttributeHandle GetNameRtiId() {
		return ms_nameTypeId;
	}

	static RTI::AttributeHandle GetPopulationRtiId() {
		return ms_popTypeId;
	}

	static RTI::InteractionClassHandle GetCommRtiId() {
		return ms_commTypeId;
	}

	static RTI::ParameterHandle GetMessageRtiId() {
		return ms_commMsgTypeId;
	}

	static RTI::FedTime const& GetLookahead() {
		return ms_lookahead;
	}

	/************************************************************************/
	/* Mutator Methods                                                      */
	/************************************************************************/
	void SetLastTime( const RTI::FedTime &time ) {
		m_lastTime = time;
	}

	void SetName( const char* );
	void SetPopulation( const double& );

	static void SetLookahead( RTI::FedTime& time ) {
		ms_lookahead = time;
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
	char*                                m_name;
	double                               m_population;
	RTI::OrderingHandle                  m_instanceId;
	RTI::FedTime&                        m_lastTime;

	RTI::FedTime&                        m_timePlusLookahead;
	static RTI::RTIambassador*           ms_rtiAmb;

	// Change flags for attributes values (dirty bits)
	RTI::Boolean                         hasNameChanged;
	RTI::Boolean                         hasPopulationChanged;

	/************************************************************************/
	/* Static Member Data                                                   */
	/************************************************************************/

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