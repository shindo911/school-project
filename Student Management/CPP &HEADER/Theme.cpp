#include "Header.h"

void Color(int x)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, x);
}

void PlaceCursor(const int x, const int y)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD PlaceCursorHere;
	PlaceCursorHere.X = x;
	PlaceCursorHere.Y = y;
	SetConsoleCursorPosition(hConsole, PlaceCursorHere);
	return;
}

void loading()
{
	PlaceCursor(1, 18);
	int i;
	for (i = 0; i<5; i++)
	{
		cout << "\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb";
		Sleep(100);
	}
	Sleep(500);
	PlaceCursor(13, 18);
}
void logo()
{
	PlaceCursor(1, 2);
	cout << "�����   �����           ��������           �����������      " << endl; PlaceCursor(1, 3);
	cout << " ���     ���          ���      ���        ���       ��      " << endl; PlaceCursor(1, 4);
	cout << " ���     ���         ���        ���       ���               " << endl; PlaceCursor(1, 5);
	cout << " ���     ���         ���        ���        �����������      " << endl; PlaceCursor(1, 6);
	cout << " ���     ���         ���        ���                 ���     " << endl; PlaceCursor(1, 7);
	cout << " ���     ���          ���      ���        ��       ���      " << endl; PlaceCursor(1, 8);
	cout << "  ��������� NIVERSITY   �������� F        ����������� CIENCE" << endl << endl; PlaceCursor(1, 9);
	cout << "****************************************************************" << endl;
	PlaceCursor(1, 10);
	cout << "                 STUDENT MANAGEMENT PROJECT                  " << endl;
	PlaceCursor(1, 11);
	cout << "****************************************************************" << endl;
}
void time()
{

	time_t now;
	time(&now);
	cout << "\tCurrent Date & Time is: " << ctime(&now) << endl;
}