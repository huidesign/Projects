#include "stdafx.h"
#include "Fellow.h"
//#include <afxwin.h>	// for AfxMessageBox

//-----------------------------------------------------------------
// Static variable definition
//-----------------------------------------------------------------
RTI::RTIambassador*         CFellow::ms_rtiAmb             = NULL;
RTI::ObjectClassHandle      CFellow::ms_hFellow            = 0;
RTI::AttributeHandle        CFellow::ms_hFellowName        = 0;
RTI::AttributeHandle        CFellow::ms_hFellowColor       = 0;
RTI::ParameterHandle        CFellow::ms_hFellowPortrait    = 0;

char* const CFellow::ms_szFellow               = "Fellow";
char* const CFellow::ms_szFellowColor          = "Color";
char* const CFellow::ms_szFellowName           = "Name";
char* const CFellow::ms_szFellowPortrait       = "Portrait";

// As BH-RTI does not support startRegistrationForObject callback function,
// so, set ms_bDoRegistry flag to true.
RTI::Boolean CFellow::ms_bDoRegistry           = RTI::RTI_TRUE;

unsigned int CFellow::ms_uExtentCardinality    = 0;
CFellowPtr CFellow::ms_aFellowExtent[]         = {};

CFellow::CFellow(const char* str)
    : fellowNameInit('\0'),
      msgInit('\0'),
      m_uFellowColor(0),
      m_uFellowPortrait(0),
      m_bNameChanged(RTI::RTI_FALSE),
      m_bColorChanged(RTI::RTI_FALSE),
      m_bPortraitChanged(RTI::RTI_FALSE)
{
    ms_aFellowExtent[ms_uExtentCardinality++] = this;
    SetFellowName(str);
}

CFellow::CFellow(RTI::ObjectHandle id)
    : fellowNameInit('\0'),
      msgInit('\0'),
      m_uFellowColor(0),
      m_uFellowPortrait(0),
      m_hInstance(id),
      m_bNameChanged(RTI::RTI_FALSE),
      m_bColorChanged(RTI::RTI_FALSE),
      m_bPortraitChanged(RTI::RTI_FALSE)
{
    ms_aFellowExtent[ms_uExtentCardinality++] = this;
    //this->SetFellowName(NULL);
}

CFellow::~CFellow(void)
{
    CFellowPtr pCFellow = NULL;
    unsigned int ndx = 0;

    //////////////////////////////////////////////////////////////////////////
    // Find the position in the extent for this instance.  The
    // zero'th position always hold the local instance.
    //////////////////////////////////////////////////////////////////////////
    for (ndx = 0; ndx < ms_uExtentCardinality; ndx++)
    {
        pCFellow = ms_aFellowExtent[ndx];

        if (pCFellow && (pCFellow->GetInstanceId() == this->GetInstanceId()))
        {
            break;
        }
    }

    if (pCFellow)
    {
        // First thing to do is move the rest of the CFellow objects
        // one position up in the collection and then reduce the 
        // cardinality by one
        for (unsigned int i = ndx; (i < ms_uExtentCardinality)
            && (ms_aFellowExtent[i] != NULL); i++)
        {   // This also set the last member to NULL
            ms_aFellowExtent[i] = ms_aFellowExtent[i+1];
        }

        ms_uExtentCardinality = ms_uExtentCardinality - 1;

        // If the instance was found in the 0th position then this is the
        // local CFellow instance so we should delete it from the federation
        // execution.
        if (ms_rtiAmb && ndx == 0)
        {
            // this call returns an event retraction handle but we don't
            // support event retraction so no need to store it.
            (void)ms_rtiAmb->deleteObjectInstance(this->GetInstanceId(),
                "Student Quit");
        }
        else
        {
            // Otherwise, this is a remote object that removeObject was called 
            // on
        }
    }
}

