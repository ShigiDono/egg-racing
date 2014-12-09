#include"stdafx.h"
#include"pie.h"
#include<atlpath.h>
void CPie::Ini_SetInt(const char *section, const char *name, int value)
{
	char buf[256];
//	ZeroMemory(buf,sizeof(buf));
//	strcpy(buf,);
	if(szIniFile[0]) {
		sprintf(buf,"%d",value);
		bool b=WritePrivateProfileStringA(section, name, buf,szIniFile);
		b=1;
	}
}


int CPie::Ini_GetInt(const char *section, const char *name, int def_val)
{
	char buf[256];

	if(FileExists(szIniFile)) {
		if(GetPrivateProfileStringA(section, name, "", buf, sizeof(buf), szIniFile))
		{ return atoi(buf); }
		else { return def_val; }
	}
	return def_val;
}


void CPie::Ini_SetFloat(const char *section, const char *name, float value)
{
	char buf[256];

	if(szIniFile[0]) {
		sprintf(buf,"%f",value);
		WritePrivateProfileStringA(section, name, buf, szIniFile);
	}
}


float CPie::Ini_GetFloat(const char *section, const char *name, float def_val)
{
	char buf[256];

	if(FileExists(szIniFile)) {
		if(GetPrivateProfileStringA(section, name, "", buf, sizeof(buf), szIniFile))
		{ return (float)atof(buf); }
		else { return def_val; }
	}
	return def_val;
}


void CPie::Ini_SetString(const char *section, const char *name, const char *value)
{
	if(szIniFile[0]) WritePrivateProfileStringA(section, name, value, szIniFile);
}


char* CPie::Ini_GetString(const char *section, const char *name, const char *def_val)
{
	if(szIniFile[0]) GetPrivateProfileStringA(section, name, def_val, szIniString, sizeof(szIniString), szIniFile);
	else strcpy(szIniString, def_val);
	return szIniString;
}
