#include "Header.h"

void Print_User(char username[], char password[], int type)
{
	ifstream Fin;
	if (type == 0)
		Fin.open("User\\Student.csv", ios_base::in);
	else if (type == 1)
		Fin.open("User\\Staff.csv", ios_base::in);
	else if (type == 2)
		Fin.open("User\\Lecturer.csv", ios_base::in);

	if (Fin.fail() == true)
	{
		cout << "Invalid Access!" << endl;
		return;
	}

	string trim;
	getline(Fin, trim);
	getline(Fin, trim);
	User user;
	while (Fin.eof() == false)
	{
		getline(Fin, trim, ',');
		getline(Fin, trim, ',');
		if (trim == username)
		{
			user.username = trim;
			getline(Fin, user.name, ',');
			getline(Fin, user.email, ',');
			getline(Fin, user.phone, ',');
			getline(Fin, user.type, ',');
			getline(Fin, user._class);
			break;
		}
		else
		{
			getline(Fin, trim, ',');
			getline(Fin, trim, ',');
			getline(Fin, trim, ',');
			getline(Fin, trim, ',');
			getline(Fin, trim);
		}
	}

	Print_Info(user, username, password, type);
}

void Print_Info(User user, char username[], char password[], int type)
{
	cout << "Username: " << user.username << endl;
	cout << "Name: " << user.name << endl;
	cout << "Class: " << user._class << endl;
	cout << "Email: " << user.email << endl;
	cout << "Phone Number: " << user.phone << endl;
	cout << "Type: " << user.type << endl;

	cout << "\n" << "Press Enter to back to Option Menu..." << endl;
	char hotkey = _getch();
	while (hotkey != 13)
	{
		hotkey = _getch();
		continue;
	}
	system("cls");

	if (type == 0)
		Student_Menu(username, password, type);
	else if (type == 1)
		Staff_Menu(username, password, type);
	else if (type == 2)
		Lecturer_Menu(username, password, type);
}

void Write_UserList(UserList user, char username[], char password[], int type)
{
	fstream file;
	if (type == 1)
		file.open("User\\Student.csv", ios_base::out);
	else if (type == 0)
		file.open("User\\Staff.csv", ios_base::out);
	else
		file.open("User\\Lecturer.csv", ios_base::out);

	int No = 1;
	file << "User,,,,,," << endl;
	file << "No,Username,Name,Email,Phone,Type,Class" << endl;

	for (User* cur = user.head; cur != NULL; cur = cur->next)
	{
		file << No << ",";
		file << cur->username << ",";
		file << cur->name << ",";
		file << cur->email << ",";
		file << cur->phone << ",";
		file << cur->type << ",";
		file << cur->_class << endl;
		No++;
	}

	file.close();
}

void checkFirstTime(const char path[], char Username[], char Password[])
{
	if (isStudent(Username, Password) && strcmp(Password, Username) == 0)
	{
		cout << "Because this is your very first time to login." << endl;
		cout << "We suggest you should change your password" << endl;
		_getch();
		changePassword(path, Username, Password);
	}
}

void changePassword(const char path[], char username[], char password[])
{
	char tempPass[100], newPass[100];
	do
	{
		cout << "Enter old password: ";
		hidePassword(tempPass);
		if (strcmp(password, tempPass) != 0)
		{
			cout << "Password is wrong!!" << endl;
			_getch();
		}
		system("cls");
	} while (strcmp(password, tempPass) != 0);
	do
	{
		do
		{
			cout << "Enter new password: ";
			hidePassword(newPass);
			if (strcmp(newPass, username) == 0)
			{
				cout << "\nYour new password shouldn't  be the same as your Username\n" << endl;
				system("cls");
				break;
			}
			cout << endl;
			cout << "Confirm new password : ";
			hidePassword(tempPass);
			if (strcmp(newPass, tempPass) != 0)
			{
				cout << "Password mismatch!!" << endl;
				_getch();
			}
			system("cls");
		} while (strcmp(newPass, tempPass) != 0);
	} while (strcmp(newPass, username) == 0);
	string un;
	string pw;
	ifstream ifile(path);
	ofstream ofile("temp.txt");
	while (!ifile.eof())
	{
		getline(ifile, un);
		getline(ifile, pw);
		if (strcmp(username, un.c_str()) == 0)
		{
			ofile << un << "\n";
			ofile.write(newPass, strlen(newPass));
			ofile.write("\n", 1);
			strcpy(password, newPass);
		}
		else
		{
			ofile << un << "\n";
			if (ifile.eof() == true)
				ofile << pw;
			else
				ofile << pw << "\n";
		}
	}
	ifile.close();
	ofile.close();
	remove(path);
	rename("temp.txt", path);
}