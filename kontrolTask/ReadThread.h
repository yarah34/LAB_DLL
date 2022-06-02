//---------------------------------------------------------------------------

#ifndef ReadThreadH
#define ReadThreadH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include "iterator.h"
#include "ProcessThread.h"
#include "Unit1.h"
#include "WorkDB.h"
//---------------------------------------------------------------------------
class ReadThread : public TThread
{
private:
	class ProcessThread *ProcessThreadPtr;
	TEvent *myEvent;
	class IteratorFS *iterator;
protected:
	void __fastcall Execute();
	void __fastcall fillForm();
    void __fastcall updateStatus();
public:
	__fastcall ReadThread(bool CreateSuspended, IteratorFS *iterator);
};
//---------------------------------------------------------------------------
#endif
