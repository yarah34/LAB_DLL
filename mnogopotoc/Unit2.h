//---------------------------------------------------------------------------

#ifndef Unit2H
#define Unit2H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
//---------------------------------------------------------------------------
class ReadThread : public TThread
{
private:
	class ProcessThread* ProcessThreadPtr;
	TEvent* myEvent;
protected:
	void __fastcall Execute();
	void __fastcall UpdateLabel();
	void __fastcall UpdateLabelINVALID_HANDLE_VALUE();
	void __fastcall UpdateLabelErrorPosition();
	void __fastcall UpdateLabelErrorbytesRead();
    void __fastcall UpdateLabelEnd();
public:
	__fastcall ReadThread(bool CreateSuspended);
	char dataBuffer[1024*512];
};
//---------------------------------------------------------------------------
#endif
