#include "Header.h"

void Staff_Menu(char username[], char password[], int type)
{
	cout << "*******************MAIN MENU*******************\n" << endl;
	cout << "INSTRUCTION: " << "press number to choose your action.\n" << endl;
	cout << "1.STUDENT" << endl;
	cout << "2.CLASS" << endl;
	cout << "3.COURSE" << endl;
	cout << "4.SCHEDULE" << endl;
	cout << "5.ATTENDANCE" << endl;
	cout << "6.SCOREBOARD" << endl;
	cout << "7.OPTION" << endl;
	cout << "8.LOG OUT" << endl;
	cout << "0.EXIT" << endl;
	cout << "\n" << "***********************************************" << endl;

	char hotkey = _getch();

	while (hotkey != '0' && hotkey != '1' && hotkey != '2' && hotkey != '3' && hotkey != '4' && hotkey != '5' && hotkey != '6' && hotkey != '7' && hotkey != '8')
	{
		hotkey = _getch();
		continue;
	}

	switch (hotkey)
	{
	case '1':
		system("cls");
		Staff_Student_Menu(username, password, type);
		break;
	case '2':
		system("cls");
		Staff_Class_Menu(username, password, type);
		break;
	case '3':
		system("cls");
		Staff_Course_Menu(username, password, type);
		break;
	case '4':
		system("cls");
		Staff_Schedule_Menu(username, password, type);
		break;
	case '5':
		system("cls");
		Staff_Attendance_Menu(username, password, type);
		break;

	case '6':
		system("cls");
		Staff_Scoreboard_Menu(username, password, type);
		break;
	case '7':
		system("cls");
		Staff_Option_Menu(username, password, type);
		break;
	case '8':
		system("cls");
		Access();
		break;

	case '0':
		system("cls");
		//exit(EXIT_FAILURE);
		return;
	}
}

void Staff_Student_Menu(char username[], char password[], int type)
{
	cout << "*******************STUDENT*******************\n" << endl;
	cout << "1.Add Student" << endl;
	cout << "2.Edit Student" << endl;
	cout << "3.Remove Student" << endl;
	cout << "4.Move Student" << endl;
	cout << "0.Back" << endl;
	cout << "\n*********************************************\n" << endl;

	char hotkey = _getch();

	while (hotkey != '0' && hotkey != '1' && hotkey != '2' && hotkey != '3' && hotkey != '4')
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
		cout << "Press '0' to back to student menu" << endl;

		hotkey_temp = _getch();
		while (hotkey_temp != '0')
		{
			hotkey_temp = _getch();
			continue;
		}

		if (hotkey_temp == '0')
		{
			system("cls");
			Staff_Student_Menu(username, password, type);
		}
	case '1':
		system("cls");
		addStudent(username, password, type);
		break;

	case '2':
		system("cls");
		editStudent(username, password, type);
		break;

	case '3':
		system("cls");
		removeStudent(username, password, type);
		break;

	case '4':
		system("cls");
		moveStudent(username, password, type);
		break;

	case '0':
		system("cls");
		Staff_Menu(username, password, type);
		break;
	}
}

void Staff_Class_Menu(char username[], char password[], int type)
{
	cout << "*******************CLASS*******************\n" << endl;
	cout << "1.Import Class" << endl;
	cout << "2.New Class" << endl;
	cout << "3.View Class" << endl;
	cout << "4.View List of Classes" << endl;
	cout << "0.Back" << endl;
	cout << "\n*******************************************\n" << endl;

	string input;
	Class _class;
	_class.head = NULL;
	char hotkey = _getch();

	while (hotkey != '0' && hotkey != '1' && hotkey != '2' && hotkey != '3' && hotkey != '4')
	{
		hotkey = _getch();
		continue;
	}

	switch (hotkey)
	{
	case '1':
		system("cls");
		cout << "Enter file's link. File must be csv file." << "\n" << "Link: ";
		getline(cin, input);

		Import_Class(input, _class, username, password, type);
		Write_Class(_class.name + ".csv", _class);

		system("cls");
		Staff_Class_Menu(username, password, type);
		break;

	case '2':
		system("cls");
		cout << "Enter new class: " << endl;
		getline(cin, input);

		Add_Class(input);

		system("cls");
		Staff_Class_Menu(username, password, type);
		break;
	case '3':
		system("cls");
		View_Class(username, password, type);
		break;
	case '4':
		system("cls");
		Print_Class_List(username, password, type);
		break;

	case '0':
		system("cls");
		Staff_Menu(username, password, type);
		break;
	}
}

