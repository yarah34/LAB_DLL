//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "GraphRAD.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button1Click(TObject *Sender)
{
	HINSTANCE hMyDll = LoadLibraryW(L"RadDll");
	if (hMyDll == NULL) {
		ShowMessage("RadDll.dll isn't found");
		return;
	}
	PGrouppa Grouppa;

	Grouppa = (PGrouppa)GetProcAddress(hMyDll,"Grouppa");
	if (Grouppa == NULL) {
		ShowMessage("Grouppa isn't found");
	}
	else {
		Form1->Label2->Caption = Grouppa();
	}

	FreeLibrary(hMyDll);

}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button2Click(TObject *Sender)
{

	HINSTANCE hMyDll = LoadLibraryW(L"RadDll");
	if (hMyDll == NULL) {
		ShowMessage("RadDll.dll isn't found");
		return;
	}
	PImya Imya;

	Imya = (PImya)GetProcAddress(hMyDll,"Imya");
	if (Imya == NULL) {
		ShowMessage("Imya isn't found");
	}
	else {
		Form1->Label3->Caption = Imya();
	}

	FreeLibrary(hMyDll);





}
//---------------------------------------------------------------------------