void CFellow::InitFellow(RTI::RTIambassador *rtiAmb)
{
    ms_rtiAmb = rtiAmb;
    if (ms_rtiAmb)
    {
        try
        {
            ms_hFellow          = ms_rtiAmb->getObjectClassHandle(ms_szFellow);
            ms_hFellowName      = ms_rtiAmb->getAttributeHandle(ms_szFellowName, ms_hFellow);
            ms_hFellowColor     = ms_rtiAmb->getAttributeHandle(ms_szFellowColor, ms_hFellow);
            ms_hFellowPortrait  = ms_rtiAmb->getAttributeHandle(ms_szFellowPortrait, ms_hFellow);
        }
        catch (RTI::Exception& e)
        {
            AfxMessageBox((CString)e._name);
        }
    }
}

void CFellow::PublishAndSubscribe()
{
    if (ms_rtiAmb)
    {
        RTI::AttributeHandleSet *fellowAttrs;
        try
        {
            fellowAttrs = RTI::AttributeHandleSetFactory::create(3);
            fellowAttrs->add(ms_hFellowName);
            fellowAttrs->add(ms_hFellowColor);
            fellowAttrs->add(ms_hFellowPortrait);
        }
        catch (RTI::Exception& e)
        {
            AfxMessageBox((CString)e._name);
        }

        try
        {
            ms_rtiAmb->subscribeObjectClassAttributes(ms_hFellow, *fellowAttrs);
            ms_rtiAmb->publishObjectClass(ms_hFellow, *fellowAttrs);
        }
        catch (RTI::Exception& e)
        {
            AfxMessageBox((CString)e._name);
        }

        fellowAttrs->empty();
        delete fellowAttrs;
    }
}

void CFellow::RegisterFellow()
{
    if (ms_rtiAmb)
    {
        while (!ms_bDoRegistry)
        {
            ms_rtiAmb->tick(0.01, 2.0);
        }
        try
        {
            m_hInstance = ms_rtiAmb->registerObjectInstance(this->GetFellowRtiId(),
                this->GetFellowName());
            //ms_rtiAmb->tick(0.01, 2.0);
        }
        catch (RTI::Exception& e)
        {
            AfxMessageBox((CString)e._name);
        }
    }
}

void CFellow::UpdateFellow(CFellow *pCFellow)
{
    char                                fellowName[256] = {'\0'};
    RTI::ULong                          fellowColor     = 0;
    RTI::ULong                          fellowPortrait  = 0;
    RTI::AttributeHandleValuePairSet    *theAttrs = NULL;

    try
    {
        theAttrs = RTI::AttributeSetFactory::create(3);
        if (pCFellow->GetFellowNameUpdate())
        {
            strcpy(fellowName, pCFellow->GetFellowName());
            theAttrs->add(pCFellow->GetFellowNameRtiId(), (char*)fellowName,
                sizeof(fellowName));
            pCFellow->SetFellowNameUpdate(RTI::RTI_FALSE);
        }
        if (pCFellow->GetFellowColorUpdate())
        {
            fellowColor = pCFellow->GetFellowColor();
            theAttrs->add(pCFellow->GetFellowColorRtiId(), (char*)&fellowColor,
                sizeof(fellowColor));
            pCFellow->SetFellowColorUpdate(RTI::RTI_FALSE);
        }
        if (pCFellow->GetFellowPortraitUpdate())
        {
            fellowPortrait = pCFellow->GetFellowPortrait();
            theAttrs->add(pCFellow->GetFellowPortraitRtiId(), (char*)&fellowPortrait,
                sizeof(fellowPortrait));
            pCFellow->SetFellowPortraitUpdate(RTI::RTI_FALSE);
        }
        if (theAttrs->size())
        {
            ms_rtiAmb->updateAttributeValues(pCFellow->GetInstanceId(),
                *theAttrs, "FellowUpdate");
            //ms_rtiAmb->tick(0.1, 2.0);
        }
        if (theAttrs)
        {
            theAttrs->empty();
            delete theAttrs;
        }
    }
    catch (RTI::Exception& e)
    {
        AfxMessageBox((CString)e._name);
    }
}

