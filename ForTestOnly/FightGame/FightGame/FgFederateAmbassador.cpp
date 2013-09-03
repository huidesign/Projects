//-----------------------------------------------------------------
// Project Include Files
//-----------------------------------------------------------------
#include "FgFederateAmbassador.hh"
#include "Student.h"
#include "Splat.h"
#include "Communication.h"
//-----------------------------------------------------------------
// System Include Files
//-----------------------------------------------------------------
#ifndef _MSC_VER
#include <stdio.h>
#include <stdlib.h>

#include <iostream.h>
#else
#include <iostream>
using std::cout;
using std::cerr;
using std::endl;
#endif

//-----------------------------------------------------------------
// Bad C like global variables being externed - bad boy!!!
//-----------------------------------------------------------------
extern RTI::Boolean        timeAdvGrant;
extern RTI::Boolean        TimeRegulation;
extern RTI::Boolean        TimeConstrained;
extern RTI::FedTime        &grantTime;


FgFederateAmbassador::FgFederateAmbassador()
{
}

FgFederateAmbassador::~FgFederateAmbassador()
throw(RTI::FederateInternalError)
{
   cerr << "FED_HW: FgFederateAmbassador::~FgFederateAmbassador destructor called in FED"
	   << endl;
}

////////////////////////////////////
// Federation Management Services //
////////////////////////////////////

void FgFederateAmbassador::synchronizationPointRegistrationSucceeded (
  const char *label) // supplied C4)
throw (
  RTI::FederateInternalError)
{
   cerr << "FED_HW: synchronizationPointRegistrationSucceeded not supported in FED"
        << endl;
}

void FgFederateAmbassador::synchronizationPointRegistrationFailed (
  const char *label) // supplied C4)
throw (
  RTI::FederateInternalError)
{
   cerr << "FED_HW: synchronizationPointRegistrationFailed not supported in FED"
        << endl;
}

void FgFederateAmbassador::announceSynchronizationPoint (
  const char *label, // supplied C4
  const char *tag)   // supplied C4
throw (
  RTI::FederateInternalError)
{
   cerr << "FED_HW: announceSynchronizationPoint not supported in FED" << endl;
}

void FgFederateAmbassador::federationSynchronized (
  const char *label) // supplied C4)
throw (
  RTI::FederateInternalError)
{
   cerr << "FED_HW: federationSynchronized not supported in FED" << endl;
}


void FgFederateAmbassador::initiateFederateSave (
  const char *label) // supplied C4
throw (
  RTI::UnableToPerformSave,
  RTI::FederateInternalError)
{
   cerr << "FED_HW: initiateFederateSave not supported in FED" << endl;
}


void FgFederateAmbassador::federationSaved ()
throw (
  RTI::FederateInternalError)
{
   cerr << "FED_HW: federationSaved not supported in FED" << endl;
}


void FgFederateAmbassador::federationNotSaved ()
throw (
  RTI::FederateInternalError)
{
   cerr << "FED_HW: federationNotSaved not supported in FED" << endl;
}


void FgFederateAmbassador::requestFederationRestoreSucceeded (
  const char *label) // supplied C4
throw (
  RTI::FederateInternalError)
{
   cerr << "FED_HW: requestFederationRestoreSucceeded not supported in FED" << endl;
}


void FgFederateAmbassador::requestFederationRestoreFailed (
  const char *label) // supplied C4
throw (
  RTI::FederateInternalError)
{
   cerr << "FED_HW: requestFederationRestoreFailed not supported in FED" << endl;
}


void FgFederateAmbassador::requestFederationRestoreFailed (
  const char *label,
  const char *reason) // supplied C4
throw (
  RTI::FederateInternalError)
{
   cerr << "FED_HW: requestFederationRestoreFailed not supported in FED" << endl;
}


void FgFederateAmbassador::federationRestoreBegun ()
throw (
  RTI::FederateInternalError)
{
   cerr << "FED_HW: federationRestoreBegun not supported in FED" << endl;
}


void FgFederateAmbassador::initiateFederateRestore (
  const char               *label,   // supplied C4
        RTI::FederateHandle handle)  // supplied C1
