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
	cout << "ллллл   ллллл           лллллллл           ллллллллллл      " << endl; PlaceCursor(1, 3);
	cout << " ллл     ллл          ллл      ллл        ллл       лл      " << endl; PlaceCursor(1, 4);
	cout << " ллл     ллл         ллл        ллл       ллл               " << endl; PlaceCursor(1, 5);
	cout << " ллл     ллл         ллл        ллл        ллллллллллл      " << endl; PlaceCursor(1, 6);
	cout << " ллл     ллл         ллл        ллл                 ллл     " << endl; PlaceCursor(1, 7);
	cout << " ллл     ллл          ллл      ллл        лл       ллл      " << endl; PlaceCursor(1, 8);
	cout << "  ллллллллл NIVERSITY   лллллллл F        ллллллллллл CIENCE" << endl << endl; PlaceCursor(1, 9);
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