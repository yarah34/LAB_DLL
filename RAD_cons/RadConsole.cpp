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
	wcout << L"����� ������ � ��������..." << endl;
	cout << "__RAD DLL__" << endl;
	wcout << L"��� ��������: ";
	wcout << StName << endl;
	wcout << L"������ ��������: ";
	cout << Grouppa() << endl;

	wchar_t *Name = new wchar_t[100];
	MyName(Name);
	cout << "__VS DLL__" << endl;
	wcout << L"��� ��������: ";
	wcout << Name << endl;
	wcout << L"������ ��������: ";
	cout << NumberOfGroup() << endl;
	system("pause");
	return 0;
}
