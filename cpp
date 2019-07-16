#ifndef __MEMBER__
#define __MEMBER__

#include <iostream>

const int MAX_NAME   = 32;
const int MAX_NUMBER = 32;
const int MAX_MEMBER = 1000;

class Member
{

	static int mIdSeed;

	protected:
		int   mId;
		char* mName;
		int   mAge;
		int   mClass;
	
	public:
		Member();
		virtual ~Member();
		
		void SetName(char* name);
		void SetAge(int age);
		void SetClass(int cls);
		
		bool Visit();
		
		int   Id();
		char* Name(); 
		int   Age(); 
		int   Class();
};

#endif

#include "Member.h"

int Member::mIdSeed = 1000;

Member::Member()
{
	mId      = mIdSeed++;
	mName    = new char[MAX_NAME];
	mName[0] = 0;
}


Member::~Member()
{
	delete[] mName;
}

void Member::SetName(char* name) { std::memcpy(mName, name, MAX_NAME); }
void Member::SetAge(int age) { mAge = age; }
void Member::SetClass(int cls) { mClass = cls; }

int   Member::Id() { return mId; }
char* Member::Name() { return mName; }
int   Member::Age() { return mAge; }
int   Member::Class() { return mClass; }

bool Member::Visit()
{
	return true;
}

#ifndef __SILVER_MEMBER__
#define __SILVER_MEMBER__

#include "Member.h"
#include <iostream>

class SilverMember : public Member
{
	protected:
		char* mHome;
		int mMileage;

	public:
		SilverMember(Member* member);
		virtual ~SilverMember();
		
		void SetHome(char* number);
		void SetMileage(int mileage);

		virtual bool Visit();

		char* Home();
		int Mileage();
};

#endif

#include "SilverMember.h"


SilverMember::SilverMember(Member* member)
{
	mId = member->Id();
	std::memcpy(mName, member->Name(), MAX_NUMBER);
	mAge = member->Age();
	mClass = member->Class();
	mHome = new char[MAX_NUMBER];
	mMileage = 0;
}

SilverMember::~SilverMember()
{
	delete[] mName;
}

void SilverMember::SetHome(char* number) { std::memcpy(mHome, number, MAX_NUMBER); }
void SilverMember::SetMileage(int mileage) { mMileage = mileage; }

char*  SilverMember::Home() { return mHome; }
int SilverMember::Mileage() { return mMileage; }

bool SilverMember::Visit()
{
	mMileage += 2;
	if(mMileage > 1000) return true;

	return false;
}

#ifndef __GOLD_MEMBER__
#define __GOLD_MEMBER__

#include <iostream>
#include "SilverMember.h"

class GoldMember : public SilverMember
{
	protected:
		char* mMobile;	

	public:
		GoldMember(SilverMember* member);
		virtual ~GoldMember();
		
		void SetMobile(char* number);

		virtual bool Visit();
		
		char* Mobile();
};

#endif

#include "GoldMember.h"

GoldMember::GoldMember(SilverMember* member) : SilverMember(member)
{
	std::memcpy(mHome, member->Home(), MAX_NUMBER);
	mMileage = member->Mileage();
	mMobile = new char[MAX_NUMBER];
}

GoldMember::~GoldMember()
{
	delete[] mMobile;
}

void GoldMember::SetMobile(char* number) { std::memcpy(mMobile, number, MAX_NUMBER); }

char*  GoldMember::Mobile() { return mMobile; }

bool GoldMember::Visit()
{
	mMileage += 3;

	return false;
}

#ifndef __PLATINUM_MEMBER__
#define __PLATINUM__MEMBER__

#include <iostream>
#include "GoldMember.h"

class PlatinumMember : public GoldMember
{

		char* mAddress;	

	public:
		PlatinumMember(GoldMember* member);
		virtual ~PlatinumMember();
		
		void SetAddress(char* mAddress);

		virtual bool Visit();
		
		char* Address();
};

#endif

#include "PlatinumMember.h"

PlatinumMember::PlatinumMember(GoldMember* member) : GoldMember(member)
{
	std::memcpy(mMobile, member->Mobile(), MAX_NUMBER);
	mAddress = new char[MAX_NUMBER];
}

PlatinumMember::~PlatinumMember()
{
	delete[] mAddress;
}

void PlatinumMember::SetAddress(char* address) { std::memcpy(mAddress, address, MAX_NUMBER); }

char*  PlatinumMember::Address() { return mAddress; }

bool PlatinumMember::Visit()
{
	mMileage += 5;

	return false;
}

#ifndef __MEMBER_MGR__
#define __MEMBER_MGR__

#include <iostream>
#include "PlatinumMember.h"

#define nullptr (0)
class MemberMgr
{
	private:
		Member* mMember[MAX_MEMBER];
		Member* mResult[MAX_MEMBER];
		int     mResultCount;

	public:
		MemberMgr();
		~MemberMgr();

		Member* Add();
		void    Delete(int id);
		Member* Visit(int id);

