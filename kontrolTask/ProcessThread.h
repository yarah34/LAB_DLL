//---------------------------------------------------------------------------

#ifndef ProcessThreadH
#define ProcessThreadH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include "WorkDB.h"
#include <cstring>
//---------------------------------------------------------------------------
class ProcessThread : public TThread
{
private:
	TEvent* myEvent;
    DWORD bufferSize;
protected:
	void __fastcall Execute();
public:
	__fastcall ProcessThread(bool CreateSuspended, TEvent* myEvent, DWORD bufferSize);

	char *readDataBuffer;
	char *workDataBuffer;
};
//---------------------------------------------------------------------------
#endif
