//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include <stdio.h>
#include "sqlite3.h"
#include "virttreeview.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "VirtualTrees"
#pragma resource "*.dfm"
TForm1 *Form1;

using namespace std;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
	VirtualStringTree1->NodeDataSize = sizeof(TreeNodeStruct);
}

void writeTable(sqlite3* Database)
{
	setlocale(LC_ALL, "Russian");

	// Открываем базу данных:
	int openResult = sqlite3_open16(L"C:\\Users\\1\\Documents\\Embarcadero\\Studio\\Projects\\VirtualTreeView\\db_sqlite.db", &Database);
	/* Database filename (UTF-16) */

	// В случае нормального открытия возвращается 0.

	// Подготовка запроса
	const char *errmsg;
	sqlite3_stmt *pStatement;

	int result = sqlite3_prepare16_v2(Database,L"SELECT * FROM russian_pet_names", -1, &pStatement, NULL); // UTF-16

	if(result != SQLITE_OK)
	{
	errmsg = sqlite3_errmsg(Database);
		printf("DB error %s \n", errmsg);
	}
	else {
			Form1->VirtualStringTree1->Clear();
			Form1->VirtualStringTree1->BeginUpdate();
		while (true)
		{
			result = sqlite3_step(pStatement);
			if(result != SQLITE_ROW) break;

			// Создаем узел
			PVirtualNode entryNode = Form1->VirtualStringTree1->AddChild(Form1->VirtualStringTree1->RootNode);

			//Заполняем данные узла
			TreeNodeStruct *nodeData = (TreeNodeStruct*)Form1->VirtualStringTree1->GetNodeData(entryNode);

			nodeData->ID = sqlite3_column_int(pStatement, 0);
			nodeData->nameAnimal = UnicodeString((wchar_t*)sqlite3_column_text16(pStatement, 1));
			nodeData->nameOwner = UnicodeString((wchar_t*)sqlite3_column_text16(pStatement, 2));
			nodeData->dateComing = UnicodeString((wchar_t*)sqlite3_column_text16(pStatement, 3));
		}

		Form1->VirtualStringTree1->EndUpdate();

	}

	// Завершение обработки запроса
	sqlite3_finalize(pStatement);

}
//---------------------------------------------------------------------------
void __fastcall TForm1::ЗаполнитьClick(TObject *Sender)
{
    setlocale(LC_ALL, "Russian");

	// Объявляем переменную:
	sqlite3* Database;

	// Открываем базу данных:
	int openResult = sqlite3_open16(L"C:\\Users\\1\\Documents\\Embarcadero\\Studio\\Projects\\VirtualTreeView\\db_sqlite.db", &Database);
	/* Database filename (UTF-16) */

	// В случае нормального открытия возвращается 0.

	if (openResult == 0)
	{
		writeTable(Database);
	}
	else
	{
		ShowMessage("WriteOpenResult =" +UnicodeString(openResult));
	}

}
//---------------------------------------------------------------------------
void __fastcall TForm1::VirtualStringTree1GetText(TBaseVirtualTree *Sender, PVirtualNode Node,
          TColumnIndex Column, TVSTTextType TextType, UnicodeString &CellText)

{
	if(Node == NULL) return;
    TreeNodeStruct *nodeData = (TreeNodeStruct*)VirtualStringTree1->GetNodeData(Node);

	switch(Column)
	{
		case 0:
		{
			CellText = UnicodeString(nodeData->nameAnimal);
			break;

		}
		case 1:
		{
			CellText = UnicodeString(nodeData->nameOwner);
			break;

		}
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm1::VirtualStringTree1AddToSelection(TBaseVirtualTree *Sender,
		  PVirtualNode Node)
{
    if(Node == NULL) return;
	TreeNodeStruct *nodeData = (TreeNodeStruct*)VirtualStringTree1->GetNodeData(Node);
	Label2->Caption = nodeData->dateComing;
}
//---------------------------------------------------------------------------
void deleteNote(sqlite3* Database, int id)
{
	// Подготовка запроса
	const char *errmsg;
	sqlite3_stmt *pStatement;

	wchar_t size[120];
	swprintf(size, 120, L"DELETE FROM russian_pet_names WHERE id = %d;",id);

	int result = sqlite3_prepare16_v2(Database,size, -1, &pStatement, NULL); // UTF-16

	if(result == SQLITE_OK)
	{
		result = sqlite3_step(pStatement);
		if(result == SQLITE_DONE)
		{
			ShowMessage("Note's deleted");
		}
		else
		{
			ShowMessage("result = "+UnicodeString(result));
		}
	}
	else
	{
		errmsg = sqlite3_errmsg(Database);
		printf("DB error %s \n", errmsg);
	}

	// Завершение обработки запроса
	sqlite3_finalize(pStatement);
}
void __fastcall TForm1::Button1Click(TObject *Sender)
{
	//Узнать, какой узел выделен
	PVirtualNode selectedNode = VirtualStringTree1->FocusedNode;

	if (selectedNode == NULL) return;

	//Получить дерево для редактирования
	TreeNodeStruct* nodeData = (TreeNodeStruct*) VirtualStringTree1->GetNodeData(selectedNode);

	// Объявляем переменную:
	sqlite3* Database;

	// Открываем базу данных:
	int openResult = sqlite3_open16(L"C:\\Users\\1\\Documents\\Embarcadero\\Studio\\Projects\\VirtualTreeView\\db_sqlite.db", &Database);
	/* Database filename (UTF-16) */
	// В случае нормального открытия возвращается 0.

	if (openResult == 0)
	{
		deleteNote(Database, nodeData->ID);
		VirtualStringTree1->BeginUpdate();
		VirtualStringTree1->DeleteNode(selectedNode);
		VirtualStringTree1->EndUpdate();
	}
	else
	{
		ShowMessage("DeleteNoteOpenResult =" +UnicodeString(openResult));
	}

}

//---------------------------------------------------------------------------
void deleteTable(sqlite3* Database) {

	// Подготовка запроса
	const char *errmsg;
	sqlite3_stmt *pStatement;

	wchar_t sql[] = L"DROP TABLE IF EXISTS urls;";

	int result = sqlite3_prepare16_v2(Database,L"DROP TABLE IF EXISTS russian_pet_names;", -1, &pStatement, NULL); // UTF-16

	if(result == SQLITE_OK)
	{
		result = sqlite3_step(pStatement);
		if(result == SQLITE_DONE)
		{
			ShowMessage("Table's deleted");
		}
		else
		{
			ShowMessage("result = "+UnicodeString(result));
		}
	}
	else
	{
		errmsg = sqlite3_errmsg(Database);
		printf("DB error %s \n", errmsg);
	}

	// Завершение обработки запроса
	sqlite3_finalize(pStatement);
}


void __fastcall TForm1::Button2Click(TObject *Sender)
{

	// Объявляем переменную:
	sqlite3* Database;

    // Открываем базу данных:
	int openResult = sqlite3_open16(L"C:\\Users\\1\\Documents\\Embarcadero\\Studio\\Projects\\VirtualTreeView\\db_sqlite.db", &Database);
	/* Database filename (UTF-16) */

	// В случае нормального открытия возвращается 0.

	if (openResult == 0)
	{

		deleteTable(Database);
        VirtualStringTree1->Clear();
	}
	else
	{
		ShowMessage("DeleteTableOpenResult =" +UnicodeString(openResult));
	}
}
//---------------------------------------------------------------------------

