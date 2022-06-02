//---------------------------------------------------------------------------

#pragma hdrstop

#include "iterator.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

IteratorFS::IteratorFS(FileSystemClass *fileSystem)
	: fileSystem(fileSystem) {
}

void IteratorFS::First() {
	index = 0;
}

void IteratorFS::Next() {
	index++;
}

bool IteratorFS::IsDone() {
	return index == -1 || index + 1 == fileSystem->clustersNumber;
}

char *IteratorFS::GetCurrent() {
	char *dataBuffer = new char[fileSystem->clusterSize];
	index = fileSystem->readCluster(dataBuffer, index);

	return index == -1 ? NULL : dataBuffer;
}

