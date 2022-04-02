#pragma hdrstop
#pragma argsused

#include <tchar.h>
#include <stdio.h>
#include "sqlite3.h"

using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{

	setlocale(LC_ALL, "Russian");

	// ��������� ����������:
	sqlite3* Database;

	// ��������� ���� ������:
	int openResult = sqlite3_open16(L"C:\\Users\\Mash\\Documents\\Embarcadero\\Studio\\Projects\\db_sqlite.db", &Database);
	/* Database filename (UTF-16) */

	// � ������ ����������� �������� ������������ 0.

	// ���������� �������
	const char *errmsg;
	sqlite3_stmt *pStatement;

	int result = sqlite3_prepare16_v2(Database,L"SELECT * FROM russian_pet_names", -1, &pStatement, NULL); // UTF-16

	if(result != SQLITE_OK)
	{
		errmsg = sqlite3_errmsg(Database);
		printf("DB error %s \n", errmsg);
	}
	else {
        while (true)
		{
			result = sqlite3_step(pStatement);
			if(result != SQLITE_ROW)
			{
				break;
			}

			wchar_t *name = (wchar_t*)sqlite3_column_text16(pStatement, 0);
			wchar_t *owner = (wchar_t*)sqlite3_column_text16(pStatement, 1);
			wprintf (L"��� ���������: %s \n", name);
			wprintf (L"��� �������: %s \n\n", owner);
		}

		// ���������� ��������� �������
		sqlite3_finalize(pStatement);
	}

	// ��������� ���� ������:
	sqlite3_close(Database);
	return 0;
}
