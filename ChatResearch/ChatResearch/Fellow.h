#pragma once
#ifndef _CHAT_RESEARCH_FELLOW_H
#define _CHAT_RESEARCH_FELLOW_H

#if defined(_MSC_VER)
#define RTI_USES_STD_FSTREAM
#endif // defined(_MSC_VER)
#include <RTI.hh>
#if defined(RTI_USES_STD_FSTREAM)
using std::ostream;
#endif // defined(_MSC_VER)

const unsigned int MAX_HELLOWORLD_FEDERATES = 20;

//-----------------------------------------------------------------
// Forward Declarations
//-----------------------------------------------------------------
class CFellow;

//-----------------------------------------------------------------
// Typedefs
//-----------------------------------------------------------------
typedef CFellow* CFellowPtr;

//-----------------------------------------------------------------
//
// CLASS:
//     Country
//
// PURPOSE:
//     The purpose of instances of class Country is to demonstrate
//     the proper usage of the RTI C++ API.  Instances can update
//     their state on the local machine (actually simulate the 
//     population) or from reflections provided by the RTI
//     (ghosting).
//
//     Note: Neither the interface nor the implementation of
//           Country is intended to be a tutorial on
//           Object-Oriented Analysis & Design.
//
// HISTORY:
//     1) Created 11/6/96
//     2) Updated to RTI 1.3 3/26/98
//
//-----------------------------------------------------------------
class CFellow
{
public:
    CFellow(const char* str);
    CFellow(RTI::ObjectHandle id);
    virtual ~CFellow(void);
    //-----------------------------------------------------------------
    // Methods acting on the RTI
    //-----------------------------------------------------------------
    static CFellowPtr   FindFellow(RTI::ObjectHandle       objectId);
    static void         InitFellow(RTI::RTIambassador *rtiAmb);
    void                PublishAndSubscribe();
    void                RegisterFellow();
    //void                Update( RTI::FedTime& newTime );
    void                UpdateFellow(CFellow *pCFellow);
    void                FellowUpdateControl(RTI::Boolean status, const RTI::AttributeHandleSet& theAttrHandles);
    //void                DeleteInstance();

    //-----------------------------------------------------------------
    // Accessor Methods
    //-----------------------------------------------------------------
    //RTI::FedTime const &                         GetLastTime()
    //{ return m_lastTime; };
    //RTI::FedTime const &                         GetLastTimePlusLookahead()
    //{ m_TimePlusLookahead = m_lastTime;
    //m_TimePlusLookahead+=ms_lookahead;
    //return m_TimePlusLookahead;};
    const char*                         GetFellowName()
    {
        return (char*)m_aFellowName;
    };
    RTI::ULong&                         GetFellowColor()
    {
        return m_uFellowColor;
    };
    RTI::ULong&                         GetFellowPortrait()
    {
        return m_uFellowPortrait;
    }

    RTI::Boolean                        GetFellowNameUpdate()
    {
        return m_bNameChanged;
    }
    RTI::Boolean                        GetFellowColorUpdate()
    {
        return m_bColorChanged;
    }
    RTI::Boolean                        GetFellowPortraitUpdate()
    {
        return m_bPortraitChanged;
    }

    RTI::ObjectHandle&                  GetInstanceId()
    {
        return m_hInstance;
    }
    //RTI::Boolean                        GetInstanceDeleted()
    //{
    //    return m_bInstanceDeleted;
    //}

    void                            SetFellowNameUpdate(RTI::Boolean status)
    {
        m_bNameChanged = status;
    }
    void                            SetFellowColorUpdate(RTI::Boolean status)
    {
        m_bColorChanged = status;
    }
    void                            SetFellowPortraitUpdate(RTI::Boolean status)
    {
        m_bPortraitChanged = status;
    }

    // Static Accessor Methods
    static RTI::ObjectClassHandle       GetFellowRtiId()
    {
        return ms_hFellow;
    }
    static RTI::AttributeHandle         GetFellowNameRtiId() 
    {
        return ms_hFellowName;
    }
    static RTI::AttributeHandle         GetFellowColorRtiId()
    {
        return ms_hFellowColor;
    }
    static RTI::AttributeHandle         GetFellowPortraitRtiId()
    {
        return ms_hFellowPortrait;
    }

    static void                         SetRegistration(RTI::Boolean status)
    {
        ms_bDoRegistry = status;
    }
    //static RTI::FedTime const &         GetLookahead()
    //{ return ms_lookahead;};

    //-----------------------------------------------------------------
    // Mutator Methods
    //-----------------------------------------------------------------
    //void                                SetLastTime( RTI::FedTime const & time )
    //{ m_lastTime = time;};
    void                                SetFellowName(const char*);
    void                                SetFellowName(CString);
    void                                SetFellowColor(const unsigned int&);
    void                                SetFellowPortrait(const unsigned int&);

    //static void SetLookahead( RTI::FedTime& time )
    //{ ms_lookahead = time;};

    //-----------------------------------------------------------------
    // Static Members
    //-----------------------------------------------------------------
    //static const double                 ms_growthRate; 

    // Extent data memebers
    static CFellowPtr                   ms_aFellowExtent[MAX_HELLOWORLD_FEDERATES + 1];
    static unsigned int                 ms_uExtentCardinality;    

protected:
    RTI::AttributeHandleValuePairSet*   CreateNVPSet();

private:
    union{
        char                            m_aFellowName[256];
        char                            fellowNameInit;
    };
    union{
        char                            m_aMessage[1024];
        char                            msgInit;
    };
    RTI::ULong                          m_uFellowColor;
    RTI::ULong                          m_uFellowPortrait;
    RTI::ObjectHandle                   m_hInstance;
    //RTI::FedTime &                      m_lastTime;
    //RTI::FedTime &                      m_TimePlusLookahead;
    static RTI::RTIambassador           *ms_rtiAmb;

    // Change flags for attribute values (dirty bits)
    RTI::Boolean                        m_bNameChanged;
    RTI::Boolean                        m_bColorChanged;
    RTI::Boolean                        m_bPortraitChanged;
    //RTI::Boolean                        m_bInstanceDeleted;

    //-----------------------------------------------------------------
    // Static Member Data
    //-----------------------------------------------------------------


    // Run-Time Type Identification data
    static RTI::ObjectClassHandle       ms_hFellow;
    static RTI::AttributeHandle         ms_hFellowName;
    static RTI::AttributeHandle         ms_hFellowColor;
    static RTI::AttributeHandle         ms_hFellowPortrait;

    // Names for querying RTTI values
    static char* const                  ms_szFellow;
    static char* const                  ms_szFellowName;
    static char* const                  ms_szFellowColor;
    static char* const                  ms_szFellowPortrait;

    // Object Register Flag
    static RTI::Boolean                 ms_bDoRegistry;

    // Lookahead Time value
    //static RTIfedTime                    ms_lookahead;
};

#endif  // define _CHAT_RESEARCH_FELLOW_H