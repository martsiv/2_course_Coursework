#pragma once
#include "Question.h"
#include "QuestionUserAnswer.h"
#include "QuestionOneAnswer.h"
#include "QuestionManyAnswer.h"
using namespace std;
typedef vector<shared_ptr<Question>>::iterator QuestionIterator;

class Test
{
	string category;
	string testName;
	int maxPoint;
	vector<shared_ptr<Question>> questions;		//polymorphism
	void RecalculateMaxPoint() { maxPoint = questions.size(); }
	int verificateNum(int leftRange, int rightRange);

public:
	Test(string category, string testName) : category(category), testName(testName), maxPoint(0) {}
	Test(const Test& test);
	Test(const string& fileName);
	string GetCategory() { return category; }
	string GetTestName() { return testName; }
	void ClearTest();
	void AddQuestion();
	void AddQuestion(shared_ptr<Question> question);
	QuestionIterator FindQuestion();
	bool IsOkQuestionIterator(QuestionIterator it);
	void DeleteQuestion(QuestionIterator it);
	void ChangeDescriptionQuestion(QuestionIterator it);
	void ChangeAnswerInQuestion(QuestionIterator it);
	void ChangeRightAnswerInQuestion(QuestionIterator it);
	float StartTest();
	int GetMaxPoint() { return maxPoint; }
	void ShowAllQuestions();
	void Export(string filename);
	int Import(string filename);
	friend bool operator< (const Test& test1, const Test& test2);
	friend bool operator== (const Test& test1, const Test& test2);
};
