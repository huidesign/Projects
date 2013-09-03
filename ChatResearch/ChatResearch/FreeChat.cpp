#include "stdafx.h"
#include "FreeChat.h"
#include "Fellow.h"
#include "Communication.h"
#include "HwFederateAmbassador.h"

// global const variable declaration
const unsigned int MAX_CHANNELS = 10;

CFreeChat::CFreeChat()
    : m_pFedAmb(NULL),
      m_hCommSpace(0),
      m_hCommChannel(0),
      m_pCFellow(NULL),
      m_pCComm(NULL),
      m_pRegion(NULL),
      m_szCommSpace("FellowCommSpace"),
      m_szCommChannel("Channel"),
      m_szFederationName("FreeChat")
{
}

CFreeChat::~CFreeChat()
{
    //if (m_pCComm)
    //{
    //    delete m_pCComm;
    //    m_pCComm = NULL;
    //}
    //if (m_pCFellow)
    //{
    //    delete m_pCFellow;
    //    m_pCFellow = NULL;
    //}
}

void CFreeChat::InitCommHandle()
{   // Used only after the function JoinFreeChat being called.
    try
    {
        m_hCommSpace   = m_rtiAmb.getRoutingSpaceHandle(m_szCommSpace);
        m_hCommChannel = m_rtiAmb.getDimensionHandle(m_szCommChannel, m_hCommSpace);
    }
    catch (RTI::Exception& e)
    {
        AfxMessageBox((CString)e._name);
    }
}

void CFreeChat::JoinFreeChat(HwFederateAmbassador *theFedAmb)
{
    m_pFedAmb = theFedAmb;
    RTI::FederateHandle fedHd = 0;
    //////////////////////////////////////////////////////////////////////////
    // Create Federation Execution
    //////////////////////////////////////////////////////////////////////////
    try
    {
        m_rtiAmb.createFederationExecution(m_szFederationName, "HitChat.fed");
    }
    catch (RTI::Exception &e)
    {
        AfxMessageBox((CString)e._name);
    }

    //////////////////////////////////////////////////////////////////////////
    // Join Federation Execution
    //////////////////////////////////////////////////////////////////////////
#ifdef WIN32
    sprintf(m_aFellowName, "Fellow_%ld", _getpid());
#endif
    try
    {
        fedHd = m_rtiAmb.joinFederationExecution(m_aFellowName, 
            m_szFederationName, m_pFedAmb);
        //if (fedHd != 0)
        //{
        //    CString str;
        //    str.Format(
        //        _T("JOIN FEDERATION SUCCESSFULLY, FEDERATE HANDLE IS %d"), 
        //        fedHd);
        //    AfxMessageBox(str);
        //}
    }
    catch (RTI::Exception &e)
    {
        AfxMessageBox((CString)e._name);
    }

    ////////////////////////////////////////////////////////////////////////////
    //// 开启联邦成员Class及Interaction是否存在异地定购恰当性建议
    ////////////////////////////////////////////////////////////////////////////
    //try
    //{
    //    m_rtiAmb.enableClassRelevanceAdvisorySwitch();
    //}
    //catch (RTI::Exception& e)
    //{
    //    AfxMessageBox((CString)e._name);
    //}

    //try
    //{
    //    m_rtiAmb.enableInteractionRelevanceAdvisorySwitch();
    //}
    //catch (RTI::Exception& e)
    //{
    //    AfxMessageBox((CString)e._name);
    //}

    InitCommHandle();
    DeclareRegion(0);
    //////////////////////////////////////////////////////////////////////////
    // 实例初始化
    //////////////////////////////////////////////////////////////////////////
    m_pCComm = new CCommunication();
    m_pCFellow = new CFellow("Sunny");
    m_pCFellow->InitFellow(&m_rtiAmb);
    m_pCComm->InitCommunication(&m_rtiAmb);

    //////////////////////////////////////////////////////////////////////////
    // Publish and Subscribe Class and Interaction
    //////////////////////////////////////////////////////////////////////////
    m_pCFellow->PublishAndSubscribe();
    m_pCComm->Publishing();
    m_pCComm->Subscribing(m_pRegion);
    m_pCComm->SetSendCommInteractions(RTI::RTI_TRUE);

    //////////////////////////////////////////////////////////////////////////
    // 注册对象实例
    //////////////////////////////////////////////////////////////////////////
    m_pCFellow->RegisterFellow();
    //pCComm->SendCommunication(m_vSubRegion.front(), 0);
}

