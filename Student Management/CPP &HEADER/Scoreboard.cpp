#include"Header.h"

void importScore(char username[], char password[], int type)
{
	string input = "nowat";
	string confirm = "Y";

	while (confirm == "Y" || confirm == "y")
	{
		cout << "Enter course's scoreboard link. File must be a csv file." << endl;
		cout << "Enter link: ";

		getline(cin, input);

		scoreList list;
		list.head = NULL;
		score* cur = NULL;
		score*p = new score;

		if (input == "")
		{
			return;
		}

		readScore(input, username, password, type, list);

		/*if (list.head == NULL)
		{
			list.head = p;

			cur = p;
		}
		else
		{
			cur->next = p;
			p->prev = cur;
			cur = p;
		}*/
		_mkdir("Scoreboard");
		writeScore("Scoreboard\\" + list.courseCode + ".csv", username, password, type, list);

		fstream file;

		file.open("Scoreboard\\" + list.courseCode + ".csv");
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
			_mkdir("Scoreboard");
			importScore(username, password, type);
			return;
		}
		else
		{
			cout << "IMPORTED SUCCESSFULLY!" << endl;
			Sleep(2000);
			system("cls");
		}
		//
		cout << "Do you want to import more scoreboard?" << endl;
		cout << "Press[Y/N]: ";
		getline(cin,confirm);

		while (confirm != "Y" && confirm != "N" && confirm != "y" && confirm != "n")
		{
			getline(cin, confirm);
		}
	}

	system("cls");
	Lecturer_Scoreboard_Menu(username, password, type);
}

void searchViewScore(char username[], char password[], int type)
{
	string input;
	scoreList list;
	list.head = NULL;

	cout << "Enter course code of the scoreboard: ";
	getline(cin, input);

	readScore("Scoreboard\\" + input + ".csv", username, password, type, list);
	printScore(username, password, type, list);
	return;
}

void viewStudentScore(char username[], char password[], int type)
{
	string input;
	scoreList list;
	list.head = NULL;

	cout << "Enter course code: ";
	getline(cin, input);

	readScore("Scoreboard\\" + input + ".csv", username, password, type, list);
	for (score* cur = list.head; cur != NULL; cur = cur->next)
	{
		if (cur->studentID == username)
		{
			system("cls");
			cout << "SCOREBOARD" << "\n" << endl;

			cout << "Student ID: " << cur->studentID << endl;
			cout << "Semester: " << cur->semester << endl;
			cout << "Year: " << cur->year << endl;
			cout << "Midterm Score: " << cur->midtermScore << endl;
			cout << "Lab Score: " << cur->labScore << endl;
			cout << "Final Score: " << cur->finalScore << endl;
			cout << "Bonus Score: " << cur->bonus << endl;
			break;
		}
	}
	cout << "\n" << "Press Enter to back to Scoreboard Menu..." << endl;
	char hotkey = _getch();
	while (hotkey != 13)
	{
		hotkey = _getch();
		continue;
	}
	system("cls");
	Student_Scoreboard_Menu(username, password, type);
	return;
}

void readScore(string path, char username[], char password[], int type, scoreList &list)
{
	fstream file(path);
	
	string trim;
	score* cur = NULL;

	if (file.is_open())
	{

		getline(file, trim, ',');
		getline(file, list.courseCode, ',');
		getline(file, trim);
		getline(file, trim);
		while (file.eof() != true)
		{
			score* s = new score;
			s->next = NULL;
			s->prev = NULL;

			getline(file, s->studentID, ',');
			getline(file, s->midtermScore, ',');
			getline(file, s->labScore, ',');
			getline(file, s->finalScore, ',');
			getline(file, s->bonus, ',');
			getline(file, s->semester, ',');
			getline(file, s->year);

			if (list.head == NULL)
			{
				list.head = s;

				cur = s;
			}
			else
			{
				cur->next = s;
				s->prev = cur;

				cur = s;
			}
		}
	}
	else
	{
		cout << "COURSE'S SCOREBOARD NOT FOUND!" << endl;
		Sleep(2000);

		system("cls");

		if (type == 1)
		{
			system("cls");
			Staff_Scoreboard_Menu(username, password, type);
			return;
		}
		else if (type == 2)
		{
			system("cls");
			Lecturer_Scoreboard_Menu(username, password, type);
			return;
		}
	}
	file.close();
}

