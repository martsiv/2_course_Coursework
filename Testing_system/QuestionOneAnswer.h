#pragma once
#include "Question.h"
using namespace std;


class QuestionOneAnswer : public Question
{
	vector<string> answers;
	int numberOfRightAnswer;		//The countdown starts not from 0, but from 1
public:
	QuestionOneAnswer(string description) : Question(description), numberOfRightAnswer(0){ ChangeAnswer(); }
	QuestionOneAnswer(string description, vector<string>& answers, int numberOfRightAnswer);
	~QuestionOneAnswer() {}
	QuestionType GetTypeQuestion() const { return QuestionType::OwnAnswer; }
	bool isCorrectRightAnswer();
	float CheckAnswer();
	void ShowRightAnswer();
	void ChangeAnswer();
	void ChangeRightAnswer();
	void ShowAllAnswers();
	void Export(string filename);
};
