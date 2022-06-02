//---------------------------------------------------------------------------

#pragma hdrstop

#include "abstract_class.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

FileSystemClass::FileSystemClass(wchar_t MediaType) {
	diskName = new wchar_t[64];
	swprintf(diskName,L"\\\\.\\%c:",MediaType);
}

FileSystemClass::FileSystemClass(wchar_t *diskName)
	: diskName(diskName) {
}


DWORD FileSystemClass::readCluster(char *dataBuffer, DWORD i) {

	HANDLE fileHandle = CreateFile(
		diskName, // ��� �����/���������� (wchar*)
		GENERIC_READ, // ����� �������
		FILE_SHARE_READ | FILE_SHARE_WRITE, //����� ���������� ������
		NULL, // �������� ������������
		OPEN_EXISTING, //������ ��������
		FILE_ATTRIBUTE_NORMAL, //����� � ��������
		NULL
		//��������� (�������������) ����� ������� � ������� ������� GENERIC_READ
	);

	if(fileHandle != INVALID_HANDLE_VALUE)
	{
		LARGE_INTEGER sectorOffset;
		sectorOffset.QuadPart = (LONGLONG)(clusterSize*i); //����� ����������������� � ������

		// ������ �������
		DWORD currentPosition = SetFilePointer(
			fileHandle,
			sectorOffset.LowPart,// ������� ����� LARGE_INTEGER
			&sectorOffset.HighPart, // ������� �����
			FILE_BEGIN
		// ����� � �����, ������������ ������� ���������� �����������������
		// (FILE_BEGIN, FILE_CURRENT, FILE_END)
		);
		if(currentPosition == sectorOffset.LowPart)
		{
			DWORD bytesToRead = clusterSize; // ������� ����� �������
			DWORD bytesRead; // ������� ������� �������

			// ������ ������
			bool readResult = ReadFile(
				  fileHandle, // ����������
				  dataBuffer, // ���� ������ ������
				  bytesToRead,
				  &bytesRead,
				  NULL //������ ���������� ������������
			);
			CloseHandle(fileHandle);

			if(readResult == false || bytesRead != bytesToRead)
			{
				return -1;
			} else
			{
				return i;
			}
		} else
		{
			CloseHandle(fileHandle);
			return -1;
		}
	} else
	{
		CloseHandle(fileHandle);
		return -1;
	}

}

DecoratorFS::DecoratorFS(FileSystemClass *fileSystem)
	: FileSystemClass(fileSystem->diskName), fileSystem(fileSystem) {
	this->sizeFS = fileSystem->sizeFS;
	this->clustersNumber = fileSystem->clustersNumber;
	this->clusterSize = fileSystem->clusterSize;
}

DWORD DecoratorFS::readCluster(char *dataBuffer, DWORD i) {

	while (true) {
		i = fileSystem->readCluster(dataBuffer, i);

		// ���� i == -1, �� ������ ���������
		if (i == -1) {
			return -1;
		}

		for (DWORD j = 0; j < fileSystem->clusterSize; j++) {
			if (dataBuffer[j] != (char)0x00) {
				return i;
			}
		}

		// ������� ������
		i++;
	}
}

FAT32_FileSystem::FAT32_FileSystem(wchar_t MediaType)
	: FileSystemClass(MediaType) {
    char dataBuffer[512];

	FAT32_BootRecord *pBootRecord = (FAT32_BootRecord*)dataBuffer;

	HANDLE fileHandle = CreateFile(
		diskName, // ��� �����/���������� (wchar*)
		GENERIC_READ, // ����� �������
		FILE_SHARE_READ | FILE_SHARE_WRITE, //����� ���������� ������
		NULL, // �������� ������������
		OPEN_EXISTING, //������ ��������
		FILE_ATTRIBUTE_NORMAL, //����� � ��������
		NULL
		//��������� (�������������) ����� ������� � ������� ������� GENERIC_READ
	);

	if(fileHandle != INVALID_HANDLE_VALUE)
	{
		LARGE_INTEGER sectorOffset;
		sectorOffset.QuadPart = 0; //����� ����������������� � ������

		// ������ �������
		DWORD currentPosition = SetFilePointer(
			fileHandle,
			sectorOffset.LowPart,// ������� ����� LARGE_INTEGER
			&sectorOffset.HighPart, // ������� �����
			FILE_BEGIN
		// ����� � �����, ������������ ������� ���������� �����������������
		// (FILE_BEGIN, FILE_CURRENT, FILE_END)
		);
		if(currentPosition == sectorOffset.LowPart)
		{
			DWORD bytesToRead = 512; // ������� ����� �������
			DWORD bytesRead; // ������� ������� �������

			// ������ ������
			bool readResult = ReadFile(
				  fileHandle, // ����������
				  dataBuffer, // ���� ������ ������
				  bytesToRead,
				  &bytesRead,
				  NULL //������ ���������� ������������
			);
			CloseHandle(fileHandle);

			if(readResult == false || bytesRead != bytesToRead) {
			} else {
				DWORD sectorsNumber = pBootRecord->ShestSectorsCount == 0 ? pBootRecord->Numb32SectFat : pBootRecord->ShestSectorsCount;
				sizeFS = (UINT64)(sectorsNumber*pBootRecord->SectorSize);
				clusterSize = (DWORD)(pBootRecord->SectorSize*pBootRecord->ClusterSize);
				clustersNumber = (DWORD)(sectorsNumber*pBootRecord->SectorSize/clusterSize);
			}
		} else {
			CloseHandle(fileHandle);
		}
	} else {
		CloseHandle(fileHandle);
	}
}

