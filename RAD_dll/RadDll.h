#ifdef LIBRARY_EXPORTS
#define LIBRARY_API __declspec(dllexport)
#else
#define LIBRARY_API __declspec(dllimport)
#endif

extern "C" LIBRARY_API int __stdcall Grouppa();
extern "C" LIBRARY_API void __stdcall Imya(wchar_t* StName);
