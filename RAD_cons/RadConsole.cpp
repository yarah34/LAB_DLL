#include <iostream>
#include "RadDll.h"
#include "VisualDLL.h"

using namespace std;

int main()
{
	setlocale(0, "");
	wcout << Imya() << endl;
	cout << Grouppa() << endl;

	wcout << MyName() << endl;
	cout << NumberOfGroup() << endl;
	system("pause");
	return 0;
}
