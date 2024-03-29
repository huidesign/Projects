/************************************************************************/
/* Project Include Files                                                */
/************************************************************************/
#include "HwFederateAmbassador.h"
#include "Country.h"

/************************************************************************/
/* System Include Files                                                 */
/************************************************************************/
#ifdef _MSC_VER
#include <iostream>
using std::cout;
using std::cerr;
using std::endl;
#else
#include <stdio.h>
#include <stdlib.h>
#include <iostream.h>
#endif

//-----------------------------------------------------------------
// Bad C like global variables being externed - bad boy!!!
//-----------------------------------------------------------------
extern RTI::Boolean timeAdvGrant;
extern RTI::Boolean timeRegulation;
extern RTI::Boolean timeConstrained;
extern RTI::FedTime& grantTime;

HwFederateAmbassador::HwFederateAmbassador()
{
}

HwFederateAmbassador::~HwFederateAmbassador()
	throw(RTI::FederateInternalError)
{
	cerr << "FED_HW: HwFederateAmbassador::~HwFederateAmbassador destructor called in FED"
		 << endl;
}

/************************************************************************/
/* Federation Management Services                                       */
/************************************************************************/
void HwFederateAmbassador::synchronizationPointRegistrationSucceeded(
	const char *label)	// supplied C4)
	throw (
	RTI::FederateInternalError) {
		cerr << "FED_HW: synchronizationPointRegistrationSucceeded not supported in FED"
			 << endl;
}

void HwFederateAmbassador::synchronizationPointRegistrationFailed(
	const char *label)	// supplied C4)
	throw (
	RTI::FederateInternalError) {
		cerr << "FED_HW: synchronizationPointRegistrationFailed not supported in FED"
			 << endl;
}

void HwFederateAmbassador::announceSynchronizationPoint(
	const char *label,	// supplied C4)
	const char *tag)	// supplied C4)
	throw (
	RTI::FederateInternalError) {
		cerr << "FED_HW: announceSynchronizationPoint not supported in FED";
}

void HwFederateAmbassador::federationSynchronized(
	const char *label)	// supplied C4)
	throw (
	RTI::FederateInternalError) {
		cerr << "FED_HW: federationSynchronized not supported in FED" << endl;
}

void HwFederateAmbassador::initiateFederateSave(
	const char *label)	// supplied C4)
	throw (
	RTI::FederateInternalError) {
		cerr << "FED_HW: initiateFederateSave not supported in FED" << endl;
}

void HwFederateAmbassador::federationSaved()
	throw (
	RTI::FederateInternalError) {
		cerr << "FED_HW: federationSaved not supported in FED" << endl;
}

void HwFederateAmbassador::federationNotSaved()
	throw (
	RTI::FederateInternalError) {
		cerr << "FED_HW: federationNotSaved not supported in FED" << endl;
}

void HwFederateAmbassador::requestFederationRestoreSucceeded(
	const char *label)	// supplied C4)
	throw (
	RTI::FederateInternalError) {
		cerr << "FED_HW: requestFederationRestoreSucceeded not supported in FED" << endl;
}

// This one is not defined in federateAmbServices.hh
void HwFederateAmbassador::requestFederationRestoreFailed(
	const char *label)	// supplied C4)
	throw (
	RTI::FederateInternalError) {
		cerr << "FED_HW: requestFederationRestoreFailed not supported in FED" << endl;
}

void HwFederateAmbassador::requestFederationRestoreFailed(
	const char *label,	// supplied C4)
	const char *reason)	// supplied C4)
	throw (
	RTI::FederateInternalError) {
		cerr << "FED_HW: requestFederationRestoreFailed not supported in FED" << endl;
}

void HwFederateAmbassador::federationRestoreBegun()
	throw (
	RTI::FederateInternalError) {
		cerr << "FED_HW: requestFederationRestoreBegun not supported in FED" << endl;
}

void HwFederateAmbassador::initiateFederateRestore(
	const char          *label,	// supplied C4)
	RTI::FederateHandle handle)	// supplied C1)
	throw (
	RTI::SpecifiedSaveLabelDoesNotExist,
	RTI::CouldNotRestore,
	RTI::FederateInternalError) {
		cerr << "FED_HW: initiateFederateRestore not supported in FED" << endl;
}

