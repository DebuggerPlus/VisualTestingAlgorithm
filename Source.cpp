// debuggerplus.com
#include <iostream>
#include "Header.h"
#include<windows.h>
#include<conio.h>
using namespace std;

void main()
{
	const int size = 10;
	int arr[size] = { 0 };
	int key = 7;
	int direct = 0;
	system("pause");
	system("cls");
	do {
	Init(arr, size);
	SelectSort(arr, size);
	// VisualBinarSearch(arr, size, key,20,5);
	BinarSearch(arr, size, key);
	cout << "Press any key for repeat! Esc for exit!";
	direct = _getch();
	Sleep(1000);
	system("cls");
	} while (direct != 27);
	exit(0);
}
