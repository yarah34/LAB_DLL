#include <iostream>
#include "RadDll.h"
#include "VisualDLL.h"

using namespace std;

int main()
{
	setlocale(0, "");
	wchar_t *StName = new wchar_t[80];
	Imya(StName);
	cout << "__RAD DLL__" << endl;
	cout << "Вывод имени студента: " << endl;
	wcout << StName << endl;
	cout << "Вывод группы студента: " << endl;
	cout << Grouppa() << endl;

	wchar_t *Name = new wchar_t[80];
	MyName(Name);
	cout << "__VS DLL__" << endl;
	cout << "Вывод имени студента: " << endl;
	wcout << Name << endl;
	cout << "Вывод имени студента: " << endl;
	cout << NumberOfGroup() << endl;
	system("pause");
	return 0;
}
