#include <iostream>
#include "RadDll.h"
#include "VisualDLL.h"

using namespace std;

int main()
{
	setlocale(0, "");
	wchar_t *StName = new wchar_t[100];
	Imya(StName);
    cout << "����� ������ � ��������..." << endl;
	cout << "__RAD DLL__" << endl;
	cout << "��� ��������: " << endl;
	wcout << StName << endl;
	cout << "������ ��������: " << endl;
	cout << Grouppa() << endl;

	wchar_t *Name = new wchar_t[100];
	MyName(Name);
	cout << "__VS DLL__" << endl;
	cout << "��� ��������: " << endl;
	wcout << Name << endl;
	cout << "������ ��������: " << endl;
	cout << NumberOfGroup() << endl;
	system("pause");
	return 0;
}
