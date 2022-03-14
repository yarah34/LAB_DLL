#include "pch.h"
#include "VisualDLL.h"

int __stdcall NumberOfGroup()
{
	return 571227;
}

static wchar_t Name[] = L"Парфилова Мария";

wchar_t * __stdcall MyName()
{
	return Name;
}