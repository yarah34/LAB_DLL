#pragma once


#ifdef LIBRARY_EXPORTS
#define LIBRARY_API __declspec(dllexport)
#else
#define LIBRARY_API __declspec(dllimport)
#endif // LIBRARY_EXPORTS

extern "C" LIBRARY_API int __stdcall NumberOfGroup();

extern "C" LIBRARY_API wchar_t * __stdcall MyName();
