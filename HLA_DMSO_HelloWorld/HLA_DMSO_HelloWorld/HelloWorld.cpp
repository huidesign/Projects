#include "Country.h"
#include "HwFederateAmbassador.h"

#if !defined(WIN32) && !defined(VXWORKS) && !defined(__KCC) && (_SUNPRO_CC_COMPAT != 5)
#	include <stream.h>
#endif

#include <string.h>
#include <stdlib.h>

#if !defined(WIN32) && !defined(VXWORKS)
#	include <unistd.h>
#endif

#include <RTI.hh>

#if defined(WIN32)
#	include <windows.h>	// for sleep
#	include <sys/timeb.h>	// for "struct _timeb"
#	include <iostream>
using std::cout;
using std::cerr;
using std::endl;
#elif defined(VXWORKS)
#	include <ace/OS.h>
#	include <iostream>
#	include <timers.h>
using std::cout;
using std::flush;
using std::endl;
using std::cerr;
#else
#	include <sys/time.h>
#endif

#include <fedtime.hh>

RTI::Boolean	timeAdvGrant = RTI::RTI_FALSE;
RTI::Boolean	timeRegulation = RTI::RTI_FALSE;
RTI::Boolean	timeConstrained = RTI::RTI_FALSE;
RTI::FedTime&	grantTime = (*(RTI::FedTimeFactory::makeZero()));

void printUsage(const char* pExeName)
{
	cout << "FED_HW: usage: "
		 << pExeName
		 << " <Country Name> <Inittial Population> [<Number of Ticks>]"
		 << endl;
}

