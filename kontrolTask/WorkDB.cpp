//---------------------------------------------------------------------------

#pragma hdrstop

#include "WorkDB.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

void fillVST(char *searchSign) {
	// Объявляем переменную:
	sqlite3* Database;

	// Открываем базу данных:
	int openResult = sqlite3_open16(L".\\fs_db.db", &Database);
	/* Database filename (UTF-16) */

	// В случае нормального открытия возвращается 0.

	if (openResult == 0)
	{
		// Подготовка запроса
		const char *errmsg;
		sqlite3_stmt *pStatement;

		wchar_t *sql = new wchar_t[256];
		swprintf(sql, 256,
			L"SELECT id, cluster FROM fs_db WHERE cluster LIKE '%%%s%%';",
			searchSign
		);

		int result = sqlite3_prepare16_v2(Database,sql, -1, &pStatement, NULL); // UTF-16

		if(result == SQLITE_OK) {
			Form1->VirtualStringTree1->Clear();
			Form1->VirtualStringTree1->BeginUpdate();
			while (true)
			{
				result = sqlite3_step(pStatement);
				if(result != SQLITE_ROW) break;

				// Создаем узел
				PVirtualNode entryNode = Form1->VirtualStringTree1->AddChild(Form1->VirtualStringTree1->RootNode);

				//Заполняем данные узла
				DBStruct *nodeData = (DBStruct*)Form1->VirtualStringTree1->GetNodeData(entryNode);

				nodeData->id = sqlite3_column_int(pStatement, 0);
				nodeData->cluster = UnicodeString((char*)sqlite3_column_blob(pStatement, 1), sqlite3_column_bytes(pStatement, 1));
			}

			Form1->VirtualStringTree1->EndUpdate();
		} else {
			ShowMessage("result = "+UnicodeString(result));
        }

		// Завершение обработки запроса
		sqlite3_finalize(pStatement);
	}

	sqlite3_close(Database);
}

void addRecord(char *dataBuffer, DWORD clusterSize) {
	// Объявляем переменную:
	sqlite3* Database;

	// Открываем базу данных:
	int openResult = sqlite3_open16(L".\\fs_db.db", &Database);
	/* Database filename (UTF-16) */

	// В случае нормального открытия возвращается 0.

	if (openResult == 0)
	{
		// Подготовка запроса
		const char *errmsg;
		sqlite3_stmt *pStatement;

		wchar_t *sql = new wchar_t[clusterSize*2];
		swprintf(sql, clusterSize*2, L"INSERT INTO fs_db (cluster) VALUES (?);");

		int result = sqlite3_prepare16_v2(Database,sql, -1, &pStatement, NULL); // UTF-16

		if(result == SQLITE_OK)
		{
			result = sqlite3_bind_blob(pStatement, 1, dataBuffer, clusterSize, SQLITE_STATIC);
			if(result == SQLITE_OK)
			{
				result = sqlite3_step(pStatement);
				if(result != SQLITE_DONE)
				{
					ShowMessage("result = "+UnicodeString(result));
				}
			}
			else
			{
				ShowMessage("result = "+UnicodeString(result));
			}
		}
		else
		{
			errmsg = sqlite3_errmsg(Database);
			ShowMessage("result = "+UnicodeString(errmsg));
		}

		delete sql;

		// Завершение обработки запроса
		sqlite3_finalize(pStatement);
	}

	sqlite3_close(Database);
}

void deleteAllRecords() {
	// Объявляем переменную:
	sqlite3* Database;

	// Открываем базу данных:
	int openResult = sqlite3_open16(L".\\fs_db.db", &Database);
	/* Database filename (UTF-16) */

	// В случае нормального открытия возвращается 0.

	if (openResult == 0)
	{
		// Подготовка запроса
		const char *errmsg;
		sqlite3_stmt *pStatement;

		wchar_t sql[] = L"DELETE FROM fs_db;";

		int result = sqlite3_prepare16_v2(Database,sql, -1, &pStatement, NULL); // UTF-16

		if(result == SQLITE_OK)
		{
			result = sqlite3_step(pStatement);
			if(result != SQLITE_DONE)
			{
				ShowMessage("result = "+UnicodeString(result));
			}
		}
		else
		{
			errmsg = sqlite3_errmsg(Database);
			ShowMessage("result = "+UnicodeString(errmsg));
		}

		// Завершение обработки запроса
		sqlite3_finalize(pStatement);
	}

	sqlite3_close(Database);
}

void deleteChosenRecord(DWORD id) {
	// Объявляем переменную:
	sqlite3* Database;

	// Открываем базу данных:
	int openResult = sqlite3_open16(L".\\fs_db.db", &Database);
	/* Database filename (UTF-16) */

	// В случае нормального открытия возвращается 0.

	if (openResult == 0)
	{
		// Подготовка запроса
		const char *errmsg;
		sqlite3_stmt *pStatement;

		wchar_t sql[] = L"DELETE FROM fs_db WHERE id = ?;";

		int result = sqlite3_prepare16_v2(Database,sql, -1, &pStatement, NULL); // UTF-16

		if(result == SQLITE_OK)
		{
			result = sqlite3_bind_int64(pStatement, 1, id);

			if(result == SQLITE_OK)
			{
                result = sqlite3_step(pStatement);
				if(result == SQLITE_DONE)
				{
					ShowMessage("The record's deleted");
				}
				else
				{
					ShowMessage("result = "+UnicodeString(result));
				}
			}
			else
			{
				ShowMessage("result = "+UnicodeString(result));
			}
		}
		else
		{
			errmsg = sqlite3_errmsg(Database);
			ShowMessage("result = "+UnicodeString(errmsg));
		}

		// Завершение обработки запроса
		sqlite3_finalize(pStatement);
	}

	sqlite3_close(Database);

}