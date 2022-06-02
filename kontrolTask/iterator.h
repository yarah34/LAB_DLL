//---------------------------------------------------------------------------

#ifndef iteratorH
#define iteratorH
#include "abstract_class.h"
//---------------------------------------------------------------------------
class IteratorFS {
	public:
		class FileSystemClass *fileSystem;
		DWORD index;

		IteratorFS(FileSystemClass *fileSystem);

		void First();
		void Next();
		bool IsDone();
		char* GetCurrent();

};
#endif
