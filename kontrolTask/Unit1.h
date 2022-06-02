//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "VirtualTrees.hpp"
#include "abstract_class.h"
#include "iterator.h"
#include "ReadThread.h"
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TLabel *Label1;
	TLabel *Label2;
	TLabel *Label3;
	TLabel *Label4;
	TLabel *Label5;
	TLabel *Label6;
	TCheckBox *CheckBoxEmptyClusters;
	TEdit *EditDiskName;
	TEdit *EditSearch;
	TLabel *LabelFS;
	TLabel *LabelSizeFS;
	TLabel *LabelClustersNumber;
	TLabel *LabelClusterSize;
	TButton *ButtonStart;
	TButton *ButtonStop;
	TVirtualStringTree *VirtualStringTree1;
	TButton *ButtonDeleteChosen;
	TButton *ButtonDeleteAll;
	TLabel *Label7;
	TButton *Button1;
	void __fastcall ButtonStartClick(TObject *Sender);
	void __fastcall VirtualStringTree1GetText(TBaseVirtualTree *Sender, PVirtualNode Node,
          TColumnIndex Column, TVSTTextType TextType, UnicodeString &CellText);
	void __fastcall ButtonStopClick(TObject *Sender);
	void __fastcall ButtonDeleteChosenClick(TObject *Sender);
	void __fastcall ButtonDeleteAllClick(TObject *Sender);
	void __fastcall Button1Click(TObject *Sender);


private:	// User declarations
    class ReadThread *readThread;
public:		// User declarations
	__fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
typedef struct {
	DWORD id;
	UnicodeString cluster;
} DBStruct;
#endif
