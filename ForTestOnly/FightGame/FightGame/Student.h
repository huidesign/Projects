#pragma once
#ifndef _FIGHTGAME_STUDENT_H
#define _FIGHTGAME_STUDENT_H
#include <RTI.hh>
#include "Splat.h"
#define MAX_FEDERATE 100
class Student
{
public:
	Student();
	Student(RTI::ObjectHandle id);
	virtual ~Student();
	//////////////////////////////////////////////////////////////////////////
	// Methods acting on the RTI
	//////////////////////////////////////////////////////////////////////////
	static Student* Find(RTI::ObjectHandle objectId);
	static void     Init(RTI::RTIambassador* rtiAmb);
	void            PublishAndSubcribe();
	void            Register();
	void            StudentUpdate(Student* pStudent);
	void            ProcessOwnership(Student* myStudent, 
                                     RTI::Boolean defector, int loop);
	void            Shoot(Student* myStudent, Splat* mySplat);
	void            DeleteInstance(Student* myStudent);
	void            PrintStudents(Student* myStudent);

	//////////////////////////////////////////////////////////////////////////
	// Accessor Methods
	//////////////////////////////////////////////////////////////////////////
	const char* GetName() 
	{
		return m_szName;
	}
	RTI::ObjectHandle& GetInstanceId() 
	{
		return m_hInstanceId;
	}
	RTI::Double& GetLunchMoney() 
	{
		return m_dLunchMoney;
	}
	RTI::ULong& GetAmmoAmount() 
	{
		return m_ulAmmoAmount;
	}
	RTI::Double& GetCleanliness()
	{
		return m_dCleanliness;
	}
	RTI::Double& GetEnsuingMess() 
	{
		return m_dEnsuingMess;
	}
	RTI::Boolean GetOwnLunchMoney() 
	{
		return m_bOwnLunchMoney;
	}
	RTI::Boolean GetOwnCleanliness() 
	{
		return m_bOwnCleanliness;
	}
	RTI::Boolean GetOwnAmmoAmount() 
	{
		return m_bOwnAmmoAmount;
	}
	RTI::Boolean GetOwnPrivilegeToDelete()
	{
		return m_bOwnPrivilegeToDelete;
	}
	RTI::Boolean GetTransferLunchMoney()
	{
		return m_bTransferLunchMoney;
	}
	RTI::Boolean GetTransferCleanliness()
	{
		return m_bTransferCleanliness;
	}
	RTI::Boolean GetTransferAmmoAmount() 
	{
		return m_bTransferAmmoAmount;
	}
	RTI::Boolean GetTransferPrivilegeToDelete() 
	{
		return m_bTransferPrivilegeToDelete;
	}
	RTI::Boolean GetLunchMoneyUpdate()
	{
		return m_bLunchMoneyUpdate;
	}
	RTI::Boolean GetCleanlinessUpdate()
	{
		return m_bCleanlinessUpdate;
	}
	RTI::Boolean GetAmmoAmountUpdate()
	{
		return m_bAmmoAmountUpdate;
	}
	RTI::Boolean GetInstanceDeleted()
	{
		return m_bInstanceDeleted;
	}

	//////////////////////////////////////////////////////////////////////////
	// Static Accessor Methods
	//////////////////////////////////////////////////////////////////////////
	static RTI::Boolean GetRegistration()
	{
		return ms_bDoRegistry;
	}
	static RTI::ObjectClassHandle GetStudentRtiId()
	{
		return ms_hStudent;
	}
	static RTI::AttributeHandle GetLunchMoneyRtiId()
	{
		return ms_hLunchMoney;
	}
	static RTI::AttributeHandle GetCleanlinessRtiId()
	{
		return ms_hCleanliness;
	}
	static RTI::AttributeHandle GetAmmoAmountRtiId()
	{
		return ms_hAmmoAmount;
	}
	static RTI::AttributeHandle GetPrivilegeToDeleteRtiId()
	{
		return ms_hPrivilegeToDelete;
	}