throw (
  RTI::SpecifiedSaveLabelDoesNotExist,
  RTI::CouldNotRestore,
  RTI::FederateInternalError)
{
   cerr << "FED_HW: initiateFederateRestore not supported in FED" << endl;
}


void FgFederateAmbassador::federationRestored ()
throw (
  RTI::FederateInternalError)
{
   cerr << "FED_HW: federationRestored not supported in FED" << endl;
}


void FgFederateAmbassador::federationNotRestored ()
throw (
  RTI::FederateInternalError)
{
   cerr << "FED_HW: federationNotRestored not supported in FED" << endl;
}


/////////////////////////////////////
// Declaration Management Services //
/////////////////////////////////////

void FgFederateAmbassador::startRegistrationForObjectClass (
        RTI::ObjectClassHandle   theClass)      // supplied C1
throw (
  RTI::ObjectClassNotPublished,
  RTI::FederateInternalError)
{
   if (theClass == Student::GetStudentRtiId())
   {
	   cout << endl;
	   cout << "### Turned registration on for Student class" << endl;
	   Student::SetRegistration(RTI::RTI_TRUE);
   }
   else
   {
	   cerr << "### startRegistrationForObjectClass unknown class: "
		   << theClass << endl;
   }
}

void FgFederateAmbassador::stopRegistrationForObjectClass (
        RTI::ObjectClassHandle   theClass)      // supplied C1
throw (
  RTI::ObjectClassNotPublished,
  RTI::FederateInternalError)
{
   if (theClass == Student::GetStudentRtiId())
   {
	   cout << endl;
	   cout << "### stopRegistrationForObjectClass callback for Student" << endl;
	   Student::SetRegistration(RTI::RTI_FALSE);
   }
   
}


void FgFederateAmbassador::turnInteractionsOn (
  RTI::InteractionClassHandle theHandle) // supplied C1
throw (
  RTI::InteractionClassNotPublished,
  RTI::FederateInternalError)
{
   if (theHandle == Splat::GetSplatRtiId())
   {
	   cout << endl;
	   cout << "### turnInteractionOn callback for splat" << endl;
	   Splat::SetSendSplat(RTI::RTI_TRUE);
   }
   else if (theHandle == Communication::GetCommRtiId())
   {
	   cout << endl;
	   cout << "### turnInteractionOn callback for Communication" << endl;
	   Communication::SetSendCommInteractions(RTI::RTI_TRUE);
   }   
   else
   {
	   cout << endl;
	   cout << "### turnInteractionsOn callback for unknown" << endl;
   }
}

void FgFederateAmbassador::turnInteractionsOff (
  RTI::InteractionClassHandle theHandle) // supplied C1
throw (
  RTI::InteractionClassNotPublished,
  RTI::FederateInternalError)
{
	if (theHandle == Splat::GetSplatRtiId())
	{
		cout << endl;
		cout << "### turnInteractionOff callback for splat" << endl;
		Splat::SetSendSplat(RTI::RTI_FALSE);
	}
	else if (theHandle == Communication::GetCommRtiId())
	{
		cout << endl;
		cout << "### turnInteractionOff callback for Communication" << endl;
		Communication::SetSendCommInteractions(RTI::RTI_FALSE);
	}
	else
	{
		cout << endl;
		cout << "### turnInteractionsOff callback for unknown" << endl;
	}
}

////////////////////////////////
// Object Management Services //
////////////////////////////////

void FgFederateAmbassador::discoverObjectInstance (
  RTI::ObjectHandle          theObject,      // supplied C1
  RTI::ObjectClassHandle     theObjectClass, // supplied C1
  const char *          theObjectName)  // supplied C4
