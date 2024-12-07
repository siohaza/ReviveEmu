// Steam.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"

#include "windows.h"

#include "CriticalSection.h"

#include <iostream>
#include <conio.h>
#include <fstream>
#include <sys/stat.h>
#include <map>
#include <MMSystem.h>
#include <io.h>
#include <cstdio>
#include <process.h>
#include <shellapi.h>
#include <stdio.h>
#include <string.h>
#include <vector>
#include "registry.h"

#define NUL '\0'

unsigned int rootAppID = 0;
CLogFile* Logger;
char szSteamDLLPath[MAX_PATH];
BOOL bSteamDll = false;
char szOrigSteamDll[MAX_PATH];
BOOL bLogging = false;
BOOL bIsEnginePatched = false;
BOOL bLogAcc = false;
BOOL bLogFS = false;
BOOL bLogUserId = false;
BOOL bSteamClient = false;
DWORD g_dwClientId;
bool bAllowNonRev = true;

int nArgs;
bool bSteamFileSystem = false;
bool bSteamBlobSystem = false;
std::vector<int> vecGCF;
char appid[10];
char szGCFPath[MAX_PATH * 5];
char szRunFromPath[MAX_PATH];
static std::vector<char*> CacheLocations;

char szLanguage[MAX_PATH];
char szSteamUser[MAX_PATH];
char szOLDLanguage[MAX_PATH];
char szBlobFile[MAX_PATH];
char szAppIni[MAX_PATH];
char chProcName[MAX_PATH];
LPWSTR *szArglist;

char szCurrentDir[MAX_PATH];

CLogFile* LoggerFileFailure;
std::string szLoggerFile;
std::string szLoggerFilePath;
std::string szLoggerMode;
bool bLogFileFailure = false;
bool LoggerFileOpened;

HMODULE g_hModule;

CRITICAL_SECTION g_CriticalSection;
static CInitCriticalSection s_InitCriticalSection(&g_CriticalSection);

typedef struct
{
	void* pCache;
	char* FullName;
	//char FullName[MAX_PATH];
	unsigned int Index;
}TGlobalDirectory;

unsigned int GlobalDirectoryTableSize = 0;
unsigned int GlobalIndexCounter = 0;

#include "Steam.h"

#include "BlobSystem\CBlobSystem.h"		//Blob

static CContentDescriptionRecord* CDR;
static CBlobFileSystem* ClientRegistryBlob;
std::vector<TGlobalDirectory> GlobalDirectoryTable;
static std::map<unsigned int, TGlobalDirectory> HashTable;

#include "CacheSystem\CCacheSystem.h"	//Cache

static CCacheFileSystem* CacheManager;



#include "SteamFilesystem.h"			//Filesystem

#include "SteamApplication.h"			//App Functions
#include "SteamInterface.h"				//Interface
#include "SteamInit.h"					//Initialization
#include "SteamAsyncCallHandling.h"		//Asynchrounous call handling
#include "SteamLogging.h"				//Logging
#include "SteamAccount.h"				//Account
#include "SteamUserIDValidation.h"		//User ID validation
#include "SteamMiniDump.h"				//Minidump
#include "SteamMisc.h"					//Misc


bool IsInPath(char* chPath, const char* cchStr);

char *strrstr(char *x,char *y) 
{
	int m = strlen(x);
	int n = strlen(y);
	char *X = (char*)malloc(m+1);
	char *Y = (char*)malloc(n+1);
	int i;
	for (i=0; i<m; i++) X[m-1-i] = x[i]; X[m] = 0;
	for (i=0; i<n; i++) Y[n-1-i] = y[i]; Y[n] = 0;
	char *Z = strstr(X,Y);
	if (Z) 
	{
		int ro = Z-X;
		int lo = ro+n-1;
		int ol = m-1-lo;
		Z = x+ol;
	}
	free(X); free(Y);
	return Z;
}

