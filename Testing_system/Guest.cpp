#include "Guest.h"

bool Guest::ChoiseYesNo(char ifTrue = 'y', char ifFasle = 'n')
{
	char choise{};
	while (true)
	{
		cin >> choise;
		cin.clear();
		cin.ignore(255, '\n');
		if (toupper(choise) == toupper(ifTrue))
			return true;
		else if (toupper(choise) == toupper(ifFasle))
			return false;
	}
}
void Guest::Show() const
{
	cout << firstname << " " << lastname << endl;
	cout << "Address: " << address << endl;
	cout << "Phone: " << phone << endl;
}