throw (
  RTI::CouldNotDiscover,
  RTI::ObjectClassNotKnown,
  RTI::FederateInternalError)
{
	cout << endl;
	cout << "### discoverObjectInstance called for student "
		 << theObjectName << " with handle " << theObject << endl;

	if (theObjectClass == Student::GetStudentRtiId())
	{
		//-----------------------------------------------------------------
		// Instantiate a local Student object to hold the state of the
		// remote object we just discovered.  This instance will get
		// stored in the static extent member data - it will be destructed
		// either when it is removed or when the application exits.
		//-----------------------------------------------------------------
		Student *tmpPtr = new Student(theObject);
		tmpPtr->SetName(theObjectName);
	}
	else
	{
		//-----------------------------------------------------------------
		// If not Student type then don't know what to do because all I
		// know about is Student objects.
		//-----------------------------------------------------------------
		cerr << "### Discover object class unknown to me." << endl;
	}
}

void FgFederateAmbassador::reflectAttributeValues (
        RTI::ObjectHandle                 theObject,     // supplied C1
  const RTI::AttributeHandleValuePairSet& theAttributes, // supplied C4
  const RTI::FedTime&                     theTime,       // supplied C1
  const char                             *theTag,        // supplied C4
        RTI::EventRetractionHandle        theHandle)     // supplied C1
throw (
  RTI::ObjectNotKnown,
  RTI::AttributeNotKnown,
  RTI::FederateOwnsAttributes,
  RTI::InvalidFederationTime,
  RTI::FederateInternalError)
{
	reflectAttributeValues(theObject, theAttributes, theTag);
}

void FgFederateAmbassador::reflectAttributeValues (
        RTI::ObjectHandle                 theObject,     // supplied C1
  const RTI::AttributeHandleValuePairSet& theAttributes, // supplied C4
  const char                             *theTag)        // supplied C4
throw (
  RTI::ObjectNotKnown,
  RTI::AttributeNotKnown,
  RTI::FederateOwnsAttributes,
  RTI::FederateInternalError)
{
	RTI::Double dLunchMoney;
	RTI::Double dCleanliness;
	RTI::ULong  ulAmmoAmount;
	cout << endl << "### reflectAttributeValues callback, which is coming from "
		 << theTag << endl;
   //-----------------------------------------------------------------
   // Find the Student instance this update is for.  If we can't find
   // it then I am getting data I didn't ask for.
   //-----------------------------------------------------------------
   Student *pStudent = Student::Find( theObject );

   if (pStudent)
   {
      //-----------------------------------------------------------------
      // Set the new attribute values in this country instance.
      //-----------------------------------------------------------------
	   cout << "   ### Found student" << pStudent->GetName() << endl;
	   try
	   {
		   RTI::ULong ulLength;
		   for (unsigned int idx = 0; idx < theAttributes.size(); idx++)
		   {
			   RTI::Handle pAttributes = theAttributes.getHandle(idx);
			   if (pAttributes == pStudent->GetLunchMoneyRtiId())
			   {
				   cout << "   ###Reflect LunchMoney" << endl;
				   theAttributes.getValue(idx, (char*)&dLunchMoney, ulLength);
				   pStudent->SetLunchMoney(dLunchMoney);
			   }
			   else if (pAttributes == pStudent->GetAmmoAmountRtiId())
			   {
				   cout << "   ###Reflect AmmoAmount" << endl;
				   theAttributes.getValue(idx, (char*)&ulAmmoAmount, ulLength);
				   pStudent->SetAmmoAmount(ulAmmoAmount);
			   }
			   else if (pAttributes == pStudent->GetCleanlinessRtiId())
			   {
				   cout << "   ###Reflect Cleanliness" << endl;
				   theAttributes.getValue(idx, (char*)&dCleanliness, ulLength);
				   pStudent->SetCleanliness(dCleanliness);
				   if (pStudent->GetCleanliness() <= 0.0)
				   {
					   pStudent->SetInstanceDeleted(RTI::RTI_TRUE);
				   }
			   }
			   else
			   {
				   cout << "   ###Unknown attributes handle" << endl;
			   }
		   }
	   }
	   catch (RTI::Exception& e)
	   {
		   cout << &e << endl;
		   exit(1);
	   }
   }
}

