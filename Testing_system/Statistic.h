#pragma once
#include <iostream>
#include <initializer_list>
#include <vector>
#include <map>
#include <iterator>
#include <algorithm>
#include <string>
using namespace std;

struct Statistic
{
	string subject;
	string topic;
	double maxScore;
	double totalScore;
	Statistic(string subject, string topic, double maxScore, double totalScore)
		: subject(subject), topic(topic), maxScore(maxScore), totalScore(totalScore) {}
	void Show() const
	{
		cout << "--------------== " << subject << " ==--------------\n";
		cout << "\t" << topic << endl;
		cout << "Scores: " << totalScore << "/" << maxScore << endl;
	}
	friend std::ostream& operator<< (std::ostream& out, const Statistic& statistic)
	{
		out << "--------------== " << statistic.subject << " ==--------------\n";
		out << "\t" << statistic.topic << endl;
		out << "Scores: " << statistic.totalScore << "/" << statistic.maxScore << endl;
	}
};
