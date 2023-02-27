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
	bool ChoiseYesNo(char ifTrue = 'y', char ifFasle = 'n')
	{
		char choise{};
		while (true)
		{
			cin >> choise;
			cin.clear();
			cin.ignore(255, '\n');
			if (toupper(choise) == toupper(ifTrue))
				return true;
			else if (toupper(choise) == toupper(ifFasle))
				return false;
		}
	}
	string encryptDecrypt(string toEncrypt) {
		char key[3] = { 'K', 'C', 'Q' }; //Any chars will work, in an array of any size
		string output = toEncrypt;

		for (int i = 0; i < toEncrypt.size(); i++)
			output[i] = toEncrypt[i] ^ key[i % (sizeof(key) / sizeof(char))];

		return output;
	}
	LoginPassword sign_in()
	{
		std::string       login;
		std::vector<char> password;

		char c;

		std::cout << "Enter login: ";
		std::cin >> login;
		std::cout << "Enter password: ";
		while ((c = _getch()) != '\r')
		{
			password.push_back(c);
			_putch('*');
		}
		std::cout << std::endl;
		string pass(password.begin(), password.end());
		cin.ignore(256, '\n');
		return LoginPassword(login, pass);
	}

	//System methods
	void RefreshVectorKeys()
	{
		vectorKeys.clear();
		for (auto i : tests)
		{
			if (find(vectorKeys.begin(), vectorKeys.end(), i.first) == vectorKeys.end())
				vectorKeys.push_back(i.first);
		}
	}
	bool CheckAdminDataFile()
	{
		ifstream in(adminDataFileName);
		string tmp;
		if (!in)
			return 0;
		if (!(in >> tmp))
			return 0;
		in.close();
		return 1;
	}
	void CreateAdminData()
	{
		LoginPassword loginPassword = sign_in();
		ofstream out(adminDataFileName);
		out << loginPassword.first << '\n';
		out << encryptDecrypt(loginPassword.second);
		out.close();
	}
	void SaveGuestFile()
	{
		ofstream out(guestsDataFileName);
		for (auto i : guests)
		{
			out << GUEST_BEGIN << ' ';
			out << LOGIN_BEGIN << ' ' << i.first << ' ' << LOGIN_END << ' ';
			out << PASSWORD_BEGIN << ' ' << i.second.GetPassword() << ' ' << PASSWORD_END << ' ';
			out << FIRSTNAME_BEGIN << ' ' << i.second.GetFullname().first << ' ' << FIRSTNAME_END << ' ';
			out << LASTNAME_BEGIN << ' ' << i.second.GetFullname().second << ' ' << LASTNAME_END << ' ';
			out << ADDRESS_BEGIN << ' ' << i.second.GetAddress() << ' ' << ADDRESS_END << ' ';
			out << PHONE_BEGIN << ' ' << i.second.GetPhone() << ' ' << PHONE_END << ' ';
			out << GUEST_END << "\n\n";
		}
		out.close();
	}
	bool LoadGuestFile()
	{
		ifstream in(guestsDataFileName);
		if (!in)
			return 1;
		string strInput;
		while (in >> strInput)
		{
			if (strInput == GUEST_BEGIN)
			{
				string login;
				string password;
				string firstname;
				string lastname;
				string address;
				string phone;
				bool b_login = 0;
				bool b_password = 0;
				bool b_firstname = 0;
				bool b_lastname = 0;
				bool b_address = 0;
				bool b_phone = 0;
				while (in >> strInput, strInput != GUEST_END)
				{
					if (strInput == LOGIN_BEGIN)
					{
						b_login = 1;
						while (in >> strInput && strInput != LOGIN_END)
							login += strInput;
					}
					else if (strInput == PASSWORD_BEGIN)
					{
						b_password = 1;
						while (in >> strInput && strInput != PASSWORD_END)
							password += strInput;
					}
					
					else if (strInput == FIRSTNAME_BEGIN)
					{
						b_firstname = 1;
						while (in >> strInput && strInput != FIRSTNAME_END)
							firstname += strInput;
					}
					else if (strInput == LASTNAME_BEGIN)
					{
						b_lastname = 1;
						while (in >> strInput && strInput != LASTNAME_END)
							lastname += strInput;
					}
					else if (strInput == ADDRESS_BEGIN)
					{
						b_address = 1;
						while (in >> strInput && strInput != ADDRESS_END)
							address += strInput;
					}
					else if (strInput == PHONE_BEGIN)
					{
						b_phone = 1;
						while (in >> strInput && strInput != PHONE_END)
							phone += strInput;
					}
				}
				if (b_login && b_password && b_firstname && b_lastname && b_address && b_phone)
					guests.emplace(PairGuest(login, Guest(login, password, firstname, lastname, address, phone)));
			}
		}
		in.close();
		return 0;
	}

	//Tests
	//void ExportCategoryList() 
	//{
	//	ofstream out("category_list.txt");
	//	for (auto i : vectorKeys)
	//		out << i << " | ";
	//	out.close();
	//}
	KeyType GetCategoryName() 	//Takes the category name from a separate vector, for quick access to categories
	{
		
		cout << "===========All categories=========\n\n";
		for (int i = 0; i < vectorKeys.size(); i++)
		{
			cout << i + 1 << ") " << vectorKeys[i] << endl;
		}
		cout << "\tEnter the category number or 0 to return: ";
		int num = verificateNum(0, vectorKeys.size());
		if (!num)
			return " ";
		return vectorKeys[num - 1];
	}
	void StartNewTest(Guest& guest) 
	{
		TestIterator testIterator = FindTest();
		if (testIterator == tests.end())
			return;
		float result = (*testIterator).second.StartTest();
		statistic.push_back(Statistic(guest.GetFullname(), (*testIterator).second.GetCategory(), (*testIterator).second.GetTestName(), (*testIterator).second.GetMaxPoint(), result));
		cout << statistic.back() << endl;
	}
	void ShowTestsInCategory(string categoryName) 
	{
		int count = 1;
		auto range = tests.equal_range(categoryName);
		for (auto i = range.first; i != range.second; i++)
			cout << count++ << ") " << (*i).second.GetTestName() << endl;
	}
	void ShowCategories() 
	{
		for (auto i : vectorKeys)
			cout << i << endl;
	}
	void ShowCategory() 
	{
		ShowTestsInCategory(GetCategoryName());
	}
	void ShowAllTestsInAllCategories()
	{
		if (tests.empty())
		{
			cout << "There are no tests\n";
			return;
		}
		KeyType category = (*tests.begin()).first;
		cout << "\tCategory: " << category << endl;
		ShowTestsInCategory(category);
		for (auto i : tests)
		{
			if (category != i.first)
			{
				category = i.first;
				cout << "\tCategory: " << category << endl;
				ShowTestsInCategory(category);
			}
		}
		system("PAUSE");
	}
	void ExportTest() 
	{
		TestIterator tmp = FindTest();
		if (tmp == tests.end())
			return;
		string filename = (*tmp).second.GetTestName();
		(*tmp).second.Export(filename);
		SaveToTestsList(filename);
	}

	int Import()
	{
		// 0 all right
		// 1 file error
		// 2 format data erorr 
		// 3 question format error
		string filename = LoadFromTestsList();
		if (filename == " ")
		{
			cout << "Error file name\n";
			return 1;
		}
		ifstream in(filename + ".txt");
		if (!in)
		{
			cerr << "Invalid reading!" << endl;
			return 1;
		}
		string in_category;
		string strInput;
		in >> strInput;
		if (strInput != TEST_BEGIN)
		{
			cout << "Eror data!\n";
			return 2;
		}
		while (in)
		{
			in >> strInput;
			if (strInput == TEST_END)
				break;
			if (strInput == CATEGORY_BEGIN)
			{
				while (in >> strInput, strInput != CATEGORY_END)
				{
					in_category += (strInput + " ");
				}
				break;
			}
		}
		in.close();
		tests.emplace(PairTest{ in_category, Test(filename + ".txt")});
		////Test tmp(filename);
		//ifstream in(filename + ".txt");
		//if (!in)
		//{
		//	cerr << "Invalid reading!" << endl;
		//	return 1;
		//}
		//TestIterator iterator;
		//string in_category;
		//string in_testName;
		//string in_description;
		//string in_answer;
		//vector<string> in_answers;
		//int in_numberOfRightAnswer;
		//vector<int> in_numbersOfRightAnswer;
		//bool b_category = 0;
		//bool b_test_name = 0;
		//bool b_description = 0;
		//bool b_answers = 0;
		//bool b_right_answers = 0;
		//string strInput;
		//in >> strInput;
		//if (strInput != TEST_BEGIN)
		//{
		//	cout << "Eror data!\n";
		//	return 2;
		//}
		//while (in)
		//{
		//	in >> strInput;
		//	if (strInput == TEST_END)
		//		break;
		//	if (strInput == CATEGORY_BEGIN && !b_category)
		//	{
		//		b_category = 1;
		//		while (in >> strInput, strInput != CATEGORY_END)
		//		{
		//			in_category += (strInput + " ");
		//		}
		//		continue;
		//	}
		//	if (strInput == TEST_NAME_BEGIN && !b_test_name)
		//	{
		//		b_test_name = 1;
		//		while (in >> strInput, strInput != TEST_NAME_END)
		//		{
		//			in_testName += (strInput + " ");
		//		}
		//		continue;
		//	}
		//	if (strInput == DESCRIPTION_BEGIN)
		//	{
		//		b_description = 1;
		//		while (in >> strInput, strInput != DESCRIPTION_END)
		//		{
		//			in_description += (strInput + " ");
		//		}
		//		continue;
		//	}
		//	if (b_category && b_test_name)
		//	{
		//		Test tmp_test(in_category, in_testName);
		//		TestIterator iterator = tests.insert(PairTest( in_category, tmp_test ));
		//	}
		//	if (strInput == QUESTION_USER_ANSWER_BEGIN)
		//	{
		//		while (in >> strInput, strInput != QUESTION_USER_ANSWER_END)
		//		{
		//			if (strInput == RIGHT_ANSWER_BEGIN)
		//			{
		//				b_right_answers = 1;
		//				in >> strInput;
		//				in_answer = strInput;
		//			}
		//		}
		//		if (!b_category || !b_test_name || !b_description || !b_right_answers)
		//		{
		//			cout << "Error in question format!\n";
		//			return 3;
		//		}
		//		shared_ptr<QuestionUserAnswer> q_tmp(new QuestionUserAnswer(in_description, in_answer));
		//		(*iterator).second.AddQuestion(q_tmp);
		//		in_answer.clear(); 
		//		b_description = 0;
		//		b_right_answers = 0;
		//	}
		//	else if (strInput == QUESTION_ONE_ANSWER_BEGIN)
		//	{
		//		while (in >> strInput, strInput != QUESTION_ONE_ANSWER_END)
		//		{
		//			if (strInput == ALL_ANSWER_BEGIN)
		//			{
		//				b_answers = 1;
		//				while (in >> strInput, strInput != ALL_ANSWER_END)
		//				{
		//					if (strInput == EXAMPLE_ANSWER_BEGIN)
		//					{
		//						while (in >> strInput, strInput != EXAMPLE_ANSWER_END)
		//						{
		//							in_answer += (strInput + " ");
		//						}
		//						in_answers.push_back(in_answer);
		//						in_answer.clear();
		//					}
		//				}
		//			}
		//			if (strInput == RIGHT_ANSWER_BEGIN)
		//			{
		//				b_right_answers = 1;
		//				in >> strInput;
		//				in_numberOfRightAnswer = stoi(strInput);
		//			}
		//		}
		//		if (!b_category || !b_test_name || !b_description || !b_answers || !b_right_answers)
		//		{
		//			cout << "Error in question format!\n";
		//			return 3;
		//		}
		//		shared_ptr<QuestionOneAnswer> q_tmp(new QuestionOneAnswer(in_description, in_answers, in_numberOfRightAnswer));
		//		(*iterator).second.AddQuestion(q_tmp);
		//		in_answer.clear();
		//		in_answers.clear();
		//		b_description = 0;
		//		b_answers = 0;
		//		b_right_answers = 0;
		//	}
		//	else if (strInput == QUESTION_MANY_ANSWER_BEGIN)
		//	{
		//		while (in >> strInput, strInput != QUESTION_MANY_ANSWER_END)
		//		{
		//			if (strInput == ALL_ANSWER_BEGIN)
		//			{
		//				b_answers = 1;
		//				while (in >> strInput, strInput != ALL_ANSWER_END)
		//				{
		//					if (strInput == EXAMPLE_ANSWER_BEGIN)
		//					{
		//						while (in >> strInput, strInput != EXAMPLE_ANSWER_END)
		//						{
		//							in_answer += (strInput + " ");
		//						}
		//						in_answers.push_back(in_answer);
		//						in_answer.clear();
		//					}
		//				}
		//			}
		//			if (strInput == RIGHT_ANSWER_BEGIN)
		//			{
		//				b_right_answers = 1;
		//				while (in >> strInput, strInput != RIGHT_ANSWER_END)
		//				{
		//					if (strInput == EXAMPLE_ANSWER_BEGIN)
		//					{
		//						while (in >> strInput, strInput != EXAMPLE_ANSWER_END)
		//						{
		//							in_numbersOfRightAnswer.push_back(stoi(strInput));
		//						}
		//					}
		//				}
		//			}
		//		}
		//		if (!b_category || !b_test_name || !b_description || !b_answers || !b_right_answers)
		//		{
		//			cout << "Error in question format!\n";
		//			return 3;
		//		}
		//		shared_ptr<QuestionManyAnswer> q_tmp(new QuestionManyAnswer(in_description, in_answers, in_numbersOfRightAnswer));
		//		(*iterator).second.AddQuestion(q_tmp);
		//		in_answer.clear();
		//		in_answers.clear();
		//		in_numbersOfRightAnswer.clear();
		//		b_description = 0;
		//		b_answers = 0;
		//		b_right_answers = 0;
		//	}
		//	in_description.clear();
		//}
		//in.close();
		RefreshVectorKeys();
		return 0;
	}

	void SaveToTestsList(string testname)
	{
		ofstream out(savedTestsFileName, ios::app);
		out << testname << " |\n";
		out.close();
	}

	string LoadFromTestsList()	//Returns the name of the file with the saved test of the same name
	{
		ifstream in(savedTestsFileName);
		if (!in)
		{
			cerr << "Invalid reading!" << endl;
			return " ";
		}
		cout << "Database with names of test files\n";
		int count = 1;
		vector<string> testsNames;
		string tmpName;
		string strInput;
		while (in >> strInput)
		{
			tmpName = strInput;
			while (in >> strInput && strInput != "|")
			{
				tmpName += " " + strInput;
			}
			testsNames.push_back(tmpName);
			cout << count++ << ") " << testsNames.back() << endl;
		}
		in.close();
		cout << "Enter number of file(or 0 - to exit):\t";
		int num = verificateNum(0, count);
		if (!num)
			return " ";
		//in.open(savedTestsFileName);
		//for (int i = 0; i < num - 1; i++)
		//	in >> tmp;
		//in.close();
		return testsNames[num - 1];
	}

	TestIterator FindTest()
	{
		KeyType key = GetCategoryName();
		if (key == " ")
			return tests.end();
		cout << "\n ============= " << key << " ============= \n\n";
		std::pair<TestIterator, TestIterator> range = tests.equal_range(key);
		VectorKeys keys;
		for (TestIterator i = range.first; i != range.second; i++)
		{
			keys.push_back((*i).second.GetTestName());
			cout << keys.size() << ")" << keys.back() << endl;
		}
		cout << "\tEnter test number, or 0 to return: ";
		int num = verificateNum(0, keys.size());
		if (!num)
			return tests.end();
		for (int i = 0; i < num - 1; i++)
			range.first++;
		return range.first;
	}

	void AddTest()
	{
		string category;
		string testName;
		cout << "Enter category name: ";
		getline(cin, category);
		cout << "Enter test name: ";
		getline(cin, testName);
		//Test tmp_test(category, testName);
		
		TestIterator iterator = tests.emplace(category, Test(category, testName));
		char ch;
		do
		{
			(*iterator).second.AddQuestion();
			cout << "Would you like to add another question? (y, n)\t";
			cin.get(ch);
			cin.ignore(256, '\n');
		} while (tolower(ch) != 'n');
		RefreshVectorKeys();
	}
	void DeleteTest()
	{
		TestIterator testIterator = FindTest();
		if (testIterator == tests.end())
			return;
		tests.erase(testIterator);
		RefreshVectorKeys();
	}
	void AddQuestion()
	{
		TestIterator testIterator = FindTest();
		if (testIterator == tests.end())
			return;
		(*testIterator).second.AddQuestion();
	}
	void ChangeQuestion()
	{
		TestIterator testIterator = FindTest();
		if (testIterator == tests.end())
			return;
		QuestionIterator questionIterator = (*testIterator).second.FindQuestion();
		if (!(*testIterator).second.IsOkQuestionIterator(questionIterator))
			return;
		
		char ch;
		string tmp;
		cout << "Would you like to change description (y, n)?\t";
		cin.get(ch);
		cin.ignore(255, '\n');
		if (tolower(ch) == 'y')
		{
			cout << "Enter new description: ";
			getline(cin, tmp);
			(*questionIterator)->ChangeDescription(tmp);
		}
		(*questionIterator)->ChangeAnswer();
	}


	//Statistic
	void ShowResultsByUser(FullName fullname, ostream& out = std::cout)
	{
		sort(statistic.begin(), statistic.end());
		out << " ========= " << fullname.first << ' ' << fullname.second << " ========= \n";
		for (auto i : statistic)
		{
			if (i.fullname == fullname)
			{
				out << "--------------== " << i.category << " ==--------------\n";
				out << "\t" << i.testName << '\n';
				out << "Number of correct answers: " << i.GetTotalScore() <<  '/' << i.GetMaxScore() << '\n';
				out << "Percentage of correct answers:" << i.GetPercent() << '\n';
				out << "Grade: " << i.GetGrade() << "\n\n";
			}
		}
	}
	void ShowResultsByTest(string testname, ostream& out = std::cout)
	{
		sort(statistic.begin(), statistic.end(), predicateComparisonByTestName);
		out << " ========= " << testname << " ========= \n\n";
		for (auto i : statistic)
		{
			if (i.GetTestName() == testname)
			{
				out << "Student: " << i.GetFullName().first << ' ' << i.GetFullName().second << '\n';
				out << "Number of correct answers: " << i.GetTotalScore() << '/' << i.GetMaxScore() << '\n';
				out << "Percentage of correct answers:" << i.GetPercent() << '\n';
				out << "Grade: " << i.GetGrade() << "\n\n";
			}
		}
	}
	void ShowResult(ostream& out = std::cout) 
	{
		sort(statistic.begin(), statistic.end(), predicateComparisonByCategory);
		out << " ================== General statistics ===============\n\n";
		for (auto i : statistic)
		{
			out << "--------------== " << i.category << " ==--------------\n";
			out << "\t" << i.testName << '\n';
			out << "Student: " << i.GetFullName().first << ' ' << i.GetFullName().second << '\n';
			out << "Number of correct answers: " << i.GetTotalScore() << '/' << i.GetMaxScore() << '\n';
			out << "Percentage of correct answers:" << i.GetPercent() << '\n';
			out << "Grade: " << i.GetGrade() << "\n\n";
		}
	}

	void ShowResultByCategory(KeyType CategoryName, ostream& out = std::cout)           //////////// треба якось щоб він приймав категорію типу назву категорії або в середині себе шукав категорію
	{
		sort(statistic.begin(), statistic.end(), predicateComparisonByCategory);
		out << " ================== " << CategoryName << " ============== = \n\n";
		for (auto i : statistic)
		{
			if (i.GetCategory() == CategoryName)
			out << "\t" << i.testName << '\n';
			out << "Student: " << i.GetFullName().first << ' ' << i.GetFullName().second << '\n';
			out << "Number of correct answers: " << i.GetTotalScore() << '/' << i.GetMaxScore() << '\n';
			out << "Percentage of correct answers:" << i.GetPercent() << '\n';
			out << "Grade: " << i.GetGrade() << "\n\n";
		}
	}

	//Guests
	void GuestMode(Guest& guest)
	{
		enum class Menu { ShowAllTests = 1, StartNewTest, ShowStatistic, Return };
		int menu = 0;
		while (menu != 4)
		{
			cout << "================ Guest mode ===================\n";
			cout << "1 - Show all tests\n"
				<< "2 - Start new test\n"
				<< "3 - Show statistic\n"
				<< "4 - Return\n";
			menu = verificateNum(1, 4);
			switch (Menu(menu))
			{
			case Menu::ShowAllTests:
				ShowAllTestsInAllCategories();
				system("PAUSE");
				break;
			case Menu::StartNewTest:
				StartNewTest(guest);
				system("PAUSE");
				break;
			case Menu::ShowStatistic:
				ShowResultsByUser(guest.GetFullname());
				system("PAUSE");
				break;
			case Menu::Return:
				return;
			}
		}
	}
	void AddGuest()
	{
		string firstname;
		string lastname;
		string address;
		string phone;
		cout << "======== Adding a new guest =========\n";
		do
		{
			LoginPassword newLoginPassword = sign_in();
			if (guests.find(newLoginPassword.first) != guests.end())
			{
				cout << "Such a login already exists, repeat with other data(y) or return(n)?\t";
				continue;
			}
			else
			{
				do
				{
					cout << "Enter firstname: ";
					getline(cin, firstname);
					cout << "Enter lastname: ";
					getline(cin, lastname);
					cout << "Enter address: ";
					getline(cin, address);
					cout << "Enter phone: ";
					getline(cin, phone);
					cout << "\nCheck your details\n";
					cout << firstname << " " << lastname << endl;
					cout << "Address: " << address << endl;
					cout << "Phine: " << phone << endl;
					cout << "Is everything ok(y) or start over(n)? ";
				} while (ChoiseYesNo('n', 'y'));
				newLoginPassword.second = encryptDecrypt(newLoginPassword.second);
				guests.emplace(PairGuest(newLoginPassword.first, Guest(newLoginPassword.first, newLoginPassword.second, firstname, lastname, address, phone)));
				SaveGuestFile();
				break;
			}
		} while (ChoiseYesNo('y', 'n'));
	}
	bool DeleteGuest()
	{
		GuestIterator guestIterator = FindGuest();
		if (guestIterator == guests.end())
			return 0;
		guests.erase(guestIterator);
		SaveGuestFile();
		return 1;
	}
	GuestIterator FindGuest()
	{
		cout << " ================== Find Guest =================\n";
		int count = 1;
		vector<pair<KeyType, FullName>> loginAndFullnames;
		for (auto i : guests)
		{
			loginAndFullnames.push_back({ i.first, i.second.GetFullname() });
			cout << count++ << ") " << loginAndFullnames.back().second.first << ' ' << loginAndFullnames.back().second.second << endl;
		}
		cout << "Enter number of guest or 0 to return: ";
		int result = verificateNum(0, loginAndFullnames.size());
		if (!result)
			return guests.end();
		return guests.find(loginAndFullnames[result - 1].first);
	}
	void ChangeGuest()
	{
		GuestIterator guestIterator = FindGuest();
		if (guestIterator == guests.end())
			return;
		LoginPassword newLoginPassword;
		string firstname;
		string lastname;
		string address;
		string phone;
		bool b_newLoginPassword = 0;
		bool b_name = 0;
		bool b_address = 0;
		bool b_phone = 0;

			cout << "======== Changing guest data =========\n";
			(*guestIterator).second.Show();
			cout << "Do you want to change your login and password?(y, n) ";
			if (ChoiseYesNo())
			{
				do
				{
					newLoginPassword = sign_in();
					if (guests.find(newLoginPassword.first) != guests.end())
					{
						cout << "Such a login already exists, repeat with other data(y) or return(n)?\t";
						continue;
					}
					b_newLoginPassword = 1;
					break;
				} while (ChoiseYesNo());
			}

			cout << "Do you want to change name?(y, n) ";
			if (ChoiseYesNo())
			{
				b_name = 1;
				cout << "Enter firstname: ";
				getline(cin, firstname);
				cout << "Enter lastname: ";
				getline(cin, lastname);
			}

			cout << "Do you want to change the address?(y, n) ";
			if (ChoiseYesNo())
			{
				b_address = 1;
				cout << "Enter address: ";
				getline(cin, address);
			}

			cout << "Do you want to change the phone?(y, n) ";
			if (ChoiseYesNo())
			{
				b_phone = 1;
				cout << "Enter phone: ";
				getline(cin, phone);
			}

			cout << " --------- New data ----------\n";
			if (b_newLoginPassword)
				cout << newLoginPassword.first << endl;
			if (b_name)
				cout << firstname << " " << lastname << endl;
			if (b_address)
				cout << "Address: " << address << endl;
			if (b_phone)
				cout << "Phone: " << phone << endl;
			cout << "\nDo you want to save your changes?(y, n) ";

		if (ChoiseYesNo());
		{
			if (b_newLoginPassword)
			{
				newLoginPassword.second = encryptDecrypt(newLoginPassword.second);
				(*guestIterator).second.SetLogin(newLoginPassword.first);
				(*guestIterator).second.SetPassword(newLoginPassword.second);
			}
			if (b_name)
				(*guestIterator).second.SetFullname(FullName(firstname, lastname));
			if (b_address)
				(*guestIterator).second.SetAddress(address);
			if (b_phone)
				(*guestIterator).second.SetPhone(phone);
			SaveGuestFile();
		}
	}
	
	//Admin 
	void AdminMode()
	{
		enum class Menu { AdminDataControl = 1, TestControl, GuestControl, StatisticControl, Return };
		int menu = 0;
		while (menu != 5)
		{
			cout << "================ Admin mode ===================\n";
			cout << "1 - Admin data control\n"
				<< "2 - Tests control\n"
				<< "3 - Guests control\n"
				<< "4 - Statistic control\n"
				<< "5 - Return\n";
			menu = verificateNum(1, 5);
			switch (Menu(menu))
			{
			case Menu::AdminDataControl:AdminDataControl();
				break;
			case Menu::TestControl:TestControl();
				break;
			case Menu::GuestControl:GuestControl();
				break;
			case Menu::StatisticControl:StatisticControl();
				break;
			case Menu::Return:
				return;
			}
		}
	}
	void AdminDataControl()
	{
		cout << "================ Admin Data Control ===================\n";
		cout << "Change login and password(y) or return(n)\n";
		if (ChoiseYesNo('y', 'n'))
			CreateAdminData();
	}
	void TestControl()
	{
		enum class Menu { AddTest = 1, AddQuestion, ChangeQuestion, ImportTest, ExportTest, ShowAllTests, Return };
		int menu = 0;
		while (menu != 7)
		{
			cout << "================ Test control ===================\n";
			cout << "1 - Add test\n"
				<< "2 - Add question\n"
				<< "3 - Change question\n"
				<< "4 - Import test\n"
				<< "5 - Export test\n"
				<< "6 - Show all tests\n"
				<< "7 - Return\n";
			menu = verificateNum(1, 7);
			switch (Menu(menu))
			{
			case Menu::AddTest:AddTest();
				break;
			case Menu::AddQuestion:AddQuestion();
				break;
			case Menu::ChangeQuestion:ChangeQuestion();
				break;
			case Menu::ImportTest:Import();
				break;
			case Menu::ExportTest:ExportTest();
				break;
			case Menu::ShowAllTests:ShowAllTestsInAllCategories();
				break;
			case Menu::Return:
				return;
			}
		}
	}
	void GuestControl()
	{
		enum class Menu { AddGuest = 1, DeleteGuest, ChangeGuest, Return };
		int menu = 0;
		while (menu != 4)
		{
			cout << "================ Guest control ===================\n";
			cout << "1 - Add Guest\n"
				<< "2 - Delete Guest\n"
				<< "3 - Change Guest\n"
				<< "4 - Return\n";
			menu = verificateNum(1, 4);
			switch (Menu(menu))
			{
			case Menu::AddGuest:AddGuest();
				break;
			case Menu::DeleteGuest:DeleteGuest();
				break;
			case Menu::ChangeGuest:ChangeGuest();
				break;
			case Menu::Return:
				return;
			}
		}
	}
	void StatisticControl()
	{
		enum class Menu { ShowTotalResult = 1, ShowResultsByCategory, ShowResultsByTest, ShowResultsByUser, Return };
		int menu = 0;
		KeyType category;
		TestIterator testIterator;
		GuestIterator guestIterator;
		string filename;
		while (menu != 5)
		{
			cout << "================ Statistic control ===================\n";
			cout << "1 - Show total result\n"
				<< "2 - Show results by category\n"
				<< "3 - Show results by test\n"
				<< "4 - Show results by Guest\n"
				<< "5 - Return\n";
			menu = verificateNum(1, 5);
			switch (Menu(menu))
			{
			case Menu::ShowTotalResult:
				
				ShowResult();
				if (!statistic.empty())
				{
					cout << "Save result to file?(y, n) ";
					if (ChoiseYesNo())
					{
						cout << "Enter the file name: ";
						cin >> filename;
						cin.clear();
						cin.ignore(256, '\n');
						ofstream fout(filename + ".txt");
						ShowResult(fout);
					}
				}
				else
				{
					cout << "No statistics found!\n";
					system("PAUSE");
				}

				break;
			case Menu::ShowResultsByCategory:
				category = GetCategoryName();
				if (category != " ")
				{
					ShowResultByCategory(category);
					cout << "Save result to file?(y, n) ";
					if (ChoiseYesNo())
					{
						cout << "Enter the file name: ";
						cin >> filename;
						cin.clear();
						cin.ignore(256, '\n');
						ofstream fout(filename + ".txt");
						ShowResultByCategory(category, fout);
					}
				}
				else
				{
					cout << "No statistics found!\n";
					system("PAUSE");
				}
				break;
			case Menu::ShowResultsByTest:
				testIterator = FindTest();
				if (testIterator != tests.end())
				{
					ShowResultsByTest((*testIterator).second.GetTestName());
					cout << "Save result to file?(y, n) ";
					if (ChoiseYesNo())
					{
						cout << "Enter the file name: ";
						cin >> filename;
						cin.clear();
						cin.ignore(256, '\n');
						ofstream fout(filename + ".txt");
						ShowResultsByTest((*testIterator).second.GetTestName(), fout);
					}
				}
				else
				{
					cout << "No statistics found!\n";
					system("PAUSE");
				}
				break;
			case Menu::ShowResultsByUser:
				guestIterator = FindGuest();
				if (guestIterator != guests.end())
				{
					ShowResultsByUser((*guestIterator).second.GetFullname());
					cout << "Save result to file?(y, n) ";
					if (ChoiseYesNo())
					{
						cout << "Enter the file name: ";
						cin >> filename;
						cin.clear();
						cin.ignore(256, '\n');
						ofstream fout(filename + ".txt");
						ShowResultsByUser((*guestIterator).second.GetFullname(), fout);
					}
				}
				else
				{
					cout << "No statistics found!\n";
					system("PAUSE");
				}
				break;
			case Menu::Return:
				return;
			}
		}
	}

