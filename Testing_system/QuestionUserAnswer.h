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
	float CheckAnswer() const
	{
		string usersAnswer;
		cout << "Enter right answer: ";
		cin >> usersAnswer;
		cin.ignore(256, '\n');
		if (answer == usersAnswer)
			return 1;
		return 0;
	}
	void ShowRightAnswer() const { cout << answer << endl; }
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
	void ShowAllAnswers() const
	{
		cout << "Write your answer\n";
	}
	void Export(ostream& out) const
	{
		out << "<DSCR> ";
		out << GetDescription() << ' ';
		out << "<DSCR/> ";
		out << "<QUA> ";
		out << "<RANS> ";
		out << answer << ' ';
		out << "<RANS/> ";
		out << "<QUA/>\n";
	}
};
