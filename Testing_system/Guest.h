#pragma once
#include <iostream>
#include <initializer_list>
#include <vector>
#include <map>
#include <iterator>
#include <algorithm>
#include <string>
#include "Statistic.h"
using namespace std;


class Guest
{
	string login;
	string password;
	string fullname;
	string address;
	string phone;
	vector<Statistic> statistic;
public:
	Guest(string login, string password, string fullname, string address, string phone)
		: login(login), password(password), address(address), phone(phone) {}
	~Guest() { statistic.clear(); }
	void AddStatistic(string title, string testName, double maxScore, double totalScore)
	{
		statistic.push_back(Statistic(title, testName, maxScore, totalScore));
	}
	void ShowStatistic() const
	{
		for (auto i : statistic)
		{
			i.Show();
			cout << endl;
		}
	}
	bool LoginValidation(string checkPassword)
	{
		return checkPassword == password;
	}
};
