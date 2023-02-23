#pragma once
#include "Question.h"
using namespace std;

class QuestionUserAnswer : public Question
{
	string answer;
public:
	QuestionUserAnswer(string description) : Question(description), answer(answer) { ChangeRightAnswer(); }
	QuestionUserAnswer(string description, string answer) : Question(description), answer(answer) {}
	~QuestionUserAnswer() {}
	float CheckAnswer() 
	{
		string usersAnswer;
		cout << "Enter right answer: ";
		cin >> usersAnswer;
		cin.ignore(256, '\n');
		//std::transform(answer.begin(), answer.end(), answer.begin(), ::tolower);
		//std::transform(usersAnswer.begin(), usersAnswer.end(), usersAnswer.begin(), ::tolower);
		if (answer == usersAnswer)
			return 1;
		return 0;
	}
	void ShowRightAnswer()  { cout << answer << endl; }
	void ChangeAnswer() { ChangeRightAnswer(); }
	void ChangeRightAnswer()
	{
		char ch;
		do
		{
			cout << "Enter the correct answer (one word): ";
			cin >> answer;
			cin.ignore(256, '\n');
			cout << answer << endl;
			cout << "Is everything correct?(y, n)\t";
			cin.get(ch);
			cin.ignore(256, '\n');
		} while (tolower(ch) != 'y');
	}
	void ShowAllAnswers() 
	{
		cout << "Write your answer\n";
	}
	void Export(string filename)
	{
		ofstream out(filename + ".txt", ios::app);
		out << DESCRIPTION_BEGIN << ' ';
		out << GetDescription() << ' ';
		out << DESCRIPTION_END << ' ';
		out << QUESTION_USER_ANSWER_BEGIN << ' ';
		out << RIGHT_ANSWER_BEGIN << ' ';
		out << answer << ' ';
		out << RIGHT_ANSWER_END << ' ';
		out << QUESTION_USER_ANSWER_END << " \n";
		out.close();
	}
};
