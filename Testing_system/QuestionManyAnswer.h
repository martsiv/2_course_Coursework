#pragma once
#include "Question.h"
using namespace std;


class QuestionManyAnswer : public Question
{
	vector<string> answers;
	vector<int> numbersOfRightAnswer;		//The countdown starts not from 0, but from 1
public:
	QuestionManyAnswer(string description) : Question(description) { ChangeAnswer(); }
	QuestionManyAnswer(string description, vector<string>& answers, vector<int>& numbersOfRightAnswer);
	~QuestionManyAnswer() {}
	QuestionType GetTypeQuestion() const { return QuestionType::ManyAnswer; }
	bool isCorrectRightAnswer();
	float CheckAnswer();
	void ShowRightAnswer();
	void ChangeAnswer();
	void ChangeRightAnswer();
	void ShowAllAnswers();
	void Export(string filename);
};


