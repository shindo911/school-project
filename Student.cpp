#include "Header.h"

void addStudent(char username[], char password[], int type)
{
	string _class;
	Student *new_student = new Student;
	cout << "ENTER INFORMATION OF STUDENT" << endl;
	cout << "Enter Student's ID: ";
	getline(cin, new_student->ID);
	cout << "Enter Student's Name: ";
	getline(cin, new_student->Name);
	cout << "Enter Student's Class: ";
	getline(cin, _class);
	cout << "Enter Student's phone number: ";
	getline(cin, new_student->phone);
	new_student->username = new_student->ID;
	new_student->email = new_student->ID + "@hcmus.edu.vn";

	new_student->next = NULL;

	fstream file;
	file.open("Class\\" + _class + ".csv", ios_base::out | ios_base::in);

	if (file.is_open() == false)
	{
		cout << "CLASS IS UNAVAILABLE!!" << endl;
		Sleep(2000);
		system("cls");
		Staff_Student_Menu(username, password, type);
		return;
	}
	
	//write into class
	Class update;
	update.head = NULL;
	Read_Class("Class\\" + _class + ".csv", update, username, password, type);
	update.number += 1;
	for (Student* cur = update.head; cur != NULL; cur = cur->next)
	{
		if (cur->Name == new_student->Name)
		{
			cout << "STUDENT'S ALREADY EXISTED!" << endl;
			Sleep(2000);
			system("cls");
			Staff_Student_Menu(username, password, type);
			return;
		}
		if (cur->next == NULL)
		{
			cur->next = new_student;
			new_student->prev = cur;
			int n1 = atoi(new_student->No.c_str());
			int n2 = atoi(cur->No.c_str());
			n1 = n2 + 1;
			new_student->No = to_string(n1);
			break;
		}
	}
	Write_Class(_class + ".csv", update);
	file.close();

	//write into user file
	file.open("User\\Student.csv", ios_base::in);
	if (file.is_open() == false)
	{
		cout << "ERROR!" << endl;
		Sleep(2000);
		system("cls");
		Staff_Student_Menu(username, password, type);
		return;
	}

	string trim;
	getline(file, trim);
	getline(file, trim);

	int num = 0;
	User user;

	while (file.eof() == false)
	{
		getline(file, trim);
		num += 1;
	}

	file.close();

	file.open("User\\Student.csv", ios_base::app);
	if (file.is_open() == false)
	{
		cout << "ERROR!" << endl;
		Sleep(2000);
		system("cls");
		Staff_Student_Menu(username, password, type);
		return;
	}

	new_student->No = to_string(num);

	file << new_student->No << ",";
	file << new_student->username << ",";
	file << new_student->Name << ",";
	file << new_student->email << ",";
	file << new_student->phone << ",";
	file << 1 << ",";
	file << _class << endl;
	   
	file.close();

	//write into class list
	updateClassList(update);
	//write into account
	file.open("Student.txt", ios_base::app);
	if (file.is_open() == false)
	{
		cout << "ERROR!" << endl;
		Sleep(2000);
		system("cls");
		Staff_Student_Menu(username, password, type);
		return;
	}

	file << "\n" << new_student->username << endl;
	file << new_student->username;

	file.close();

	cout << "ADDED SUCESSFULLY!" << endl;
	Sleep(2000);
	system("cls");
	Staff_Student_Menu(username, password, type);
}

void updateClassList(Class p)
{
	string text, num;
	fstream ifile("Class\\Class_List.txt", ios_base::in);
	fstream ofile("Class\\temp.txt", ios_base::out);
	while (ifile.eof() != true)
	{
		getline(ifile, text, ',');
		if (text == "") break;
		getline(ifile, num);
		if (text != p.name)
		{
			ofile << text << "," << num << endl;
		}
		else
		{
			ofile << text << "," << p.number << endl;
		}
	}
	ifile.close();
	ofile.close();

	fstream fo("Class\\Class_List.txt", ios_base::out);
	fstream fi("Class\\temp.txt", ios_base::in);
	while (fi.eof() != true)
	{
		getline(fi, text);
		if (text == "") break;
		fo << text << endl;
	}
	fo.close();
	fi.close();
	remove("Class\\temp.txt");
}

