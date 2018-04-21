#include "Header.h"

void Lecturer_Menu(char username[], char password[], int type)
{
	cout << "*******************MAIN MENU*******************\n" << endl;
	cout << "INSTRUCTION: " << "press number to choose your action.\n" << endl;
	cout << "1.SCOREBOARD" << endl;
	cout << "2.OPTION" << endl;
	cout << "3.LOG OUT" << endl;
	cout << "0.EXIT" << endl;
	cout << "\n" << "***********************************************" << endl;
	char hotkey = _getch();

	while (hotkey != '0' && hotkey != '1' && hotkey != '2' && hotkey != '3')
	{
		hotkey = _getch();
		continue;
	}

	switch (hotkey)
	{
	case '1':
		system("cls");
		Lecturer_Scoreboard_Menu(username, password, type);
		break;
	case '2':
		system("cls");
		Lecturer_Option_Menu(username, password, type);
		break;
	case '3':
		system("cls");		
		Access();
		break;

	case '0':
		return;
		exit(EXIT_FAILURE);
		break;
	}

}

void Lecturer_Scoreboard_Menu(char username[], char password[], int type)
{
	cout << "*******************SCOREBOARD*******************\n" << endl;
	cout << "1.Import Scoreboard" << endl;
	cout << "2.Edit Grade" << endl;
	cout << "3.View Scoreboard" << endl;
	cout << "0.Back" << endl;
	cout << "\n************************************************\n" << endl;
	char hotkey = _getch();

	while (hotkey != '0' && hotkey != '1' && hotkey != '2' && hotkey != '3')
	{
		hotkey = _getch();
		continue;
	}

	char hotkey_temp;
	switch (hotkey)
	{
	default:
		system("cls");
		cout << "This is still in Beta process, come back at the next release." << endl;
		cout << "Press '0' to back to scoreboard menu" << endl;

		hotkey_temp = _getch();
		while (hotkey_temp != '0')
		{
			hotkey_temp = _getch();
			continue;
		}

		if (hotkey_temp == '0')
		{
			system("cls");
			Lecturer_Scoreboard_Menu(username, password, type);
		}
		
	case '1':
		system("cls");
		importScore(username, password, type);

		break;
	case '2':
		system("cls");
		editScore(username, password, type);

		break;

	case '3':
		system("cls");
		searchViewScore(username, password, type);

		break;

	case '0':
		system("cls");
		Lecturer_Menu(username, password, type);
		break;
	}

}

void Lecturer_Option_Menu(char username[], char password[], int type)
{
	cout << "*******************OPTION*******************\n" << endl;
	cout << "1.Profile" << endl;
	cout << "2.Change Password" << endl;
	cout << "0.Back" << endl;
	cout << "\n********************************************\n" << endl;

	char hotkey = _getch();

	while (hotkey != '0' && hotkey != '1' && hotkey != '2')
	{
		hotkey = _getch();
		continue;
	}

	switch (hotkey)
	{
	case '1':
		system("cls");
		Print_User(username, password, type);
		break;

	case '2':
		system("cls");
		changePassword("teacher.txt", username, password);

		cout << "CHANGE PASSWORD SUCCESSFULLY!!" << endl;
		Sleep(2000);

		system("cls");
		Lecturer_Option_Menu(username, password, type);
		break;

	case '0':
		system("cls");
		Lecturer_Menu(username, password, type);
		break;

	}
}