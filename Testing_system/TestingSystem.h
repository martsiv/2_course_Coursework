#pragma once
#include <iostream>
#include <initializer_list>
#include <conio.h>
#include <vector>
#include <map>
#include <iterator>
#include <algorithm>
#include <string>
#include "Statistic.h"
#include "Guest.h"
#include "Test.h"
#include "QuestionManyAnswer.h"
#include "QuestionOneAnswer.h"
#include "QuestionUserAnswer.h"
using namespace std;

const char GUEST_BEGIN[] = "<GUEST>";
const char GUEST_END[] = "<GUEST/>";
const char LOGIN_BEGIN[] = "<LOGIN>";
const char LOGIN_END[] = "<LOGIN/>";
const char PASSWORD_BEGIN[] = "<PASSWORD>";
const char PASSWORD_END[] = "<PASSWORD/>";
const char FIRSTNAME_BEGIN[] = "<FNAME>";
const char FIRSTNAME_END[] = "<FNAME/>";
const char LASTNAME_BEGIN[] = "<LNAME>";
const char LASTNAME_END[] = "<LNAME/>";
const char ADDRESS_BEGIN[] = "<ADDRESS>";
const char ADDRESS_END[] = "<ADDRESS/>";
const char PHONE_BEGIN[] = "<PHONE>";
const char PHONE_END[] = "<PHONE/>";

typedef std::string KeyType;
typedef std::pair<const KeyType, Test> PairTest;
typedef std::pair<const KeyType, Guest> PairGuest;
typedef std::multimap<KeyType, Test> MultimapTests;
typedef std::map<string, Guest> MapGuest;
typedef std::vector<KeyType> VectorKeys;
typedef MultimapTests::iterator TestIterator;
typedef MapGuest::iterator GuestIterator;
typedef std::pair<string, string> LoginPassword;
//insert_iterator<MultimapTests>::container_type;

class TestingSystem
{
	map<string, Guest> guests;
	vector<Statistic> statistic;
	MultimapTests tests;
	VectorKeys vectorKeys;
	string savedTestsFileName = "Tests_List.txt";
	string adminDataFileName = "AdminLogin.txt";
	string guestsDataFileName = "Guests.txt";

	//Supporting methods
	bool ChoiseYesNo(char ifTrue, char ifFasle);
	string encryptDecrypt(string toEncrypt);
	LoginPassword sign_in();
	int verificateNum(int leftRange, int rightRange);

	//System methods
	void RefreshVectorKeys();
	bool CheckAdminDataFile();
	void CreateAdminData();
	void SaveGuestFile();
	bool LoadGuestFile();
	KeyType GetCategoryName();
	void StartNewTest(Guest& guest);
	void ShowTestsInCategory(string categoryName);
	void ShowCategories();
	void ShowCategory();
	void ShowAllTestsInAllCategories();
	void ExportTest();
	int Import();
	void SaveToTestsList(string testname);
	string LoadFromTestsList();
	TestIterator FindTest();
	void AddTest();
	void DeleteTest();
	void AddQuestion();
	void ChangeQuestion();
	//Statistic
	void ShowResultsByUser(FullName fullname, ostream& out);
	void ShowResultsByTest(string testname, ostream& out);
	void ShowResult(ostream& out);
	void ShowResultByCategory(KeyType CategoryName, ostream& out);

	//Guests
	void GuestMode(Guest& guest);
	void AddGuest();
	bool DeleteGuest();
	GuestIterator FindGuest();
	void ChangeGuest();
	
	//Admin 
	void AdminMode();
	void AdminDataControl();
	void TestControl();
	void GuestControl();
	void StatisticControl();
public:
	TestingSystem() {}
	void Run();
};
