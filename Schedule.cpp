#include "Header.h"

void import_schedule(char username[], char password[], int type)
{
	string input; 
	string confirm = "Y";

	while (confirm == "Y" || confirm == "y")
	{
		cout << "Enter course's schedule link. File must be a csv file." << endl;
		cout << "Enter link: ";

		getline(cin,input);

		scheduleList list;
		list.head = NULL;
		schedule* cur = NULL;
		schedule*p = new schedule;

		read_schedule(input, p);

		if (list.head == NULL)
		{
			list.head = p;

			cur = p;
		}
		else
		{
			cur->next = p;
			p->prev = cur;
			cur = p;
		}
		write_schedule(p);

		count_scheduleNum(p);
		write_schedule_list(p->course_name, p->session_num);
		//CHECK IMPORTED
		fstream file;
		file.open("Schedule\\" + p->course_name + ".csv");
		if (file.is_open() == false)
		{
			system("cls");
			cout << "IMPORTED ERROR!! PLEASE CHECK IF THE FILE IS AVAILABLE OR FILE LINK IS CORRECT." << endl;
			cout << "ERROR REPORT: " << input << endl;

			cout << "Press Enter to import again..." << endl;

			char hotkey = _getch();

			while (hotkey != 13)
			{
				hotkey = _getch();
				continue;
			}
			import_schedule(username, password, type);
			return;
		}
		else
		{
			cout << "IMPORTED SUCCESSFULLY!" << endl;
			Sleep(2000);
			system("cls");
		}
		//
		cout << "Do you want to import more schedule?" << endl;
		cout << "Press[Y/N]: ";
		getline(cin, confirm);

		while (confirm != "Y" && confirm != "N" && confirm != "y" && confirm != "n")
		{
			getline(cin, confirm);
		}
	}

	system("cls");
	Staff_Schedule_Menu(username, password, type);
}

void edit_schedule(char username[], char password[], int type)
{
	string input;

	cout << "Enter course name of schedule you want to edit: "<< endl;
	cout << "Enter: ";
	getline(cin, input);
	fstream file;
	file.open("Schedule\\" + input + ".csv", ios_base::in);

	if (file.is_open() == false)
	{
		cout << "SCHEDULE INVALID! IT MIGHT BE UNAVAILABLE, CHECK IF SCHEDULE HAS BEEN ADDED!" << endl;
		Sleep(2000);
		system("cls");
		Staff_Schedule_Menu(username, password, type);
		return;
	}

	schedule* p = new schedule;
	read_schedule("Schedule\\" + input + ".csv", p);

	system("cls");
	print_schedule(username, password, type, p);

	string p_class = "0", p_day = "0", p_session = "0";
	char confirm = 'Y';
	int row, col;

	while (confirm == 'Y' || confirm == 'y')
	{
		cout << "Enter class/day/session you want to change: " << endl;
		cout << "Class: ";
		getline(cin, p_class);
		cout << "Day: ";
		getline(cin, p_day);
		while (p_day != "Monday" && p_day != "Tuesday" && p_day != "Wednesday" && p_day != "Thursday" && p_day != "Friday" && p_day != "Saturday")
			getline(cin, p_day);

		cout << "Session(1-4): ";
		getline(cin, p_session);
		while (p_session != "1" && p_session != "2" && p_session != "3" && p_session != "4")
			getline(cin, p_session);

		if (p_day == "Monday")
			col = 1;
		else if (p_day == "Tuesday")
			col = 2;
		else if (p_day == "Wednesday")
			col = 3;
		else if (p_day == "Thursday")
			col = 4;
		else if (p_day == "Friday")
			col = 5;
		else if (p_day == "Saturday")
			col = 6;

		if (p_session == "1")
			row = 1;
		else if (p_session == "2")
			row = 2;
		else if (p_session == "3")
			row = 3;
		else if (p_session == "4")
			row = 4;

		p->class_pos[row][col] = p_class;

		print_schedule(username, password, type, p);

		cout << "Do you want to change more?" << "\n" << "Press[Y/N]: " << endl;
		cin >> confirm;
		cin.ignore();
		while (confirm != 'Y' && confirm != 'N' && confirm != 'y' && confirm != 'n')
		{
			cin >> confirm;
			cin.ignore();
		}
	}

	count_scheduleNum(p);
	write_schedule(p);
	updateScheduleList(p);

	file.close();

	system("cls");
	Staff_Schedule_Menu(username, password, type);
}

