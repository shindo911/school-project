#include "Header.h"

// imports from file a class.
void Import_Class(string path, Class &_class, char username[], char password[], int type)
{
	// opens file to load, check if it's available or not
	fstream File;
	File.open(path, ios_base::in);
	if (File.fail() == true)
	{
		cout << "Invalid Access!" << endl;
		Staff_Class_Menu(username, password, type);
		return;
	}

	_class.number = 0;
	getline(File, _class.name, ',');
	File.seekg(43, File.cur);

	Student* cur = NULL;

	while (File.eof() != true)
	{
		Student* p = new Student;
		getline(File, p->No, ',');
		if (p->No == "")
		{
			cur->next = NULL;
			break;
		}
		getline(File, p->ID, ',');
		getline(File, p->Name, ',');
		getline(File, p->email, ',');
		getline(File, p->phone, ',');
		getline(File, p->username);


		if (_class.head == NULL)
		{
			_class.head = p;
			cur = p;
		}
		else
		{
			cur->next = p;
			p->prev = cur;
			cur = p;
		}
		_class.number++;
	}

	File.close();

	//write into class list
	File.open("Class\\Class_List.txt",ios_base::out | ios_base::app);

	File << _class.name << ",";
	File << _class.number << endl;

	File.close();

	//write into account
	File.open("Student.txt", ios_base::app);
	if (File.is_open() == false)
	{
		cout << "ERROR!" << endl;
		Sleep(2000);
		system("cls");
		Staff_Student_Menu(username, password, type);
		return;
	}

	for (Student* cur = _class.head; cur != NULL; cur = cur->next)
	{
		File << "\n" << cur->username << endl;
		File << cur->username;
	}
	File.close();
}

// add a new empty class
void Add_Class(string path)
{
	fstream File;
	_mkdir("Class");
	File.open("Class\\Class_List.txt", ios_base::in);
	if (!File)
	{ }
	else
	{
		File.seekp(0, File.beg);

		while (File.eof() != true)
		{
			string temp;
			getline(File, temp, ',');
			File.ignore(5, '\n');
			if (temp == path)
			{
				system("cls");
				cout << "Class has already exist." << endl;
				Sleep(2000);

				File.close();
				return;
			}
		}
	}
	File.close();

	File.open("Class\\" + path + ".csv", ios_base::out);
	File << path << ",,,,,," << "\n" << 0 << endl;
	File.close();


	File.open("Class\\Class_List.txt", ios_base::app);
	File << path << "," << "0" << endl;
	File.close();

	system("cls");
	cout << "ADDED SUCCESSFULLY!" << endl;
	Sleep(2000);

}

// View list of students in a class
void View_Class(char username[], char password[], int type)
{
	string input;
	cout << "Enter class: ";
	getline(cin, input);

	fstream file;
	file.open("Class\\" + input + ".csv");
	if (file.is_open() == false)
	{
		system("cls");
		cout << "CLASS IN UNAVAILABLE!" << endl;
		system("cls");

		Staff_Class_Menu(username, password, type);
		return;
	}
	else
	{
		Class _class;
		_class.head = NULL;

		system("cls");
		Read_Class("Class\\" + input + ".csv", _class, username, password, type);
		Print_Class(_class, username, password, type);

		system("cls");
		Staff_Class_Menu(username, password, type);
		return;
	}
}

// write a class to file
void Write_Class(string path, Class _class)
{
	ofstream Fout;
	_mkdir("Class");
	Fout.open("Class\\" + path, ios_base::out);
	Fout << _class.name << ",,,,," << endl;
	Fout << _class.number << endl;
	Fout << "No,ID,Fullname,Email,Phone,Username" << endl;
	Student* cur = new Student;
	cur = _class.head;

	while (cur != NULL)
	{
		Fout << cur->No << ",";
		Fout << cur->ID << ",";
		Fout << cur->Name << ",";
		Fout << cur->email << ",";
		Fout << cur->phone << ",";
		Fout << cur->username << endl;

		cur = cur->next;
	}

	system("cls");
	cout << "IMPORT SUCCESSFULLY!!" << endl;
	Sleep(2000);
	Fout.close();
}

