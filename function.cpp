#include "Header.h"
#include <iostream>
#include<windows.h>
using namespace std;


void Init(int* arr, const int size)
{
	int range = 10;
	for (int i = 0; i < size; i++) arr[i] = rand() % range;
}

void VisualOutPut(int* arr, const int size, int x, int y) {

	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	// скрыть курсор
	CONSOLE_CURSOR_INFO structCursorInfo;
	GetConsoleCursorInfo(h, &structCursorInfo);
	structCursorInfo.bVisible = FALSE;
	SetConsoleCursorInfo(h, &structCursorInfo);

	COORD Start = { x,y };
	COORD coord_arr;

	SetConsoleCursorPosition(h, Start);

	enum maze_objects { HALL, WALL, GOLD, VRAG };
	enum colors { BLUE = 9, RED = 12, YELLOW = 14, DARKGREEN = 2, WHITE = 7 };

	int height = 9;
	int width = size * 4 + 1 + 9;

	// объ§вление двумерного динамического массива
	int** maze = new int* [height];
	for (int i = 0; i < height; i++) maze[i] = new int[width];

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (i == 0 || i == height - 1 || j == 0 || !((j - 1) % 4) && j != 1 && j != 5 || i == height / 2) maze[i][j] = WALL;
		}
	}

	for (int dy = 0; dy < height; dy++) {
		Start.Y = dy + y;
		SetConsoleCursorPosition(h, Start);
		for (int dx = 0; dx < width; dx++)
			if (maze[dy][dx] == WALL)
			{
				SetConsoleTextAttribute(h, DARKGREEN);
				cout << (char)178;
			}
			else cout << " ";
		cout << endl;
	}

	coord_arr.X = x + 2;
	coord_arr.Y = y + 2;
	SetConsoleTextAttribute(h, WHITE);
	SetConsoleCursorPosition(h, coord_arr);
	cout << "index";
	coord_arr.Y = y + 6;
	SetConsoleCursorPosition(h, coord_arr);
	cout << "arr[i]";


	for (int i = 0; i < size; i++) {
		coord_arr.X = i * 4 + 2 + x + 9;
		coord_arr.Y = 6 + y;
		SetConsoleCursorPosition(h, coord_arr);
		SetConsoleTextAttribute(h, WHITE);
		cout << arr[i];
		coord_arr.Y = 2 + y;
		SetConsoleCursorPosition(h, coord_arr);
		cout << i;

	}
	coord_arr.Y = y + 15;
	SetConsoleCursorPosition(h, coord_arr);
}

void SelectSort(int* arr, const int size)
{
	int tmp;
	for (int i = 0; i < size - 1; i++) {
		for (int j = i + 1; j < size; j++) {
			if (arr[j] < arr[i]) {
				tmp = arr[j];
				arr[j] = arr[i];
				arr[i] = tmp;
			}
		}
	}
}

void BinarSearch(int* arr, const int size, int key) {
	bool flag = false;
	int l = 0; // лева€ граница
	int r = size-1; // права€ граница
	int mid;
	while ((l <= r) && (flag != true)) {
		mid = (l + r) / 2; // считываем срединный индекс отрезка [l,r]
		if (arr[mid] == key) flag = true; //провер€ем ключ со серединным элементом
		if (arr[mid] > key) r = mid - 1; // провер€ем, какую часть нужно отбросить
		else l = mid + 1;
	}
	if (flag) cout << "iKey = "<< mid<<endl;
	else cout << "No this element in massive!"<<endl;
}


