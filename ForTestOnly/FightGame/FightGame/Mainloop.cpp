#include <RTI.hh>
#include <fedtime.hh>

RTIfedTime gLookahead(1);
RTIfedTime gCurrentTime(0);

// Time Policy flag
RTI::Boolean gRegulating      = RTI::RTI_FALSE;
RTI::Boolean gConstrained     = RTI::RTI_FALSE;
RTI::Boolean gTimeRegulated   = RTI::RTI_FALSE;
RTI::Boolean gTimeConstrained = RTI::RTI_FALSE;

// Time Advance Grant flag
RTI::Boolean gTimeAdvGrant = RTI::RTI_FALSE;

// Time Advancing flag
RTI::Boolean gTimeAdvanceOutstanding = RTI::RTI_FALSE;
