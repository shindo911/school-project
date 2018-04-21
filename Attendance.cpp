#include"Header.h"

void searchViewAttend(char username[], char password[], int type)
{
	string input;
	AttendList list;
	list.head = NULL;

	cout << "Enter course code of the attendance board: ";
	getline(cin, input);

	cout << "\nNOTE: 'x' represents for absence.\n" << endl;
	readAttend("Attendance\\" + input + ".csv", username, password, type, list);
	printAttend(username, password, type, list);

}

void readAttend(string path, char username[], char password[], int type, AttendList &list)
{
	fstream file(path);


	string trim;
	attendance* cur = NULL;

	if (file.is_open())
	{

		getline(file, trim, ',');
		getline(file, list.courseCode, ',');
		getline(file, trim);
		getline(file, trim);
		while (file.eof() != true)
		{
			attendance* a = new attendance;
			a->next = NULL;
			a->prev = NULL;

			getline(file, a->StudentID, ',');
			if (a->StudentID == "")
				break;
			getline(file, a->name, ',');
			getline(file, a->_class, ',');
			
			for (int i = 0; i < 10; i++)
			{
				if (i == 9)
					getline(file, a->student[i]);
				else
					getline(file, a->student[i], ',');
			}

			if (list.head == NULL)
			{
				list.head = a;

				cur = a;
			}
			else
			{
				cur->next = a;
				a->prev = cur;

				cur = a;
			}
		}
	}
	else
	{
		cout << "COURSE'S ATTENDANCE NOT FOUND!" << endl;
		Sleep(2000);

		system("cls");
		Staff_Attendance_Menu(username, password, type);
	}

	file.close();
}

void printAttend(char username[], char password[], int type, AttendList list)
{
	cout << "Cource code: " << list.courseCode << endl;

	cout << setw(12) << left << "Student ID";
	cout << setw(20) << left << "Name";
	cout << setw(11) << left << "Class";
	cout << setw(10) << left << "Lecture 1";
	cout << setw(10) << left << "Lecture 2";
	cout << setw(10) << left << "Lecture 3";
	cout << setw(10) << left << "Lecture 4";
	cout << setw(10) << left << "Lecture 5";
	cout << setw(10) << left << "Lecture 6";
	cout << setw(10) << left << "Lecture 7";
	cout << setw(10) << left << "Lecture 8";
	cout << setw(10) << left << "Lecture 9";
	cout << setw(10) << left << "Lecture 10" << endl;

	for (attendance* cur = list.head; cur != NULL; cur = cur->next)
	{
		cout << setw(12) << left << cur->StudentID;
		cout << setw(20) << left << cur->name;
		cout << setw(11) << left << cur->_class;
		for (int i = 0; i < 10; i++)
		{
			if (i == 9)
				cout << setw(10) << left << cur->student[i] << endl;
			else
				cout << setw(10) << left << cur->student[i];
		}
	}

	cout << "\n" << "Press Enter to back to Attendance Menu..." << endl;
	char hotkey = _getch();
	while (hotkey != 13)
	{
		hotkey = _getch();
		continue;
	}

	system("cls");
	Staff_Attendance_Menu(username, password, type);
}

void writeAttend(string path, char username[], char password[], int type, AttendList list)
{
	fstream file;

	file.open(path, ios_base::out);

	file << "Course code," << list.courseCode << ",,,,,,,,,," << endl;
	file << "Student ID,Name,Class,Lecture 1,Lecture 2,Lecture 3,Lecture 4,Lecture 5,Lecture 6,Lecture 7,Lecture 8,Lecture 9,Lecture 10" << endl;

	for (attendance* cur = list.head; cur != NULL; cur = cur->next)
	{
		file << cur->StudentID << ",";
		file << cur->name << ",";
		file << cur->_class << ",";
		for (int i = 0; i < 10; i++)
		{
			if (i == 9)
				file << cur->student[i] << endl;
			else
				file << cur->student[i] << ",";
		}
	}

	file.close();
}

void exportAttend(char username[], char password[], int type)
{
	string input, link, filename;

	cout << "Enter course code of attendance: ";
	getline(cin, input);

	AttendList list;
	list.head = NULL;

	readAttend("Attendance\\" + input + ".csv", username, password, type, list);

	cout << "Enter destination to export!" << endl;
	cout << "Enter path: ";
	getline(cin, link);
	cout << "Save as(filename, not include .csv): ";
	getline(cin, filename);

	writeAttend(link + filename + ".csv", username, password, type, list);

	fstream file;
	file.open(link + filename + ".csv");
	if (file.is_open() == true)
	{
		cout << "EXPORT SUCCESSFULLY!" << endl;
		Sleep(2000);

		system("cls");
		Staff_Attendance_Menu(username, password, type);
	}
	else
	{
		system("cls");
		cout << "ERROR!" << endl;
		Sleep(2000);

		system("cls");
		Staff_Attendance_Menu(username, password, type);
		return;
	}
	file.close();
}