		void SearchByName(char* name);
		void SearchByAge(int age);
		void SearchByClass(int cls);
		void SearchAll();

		Member* Result();
};

#endif

#include "MemberMgr.h"

MemberMgr::MemberMgr()
{
	for (int c = 0; c < MAX_MEMBER; c++)
	{
		mMember[c] = nullptr;
	}

	mResultCount = 0;
}

MemberMgr::~MemberMgr()
{
	for (int c = 0; c <MAX_MEMBER; c++)
	{
		if(mMember[c] != nullptr)
		{
			delete mMember[c];
		}
	}
}


Member* MemberMgr::Add()
{
	int i;

	for (i = 0; i < MAX_MEMBER; i++)
	{
		if (mMember[i] == nullptr)
		{
			break;
		}
	}

	if (i == MAX_MEMBER)
	{
		return nullptr;
	}

	mMember[i] = new Member;
	return mMember[i];
}


void MemberMgr::Delete(int id)
{
	int i;

	for (i = 0; i < MAX_MEMBER; i++)
	{
		if(mMember[i] == nullptr)
		{
			continue;
		}

		if (mMember[i]->Id() == id)
		{
			break;
		}
	}

	if (i == MAX_MEMBER)
	{
		return;
	}

	delete mMember[i];
	mMember[i] = nullptr;

	return;
}

Member* MemberMgr::Visit(int id)
{
	int i;

	for (i = 0; i < MAX_MEMBER; i++)
	{
		if (mMember[i] == nullptr)
		{
			continue;
		}

		if (mMember[i]->Id() == id)
		{
			break;
		}
	}

	if (i == MAX_MEMBER)
	{
		return false;
	}

	if (mMember[i]->Visit() == false)
	{
		return nullptr;
	}

	if (typeid(*mMember[i]) == typeid(Member))
	{
		SilverMember* silver = new SilverMember(mMember[i]);
		delete mMember[i];
		mMember[i] = silver;
	}
	else if(typeid(*mMember[i]) == typeid(SilverMember))
	{
		GoldMember* gold = new GoldMember((SilverMember*)mMember[i]);
		delete mMember[i];
		mMember[i] = gold;
	}
	else
	{
		PlatinumMember* platinum = new PlatinumMember((GoldMember*)mMember[i]);
		delete mMember[i];
		mMember[i] = platinum;
	}

	return mMember[i];
}

void MemberMgr::SearchByName(char* name)
{
	mResultCount = 0;

	for (int i = 0; i < MAX_MEMBER; i++)
	{
		if (mMember[i] == nullptr)
		{
			continue;
		}

		if (std::strcmp(mMember[i]->Name(), name) == 0)
		{
			mResult[mResultCount++] = mMember[i];
		}
	}

	return;
}


void MemberMgr::SearchByAge(int age)
{
	mResultCount = 0;

	for (int i = 0; i < MAX_MEMBER; i++)
	{
		if (mMember[i] == nullptr)
		{
			continue;
		}

		if (mMember[i]->Age() == age)
		{
			mResult[mResultCount++] = mMember[i];
		}
	}

	return;
}


void MemberMgr::SearchByClass(int cls)
{
	mResultCount = 0;

	for (int i = 0; i < MAX_MEMBER; i++)
	{
		if (mMember[i] == nullptr)
		{
			continue;
		}

		if (mMember[i]->Class() == cls)
		{
			mResult[mResultCount++] = mMember[i];
		}
	}

	return;
}


void MemberMgr::SearchAll()
{
	mResultCount = 0;

	for (int i = 0; i < MAX_MEMBER; i++)
	{
		if (mMember[i] == nullptr)
		{
			continue;
		}

		mResult[mResultCount++] = mMember[i];
	}

	return;
}

Member* MemberMgr::Result()
{
	Member* result = nullptr;

	if (mResultCount == 0)
	{
		return nullptr;
	}

	for (int i = 0; i < MAX_MEMBER; i++)
	{
		if (mResult[i] != nullptr)
		{
			result = mResult[i];

			mResult[i] = nullptr;
			mResultCount--;
			break;
		}
	}

	return result;
}

#ifndef __MEMBER_VIEW__
#define __MEMBER_VIEW__

#include <iostream>
#include "Member.h"
#include "MemberMgr.h"

class MemberView
{
	private:
		MemberMgr* mMgr;

		void DisplayResult();

	public:
		MemberView(MemberMgr* mgr) { mMgr = mgr; }
	
		static void DisplayMemu();

		void Add();
		void Delete();
		void Visit();

		void SearchByName();
		void SearchByAge();
		void SearchByClass();
		void SearchAll();
};

#endif

#include "MemberView.h"

