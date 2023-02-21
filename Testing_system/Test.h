#pragma once
#include "Question.h"
#include "QuestionUserAnswer.h"
#include "QuestionOneAnswer.h"
#include "QuestionManyAnswer.h"
using namespace std;
int verificateNum(int leftRange, int rightRange)
{
	int num;
	while (!(cin >> num) || (num < leftRange) || (rightRange < num))
	{
		cin.clear();
		while (cin.get() != '\n')
			continue;
	}
	cin.ignore(256, '\n');
	return num;
}
class Test
{
	enum class QuestionType { OwnAnswer = 1, OneAnswer, ManyAnswer };
	string category;
	string testName;
	int maxPoint;
	vector<Question*> questions;		//polymorphism
	void RecalculateMaxPoint() { maxPoint = questions.size(); }
	
public:
	Test(string category, string testName) : category(category), testName(testName), maxPoint(0) {}
	~Test()
	{
		for (auto i : questions)
			delete i;
		questions.clear();
	}
	string GetCategory() const { return category; }
	string GetTestName() const { return testName; }
	void ClearTest()
	{
		questions.clear();
		RecalculateMaxPoint();
	}
	void AddQuestion()
	{
		cout << "Choose a question type\n"
			<< "1 - With own answer\n"
			<< "2 - With one correct answer\n"
			<< "3 - With several correct answers\n"
			<< "0 - To return\n";

		int result = verificateNum(0, 3);
		if (!result)
			return;
		cout << "Enter description: ";
		string description;
		getline(cin, description);

		switch (QuestionType(result))
		{
		case Test::QuestionType::OwnAnswer:
			questions.push_back(new QuestionUserAnswer(description));
			//questions.back()->SetAnswer();
			break;
		case Test::QuestionType::OneAnswer:
			questions.push_back(new QuestionOneAnswer(description));
			break;
		case Test::QuestionType::ManyAnswer:
			questions.push_back(new QuestionManyAnswer(description));
			break;
		default:
			break;
		}
		RecalculateMaxPoint();
	}
	void AddQuestion(Question* question)
	{
		questions.push_back(question);
	}
	vector<Question*>::iterator FindQuestion()
	{
		int count = 0;
		for (auto i : questions)
		{
			cout << "#" << count++ << " ";
			i->AskQuestion();
		}
		cout << "Enter the question index. Or -1 to exit\n";
		int res = verificateNum(-1, questions.size() - 1);
		if (res == -1)
			return questions.end();
		return questions.begin() + res;
	}
	void DeleteQuestion(vector<Question*>::iterator it)
	{
		delete *it;
		questions.erase(it);
		RecalculateMaxPoint();
	}
	void ChangeDescriptionQuestion(vector<Question*>::iterator it)
	{
		cout << "Enter new description: ";
		string description;
		getline(cin, description);
		(*it)->ChangeDescription(description);
	}
	void ChangeAnswerInQuestion(vector<Question*>::iterator it)
	{
		(*it)->ChangeAnswer();
	}
	void ChangeRightAnswerInQuestion(vector<Question*>::iterator it)
	{
		(*it)->ChangeRightAnswer();
	}
	float StartTest()
	{
		cout << "Test on the subject of " << category << " on the topic of " << testName << endl;
		if (!questions.size())
			cout << "There are no questions in the test!\n";
		float result = 0;
		int count = 1;
		for (auto i : questions)
		{
			cout << "Question " << count++ << " of " << questions.size() << endl;
			i->AskQuestion();
			result += i->CheckAnswer();
		}

		return result;
	}
	int GetMaxPoint() const { return maxPoint; }
	void ShowAllQuestions() const
	{
		int count = 1;
		for (auto i : questions)
		{
			cout << "\tQuestion " << count++ << endl;
			i->AskQuestion();
			i->ShowAllAnswers();
		}
	}
	void Export(string filename = "") const
	{
		if (filename == "")
			filename = testName;
		ofstream out(filename + ".txt");
		out << "<TEST> ";
		out << "<CTG> " << category << " <CTG/> ";
		out << "<NAME> " << testName << " <NAME/> \n";
		for (auto i : questions)
			i->Export(out);
		out << "\n<TEST/> ";
		out.close();
	}
	//int Import(string filename = "")
	//{
	//	// 0 all right
	//	// 1 file error
	//	// 2 format data erorr 
	//	// 3 question format error
	//	ifstream in(filename);
	//	if (!in)
	//	{
	//		cerr << "Invalid reading!" << endl;
	//		return 1;
	//	}
	//	string in_category;
	//	string in_testName;
	//	string in_description;
	//	string in_answer;
	//	vector<string> in_answers;
	//	int in_numberOfRightAnswer;
	//	vector<int> in_numbersOfRightAnswer;
	//	bool b_category = 0;
	//	bool b_test_name = 0;
	//	bool b_description = 0;
	//	bool b_answers = 0;
	//	bool b_right_answers = 0;
	//	string strInput;
	//	in >> strInput;
	//	if (strInput != TEST_BEGIN)
	//	{
	//		cout << "Eror data!\n";
	//		return 2;
	//	}
	//	while (in)
	//	{
	//		in >> strInput;
	//		if (strInput == TEST_END)
	//			break;
	//		if (strInput == CATEGORY_BEGIN)
	//		{
	//			while (in >> strInput, strInput != CATEGORY_END)
	//			{
	//				in_category += (strInput + " ");
	//			} 
	//			continue;
	//		}
	//		if (strInput == TEST_NAME_BEGIN)
	//		{
	//			while (in >> strInput, strInput != TEST_NAME_END)
	//			{
	//				in_testName += (strInput + " ");
	//			}
	//			continue;
	//		}
	//		if (strInput == DESCRIPTION_BEGIN)
	//		{
	//			while (in >> strInput, strInput != DESCRIPTION_END)
	//			{
	//				in_description += (strInput + " ");
	//			}
	//			continue;
	//		}
	//		if (strInput == QUESTION_USER_ANSWER_BEGIN)
	//		{
	//			while (in >> strInput, strInput != QUESTION_USER_ANSWER_END)
	//			{
	//				if (strInput == RIGHT_ANSWER_BEGIN)
	//				{
	//					in >> strInput;
	//					in_answer = strInput;
	//				}
	//			}
	//			if (!b_category || !b_test_name || !b_description || !b_right_answers)
	//			{
	//				cout << "Error in question format!\n";
	//				return 3;
	//			}
	//			QuestionUserAnswer* q_tmp = new QuestionUserAnswer(in_description, in_answer);
	//			AddQeustion(q_tmp);
	//			in_answer.clear();
	//		}
	//		else if (strInput == QUESTION_ONE_ANSWER_BEGIN)
	//		{
	//			while (in >> strInput, strInput != QUESTION_ONE_ANSWER_END)
	//			{
	//				if (strInput == ALL_ANSWER_BEGIN)
	//				{
	//					while (in >> strInput, strInput != ALL_ANSWER_END)
	//					{
	//						if (strInput == EXAMPLE_ANSWER_BEGIN)
	//						{
	//							while (in >> strInput, strInput != EXAMPLE_ANSWER_END)
	//							{
	//								in_answer += (strInput + " ");
	//							}
	//							in_answers.push_back(in_answer);
	//							in_answer.clear();
	//						}
	//					}
	//				}
	//				if (strInput == RIGHT_ANSWER_BEGIN)
	//				{
	//					in >> strInput;
	//					in_numberOfRightAnswer = stoi(strInput);
	//				}
	//			}
	//			if (!b_category || !b_test_name || !b_description || !b_answers || !b_right_answers)
	//			{
	//				cout << "Error in question format!\n";
	//				return 3;
	//			}
	//			QuestionOneAnswer* q_tmp = new QuestionOneAnswer(in_description, in_answers, in_numberOfRightAnswer);
	//			AddQeustion(q_tmp);
	//			in_answer.clear();
	//			in_answers.clear();
	//		}
	//		else if (strInput == QUESTION_MANY_ANSWER_BEGIN)
	//		{
	//			while (in >> strInput, strInput != QUESTION_MANY_ANSWER_END)
	//			{
	//				if (strInput == ALL_ANSWER_BEGIN)
	//				{
	//					while (in >> strInput, strInput != ALL_ANSWER_END)
	//					{
	//						if (strInput == EXAMPLE_ANSWER_BEGIN)
	//						{
	//							while (in >> strInput, strInput != EXAMPLE_ANSWER_END)
	//							{
	//								in_answer += (strInput + " ");
	//							}
	//							in_answers.push_back(in_answer);
	//							in_answer.clear();
	//						}
	//					}
	//				}
	//				if (strInput == RIGHT_ANSWER_BEGIN)
	//				{
	//					while (in >> strInput, strInput != RIGHT_ANSWER_END)
	//					{
	//						if (strInput == EXAMPLE_ANSWER_BEGIN)
	//						{
	//							while (in >> strInput, strInput != EXAMPLE_ANSWER_END)
	//							{
	//								in_numbersOfRightAnswer.push_back(stoi(strInput));
	//							}
	//						}
	//					}
	//				}
	//			}
	//			if (!b_category || !b_test_name || !b_description || !b_answers || !b_right_answers)
	//			{
	//				cout << "Error in question format!\n";
	//				return 3;
	//			}
	//			QuestionManyAnswer* q_tmp = new QuestionManyAnswer(in_description, in_answers, in_numbersOfRightAnswer);
	//			AddQeustion(q_tmp);
	//			in_answer.clear();
	//			in_answers.clear();
	//			in_numbersOfRightAnswer.clear();
	//		}
	//		in_description.clear();
	//	}
	//	in.close();
	//	return 0;
	//}
	friend bool operator< (const Test& test1, const Test& test2)
	{
		return test1.category < test1.category;
	}
};