void FgFederateAmbassador::receiveInteraction (
        RTI::InteractionClassHandle       theInteraction, // supplied C1
  const RTI::ParameterHandleValuePairSet& theParameters,  // supplied C4
  const RTI::FedTime&                     theTime,        // supplied C4
  const char                             *theTag,         // supplied C4
        RTI::EventRetractionHandle        theHandle)      // supplied C1
throw (
  RTI::InteractionClassNotKnown,
  RTI::InteractionParameterNotKnown,
  RTI::InvalidFederationTime,
  RTI::FederateInternalError)
{
   this->receiveInteraction( theInteraction, theParameters, theTag );
}

void FgFederateAmbassador::receiveInteraction (
        RTI::InteractionClassHandle       theInteraction, // supplied C1
  const RTI::ParameterHandleValuePairSet& theParameters,  // supplied C4
  const char                             *theTag)         // supplied C4
throw (
  RTI::InteractionClassNotKnown,
  RTI::InteractionParameterNotKnown,
  RTI::FederateInternalError)
{
   //  Pass the interaction off to the Country class
   // so that it can be processed.
	cout << endl << "###receiveInteraction callback" << endl;
	if (theInteraction == Splat::GetSplatRtiId())
	{
		cout << "   ###Splat Interaction Received" << endl;
		char aTargetName[MAX_STRING];
		RTI::Double dEnsuingMess = 0.0;
		RTI::ULong  ulLength;
		try
		{
			for (unsigned int idx = 0; idx < theParameters.size(); idx++)
			{
				RTI::Handle pParameter = theParameters.getHandle(idx);
				if ( pParameter == Splat::GetTargetRtiId())
				{
					cout << "   ###Unpack Target" << endl;
					theParameters.getValue(idx, (char*)aTargetName, ulLength);
				}
				else if (pParameter == Splat::GetEnsuingMessRtiId())
				{
					cout << "   ###Unpack EnsuingMess" << endl;
					theParameters.getValue(idx, (char*)&dEnsuingMess, ulLength);
				}
				else
				{
					cout << "   ###Unknown parameter handle" << endl;
				}
			}
		}
		catch (RTI::Exception& e)
		{
			cout << &e << endl;
			exit(1);
		}
		
		// Look for the target among my students
        unsigned int idx = 0;
		for (; idx < Student::ms_extentCardinality; idx++)
		{
			if (Student::ms_studentExtent[idx]->GetInstanceDeleted())
			{
				continue;
			}
			if (!strcmp((Student::ms_studentExtent[idx])->GetName(), aTargetName))
			{
				// Add the value to EnsuingMess
				cout << "   ###The target is " << aTargetName << endl;
				cout << "   ###I Have Been " << theTag << endl;
				(Student::ms_studentExtent[idx])->SetEnsuingMess(
					(Student::ms_studentExtent[idx])->GetEnsuingMess() 	
					+ dEnsuingMess);
				(Student::ms_studentExtent[idx])->SetCleanliness(
					(Student::ms_studentExtent[idx])->GetCleanliness() 
					- dEnsuingMess);
				if ((Student::ms_studentExtent[idx])->GetCleanliness() <= 0.0)
				{
					(Student::ms_studentExtent[idx])->SetInstanceDeleted(
						RTI::RTI_TRUE);
				}
				else
				{
					(Student::ms_studentExtent[idx])->SetCleanlinessUpdate(
						RTI::RTI_TRUE);
				}
				break;
			}	
		}
		if (idx == Student::ms_extentCardinality)
		{
            cout << "   #No One be " << theTag << endl;
		}
		
	}
	else if (theInteraction == Communication::GetCommRtiId())
	{
        cout << endl << "   ###Communication Interaction Received" << endl;
        char       aMessage[MAX_STRING];
        RTI::ULong ulLength;
        try
        {
            for (unsigned int p = 0; p < theParameters.size(); p++)
            {
                if (theParameters.getHandle(p) == Communication::GetMessageRtiId())
                {
                    cout << "   ###Unpack Message" << endl;
                    theParameters.getValue(p, (char*)aMessage, ulLength);
                    cout << "   ###Message is" << aMessage << endl;
                }
                else
                {
                    cout << "   ###Unknown parameter handle" << endl;
                }
            }
        }
        catch (RTI::Exception& e)
        {
            cout << &e << endl;
            exit(1);
        }
	}
    else
    {
        cout << "  ###Unknown interaction" << endl;
    }
}

