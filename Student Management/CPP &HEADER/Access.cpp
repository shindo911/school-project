#include "Header.h"


/* Access
Variables:
	username: variable contain string of username.
	password: variable contain string of password.
	type: contain value of user type.
*/
void Access()
{
	char username[50], password[50];
	int type;

	Login(username, password, type);	// let the user access, update username, password and type.

	switch(type)
	{
	case 0: // user is a student
		system("cls");
		cout << "===============HELLO USER===============" << endl;
		cout << "        Press Enter to continue         " << endl;
		if (_getch() == 13)
			system("cls");

		Student_Menu(username, password, type); // access to student's main menu.
		break;

	case 1:	// user is a staff
		system("cls");
		cout << "===============HELLO USER===============" << endl;
		cout << "        Press Enter to continue         " << endl;
		if (_getch() == 13)
			system("cls");
		
		Staff_Menu(username, password, type); // access to staff's main menu.
		break;

	case 2: // user is a lecturer
		system("cls");
		cout << "===============HELLO USER===============" << endl;
		cout << "        Press Enter to continue         " << endl;
		if (_getch() == 13)
			system("cls");

		Lecturer_Menu(username, password, type); // access to lecturer's main menu.
		break;
	}
}
