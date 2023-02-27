#pragma once
#include <iostream>
#include <initializer_list>
#include <vector>
#include <map>
#include <iterator>
#include <algorithm>
#include <string>
using namespace std;

typedef std::pair<string, string> FullName;

class Guest
{
	string login;
	string password;
	string firstname;
	string lastname;
	string address;
	string phone;
public:
	Guest(string login, string password, string firstname, string lastname, string address, string phone)
		: login(login), password(password), firstname(firstname), lastname(lastname), address(address), phone(phone) {}
	~Guest() { }
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
	void Show() const
	{
		cout << firstname << " " << lastname << endl;
		cout << "Address: " << address << endl;
		cout << "Phone: " << phone << endl;
	}
	FullName GetFullname() const
	{
		return FullName(firstname, lastname);
	}
	string GetPassword() const { return password; }
	string GetAddress() const
	{
		return address;
	}
	string GetPhone() const
	{
		return phone;
	}
	void SetLogin(string login) { this->login = login; }
	void SetPassword(string password) { this->password = password; }
	void SetFullname(FullName fullname) 
	{ 
		firstname = fullname.first;
		lastname = fullname.second;
	}
	void SetAddress(string address) { this->address = address; }
	void SetPhone(string phone) { this->phone = phone; }
	//void SetNewData()
	//{
	//	string tmp_firstname;
	//	string tmp_lastname;
	//	string tmp_address;
	//	string tmp_phone;

	//	if (ChoiseYesNo('y', 'n'))
	//	{
	//		cout << "Enter firstname: ";
	//		getline(cin, tmp_firstname);
	//		cout << "Enter lastname: ";
	//		getline(cin, tmp_lastname);

	//	}
	//	cout << "Enter address: ";
	//	getline(cin, tmp_address);
	//	cout << "Enter phone: ";
	//	getline(cin, tmp_phone);
	//	cout << "========== New data ===========\n";
	//	cout << tmp_firstname << ' ' << tmp_lastname << endl;
	//	cout << "Address: " << tmp_address << endl;
	//	cout << "Phone: " << tmp_phone << endl;
	//	cout << "Save (y) or return (n): ";
	//	char choise{};
	//	while (true)
	//	{
	//		cin >> choise;
	//		cin.clear();
	//		cin.ignore(255, '\n');
	//		if (toupper(choise) == toupper('y'))
	//		{
	//			firstname = tmp_firstname;
	//			lastname = tmp_lastname;
	//			address = tmp_address;
	//			phone = tmp_phone;
	//			return;
	//		}
	//		else if (toupper(choise) == toupper('n'))
	//			return;
	//	}
	//}
	friend bool operator< (const Guest& guest1, const Guest& guest2) 
	{ 
		return ((guest1.firstname == guest2.firstname) ? (guest1.lastname < guest2.lastname) : (guest1.firstname < guest2.firstname));
	}
};