void printScore(char username[], char password[], int type, scoreList list)
{
	cout << "Cource code: " << list.courseCode << endl;

	cout << setw(12) << left << "Student ID";
	cout << setw(15) << left << "Midterm Score";
	cout << setw(11) << left << "Lab Score";
	cout << setw(13) << left << "Final Score";
	cout << setw(8) << left << "Bonus";
	cout << setw(9) << left << "Semester";
	cout << setw(10) << left << "Year" << endl;

	for (score* cur = list.head; cur != NULL; cur = cur->next)
	{
		cout << setw(12) << left << cur->studentID;
		cout << setw(15) << left << cur->midtermScore;
		cout << setw(11) << left << cur->labScore;
		cout << setw(13) << left << cur->finalScore;
		cout << setw(8) << left << cur->bonus;
		cout << setw(9) << left << cur->semester;
		cout << setw(10) << left << cur->year << endl;
	}
	cout << "\n" << "Press Enter to back to Scoreboard Menu..." << endl;
	char hotkey = _getch();
	while (hotkey != 13)
	{
		hotkey = _getch();
		continue;
	}

	if (type == 1)
	{
		system("cls");
		Staff_Scoreboard_Menu(username, password, type);
		return;
	}
	else if (type == 2)
	{
		system("cls");
		Lecturer_Scoreboard_Menu(username, password, type);
	}
}

void writeScore(string path, char username[], char password[], int type, scoreList list)
{
	fstream file;

	file.open(path, ios_base::out);
	
	file << "Course code," << list.courseCode << ",,,,," << endl;
	file << "Student ID,Midterm score,Lap score,Final score,Bonus,Semester,Year" << endl;

	for (score* cur = list.head; cur != NULL; cur = cur->next)
	{
		file << cur->studentID << ",";
		file << cur->midtermScore << ",";
		file << cur->labScore << ",";
		file << cur->finalScore << ",";
		file << cur->bonus << ",";
		file << cur->semester << ",";
		file << cur->year << endl;
	}

	file.close();
}

void exportScore(char username[], char password[], int type)
{
	string input, link, filename;

	cout << "Enter course code of scoreboard: ";
	getline(cin, input);

	scoreList list;
	list.head = NULL;

	readScore("Scoreboard\\" + input + ".csv", username, password, type, list);

	cout << "Enter destination to export!" << endl;
	cout << "Enter path: ";
	getline(cin, link);
	cout << "Save as(filename, not include .csv): ";
	getline(cin, filename);

	writeScore(link + filename + ".csv", username, password, type, list);

	fstream file;
	file.open(link + filename + ".csv");
	if (file.is_open() == true)
	{
		cout << "EXPORT SUCCESSFULLY!" << endl;
		Sleep(2000);

		system("cls");
		Staff_Scoreboard_Menu(username, password, type);
	}
	else
	{
		cout << "ERROR!" << endl;
		Sleep(2000);

		system("cls");
		Staff_Scoreboard_Menu(username, password, type);
		return;
	}
	file.close();
}

void editScore(char username[], char password[], int type)
{
	string input, id, newMid, newLab, newFin, bonus;

	cout << "Enter course code of scoreboard: ";
	getline(cin, input);
	cout << "Enter student ID: ";
	getline(cin, id);
	string trim;
	ifstream ifile("Scoreboard\\" + input + ".csv");
	ofstream ofile("Scoreboard\\temp.csv");
	if (ifile.is_open())
	{
		getline(ifile, trim);
		ofile << trim << endl;
		getline(ifile, trim);
		ofile << trim << endl;
		while (ifile.eof() != true)
		{
			score* s = new score;
			getline(ifile, s->studentID, ',');
			ofile << s->studentID << ",";

			if (s->studentID == id)
			{
				cout << " New Midterm Score: ";
				getline(cin, newMid);
				getline(ifile, s->midtermScore, ',');
				ofile << newMid << ",";
				cout << " New Lab Score: ";
				getline(cin, newLab);
				getline(ifile, s->labScore, ',');
				ofile << newLab << ",";
				cout << " New Final Score: ";
				getline(cin, newFin);
				getline(ifile, s->finalScore, ',');
				ofile << newFin << ",";
				cout << " New Bonus Score: ";
				getline(cin, bonus);
				getline(ifile, s->bonus, ',');
				ofile << bonus << ",";

			}
			else
			{
				getline(ifile, s->midtermScore, ',');
				ofile << s->midtermScore << ",";
				getline(ifile, s->labScore, ',');
				ofile << s->labScore << ",";
				getline(ifile, s->finalScore, ',');
				ofile << s->finalScore << ",";
				getline(ifile, s->bonus, ',');
				ofile << s->bonus << ",";

			}
			getline(ifile, s->semester, ',');
			ofile << s->semester << ",";
			getline(ifile, s->year);
			ofile << s->year << endl;
		}
	}
	else
	{
		system("cls");
		cout << "SCOREBOARD UNAVAILABLE!";
		Sleep(2000);
		system("cls");
		Lecturer_Scoreboard_Menu(username, password, type);
		return;
	}
	ifile.close();
	ofile.close();

	string text;
	string temp = "Scoreboard\\" + input + ".csv";
	fstream fo(temp, ios_base::out);
	fstream fi("Scoreboard\\temp.csv", ios_base::in);
	while (fi.eof() != true)
	{
		getline(fi, text);
		if (text == "") break;
		fo << text << endl;
	}
	fo.close();
	fi.close();
	remove("Scoreboard\\temp.csv");

	system("cls");
	cout << "EDIT SUCCESSFULLY!" << endl;
	system("cls");
	Lecturer_Scoreboard_Menu(username, password, type);
}