char *_stristr(const char *String, const char *Pattern)
{
	char *pptr, *sptr, *start;

	for (start = (char *)String; *start != NUL; start++)
	{
		/* find start of pattern in string */
		for ( ; ((*start!=NUL) && (toupper(*start) != toupper(*Pattern))); start++)
			;
		if (NUL == *start)
			return NULL;

		pptr = (char *)Pattern;
		sptr = (char *)start;

		while (toupper(*sptr) == toupper(*pptr))
		{
			sptr++;
			pptr++;

			/* if end of pattern then pattern was found */

			if (NUL == *pptr)
				return (start);
		}
	}
	return NULL;
}


bool inArgs(LPWSTR arg) {
	for(int i=0; i<nArgs; i++) {
		if(_wcsicmp(szArglist[i],arg) == 0) {
			return true;
		}
	}
	return false;
}

void InitGlobalVaribles();

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call)
	{
		case DLL_PROCESS_ATTACH:
			strcpy(szOLDLanguage,"unset");
			getRegistryU("Software\\Valve\\Steam","Language",szOLDLanguage,MAX_PATH); 
			_strlwr(szOLDLanguage);
			g_hModule = hModule;
			InitGlobalVaribles();
			if (bLogging)Logger->Write("DllMain: DLL_PROCESS_ATTACH\n");
			break;

		case DLL_THREAD_ATTACH:
		
			if (bLogging)Logger->Write("DllMain: DLL_THREAD_ATTACH\n");
			break;
	
		case DLL_THREAD_DETACH:
		
			if (bLogging)Logger->Write("DllMain: DLL_THREAD_DETACH\n");
			break;
	
		case DLL_PROCESS_DETACH:
		
			if (bLogging)Logger->Write("DllMain: DLL_PROCESS_DETACH\n");
			setRegistry("Software\\Valve\\Steam","Language",szOLDLanguage); 
			g_hModule = NULL;
			break;
	
	}
	return TRUE;
}