void HwFederateAmbassador::federationRestored()
	throw (
	RTI::FederateInternalError) {
		cerr << "FED_HW: initiateFederateRestore not supported in FED" << endl;
}

void HwFederateAmbassador::federationNotRestored()
	throw (
	RTI::FederateInternalError) {
		cerr << "FED_HW: federationNotRestored not supported in FED" << endl;
}

/************************************************************************/
/* Declaration Management Services                                      */
/************************************************************************/
void HwFederateAmbassador::startRegistrationForObjectClass(
	RTI::ObjectClassHandle theClass)	// supplied C1)
	throw (
	RTI::ObjectClassNotPublished,
	RTI::FederateInternalError) {
		cerr << "FED_HW: startRegistrationForObjectClass not supported in FED" << endl;
}

void HwFederateAmbassador::stopRegistrationForObjectClass(
	RTI::ObjectClassHandle theClass)	// supplied C1)
	throw (
	RTI::ObjectClassNotPublished,
	RTI::FederateInternalError) {
		cerr << "FED_HW: stopRegistrationForObjectClass not supported in FED" << endl;
}

void HwFederateAmbassador::turnInteractionsOn(
	RTI::InteractionClassHandle theHandle)	// supplied C1)
	throw (
	RTI::InteractionClassNotPublished,
	RTI::FederateInternalError) {
		cerr << "FED_HW: turnInteractionsOn not supported in FED" << endl;
}

void HwFederateAmbassador::turnInteractionsOff(
	RTI::InteractionClassHandle theHandle)	// supplied C1)
	throw (
	RTI::InteractionClassNotPublished,
	RTI::FederateInternalError) {
		cerr << "FED_HW: turnInteractionsOff not supported in FED" << endl;
}

/************************************************************************/
/* Object Management Services                                           */
/************************************************************************/

void HwFederateAmbassador::discoverObjectInstance(	
	RTI::ObjectHandle      theObject,	    // supplied C1)
	RTI::ObjectClassHandle theObjectClass,	// supplied C1)
	const char             *theObjectName)	// supplied C4)
	throw (
	RTI::CouldNotDiscover,
	RTI::ObjectClassNotKnown,
	RTI::FederateInternalError) {
		cout << "FED_HW: Discover object " << theObject << endl;

		if (theObjectClass == Country::GetCountryRtiId())
		{
			//-----------------------------------------------------------------
			// Instantiate a local Country object to hold the state of the
			// remote object we just discovered.  This instance will get
			// stored in the static extent member data - it will be destructed
			// either when it is removed or when the application exits.
			//-----------------------------------------------------------------
			Country *tmpPtr = new Country(theObject);
		}
		else
		{
			//-----------------------------------------------------------------
			// If not Country type then don't know what to do because all I
			// know about is Country objects.
			//-----------------------------------------------------------------
			cerr << "FED_HW: Discovered object class unknown to me." << endl;
		}
}

void HwFederateAmbassador::reflectAttributeValues(
	RTI::ObjectHandle                       theObject,	    // supplied C1)
	const RTI::AttributeHandleValuePairSet& theAttributes,	// supplied C4) 
	const RTI::FedTime&                     theTime,	    // supplied C1) 
	const char                              *theTag,	    // supplied C4)
	RTI::EventRetractionHandle              theHandle)	    // supplied C1)
	throw (
	RTI::ObjectNotKnown,
	RTI::AttributeNotKnown,
	RTI::FederateOwnsAttributes,
	RTI::InvalidFederationTime,
	RTI::FederateInternalError) {
		//-----------------------------------------------------------------
		// Find the Country instance this update is for.  If we can't find
		// it then I am getting data I didn't ask for.
		//-----------------------------------------------------------------
		Country *pCountry = Country::Find(theObject);

		if (pCountry)
		{
			//-----------------------------------------------------------------
			// Set the new attribute values in this country instance.
			//-----------------------------------------------------------------
			pCountry->Update(theAttributes);
			pCountry->SetLastTime(theTime);
		}
		else
			throw RTI::ObjectNotKnown("received reflection for unknown OID");
}

