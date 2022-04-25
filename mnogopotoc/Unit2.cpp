//---------------------------------------------------------------------------

#include <System.hpp>
#pragma hdrstop

#include "Unit1.h"
#include "Unit2.h"
#include "Unit3.h"
#pragma package(smart_init)
//---------------------------------------------------------------------------
__fastcall ReadThread::ReadThread(bool CreateSuspended)
	: TThread(CreateSuspended)
{
	FreeOnTerminate = true;
	myEvent = new TEvent(NULL, true, false, "", false);
	ProcessThreadPtr = new ProcessThread(myEvent, true);

	ProcessThreadPtr->dataBufferPtr = dataBuffer;
}
//---------------------------------------------------------------------------
void __fastcall ReadThread::Execute()
{

	// Ввод буквы носителя с консоли
	wchar_t MediaType[64]; // массив
	UnicodeString deviceName = Form1->Edit1->Text;
	wchar_t MediaType1 = deviceName.w_str()[0];
	swprintf(MediaType,L"\\\\.\\%c:",MediaType1); //выводит данные в Edit

	HANDLE fileHandle = CreateFile(
		MediaType, // Имя файла/устройства (wchar*)
		GENERIC_READ, // режим доступа
		FILE_SHARE_READ, //Режим совместной работы
		NULL, // Атрибуты безопасности
		OPEN_EXISTING, //способ открытия
		FILE_ATTRIBUTE_NORMAL, //флаги и атрибуты
		NULL
		//Описатель (идентификатор) файла шаблона с правами доступа GENERIC_READ
		);

	if(fileHandle == INVALID_HANDLE_VALUE)
	{
	   Synchronize(&UpdateLabelINVALID_HANDLE_VALUE);
	   CloseHandle(fileHandle);
	   return;
	}

	LARGE_INTEGER sectorOffset;
	sectorOffset.QuadPart = 0; //чтобы позиционироваться в начале

	// Задать позицию
	unsigned long currentPosition = SetFilePointer(
		  fileHandle,
		  sectorOffset.LowPart,// младшая часть LARGE_INTEGER
		  &sectorOffset.HighPart, // старшая часть
		  FILE_BEGIN
	// Точка в файле, относительно которой необходимо позиционироваться
	// (FILE_BEGIN, FILE_CURRENT, FILE_END)
		);

	if(currentPosition != sectorOffset.LowPart)
	{
		Synchronize(&UpdateLabelErrorPosition);
		CloseHandle(fileHandle);
		return;
	}

	ProcessThreadPtr->Start();

	DWORD bytesToRead = 1024*512; // сколько нужно считать
	DWORD bytesRead; // сколько удалось считать


	while(true)
	{
		//Ресурсоемкая операция чтения данных
		// Чтение данных
		bool readResult = ReadFile(
			  fileHandle, // дескриптор
			  dataBuffer, // куда читаем данные
			  bytesToRead,
			  &bytesRead,
			  NULL //ручное управление буферизацией
			);

		if(readResult == false || bytesRead != bytesToRead)
		{
			Synchronize(&UpdateLabelErrorbytesRead);
			Synchronize(&UpdateLabelEnd);
			break;
		}
		Sleep(100);
		Synchronize(&UpdateLabel);

		//Уведомить второй поток о готовности данных
		myEvent->SetEvent();

		Sleep(20);

		while (myEvent->WaitFor(0) == wrSignaled)
		{
			Sleep(10);
		}

		// Завершить поток по требованию
		if(Terminated) break;
	}

	CloseHandle(fileHandle);
	ProcessThreadPtr->Terminate();
	delete ProcessThreadPtr;
}
//---------------------------------------------------------------------------
void __fastcall ReadThread::UpdateLabel()
{
	TColor colors[] = {
	// GREEN - 9
	// YELLOW - 2
	// RED - 1
	clBlack, clRed, clYellow, clLime, clAqua, clBlue, clFuchsia, clWhite,
	clMaroon, clGreen, clOlive, clNavy, clPurple, clTeal, clGray, clSilver
	};
	Form1->Label3->Font->Color = colors[9];
	Form1->Label3->Caption = "Выполнение потока чтения завершено";
}
//---------------------------------------------------------------------------
void __fastcall ReadThread::UpdateLabelINVALID_HANDLE_VALUE()
{
	TColor colors[] = {
	// GREEN - 9
	// YELLOW - 2
	// RED - 1
	clBlack, clRed, clYellow, clLime, clAqua, clBlue, clFuchsia, clWhite,
	clMaroon, clGreen, clOlive, clNavy, clPurple, clTeal, clGray, clSilver
	};
	Form1->Label6->Font->Color = colors[1];
	Form1->Label6->Caption = "INVALID_HANDLE_VALUE";
}
void __fastcall ReadThread::UpdateLabelErrorPosition()
{
	TColor colors[] = {
	// GREEN - 9
	// YELLOW - 2
	// RED - 1
	clBlack, clRed, clYellow, clLime, clAqua, clBlue, clFuchsia, clWhite,
	clMaroon, clGreen, clOlive, clNavy, clPurple, clTeal, clGray, clSilver
	};
	Form1->Label6->Font->Color = colors[1];
	Form1->Label6->Caption = "Error Position";
}
void __fastcall ReadThread::UpdateLabelErrorbytesRead()
{
	TColor colors[] = {
	// GREEN - 9
	// YELLOW - 2
	// RED - 1
	clBlack, clRed, clYellow, clLime, clAqua, clBlue, clFuchsia, clWhite,
	clMaroon, clGreen, clOlive, clNavy, clPurple, clTeal, clGray, clSilver
	};
	Form1->Label6->Font->Color = colors[1];
	Form1->Label6->Caption = "Error bytesRead";
}
void __fastcall ReadThread::UpdateLabelEnd()
{
	TColor colors[] = {
	// GREEN - 9
	// YELLOW - 2
	// RED - 1
	clBlack, clRed, clYellow, clLime, clAqua, clBlue, clFuchsia, clWhite,
	clMaroon, clGreen, clOlive, clNavy, clPurple, clTeal, clGray, clSilver
	};
	Form1->Label3->Font->Color = colors[9];
	Form1->Label3->Caption = "Обработка завершена";
}


