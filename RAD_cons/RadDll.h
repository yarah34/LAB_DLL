#ifdef LIBRARY_EXPORTS
#define LIBRARY_API __declspec(dllexport)
#else
#define LIBRARY_API __declspec(dllimport)
#endif

extern "C" LIBRARY_API int __stdcall Grouppa();
extern "C" LIBRARY_API wchar_t* __stdcall Imya();