void VisualBinarSearch(int* arr, const int size, int key,int x,int y)
{
	VisualOutPut(arr, size, x,y);

	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	// скрыть курсор
	CONSOLE_CURSOR_INFO structCursorInfo;
	GetConsoleCursorInfo(h, &structCursorInfo);
	structCursorInfo.bVisible = FALSE;
	SetConsoleCursorInfo(h, &structCursorInfo);

	COORD ckey = { 1,3 };

	enum maze_objects { HALL, WALL, GOLD, VRAG };
	enum colors { BLUE = 9, RED = 12, YELLOW = 14, DARKGREEN = 2, WHITE = 7, DARKGRAY=8,LIGHTGREEN=10 };
	
	int key_color = BLUE;
	int index_color = YELLOW;
	int mid_color = LIGHTGREEN;

	SetConsoleCursorPosition(h, ckey);
	cout << "key = ";
	SetConsoleTextAttribute(h, key_color);
	cout << key << endl << endl;
	SetConsoleTextAttribute(h, WHITE);

	bool flag = false;
	int iMid;
	int l = 0; // лева€ граница
	int r = 9; // права€ граница

	int dll = -1;
	int dlr = -1;
	int drl = size;
	int drr = size;
	int tmp = 0;

	while ((l <= r) && (flag != true)) {
		iMid = (l + r) / 2; // считываем средний индекс отрезка
		// окрасить arr[iMid]
		if (arr[iMid] != key) 
			SetConsoleTextAttribute(h, mid_color);
		else 
			SetConsoleTextAttribute(h, index_color);
			ckey.X = x + iMid * 4 + 11;
			ckey.Y = y + 2;
			SetConsoleCursorPosition(h, ckey);
			cout << iMid;
			ckey.Y = y - 2;
			ckey.X = x + iMid * 4 + 10;
			SetConsoleCursorPosition(h, ckey);
			cout << "mid";

		if (arr[iMid] == key) flag = true;// провер€ем ключ со серединным элементом
		else 
		if (arr[iMid] > key) {	// провер€ем, какую часть нужно отбросить
			r = iMid - 1; 
			ckey.X = 30;
			ckey.Y = 1;
			SetConsoleCursorPosition(h, ckey);
			cout << "Mid > key";
			Sleep(3000);
			// затемнить правую часть
			//for (int i = iMid + 1; i < size; i++) {
			//	SetConsoleTextAttribute(h, DARKGRAY);
			//	ckey.X = x + i* 4 + 11;
			//	ckey.Y = y + 2;
			//	SetConsoleCursorPosition(h, ckey);
			//	cout << i;
			//}

			// отбросить правую часть
			tmp = drl;
			drl = iMid;
			drr = tmp - 1;
			//ckey.Y = 2;
			//ckey.X = 40;
			//SetConsoleCursorPosition(h, ckey);
			//cout << " drl = " << drl << " drr = " << drr;
			for (int i = drl; i <= drr; i++) {
					ckey.X = x + i* 4 + 11;
					ckey.Y = y + 2;
					SetConsoleCursorPosition(h, ckey);
					cout << " ";
					ckey.Y = y + 6;
					SetConsoleCursorPosition(h, ckey);
					cout << " ";
			}
			Sleep(3000);
		}
		else
		{
			l = iMid + 1;
			ckey.X = 30;
			ckey.Y = 1;
			SetConsoleCursorPosition(h, ckey);
			cout << "Mid < key";
			Sleep(3000);
			// затемнить левую часть
			//for (int i = 0; i < iMid; i++) {
			//	SetConsoleTextAttribute(h, DARKGRAY);
			//	ckey.X = x + i * 4 + 11;
			//	ckey.Y = y + 2;
			//	SetConsoleCursorPosition(h, ckey);
			//	cout << i;
			//}

			// отбросить левую часть
			tmp = dlr;
			dlr = iMid;
			dll = tmp + 1;
			//ckey.X = 20;
			//ckey.Y = 2;
			/*SetConsoleCursorPosition(h, ckey);
			cout << " dll = " << dll << " dlr = " << dlr;
			*/for (int i = dll; i <= dlr; i++) {
				ckey.X = x + i * 4 + 11;
				ckey.Y = y + 2;
				SetConsoleCursorPosition(h, ckey);
				cout << " ";
				ckey.Y = y + 6;
				SetConsoleCursorPosition(h, ckey);
				cout << " ";
			}
			Sleep(3000);
		}

		ckey.Y = y - 2;
		ckey.X = x + iMid * 4 + 10;
		SetConsoleCursorPosition(h, ckey);
		cout << "   ";
	}


	if (flag)
	{
		ckey.X = 1;
		ckey.Y = 5;
		SetConsoleCursorPosition(h, ckey);
		cout << "iKey = ";
		SetConsoleTextAttribute(h, index_color);
		cout << iMid << endl;
		SetConsoleTextAttribute(h, WHITE);

	}
		
		
	else cout << "Sorry, no this element!";
	ckey.Y = 20;
	SetConsoleCursorPosition(h, ckey);
}



void Color() {
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	for (int i = 0; i < 16; i++) {
		SetConsoleTextAttribute(h, i);
		cout << i << endl;
	}
}