void CFreeChat::SendTestMsg(CString str)
{
    char buf[256];
    CovertUnicode(str, buf);
    if (m_pCComm != NULL)
    {
        m_pCComm->SendCommunication(buf);
    }
}

void CFreeChat::SendChatMsg(CString str, RTI::ULong theChannel)
{
    static RTI::ULong preChannel = 0;
    if (m_pCComm != NULL)
    {
        char buf[256];
        CovertUnicode(str, buf);
        if (theChannel != preChannel)
        {
            ModifyRegion(m_pRegion, theChannel);
        }
        m_pCComm->SendCommunication(m_pRegion, buf);
        preChannel = theChannel;
    }
}

void CFreeChat::ExitFreeChat()
{
    try
    {
        m_rtiAmb.resignFederationExecution(
            RTI::DELETE_OBJECTS_AND_RELEASE_ATTRIBUTES);
    }
    catch (RTI::Exception &e)
    {
        AfxMessageBox((CString)e._name);
    }

    try
    {
        m_rtiAmb.destroyFederationExecution(m_szFederationName);
        AfxMessageBox(_T("Destroy Federation Execution."));
    }
    catch (RTI::FederatesCurrentlyJoined)
    {
        AfxMessageBox(_T("Federate Currently Joined."));
    }
}

void CFreeChat::DeclareRegion(RTI::ULong theChannel)
{
    m_pRegion = m_rtiAmb.createRegion(m_hCommSpace, 1);

    RTI::ULong channelRange = 
        (RTI::ULong)(double(theChannel) / double(MAX_CHANNELS) *
        (MAX_EXTENT - MIN_EXTENT) + MIN_EXTENT);
    m_pRegion->setRangeLowerBound(0, m_hCommChannel, channelRange);
    m_pRegion->setRangeUpperBound(0, m_hCommChannel, channelRange);

    m_rtiAmb.notifyAboutRegionModification(*m_pRegion);
}

void CFreeChat::ModifyRegion(RTI::Region *theRegion, RTI::ULong newChannel)
{
    if (theRegion != NULL)
    {
        RTI::ULong channelRange = 
            (RTI::ULong)(double(newChannel) / double(MAX_CHANNELS) *
            (MAX_EXTENT - MIN_EXTENT) + MIN_EXTENT);
        theRegion->setRangeLowerBound(0, m_hCommChannel, channelRange);
        theRegion->setRangeUpperBound(0, m_hCommChannel, channelRange);

        m_rtiAmb.notifyAboutRegionModification(*theRegion);
    }
}

void CFreeChat::CovertUnicode(CString str, char *buf)
{   // It's unsafe!
    wchar_t* p;
    p = str.GetBuffer(str.GetLength());
    str.ReleaseBuffer();
    WideCharToMultiByte(CP_ACP, WC_COMPOSITECHECK, p, -1, buf, 
        strlen(buf), NULL, NULL);
    //size_t len = wcslen(p) + 1;
    //size_t converted = 0;
    //wcstombs_s(&converted, buf, len, p, _TRUNCATE);
}

void CFreeChat::Chr2Wch(const char *buffer, wchar_t *wBuf)
{
    size_t len = strlen(buffer); 
    size_t wlen = MultiByteToWideChar(CP_ACP, 0, (const char*)buffer, int(len), NULL, 0); 
    wBuf = new wchar_t[wlen + 1]; 
    MultiByteToWideChar(CP_ACP, 0, (const char*)buffer, int(len), wBuf, int(wlen)); 
} 
