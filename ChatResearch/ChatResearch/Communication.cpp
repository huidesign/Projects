#include "stdafx.h"
#include "Communication.h"

//-----------------------------------------------------------------
// Static variable definition
//-----------------------------------------------------------------
RTI::RTIambassador*         CCommunication::ms_rtiAmb                = NULL;
RTI::InteractionClassHandle CCommunication::ms_hCommunication        = 0;
RTI::ParameterHandle        CCommunication::ms_hCommMsg              = 0;

char* const CCommunication::ms_szCommunication                       = "Communication";
char* const CCommunication::ms_szCommMsg                             = "Message";

CCommunication::CCommunication()
    : m_bSendCommInteractions(RTI::RTI_FALSE)
{
}

CCommunication::~CCommunication()
{
}

void CCommunication::InitCommunication(RTI::RTIambassador* rtiAmb)
{
    ms_rtiAmb = rtiAmb;
    if (ms_rtiAmb)
    {
        try
        {
            ms_hCommunication = ms_rtiAmb->getInteractionClassHandle(ms_szCommunication);
            ms_hCommMsg       = ms_rtiAmb->getParameterHandle(ms_szCommMsg, ms_hCommunication);
        }
        catch (RTI::Exception& e)
        {
            AfxMessageBox((CString)e._name);
        }
    }
}

void CCommunication::Publishing()
{
    if (ms_rtiAmb)
    {
        try
        {
            ms_rtiAmb->publishInteractionClass(ms_hCommunication);
        }
        catch (RTI::Exception& e)
        {
            AfxMessageBox((CString)e._name);
        }
    }
}

void CCommunication::Subscribing()
{
    if (ms_rtiAmb)
    {
        try
        {
            ms_rtiAmb->subscribeInteractionClass(ms_hCommunication);
        }
        catch (RTI::Exception& e)
        {
            AfxMessageBox((CString)e._name);
        }
    }
}

void CCommunication::Subscribing(RTI::Region *theRegion)
{
    if (ms_rtiAmb)
    {
        try
        {
            ms_rtiAmb->subscribeInteractionClassWithRegion(ms_hCommunication,
                *theRegion);
        }
        catch (RTI::Exception& e)
        {
            AfxMessageBox((CString)e._name);
        }
    }
}

void CCommunication::SendCommunication(RTI::Region *theRegion, const char* msg)
{
    if (GetSendCommInteractions())
    {
        try
        {
            RTI::ParameterHandleValuePairSet *params
                = RTI::ParameterSetFactory::create(1);
            params->add(ms_hCommMsg, msg, strlen(msg) + 1);

            ms_rtiAmb->sendInteractionWithRegion(ms_hCommunication,
                                                 *params,
                                                 "Communication",
                                                 *theRegion);
            //ms_rtiAmb->tick(0.01, 2.0);

            if (params)
            {
                params->empty();
                delete params;
            }
        }
        catch (RTI::Exception& e)
        {
            AfxMessageBox((CString)e._name);
        }
    }
}

void CCommunication::SendCommunication(const char* msg)
{
    if (GetSendCommInteractions())
    {
        try
        {
            RTI::ParameterHandleValuePairSet *params
                = RTI::ParameterSetFactory::create(1);
            params->add(ms_hCommMsg, msg, strlen(msg) + 1);

            ms_rtiAmb->sendInteraction(ms_hCommunication,
                *params,
                "Communication");
            //ms_rtiAmb->tick(0.01, 2.0);

            if (params)
            {
                params->empty();
                delete params;
            }
        }
        catch (RTI::Exception& e)
        {
            AfxMessageBox((CString)e._name);
        }
    }
}