void remove_schedule(char username[], char password[], int type)
{
	string input, namefile;
	cout << "Enter course's name of schedule you want to remove:" << endl;
	cout << "Enter: ";
	getline(cin,input);

	namefile = input;
	input = "Schedule\\" + input + ".csv";

	if (remove(input.c_str()) != 0)
	{
		system("cls");
		cout << "SCHEDULE INVALID! IT MIGHT BE ALREADY UNAVAILABLE EITHER DELETED!" << endl;
		system("cls");
		Staff_Schedule_Menu(username, password, type);
		return;

	}
	else
	{
		removeScheduleList(namefile);
		system("cls");
		cout << "REMOVE SUCCESSFULLY!!" << endl;
		Sleep(2000);
	}
	system("cls");
	Staff_Schedule_Menu(username, password, type);
}

void add_schedule(char username[], char password[], int type)
{
	schedule* p = new schedule;
	string p_class, p_day = "0", p_session = "0";
	string confirm = "Y";
	int row, col;
	cout << "Add new course's schedule!!" << "\n" << endl;

	cout << "Enter course name of this schedule: ";
	getline(cin, p->course_name);
	cout << "\n";

	if (!isScheduleExist(p->course_name))
	{
		print_schedule(username, password, type, p);
		
		while (confirm == "Y" || confirm == "y")
		{
			cout << "Enter class/day/session: " << endl;
			cout << "Class: ";
			cin >> p_class;
			cout << "Day: ";

			cin >> p_day;
			while (p_day != "Monday" && p_day != "Tuesday" && p_day != "Wednesday" && p_day != "Thursday" && p_day != "Friday" && p_day != "Saturday")
				cin >> p_day;

			cout << "Session(1-4): ";
			cin >> p_session;
			while (p_session != "1" && p_session != "2" && p_session != "3" && p_session != "4")
				cin >> p_session;


			if (p_day == "Monday")
				col = 1;
			else if (p_day == "Tuesday")
				col = 2;
			else if (p_day == "Wednesday")
				col = 3;
			else if (p_day == "Thursday")
				col = 4;
			else if (p_day == "Friday")
				col = 5;
			else if (p_day == "Saturday")
				col = 6;

			if (p_session == "1")
				row = 1;
			else if (p_session == "2")
				row = 2;
			else if (p_session == "3")
				row = 3;
			else if (p_session == "4")
				row = 4;

			p->class_pos[row][col] = p_class;

			print_schedule(username, password, type, p);
			
			cout << "Do you want to add more?" << "\n" << "Press[Y/N]: " << endl;
			getline(cin,confirm);
			while (confirm != "Y" && confirm != "N" && confirm != "y" && confirm != "n")
				getline(cin,confirm);
		}
		count_scheduleNum(p);
		write_schedule(p);
		write_schedule_list(p->course_name, p->session_num);
	}
	else
	{
		system("cls");
		cout << "Schedule has already exist." << endl;
		Sleep(2000);
	}
	system("cls");
	Staff_Schedule_Menu(username, password, type);
}

void updateScheduleList(schedule* p)
{
	string text, num;
	fstream ifile("Schedule\\Schedule_List.txt", ios_base::in);
	fstream ofile("Schedule\\temp.txt", ios_base::out);
	while (ifile.eof() != true)
	{
		getline(ifile, text, ',');
		if (text == "") break;
		getline(ifile, num);
		if (text != p->course_name)
		{
			ofile << text << "," << num << endl;
		}
		else
		{
			ofile << text << "," << p->session_num << endl;
		}
	}
	ifile.close();
	ofile.close();

	fstream fo("Schedule\\Schedule_List.txt", ios_base::out);
	fstream fi("Schedule\\temp.txt", ios_base::in);
	while (fi.eof() != true)
	{
		getline(fi, text);
		if (text == "") break;
		fo << text << endl;
	}
	fo.close();
	fi.close();
	remove("Schedule\\temp.txt");
}

