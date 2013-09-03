#include "Student.h"
#include <iostream>
using std::cout;
using std::cerr;
using std::endl;

Student::Student()
{

}

Student::Student(RTI::ObjectHandle id)
{

}

Student::~Student()
{

}

void Student::Init(RTI::RTIambassador* rtiAmb)
{
	ms_rtiAmb = rtiAmb;

	if(ms_rtiAmb)
	{
		try
		{
			ms_hStudent = ms_rtiAmb->getObjectClassHandle(ms_szStudent);
			ms_hAmmoAmount = ms_rtiAmb->getAttributeHandle(ms_szAmmoAmount, 
				ms_hStudent);
			ms_hCleanliness = ms_rtiAmb->getAttributeHandle(ms_szCleanliness,
				ms_hStudent);
			ms_hPrivilegeToDelete = ms_rtiAmb->getAttributeHandle(
				ms_szPrivilegeToDelete, ms_hStudent);
		}
		catch(RTI::Exception& e)
		{
			cout << &e << endl;
			exit(1);
		}
	}
}

void Student::PublishAndSubcribe()
{
	if(ms_rtiAmb)
	{
		RTI::AttributeHandleSet *StudentAttributes;
		try
		{
			StudentAttributes = RTI::AttributeHandleSetFactory::create(4);
			StudentAttributes->add(ms_hLunchMoney);
			StudentAttributes->add(ms_hAmmoAmount);
			StudentAttributes->add(ms_hCleanliness);
			StudentAttributes->add(ms_hPrivilegeToDelete);
		}
		catch (RTI::Exception& e)
		{
			cout << &e << endl;
			exit(1);
		}

		try
		{
			ms_rtiAmb->subscribeObjectClassAttributes(ms_hStudent, 
				*StudentAttributes);
		}
		catch (RTI::Exception& e)
		{
			cout << &e << endl;
			exit(1);
		}

		try
		{
			ms_rtiAmb->publishObjectClass(ms_hStudent, *StudentAttributes);
		}
		catch (RTI::Exception& e)
		{
			cout << &e << endl;
			exit(1);
		}

		// CleanUp Attributes
		if (StudentAttributes)
		{
			StudentAttributes->empty();
			delete StudentAttributes;
		}
	}
}

void Student::Register()
{
	if (!ms_bDoRegistry)
	{
		cout << "*** Because no one Subscribe Student Class, so tick time!" 
             << endl;
	}
	while(!ms_bDoRegistry)
	{
		ms_rtiAmb->tick(0.01, 1.0);
	}

	for (int i = 0; i < STUDENT_NUM; i++)
	{
		try
		{
			(this->ms_studentExtent[i])->m_hInstanceId = 
				ms_rtiAmb->registerObjectInstance(
				(this->ms_studentExtent[i])->GetStudentRtiId(),
				(this->ms_studentExtent[i]->GetName()));
			cout << "*** Registered Student:"
				 << (this->ms_studentExtent[i])->GetInstanceId()
				 << "Name: " << (this->ms_studentExtent[i])->GetName()
				 << endl;
		}
		catch(RTI::Exception& e)
		{
			cerr << "*** ERROR:" << &e << endl;
		}
	}
}

void Student::DeleteInstance(Student* myStudent)
{
	Student *pStudent = NULL;
	for (int idx = 0; idx < myStudent->ms_extentCardinality; idx++)
	{
		pStudent = myStudent->ms_studentExtent[idx];
		if (pStudent->GetInstanceDeleted() 
            && pStudent->GetOwnPrivilegeToDelete())
		{
			try
			{
				cout << endl;
				cout << "*** Delete Object: " << pStudent->GetName() << endl;
				if (gRegulating)
				{
					ms_rtiAmb->queryLookahead(gLookahead);
					ms_rtiAmb->deleteObjectInstance(pStudent->GetInstanceId(),
						gCurrentTime + gLookahead, "Students Quits");
					ms_rtiAmb->tick(0.01, 1.0);
				}
				else
				{
					ms_rtiAmb->deleteObjectInstance(pStudent->GetInstanceId(),
						"Students Quits");
					ms_rtiAmb->tick(0.01, 1.0);
				}
			}
			catch (RTI::Exception& e)
			{
				cout << &e << endl;
				exit(1);
			}
			pStudent->SetOwnPrivilegeToDelete(RTI::RTI_FALSE);
		}
	}
}