void FgFederateAmbassador::removeObjectInstance (
        RTI::ObjectHandle          theObject, // supplied C1
  const RTI::FedTime&              theTime,   // supplied C4
  const char                      *theTag,    // supplied C4
        RTI::EventRetractionHandle theHandle) // supplied C1
throw (
  RTI::ObjectNotKnown,
  RTI::InvalidFederationTime,
  RTI::FederateInternalError)
{
   //-----------------------------------------------------------------
   // Call the other removeObject method since this should probably
   //  be implemented using default parameter values.
   //-----------------------------------------------------------------
   this->removeObjectInstance( theObject, theTag );
}

void FgFederateAmbassador::removeObjectInstance (
        RTI::ObjectHandle          theObject, // supplied C1
  const char                      *theTag)    // supplied C4
throw (
  RTI::ObjectNotKnown,
  RTI::FederateInternalError)
{
	cout << endl;
	cout << "### removeObjectInstance callback" << endl;
	Student *pStudent = Student::Find(theObject);
	if (pStudent)
	{
		cout << "### Removing student " << pStudent->GetName() << endl;
		for (int idx = 0; idx < pStudent->ms_extentCardinality; idx++)
		{
			if (pStudent->GetInstanceId() == 
				(pStudent->ms_studentExtent[idx])->GetInstanceId())
				break;
		}
		pStudent->SetInstanceDeleted(RTI::RTI_TRUE);
	}
	else
	{
		cout << "### Student object " << theObject << "not found" << endl;
	}
}

void FgFederateAmbassador::attributesInScope (
        RTI::ObjectHandle        theObject,     // supplied C1
  const RTI::AttributeHandleSet& theAttributes) // supplied C4
throw (
  RTI::ObjectNotKnown,
  RTI::AttributeNotKnown,
  RTI::FederateInternalError)
{
   cerr << "FED_HW: attributesInScope not supported in FED" << endl;
}

void FgFederateAmbassador::attributesOutOfScope (
        RTI::ObjectHandle        theObject,     // supplied C1
  const RTI::AttributeHandleSet& theAttributes) // supplied C4
throw (
  RTI::ObjectNotKnown,
  RTI::AttributeNotKnown,
  RTI::FederateInternalError)
{
   cerr << "FED_HW: attributesOutOfScope not supported in FED" << endl;
}

void FgFederateAmbassador::provideAttributeValueUpdate (
        RTI::ObjectHandle        theObject,     // supplied C1
  const RTI::AttributeHandleSet& theAttributes) // supplied C4
throw (
  RTI::ObjectNotKnown,
  RTI::AttributeNotKnown,
  RTI::AttributeNotOwned,
  RTI::FederateInternalError)
{
   //-----------------------------------------------------------------
   // Find the Country instance this request is for.
   //-----------------------------------------------------------------
   Country *pCountry = Country::Find( theObject );

   if ( pCountry )
   {
      //-----------------------------------------------------------------
      // Touch the appropriate attribute values in this country
      // instance so that the get updated next cycle.
      //-----------------------------------------------------------------
      RTI::AttributeHandle attrHandle;

      //-----------------------------------------------------------------
      // We need to iterate through the AttributeHandleSet
      // to extract each AttributeHandle.  Based on the type
      // specified ( the value returned by getHandle() ) we need to
      // set the status of whether we should send this type of data.
      //-----------------------------------------------------------------
      for (unsigned int i = 0; i < theAttributes.size(); i++ )
      {
         attrHandle = theAttributes.getHandle( i );
         if ( attrHandle == Country::GetPopulationRtiId() )
         {
            // Touch population so that it gets update next cycle
            pCountry->SetPopulation( pCountry->GetPopulation() );
         }
         else if ( attrHandle == Country::GetNameRtiId() )
         {
            // Touch name so that it gets update next cycle
            pCountry->SetName( pCountry->GetName() );
         }
      }
   }
}

