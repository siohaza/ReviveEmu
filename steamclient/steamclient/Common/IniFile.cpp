#pragma warning(disable:4996)//disable deprecated warnings

#include "commonincludes.h"

CIniFile::CIniFile(char* szIniFilePath)
{
	if(szIniFilePath)
	{
		strcpy(this->szIniFilePath, szIniFilePath);
	}
}
CIniFile::~CIniFile(){}

bool CIniFile::IniWriteValue(char* Section, char* Key, char* Value)
{
	return (WritePrivateProfileStringA(Section, Key, Value, this->szIniFilePath) == TRUE ? true : false);
}

char* CIniFile::IniReadValue(char* Section, char* Key)
{
	char* retval = new char[256];
	if(GetPrivateProfileStringA(Section, Key, "", retval, 256, this->szIniFilePath))
	{
		return retval;
	}
	delete retval;
	return NULL;
}
