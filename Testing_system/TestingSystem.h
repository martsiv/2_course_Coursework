#pragma once
#include <iostream>
#include <initializer_list>
#include <conio.h>
#include <vector>
#include <map>
#include <iterator>
#include <algorithm>
#include <string>
#include "Guest.h"
#include "Test.h"
#include "QuestionManyAnswer.h"
#include "QuestionOneAnswer.h"
#include "QuestionUserAnswer.h"
using namespace std;

typedef std::string KeyType;
typedef std::pair<const KeyType, Test> PairTest;
typedef std::multimap<KeyType, Test> MultimapTests;
typedef std::vector<KeyType> VectorKeys;
typedef MultimapTests::iterator TestIterator;
typedef std::pair<string, string> LoginPassword;

class TestingSystem
{
	map<string, Guest> guests;
	vector<Statistic> statistic;
	MultimapTests tests;
	VectorKeys vectorKeys;
	string savedTestsFileName = "Tests_List.txt";
	string adminDataFileName = "AdminLogin.txt";
	string guestsDataFileName = "Guests.txt";

	bool ChoiseYesNo(char ifTrue, char ifFasle)
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
	void RefreshVectorKeys()
	{
		vectorKeys.clear();
		for (auto i : tests)
			vectorKeys.push_back(i.first);
	}
	void ShowTestsInCategory(string categoryName) const
	{
		int count = 1;
		auto range = tests.equal_range(categoryName);
		for (auto i = range.first; i != range.second; i++)
			cout << count++ << ") " << (*i).second.GetTestName() << endl;
	}
	void ShowCategories() const
	{
		for (auto i : tests)
			cout << i.first << endl;
	}
	void ShowCategory() const
	{
		ShowTestsInCategory(GetCategoryName());
	}
	void ExportTest()
	{
		Test& tmp = (*FindTest()).second;
		string testname = tmp.GetTestName();
		tmp.Export(testname);
		SaveToTestsList(testname);
	}
	void SaveToTestsList(string testname)
	{
		ofstream out(savedTestsFileName, ios::app);
		out << testname << ".txt\n";
		out.close();
	}
	void ExportCategoryList() 
	{
		ofstream out("category_list.txt");
		for (auto i : vectorKeys)
			out << i << " | ";
		out.close();
	}
	TestIterator FindTest()
	{
		KeyType key = GetCategoryName();
		cout << "\n ============= " << key << " ============= \n\n";
		std::pair<TestIterator, TestIterator> range = tests.equal_range(key);
		VectorKeys keys;
		for (TestIterator i = range.first; i != range.second; i++)
		{
			keys.push_back((*i).second.GetTestName());
			cout << keys.size() << ")" << keys.back() << endl;
		}
		cout << "\tEnter test number: ";
		int num = verificateNum(1, keys.size());

		for (int i = 0; i < num - 1; i++)
			range.first++;
		return range.first;
	}
	KeyType GetCategoryName() const	//Takes the category name from a separate vector, for quick access to categories
	{
		
		cout << "===========All categories=========\n\n";
		for (int i = 0; i < vectorKeys.size(); i++)
		{
			cout << i + 1 << ") " << vectorKeys[i] << endl;
		}
		cout << "\tEnter the category number: ";
		int num = verificateNum(1, vectorKeys.size());
		return vectorKeys[num - 1];
	}
	void AddTest()
	{
		string category;
		string testName;
		cout << "Enter category name: ";
		getline(cin, category);
		cout << "Enter test name: ";
		getline(cin, testName);
		TestIterator iterator = tests.insert(PairTest(category, Test(category, testName)));
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
		tests.erase(FindTest());
		RefreshVectorKeys();
	}
	void AddQuestion()
	{
		(*FindTest()).second.AddQuestion();
	}
	void ChangeQuestion()
	{
		Question* tmp_question = *((*FindTest()).second.FindQuestion()); //Problem with this!!!!!
		char ch;
		string tmp;
		cout << "Would you like to change description (y, n)?\t";
		cin.get(ch);
		cin.ignore(255, '\n');
		if (tolower(ch) == 'y')
		{
			cout << "Enter new description: ";
			getline(cin, tmp);
			tmp_question->ChangeDescription(tmp);
		}
		tmp_question->ChangeAnswer();
	}
	string LoadFromTestsList()	//Returns the name of the file with the saved test of the same name
	{
		ifstream in(savedTestsFileName);
		if (!in)
		{
			cerr << "Invalid reading!" << endl;
			return "";
		}
		cout << "Database with names of test files\n";
		int count = 1;
		string tmp;
		while (in)
		{
			in >> tmp;
			cout << count++ << ") " << tmp << endl;
		}
		in.close();
		cout << "Enter number of file(or 0 - to exit):\t";
		int num = verificateNum(0, count);
		if (!num)
			return "";
		in.open(savedTestsFileName);
		for (int i = 0; i < num - 1; i++)
			in >> tmp;
		in.close();
		return tmp;
	}
	int Import()
	{
		// 0 all right
		// 1 file error
		// 2 format data erorr 
		// 3 question format error
		string filename = LoadFromTestsList();
		if (filename == "")
		{
			cout << "Error file name\n";
			return 1;
		}
		ifstream in(filename);
		if (!in)
		{
			cerr << "Invalid reading!" << endl;
			return 1;
		}
		TestIterator iterator;
		string in_category;
		string in_testName;
		string in_description;
		string in_answer;
		vector<string> in_answers;
		int in_numberOfRightAnswer;
		vector<int> in_numbersOfRightAnswer;
		bool b_category = 0;
		bool b_test_name = 0;
		bool b_description = 0;
		bool b_answers = 0;
		bool b_right_answers = 0;
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
			if (strInput == CATEGORY_BEGIN && !b_category)
			{
				b_category = 1;
				while (in >> strInput, strInput != CATEGORY_END)
				{
					in_category += (strInput + " ");
				}
				continue;
			}
			if (strInput == TEST_NAME_BEGIN && !b_test_name)
			{
				b_test_name = 1;
				while (in >> strInput, strInput != TEST_NAME_END)
				{
					in_testName += (strInput + " ");
				}
				continue;
			}
			if (strInput == DESCRIPTION_BEGIN)
			{
				b_description = 1;
				while (in >> strInput, strInput != DESCRIPTION_END)
				{
					in_description += (strInput + " ");
				}
				continue;
			}
			if (b_category && b_test_name)
			{
				TestIterator iterator = tests.insert(PairTest(in_category, Test(in_category, in_testName)));
			}
			if (strInput == QUESTION_USER_ANSWER_BEGIN)
			{
				while (in >> strInput, strInput != QUESTION_USER_ANSWER_END)
				{
					if (strInput == RIGHT_ANSWER_BEGIN)
					{
						b_right_answers = 1;
						in >> strInput;
						in_answer = strInput;
					}
				}
				if (!b_category || !b_test_name || !b_description || !b_right_answers)
				{
					cout << "Error in question format!\n";
					return 3;
				}
				QuestionUserAnswer* q_tmp = new QuestionUserAnswer(in_description, in_answer);
				(*iterator).second.AddQuestion(q_tmp);
				in_answer.clear();
				b_description = 0;
				b_right_answers = 0;
			}
			else if (strInput == QUESTION_ONE_ANSWER_BEGIN)
			{
				while (in >> strInput, strInput != QUESTION_ONE_ANSWER_END)
				{
					if (strInput == ALL_ANSWER_BEGIN)
					{
						b_answers = 1;
						while (in >> strInput, strInput != ALL_ANSWER_END)
						{
							if (strInput == EXAMPLE_ANSWER_BEGIN)
							{
								while (in >> strInput, strInput != EXAMPLE_ANSWER_END)
								{
									in_answer += (strInput + " ");
								}
								in_answers.push_back(in_answer);
								in_answer.clear();
							}
						}
					}
					if (strInput == RIGHT_ANSWER_BEGIN)
					{
						b_right_answers = 1;
						in >> strInput;
						in_numberOfRightAnswer = stoi(strInput);
					}
				}
				if (!b_category || !b_test_name || !b_description || !b_answers || !b_right_answers)
				{
					cout << "Error in question format!\n";
					return 3;
				}
				QuestionOneAnswer* q_tmp = new QuestionOneAnswer(in_description, in_answers, in_numberOfRightAnswer);
				(*iterator).second.AddQuestion(q_tmp);
				in_answer.clear();
				in_answers.clear();
				b_description = 0;
				b_answers = 0;
				b_right_answers = 0;
			}
			else if (strInput == QUESTION_MANY_ANSWER_BEGIN)
			{
				while (in >> strInput, strInput != QUESTION_MANY_ANSWER_END)
				{
					if (strInput == ALL_ANSWER_BEGIN)
					{
						b_answers = 1;
						while (in >> strInput, strInput != ALL_ANSWER_END)
						{
							if (strInput == EXAMPLE_ANSWER_BEGIN)
							{
								while (in >> strInput, strInput != EXAMPLE_ANSWER_END)
								{
									in_answer += (strInput + " ");
								}
								in_answers.push_back(in_answer);
								in_answer.clear();
							}
						}
					}
					if (strInput == RIGHT_ANSWER_BEGIN)
					{
						b_right_answers = 1;
						while (in >> strInput, strInput != RIGHT_ANSWER_END)
						{
							if (strInput == EXAMPLE_ANSWER_BEGIN)
							{
								while (in >> strInput, strInput != EXAMPLE_ANSWER_END)
								{
									in_numbersOfRightAnswer.push_back(stoi(strInput));
								}
							}
						}
					}
				}
				if (!b_category || !b_test_name || !b_description || !b_answers || !b_right_answers)
				{
					cout << "Error in question format!\n";
					return 3;
				}
				QuestionManyAnswer* q_tmp = new QuestionManyAnswer(in_description, in_answers, in_numbersOfRightAnswer);
				(*iterator).second.AddQuestion(q_tmp);
				in_answer.clear();
				in_answers.clear();
				in_numbersOfRightAnswer.clear();
				b_description = 0;
				b_answers = 0;
				b_right_answers = 0;
			}
			in_description.clear();
		}
		in.close();
		RefreshVectorKeys();
		return 0;
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
		return LoginPassword(login, pass);
	}
	string encryptDecrypt(string toEncrypt) {
		char key[3] = { 'K', 'C', 'Q' }; //Any chars will work, in an array of any size
		string output = toEncrypt;

		for (int i = 0; i < toEncrypt.size(); i++)
			output[i] = toEncrypt[i] ^ key[i % (sizeof(key) / sizeof(char))];

		return output;
	}

	void AddGuest(string login, string password, string fullname, string address, string phone)
	{

	}
	bool DeleteGuest(string login, string password)
	{

	}
	
	//Admin menu
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
				break;
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
		enum class Menu { AddTest = 1, AddQuestion, ChangeQuestion, ImportTest, ExportTest, Return };
		int menu = 0;
		while (menu != 6)
		{
			cout << "================ Test control ===================\n";
			cout << "1 - Add test\n"
				<< "2 - Add question\n"
				<< "3 - Change question\n"
				<< "4 - Import test\n"
				<< "5 - Export test\n"
				<< "6 - Return\n";
			menu = verificateNum(1, 6);
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
			case Menu::Return:
				break;
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
			case Menu::AddGuest:
				break;
			case Menu::DeleteGuest:StartNewTest();
				break;
			case Menu::ChangeGuest:
				break;
			case Menu::Return:
				break;
			}
		}
	}
	void StatisticControl()
	{
		enum class Menu { ShowTotalResult = 1, ShowResultsByCategory, ShowResultsByTest, ShowResultsByUser, Return };
		int menu = 0;
		while (menu != 5)
		{
			cout << "================ Statistic control ===================\n";
			cout << "1 - Show total result\n"
				<< "2 - Show results by category\n"
				<< "3 - Show results by test\n"
				<< "4 - Show results by Guest\n"
				<< "5 - Return\n";
			menu = verificateNum(1, 4);
			switch (Menu(menu))
			{
			case Menu::ShowTotalResult:ShowResult();
				break;
			case Menu::ShowResultsByCategory:ShowCategories();
				break;
			case Menu::ShowResultsByTest:ShowResultsByTest();
				break;
			case Menu::ShowResultsByUser:ShowResultsByUser();
				break;
			case Menu::Return:
				break;
			}
		}
	}
	//Guest menu
	void GuestMode()
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
				break;
			case Menu::StartNewTest:StartNewTest();
				break;
			case Menu::ShowStatistic:
				//but find User First
				ShowResultsByUser();
				break;
			case Menu::Return:
				break;
			}
		}
	}
	void ShowResult() {}
	//Mb add arguments
	void ShowResultsByCategory(){}
	void ShowResultsByTest() {}
	void ShowResultsByUser() {}

	void StartNewTest() {}

public:
	TestingSystem() {}
	void Run()
	{
		if (!CheckAdminDataFile())
		{
			cout << "This is your first login, you need to enter an administrator login and password\n\n";
			CreateAdminData();
		}
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
				while (true)
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
						AdminMode();
				} 
				in.close();
			}
			if (choise == 2)	//Guest
			{

			}
			if (choise == 3)	//Exit
			{
				cout << "Goodbye!\n";
				return;
			}
		} while (choise != 3);
	}
};