void editStudent(char username[], char password[], int type)
{
	string ID, _class;
	cout << "Enter student's ID you want to edit: ";
	getline(cin, ID);
	cout << "Enter student's class: ";
	getline(cin, _class);
	system("cls");

	// read class contain student
	Class edit;
	edit.head = NULL;
	Read_Class("Class\\" + _class + ".csv", edit, username, password, type);

	// read student user list
	UserList list;
	readUserStudentList(list, username, password, type);

	Student* edit_student = NULL;
	for (Student* cur = edit.head; cur != NULL; cur = cur->next)
	{
		if (cur->ID == ID)
		{
			edit_student = cur;
			break;
		}
	}

	if (edit_student == NULL)
	{
		system("cls");
		cout << "STUDENT IS NOT EXIST!" << endl;
		system("cls");
		Staff_Student_Menu(username, password, type);
		return;
	}

	User* user_edit_student = NULL;
	for (User* cur = list.head; cur != NULL; cur = cur->next)
	{
		if (cur->username == ID)
		{
			user_edit_student = cur;
			break;
		}
	}
	// Start editing
	char confirm = 'Y';
	while (confirm == 'Y' || confirm == 'y')
	{
		cout << "Choose category you want to make change(enter number):" << endl;
		cout << "1. Student ID: " << edit_student->ID << endl;
		cout << "2. Student's name: " << edit_student->Name << endl;
		cout << "3. Email: " << edit_student->email << endl;
		cout << "4. Phone Number: " << edit_student->phone << endl;

		string input;

		cout << "Enter: ";
		getline(cin, input);
		 while (input != "1" && input != "2" && input != "3" && input != "4")
			 getline(cin, input);

		string new_add;
		if (input == "1")
		{
			cout << "New Student ID: ";
			getline(cin, new_add);
			edit_student->ID = new_add;
		}
		else if (input == "2")
		{
			cout << "New Student's Name: ";
			getline(cin, new_add);
			edit_student->Name = new_add;
			user_edit_student->name = new_add;
		}
		else if (input == "3")
		{
			cout << "New Email: ";
			getline(cin, new_add);
			edit_student->email = new_add;
			user_edit_student->email = new_add;
		}
		else if (input == "4")
		{
			cout << "New Phone Number: ";
			getline(cin, new_add);
			edit_student->phone = new_add;
			user_edit_student->phone = new_add;
		}

		cout << "\n";
		cout << "1. Student ID: " << edit_student->ID << endl;
		cout << "2. Student's name: " << edit_student->Name << endl;
		cout << "3. Email: " << edit_student->email << endl;
		cout << "4. Phone Number: " << edit_student->phone << endl;

		cout << "\nDo you want to edit more?" << "\n" << "Press[Y/N]: ";
		cin >> confirm;
		cin.ignore();
		while (confirm != 'Y' && confirm != 'N' && confirm != 'y' && confirm != 'n')
		{
			cin >> confirm;
			cin.ignore();
		}
	}

	Write_Class(_class + ".csv", edit);
	Write_UserList(list, username, password, type);

	cout << "EDITED SUCESSFULLY!" << endl;
	Sleep(2000);
	system("cls");
	Staff_Student_Menu(username, password, type);
}

void removeStudent(char username[], char password[], int type)
{
	string ID, _class;
	cout << "Enter student's ID you want to delete: ";
	getline(cin, ID);
	cout << "Enter student's class: ";
	getline(cin, _class);

	// read and update class contain removed student
	Class remove;
	remove.head = NULL;
	Read_Class("Class\\" + _class + ".csv", remove, username, password, type);

	fstream file;
	file.open("Class\\" + _class + ".csv",ios_base::out);

	if (file.is_open() == false)
	{
		cout << "CLASS IS UNAVAILABLE!!" << endl;
		Sleep(2000);
		system("cls");
		Staff_Student_Menu(username, password, type);
		return;
	}

	remove.number--;
	file << remove.name << ",,,,," << endl;
	file << remove.number << endl;
	file << "No,ID,Fullname,Email,Phone,Username" << endl;

	for (Student* cur = remove.head; cur != NULL; cur = cur->next)
	{
		if (cur->ID == ID)
		{
			for (Student* No = cur->next; No != NULL; No = No->next)
			{
				No->No = No->prev->No;
			}
		}
		else
		{
			file << cur->No << ",";
			file << cur->ID << ",";
			file << cur->Name << ",";
			file << cur->email << ",";
			file << cur->phone << ",";
			file << cur->username << endl;
		}
	}

	file.close();

	// read and update class list
	remove.number--;
	updateClassList(remove);

	// read and update student user list
	UserList StudentList;
	readUserStudentList(StudentList, username, password, type);

	file.open("User\\Student.csv", ios_base::out);
	if (file.is_open() == false)
	{
		cout << "ERROR!" << endl;
		Sleep(2000);
		system("cls");
		Staff_Student_Menu(username, password, type);
		return;
	}

	int No = 1;
	file << "User,,,,,," << endl;
	file << "No,Username,Name,Email,Phone,Type,Class" << endl;

	for (User* cur = StudentList.head; cur != NULL; cur = cur->next)
	{
		if (cur->username == ID)
		{
			continue;
		}
		else
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
	}

	file.close();

	//updateUserAccount(ID);

	cout << "REMOVED SUCESSFULLY!" << endl;
	Sleep(2000);
	system("cls");
	Staff_Student_Menu(username, password, type);
}

