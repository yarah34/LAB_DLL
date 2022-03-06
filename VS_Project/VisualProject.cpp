#include <iostream>
#include "VisualDLL.h"


using namespace std;

int main()
{
    setlocale(0, "");
    wcout << MyName() << endl;
    cout << NumberOfGroup() << endl;
    system("pause");

    return 0;
}
