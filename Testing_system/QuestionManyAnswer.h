#pragma once
#include "Question.h"
using namespace std;


class QuestionManyAnswer : public Question
{
	vector<string> answers;
	vector<int> numbersOfRightAnswer;		//The countdown starts not from 0, but from 1
public:
	QuestionManyAnswer(string description) : Question(description) { ChangeAnswer(); }
	QuestionManyAnswer(string description, vector<string>& answers, vector<int>& numbersOfRightAnswer)
		: Question(description)
	{
		for (auto i : answers)
			this->answers.push_back(i);
		for (auto i : numbersOfRightAnswer)
			this->numbersOfRightAnswer.push_back(i);
	}
	~QuestionManyAnswer() {}
	QuestionType GetTypeQuestion() const { return QuestionType::ManyAnswer; }
	bool isCorrectRightAnswer() 
	{
		for (auto i : numbersOfRightAnswer)
		{
			if (i <= 0 || answers.size() < i)
				return 0;
		}
		return 1;
	}	 
	float CheckAnswer() 
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
		string s_userAnswer;
		vector<int> i_userAnswer;
		do
		{
			i_userAnswer.clear();
			cout << "Enter " << numbersOfRightAnswer.size() << " numbers of correct answers (with a space): ";

			getline(cin, s_userAnswer);
			for (auto i : s_userAnswer)
			{
				if (i == ' ')
					continue;
				if (isdigit(i))
					i_userAnswer.push_back(i - 48);
			}
		} while (numbersOfRightAnswer.size() != i_userAnswer.size());
		float result = 0;
		double step = (double)1 / numbersOfRightAnswer.size();
		for (auto i : i_userAnswer)
		{
			if (find(numbersOfRightAnswer.begin(), numbersOfRightAnswer.end(), i) != numbersOfRightAnswer.end())
				result += step;
		}
		return result;
	}
	void ShowRightAnswer() 
	{
		if (!isCorrectRightAnswer())
		{
			cout << "Erorr question! Check questin or answer!\n";
			return;
		}
		for (auto i : numbersOfRightAnswer)
			cout << answers[i - 1] << endl;
	}
	void ChangeAnswer()
	{
		vector<string> tmp;
		string userAnswer;
		char ch;
		do
		{
			int count = 0;
			tmp.clear();
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

			if (tmp.size() < 3)
			{
				cout << "There must be at least 3 options. Try again!\n";
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
		for (auto i : answers)		//show all answers
		{
			cout << ++count << ") " << i << endl;
		}
		char ch;
		string s_userAnswer;
		vector<int> i_userAnswer;
		do
		{
			bool isCorrect = 0;
			while (!isCorrect)	//check the range (0 - answers size vector)
			{
				i_userAnswer.clear();
				isCorrect = 1;
				cout << "Enter the numbers of correct answers (with a space): ";
				getline(cin, s_userAnswer);
				for (auto i : s_userAnswer)
				{
					if (i == ' ')
						continue;
					if (isdigit(i) && (((i - 48) <= 0) || (answers.size() < (i - 48))))
					{
						cout << "Invalid number of right answer\n";
						isCorrect = 0;
					}
					if (isdigit(i))
						i_userAnswer.push_back(i - 48);
				}
				if (answers.size() <= i_userAnswer.size())
				{
					cout << "There should be fewer correct answers than total answers. Try again!\n";
					isCorrect = 0;
				}
			}

			cout << "\nNew right answers:\n";		//new right answers in tmp vector
			for (auto i : i_userAnswer)
				cout << i << ") " << answers[i - 1] << endl;
			cout << "\nAll right?(y) Try again?(n)\t";
			cin.get(ch);
			cin.ignore(255, '\n');
		} while (tolower(ch) != 'y');
		
		numbersOfRightAnswer.clear();
		for (auto i : i_userAnswer)
			numbersOfRightAnswer.push_back(i);
		sort(numbersOfRightAnswer.begin(), numbersOfRightAnswer.end());
		//cout << "New result of right answers: \n";
		//ShowRightAnswer();

	}
	void ShowAllAnswers() 
	{
		int count = 1;
		for (auto i : answers)
			cout << count++ << ") " << i << endl;
	}
	void Export(string filename)
	{
		ofstream out(filename + ".txt", ios::app);
		out << DESCRIPTION_BEGIN << ' ';
		out << GetDescription() << ' ';
		out << DESCRIPTION_END << ' ';
		out << QUESTION_MANY_ANSWER_BEGIN << ' ';
		out << ALL_ANSWER_BEGIN << ' ';
		for (auto i : answers)
			out << EXAMPLE_ANSWER_BEGIN << ' ' << i << ' ' << EXAMPLE_ANSWER_END << ' ';
		out << ALL_ANSWER_END << ' ';
		out << RIGHT_ANSWER_BEGIN << ' ';
		for (auto i : numbersOfRightAnswer)
			out << EXAMPLE_ANSWER_BEGIN << ' ' << i << ' ' << EXAMPLE_ANSWER_END << ' ';
		out << RIGHT_ANSWER_END << ' ';
		out << QUESTION_MANY_ANSWER_END << " \n";
		out.close();
	}
};


