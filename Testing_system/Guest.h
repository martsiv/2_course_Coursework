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
	bool ChoiseYesNo(char ifTrue, char ifFasle);
	void Show() const;
	FullName GetFullname() const { return FullName(firstname, lastname); }
	string GetPassword() const { return password; }
	string GetAddress() const { return address;	}
	string GetPhone() const	{ return phone; }
	void SetLogin(string login) { this->login = login; }
	void SetPassword(string password) { this->password = password; }
	void SetFullname(FullName fullname) 
	{ 
		firstname = fullname.first;
		lastname = fullname.second;
	}
	void SetAddress(string address) { this->address = address; }
	void SetPhone(string phone) { this->phone = phone; }
	friend bool operator< (const Guest& guest1, const Guest& guest2) { return ((guest1.firstname == guest2.firstname) ? (guest1.lastname < guest2.lastname) : (guest1.firstname < guest2.firstname)); }
};
