#include <stdio.h>
#include <iostream>
#include <vector>
#include <windows.h>

using namespace std;

 void main ()
{
	UINT64 time1, time2, time3, time4;
	GetSystemTimeAsFileTime((LPFILETIME)&time1);
	for (int i = 0; i < 1000000; i++)
	{
	int *a = new int[10000];
	delete[] a;
	}
	GetSystemTimeAsFileTime((LPFILETIME)&time2);
	GetSystemTimeAsFileTime((LPFILETIME)&time3);
	for (int i = 0; i < 1000000; i++)
	{
	vector<int> a(10000);
	}
	GetSystemTimeAsFileTime((LPFILETIME)&time4);

	double newWork = (double)(time2 - time1)*1e-7; //перевод в секунды

	double vectorWork = (double) (time4 - time3)*1e-7; //перевод в секунды

	cout << "WorkTime in seconds of NEW: " << newWork << endl;
	cout << "WorkTime in seconds of VECTOR: " << vectorWork << endl;

	system("pause");

}
