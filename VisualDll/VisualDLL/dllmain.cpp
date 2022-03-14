#include "pch.h"
#include "VisualDLL.h"

int __stdcall NumberOfGroup()
{
	return 571227;
}

void  __stdcall MyName(wchar_t* Name)
{
	wcscpy(Name, L"Мария Парфилова");
}