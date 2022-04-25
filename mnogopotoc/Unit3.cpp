//---------------------------------------------------------------------------

#include <System.hpp>
#pragma hdrstop

#include "Unit1.h"
#include "Unit2.h"
#include "Unit3.h"
#pragma package(smart_init)
//---------------------------------------------------------------------------

__fastcall ProcessThread::ProcessThread(TEvent* myEvent, bool CreateSuspended)
	: TThread(CreateSuspended), myEvent(myEvent)
{
	FreeOnTerminate = true;
}
//---------------------------------------------------------------------------
void __fastcall ProcessThread::Execute()
{
	i = 0;
	while(true)
	{
		//ожидание, когда флаг будет установлен
		if(myEvent->WaitFor(0) == wrSignaled)
		{
			//Принять данные
			Sleep(50);


			//Сброс флага
			myEvent->ResetEvent();
		}

		//Ресурсоемкая операция обработки данных
		Sleep(200);

		// Завершить поток по требованию
		if(Terminated) break;
		Synchronize(&UpdateLabel);
		i++;
	}
}
//---------------------------------------------------------------------------
void __fastcall ProcessThread::UpdateLabel()
{
	Form1->Label4->Caption = UnicodeString(i);
	//Form1->Label4->Caption = UnicodeString(i) + u"\n" + UnicodeString(dataBufferPtr);
}
