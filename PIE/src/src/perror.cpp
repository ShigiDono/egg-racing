#include"stdafx.h"
#include"perror.h"
char	ERROR_QUEUE[1024][256];
int		ECount=1024;
char	eszAppPath[MAX_PATH];
DWORD	Tab=0,STime=0;
char _szFormat[2048];
char _szFormat1[2048];
char	fs[100];
bool	_em=1;
void	DisableMessages(){
	_em=false;
}
void	EnableMessages()
{
	_em=true;
}

void _Start()
{
	STime=timeGetTime();
}
void	WriteTime(FILE *_f)
{
	SYSTEMTIME tt;
	GetSystemTime(&tt);
	char time[100];
	ZeroMemory(time,sizeof(time));
	ZeroMemory(fs,sizeof(fs));
/*	strcpy(fs,"HH':'mm':'ss");
	int l=0;
	l=GetTimeFormat(LOCALE_SYSTEM_DEFAULT,DATE_LONGDATE	,&tt,fs,time,0);
	GetTimeFormat(LOCALE_SYSTEM_DEFAULT,DATE_LONGDATE	,&tt,fs,time,l);
	fprintf(f,time);*/
	if (_f==NULL){
		FILE *f = NULL;
		//	strcpy(_szFormat,szFormat);
		f = fopen(eszAppPath, "a");
		fprintf(f,"%d : %d : %d ",tt.wHour,tt.wMinute,tt.wSecond);
		fclose(f);
	}
	else{
		fprintf(_f,"%d : %d : %d ",tt.wHour,tt.wMinute,tt.wSecond);
	}
}
void	WriteDate(FILE *_f)
{
	SYSTEMTIME tt;
	GetSystemTime(&tt);
	char time[100];
	ZeroMemory(time,sizeof(time));
	ZeroMemory(fs,sizeof(fs));
	strcpy(fs,"dddd',' MMMM dd yyyy");
	int l=0;
	l=GetDateFormatA(LOCALE_SYSTEM_DEFAULT,0,&tt,fs,time,0);
	GetDateFormatA(LOCALE_SYSTEM_DEFAULT,0,&tt,fs,time,l);
	if (_f==NULL){
		FILE *f = NULL;
		//	strcpy(_szFormat,szFormat);
		f = fopen(eszAppPath, "a");
		fprintf(f,"%s ",time);
		fclose(f);
	}
	else{
		fprintf(_f,"%s ",time);
	}
}
void	WriteRunningTime(FILE *_f)
{
	if (_f==NULL){
		FILE *f = NULL;
		//	strcpy(_szFormat,szFormat);
		f = fopen(eszAppPath, "a");
		float t=(float)(timeGetTime()-STime)/1000;
		fprintf(f,"%f sec. ",t);
		fclose(f);
	}
	else{
		float t=(float)(timeGetTime()-STime)/1000;
		fprintf(_f,"%f sec. ",t);
	}
}

void	AddTab()
{
	Tab++;
}
void	RemTab()
{
	if (Tab==0)
		PutError("Syntax error! Missed tab!");
	Tab--;
}
void	ClearErrorQueue()
{
	ZeroMemory(eszAppPath,MAX_PATH);
	GetCurrentDirectoryA(1024,eszAppPath);
	eszAppPath[strlen(eszAppPath)]='\\';
	strcat(eszAppPath,"system.log");
	ZeroMemory(ERROR_QUEUE,ECount*256);
	ECount=0;
}
void	WriteErrors(char *fname)
{
	FILE *hf = NULL;
	hf = fopen(fname, "a");
	for (int i=0;i<ECount;i++){
		fprintf(hf, "%s\n",ERROR_QUEUE[i]);
	}

	fclose(hf);
}
/*void	PutError(char *Error)
{
	strcpy(ERROR_QUEUE[ECount++],Error);
}*/
void PutError(const char *szFormat, ...)
{
	va_list ap;

	va_start(ap, szFormat);
	vsprintf(ERROR_QUEUE[ECount++],szFormat, ap);
//	vprintf(hf, szFormat, ap);
	va_end(ap);
}
void WriteMsg(const char *szFormat, ...)
{
	if (!_em) return;
	va_list ap;
	FILE *hf = NULL;
//	strcpy(_szFormat,szFormat);
	hf = fopen(eszAppPath, "a");
	for (int i=0;i<Tab;i++)
		fprintf(hf,"	");
	if (szFormat[0]=='-')
		WriteRunningTime(hf);
	va_start(ap, szFormat);
//	vsprintf(ERROR_QUEUE[ECount++],szFormat, ap);
	vfprintf(hf, szFormat, ap);
	va_end(ap);
	fprintf(hf,"\n");
	fclose(hf);
}
int		GetErrorCount()
{
	return ECount;
}
bool	bError()
{
	return ECount!=0;
}