void HwFederateAmbassador::reflectAttributeValues(
	RTI::ObjectHandle                       theObject,	    // supplied C1)
	const RTI::AttributeHandleValuePairSet& theAttributes,	// supplied C4) 
	const char                              *theTag)	    // supplied C4)
	throw (
	RTI::ObjectNotKnown,
	RTI::AttributeNotKnown,
	RTI::FederateOwnsAttributes,
	RTI::FederateInternalError) {
		//-----------------------------------------------------------------
		// Find the Country instance this update is for.  If we can't find
		// it then I am getting data I didn't ask for.
		//-----------------------------------------------------------------
		Country *pCountry = Country::Find(theObject);

		if (pCountry)
		{
			//-----------------------------------------------------------------
			// Set the new attribute values in this country instance.
			//-----------------------------------------------------------------
			pCountry->Update(theAttributes);
			RTI::FedTime * zero_time = RTI::FedTimeFactory::makeZero();
			pCountry->SetLastTime(*zero_time);
			delete zero_time;
		}
}

void HwFederateAmbassador::receiveInteraction(
	RTI::InteractionClassHandle             theInteraction,	// supplied C1) 
	const RTI::ParameterHandleValuePairSet& theParameters,	// supplied C4) 
	const RTI::FedTime&                     theTime,	    // supplied C4) 
	const char                              *theTag,	    // supplied C4) 
	RTI::EventRetractionHandle              theHandle)	// supplied C1) 
	throw (
	RTI::InteractionClassNotKnown,
	RTI::InteractionParameterNotKnown,
	RTI::InvalidFederationTime,
	RTI::FederateInternalError) {
		this->receiveInteraction(theInteraction, theParameters, theTag);
}

void HwFederateAmbassador::receiveInteraction(
	RTI::InteractionClassHandle             theInteraction,	// supplied C1) 
	const RTI::ParameterHandleValuePairSet& theParameters,	// supplied C4) 
	const char                              *theTag)	    // supplied C4) 
	throw (
	RTI::InteractionClassNotKnown,
	RTI::InteractionParameterNotKnown,
	RTI::FederateInternalError) {
		//  Pass the interaction off to the Country class
		// so that it can be processed.
		Country::Update(theInteraction, theParameters);
}

void HwFederateAmbassador::removeObjectInstance(
	RTI::ObjectHandle   theObject,	    // supplied C1)
	const RTI::FedTime& theTime,	    // supplied C4)
	const char          *theTag,		// supplied C4)
	RTI::EventRetractionHandle theHandle)	// supplied C1)
	throw (
	RTI::ObjectNotKnown,
	RTI::InvalidFederationTime,
	RTI::FederateInternalError) {
		//-----------------------------------------------------------------
		// Call the other removeObject method since this should probably
		//  be implemented using default parameter values.
		//-----------------------------------------------------------------
		this->removeObjectInstance(theObject, theTag);
}

void HwFederateAmbassador::removeObjectInstance(
	RTI::ObjectHandle theObject,	// supplied C1)
	const char        *theTag)		// supplied C4)
	throw (
	RTI::ObjectNotKnown,
	RTI::FederateInternalError) {
		cout << "FED_HW: Remove object " << theObject << endl;

		Country *pCountry = Country::Find(theObject);
		if (pCountry)
		{
			delete pCountry;
		}
}

void HwFederateAmbassador::attributesInScope(
	RTI::ObjectHandle              theObject,	    // supplied C1)
	const RTI::AttributeHandleSet& theAttributes)	// supplied C4)
	throw (
	RTI::ObjectNotKnown,
	RTI::AttributeNotKnown,
	RTI::FederateInternalError) {
		cerr << "FED_HW: attributesInScope not supported in FED" << endl;
}

void HwFederateAmbassador::attributesOutOfScope(
	RTI::ObjectHandle              theObject,	    // supplied C1)
	const RTI::AttributeHandleSet& theAttributes)	// supplied C4)
	throw (
	RTI::ObjectNotKnown,
	RTI::AttributeNotKnown,
	RTI::FederateInternalError) {
		cerr << "FED_HW: attributesOutOfScope not supported in FED" << endl;
}

