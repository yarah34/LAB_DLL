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
		//��������, ����� ���� ����� ����������
		if(myEvent->WaitFor(0) == wrSignaled)
		{

			// ������� ������ � ��
			addRecord(readDataBuffer, bufferSize);

			//����� �����
			myEvent->ResetEvent();
		}


		// ��������� ����� �� ����������
		if(Terminated) break;
	}

	delete readDataBuffer, workDataBuffer;
}
//---------------------------------------------------------------------------
