//---------------------------------------------------------------------------

#include <System.hpp>
#pragma hdrstop

#include "ReadThread.h"
#pragma package(smart_init)
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

__fastcall ReadThread::ReadThread(bool CreateSuspended, IteratorFS *iterator)
	: TThread(CreateSuspended), iterator(iterator)
{
	FreeOnTerminate = true;
	myEvent = new TEvent(NULL, true, false, "", false);
	ProcessThreadPtr = new ProcessThread(true, myEvent, iterator->fileSystem->clusterSize);
}
//---------------------------------------------------------------------------
void __fastcall ReadThread::Execute()
{
    ProcessThreadPtr->Start();

	for (iterator->First(); !iterator->IsDone(); iterator->Next()) {
		Synchronize(&updateStatus);

		ProcessThreadPtr->readDataBuffer = iterator->GetCurrent();
		if (ProcessThreadPtr->readDataBuffer == NULL) {
            break;
		}

		myEvent->SetEvent();
        while (myEvent->WaitFor(0) == wrSignaled)
		{
			if(Terminated) break;
			Sleep(10);
		}

		if (Terminated) break;
	}

	ProcessThreadPtr->Terminate();
	Synchronize(&fillForm);
	delete ProcessThreadPtr;
}
//---------------------------------------------------------------------------

void __fastcall ReadThread::fillForm() {
	fillVST((char*)Form1->EditSearch->Text.w_str());

	Form1->ButtonStart->Enabled = true;
	Form1->ButtonStop->Enabled = false;
	Form1->ButtonDeleteAll->Enabled = true;
	Form1->ButtonDeleteChosen->Enabled = true;
}

void __fastcall ReadThread::updateStatus() {
	Form1->Label7->Caption = UnicodeString(iterator->index);
}
