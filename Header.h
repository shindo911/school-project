#pragma once
#ifndef _Header_H
#define _Header_H

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<iostream>
#include<fstream>
#include<windows.h>
#include<conio.h>
#include<string>
#include <iomanip>
#include<istream>
#include<direct.h>
#include<io.h>
#include<time.h>

using namespace std;


// DEFINE STRUCT
struct User
{
	string username;
	string name;
	string email;
	string phone;
	string type;
	string password;
	string _class;
	User* next;
	User* prev;
};

struct UserList
{
	int type;
	User* head;
};

struct Student
{
	string No;
	string ID;
	string Name;
	string email;
	string phone;
	string username;
	Student* next;
	Student* prev;
};

struct Class
{
	string name;
	int number;
	Student* head;
	Class* next;
	Class* prev;
};

struct ClassList
{
	int number;
	Class* _class;
};

struct course
{
	string courseCode;
	string year;
	string semester;
	string courseName;
	string lectureName;
	string dayStart;
	string dayEnd;
	string timeStart;
	string timeEnd;
	string dayOfWeek;
	course* next;
	course* prev;
};

struct courseList
{
	course* head;
	course* tail;
};

struct schedule
{
	string course_name;
	int session_num;
	string class_pos[5][7] = {
		"", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday",
		"Section 1", "", "", "", "", "", "",
		"Section 2", "", "", "", "", "", "",
		"Section 3", "", "", "", "", "", "",
		"Section 4", "", "", "", "", "", "",
	};
	schedule* next;
	schedule* prev;
};

struct scheduleList
{
	schedule* head;
};

struct score
{
	string studentID;
	string midtermScore;
	string labScore;
	string finalScore;
	string bonus;
	string semester;
	string year;

	score* next;
	score* prev;
};

struct scoreList
{
	string courseCode;
	score* head;
};

struct attendance
{
	string StudentID;
	string name;
	string _class;
	string student[10] = {
		"", "", "", "", "", "", "", "", "", ""
	};
	attendance* next;
	attendance* prev;
};

struct AttendList
{
	string courseCode;
	attendance* head;
};

struct CheckIn
{
	string course;
	string day;
	string time;
	CheckIn* next;
};

struct checkInList
{
	string course;
	CheckIn* head;
};

//Theme
void Color(int x);
void PlaceCursor(const int x, const int y);
void loading();
void logo();
void time();


// Access Function
void Access();

//Log In
void hidePassword(char pass[]);
bool isStudent(char user[], char pass[]);
bool isLecturer(char user[], char pass[]);
bool isStaff(char user[], char pass[]);
bool isExist(char user[], char pass[]);
void Login(char Username[], char Password[], int &type);

// Staff Menu Categories
void Staff_Menu(char username[], char password[], int type);
void Staff_Student_Menu(char username[], char password[], int type);
void Staff_Class_Menu(char username[], char password[], int type);
void Staff_Course_Menu(char username[], char password[], int type);
void Staff_Schedule_Menu(char username[], char password[], int type);
void Staff_Attendance_Menu(char username[], char password[], int type);
void Staff_Scoreboard_Menu(char username[], char password[], int type);
void Staff_Option_Menu(char username[], char Password[], int type);

// Student Menu Categories
void Student_Menu(char username[], char password[], int type);
void Student_Checkin_Menu(char username[], char password[], int type);
void Student_Scoreboard_Menu(char username[], char password[], int type);
void Student_Schedule_Menu(char username[], char password[], int type);
void Student_Option_Menu(char username[], char password[], int type);

// Lecturer Menu Categories
void Lecturer_Menu(char username[], char password[], int type);
void Lecturer_Scoreboard_Menu(char username[], char password[], int type);
void Lecturer_Option_Menu(char username[], char password[], int type);

//Student
void addStudent(char username[], char password[], int type);
void updateClassList(Class p);
void removeStudent(char username[], char password[], int type);
void readUserStudentList(UserList &StudentList, char username[], char password[], int type);
void editStudent(char username[], char password[], int type);
void moveStudent(char username[], char password[], int type);
void updateUserAccount(string ID);

//Class
void Import_Class(string path, Class &_class, char username[], char password[], int type);
void Write_Class(string path, Class _class);
void View_Class(char username[], char password[], int type);
void Read_Class(string path, Class &_class, char username[], char password[], int type);
void Print_Class(Class _class, char username[], char password[], int type);
void Print_Class_List(char username[], char password[], int type);
void Add_Class(string path);

// Course
void importCourse(courseList &c);
course* createCourse();
void writeCourse(course* c);
void removeCourse(string path, courseList list);
void printCourseList(courseList list);
void editCourse(courseList list);

// Schedule
void import_schedule(char username[], char password[], int type);
void add_schedule(char username[], char password[], int type);
void edit_schedule(char username[], char password[], int type);
void remove_schedule(char username[], char password[], int type);
void write_schedule(schedule* p);
void read_schedule(string path, schedule* p);
void print_schedule(char username[], char password[], int type, schedule* p);
void updateScheduleList(schedule* p);
void removeScheduleList(string scheduleName);
void write_schedule_list(string scheduleName, int num);
bool isScheduleExist(string scheduleName);
void view_schedule_list(char username[], char password[], int type);
void count_scheduleNum(schedule* p);

// Scoreboard
void importScore(char username[], char password[], int type);
void searchViewScore(char username[], char password[], int type);
void readScore(string path, char username[], char password[], int type, scoreList &list);
void writeScore(string path, char username[], char password[], int type, scoreList list);
void printScore(char username[], char password[], int type, scoreList list);
void exportScore(char username[], char password[], int type);
void editScore(char username[], char password[], int type);
void viewStudentScore(char username[], char password[], int type);

// Attendance
void searchViewAttend(char username[], char password[], int type);
void readAttend(string path, char username[], char password[], int type, AttendList &list);
void printAttend(char username[], char password[], int type, AttendList list);
void writeAttend(string path, char username[], char password[], int type, AttendList list);
void exportAttend(char username[], char password[], int type);

//Check-in
void checkIn(char username[], char password[], int type);
void getTime(char day[], int &hour, int &min);
void writeCheckIn(string code, char day[], int hour, int min, char username[], char password[], int type);
void viewCheckIn(char username[], char password[], int type);
void viewschedule(char username[], char password[], int type);

//Option
void Print_User(char username[], char password[], int type);
void Print_Info(User user, char username[], char password[], int type);
void Write_UserList(UserList user, char username[], char password[], int type);
void changePassword(const char path[], char username[], char password[]);
void checkFirstTime(const char path[], char Username[], char Password[]);

#endif // !_Header_H
