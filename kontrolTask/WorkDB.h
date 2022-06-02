//---------------------------------------------------------------------------

#ifndef WorkDBH
#define WorkDBH
#include "sqlite3.h"
#include "Unit1.h"
#include <vcl.h>
//---------------------------------------------------------------------------

void fillVST(char *searchSign);
void addRecord(char *dataBuffer, DWORD clusterSize);
void deleteAllRecords();
void deleteChosenRecord(DWORD id);

#endif