void CFellow::FellowUpdateControl(RTI::Boolean status,
    const RTI::AttributeHandleSet& theAttrHandles)
{
    RTI::AttributeHandle attrHandle;

    for (unsigned int i = 0; i < theAttrHandles.size(); i++)
    {
        attrHandle = theAttrHandles.getHandle(i);
        if (attrHandle == CFellow::GetFellowNameRtiId())
        {
            m_bNameChanged = status;
        }
        else if (attrHandle == CFellow::GetFellowColorRtiId())
        {
            m_bColorChanged = status;
        }
        else if (attrHandle == CFellow::GetFellowPortraitRtiId())
        {
            m_bPortraitChanged = status;
        }
    }
}

CFellow* CFellow::FindFellow(RTI::ObjectHandle objectId)
{
    CFellowPtr pCFellow = NULL;

    for (unsigned int i = 0; i < ms_uExtentCardinality; i++)
    {
        pCFellow = ms_aFellowExtent[i];

        if (pCFellow &&(pCFellow->GetInstanceId() == objectId))
        {
            break;
        }
        else
        {
            pCFellow = NULL;
        }
    }

    return pCFellow;
}

//void CFellow::DeleteInstance()
//{
//    CFellow *pCFellow = NULL;
//    for (unsigned int idx = 0; idx < CFellow::ms_uExtentCardinality; idx++)
//    {
//        pCFellow = CFellow::ms_aFellowExtent[idx];
//        if (pCFellow->GetInstanceDeleted())
//        {
//
//        }
//    }
//}

RTI::AttributeHandleValuePairSet* CFellow::CreateNVPSet()
{
    RTI::AttributeHandleValuePairSet *pCFellowAttrs = NULL;

    if (ms_rtiAmb)
    {
        pCFellowAttrs = RTI::AttributeSetFactory::create(3);

        if (m_bNameChanged)
        {
            pCFellowAttrs->add(this->GetFellowNameRtiId(),
                (char*)this->GetFellowName(),
                ((strlen(this->GetFellowName()) + 1) * sizeof(char)));
        }
        if (m_bColorChanged)
        {
            RTI::ULong tmp;
            *((long*)&tmp) = htonl(*(((long*)&this->GetFellowColor()) + 1));
            *(((long*)&tmp) + 1) = htonl(*((long*)&this->GetFellowColor()));
            pCFellowAttrs->add(this->GetFellowColorRtiId(),
                (char*)&tmp,
                sizeof(RTI::ULong));
        }
        if (m_bPortraitChanged)
        {
            RTI::ULong tmp;
            *((long*)&tmp) = htonl(*(((long*)&this->GetFellowPortrait()) + 1));
            *(((long*)&tmp) + 1) = htonl(*((long*)&this->GetFellowPortrait()));
            pCFellowAttrs->add(this->GetFellowPortraitRtiId(),
                (char*)&tmp,
                sizeof(RTI::ULong));
        }
    }

    return pCFellowAttrs;
}

void CFellow::SetFellowName(const char* szName)
{
    if (strcmp(m_aFellowName, szName))
    {
        if (szName && strlen(szName) > 0)
        {
            strcpy(m_aFellowName, szName);
        }
        else
        {
            m_aFellowName[0] = '\0';
        }
        m_bNameChanged = RTI::RTI_TRUE;
    }
}

void CFellow::SetFellowName(CString str)
{
    wchar_t* p;
    p = str.GetBuffer(str.GetLength());
    str.ReleaseBuffer();
    WideCharToMultiByte(CP_ACP, WC_COMPOSITECHECK, p, -1, m_aFellowName, 
        sizeof(m_aFellowName), NULL, NULL);
}

void CFellow::SetFellowColor(const unsigned int& uColor)
{
    m_uFellowColor = uColor;
    m_bColorChanged = RTI::RTI_TRUE;
}

void CFellow::SetFellowPortrait(const unsigned int& uPortrait)
{
    m_uFellowPortrait = uPortrait;
    m_bPortraitChanged = RTI::RTI_TRUE;
}
