#pragma once
#include "Question.h"
using namespace std;


class QuestionOneAnswer : public Question
{
	vector<string> answers;
	int numberOfRightAnswer;		//The countdown starts not from 0, but from 1
public:
	QuestionOneAnswer(string description) : Question(description), numberOfRightAnswer(0){ ChangeAnswer(); }
	QuestionOneAnswer(string description, vector<string>& answers, int numberOfRightAnswer)
		: Question(description), numberOfRightAnswer(numberOfRightAnswer)
	{
		for (auto i : answers)
			this->answers.push_back(i);
	}
	~QuestionOneAnswer() {}
	bool isCorrectRightAnswer() const
	{
		if (numberOfRightAnswer <= 0 || answers.size() < numberOfRightAnswer)
			return 0;
		return 1;
	}
	float CheckAnswer() const
	{
		if (!isCorrectRightAnswer())
		{
			cout << "Erorr question! Check questin or answer!\n";
			return 0;
		}
		int count = 0;
		for (auto i : answers)
		{
			cout << ++count << ") " << i << endl;
		}
		cout << "Enter the number of the correct answer: ";
		int userAnswer;
		cin >> userAnswer;
		if (!cin)
			cin.clear();
		cin.ignore(256, '\n');
		if (userAnswer == numberOfRightAnswer)
			return 1;
		return 0;
	}
	void ShowRightAnswer() const 
	{
		if (!isCorrectRightAnswer())
		{
			cout << "Erorr question! Check questin or answer!\n";
			return;
		}
		cout << answers[numberOfRightAnswer - 1] << endl; 
	}
	void ChangeAnswer()
	{
		vector<string> tmp;
		string userAnswer;
		char ch{};
		do
		{
			tmp.clear();
			int count = 0;
			cout << "Write all the answer options\n";
			do
			{
				cout << "Enter answer #" << ++count << endl;
				getline(cin, userAnswer);
				tmp.push_back(userAnswer);
				cout << "Would you like to enter another answer option(Y), or exit(N)?\t";
				cin.get(ch);
				cin.ignore(255, '\n');
			} while (tolower(ch) != 'n');

			if (tmp.size() < 2)
			{
				cout << "There must be at least 2 options. Try again!\n";
				continue;
			}
			cout << "\nNew answer options\n";
			count = 0;
			for (auto i : tmp)
			{
				cout << ++count << ") " << i << endl;
			}
			cout << "\nAll right?(y) Try again?(n)\t";
			cin.get(ch);
			cin.ignore(255, '\n');
		} while (tolower(ch) != 'y');

		answers.clear();
		for (auto i : tmp)
			answers.push_back(i);
		ChangeRightAnswer();
	}
	void ChangeRightAnswer()
	{
		int count = 0;
		for (auto i : answers)
		{
			cout << ++count << ") " << i << endl;
		}
		bool isCorrect = 0;
		while (!isCorrect)		// check or response new right answer to the range of all answers
		{
			isCorrect = 1;
			cout << "Enter the number of the correct answer: ";
			cin >> numberOfRightAnswer;
			if (!cin)
				cin.clear();
			cin.ignore(255, '\n');
			if (numberOfRightAnswer <= 0 || answers.size() < numberOfRightAnswer)
			{
				cout << "Invalid number (out of the range)\n";
				isCorrect = 0;
			}
		}
	}
	void ShowAllAnswers() const
	{
		int count = 1;
		for (auto i : answers)
			cout << count++ << ") " << i << endl;
	}
	void Export(ostream& out) const
	{
		out << "<DSCR> ";
		out << GetDescription() << ' ';
		out << "<DSCR/> ";
		out << "<QOA> ";
		out << "<AANS> ";
		for (auto i : answers)
			out << EXAMPLE_ANSWER_BEGIN << ' ' << i << ' ' << EXAMPLE_ANSWER_END << ' ';
		out << "<AANS/> ";
		out << "<RANS> ";
		out << numberOfRightAnswer << " ";
		out << "<RANS/> ";
		out << "<QOA/>\n";
	}
};