void updateUserAccount(string ID)
{
	string text, pass;
	fstream ifile("student.txt", ios_base::in);
	fstream ofile("temp.txt", ios_base::out);
	getline(ifile, text, ',');
	getline(ifile, pass);
	while (ifile.eof() != true)
	{
		if (text != ID)
		{
			ofile << text << "," << pass << endl;
		}
		getline(ifile, text, ',');
		if (text == "") break;
		getline(ifile, pass);
	}
	ifile.close();
	ofile.close();

	fstream fo("student.txt", ios_base::out);
	fstream fi("temp.txt", ios_base::in);
	while (fi.eof() != true)
	{
		getline(fi, text);
		if (text == "") break;
		fo << text << endl;
	}
	fo.close();
	fi.close();
	remove("temp.txt");
}

void readUserStudentList(UserList &StudentList, char username[], char password[], int type)
{
	fstream file;
	file.open("User\\Student.csv", ios_base::in);
	if (file.is_open() == false)
	{
		cout << "ERROR!" << endl;
		Sleep(2000);
		system("cls");
		Staff_Student_Menu(username, password, type);
		return;
	}

	StudentList.type = 1;
	StudentList.head = NULL;

	string trim;
	getline(file, trim);
	getline(file, trim);

	User* cur = NULL;
	while(file.eof() == false)
	{
		getline(file, trim, ',');
		if (trim == "")
		{
			break;
		}
		User* p = new User;
		getline(file, p->username, ',');
		getline(file, p->name, ',');
		getline(file, p->email, ',');
		getline(file, p->phone, ',');
		getline(file, p->type, ',');
		getline(file, p->_class);
		p->next = NULL;
		p->prev = NULL;

		if (StudentList.head == NULL)
		{
			StudentList.head = p;
			cur = p;
		}
		else
		{
			cur->next = p;
			p->prev = cur;
			cur = p;
		}
	}

	file.close();
}

void moveStudent(char username[], char password[], int type)
{
	string ID, old_class, new_class;
	cout << "Enter student's ID you want to move: ";
	getline(cin, ID);
	cout << "Enter student's recent class: ";
	getline(cin, old_class);
	cout << "Enter student's new class: ";
	getline(cin, new_class);

	//Read from old class and delete student
	Class remove;
	remove.head = NULL;
	Read_Class("Class\\" + old_class + ".csv", remove, username, password, type);

	fstream file;
	file.open("Class\\" + old_class + ".csv", ios_base::out);
	if (file.is_open() == false)
	{
		cout << "CLASS IS UNAVAILABLE!!" << endl;
		Sleep(2000);
		system("cls");
		Staff_Student_Menu(username, password, type);
		return;
	}

	file << remove.name << ",,,,," << endl;
	remove.number--;
	file << remove.number << endl;
	file << "No,ID,Fullname,Email,Phone,Username" << endl;

	Student* transfer = new Student;
	for (Student* cur = remove.head; cur != NULL; cur = cur->next)
	{
		if (cur->ID == ID)
		{
			string temp = cur->No;
			string temp1;
			for (Student* No = cur->next; No != NULL; No = No->next)
			{
				temp1 = No->No;
				No->No = temp;
				temp = temp1;
			}
			transfer->ID = cur->ID;
			transfer->Name = cur->Name;
			transfer->email = cur->email;
			transfer->phone = cur->phone;
			transfer->username = cur->username;
			transfer->next = NULL;
			transfer->prev = NULL;
		}
		else
		{
			file << cur->No << ",";
			file << cur->ID << ",";
			file << cur->Name << ",";
			file << cur->email << ",";
			file << cur->phone << ",";
			file << cur->username << endl;
		}
	}

	updateClassList(remove);
	file.close();

	//Write to new class
	Class add;
	add.head = NULL;
	Read_Class("Class\\" + new_class + ".csv", add, username, password, type);

	file.open("Class\\" + new_class + ".csv", ios_base::out);
	if (file.is_open() == false)
	{
		cout << "CLASS IS UNAVAILABLE!!" << endl;
		Sleep(2000);
		system("cls");
		Staff_Student_Menu(username, password, type);
		return;
	}

	add.number += 1;
	for (Student* cur = add.head; cur != NULL; cur = cur->next)
	{
		if (cur->Name == transfer->Name)
		{
			cout << "STUDENT'S ALREADY EXISTED!" << endl;
			Sleep(2000);
			system("cls");
			Staff_Student_Menu(username, password, type);
			return;
		}
		if (cur->next == NULL)
		{
			cur->next = transfer;
			transfer->prev = cur;
			int n1 = atoi(transfer->No.c_str());
			int n2 = atoi(cur->No.c_str());
			n1 = n2 + 1;
			transfer->No = to_string(n1);
			break;
		}
	}
	updateClassList(add);
	Write_Class(new_class + ".csv", add);
	file.close();


	UserList list;
	readUserStudentList(list, username, password, type);

	for (User* cur = list.head; cur != NULL; cur = cur->next)
	{
		if (cur->username == ID)
		{
			cur->_class = new_class;
			break;
		}
	}

	Write_UserList(list, username, password, type);

	cout << "MOVED SUCESSFULLY!" << endl;
	Sleep(2000);
	system("cls");
	Staff_Student_Menu(username, password, type);
}
