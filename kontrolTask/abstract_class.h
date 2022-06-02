//---------------------------------------------------------------------------

#ifndef abstract_classH
#define abstract_classH
#include "Unit1.h"
#include <cmath>
#include <vcl.h>
//---------------------------------------------------------------------------
class FileSystemClass {
	protected:
		FileSystemClass (wchar_t MediaType);
		FileSystemClass (wchar_t *diskName);

	public:
		HANDLE fileHandle;
		UINT64 sizeFS;
		DWORD clustersNumber;
		DWORD clusterSize;
		wchar_t *diskName;

		virtual DWORD readCluster(char *dataBuffer, DWORD i);
};

class DecoratorFS : public FileSystemClass {
	public:
		class FileSystemClass *fileSystem;
		DecoratorFS(FileSystemClass *fileSystem);

		DWORD readCluster(char *dataBuffer, DWORD i);
};
//FAT32
#pragma pack(push, 1)
typedef struct
{
	char Padding1[3];
	char OEM_Name[8];
	unsigned short SectorSize;
	unsigned char ClusterSize;
	// ���������� ��������� (���-�� �������� � ��������)
	unsigned short ReservedAreaSize;
	unsigned char NumberCopiesFat;
	unsigned short MaxNumberRecRootCat;
	// ����. ���-�� 32-����. ������� � �������� ��������
	unsigned short ShestSectorsCount;
	//16-����. ���-�� �������� � ��
	char MediaType;
	// ��� ��������
	unsigned short FatSize16;
	unsigned short NumberSectTrack;
	// ���-�� �������� � �������
	unsigned short NumberHeads;
	// ���-�� �������
	unsigned int NumbSectBfStartSection;
	// ���-�� �������� ����� ������� �������
	unsigned int Numb32SectFat;
	// 32-��������� ���-�� �������� ��
	unsigned int FatSize32;
	unsigned int ClusterRootCatOffset;
	// �������,  ������� ��������� �������� �������
	unsigned short SectReservCopyBootSector;
	// ������, � ������� ��������� ����� ����.�������


} FAT32_BootRecord;
#pragma pack (pop)

class FAT32_FileSystem : public FileSystemClass {
	public:
		FAT32_FileSystem(wchar_t MediaType);
};

//EXFAT
#pragma pack(push, 1)
// https://docs.microsoft.com/ru-ru/windows/win32/fileio/exfat-specification
typedef struct {
	char JumpBoot[3];

	char FileSystemName[8];
	char MustBeZero[53];
	unsigned long long PartitionOffset;
	unsigned long long VolumeLength;
	unsigned int FatOffset;
	unsigned int FatLength;
	unsigned int ClusterHeapOffset;
	unsigned int ClusterCount;
	unsigned int FirstClusterOfRootDirectory;
	unsigned int VolumeSerialNumber;
	unsigned short FileSystemRevision;
	unsigned short VolumeFlags;
	unsigned char BytesPerSectorShift;
	unsigned char SectorsPerClusterShift;

} exFAT_BootRecord;
#pragma pack(pop)

class exFAT_FileSystem : public FileSystemClass {
	public:
		exFAT_FileSystem(wchar_t MediaType);
};


// Fabric method
enum FileSystem_Type {
	FAT32_Type = 1,
	exFAT_Type = 2
};

FileSystem_Type FindFileSystemType(wchar_t MediaType);

FileSystemClass *CreateFileSystem(FileSystem_Type type, wchar_t MediaType);

#endif
