// dllmain.cpp : Defines the entry point for the DLL application.
#include ".\Common\commonincludes.h"
#include ".\Common\support.h"

//
// Variables
//

char chClientDLLPath[MAX_PATH];
char g_chName[50];
char g_chLang[20];
char pchServerBrowser[MAX_PATH];
char g_chMasterServer[MAX_PATH] = "hl2master.steampowered.com";
bool g_bLogging = false;
DWORD g_dwClientId;
CIniFile* Ini;
CLogFile* Logger;

//
// Prototypes
//

void Init(HMODULE hModule);

//
// Main
//

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
#ifdef _DEBUG 
	MessageBoxA(0, "Attach now!", "DBG", 0);
#endif
		Init(hModule);
		break;
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}

void Init(HMODULE hModule)
{
	char chLogFile[MAX_PATH];
	char chIniFile[MAX_PATH];

	if(GetModuleFileNameA(hModule, chClientDLLPath, MAX_PATH))
	{
		char* pchLastSlash = strrstr(chClientDLLPath, "bin\\");
		if (pchLastSlash)
		{
			*pchLastSlash = 0;
		}
		else
		{
			pchLastSlash = strrchr(chClientDLLPath, '\\');
			pchLastSlash++;
			*pchLastSlash = 0;
		}
		strcpy(chIniFile, chClientDLLPath);
		strcat(chIniFile, "rev.ini");

//
// Initialize the serverbrowser.vdf file
//
		strcpy(pchServerBrowser, chClientDLLPath);
		strcat(pchServerBrowser, "\\platform\\config\\serverbrowser.vdf");

//
// Initialize and parse the INI file
//
		Ini = new CIniFile(chIniFile);
		if(char* Logging = Ini->IniReadValue("steamclient", "Logging")) // Is logging enabled ?
		{
			if (strcmp(Logging, "True") == 0) 
			{
				g_bLogging = true;
				strcpy(chLogFile, chClientDLLPath);
				strcat(chLogFile, "rev-client.log");
				Logger = new CLogFile(chLogFile);
				Logger->Clear();
				Logger->Write("Logging initialized.\n");
			} 
			delete Logging;
		}
		if(char* PlayerName = Ini->IniReadValue("steamclient", "PlayerName")) // Player name used in TF2 and newer games
		{
			strcpy(g_chName, PlayerName);
			delete PlayerName;
		}
		else
		{
			strcpy(g_chName, "REVOLUTiON");
		}
		if(char* MasterServer = Ini->IniReadValue("steamclient", "MasterServer")) // Master Server to query, used in TF2 and newer games
		{
			strcpy(g_chMasterServer, MasterServer);
			delete MasterServer;
		}
		if (g_bLogging)
		{
			Logger->Write("Using player name: %s\n", g_chName);
		}

//
// Initialize the unique User ID used to authenticate with game server
//
		GetVolumeInformationA(NULL, NULL, NULL, &g_dwClientId, NULL, NULL, NULL, NULL);
		return;
	}
	ExitProcess(-1);
}