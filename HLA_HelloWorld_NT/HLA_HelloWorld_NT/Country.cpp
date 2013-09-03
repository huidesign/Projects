#include "Country.h"

#ifndef _MSC_VER
#include <stdlib.h>
#include <iostream.h>
#include <string.h>
#include <netinet/in.h>
#else
#include <winsock2.h>
#include <iostream>
using std::cout;
using std::cerr;
using std::endl;
#endif

// For Ntohl and Cvt_ftof
#if defined(_X86_) && !defined(WIN32)
#include <arpa/inet.h>
#endif

#if defined(__alpha)
#include <arpa/inet.h>
#include <cvt.h>
#endif	//__alpha

/************************************************************************/
/* Static Variable Definition                                           */
/************************************************************************/
RTI::RTIambassador*          Country::ms_rtiAmb        = NULL;
RTI::ObjectClassHandle       Country::ms_countryTypeId = 0;
RTI::AttributeHandle         Country::ms_nameTypeId    = 0;
RTI::AttributeHandle         Country::ms_popTypeId     = 0;
RTI::InteractionClassHandle  Country::ms_commTypeId    = 0;
RTI::ParameterHandle         Country::ms_commMsgTypeId = 0;

RTIfedTime Country::ms_lookahead(1.0);

char* const  Country::ms_commTypeStr    = "Country";
char* const  Country::ms_nameTypeStr    = "Name";
char* const  Country::ms_popTypeStr     = "Population";

char* const  Country::ms_commTypeStr    = "Communication";
char* const  Country::ms_commMsgTypeStr = "Message";

const double Country::ms_growthRate(0.001);

CountryPtr Country::ms_countryExtent[MAX_HELLOWORLD_FEDERATES + 1] = {NULL};

UINT Country::ms_extentCardinality = 0;

// Non-Class Constant
const double countryDefaultPopulation = 100;
//-----------------------------------------------------------------
//
// METHOD:
//     Country::Country( const char* name, const char* populationStr )
//
// PURPOSE:
//     Constructor.  The constructor initializes the member data
//     with the values passed in and adds this Country instance to
//     the Country extenet (collection of all elements of a type).
//
// RETURN VALUES:
//     None. 
//-----------------------------------------------------------------
Country::Country(const char *name, const char *populationStr)
	:m_name(NULL),
	m_lastTime(*(RTI::FedTimeFactory::makeZero())),
	m_TimePlusLookahead