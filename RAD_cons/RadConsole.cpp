#include <iostream>
#include "RadDll.h"
#include "VisualDLL.h"
#include <clocale>

using namespace std;

int main()
{
	setlocale(LC_ALL, "Russian");
	wchar_t *StName = new wchar_t[100];
	Imya(StName);
	wcout << L"Вывод данных о студенте..." << endl;
	cout << "__RAD DLL__" << endl;
	wcout << L"Имя студента: ";
	wcout << StName << endl;
	wcout << L"Группа студента: ";
	cout << Grouppa() << endl;

	wchar_t *Name = new wchar_t[100];
	MyName(Name);
	cout << "__VS DLL__" << endl;
	wcout << L"Имя студента: ";
	wcout << Name << endl;
	wcout << L"Группа студента: ";
	cout << NumberOfGroup() << endl;
	system("pause");
	return 0;
}
