#include "Header.h"

void Student_Menu(char username[], char password[], int type)
{
	cout << "*******************MAIN MENU*******************\n" << endl;
	cout << "INSTRUCTION: " << "press number to choose your action.\n" << endl;

	cout << "1.CHECK-IN" << endl;
	cout << "2.SCOREBOARD" << endl;
	cout << "3.SCHEDULE" << endl;
	cout << "4.OPTION" << endl;
	cout << "5.LOG OUT" << endl;
	cout << "0.EXIT" << endl;
	cout << "\n" << "***********************************************" << endl;

	char hotkey = _getch();

	while (hotkey != '0' && hotkey != '1' && hotkey != '2' && hotkey != '3' && hotkey != '4' && hotkey != '5')
	{
		hotkey = _getch();
		continue;
	}

	switch (hotkey)
	{
	case '1':
		system("cls");
		Student_Checkin_Menu(username, password, type);
		break;
	case '2':
		system("cls");
		Student_Scoreboard_Menu(username, password, type);
		break;
	case '3':
		system("cls");
		Student_Schedule_Menu(username, password, type);
		break;
	case '4':
		system("cls");
		Student_Option_Menu(username, password, type);
		break;
	case '5':
		system("cls");
		Access();
		break;

	case '0':
		return;
		exit(EXIT_FAILURE);
	}
}

void Student_Checkin_Menu(char username[], char password[], int type)
{
	cout << "*******************COURSE*******************\n" << endl;
	cout << "1.Check-in" << endl;
	cout << "2.View Check-in Result" << endl;
	cout << "0.Back" << endl;
	cout << "\n********************************************\n" << endl;

	char hotkey = _getch();

	while (hotkey != '0' && hotkey != '1' && hotkey != '2')
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
		cout << "Press '0' to back to option menu" << endl;

		hotkey_temp = _getch();

		while (hotkey_temp != '0')
		{
			hotkey_temp = _getch();
			continue;
		}

		if (hotkey_temp == '0')
		{
			system("cls");
			Student_Checkin_Menu(username, password, type);
		}
		break;
	case '1':
		system("cls");
		checkIn(username, password, type);
		break;
	case '2':
		system("cls");
		viewCheckIn(username, password, type);
		break;
	case '0':
		system("cls");
		Student_Menu(username, password, type);
		break;
	}

}

void Student_Scoreboard_Menu(char username[], char password[], int type)
{
	cout << "*******************SCOREBOARD*******************\n" << endl;
	cout << "1.View Scoreboard" << endl;
	cout << "0.Back" << endl;
	cout << "\n************************************************\n" << endl;
	
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
		viewStudentScore(username, password, type);
		break;

	case '0':
		system("cls");
		Student_Menu(username, password, type);
		break;
	}

}

void Student_Schedule_Menu(char username[], char password[], int type)
{
	cout << "*******************SCHEDULE*******************\n" << endl;
	cout << "1.View Schedule" << endl;
	cout << "0.Back" << endl;
	cout << "\n**********************************************\n" << endl;

	char hotkey = _getch();

	while (hotkey != '0' && hotkey != '1')
	{
		hotkey = _getch();
		continue;
	}

	switch (hotkey)
	{
	case '1':
		system("cls");
		viewschedule(username, password, type);
		break;

	case '0':
		system("cls");
		Student_Menu(username, password, type);
		break;
	}
}

void Student_Option_Menu(char username[], char password[], int type)
{
	cout << "*******************OPTION*******************\n" << endl;
	cout << "1.View Profile" << endl;
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
		changePassword("student.txt", username, password);

		cout << "CHANGE PASSWORD SUCCESSFULLY!!" << endl;
		Sleep(2000);

		system("cls");
		Student_Option_Menu(username, password, type);
		break;
	case '0':

		system("cls");
		Student_Menu(username, password, type);
		break;
	}
}
