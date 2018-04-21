#include "Header.h"

void hidePassword(char pass[])
{

	char ch;
	int position = 0;
	while (1)
	{
		ch = _getch();
		if (ch == 13) break;
		else if (ch == 8)
		{
			if (position > 0)
			{
				position--;
				cout << "\b \b";
			}
		}
		else if (ch == 9)
		{
			continue;
		}
		else
		{
			pass[position] = ch;
			position++;
			cout << '*';
		}
	}
	pass[position] = '\0';
}

bool isStudent(char user[], char pass[])
{
	char username[50], password[50];
	ifstream studentUser("student.txt");
	while (!studentUser.eof())
	{
		studentUser.getline(username, 50, '\n');
		studentUser.getline(password, 50, '\n');
		if (strcmp(user, username) == 0 && strcmp(pass, password) == 0) return true;
	}
	return false;
}

bool isLecturer(char user[], char pass[])
{
	char username[50], password[50];
	ifstream lecturerUser("teacher.txt");
	while (!lecturerUser.eof())
	{
		lecturerUser.getline(username, 50, '\n');
		lecturerUser.getline(password, 50, '\n');
		if (strcmp(user, username) == 0 && strcmp(pass, password) == 0) return true;
	}
	return false;
}

bool isStaff(char user[], char pass[])
{
	char username[50], password[50];
	ifstream staffUser("staff.txt");

	while (!staffUser.eof())
	{
		staffUser.getline(username, 50, '\n');
		staffUser.getline(password, 50, '\n');
		if (strcmp(user, username) == 0 && strcmp(pass, password) == 0) return true;
	}
	return false;
}

bool isExist(char user[], char pass[])
{
	if (isStudent(user, pass) || isStaff(user, pass) || isLecturer(user, pass))
		return true;
	return false;
}

void Login(char Username[], char Password[], int &type)
{
	int wrong = 0;
	//char login_un[50], login_pw[50];

	do
	{
		logo();
		time();
		cout << "Enter Username: ";
		cin.getline(Username, 50);
		cout << "Enter Password: ";
		hidePassword(Password);
		loading();
		if (!isExist(Username, Password))
		{
			cout << "Username or Password is wrong!!\n";
			_getch();
			wrong++;
			system("cls");
		}
		if (wrong == 5)
		{
			cout << "Too many login attempts! The program will now terminate." << endl;
			return;
		}
	} while (!isExist(Username, Password));
	system("cls");
	checkFirstTime("student.txt", Username, Password);
	//cout << hashPassword(login_un, login_pw) << endl;
	if (isStudent(Username, Password))
		type = 0;
	else if (isStaff(Username, Password))
		type = 1;
	else if (isLecturer(Username, Password))
		type = 2;
}
