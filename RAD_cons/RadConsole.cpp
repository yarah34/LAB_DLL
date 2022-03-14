#include <iostream>
#include "RadDll.h"
#include "VisualDLL.h"

using namespace std;

int main()
{
	setlocale(0, "");
	wchar_t *StName = new wchar_t[80];
	Imya(StName);
	cout << "RAD DLL" << endl;
	wcout << StName << endl;
	cout << Grouppa() << endl;

	wchar_t *Name = new wchar_t[80];
	MyName(Name);
	cout << "VS DLL" << endl;
	wcout << Name << endl;
	cout << NumberOfGroup() << endl;
	system("pause");
	return 0;
}