void InitGlobalVaribles()
{
	char chWd[MAX_PATH];
	_getcwd(chWd, MAX_PATH);

	szArglist = CommandLineToArgvW(GetCommandLineW(), &nArgs);

	wcstombs(szRunFromPath, szArglist[0], MAX_PATH);
	V_StripFilename(szRunFromPath);

	if (strlen(szRunFromPath) < 1 || szRunFromPath != chWd)
	{
		_getcwd(szRunFromPath, MAX_PATH);
	}

	_strlwr(szRunFromPath);
	V_FixSlashes(szRunFromPath);

	char envBuffer[128];
	int envBufferLen = GetEnvironmentVariableA("SteamAppId", envBuffer, sizeof(envBuffer));
	if (envBufferLen && envBufferLen < sizeof(envBuffer))
	{
		strcpy(appid, envBuffer);
	}
	else if (inArgs(L"-appid") == true) 
	{
		for(int i=0; i<nArgs; i++)
		{
			if(_wcsicmp(szArglist[i],L"-appid") == 0)
			{
				wcstombs(appid, szArglist[i + 1], 255);
			}
		}
	}
	else *appid = 0;

		if (!*appid)
		{
			GetModuleFileNameA(NULL, chProcName, MAX_PATH);
			szArglist = CommandLineToArgvW(GetCommandLineW(), &nArgs);
			if(inArgs(L"-game") == true) 
			{
				for(int j=0; j<nArgs; j++) 
				{
					if(_wcsicmp(szArglist[j],L"-game") == 0) 
					{
						wcstombs(appid, szArglist[j + 1], 255);
					}
				}

				if (appid)
				{
					if (!_stricmp(appid, "cstrike"))
					{
						if(_stristr(chProcName, "hl.exe")) strcpy(appid, "10");
						if(_stristr(chProcName, "hl2.exe")) strcpy(appid, "240");
					}
					else if (!_stricmp(appid, "dod"))
					{
						if(_stristr(chProcName, "hl.exe")) strcpy(appid, "30");
						if(_stristr(chProcName, "hl2.exe")) strcpy(appid, "300");
					}
					else if (!_stricmp(appid, "garrysmod"))
					{
						if(_stristr(chProcName, "hl2.exe")) strcpy(appid, "4000");
					}
					else if (!_stricmp(appid, "hl2mp"))
					{
						if(_stristr(chProcName, "hl2.exe")) strcpy(appid, "320");
					}
					else if (!_stricmp(appid, "tf"))
					{
						if(_stristr(chProcName, "hl2.exe")) strcpy(appid, "440");
					}
					else if (!_stricmp(appid, "episodic"))
					{
						if(_stristr(chProcName, "hl2.exe")) strcpy(appid, "380");
					}
					else if (!_stricmp(appid, "ep2"))
					{
						if(_stristr(chProcName, "hl2.exe")) strcpy(appid, "420");
					}
					else if (!_stricmp(appid, "portal"))
					{
						if(_stristr(chProcName, "hl2.exe")) strcpy(appid, "400");
					}
					else if (!_stricmp(appid, "lostcoast"))
					{
						if(_stristr(chProcName, "hl2.exe")) strcpy(appid, "340");
					}
					else if (!_stricmp(appid, "launcher"))
					{
						if(_stristr(chProcName, "SourceSDK.exe")) strcpy(appid, "211");
					}
					else
						*appid = 0;
				}
			}
			else if(_stristr(chProcName, "hl.exe")) strcpy(appid, "70");
			else if(_stristr(chProcName, "hl2.exe")) strcpy(appid, "220");
		}

			char chLogFile[MAX_PATH];
			char chIniFile[MAX_PATH];
			char chClientPath[MAX_PATH];

			if(GetModuleFileNameA(g_hModule, szSteamDLLPath, MAX_PATH))
			{
				char* pchLastSlash = strrstr(szSteamDLLPath, "bin\\");
				if (pchLastSlash)
				{
					if (_stricmp(pchLastSlash,"bin\\steam.dll")==0)
					{
						*pchLastSlash = 0;
					}
					else
					{
						pchLastSlash = strrchr(szSteamDLLPath, '\\');
						pchLastSlash++;
						*pchLastSlash = 0;
					}
				}
				else
				{
					pchLastSlash = strrchr(szSteamDLLPath, '\\');
					pchLastSlash++;
					*pchLastSlash = 0;
				}
				strcpy(chIniFile, szSteamDLLPath);
				strcat(chIniFile, "rev.ini");
				strcpy(szAppIni, szSteamDLLPath);
				strcat(szAppIni, "revApps.ini");

						char chCmdLine[MAX_PATH];
						char temp[MAX_PATH];
						strcpy(chCmdLine, "");
						for (int i = 0; i<nArgs; i++)
						{
							wcstombs(temp, szArglist[i], 255);
							strcat(temp, " ");
							strcat(chCmdLine, temp);
						}


				//
				// Initialize and parse the INI file
				//
				CIniFile* Ini = new CIniFile(chIniFile);

				if(char* Logging = Ini->IniReadValue("Emulator", "Logging")) // Is logging enabled ?
				{
					if (_stricmp(Logging, "True") == 0) 
					{
						bLogging = true;
						GetModuleFileNameA(NULL, chProcName, MAX_PATH);
						strcpy(chProcName, strrchr(chProcName, '\\')+1);
						strcpy(chLogFile, szSteamDLLPath);
						strcat(chLogFile, chProcName);
						strcat(chLogFile, "_REVOLUTiON.log");
						Logger = new CLogFile(chLogFile);
						Logger->Clear();
						Logger->Write("Logging initialized.\n");
						Logger->Write("Run path initialized to %s\n",szRunFromPath);
						Logger->Write("Command line: %s\n", chCmdLine);

					} 
					delete[] Logging;
				}
				if (bLogging)
				{
					if(char* Logging = Ini->IniReadValue("Log", "FileSystem")) // Is FS logging enabled ?
					{
						if (_stricmp(Logging, "True") == 0) 
						{
							bLogFS = true;
							if (bLogging) Logger->Write("FileSystem logging initialized.\n");
						} 
						delete[] Logging;
					}
					if(char* Logging = Ini->IniReadValue("Log", "Account")) // Is Acc logging enabled ?
					{
						if (_stricmp(Logging, "True") == 0) 
						{
							bLogAcc = true;
							if (bLogging) Logger->Write("Account logging initialized.\n");
						} 
						delete[] Logging;
					}
					if(char* Logging = Ini->IniReadValue("Log", "UserID")) // Is UserID logging enabled ?
					{
						if (_stricmp(Logging, "True") == 0) 
						{
							bLogUserId = true;
							if (bLogging) Logger->Write("UserID logging initialized.\n");
						} 
						delete[] Logging;
					}


					if (bLogFileFailure)
					{
						char tmpFile[MAX_PATH];

						strcpy(tmpFile, szSteamDLLPath);
						strcat(tmpFile,"\\REVOLUTiON_File_Failure.Log");
						LoggerFileFailure = new CLogFile(tmpFile);
						LoggerFileFailure->Clear();

						if (bLogging) Logger->Write("Cache File Load Failure logging initialized.\n");

					}
				}

				/*
				if (bLogging)
				{
					Logger->Write("Processing passed arguments:\n");
					char * szTEMP = new char[MAX_PATH];
					for(int j=0; j<nArgs; j++) 
					{
						wcstombs(szTEMP, szArglist[j], MAX_PATH);
						Logger->Write("\tArg[%u]: %s\n",j, szTEMP);

					}
					delete [] szTEMP;

				}
				*/

				if(char* SteamUSR = Ini->IniReadValue("Emulator", "SteamUser"))
				{
					if (strlen(SteamUSR)>0)
					{
						strcpy(szSteamUser,SteamUSR);
					}
					else
					{
						strcpy(szSteamUser,"revCrew");
					}
					delete[] SteamUSR;
				}
				else
				{
					strcpy(szSteamUser,"revCrew");
				}

				SetEnvironmentVariableA("SteamUser", szSteamUser);
				if (bLogging) Logger->Write("Steam User set to %s\n",szSteamUser);

				if(char* CheckLang = Ini->IniReadValue("Emulator", "Language")) 
				{
					strcpy(szLanguage,CheckLang);
					if (strcmp(szOLDLanguage,"unset") == 0)
					{
						strcpy(szOLDLanguage,"English");
					}

					delete[] CheckLang;
				}
				else
				{
					if (strcmp(szOLDLanguage,"unset") == 0)
					{
						strcpy(szOLDLanguage,"English");
						strcpy(szLanguage,szOLDLanguage);
					}
					else
					{
						strcpy(szLanguage,szOLDLanguage);
					}
				}

				_strlwr(szLanguage);

				setRegistry("Software\\Valve\\Steam","Language",szLanguage); 

				if (bLogging) Logger->Write("Steam language initialized (%s)\n", szLanguage);

				if(char* GCFEnable = Ini->IniReadValue("Emulator", "CacheEnabled")) 
				{
					if (_stricmp(GCFEnable, "True") == 0) 
					{
						if (char* Path = Ini->IniReadValue("Emulator", "CachePath"))
						{
							strcpy(szGCFPath, Path);
							delete[] Path;
						}
						else
						{
							szGCFPath[0] = '\0';
						}

						// Alternate path to avoid HL2 anti-piracy.
						strcpy(szBlobFile, "platform\\ClientRegistry.blob");
						struct _stat filestat;
						if (_stat(szBlobFile, &filestat) == -1)
						{
							strcpy(szBlobFile, szSteamDLLPath);
							strcat(szBlobFile, "ClientRegistry.Blob");
						}

						if (_stat(szBlobFile, &filestat) == 0)
						{		
							if (bLogging) Logger->Write("Cache support initialized via %s\n",szBlobFile);
							bSteamFileSystem = true;
							bSteamBlobSystem = true;
						}
						else
						{
							bSteamBlobSystem = false;

							if (_stat(szAppIni, &filestat) == 0)
							{
								if (bLogging) Logger->Write("Cache support initialized via revApps.Ini\n");
								bSteamFileSystem = true;
							}
							else
							{
								bSteamFileSystem = false;
								if (bLogging) Logger->Write("Cache support was not initialized. No ClientRegistry.Blob and No RevSteamApps.ini were found!\n");
							}
						} 

						if (bSteamFileSystem == true)
						{
							char * pch;
							pch = strtok (szGCFPath,";");
							while (pch != NULL)
							{
								CacheLocations.push_back(pch); 
								pch = strtok (NULL, ";");

							}

							if (CacheLocations.size() > 0)
							{
								if (bLogging) Logger->Write("-- Multiple cache locations detected\n");
							}
							else
							{
								bSteamFileSystem = false;
								if (bLogging) Logger->Write("Cache support was not enabled as no valid GCF path was specified! Using extracted content only!\n");
							}
						}
					}
					else
					{
						bSteamFileSystem = false;
						if (bLogging) Logger->Write("Cache support was not enabled. Using extracted content only!\n");
					}
					delete[] GCFEnable;
				}


				if(char* SteamDll = Ini->IniReadValue("Emulator", "SteamDll"))
				{
					strcpy(szOrigSteamDll, SteamDll);
					bSteamDll = TRUE;
					delete[] SteamDll;
				}
				if(char* Misc = Ini->IniReadValue("Emulator", "ForceRevClient")) // Is other client emu allowed ?
				{
					if (_stricmp(Misc, "True") == 0) 
					{
						bAllowNonRev = false;
						if (bLogging) Logger->Write("Non-REVOLUTiON clients will not be allowed to join the server.\n");
					} 
					delete[] Misc;
				}
				if(bSteamDll == TRUE) // is Original Steam DLL set ?
				{
					char buffer[255];
					sprintf(buffer, "%x", (int)LoadLibraryA(szOrigSteamDll));
					if (!atoi(buffer)) 
					{
						char szErrMsg[255] = "Unable to load ";
						strcat(szErrMsg, szOrigSteamDll);
						strcat(szErrMsg, ". \nPlease edit or comment out SteamDll value in rev.ini");
						MessageBoxA(0, szErrMsg, "Error", 0);
						ExitProcess(1);
					}
					if (bLogging) Logger->Write("-- Original Steam.dll set: %s (0x%s)\n", szOrigSteamDll, buffer);
				}

		//
		// Set the registry values required for steamclient.dll to be loaded
		//
				if(char* SteamClient = Ini->IniReadValue("Emulator", "SteamClient")) // Should we enable steamclient loading ?
				{
					if (_stricmp(SteamClient, "True") == 0) 
					{
						bSteamClient = true;
						GetModuleFileNameA(NULL, chProcName, MAX_PATH);
						strcpy(chClientPath, szSteamDLLPath);
				
						if (_stristr(chProcName, "hlds.exe") || _stristr(chProcName, "hl.exe")) strcat(chClientPath, "steamclient.dll");
						else if (_stristr(chProcName, "srcds.exe") || _stristr(chProcName, "hl2.exe") || _stristr(chProcName, "sdklauncher.exe")) strcat(chClientPath, "bin\\steamclient.dll");
						else strcat(chClientPath, "steamclient.dll");
						
						if (bLogging) Logger->Write("-- Using Steam Client: %s\n", chClientPath);
						setRegistry("Software\\Valve\\Steam\\ActiveProcess","pid",GetCurrentProcessId()); 
						setRegistry("Software\\Valve\\Steam\\ActiveProcess","SteamClientDll",chClientPath);

						/*HMODULE hSteamApi = GetModuleHandleA("steam_api.dll");
						if (hSteamApi && _stristr(chCmdLine, "left4dead"))
						{
							FARPROC SteamAPI_Init = GetProcAddress(hSteamApi, "SteamAPI_Init");
							SteamAPI_Init();
							if (bLogging) Logger->Write("-- Using Steam Client: %s\n", chClientPath);
						}*/
					} 
					delete[] SteamClient;
				}

				delete Ini;

				//
				// Initialize the unique User ID used to authenticate with game server
				//
				GetVolumeInformationA(NULL, NULL, NULL, &g_dwClientId, NULL, NULL, NULL, NULL);
				return;

			}
			
			ExitProcess(0);

}

bool IsInPath(char* chPath, const char* cchStr)
{
	unsigned int i = 0, j = 0;
Start:
	while (i < strlen(chPath))
		{
			for (j = 0; j < strlen(cchStr); j++)
			{
				if (chPath[i+j] != cchStr[j])
				{
					i++;
					goto Start;
				}
			}
			return 1;
		}
		return 0;
}