void HwFederateAmbassador::provideAttributeValueUpdate(
	RTI::ObjectHandle              theObject,	    // supplied C1)
	const RTI::AttributeHandleSet& theAttributes)	// supplied C4)
	throw (
	RTI::ObjectNotKnown,
	RTI::AttributeNotKnown,
	RTI::AttributeNotOwned,
	RTI::FederateInternalError) {
		//-----------------------------------------------------------------
		// Find the Country instance this request is for.
		//-----------------------------------------------------------------
		Country *pCountry = Country::Find(theObject);

		if (pCountry)
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
			for (unsigned int i = 0; i < theAttributes.size(); i++)
			{
				attrHandle = theAttributes.getHandle(i);
				if (attrHandle == Country::GetPopulationRtiId())
				{
					// Touch population so that it gets update next cycle
					pCountry->SetPopulation(pCountry->GetPopulation());
				}
				else if (attrHandle == Country::GetNameRtiId())
				{
					// Touch name so that it gets update next cycle
					pCountry->SetName(pCountry->GetName());
				}
			}
		}
}

void HwFederateAmbassador::turnUpdatesOnForObjectInstance(
	RTI::ObjectHandle              theObject,	    // supplied C1) 
	const RTI::AttributeHandleSet& theAttributes)	// supplied C4)
	throw (
	RTI::ObjectNotKnown,
	RTI::AttributeNotKnown,
	RTI::FederateInternalError) {
		cerr << "FED_HW: turnUpdatesOnForObjectInstance not supported in FED" << endl;
}

void HwFederateAmbassador::turnUpdatesOffForObjectInstance(
	RTI::ObjectHandle              theObject,	    // supplied C1) 
	const RTI::AttributeHandleSet& theAttributes)	// supplied C4)
	throw (
	RTI::ObjectNotKnown,
	RTI::AttributeNotKnown,
	RTI::FederateInternalError) {
		 cerr << "FED_HW: turnUpdatesOffForObjectInstance not supported in FED" << endl;
}

/************************************************************************/
/* Ownership Management Services                                        */
/************************************************************************/

void HwFederateAmbassador::requestAttributeOwnershipAssumption(
	RTI::ObjectHandle              theObject,	        // supplied C1)
	const RTI::AttributeHandleSet& offeredAttributes,	// supplied C4)
	const char                     *theTag)	            // supplied C4)
	throw (
	RTI::ObjectNotKnown,
	RTI::AttributeNotKnown,
	RTI::AttributeAlreadyOwned,
	RTI::AttributeNotPublished,
	RTI::FederateInternalError) {
		cerr << "FED_HW: requestAttributeOwnershipAssumption not supported in FED" << endl;
}

void HwFederateAmbassador::attributeOwnershipDivestitureNotification(
	RTI::ObjectHandle              theObject,	        // supplied C1) 
	const RTI::AttributeHandleSet& releasedAttributes)	// supplied C4)
	throw (
	RTI::ObjectNotKnown,
	RTI::AttributeNotKnown,
	RTI::AttributeNotOwned,
	RTI::AttributeDivestitureWasNotRequested,
	RTI::FederateInternalError) {
		cerr << "FED_HW: attributeOwnershipDivestitureNotification not supported in FED"
			<< endl;
}

void HwFederateAmbassador::attributeOwnershipAcquisitionNotification(
	RTI::ObjectHandle              theObject,	         // supplied C1)
	const RTI::AttributeHandleSet& securedAttributes)	// supplied C4)
	throw (
	RTI::ObjectNotKnown,
	RTI::AttributeNotKnown,
	RTI::AttributeAcquisitionWasNotRequested,
	RTI::AttributeAlreadyOwned,
	RTI::AttributeNotPublished,
	RTI::FederateInternalError) {
		cerr << "FED_HW: attributeOwnershipAcquisitionNotification not supported in FED"
			<< endl;
}

void HwFederateAmbassador::attributeOwnershipUnavailable(
	RTI::ObjectHandle              theObject,	    // supplied C1)
	const RTI::AttributeHandleSet& theAttributes)	// supplied C4)
	throw (
	RTI::ObjectNotKnown,
	RTI::AttributeNotKnown,
	RTI::AttributeAlreadyOwned,
	RTI::AttributeAcquisitionWasNotRequested,
	RTI::FederateInternalError) {
		 cerr << "FED_HW: attributeOwnershipUnavailable not supported in FED" << endl;
}

