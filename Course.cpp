#include "Header.h"

void importCourse(courseList &c)
{
	string input;
	cout << "Enter file's link. File must be csv file." << endl;
	cout << "Enter link: ";
	getline(cin, input);
	string trim;
	fstream file(input);
	if (file.is_open())
	{
		getline(file, trim);
		course* cur = NULL;
		while (file.eof() != true)
		{
			course*p = new course;
			getline(file, p->courseCode, ',');
			if (p->courseCode == "")
			{
				cur->next = NULL;
				break;
			}
			getline(file, p->year, ',');
			getline(file, p->semester, ',');
			getline(file, p->courseName, ',');
			getline(file, p->lectureName, ',');
			getline(file, p->dayStart, ',');
			getline(file, p->dayEnd, ',');
			getline(file, p->timeStart, ',');
			getline(file, p->timeEnd, ',');
			getline(file, p->dayOfWeek, '\n');
			p->next = NULL;			
			p->prev = NULL;
			if (c.head == NULL)
			{
				c.head = p;
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
	else
	{
		cout << "Can't open file!";
		return;
	}

	_mkdir("Course");
	file.open("Course\\course.csv", ios_base::out);
	file << trim << ",,,," << endl;
	file.close();

	for (course* p = c.head; p != NULL; p = p->next)
	{
		writeCourse(p);
	}

	cout << "COURSE IMPORTED SUCCESSFULLY!" << endl;
	Sleep(2000);
}

course* createCourse()
{
	course* c = new course;
	cout << "Course Code: ";
	getline(cin, c->courseCode);
	cout << "Year: ";
	getline(cin, c->year);
	cout << "Semester: ";
	getline(cin, c->semester);
	cout << "Course Name: ";
	getline(cin, c->courseName);
	cout << "Lecturer Username: ";
	getline(cin, c->lectureName);
	cout << "Start at(date): ";
	getline(cin, c->dayStart);
	cout << "End at(date): ";
	getline(cin, c->dayEnd);
	cout << "From(time): ";
	getline(cin, c->timeStart);
	cout << "To(time): ";
	getline(cin, c->timeEnd);
	cout << "Date of week: ";
	getline(cin, c->dayOfWeek);
	c->dayOfWeek = "\"" + c->dayOfWeek + "\"";
	c->next = NULL;
	c->prev = NULL;
	return c;
}

void writeCourse(course* c)
{
	ofstream file;

	file.open("Course\\course.csv", ios_base::app);
	file.seekp(0, file.end);
	file << c->courseCode << ",";
	file << c->year << ",";
	file << c->semester << ",";
	file << c->courseName << ",";
	file << c->lectureName << ",";
	file << c->dayStart << ",";
	file << c->dayEnd << ",";
	file << c->timeStart << ",";
	file << c->timeEnd << ",";
	file << c->dayOfWeek << endl;

	file.close();

}

void removeCourse(string path, courseList list)
{
	string trim, del;
	fstream file;

	file.open("Course\\course.csv", ios_base::in);

	if (file.is_open())
	{
		getline(file, trim);
		course* cur = NULL;
		while (file.eof() != true)
		{
			course*p = new course;
			getline(file, p->courseCode, ',');
			if (p->courseCode == path)
			{
				getline(file, del);
				getline(file, p->courseCode, ',');
			}
			if (p->courseCode == "")
				break;
			getline(file, p->year, ',');
			getline(file, p->semester, ',');
			getline(file, p->courseName, ',');
			getline(file, p->lectureName, ',');
			getline(file, p->dayStart, ',');
			getline(file, p->dayEnd, ',');
			getline(file, p->timeStart, ',');
			getline(file, p->timeEnd, ',');
			getline(file, p->dayOfWeek, '\n');
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
		file.close();
	}
	else
	{
		cout << "Can't open file!";
		return;
	}

	file.open("Course\\course.csv", ios_base::out);
	file << trim << ",,,," << endl;
	file.close();

	for (course* p = list.head; p != NULL; p = p->next)
	{
		writeCourse(p);
	}
}

void printCourseList(courseList list)
{
	string trim;
	fstream file("Course\\course.csv");
	if (file.is_open())
	{
		getline(file, trim);
		course* cur = NULL;
		while (file.eof() != true)
		{
			course*p = new course;
			getline(file, p->courseCode, ',');
			if (p->courseCode == "")
			{
				cur->next = NULL;
				break;
			}
			getline(file, p->year, ',');
			getline(file, p->semester, ',');
			getline(file, p->courseName, ',');
			getline(file, p->lectureName, ',');
			getline(file, p->dayStart, ',');
			getline(file, p->dayEnd, ',');
			getline(file, p->timeStart, ',');
			getline(file, p->timeEnd, ',');
			getline(file, p->dayOfWeek, '\n');

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
		file.close();

	}
	else
	{
		cout << "Can't open file!";
		return;
	}
	cout << setw(8) << left << "Code";
	cout << setw(11) << "Year";
	cout << setw(10) << "Semester";
	cout << setw(30) << "Name";
	cout << setw(10) << "Lecturer";
	cout << setw(13) << "Start";
	cout << setw(13) << "End";
	cout << setw(8) << "From";
	cout << setw(8) << "To";
	cout << setw(50) << "Day Of Week" << endl;
	for (course* cur = list.head; cur != NULL; cur = cur->next)
	{
		cout << setw(8) << left << cur->courseCode;
		cout << setw(11) << cur->year;
		cout << setw(10) << cur->semester;
		cout << setw(30) << left << cur->courseName;
		cout << setw(10) << left << cur->lectureName;
		cout << setw(13) << cur->dayStart;
		cout << setw(13) << cur->dayEnd;
		cout << setw(8) << cur->timeStart;
		cout << setw(8) << cur->timeEnd;
		cout << setw(50) << left << cur->dayOfWeek << endl;
	}

	cout << "\n" << "Press Enter to back to Course Menu..." << endl;
	char hotkey = _getch();
	while (hotkey != 13)
	{
		hotkey = _getch();
		continue;
	}
}

void editCourse(courseList list)
{
	ifstream ifile("Course\\course.csv");
	string editID = "";
	cout << "Enter course code to edit: ";
	getline(cin, editID);
	string trim;
	getline(ifile, trim);
	ofstream ofile("temp.csv");
	ofile << trim << "\n";
	while (ifile.eof() != true)
	{
		course*p = new course;
		getline(ifile, p->courseCode, ',');
		if (p->courseCode == "")
			break;
		if (p->courseCode == editID)
		{
			p = createCourse();
			ofile << p->courseCode << ",";
			ofile << p->year << ",";
			ofile << p->semester << ",";
			ofile << p->courseName << ",";
			ofile << p->lectureName << ",";
			ofile << p->dayStart << ",";
			ofile << p->dayEnd << ",";
			ofile << p->timeStart << ",";
			ofile << p->timeEnd << ",";
			ofile << p->dayOfWeek << endl;
			getline(ifile, trim, '\n');
		}
		else
		{
			getline(ifile, p->year, ',');
			getline(ifile, p->semester, ',');
			getline(ifile, p->courseName, ',');
			getline(ifile, p->lectureName, ',');
			getline(ifile, p->dayStart, ',');
			getline(ifile, p->dayEnd, ',');
			getline(ifile, p->timeStart, ',');
			getline(ifile, p->timeEnd, ',');
			getline(ifile, p->dayOfWeek, '\n');
			ofile << p->courseCode << ",";
			ofile << p->year << ",";
			ofile << p->semester << ",";
			ofile << p->courseName << ",";
			ofile << p->lectureName << ",";
			ofile << p->dayStart << ",";
			ofile << p->dayEnd << ",";
			ofile << p->timeStart << ",";
			ofile << p->timeEnd << ",";
			ofile << p->dayOfWeek << endl;
		}
	}
	ifile.close();
	ofile.close();
	remove("Course\\course.csv");
	rename("temp.csv", "Course\\course.csv");
	system("cls");
	cout << "EDIT SUCCESSFULLY!" << endl;
	Sleep(2000);
}