void removeScheduleList(string scheduleName)
{
	string text, num;
	fstream ifile("Schedule\\Schedule_List.txt", ios_base::in);
	fstream ofile("Schedule\\temp.txt", ios_base::out);
	while (ifile.eof() != true)
	{
		getline(ifile, text, ',');
		if (text == "") break;
		getline(ifile, num);
		if (text != scheduleName)
		{
			ofile << text << "," << num << endl;
		}
	}
	ifile.close();
	ofile.close();

	fstream fo("Schedule\\Schedule_List.txt", ios_base::out);
	fstream fi("Schedule\\temp.txt", ios_base::in);
	while (fi.eof() != true)
	{
		getline(fi, text);
		if (text == "") break;
		fo << text << endl;
	}
	fo.close();
	fi.close();
	remove("Schedule\\temp.txt");
}

void write_schedule_list(string scheduleName, int num)
{
	fstream file("Schedule/Schedule_List.txt", ios_base::app);
	file << scheduleName << "," << num << endl;
	file.close();
}

bool isScheduleExist(string scheduleName)
{
	fstream File;
	string temp, trim;
	File.open("Schedule\\Schedule_List.txt", ios_base::in);
	File.seekp(0, File.beg);

	while (File.eof() != true)
	{
		getline(File, temp, ',');
		getline(File, trim);
		if (temp == scheduleName)
		{

			File.close();
			return true;
		}
	}
	File.close();
	return false;
}

void view_schedule_list(char username[], char password[], int type)
{
	ifstream Fin;
	Fin.open("Schedule\\Schedule_List.txt", ios_base::in);

	scheduleList list;
	list.head = NULL;
	schedule* cur = NULL;

	while (Fin.eof() != true)
	{
		schedule* p = new schedule;

		getline(Fin, p->course_name, ',');
		if (p->course_name == "\n")
		{
			p->next = NULL;
			break;
		}
		Fin >> p->session_num;
		Fin.seekg(1, Fin.cur);

		p->next = NULL;
		p->prev = NULL;
		if (list.head == NULL)
		{
			list.head = p;
			cur = p;
		}
		else
		{
			cur->next = p;
			p->prev = cur;
			cur = p;
		}
	}
	cout << setw(10) << left << "Schedule";
	cout << setw(10) << left << "Number of Session" << endl;

	cout << setfill('=');
	cout << setw(30) << "=" << endl;
	cout << setfill(' ');

	for (schedule* cur = list.head; cur != NULL; cur = cur->next)
	{
		cout << setw(10) << left << cur->course_name;
		cout << setw(10) << left << cur->session_num;
	}

	cout << "\n" << "Press Enter to back to Schedule Menu..." << endl;
	char hotkey = _getch();
	while (hotkey != 13)
	{
		hotkey = _getch();
		continue;
	}
	system("cls");
	Staff_Schedule_Menu(username, password, type);
	Fin.close();

}

void write_schedule(schedule* p)
{
	fstream file;
	_mkdir("Schedule");
	file.open("Schedule\\" + p->course_name + ".csv", ios_base::out);
	
	file << p->course_name << ",,,,,,," << endl;

	for (int i = 0 ; i < 5; i++)
		for (int j = 0; j < 7; j++)
		{
			if (j == 6)
				file << p->class_pos[i][j] << "\n";
			else
				file << p->class_pos[i][j] << ",";
		}

	file.close();
}

void read_schedule(string path, schedule* p)
{
	fstream file;
	file.open(path, ios_base::in);

	p->next = NULL;
	p->prev = NULL;

	string temp;
	getline(file, p->course_name, ',');
	getline(file, temp, '\n');
	getline(file, temp, '\n');

	for (int i = 1; i < 5; i++)
	{
		getline(file, temp, ',');
		for (int j = 1; j < 7; j++)
		{
			if (j == 6)
				getline(file, p->class_pos[i][j]);
			else
				getline(file, p->class_pos[i][j], ',');
		}
	}
	file.close();
}

void print_schedule(char username[], char password[], int type, schedule* p)
{
	cout << "SCHEDULE: " << p->course_name << endl;
	
	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 7; j++)
		{
			if (j == 6)
				cout << setw(13) << left << p->class_pos[i][j] << endl;
			else
				cout << setw(10) << left << p->class_pos[i][j];
		}
	cout << "\n";
}

void count_scheduleNum(schedule* p)
{
	p->session_num = 0;
	for (int i = 1; i < 5; i++)
		for (int j = 1; j < 7; j++)
		{
			if (p->class_pos[i][j] == "")
				continue;
			else
				p->session_num++;
		}
}