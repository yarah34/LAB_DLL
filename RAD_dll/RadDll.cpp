 #include "RadDll.h"

int __stdcall Grouppa()
{
	return 571227;
}

static wchar_t StName[] = L"Парфилова Мария";

wchar_t * __stdcall Imya()
{
	return StName;
}
