#ifndef PIE_ERROR
#define PIE_ERROR
#include"stdafx.h"

void	ClearErrorQueue();
void	WriteErrors(char *fname);
void	PutError(const char *szFormat, ...);
int		GetErrorCount();
bool	bError();
void	WriteMsg(const char *szFormat, ...);
void	AddTab();
void	RemTab();
void	_Start();
void	WriteTime(FILE *_f);
void	WriteDate(FILE *_f);
void	WriteRunningTime(FILE *_f);
void	DisableMessages();
void	EnableMessages();



#endif	PIE_ERROR