void HwFederateAmbassador::requestAttributeOwnershipRelease(
	RTI::ObjectHandle              theObject,	        // supplied C1)
	const RTI::AttributeHandleSet& candidateAttributes,	// supplied C4)
	const char                     *theTag)	            // supplied C4)
	throw (
	RTI::ObjectNotKnown,
	RTI::AttributeNotKnown,
	RTI::AttributeNotOwned,
	RTI::FederateInternalError) {
		 cerr << "FED_HW: requestAttributeOwnershipRelease not supported in FED" << endl;
}

void HwFederateAmbassador::confirmAttributeOwnershipAcquisitionCancellation(
	RTI::ObjectHandle              theObject, 
	const RTI::AttributeHandleSet& theAttributes)
	throw (
	RTI::ObjectNotKnown,
	RTI::AttributeNotKnown,
	RTI::AttributeAlreadyOwned,
	RTI::AttributeAcquisitionWasNotCanceled,
	RTI::FederateInternalError) {
		cerr << "FED_HW: confirmAttributeOwnershipAcquisitionCancellation not"
			<< " supported in FED" << endl;
}

void HwFederateAmbassador::informAttributeOwnership(
	RTI::ObjectHandle    theObject, 
	RTI::AttributeHandle theAttribute, 
	RTI::FederateHandle  theOwner)
	throw (
	RTI::ObjectNotKnown,
	RTI::AttributeNotKnown,
	RTI::FederateInternalError) {
		cerr << "FED_HW: informAttributeOwnership not supported in FED" << endl;
}

void HwFederateAmbassador::attributeIsNotOwned(
	RTI::ObjectHandle theObject, 
	RTI::AttributeHandle theAttribute)
	throw (
	RTI::ObjectNotKnown,
	RTI::AttributeNotKnown,
	RTI::FederateInternalError) {
		cerr << "FED_HW: attributeIsNotOwned not supported in FED" << endl;
}

void HwFederateAmbassador::attributeOwnedByRTI(
	RTI::ObjectHandle theObject, 
	RTI::AttributeHandle theAttribute)
	throw (
	RTI::ObjectNotKnown,
	RTI::AttributeNotKnown,
	RTI::FederateInternalError) {
		cerr << "FED_HW: attributeOwnedByRTI not supported in FED" << endl;
}

/************************************************************************/
/* Time Management Services                                             */
/************************************************************************/

void HwFederateAmbassador::timeRegulationEnabled(
	const RTI::FedTime& theFederateTime)
	throw (
	RTI::InvalidFederationTime,
	RTI::EnableTimeRegulationWasNotPending,
	RTI::FederateInternalError) {
		cout << "FED_HW: Time granted (timeRegulationEnabled) to: "
			 << theFederateTime << endl;
		grantTime = theFederateTime;
		timeAdvGrant = RTI::RTI_TRUE;
		timeRegulation = RTI::RTI_TRUE;
}

void HwFederateAmbassador::timeConstrainedEnabled(
	const RTI::FedTime& theFederateTime)
	throw (
	RTI::InvalidFederationTime,
	RTI::EnableTimeConstrainedWasNotPending,
	RTI::FederateInternalError) {
		cout << "FED_HW: Time granted (timeConstrainedEnable) to: "
			 << theFederateTime << endl;
		grantTime = theFederateTime;
		timeAdvGrant = RTI::RTI_TRUE;
		timeConstrained = RTI::RTI_TRUE;
}

void HwFederateAmbassador::timeAdvanceGrant(
	const RTI::FedTime& theTime)
	throw (
	RTI::InvalidFederationTime,
	RTI::TimeAdvanceWasNotInProgress,
	RTI::FederateInternalError) {
		cout << "FED_HW: Time granted (timeAdvancedGrant) to :"
			 << theTime << endl;
		grantTime = theTime;
		timeAdvGrant = RTI::RTI_TRUE;
}

void HwFederateAmbassador::requestRetraction(
	RTI::EventRetractionHandle theHandle)
	throw (
	RTI::EventNotKnown,
	RTI::FederateInternalError) {
		cerr << "FED_HW: requestRetraction not supported in FED" << endl;
}