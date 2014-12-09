#ifndef PIE_FILES
#define PIE_FILES
#include"main.h"
//FILE TYPES
/*typedef enum _FILE_TYPE
{
    FILE_INI	= 0x0,
	FILE_BIN	= 0x1,
	FILE_DAT	= 0x2
}FILE_TYPE;*/
typedef enum _READ_WRITE
{
    FILE_READ	= 0x0,
	FILE_WRITE	= 0x1,
}READ_WRITE;
void FilesAssign(char *CDir);
class CPFile
{
public:
	CPFile();
	bool		Open(LPCSTR FName,READ_WRITE rw);
	bool		Read(LPVOID data,DWORD size);
	bool		ReadNullTerminatedString(char *str);
	bool		WriteNullTerminatedString(char *str);
	bool		Write(LPVOID data,DWORD size);
	bool		Close();
	DWORD		SetOffset(LONG offset,WORD pos);
	DWORD		GetNBytes(){return rb;}
	DWORD		GetOffset();
	DWORD		Size(){if (size) return size;	return GetFileSize(file,NULL);}
	bool		Reopen();
private:
	HANDLE		file;
	READ_WRITE	type;
	DWORD		offset;
	DWORD		rb;
	DWORD		size;
	bool		opened;
	char		fname[MAX_PATH];
};
typedef CPFile* PFile;


#endif PIE_FILES