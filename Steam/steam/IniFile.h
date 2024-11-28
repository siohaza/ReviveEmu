#pragma once

#include <windows.h>

class CIniFile
{
private:
	char szIniFilePath[255];
public:
	CIniFile(char* szIniFilePath);
	~CIniFile();

	bool IniWriteValue(char* Section, char* Key, char* Value);
	char* IniReadValue(char* Section, char* Key);
};
