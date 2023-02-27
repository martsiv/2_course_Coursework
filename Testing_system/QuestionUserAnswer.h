#pragma once
#include "Question.h"
using namespace std;

class QuestionUserAnswer : public Question
{
	string answer;
public:
	QuestionUserAnswer(string description) : Question(description), answer("") { ChangeRightAnswer(); }
	QuestionUserAnswer(string description, string answer) : Question(description), answer(answer) {}
	~QuestionUserAnswer() {}
	QuestionType GetTypeQuestion() const { return QuestionType::OwnAnswer; }
	float CheckAnswer();
	void ShowRightAnswer()  { cout << answer << endl; }
	void ChangeAnswer() { ChangeRightAnswer(); }
	void ChangeRightAnswer();
	void ShowAllAnswers() { cout << "Write your answer\n"; }
	void Export(string filename);
};