	//////////////////////////////////////////////////////////////////////////
	// Mutator Method
	//////////////////////////////////////////////////////////////////////////
	void SetName(const char*);
	void SetLunchMoney(const RTI::Double);
	void SetAmmoAmount(const RTI::ULong);
	void SetCleanliness(const RTI::Double);
	void SetEnsuingMess(const RTI::Double);

	void SetOwnLunchMoney(RTI::Boolean status)
	{
		m_bOwnLunchMoney = status;
	}
	void SetOwnCleanliness(RTI::Boolean status)
	{
		m_bOwnCleanliness = status;
	}
	void SetOwnAmmoAmount(RTI::Boolean status)
	{
		m_bOwnAmmoAmount = status;
	}
	void SetOwnPrivilegeToDelete(RTI::Boolean status)
	{
		m_bOwnPrivilegeToDelete = status;
	}

	void SetTransferLunchMoney(RTI::Boolean status)
	{
		m_bTransferLunchMoney = status;
	}
	void SetTransferAmmoAmount(RTI::Boolean status)
	{
		m_bTransferAmmoAmount = status;
	}
	void SetTransferCleanliness(RTI::Boolean status)
	{
		m_bTransferCleanliness = status;
	}
	void SetTransferPrivilegeToDelete(RTI::Boolean status)
	{
		m_bTransferPrivilegeToDelete = status;
	}

	void SetLunchMoneyUpdate(RTI::Boolean status)
	{
		m_bLunchMoneyUpdate = status;
	}
	void SetAmmoAmountUpdate(RTI::Boolean status)
	{
		m_bAmmoAmountUpdate = status;
	}
	void SetCleanlinessUpdate(RTI::Boolean status)
	{
		m_bCleanlinessUpdate = status;
	}
	void SetInstanceDeleted(RTI::Boolean status)
	{
		m_bInstanceDeleted = status;
	}
	void SetUpdateControl(RTI::Boolean status, 
		const RTI::AttributeHandleSet& theAttrHandles);
	// Static Mutator Methods
	static void SetRegistration(RTI::Boolean status)
	{
		ms_bDoRegistry = status;
	}

	//////////////////////////////////////////////////////////////////////////
	// Static Members
	//////////////////////////////////////////////////////////////////////////
	static Student* ms_studentExtent[MAX_FEDERATE + 1];
	static unsigned ms_extentCardinality;

private:
	char *m_szName;
	RTI::OrderingHandle m_hInstanceId;
	RTI::Double m_dLunchMoney;
	RTI::ULong m_ulAmmoAmount;
	RTI::Double m_dCleanliness;
	RTI::Double m_dEnsuingMess;

	RTI::Boolean m_bOwnAmmoAmount;
	RTI::Boolean m_bOwnLunchMoney;
	RTI::Boolean m_bOwnCleanliness;
	RTI::Boolean m_bOwnPrivilegeToDelete;

	RTI::Boolean m_bTransferAmmoAmount;
	RTI::Boolean m_bTransferLunchMoney;
	RTI::Boolean m_bTransferCleanliness;
	RTI::Boolean m_bTransferPrivilegeToDelete;

	RTI::Boolean m_bAmmoAmountUpdate;
	RTI::Boolean m_bLunchMoneyUpdate;
	RTI::Boolean m_bCleanlinessUpdate;
	RTI::Boolean m_bInstanceDeleted;
	//////////////////////////////////////////////////////////////////////////
	// Static Member Data
	//////////////////////////////////////////////////////////////////////////

	// Registration Control Flags for class
	static RTI::Boolean ms_bDoRegistry;

	// Run-Time Type Identification data
	static RTI::ObjectClassHandle ms_hStudent;
	static RTI::AttributeHandle   ms_hLunchMoney;
	static RTI::AttributeHandle   ms_hAmmoAmount;
	static RTI::AttributeHandle   ms_hCleanliness;
	static RTI::AttributeHandle   ms_hPrivilegeToDelete;

	// Names for querying RTI values
	static char* const            ms_szStudent;
	static char* const            ms_szLunchMoney;
	static char* const            ms_szAmmoAmount;
	static char* const            ms_szCleanliness;
	static char* const            ms_szPrivilegeToDelete;

	static RTI::RTIambassador*    ms_rtiAmb;
};

#endif