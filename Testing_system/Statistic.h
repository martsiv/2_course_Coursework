#pragma once
#include <iostream>
#include <initializer_list>
#include <vector>
#include <map>
#include <iterator>
#include <algorithm>
#include <string>
#include "Guest.h"
using namespace std;

struct Statistic
{
	FullName fullname;
	string category;
	string testName;
	double maxScore;
	double totalScore;
	Statistic(FullName fullname, string category, string testName, double maxScore, double totalScore)
		: fullname(fullname), category(category), testName(testName), maxScore(maxScore), totalScore(totalScore) {}
	FullName GetFullName() const { return fullname; }
	string GetCategory() const { return category; }
	string GetTestName() const { return testName; }
	int GetMaxScore() const { return maxScore; }
	double GetTotalScore() const{ return totalScore; }
	int GetPercent() const { return totalScore / maxScore * 100; }
	int GetGrade() const { return totalScore / maxScore * 100 / 8.333; }
	friend bool operator< (const Statistic& statistic1, const Statistic& statistic2)
	{
		return ((statistic1.fullname.first == statistic2.fullname.first) ? (statistic1.fullname.second < statistic2.fullname.second) : (statistic1.fullname.first < statistic2.fullname.first));
	}

	friend std::ostream& operator<< (std::ostream& out, const Statistic& statistic)
	{
		out << "--------------== " << statistic.category << " ==--------------\n";
		out << "\t" << statistic.testName << '\n';
		out << "Student: " << statistic.fullname.first << ' ' << statistic.fullname.second << '\n';
		out << "Number of correct answers: " << statistic.GetTotalScore() << '/' << statistic.GetMaxScore() << '\n';
		out << "Percentage of correct answers:" << statistic.GetPercent() << '\n';
		out << "Grade: " << statistic.GetGrade() << endl;
		return out;
	}
};
