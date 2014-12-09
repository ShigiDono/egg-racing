#include"stdafx.h"
#include"files.h"
char fAppPath[MAX_PATH];
void FilesAssign(char *CDir)
{
	ZeroMemory(fAppPath,MAX_PATH);
	strcpy(fAppPath,CDir);
}
CPFile::CPFile()
{
	ZeroMemory(this,sizeof(CPFile));
	type=FILE_READ;
}
bool CPFile::Open(LPCSTR FName,READ_WRITE rw)
{
	char temp[MAX_PATH];
	ZeroMemory(temp,MAX_PATH);
	strcpy(temp,fAppPath);
	strcat(temp,FName);
	file=PIEOpenFile(temp,(rw==FILE_READ));
	offset=0;
	type=rw;
	opened=1;
	strcpy(fname,FName);
	if (rw==FILE_READ)
		size=GetFileSize(file,NULL);
	else
		size=0;
	return (file!=NULL);
}
bool CPFile::Close()
{
	opened=0;
	offset=0;
	return CloseHandle(file);	
}
bool CPFile::Reopen()
{
	if (opened)
		if (!Close()) return 0;
	return Open(fname,type);
}
bool CPFile::Read(LPVOID data,DWORD size)
{
	if (PIEReadFile(file,data,size,&rb,NULL))
	{
		offset+=rb;
		return rb!=0;
	}
	if (rb)
		offset+=rb;
	return 1;
}
bool CPFile::Write(LPVOID data,DWORD size)
{
	if (PIEWriteFile(file,data,size,&rb,NULL))
	{
		offset+=rb;
		return rb!=0;
	}
	if (rb)
		offset+=rb;
	return 1;
}
DWORD CPFile::SetOffset(LONG _offset,WORD pos)
{
	if (pos==FILE_BEGIN)
	{
		if (_offset<0)
			_offset=0;
		if (_offset>(LONG)Size())
			_offset=Size();
		offset=_offset;
	}
	if (pos==FILE_CURRENT)
	{
		if (offset+_offset<0)
			_offset=offset;
		if (offset+_offset>Size())
			_offset=Size()-offset;
		offset+=_offset;
	}
	if (pos==FILE_END)
	{
		if (_offset>0)
			_offset=0;
		if (_offset<-(LONG)Size())
			_offset=-(LONG)Size();
		offset=Size()+_offset;
	}
	return PIESetOffset(file,_offset,pos);
}
DWORD CPFile::GetOffset()
{
	return offset;
}
bool CPFile::ReadNullTerminatedString(char *str)
{
	char b=1;
	int i=0;
	while (b!=0){
		if (!Read(&b,1))
			return 0;
		if (b!=0){
			str[i]=b;
			i++;
		}
	}
	return 1;
}
bool CPFile::WriteNullTerminatedString(char *str)
{
	for (int i=0;i<strlen(str);i++)
	{
		if (!Write(&str[i],1))
			return 0;
	}
	char b=0;
	return Write(&b,1);
}