void FgFederateAmbassador::turnUpdatesOnForObjectInstance (
        RTI::ObjectHandle        theObject,     // supplied C1
  const RTI::AttributeHandleSet& theAttributes) // supplied C4
throw (
  RTI::ObjectNotKnown,
  RTI::AttributeNotOwned,
  RTI::FederateInternalError)
{
	cout << endl;
	cout << "### turnUpdatesOnForObjectInstance callback" << endl;
	Student *pStudent = Student::Find(theObject);
	if (pStudent)
	{
		pStudent->SetUpdateControl(RTI::RTI_TRUE, theAttributes);
	}
	else
	{
		cout << "### Student object" << theObject << " not found" << endl;
	}
}

void FgFederateAmbassador::turnUpdatesOffForObjectInstance (
        RTI::ObjectHandle        theObject,      // supplied C1
  const RTI::AttributeHandleSet& theAttributes) // supplied C4
throw (
  RTI::ObjectNotKnown,
  RTI::AttributeNotOwned,
  RTI::FederateInternalError)
{
	cout << endl;
	cout << "### turnUpdatesOffForObjectInstance callback" << endl;
	Student *pStudent = Student::Find(theObject);
	if (pStudent)
	{
		pStudent->SetUpdateControl(RTI::RTI_FALSE, theAttributes);
	}
	else
	{
		cout << "### Student object" << theObject << " not found" << endl;
	}
}

///////////////////////////////////
// Ownership Management Services //
///////////////////////////////////

void FgFederateAmbassador::requestAttributeOwnershipAssumption (
        RTI::ObjectHandle        theObject,         // supplied C1
  const RTI::AttributeHandleSet& offeredAttributes, // supplied C4
  const char                    *theTag)            // supplied C4
throw (
  RTI::ObjectNotKnown,
  RTI::AttributeNotKnown,
  RTI::AttributeAlreadyOwned,
  RTI::AttributeNotPublished,
  RTI::FederateInternalError)
{
   cerr << "FED_HW: requestAttributeOwnershipAssumption not supported in FED" << endl;
}

void FgFederateAmbassador::attributeOwnershipDivestitureNotification (
        RTI::ObjectHandle        theObject,          // supplied C1
  const RTI::AttributeHandleSet& releasedAttributes) // supplied C4
throw (
  RTI::ObjectNotKnown,
  RTI::AttributeNotKnown,
  RTI::AttributeNotOwned,
  RTI::AttributeDivestitureWasNotRequested,
  RTI::FederateInternalError)
{
   cerr << "FED_HW: attributeOwnershipDivestitureNotification not supported in FED"
        << endl;
}

void FgFederateAmbassador::attributeOwnershipAcquisitionNotification (
        RTI::ObjectHandle        theObject,         // supplied C1
  const RTI::AttributeHandleSet& securedAttributes) // supplied C4
throw (
  RTI::ObjectNotKnown,
  RTI::AttributeNotKnown,
  RTI::AttributeAcquisitionWasNotRequested,
  RTI::AttributeAlreadyOwned,
  RTI::AttributeNotPublished,
  RTI::FederateInternalError)
{
   cerr << "FED_HW: attributeOwnershipAcquisitionNotification not supported in FED"
        << endl;
}

void FgFederateAmbassador::attributeOwnershipUnavailable (
        RTI::ObjectHandle        theObject,         // supplied C1
  const RTI::AttributeHandleSet& theAttributes) // supplied C4
throw (
  RTI::ObjectNotKnown,
  RTI::AttributeNotKnown,
  RTI::AttributeAlreadyOwned,
  RTI::AttributeAcquisitionWasNotRequested,
  RTI::FederateInternalError)
{
   cerr << "FED_HW: attributeOwnershipUnavailable not supported in FED" << endl;
}

void FgFederateAmbassador::requestAttributeOwnershipRelease (
        RTI::ObjectHandle        theObject,           // supplied C1
  const RTI::AttributeHandleSet& candidateAttributes, // supplied C4
  const char                    *theTag)              // supplied C4