public:
	TestingSystem() {}
	void Run()
	{
		if (!CheckAdminDataFile())
		{
			cout << "This is your first login, you need to enter an administrator login and password\n\n";
			CreateAdminData();
		}
		LoadGuestFile();
		int choise = 0;
		do
		{
			cout << "Sign in as\n"
				<< "\t1 - Admin\n"
				<< "\t2 - Guest\n"
				<< "\t3 - Exit\n";
			choise = verificateNum(1, 3);
			if (choise == 1)	//Admin
			{
				cout << "\tLogin to the admin panel\n";
				ifstream in(adminDataFileName);
				string login;
				string password;
				in >> login;
				in >> password;
				bool success_login = 0;
				while (!success_login)
				{
					LoginPassword loginPassword = sign_in();
					if (login != loginPassword.first)
					{
						cout << "The login is incorrect!\n";
						cout << "Enter again(y) or exit(n)? ";
						if (ChoiseYesNo('y', 'n'))
							continue;
						else
							break;
					}
					if (password != encryptDecrypt(loginPassword.second))
					{
						cout << "The password is incorrect!\n";
						cout << "Enter again(y) or exit(n)? ";
						if (ChoiseYesNo('y', 'n'))
							continue;
						else
							break;
					}
					else
					{
						AdminMode();
						success_login = 1;
					}
				} 
				in.close();
			}
			if (choise == 2)	//Guest
			{
				cout << "1 - Sign in\n"
					<< "2 - Login\n"
					<< "3 - Return\n";
				choise = verificateNum(1, 3);
				if (choise == 1)
					AddGuest();
				else if (choise == 3)
					continue;
				else
				{
					cout << "\n========== Login to the guest menu ==========\n";
					ifstream in(guestsDataFileName);

					bool success_login = 0;
					string str_in;
					bool found_login = 0;
					while (!success_login)
					{
						LoginPassword loginPassword = sign_in();
						
						GuestIterator guestIterator = guests.find(loginPassword.first);
						if (guestIterator == guests.end())
						{
							cout << "The login is incorrect!\n";
							cout << "Enter again(y) or exit(n)? ";
							if (ChoiseYesNo('y', 'n'))
								continue;
							else
								break;
						}
						if (encryptDecrypt(loginPassword.first) == (*guestIterator).second.GetPassword())
						{
							success_login = 1;
							GuestMode((*guestIterator).second);
						}
				
					}
					in.close();
				}
			}
			if (choise == 3)	//Exit
			{
				cout << "Goodbye!\n";
				return;
			}
		} while (choise != 3);
	}
};
