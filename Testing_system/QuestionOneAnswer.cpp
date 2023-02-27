#include "QuestionOneAnswer.h"

QuestionOneAnswer::QuestionOneAnswer(string description, vector<string>& answers, int numberOfRightAnswer)
	: Question(description), numberOfRightAnswer(numberOfRightAnswer)
{
	for (auto i : answers)
		this->answers.push_back(i);
}
bool QuestionOneAnswer::isCorrectRightAnswer()
{
	if (numberOfRightAnswer <= 0 || answers.size() < numberOfRightAnswer)
		return 0;
	return 1;
}
float QuestionOneAnswer::CheckAnswer()
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
void QuestionOneAnswer::ShowRightAnswer()
{
	if (!isCorrectRightAnswer())
	{
		cout << "Erorr question! Check questin or answer!\n";
		return;
	}
	cout << answers[numberOfRightAnswer - 1] << endl;
}
void QuestionOneAnswer::ChangeAnswer()
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
void QuestionOneAnswer::ChangeRightAnswer()
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
void QuestionOneAnswer::ShowAllAnswers()
{
	int count = 1;
	for (auto i : answers)
		cout << count++ << ") " << i << endl;
}
void QuestionOneAnswer::Export(string filename)
{
	ofstream out(filename + ".txt", ios::app);
	out << DESCRIPTION_BEGIN << ' ';
	out << GetDescription() << ' ';
	out << DESCRIPTION_END << ' ';
	out << QUESTION_ONE_ANSWER_BEGIN << ' ';
	out << ALL_ANSWER_BEGIN << ' ';
	for (auto i : answers)
		out << EXAMPLE_ANSWER_BEGIN << ' ' << i << ' ' << EXAMPLE_ANSWER_END << ' ';
	out << ALL_ANSWER_END << ' ';
	out << RIGHT_ANSWER_BEGIN << ' ';
	out << numberOfRightAnswer << " ";
	out << RIGHT_ANSWER_END << ' ';
	out << QUESTION_ONE_ANSWER_END << " \n";
	out.close();
}