void MemberView::DisplayResult()
{
	while (Member* member = mMgr->Result())
	{
		std::cout << "----------\n";
		std::cout << "ID: " << member->Id() << "\n";
		std::cout << "Name: " << member->Name() << "\n";
		std::cout << "Age: " << member->Age() << "\n";
		std::cout << "Class: " << member->Class() << "\n";

		if (typeid(*member) == typeid(SilverMember))
		{
			SilverMember* silver = (SilverMember*)member;

			std::cout << "Home Number: " << silver->Home() << "\n";
			std::cout << "Mileage: " << silver->Mileage() << "\n\n";
			std::cout << "Grade: Siver Member\n";
		}
		else if (typeid(*member) == typeid(GoldMember))
		{
			GoldMember* gold = (GoldMember*)member;

			std::cout << "Home Number: " << gold->Home() << "\n";
			std::cout << "Mobile Number: " << gold->Mobile() << "\n";
			std::cout << "Mileage: " << gold->Mileage() << "\n\n";
			std::cout << "Grade: Gold Member\n";
		}
		else if (typeid(*member) == typeid(PlatinumMember))
		{
			PlatinumMember* platinum = (PlatinumMember*)member;

			std::cout << "Home Number: " << platinum->Home() << "\n";
			std::cout << "Mobile Number: " << platinum->Mobile() << "\n";
			std::cout << "Mileage: " << platinum->Mileage() << "\n";
			std::cout << "Address: " << platinum->Address() << "\n\n";
			std::cout << "Grade: Platinum Member\n";

		}

	}

	return;
}

void MemberView::Add()
{
	char   name[MAX_NAME];
	int    n;

	std::cout << "Enter Name: ";
	std::cin.ignore();
	std::cin.getline(name, MAX_NAME);

	if (name[0] == 0)
	{
		std::cout << "Name filed must be entered\n";
		return;
	}

	Member* member = mMgr->Add();

	member->SetName(name);

	std::cout << "Enter Age: ";
	std::cin >> n;
	member->SetAge(n);

	std::cout << "Enter Class: ";
	std::cin >> n;
	member->SetClass(n);

	return;
}


void MemberView::Delete()
{
	int id;

	std::cout << "Enter ID: ";
	std::cin >> id;
	mMgr->Delete(id);

	return;
}

void MemberView::Visit()
{
	int id;

	std::cout << "Enter ID: ";
	std::cin >> id;
	Member* member = mMgr->Visit(id);

	if (member == nullptr)
	{
		return;
	}

	char number[MAX_NUMBER];

	if (typeid(*member) == typeid(SilverMember))
	{
		std::cout << "Enter Home Number: ";
		std::cin.ignore();
		std::cin.getline(number, MAX_NUMBER);

		SilverMember* silver = (SilverMember*)member;
		silver->SetHome(number);
	}
	else if(typeid(*member) == typeid(GoldMember))
	{
		std::cout << "Enter Mobile Number: ";
		std::cin.ignore();
		std::cin.getline(number, MAX_NUMBER);

		GoldMember* gold = (GoldMember*)member;
		gold->SetMobile(number);
	}
	else
	{
		std::cout << "Enter Mobile Address: ";
		std::cin.ignore();
		std::cin.getline(number, MAX_NUMBER);

		PlatinumMember* platinum = (PlatinumMember*)member;
		platinum->SetAddress(number);
	}

	return;
}


void MemberView::SearchByName()
{
	char name[MAX_NAME];

	std::cout << "Enter Name: ";
	std::cin.ignore();
	std::cin.getline(name, MAX_NAME);
	mMgr->SearchByName(name);

	DisplayResult();
}


void MemberView::SearchByAge()
{
	int age;

	std::cout << "Enter Age: ";
	std::cin >> age;
	mMgr->SearchByAge(age);

	DisplayResult();
}


void MemberView::SearchByClass()
{
	int cls;

	std::cout << "Enter Class: ";
	std::cin >> cls;
	mMgr->SearchByClass(cls);

	DisplayResult();
}


void MemberView::SearchAll()
{
	mMgr->SearchAll();

	DisplayResult();
}

void MemberView::DisplayMemu()
{
	std::cout << "1. Registration\n";
	std::cout << "2. Withdrawal\n";
	std::cout << "3. Visit\n";
	std::cout << "4. Search by Name\n";
	std::cout << "5. Search by Age\n";
	std::cout << "6. Search by Class\n";
	std::cout << "7. Search All\n";
	std::cout << "0. Exit\n";
	printf("Command: ");
}


#include <iostream>

#include "Member.h"
#include "MemberMgr.h"
#include "MemberView.h"

int main()
{
	MemberMgr mgr;
	MemberView view(&mgr);

	while (true)
	{
		MemberView::DisplayMemu();

		int cmd;
		std::cin >> cmd;
		switch (cmd)
		{
			case 1: view.Add(); break;
			case 2: view.Delete(); break;
			case 3: view.Visit(); break;
			case 4: view.SearchByName(); break;
			case 5: view.SearchByAge(); break;
			case 6: view.SearchByClass(); break;
			case 7: view.SearchAll(); break;
			case 0: return 0;
		}
	}
}












