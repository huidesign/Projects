#pragma once
#ifndef _CHAT_RESEARCH_CFREE_CHAT_H
#define _CHAT_RESEARCH_CFREE_CHAT_H

#if defined(_MSC_VER)
#define RTI_USES_STD_FSTREAM
#endif // defined(_MSC_VER)
#include <RTI.hh>

class CFellow;
class CCommunication;
class HwFederateAmbassador;

class CFreeChat
{
public:
    CFreeChat();
    virtual ~CFreeChat();
    void JoinFreeChat(HwFederateAmbassador *theFedAmb);
    void ExitFreeChat();
    void InitCommHandle();
    void SendTestMsg(CString str);
    void SendChatMsg(CString str, RTI::ULong theChannel = 0);
    void DeclareRegion(RTI::ULong theChannel);
    void ModifyRegion(RTI::Region *theRegion, RTI::ULong newChannel);
    void CovertUnicode(CString str, char *buf);
    void Chr2Wch(const char *buffer, wchar_t *wBuf);
private:
    RTI::RTIambassador                  m_rtiAmb;
    HwFederateAmbassador               *m_pFedAmb;

    RTI::SpaceHandle                    m_hCommSpace;
    RTI::DimensionHandle                m_hCommChannel;

    CFellow                             *m_pCFellow;
    CCommunication                      *m_pCComm;

    RTI::Region*                        m_pRegion;

    char* const                         m_szCommSpace;
    char* const                         m_szCommChannel;
    char* const                         m_szFederationName;

    char                                m_aFellowName[256];
};


#endif _CHAT_RESEARCH_CFREE_CHAT_H