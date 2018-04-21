#include "Header.h"

void checkIn(char username[], char password[], int type)
{
	string code;
	cout << "Enter course code you want to check in: ";
	getline(cin, code);

	schedule* p = new schedule;
	read_schedule("Schedule\\" + code + ".csv", p);

	char day[20];
	int hour;
	int min;

	getTime(day, hour, min);

	for (int i = 1; i < 5; i++)
	{	for (int j = 1; j < 7; j++)
		{
			if (p->class_pos[i][j] == code)
			{
				if (p->class_pos[0][j] == day)
				{
					if (p->class_pos[i][0] == "Session 1")
					{
						if ((hour >= 7 && min >= 30) && (hour <= 9 && min <= 30))
						{
							writeCheckIn(code, day, hour, min, username, password, type);
							cout << "CHECK-IN SUCCESSFULLY!" << endl;
							Sleep(2000);
							system("cls");
							Student_Checkin_Menu(username, password, type);
							return;
						}

					}
					else if (p->class_pos[i][0] == "Session 2")
					{
						if ((hour >= 9 && min >= 30) && (hour <= 11 && min <= 15))
						{
							writeCheckIn(code, day, hour, min, username, password, type);
							cout << "CHECK-IN SUCCESSFULLY!" << endl;
							Sleep(2000);
							system("cls");
							Student_Checkin_Menu(username, password, type);
							return;
						}
					}
					else if (p->class_pos[i][0] == "Session 3")
					{
						if ((hour >= 13 && min >= 30) && (hour <= 15 && min <= 30))
						{
							writeCheckIn(code, day, hour, min, username, password, type);
							cout << "CHECK-IN SUCCESSFULLY!" << endl;
							Sleep(2000);
							system("cls");
							Student_Checkin_Menu(username, password, type);
							return;
						}
					}
					else if (p->class_pos[i][0] == "Session 4")
					{
						if ((hour >= 15 && min >= 30) && (hour <= 17 && hour <= 15))
						{
							writeCheckIn(code, day, hour, min, username, password, type);
							cout << "CHECK-IN SUCCESSFULLY!" << endl;
							Sleep(2000);
							system("cls");
							Student_Checkin_Menu(username, password, type);
							return;
						}
					}
				}
			}
		}
	}
	cout << "YOU HAS MISS YOUR CHECK-IN!" << endl;
	Sleep(2000);
	system("cls");
	Student_Checkin_Menu(username, password, type);
}

void getTime(char day[], int &hour, int &min)
{
	time_t rawtime;
	struct tm *info;

	time(&rawtime);

	info = localtime(&rawtime);
	hour = info->tm_hour;
	min = info->tm_min;
	strftime(day, 20, "%A", info);
}

void writeCheckIn(string code, char day[], int hour, int min, char username[], char password[], int type)
{
	_mkdir("CheckIn");
	fstream file;
	string path = username;
	file.open("CheckIn\\" + path + ".txt", ios_base::app);
	if (file.is_open() == false)
	{
		system("cls");
		cout << "ERROR!" << endl;
		Sleep(2000);
		system("cls");
		return;
	}

	file << code << ",";
	file << day << ",";
	file << hour << ":";
	file << min << endl;

	file.close();
}

void viewCheckIn(char username[], char password[], int type)
{
	fstream file;
	string path = username;
	file.open("CheckIn\\" + path + ".txt", ios_base::in);
	file.open("CheckIn\\" + path + ".txt", ios_base::app);
	if (file.is_open() == false)
	{
		system("cls");
		cout << "ERROR!" << endl;
		Sleep(2000);
		system("cls");
		Student_Checkin_Menu(username, password, type);
		return;
	}


	cout << setw(10) << left << "Course";
	cout << setw(10) << left << "Day";
	cout << setw(10) << left << "Time" << "\n" << endl;

	while (file.eof() == false)
	{
		CheckIn* p = new CheckIn;

		getline(file, p->course, ',');
		if (p->course == "")
			break;
		getline(file, p->day, ',');
		getline(file, p->time);
		
		cout << setw(10) << left << p->course;
		cout << setw(10) << left << p->day;
		cout << setw(10) << left << p->time << endl;
	}
}

void viewschedule(char username[], char password[], int type)
{
	string input;
	cout << "Enter course of schedule you want to view: ";
	getline(cin, input);

	schedule* p =new schedule;
	read_schedule("Schedule\\" + input + ".csv", p);
	print_schedule(username, password, type, p);
}