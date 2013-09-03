#pragma once
#ifndef _CHAT_RESEARCH_CCommunication_H
#define _CHAT_RESEARCH_CCommunication_H

#if defined(_MSC_VER)
#define RTI_USES_STD_FSTREAM
#endif // defined(_MSC_VER)
#include <RTI.hh>
class CCommunication;

class CCommunication
{
public:
    CCommunication();
    virtual ~CCommunication();
    //-------------------------
    // Methods acting on the RTI
    //--------------------------
    static void                         InitCommunication(RTI::RTIambassador* rtiAmb);
    void                                Publishing();
    void                                Subscribing();
    void                                Subscribing(RTI::Region *theRegion);
    void                                SendCommunication(const char* msg);
    void                                SendCommunication(RTI::Region *theRegion, const char* msg);
    void                                SetSendCommInteractions(RTI::Boolean status)
    {
        m_bSendCommInteractions = status;
    };
    static RTI::InteractionClassHandle  GetCommRtiId()
    {
        return ms_hCommunication;
    };
    static RTI::ParameterHandle         GetMessageRtiId()
    {
        return ms_hCommMsg;
    };
    RTI::Boolean                 GetSendCommInteractions()
    {
        return m_bSendCommInteractions;
    };
private:
    RTI::Boolean                        m_bSendCommInteractions;

    static RTI::RTIambassador           *ms_rtiAmb;
    static RTI::InteractionClassHandle  ms_hCommunication;
    static RTI::ParameterHandle         ms_hCommMsg;

    static char* const                  ms_szCommunication;
    static char* const                  ms_szCommMsg;
};

#endif // define _CHAT_RESEARCH_CCommunication