int hw_main(int argc, char *argv[])
{
	double       PreviousPopulation[100];
	const char   *exeName = argv[0];	        // Name of executable process
	char *const  fedExecName = "HelloWorld";	// Name of the Federation Execution
	Country      *myCountry = NULL;	            // Pointer to Federate's Country
	int          numberOfTicks(100);
	long         timeManaged = 1;

	int loopCounter = 0;

	for (; loopCounter < 100; ++loopCounter)
	{
		PreviousPopulation[loopCounter] = 0.0;
	}

	loopCounter = 0;

	//////////////////////////////////////////////////////////////////////////
	// Make sure executable is provided with correct number of arguments
	//////////////////////////////////////////////////////////////////////////
	if (argc < 3)
	{
		printUsage(exeName);
		return -1;
	}
	else if (!argv[1] && !argv[2] && (argc == 3 || !argv[3]))
	{
		printUsage(exeName);
	}
	else
	{
		myCountry = new Country(argv[1], argv[2]);
		if (argc > 3)
		{
			numberOfTicks = atoi(argv[3]);
		}
		if (argc > 4)
		{
			timeManaged = 0;
		}
	}

	try
	{
		//////////////////////////////////////////////////////////////////////////
		// Create RTI objects
		// The federate communicates to the RTI through the RTIambassador
		// object and the RTI communicates back to the federate through
		// the FederateAmbassador object.
		//////////////////////////////////////////////////////////////////////////
		RTI::RTIambassador       rtiAmb;		// libRTI provided
		HwFederateAmbassador     fedAmb;        // User-defined

		// Named value placeholder for the federates handle -
		// we don't really use this in HelloWorld but some
		// services and MOM might need it - if we were to use them.
		RTI::FederateHandle      federateId;

#if defined(WIN32)
		struct _timeb tb;
		_ftime(&tb);

		cout << myCountry->GetName() << " " << tb.time << " "
			 << tb.millitm * 1000 << " START" << endl;
#elif defined(VXWORKS)
		struct timespec tp;
		clock_gettime(CLOCK_REALTIME, &tp);

		cout << myCountry->GetName() << " " << tp.tv_sec << " "
			 << tp.tv_nsec / 1000L << " START" << endl;
#else
		static struct timeval tp;
		gettimeofday(&tp, NULL);

		cout << myCountry->GetName() << " "
			 << tp.tv_sec << " "
			 << tp.tv_usec << " "
			 << "START\n";
#endif

		RTI::Boolean Jointed = RTI::RTI_FALSE;
		int numTries         = 0;

		while (!Jointed && (numTries++ < 20))
		{
			//////////////////////////////////////////////////////////////////////////
			// Create Federation Execution
			//////////////////////////////////////////////////////////////////////////
			try
			{
				cout << "FED_HW: CREATING FEDERATION EXECUTION" << endl;
				rtiAmb.createFederationExecution(fedExecName, "HelloWorld.fed");
				cout << "FED_HW: SUCCESSFUL CREATE FEDERATION EXCUTIN" << endl;
			}
			catch (RTI::FederationExecutionAlreadyExists &e)
			{
				cerr << "FED_HW: Note: Federation execution already exists."
					 << e << endl;
			}
			catch (RTI::Exception &e)
			{
				cerr << "FED_HW: ERROR:_CFE" << e << endl;
				return -1;
			}

			//////////////////////////////////////////////////////////////////////////
			// Join Federation Execution
			//////////////////////////////////////////////////////////////////////////
			try
			{
				cout << "FED_HW: JOINING FEDERATION EXECUTION: " << exeName << endl;

				federateId = rtiAmb.joinFederationExecution(myCountry->GetName(),
					                                        fedExecName,
															&fedAmb);
				Jointed = RTI::RTI_TRUE;
			} 
			catch (RTI::FederateAlreadyExecutionMember &e)
			{
				cerr << "FED_HW: ERROR: " << myCountry->GetName()
					 << " already exists in the Federation Execution "
					 << fedExecName << "." << endl;
				cerr << e << endl;
				return -1;
			}
			catch (RTI::FederationExecutionDoesNotExist)
			{
				cerr << "FED_HW: ERROR: " << fedExecName << " Federation Execution "
					 << "does not exist." << endl;
				rtiAmb.tick(2.0, 2.0);
			}
			catch (RTI::Exception &e)
			{
				cerr << "FED_HW: ERROR:_JFE" << e << endl;
				return -1;
			}	
		}	// end of while

		cout << "FED_HW: JOINED SUCCESSFULLY: " << exeName
			 << ": Federate Handle = " << federateId << endl;

		 Country::Init(&rtiAmb);

		 myCountry->PublishAndSubscribe();
		 myCountry->Register();

		 // Set time step to 10
		 const RTIfedTime timeStep(10.0);

		 timeAdvGrant = RTI::RTI_FALSE;

		 try
		 {
			 cout << "FED_HW: ENABLING AYSNCHRONOUS DELIVERY" << endl;
			 rtiAmb.enableAsynchronousDelivery();
		 }
		 catch (RTI::Exception &e)
		 {
			 cerr << "FED_HW: ERROR:" << e << endl;
		 }

		 if (timeManaged)
		 {
			 //////////////////////////////////////////////////////////////////////////
			 // Set the Time Management parameters
			 // This version of HelloWorld operates as a time-stepped
			 // simulation.  This means that it should be constrained
			 // and regulating.
			 //////////////////////////////////////////////////////////////////////////
			 try
			 {
				 cout << "FED_HW: ENABLING TIME CONTRAINT" << endl;
				 //////////////////////////////////////////////////////////////////////////
				 // Turn on constrained status so that regulating
				 // federates will control our advancement in time.
				 //////////////////////////////////////////////////////////////////////////
				 rtiAmb.enableTimeConstrained();
				 timeAdvGrant    = RTI::RTI_FALSE;
				 timeConstrained = RTI::RTI_FALSE;

				 //////////////////////////////////////////////////////////////////////////
				 // Tick the RTI until we get the timeConstrainedEnabled
				 // callback with my current time.
				 //////////////////////////////////////////////////////////////////////////
				 while (!timeConstrained)
				 {
					 rtiAmb.tick(0.01, 1.0);
				 }
			 }
			 catch (RTI::Exception &e)
			 {
				 cerr << "FED_HW: ERROR:" << e << endl;
			 }

			 try
			 {
				 cout << "FED_HW: ENABLING TIME REGULATION WITH LOOKAHEAD = "
					  << Country::GetLookahead() << endl;
				 //////////////////////////////////////////////////////////////////////////
				 // Turn on regulating status so that constrained
				 // federates will be controlled by our time.
				 //////////////////////////////////////////////////////////////////////////
				 rtiAmb.enableTimeRegulation(grantTime, Country::GetLookahead());

				 //////////////////////////////////////////////////////////////////////////
				 // enableTimeRegulation is an implicit timeAdvanceRequest so set 
				 // timeAdvGrant to TRUE since we will get a timeRegulationEnabled 
				 // which is an implicit timeAdvanceGrant
				 //////////////////////////////////////////////////////////////////////////
				 timeAdvGrant = RTI::RTI_FALSE;
				 timeRegulation = RTI::RTI_FALSE;

				 //////////////////////////////////////////////////////////////////////////
				 // Tick the RTI until we get the timeRegulationEnabled
				 // callback with my current time.
				 //////////////////////////////////////////////////////////////////////////
				 while (!timeRegulation)
				 {
					 rtiAmb.tick(0.01, 1.0);
				 }
			 }
			 catch (RTI::Exception &e)
			 {
				 cerr << "FED_HW: ERROR:" << e << endl;
			 }
		 }

		 //////////////////////////////////////////////////////////////////////////
		 // 1.) Calculate current state and update to RTI.
		 // 2.) Ask for a time advance.
		 // 3.) Tick the RTI waiting for the grant and process all
		 //     RTI initiated services (especially reflections).
		 // 4.) Repeat.
		 //////////////////////////////////////////////////////////////////////////
		 int counter = 0;

		 while (counter++ < numberOfTicks - 1)
		 {
			 cout << "FED_HW: " << endl;
			 cout << "FED_HW: HelloWorld Event Loop Iteration #: " << counter << endl;

			 //////////////////////////////////////////////////////////////////////////
			 // 1.) - Update current state
			 //////////////////////////////////////////////////////////////////////////
			 myCountry->Update(grantTime);

			 // Print state of all countries
			 Country *pCountry = NULL;
			 for (unsigned int i = 0; i < Country::ms_extentCardinality; i++)
			 {
				 pCountry = Country::ms_countryExtent[i];

				 if (pCountry)
				 {
					 cout << "FED_HW: Country[" << i << "]" << pCountry << endl;

					 // Start of the modification
					 if (pCountry->GetPopulation() == PreviousPopulation[i])
					 {
						 cout << "*****************Not Updated******************\n";	
					 }
					 PreviousPopulation[i] = pCountry->GetPopulation();
					 // End of the modification
				 }
			 }
			 
			 //////////////////////////////////////////////////////////////////////////
			 // 2.) - Ask for a time advance.
			 //////////////////////////////////////////////////////////////////////////
			 if (RTI::RTI_FALSE)
			 {
				 try
				 {
					 RTIfedTime requestTime(timeStep.getTime());
					 requestTime += grantTime;
					 timeAdvGrant = RTI::RTI_FALSE;
					 loopCounter++;
					 rtiAmb.timeAdvanceRequest(requestTime);
				 }
				 catch (RTI::Exception &e)
				 {
				 	cerr << "FED_HW: ERROR: " << e << endl;
				 }
			 }
			 else
			 {
				 //////////////////////////////////////////////////////////////////////////
				 // 2.) - Ask for a next event request advance.
				 //////////////////////////////////////////////////////////////////////////
				 try
				 {
					 RTIfedTime requestTime(timeStep.getTime());
					 requestTime += grantTime;
					 timeAdvGrant = RTI::RTI_FALSE;
					 loopCounter = 0;
					 rtiAmb.nextEventRequest(requestTime);
				 }
				 catch (RTI::Exception &e)
				 {
					 cerr << "FED_HW: ERROR: " << e << endl;
				 }
			 }
			 //////////////////////////////////////////////////////////////////////////
			 // 3.) Tick the RTI waiting for the grant and process all
			 //     RTI initiated services (especially reflections).
			 //////////////////////////////////////////////////////////////////////////
			 if (timeManaged)
				 while (timeAdvGrant != RTI::RTI_TRUE)
				 {
					 //////////////////////////////////////////////////////////////////////////
					 // Tick will turn control over to the RTI so that it can
					 // process an event.  This will cause an invocation of one
					 // of the federateAmbassadorServices methods.
					 //
					 // Be sure not to invoke the RTIambassadorServices from the
					 // federateAmbassadorServices; otherwise, a ConcurrentAccess
					 // exception will be thrown.
					 //////////////////////////////////////////////////////////////////////////
					 rtiAmb.tick(0.01, 1.0);
				 }
			 else
				 rtiAmb.tick(2.0, 3.0);
		 }
		 //////////////////////////////////////////////////////////////////////////
		 // 4.) - Repeat
		 //////////////////////////////////////////////////////////////////////////

		 if (myCountry)
		 {
			 // Perform last update - this is necessary to give the
			 // Country instance the current granted time otherwise
			 // the deleteObjectInstance call that happens in the
			 // destructor will have an invalid time since it is in
			 // the past. This is a problem with HelloWorld not RTI.
			 myCountry->Update(grantTime);
			 delete myCountry;
		 }

		 if (timeManaged)
		 {
			 try
			 {
				 rtiAmb.disableTimeConstrained();
				 timeConstrained = RTI::RTI_FALSE;
			 }
			 catch (RTI::Exception &e)
			 {
			 	cerr << "FED_HW:ERR:" << e << endl;
			 }

			 try
			 {
				 rtiAmb.disableTimeRegulation();
				 timeRegulation = RTI::RTI_FALSE;
			 }
			 catch (RTI::Exception &e)
			 {
				 cerr << "FED_HW: ERROR:" << e << endl;
			 }
		 }

		 //////////////////////////////////////////////////////////////////////////
		 // Resign from the federation execution to remove this federate from 
		 // participation.  The flag provided will instruct the RTI to call 
		 // deleteObjectInstance for all objects this federate has privilegeToDelete
		 // for (which by default is all objects that this federate registered) and 
		 // to release ownership of any attributes that this federate owns but does 
		 // not own the privilefeToDelete for.
		 //////////////////////////////////////////////////////////////////////////

		 try
		 {
			 cout << "FED_HW: RESIGN FEDERATION EXECUTION CALLED" << endl;

			 rtiAmb.resignFederationExecution(RTI::DELETE_OBJECTS_AND_RELEASE_ATTRIBUTES);
			 cout << "FED_HW: SUCCESSFUL RESIGN FEDERATION EXECUTION CALLED" << endl;
		 }
		 catch (RTI::Exception &e)
		 {
			 cerr << "FED_HW: ERROR:" << e << endl;
			 return -1;
		 }

		 //////////////////////////////////////////////////////////////////////////
		 // Destroy the federation execution in case we are the last federate.
		 // This will not do anything bad if there other federates joined.
		 // The RTI will throw us an exception telling us that other federates
		 // are joined and we can just ignore that.
		 //////////////////////////////////////////////////////////////////////////
		 try
		 {
			 cout << "FED_HW: DESTROY FEDERATION EXECUTION CALLED" << endl;
			 rtiAmb.destroyFederationExecution(fedExecName);
			 cout << "FED_HW: SUCCESFUL DESTROY FEDERATION EXECUTION CALLED" << endl;
		 }
		 catch (RTI::FederatesCurrentlyJoined&)
		 {
			 cerr << "FED_HW: FederatesCurrentlyJoined" << endl;
			 return 0;
		 }
		 catch (RTI::FederationExecutionDoesNotExist&)
		 {
			 cerr << "FED_HW: FederationExecutinDoesNotExist" << endl;
			 return 0;
		 }
		 catch (RTI::Exception &e)
		 {
			 cerr << "FED_HW: ERROR:" << e << endl;
			 return -1;
		 }
	}
	catch (RTI::ConcurrentAccessAttempted &e)
	{
		cerr << "FED_HW: ERROR: Concurrent access to the RTI was attemted.\n"
			<< "       Exception caught in main() - PROGRAM EXITING.\n"
			<< "\n"
			<< "Note:  Concurrent access will result from invoking\n"
			<< "       RTIambassadorServices within the scope of\n"
			<< "       federateAmbassadorService invocations.\n"
			<< "\n"
			<< "       e.g. RTI calls provideAttributeValueUpdate() and\n"
			<< "       within that method you invoke updateAttributeValues\n"
			<< endl;
		cerr << e << endl;
		return -1;
	}
	catch (RTI::Exception &e)
	{
		cerr << "FED_HW: ERROR:" << e << endl;
		return -1;
	}

#if defined(WIN32)
	struct _timeb tb;
	_ftime(&tb);

	cout << argv[2] << " " << tb.time << " " << tb.millitm * 1000 << 
		" END" << endl;
#elif defined(VXWORKS)
	struct timespec tp;
	clock_gettime(CLOCK_REALTIME, &tp);

	cout << argv[2] << " " << tp.tv_sec << " " << tp.tv_nsec / 1000L 
		<< " START" << endl;
#else
	static struct timeval tp;
	gettimeofday(&tp, NULL);

	cout << argv[2] << " "
		<< tp.tv_sec << " "
		<< tp.tv_usec << " "
		<< "END\n";
#endif

	cout << "FED_HW: Exiting " << exeName << "." << endl;

	return 0;
}


#if defined(VXWORKS)
extern "C" 
{
	int
		hwmain(char* arg1, char* arg2, char* arg3)
	{
		ACE_MAIN_OBJECT_MANAGER;

		char* argv[] = { "hw_main", arg1, arg2, arg3 };
		int argc = 1;

		if ( argv[0] )
		{
			argc++;
			if ( argv[1] )
			{
				argc++;
				if ( argv[2] )
				{
					argc++;
				}
			}
		}

		return hw_main(argc, argv);
	}
}
#else
int
	main(int argc, char** argv)
{
	return hw_main(argc, argv);
}
#endif