#include <iostream>
#include "VisualDLL.h"


using namespace std;


int main()
{
    setlocale(0, "");
    wchar_t* Name = new wchar_t[80];
    MyName(Name);
    wcout << Name << endl;
    cout << NumberOfGroup() << endl;
    system("pause");

    return 0;
}