// read a class csv file
void Read_Class(string path, Class &_class,char username[], char password[], int type)
{
	ifstream Fin;
	Fin.open(path, ios_base::in);

	getline(Fin, _class.name, ',');
	Fin.seekg(6, Fin.cur);
	Fin >> _class.number;

	if (_class.number == 0)
	{
		_class.head = NULL;
		_class.next = NULL;
		_class.prev = NULL;
		return;
	}
	Fin.seekg(39, Fin.cur);

	Student* cur = NULL;

	while (Fin.eof() != true)
	{
		Student* p = new Student;
		getline(Fin, p->No, ',');
		if (p->No == "")
		{
			cur->next = NULL;
			break;
		}
		getline(Fin, p->ID, ',');
		getline(Fin, p->Name, ',');
		getline(Fin, p->email, ',');
		getline(Fin, p->phone, ',');
		getline(Fin, p->username);


		if (_class.head == NULL)
		{
			_class.head = p;
			cur = p;
		}
		else
		{
			cur->next = p;
			p->prev = cur;
			cur = p;
		}
	}
	Fin.close();
}

// print a class to the screen
void Print_Class(Class _class, char username[], char password[], int type)
{
	cout << "Class: " << _class.name << endl;
	cout << "Number of student: " << _class.number << "\n" << endl;

	cout << setw(3) << left << "No";
	cout << setw(8) << left << " ID";
	cout << setw(20) << left << "Fullname";
	cout << setw(23) << left << "Email";
	cout << setw(13) << left << "Phone";
	cout << setw(8) << left << "Username" << endl;

	cout << setfill('=');
	cout << setw(80) << "=" << endl;
	cout << setfill(' ');

	for (Student* cur = _class.head; cur != NULL; cur = cur->next)
	{
		cout << setw(3) << left << cur->No;
		cout << setw(8) << left << cur->ID;
		cout << setw(20) << left << cur->Name;
		cout << setw(23) << left << cur->email;
		cout << setw(13) << left << cur->phone;
		cout << setw(8) << left << cur->username << endl;
	}

	cout << "\n" << "Press Enter to back to Class Menu..." << endl;
	char hotkey = _getch();
	while (hotkey != 13)
	{
		hotkey = _getch();
		continue;
	}
}

// print the list of classes
void Print_Class_List(char username[], char password[], int type)
{
	ifstream Fin;
	Fin.open("Class\\Class_List.txt", ios_base::in);

	ClassList list;
	list._class = NULL;
	Class* cur = NULL;

	while (Fin.eof() != true)
	{
		Class* p = new Class;

		getline(Fin, p->name, ',');
		if (p->name == "\n")
		{
			break;
		}
		Fin >> p->number;
		Fin.seekg(1, Fin.cur);

		p->next = NULL;
		p->prev = NULL;
		if (list._class == NULL)
		{
			list._class = p;
			cur = p;
		}
		else
		{
			cur->next = p;
			p->prev = cur;
			cur = p;
		}
	}
	cout << setw(10) << left << "Class";
	cout << setw(10) << left << "Number of Student" << endl;

	cout << setfill('=');
	cout << setw(30) << "=" << endl;
	cout << setfill(' ');

	for (Class* cur = list._class; cur != NULL; cur = cur->next)
	{ 
		cout << setw(10) << left << cur->name;
		cout << setw(10) << left << cur->number;
	}

	cout << "\n" << "Press Enter to back to Class Menu..." << endl;
	char hotkey = _getch();
	while (hotkey != 13)
	{
		hotkey = _getch();
		continue;
	}
	system("cls");
	Staff_Class_Menu(username, password, type);
	Fin.close();
}