throw (
  RTI::ObjectNotKnown,
  RTI::AttributeNotKnown,
  RTI::AttributeNotOwned,
  RTI::FederateInternalError)
{
   cerr << "FED_HW: requestAttributeOwnershipRelease not supported in FED" << endl;
}

void FgFederateAmbassador::confirmAttributeOwnershipAcquisitionCancellation (
        RTI::ObjectHandle        theObject,         // supplied C1
  const RTI::AttributeHandleSet& theAttributes) // supplied C4
throw (
  RTI::ObjectNotKnown,
  RTI::AttributeNotKnown,
  RTI::AttributeAlreadyOwned,
  RTI::AttributeAcquisitionWasNotCanceled,
  RTI::FederateInternalError)
{
   cerr << "FED_HW: confirmAttributeOwnershipAcquisitionCancellation not"
        << " supported in FED" << endl;
}

void FgFederateAmbassador::informAttributeOwnership (
  RTI::ObjectHandle    theObject,    // supplied C1
  RTI::AttributeHandle theAttribute, // supplied C1
  RTI::FederateHandle  theOwner)     // supplied C1
throw (
  RTI::ObjectNotKnown,
  RTI::AttributeNotKnown,
  RTI::FederateInternalError)
{
   cerr << "FED_HW: informAttributeOwnership not supported in FED" << endl;
}

 void FgFederateAmbassador::attributeIsNotOwned (
  RTI::ObjectHandle    theObject,    // supplied C1
  RTI::AttributeHandle theAttribute) // supplied C1
throw (
  RTI::ObjectNotKnown,
  RTI::AttributeNotKnown,
  RTI::FederateInternalError)
{
   cerr << "FED_HW: attributeIsNotOwned not supported in FED" << endl;
}

void FgFederateAmbassador::attributeOwnedByRTI (
  RTI::ObjectHandle    theObject,    // supplied C1
  RTI::AttributeHandle theAttribute) // supplied C1
throw (
  RTI::ObjectNotKnown,
  RTI::AttributeNotKnown,
  RTI::FederateInternalError)
{
   cerr << "FED_HW: attributeOwnedByRTI not supported in FED" << endl;
}

//////////////////////////////
// Time Management Services //
//////////////////////////////

void FgFederateAmbassador::timeRegulationEnabled (
 const  RTI::FedTime& theFederateTime) // supplied C4
throw (
  RTI::InvalidFederationTime,
  RTI::EnableTimeRegulationWasNotPending,
  RTI::FederateInternalError)
{
   cout << "FED_HW: Time granted (timeRegulationEnabled) to: "
        << theFederateTime << endl;
   grantTime = theFederateTime;
   timeAdvGrant = RTI::RTI_TRUE;
   TimeRegulation = RTI::RTI_TRUE;
}

void FgFederateAmbassador::timeConstrainedEnabled (
  const RTI::FedTime& theFederateTime) // supplied C4
throw (
  RTI::InvalidFederationTime,
  RTI::EnableTimeConstrainedWasNotPending,
  RTI::FederateInternalError)
{
   cout << "FED_HW: Time granted (timeConstrainedEnabled) to: "
        << theFederateTime << endl;
   grantTime = theFederateTime;
   timeAdvGrant = RTI::RTI_TRUE;
   TimeConstrained = RTI::RTI_TRUE;
}

void FgFederateAmbassador::timeAdvanceGrant (
  const RTI::FedTime& theTime) // supplied C4
throw (
  RTI::InvalidFederationTime,
  RTI::TimeAdvanceWasNotInProgress,
  RTI::FederateInternalError)
{
   cout << "FED_HW: Time granted (timeAdvanceGrant) to: "
        << theTime << endl;
   grantTime = theTime;
   timeAdvGrant = RTI::RTI_TRUE;
}

void FgFederateAmbassador::requestRetraction (
  RTI::EventRetractionHandle theHandle) // supplied C1
throw (
  RTI::EventNotKnown,
  RTI::FederateInternalError)
{
   cerr << "FED_HW: requestRetraction not supported in FED" << endl;
}

