#pragma once
#include <iostream>
#include <fstream>
#include <initializer_list>
#include <vector>
#include <map>
#include <iterator>
#include <algorithm>
#include <string>
using namespace std;

const char TEST_BEGIN[] = "<TEST>";
const char TEST_END[] = "<TEST/>";
const char CATEGORY_BEGIN[] = "<CTG>";
const char CATEGORY_END[] = "<CTG/>";
const char TEST_NAME_BEGIN[] = "<NAME>";
const char TEST_NAME_END[] = "<NAME/>";

const char DESCRIPTION_BEGIN[] = "<DSCR>";
const char DESCRIPTION_END[] = "<DSCR/>";
const char QUESTION_USER_ANSWER_BEGIN[] = "<QUA>";
const char QUESTION_USER_ANSWER_END[] = "<QUA/>";
const char QUESTION_ONE_ANSWER_BEGIN[] = "<QOA>";
const char QUESTION_ONE_ANSWER_END[] = "<QOA/>";
const char QUESTION_MANY_ANSWER_BEGIN[] = "<QMA>";
const char QUESTION_MANY_ANSWER_END[] = "<QMA/>";
const char ALL_ANSWER_BEGIN[] = "<AANS>";
const char ALL_ANSWER_END[] = "<AANS/>";
const char RIGHT_ANSWER_BEGIN[] = "<RANS>";
const char RIGHT_ANSWER_END[] = "<RANS/>";
const char EXAMPLE_ANSWER_BEGIN[] = "<EANS>";
const char EXAMPLE_ANSWER_END[] = "<EANS/>";

class Question
{
	string description;
public:
	Question(string description) : description(description) {}
	virtual ~Question() {}
	void AskQuestion() const { cout << description << endl; }
	string GetDescription() const { return description; }
	void ChangeDescription(string newDescription) { description = newDescription; }
	virtual float CheckAnswer() const = 0;
	virtual void ShowRightAnswer() const = 0;
	virtual void ChangeAnswer() = 0;
	virtual void ChangeRightAnswer() = 0;
	virtual void ShowAllAnswers() const = 0;
	virtual void Export(ostream& out) const = 0;
};