void Student::StudentUpdate(Student* pStudent)
{
	int idx = 0;
	RTI::Double dLunchMoney;
	RTI::Double dCleanliness;
	RTI::ULong  ulAmmoAmount;
	RTI::AttributeHandleValuePairSet *theAttrs = NULL;

	try
	{
		theAttrs = RTI::AttributeSetFactory::create(3);
		// Update Student
		if (pStudent->GetLunchMoneyUpdate())
		{
			dLunchMoney = pStudent->GetLunchMoney();
			theAttrs->add(pStudent->GetLunchMoneyRtiId(),
				(char*)&dLunchMoney, sizeof(dLunchMoney));
			pStudent->SetLunchMoneyUpdate(RTI::RTI_FALSE);
		}

		if (pStudent->GetAmmoAmountUpdate())
		{
			ulAmmoAmount = pStudent->GetAmmoAmount();
			theAttrs->add(pStudent->GetAmmoAmountRtiId(),
				(char*)&ulAmmoAmount, sizeof(ulAmmoAmount));
			pStudent->SetAmmoAmountUpdate(RTI::RTI_FALSE);
		}

		if (pStudent->GetCleanlinessUpdate())
		{
			dCleanliness = GetCleanliness();
			theAttrs->add(pStudent->GetCleanlinessRtiId(),
				(char*)&dCleanliness, sizeof(dCleanliness));
			pStudent->SetCleanlinessUpdate(RTI::RTI_FALSE);
		}

		if (theAttrs->size())
		{
			cout << "*** Update " << pStudent->GetName() << endl;
			if (gRegulating)
			{
				ms_rtiAmb->queryLookahead(gLookahead);
				ms_rtiAmb->updateAttributeValues(pStudent->GetInstanceId(),
					*theAttrs, gCurrentTime + gLookahead, "Student Update");
				ms_rtiAmb->tick(0.1, 1.0);
			}
			else
			{
				ms_rtiAmb->updateAttributeValues(pStudent->GetInstanceId(),
					*theAttrs, "Student Update");
				ms_rtiAmb->tick(0.1, 1.0);
			}
		}
		
		if (theAttrs)
		{
			theAttrs->empty();
			delete theAttrs;
		}
	}
	catch (RTI::Exception& e)
	{
		cout << &e << endl;
		exit(1);
	}
}