void Staff_Course_Menu(char username[], char password[], int type)
{
	cout << "*******************COURSE*******************\n" << endl;
	cout << "1.Import Course" << endl;
	cout << "2.Add Course" << endl;
	cout << "3.Edit Course" << endl;
	cout << "4.Remove Course" << endl;
	cout << "5.View Course List" << endl;
	cout << "0.Back" << endl;
	cout << "\n********************************************\n" << endl;

	char hotkey = _getch();

	while (hotkey != '0' && hotkey != '1' && hotkey != '2' && hotkey != '3' && hotkey != '4'&& hotkey != '5')
	{
		hotkey = _getch();
		continue;
	}

	courseList list;
	list.head = NULL;
	string input;

	switch (hotkey)
	{
	case '1':
		system("cls");


		importCourse(list);

		system("cls");
		Staff_Course_Menu(username, password, type);
		break;

	case '2':
		system("cls");

		writeCourse(createCourse());

		system("cls");
		cout << "COURSE ADDED SUCCESSFULLY!" << endl;
		Sleep(2000);

		system("cls");
		Staff_Course_Menu(username, password, type);
		break;

	case '3':
		system("cls");
		editCourse(list);
		system("cls");
		Staff_Course_Menu(username, password, type);
		break;
	case '4':
		system("cls");
		cout << "Enter course you want to remove: ";
		getline(cin, input);

		removeCourse(input, list);

		system("cls");
		Staff_Course_Menu(username, password, type);
		break;

	case '5':
		system("cls");

		printCourseList(list);

		system("cls");
		Staff_Course_Menu(username, password, type);
		break;

	case '0':
		system("cls");
		Staff_Menu(username, password, type);
		break;
	}
}

void Staff_Schedule_Menu(char username[], char password[], int type)
{
	cout << "*******************SCHEDULE*******************\n" << endl;
	cout << "1.Import Schedule" << endl;
	cout << "2.Add Schedule" << endl;
	cout << "3.Edit Schedule" << endl;
	cout << "4.Remove Schedule" << endl;
	cout << "5.View Schedule List" << endl;
	cout << "0.Back" << endl;
	cout << "\n**********************************************\n" << endl;

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
		import_schedule(username, password, type);

		break;
	case '2':
		system("cls");
		add_schedule(username, password, type);

		break;
	case '3':
		system("cls");
		edit_schedule(username, password, type);

		break;
	case '4':
		system("cls");
		remove_schedule(username, password, type);

		break;
	case '5':
		system("cls");
		view_schedule_list(username, password, type);
		break;

	case '0':
		system("cls");
		Staff_Menu(username, password, type);
		break;
	}

}

void Staff_Attendance_Menu(char username[], char password[], int type)
{
	cout << "*******************ATTENDANCE*******************\n" << endl;
	cout << "1.Search & View Attendance" << endl;
	cout << "2.Export Attendance" << endl;
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
		searchViewAttend(username, password, type);
		break;

	case '2':
		system("cls");
		exportAttend(username, password, type);
		break;

	case '0':
		system("cls");
		Staff_Menu(username, password, type);
		break;
	}
}

void Staff_Scoreboard_Menu(char username[], char password[], int type)
{
	cout << "*******************SCOREBOARD*******************\n" << endl;
	cout << "1.Search & View Scoreboard" << endl;
	cout << "2.Export Scoreboard" << endl;
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
		searchViewScore(username, password, type);
		break;

	case '2':
		system("cls");
		exportScore(username, password, type);
		break;

	case '0':
		system("cls");
		Staff_Menu(username, password, type);
		break;
	}
}

void Staff_Option_Menu(char username[], char password[], int type)
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
		changePassword("staff.txt", username, password);

		cout << "CHANGE PASSWORD SUCCESSFULLY!!" << endl;
		Sleep(2000);

		system("cls");
		Staff_Option_Menu(username, password, type);
		break;

	case '0':
		system("cls");
		Staff_Menu(username, password, type);
		break;
	}
}
