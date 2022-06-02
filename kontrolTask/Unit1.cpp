//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "VirtualTrees"
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
    VirtualStringTree1->NodeDataSize = sizeof(DBStruct);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::ButtonStartClick(TObject *Sender)
{
	wchar_t MediaType = UnicodeString(Form1->EditDiskName->Text).w_str()[0];
	bool EmptyClusters = CheckBoxEmptyClusters->Checked;

	FileSystem_Type Type = FindFileSystemType(MediaType);

	if (Type == NULL) {
		ShowMessage("File system not found (supports only exFAT and FAT32)");
		return;
	}

	FileSystemClass* fileSystem = CreateFileSystem(Type, MediaType);

	if (Type == FileSystem_Type::exFAT_Type) {
		LabelFS->Caption = "exFAT";
	} else {
		LabelFS->Caption = "FAT32";
	}

	LabelSizeFS->Caption = UnicodeString(fileSystem->sizeFS);
	LabelClustersNumber->Caption = UnicodeString(fileSystem->clustersNumber);
	LabelClusterSize->Caption = UnicodeString(fileSystem->clusterSize);

	if (!EmptyClusters) {
		fileSystem = new DecoratorFS(fileSystem);
	}

	IteratorFS* iterator = new IteratorFS(fileSystem);
	readThread = new ReadThread(false, iterator);

	ButtonDeleteAll->Enabled = false;
	ButtonDeleteChosen->Enabled = false;
	ButtonStart->Enabled = false;
    ButtonStop->Enabled = true;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::VirtualStringTree1GetText(TBaseVirtualTree *Sender, PVirtualNode Node,
		  TColumnIndex Column, TVSTTextType TextType, UnicodeString &CellText)

{
	if (Node == NULL) return;
	DBStruct* nodeData = (DBStruct*) VirtualStringTree1->GetNodeData(Node);

	switch (Column)
	{
		case 0:
		{
			CellText = nodeData->id;
			break;
		}
		case 1:
		{
			CellText = nodeData->cluster;
			break;
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm1::ButtonStopClick(TObject *Sender)
{
	readThread->Terminate();
	ButtonStart->Enabled = true;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::ButtonDeleteChosenClick(TObject *Sender)
{
	//Узнать, какой узел выделен
	PVirtualNode selectedNode = VirtualStringTree1->FocusedNode;

	if (selectedNode == NULL) return;

    //Получить дерево для редактирования
	DBStruct* nodeData = (DBStruct*) VirtualStringTree1->GetNodeData(selectedNode);

	deleteChosenRecord(nodeData->id);

	VirtualStringTree1->BeginUpdate();
	VirtualStringTree1->DeleteNode(selectedNode);
	VirtualStringTree1->EndUpdate();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::ButtonDeleteAllClick(TObject *Sender)
{
	// Очищение таблицы
	deleteAllRecords();
	VirtualStringTree1->Clear();

	ButtonDeleteAll->Enabled = false;
	ButtonDeleteChosen->Enabled = false;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button1Click(TObject *Sender)
{
	fillVST((char*)EditSearch->Text.w_str());
}
//---------------------------------------------------------------------------