void Student::ProcessOwnership(Student* myStudent, 
    RTI::Boolean defector, int loop)
{
    // One federate is designed the defector. After a period of time, 
    // this federate initiates the divestiture of a student. After another 
    // delay, this federate initiates the assumption of a student.

    Student *pStudent = NULL;

    // If we are the defector federate and the loop is 10, then divest.
    if (defector && loop == 10)
    {
        int defectorIdx = -1;
        
        // Pick the first available student to defect
        for (int idx = 0; idx < myStudent->ms_extentCardinality; idx++)
        {
            pStudent = myStudent->ms_studentExtent[idx];
            if (!pStudent->GetInstanceDeleted()
                && pStudent->GetOwnLunchMoney()
                && !pStudent->GetTransferLunchMoney()
                && pStudent->GetOwnAmmoAmount()
                && !pStudent->GetTransferAmmoAmount()
                && pStudent->GetOwnCleanliness()
                && !pStudent->GetTransferCleanliness()
                && pStudent->GetOwnPrivilegeToDelete()
                && !pStudent->GetTransferPrivilegeToDelete())
            {
                defectorIdx = idx;
                break;
            }
        }

        // If we found a student, then initiate divestiture
        if (defectorIdx > -1)
        {   
            try
            {
                cout << "***Initiate Divestiture of " << pStudent->GetName() 
                     << endl;
                RTI::AttributeHandleSet *theAttrs = NULL;
                try
                {
                    theAttrs = RTI::AttributeHandleSetFactory::create(4);
                    theAttrs->add(pStudent->GetLunchMoneyRtiId());
                    theAttrs->add(pStudent->GetAmmoAmountRtiId());
                    theAttrs->add(pStudent->GetCleanlinessRtiId());
                    theAttrs->add(pStudent->GetPrivilegeToDeleteRtiId());
                }
                catch (RTI::Exception& e)
                {
                    cout << &e << endl;
                    exit(1);
                }
                ms_rtiAmb->negotiatedAttributeOwnershipDivestiture(
                    pStudent->GetInstanceId(),
                    *theAttrs,
                    "Divest");
                ms_rtiAmb->tick(0.01, 1.0);
                theAttrs->empty();
                delete theAttrs;
            }
            catch (RTI::Exception& e)
            {
                cout << &e << endl;
                exit(1);
            }
        }
        else
        {
            cout << "***Couldn't find a student to divest!" << endl;
        }
    }
    // If we are the defector federate and the loop is 30, then acquire.
    else if (defector && loop == 30)
    {
        int defectorIdx = -1;
        // Pick the first available student to defect
        for (int idx = 0; idx < myStudent->ms_extentCardinality; idx++)
        {
            pStudent = myStudent->ms_studentExtent[idx];
            if (!pStudent->GetInstanceDeleted()
                && !pStudent->GetOwnLunchMoney()
                && !pStudent->GetTransferLunchMoney()
                && !pStudent->GetOwnAmmoAmount()
                && !pStudent->GetTransferAmmoAmount()
                && !pStudent->GetOwnCleanliness()
                && !pStudent->GetTransferCleanliness()
                && !pStudent->GetOwnPrivilegeToDelete()
                && !pStudent->GetTransferPrivilegeToDelete())
            {
                defectorIdx = idx;
                break;
            }
        }

        // If we found a student, then initiate divestiture
        if (defectorIdx > -1)
        {   
            try
            {
                cout << "***Initiate Acquisition of " << pStudent->GetName()
                     << endl;
                RTI::AttributeHandleSet *theAttrs = NULL;
                try
                {
                    theAttrs = RTI::AttributeHandleSetFactory::create(4);
                    theAttrs->add(pStudent->GetLunchMoneyRtiId());
                    theAttrs->add(pStudent->GetAmmoAmountRtiId());
                    theAttrs->add(pStudent->GetCleanlinessRtiId());
                    theAttrs->add(pStudent->GetPrivilegeToDeleteRtiId());
                }
                catch (RTI::Exception& e)
                {
                    cout << &e << endl;
                    exit(1);
                }
                ms_rtiAmb->attributeOwnershipAcquisition(
                    pStudent->GetInstanceId(),
                    *theAttrs,
                    "Acquire");
                ms_rtiAmb->tick(0.01, 1.0);
                theAttrs->empty();
                delete theAttrs;
            }
            catch (RTI::Exception& e)
            {
                cout << &e << endl;
                exit(1);
            }
        }
        else
        {
            cout << "***Couldn't find a student to acquire!" << endl;
        }
    }
    // Initiating a transfer results in one of the callbacks above.
    for (int idx = 0; idx < myStudent->ms_extentCardinality; idx++)
    {
        pStudent = myStudent->ms_studentExtent[idx];
        if (!pStudent->GetInstanceDeleted() 
            && (pStudent->GetOwnLunchMoney() && 
            !pStudent->GetTransferLunchMoney())
            || (pStudent->GetTransferAmmoAmount() &&
            !pStudent->GetTransferAmmoAmount())
            || (pStudent->GetCleanliness() &&
            !pStudent->GetTransferCleanliness())
            || (pStudent->GetOwnPrivilegeToDelete() &&
            !pStudent->GetPrivilegeToDeleteRtiId()))
        {
            try
            {
                cout << "***Attempting to release " << pStudent->GetName() 
                     << endl;
                RTI::AttributeHandleSet* theAttrs = NULL;
                try
                {
                    theAttrs = RTI::AttributeHandleSetFactory::create(4);
                    if (pStudent->GetTransferLunchMoney())
                    {
                        theAttrs->add(pStudent->GetLunchMoneyRtiId());

                    }
                }
                catch (CException* e)
                {
                }
            }
            catch (CException* e)
            {
            }
        }
    }
}