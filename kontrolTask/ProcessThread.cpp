//---------------------------------------------------------------------------

#include <System.hpp>
#pragma hdrstop

#include "ProcessThread.h"
#pragma package(smart_init)
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------

__fastcall ProcessThread::ProcessThread(bool CreateSuspended, TEvent* myEvent, DWORD bufferSize)
	: TThread(CreateSuspended), myEvent(myEvent), bufferSize(bufferSize)
{
	FreeOnTerminate = true;
	workDataBuffer = new char[bufferSize];
}
//---------------------------------------------------------------------------
void __fastcall ProcessThread::Execute()
{
	while(true)
	{
		//ожидание, когда флаг будет установлен
		if(myEvent->WaitFor(0) == wrSignaled)
		{

			// Вставка данных в БД
			addRecord(readDataBuffer, bufferSize);

			//Сброс флага
			myEvent->ResetEvent();
		}


		// Завершить поток по требованию
		if(Terminated) break;
	}

	delete readDataBuffer, workDataBuffer;
}
//---------------------------------------------------------------------------
