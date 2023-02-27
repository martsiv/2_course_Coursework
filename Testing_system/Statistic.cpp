#include "Statistic.h"

std::ostream& operator<< (std::ostream& out, const Statistic& statistic)
{
	out << "--------------== " << statistic.category << " ==--------------\n";
	out << "\t" << statistic.testName << '\n';
	out << "Student: " << statistic.fullname.first << ' ' << statistic.fullname.second << '\n';
	out << "Number of correct answers: " << statistic.GetTotalScore() << '/' << statistic.GetMaxScore() << '\n';
	out << "Percentage of correct answers:" << statistic.GetPercent() << '\n';
	out << "Grade: " << statistic.GetGrade() << endl;
	return out;
}
bool predicateComparisonByTestName(const Statistic& stat1, const Statistic& stat2)
{
	return ((stat1.GetTestName() == stat2.GetTestName()) ? (stat1 < stat2) : (stat1.GetTestName() > stat2.GetTestName()));
}
bool predicateComparisonByCategory(const Statistic& stat1, const Statistic& stat2)
{
	return ((stat1.GetCategory() == stat2.GetCategory()) ? predicateComparisonByTestName(stat1, stat2) : (stat1.GetCategory() > stat2.GetCategory()));
}