exFAT_FileSystem::exFAT_FileSystem(wchar_t MediaType)
	: FileSystemClass(MediaType) {
    char dataBuffer[512];

	exFAT_BootRecord *pBootRecord = (exFAT_BootRecord*)dataBuffer;

	HANDLE fileHandle = CreateFile(
		diskName, // ��� �����/���������� (wchar*)
		GENERIC_READ, // ����� �������
		FILE_SHARE_READ | FILE_SHARE_WRITE, //����� ���������� ������
		NULL, // �������� ������������
		OPEN_EXISTING, //������ ��������
		FILE_ATTRIBUTE_NORMAL, //����� � ��������
		NULL
		//��������� (�������������) ����� ������� � ������� ������� GENERIC_READ
	);

	if(fileHandle != INVALID_HANDLE_VALUE)
	{
		LARGE_INTEGER sectorOffset;
		sectorOffset.QuadPart = 0; //����� ����������������� � ������

		// ������ �������
		DWORD currentPosition = SetFilePointer(
			fileHandle,
			sectorOffset.LowPart,// ������� ����� LARGE_INTEGER
			&sectorOffset.HighPart, // ������� �����
			FILE_BEGIN
		// ����� � �����, ������������ ������� ���������� �����������������
		// (FILE_BEGIN, FILE_CURRENT, FILE_END)
		);
		if(currentPosition == sectorOffset.LowPart)
		{
			DWORD bytesToRead = 512; // ������� ����� �������
			DWORD bytesRead; // ������� ������� �������

			// ������ ������
			bool readResult = ReadFile(
				  fileHandle, // ����������
				  dataBuffer, // ���� ������ ������
				  bytesToRead,
				  &bytesRead,
				  NULL //������ ���������� ������������
			);
			CloseHandle(fileHandle);

			if(readResult == false || bytesRead != bytesToRead) {
			} else {
				clusterSize = (DWORD)(pow((double)2, (int)pBootRecord->BytesPerSectorShift)*pow((double)2, (int)pBootRecord->SectorsPerClusterShift));
				clustersNumber = (DWORD)(pBootRecord->ClusterCount);
				sizeFS = clustersNumber*clusterSize;
			}
		} else {
			CloseHandle(fileHandle);
		}
	} else {
		CloseHandle(fileHandle);
	}
}

FileSystem_Type FindFileSystemType(wchar_t MediaType) {
	char dataBuffer[512];

	FAT32_BootRecord *pBootRecord = (FAT32_BootRecord*)dataBuffer;

	wchar_t diskName[64];
	swprintf(diskName,L"\\\\.\\%c:",MediaType);

    HANDLE fileHandle = CreateFile(
		diskName, // ��� �����/���������� (wchar*)
		GENERIC_READ, // ����� �������
		FILE_SHARE_READ | FILE_SHARE_WRITE, //����� ���������� ������
		NULL, // �������� ������������
		OPEN_EXISTING, //������ ��������
		FILE_ATTRIBUTE_NORMAL, //����� � ��������
		NULL
		//��������� (�������������) ����� ������� � ������� ������� GENERIC_READ
	);

	if(fileHandle != INVALID_HANDLE_VALUE)
	{
		LARGE_INTEGER sectorOffset;
		sectorOffset.QuadPart = 0; //����� ����������������� � ������

		// ������ �������
		DWORD currentPosition = SetFilePointer(
			fileHandle,
			sectorOffset.LowPart,// ������� ����� LARGE_INTEGER
			&sectorOffset.HighPart, // ������� �����
			FILE_BEGIN
		// ����� � �����, ������������ ������� ���������� �����������������
		// (FILE_BEGIN, FILE_CURRENT, FILE_END)
		);
		if(currentPosition == sectorOffset.LowPart)
		{
			DWORD bytesToRead = 512; // ������� ����� �������
			DWORD bytesRead; // ������� ������� �������

			// ������ ������
			bool readResult = ReadFile(
				  fileHandle, // ����������
				  dataBuffer, // ���� ������ ������
				  bytesToRead,
				  &bytesRead,
				  NULL //������ ���������� ������������
			);
			CloseHandle(fileHandle);

			if(readResult == false || bytesRead != bytesToRead)
			{
				return NULL;
			} else
			{

				if (strstr(pBootRecord->OEM_Name, "MSDOS5.0") != 0)
				{
					return FileSystem_Type::FAT32_Type;
				} else if (strstr(pBootRecord->OEM_Name, "EXFAT") != 0)
				{
					return FileSystem_Type::exFAT_Type;
				} else
				{
					return NULL;
				}
			}
		}
		else {
			CloseHandle(fileHandle);
			return NULL;
		}
	} else {
		CloseHandle(fileHandle);
		return NULL;

	}
}

FileSystemClass *CreateFileSystem(FileSystem_Type type, wchar_t MediaType) {
	switch (type)
	{
		case FileSystem_Type::exFAT_Type:
			return new exFAT_FileSystem(MediaType);
		case FileSystem_Type::FAT32_Type:
			return new FAT32_FileSystem(MediaType);
	}

	return NULL;
}

