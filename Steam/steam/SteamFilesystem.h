#include "strtools.h"

extern unsigned int rootAppID;
extern CRITICAL_SECTION g_CriticalSection;
#define ENTER_CRITICAL_SECTION CEnterCriticalSection ECS(&g_CriticalSection)

const char * GetCacheNameFromAppID(unsigned int uAppID)
{
	for(unsigned int i = 0; i < CDR->ApplicationRecords.size(); i++)
	{
		if(uAppID == CDR->ApplicationRecords[i]->AppId)
		{
			return CDR->ApplicationRecords[i]->InstallDirName;
		}
	}
	return NULL;
}

unsigned int GetAppIDFromCacheName(const char * szGCF)
{
	for(unsigned int i = 0; i < CDR->ApplicationRecords.size(); i++)
	{
		if(_stricmp(szGCF,CDR->ApplicationRecords[i]->InstallDirName) == 0)
		{
			return CDR->ApplicationRecords[i]->AppId;
		}
	}
	return NULL;
}

unsigned int GetAppIDFromName(char * szName)
{
	for(unsigned int i = 0; i < CDR->ApplicationRecords.size(); i++)
	{
		if(_stricmp(szName,CDR->ApplicationRecords[i]->Name) == 0)
		{
			return CDR->ApplicationRecords[i]->AppId;
		}
	}
	return NULL;
}

unsigned int GetAppRecordID(unsigned int uAppID)
{
	for(unsigned int i = 0; i < CDR->ApplicationRecords.size(); i++)
	{
		if(uAppID == CDR->ApplicationRecords[i]->AppId)
		{
			return i;
		}
	}
	return NULL;
}

void MountFileSystemByID(unsigned int uId, const char* szExtraMount)
{
	char szPath[MAX_PATH];
	char szGCF[MAX_PATH];
	unsigned int cHandle;

	strcpy(szGCF, CDR->ApplicationRecords[uId]->InstallDirName);
	_strlwr(szGCF);

	for (unsigned int uIndex = 0; uIndex < CacheLocations.size(); uIndex++)
	{
		strcpy(szPath, CacheLocations[uIndex]);
		strcat(szPath, "\\");
		strcat(szPath, szGCF);
		strcat(szPath, ".gcf" );

		cHandle = CacheManager->MountCache(szPath, CacheManager->NumCaches(), szExtraMount);

		if(cHandle != NULL)
		{
			vecGCF.push_back(cHandle);
		}
	}
}

void MountFileSystemByName(const char * szPath )
{
	unsigned int cHandle;
	unsigned int index = vecGCF.size();
	cHandle = CacheManager->MountCache(szPath, index, "");
	if(cHandle != NULL)
	{
		vecGCF.push_back(cHandle);
	}
}



void MountExtraCaches(unsigned int uAppID)
{
	char szPath[MAX_PATH];
	strcpy(szPath, "");

	for (unsigned int uIndex = 0; uIndex < CacheLocations.size(); uIndex++)
	{
		if ((uAppID == 20) || (uAppID == 50) || (uAppID == 70) || (uAppID == 130))
		{
			strcat(szPath, CacheLocations[uIndex]);
			strcat(szPath, "\\");
			strcat(szPath,"half-life high definition.gcf");
		}

		if (strlen(szPath) > 0)
		{
			if (bLogging && bLogFS)	Logger->Write("Loading Optional Cache Requirements for AppID(%u)\n", uAppID);

			MountFileSystemByName(szPath);
		}

#if _M_X64
		// compile for 64-bit version only

		strcpy(szPath, "");

		if ((uAppID == 220) || (uAppID == 340))
		{
			strcat(szPath, CacheLocations[uIndex]);
			strcat(szPath, "\\");
			strcat(szPath,"source engine 64-bit.gcf");
		}

		if (strlen(szPath) > 0)
		{
			if (bLogging && bLogFS)	Logger->Write("Loading Optional 64-bit Requirements for AppID(%u)\n", uAppID);

			MountFileSystemByName(szPath);
		}
#endif
	}
}


void MountExtraLanguageCaches(const char * szName, const char * szLanguage, bool CheckingDependancy)
{
	char szPath[MAX_PATH];
	char szthisLanguage[MAX_PATH];
	strcpy(szthisLanguage,szLanguage);

	strcpy(szPath, szName);

	strcat(szPath," ");
	strcat(szPath,szthisLanguage);

	unsigned int uAppId = GetAppIDFromName(szPath);

	if (uAppId)
	{
		for (unsigned int uIndex = 0; uIndex < CacheLocations.size(); uIndex++)
		{
			if (strcmp(szthisLanguage,"russian") == 0 && strcmp(szName,"half-life 2") == 0)
			{
				if (bLogging && bLogFS)	Logger->Write("Loading Localized Cache Requirements for AppID(%u) Language(%s)\n", uAppId, "buka russian");

				strcpy(szPath, CacheLocations[uIndex]);
				strcat(szPath, "\\");
				strcat(szPath, "half-life 2 buka russian.gcf");
				MountFileSystemByName(szPath);
			}

			if (bLogging && bLogFS)	Logger->Write("Loading Localized Cache Requirements for AppID(%u) Language(%s)\n", uAppId, szthisLanguage);

			MountFileSystemByID(GetAppRecordID(uAppId), "");
		}
	}

	strcpy(szPath, szName);

	uAppId = GetAppIDFromName(szPath);

	if (uAppId)
	{
		// Check app dependancy and load as appropriate
		if (CheckingDependancy)
		{
			TSteamError steamError;
			unsigned int uPropertyValueLength;
			char szPropertyValue[MAX_PATH];

			SteamGetAppUserDefinedInfo(uAppId , "dependantOnApp", szPropertyValue, MAX_PATH, &uPropertyValueLength, &steamError);

			if (uPropertyValueLength > 0)
			{
				unsigned int uAppRecordDependant = GetAppRecordID(atoi(szPropertyValue));

				if (uAppRecordDependant)
				{
					MountExtraLanguageCaches(CDR->ApplicationRecords[uAppRecordDependant]->Name, szLanguage, true);
				}
			}
		}
	}
}

SteamHandle_t SteamOpenFile2(const char* cszFileName, const char* cszMode, int nFlags, unsigned int* puFileSize, int* pbLocal, TSteamError* pError)
{
	ENTER_CRITICAL_SECTION;

	if (bLogging && bLogFS) Logger->Write("SteamOpenFileEx (%s, %s, %u, 0x%p, 0x%p)\n", cszFileName, cszMode, nFlags, puFileSize, pbLocal);

	std::string FullPath(cszFileName);
	int dot = FullPath.find_last_of('\\');
	std::string FileName = FullPath.substr(dot + 1);
	std::string PathName = FullPath.substr(0, dot+ 1);

	if (strcmp(FileName.c_str(),szLoggerFile.c_str()) != 0)
	{
		if (LoggerFileOpened == false)
		{
			if (bLogging && bLogFileFailure) LoggerFileFailure->Write("[FAIL](%s) %s >> %s)\n", szLoggerMode.c_str(), szLoggerFile.c_str(), szLoggerFilePath.c_str());
		}
		else
		{
			LoggerFileOpened = false;
		}
		szLoggerFile = FileName;
		szLoggerFilePath = PathName;
		szLoggerMode = cszMode;
	}

	SteamClearError(pError);

	if (strpbrk(cszFileName, "?*"))
	{
		pError->eSteamError = eSteamErrorNotFound;
		if (bLogging && bLogFS) Logger->Write("\tFile not found (%s)\n", cszFileName);
		return STEAM_INVALID_HANDLE;
	}

	// FIXME: Is this necessary?
	char szFullPath[MAX_PATH];
	V_MakeAbsolutePath(szFullPath, MAX_PATH, cszFileName);

	TFileInCacheHandle* hCacheFile = NULL;
	FILE* pFile = fopen(szFullPath, cszMode);

	if (pFile)
	{
		hCacheFile = new TFileInCacheHandle();
		memset(hCacheFile, 0, sizeof(TFileInCacheHandle));
		hCacheFile->IsFileLocal = 1;
		hCacheFile->LocalFile = pFile;

		if (puFileSize)
		{
			fseek(pFile, 0, SEEK_END);
			*puFileSize = ftell(pFile);
			fseek(pFile, 0, SEEK_SET);
		}

		if (pbLocal)
			*pbLocal = 1;

		if (bLogging && bLogFS) Logger->Write("\tOpened 0x%08X from Local(%s) %s >> %s\n", (long)hCacheFile, cszMode, FileName.c_str(), PathName.c_str());
		LoggerFileOpened = true;
	}
	else
	{
		if (bSteamFileSystem == true)
			hCacheFile = CacheManager->CacheOpenFileEx(cszFileName, cszMode, puFileSize);

		if (!hCacheFile)
		{
			pError->eSteamError = eSteamErrorNotFound;
			if (bLogging && bLogFS) Logger->Write("\tFile not found (%s)\n", cszFileName);
		}
		else
		{
			if (pbLocal)
				*pbLocal = 0;

			if (bLogging && bLogFS) Logger->Write("\tOpened 0x%08X from Cache(%s) %s\n", (long)hCacheFile, cszMode, cszFileName);
		}
	}

	return (SteamHandle_t)hCacheFile;
}

STEAM_API int SteamMountFilesystem(unsigned int uAppId, const char *szMountPath, TSteamError *pError)
{
	if (bLogging) Logger->Write("SteamMountFilesystem (%u, %s)\n", uAppId, szMountPath);

	ENTER_CRITICAL_SECTION;

	if(CDR)
	{
		unsigned int uAppRecord = GetAppRecordID(uAppId);

		if (uAppRecord)
		{
			MountExtraLanguageCaches(CDR->ApplicationRecords[uAppRecord]->Name, szLanguage, true);
			MountExtraCaches(uAppId);

			if (CDR->ApplicationRecords[uAppRecord]->FilesystemsRecord.size() > 0)
			{
				// Language Caches have been processed as this is a root AppID

				for(unsigned int x = 0; x < CDR->ApplicationRecords[uAppRecord]->FilesystemsRecord.size(); x++)
				{
					CAppFilesystemRecord* pFSRecord = CDR->ApplicationRecords[uAppRecord]->FilesystemsRecord[x];

					// Don't mount depots from other operating systems.
#if defined(_WIN32)
					const char *cszHostOS = "windows";
#elif defined(__APPLE__)
					const char* cszHostOS = "macos";
#elif defined(__linux__)
					const char* cszHostOS = "linux";
#endif
					if (pFSRecord->OS && strcmp(pFSRecord->OS, cszHostOS) != 0)
						continue;

					if (bLogging && bLogFS) Logger->Write("Loading Default Cache Requirements for AppID(%u)\n", pFSRecord->AppId);

					MountFileSystemByID(GetAppRecordID(pFSRecord->AppId), pFSRecord->MountName);
				}
			}
			else
			{
				// Language Caches must be processed by calculating the rootAppID as some mods mount individual depots directly
				// rootAppID was recorded on the last enumerate app call as this would populate the enumerations for the root app

				int urootAppRecord = GetAppRecordID(rootAppID);

				if (urootAppRecord)
				{
					MountExtraLanguageCaches(CDR->ApplicationRecords[urootAppRecord]->Name, szLanguage, true);
					MountExtraCaches(rootAppID);
				}

				if (bLogging && bLogFS)
					Logger->Write("Loading Default Cache Requirements for AppID(%d)\n", uAppId);

				MountFileSystemByID(uAppRecord, "");
			}
		}

		SteamClearError(pError);
	}
	else
	{
		if (bLogging && bLogFS) Logger->Write("Error retrieving CDR from blob file!\n");
		pError->eSteamError = eSteamErrorUnknown;
		return 0;
	}

	return 1;
}

STEAM_API int SteamUnmountFilesystem(unsigned int uAppID, TSteamError* pError)
{
	if (bLogging) Logger->Write("SteamUnmountFilesystem (%u)\n", uAppID);
	SteamClearError(pError);

	return 1;
}

STEAM_API int SteamMountAppFilesystem(TSteamError *pError)
{
	if (bLogging) Logger->Write("SteamMountAppFilesystem\n");

	SteamClearError(pError);

	if (bSteamFileSystem == true)
	{
		if (!appid)
		{
			MessageBoxA(NULL, "You are trying to launch an unknown App ID, please specify -appid on the command line or write App ID into steam_appid.txt.", "RevEmu - AppID?", 0);
			ExitProcess(0xffffffff);
		}

		if (bSteamBlobSystem == true && CDR)
		{
			return SteamMountFilesystem(appid, "", pError);
		}
		else
		{
			CIniFile AppIni(szAppIni);
			char szSection[64];
			char szKey[64];
			char szPath[MAX_PATH];
			char *szGCF;
			int i;

			sprintf(szSection, "%d", appid);

			for(i = 1; i < 50; i++)
			{
				for (unsigned int uIndex = 0; uIndex < CacheLocations.size(); uIndex++)
				{
					sprintf(szKey, "GCF%d", i);
					szGCF = AppIni.IniReadValue(szSection, szKey);

					if(szGCF != NULL)
					{
						strcpy(szPath, CacheLocations[uIndex]);
						strcat(szPath, "\\");
						strcat(szPath, szGCF);

						MountFileSystemByName(szPath);
						delete[] szGCF;
					}
					else
					{
						break;
					}
				}
			}
		}

		return 1;
	}

	return 1;
}


STEAM_API int SteamUnmountAppFilesystem(TSteamError* pError)
{
	ENTER_CRITICAL_SECTION;

	if (bLogging) Logger->Write("SteamUnmountAppFilesystem\n");

	if (bSteamFileSystem == true)
	{
		for (size_t i = 0; i < vecGCF.size(); i++)
		{
			CacheManager->UnmountCache(vecGCF[i]);
		}

		vecGCF.clear();
		HashTable.clear();
		GlobalDirectoryTable.clear();
		GlobalDirectoryTableSize = 0;
		GlobalIndexCounter = 0;

		if (bLogging && bLogFS) Logger->Write("Cache Unmounted for AppID %d\n", appid);
	}

	SteamClearError(pError);
	return 1;
}


STEAM_API SteamHandle_t SteamOpenFileEx(const char* cszFileName, const char* cszMode, unsigned int* puFileSize, TSteamError* pError)
{
	return SteamOpenFile2(cszFileName, cszMode, 0, puFileSize, NULL, pError);
}

STEAM_API SteamHandle_t SteamOpenFile(const char* cszFileName, const char* cszMode, TSteamError* pError)
{
	return SteamOpenFile2(cszFileName, cszMode, 0, NULL, NULL, pError);
}

STEAM_API unsigned int SteamReadFile(void* pBuf, unsigned int uSize, unsigned int uCount, SteamHandle_t hFile, TSteamError* pError)
{
	ENTER_CRITICAL_SECTION;

	//if (bLogging && bLogFS) Logger->Write("SteamReadFile (0x%p, %u, %u, 0x%08X)\n", pBuf, uSize, uCount, (long)hFile);

	SteamClearError(pError);

	TFileInCacheHandle* hCacheFile = (TFileInCacheHandle*)hFile;
	unsigned int readamount = 0;

	if (hCacheFile->IsFileLocal)
	{
		readamount = fread(pBuf, uSize, uCount, hCacheFile->LocalFile);

		if (readamount != uCount && feof(hCacheFile->LocalFile))
		{
			pError->eSteamError = eSteamErrorEOF;
		}
	}
	else
	{
		readamount = CacheManager->CacheReadFile(pBuf, uSize, uCount, hCacheFile);

		if (readamount != uSize * uCount)
		{
			pError->eSteamError = eSteamErrorEOF;
		}

		if (uSize > 1)
		{
			readamount /= uSize;
		}
	}

	return readamount;
}

extern BOOL bSteamStartup;

STEAM_API int SteamCloseFile(SteamHandle_t hFile, TSteamError* pError)
{
	ENTER_CRITICAL_SECTION;

	if (bLogging && bLogFS) Logger->Write("SteamCloseFile (0x%08X)\n", (long)hFile);

	SteamClearError(pError);

	// HACK: This is a workaround for a bug in CS:S Beta srcds which randomly calls SteamCloseFile with
	// a garbage parameter if run without -steam. Real Steam fails out due to a check that throws
	// a C++ exception if the engine never called SteamStartup.
	// Ideally, we should do this for every function except for user validation but whatever.
	if (!bSteamStartup)
	{
		pError->eSteamError = eSteamErrorLibraryNotInitialized;
		return EOF;
	}

	TFileInCacheHandle* hCacheFile = (TFileInCacheHandle*)hFile;
	int retval = EOF;

	if (hCacheFile->IsFileLocal)
	{
		FILE* pFile = hCacheFile->LocalFile;
		retval = fclose(pFile);
		delete hCacheFile;
	}
	else
	{
		retval = CacheManager->CacheCloseFile(hCacheFile);
	}

	return retval;
}

STEAM_API SteamHandle_t SteamFindFirst(const char *cszPattern, ESteamFindFilter eFilter, TSteamElemInfo *pFindInfo, TSteamError *pError )
{
	ENTER_CRITICAL_SECTION;

	if (bLogging && bLogFS) Logger->Write("SteamFindFirst (%s, %u)\n", cszPattern, eFilter);

	SteamClearError(pError);

	switch (eFilter)
	{
	case eSteamFindRemoteOnly:
	case eSteamFindAll:
		{
			if (bSteamFileSystem)
			{
				TFindHandle* hFind = CacheManager->CacheFindFirst(cszPattern, eFilter, pFindInfo);
				if (hFind)
				{
					return (SteamHandle_t)hFind;
				}

				if (eFilter == eSteamFindRemoteOnly)
				{
					pError->eSteamError = eSteamErrorNotFound;
					if (bLogging && bLogFS) Logger->Write("\tFile pattern not found in cache (%s)\n", cszPattern);
					return STEAM_INVALID_HANDLE;
				}
			}

			// Fall through to local search if we find nothing in GCF or GCF support is disabled.
		}

	case eSteamFindLocalOnly:
		{
			_finddata_t finddata;
			intptr_t hLocalFind = _findfirst(cszPattern, &finddata);
			if (hLocalFind == -1)
			{
				pError->eSteamError = eSteamErrorNotFound;
				if (bLogging && bLogFS) Logger->Write("\tFile pattern not found (%s)\n", cszPattern);
				return STEAM_INVALID_HANDLE;
			}
			pFindInfo->bIsDir = ((finddata.attrib & _A_SUBDIR) != 0);
			pFindInfo->uSizeOrCount = finddata.size;
			pFindInfo->bIsLocal = 1;
			pFindInfo->lCreationTime = (long)finddata.time_create;
			pFindInfo->lLastAccessTime = (long)finddata.time_access;
			pFindInfo->lLastModificationTime = (long)finddata.time_write;
			strcpy(pFindInfo->cszName, finddata.name);
			SteamClearError(pError);

			TFindHandle* hFind = new TFindHandle();
			memset(hFind, 0, sizeof(TFindHandle));

			hFind->IsFindLocal = true;
			hFind->LocalFind = hLocalFind;
			hFind->eFilter = eFilter;
			strcpy(hFind->szPattern, cszPattern);
			if (bLogging && bLogFS) Logger->Write("\tFound Local file (%s) using pattern (%s)\n", finddata.name, cszPattern);

			return (SteamHandle_t)hFind;
		}
	default:
		{
			pError->eSteamError = eSteamErrorBadArg;
			if (bLogging && bLogFS) Logger->Write("\tFile not found (%s) <BAD ARGUMENT>\n", cszPattern);
			return STEAM_INVALID_HANDLE;
		}
	}
}

STEAM_API int SteamFindNext(SteamHandle_t hDirectory, TSteamElemInfo *pFindInfo, TSteamError *pError )
{
	ENTER_CRITICAL_SECTION;

	if (bLogging && bLogFS) Logger->Write("SteamFindNext\n");

	SteamClearError(pError);

	TFindHandle* hCacheFind = reinterpret_cast<TFindHandle*>(hDirectory);

	if (!strpbrk(hCacheFind->szPattern, "?*"))
	{
		return -1;
	}

	if (!hCacheFind->IsFindLocal && (hCacheFind->eFilter == eSteamFindAll || hCacheFind->eFilter == eSteamFindRemoteOnly))
	{
		int retval = CacheManager->CacheFindNext(hCacheFind, pFindInfo);

		if (retval == -1 && hCacheFind->eFilter == eSteamFindAll)
		{
			// switch to local search
			_finddata_t finddata;
			intptr_t hLocalFind = _findfirst(hCacheFind->szPattern, &finddata);

			if (hLocalFind != -1)
			{
				pFindInfo->bIsDir = ((finddata.attrib & _A_SUBDIR) != 0);
				pFindInfo->uSizeOrCount = finddata.size;
				pFindInfo->bIsLocal = 1;
				pFindInfo->lCreationTime = (long)finddata.time_create;
				pFindInfo->lLastAccessTime = (long)finddata.time_access;
				pFindInfo->lLastModificationTime = (long)finddata.time_write;
				strcpy(pFindInfo->cszName, finddata.name);

				hCacheFind->IsFindLocal = true;
				hCacheFind->LocalFind = hLocalFind;

				SteamClearError(pError);
				if (bLogging && bLogFS) Logger->Write("\tFound Local file (%s)\n", finddata.name);

				return 0;
			}

			return -1;
		}

		return retval;
	}

	if ((hCacheFind->IsFindLocal && (hCacheFind->eFilter == eSteamFindAll || hCacheFind->eFilter == eSteamFindLocalOnly)) || !bSteamFileSystem)
	{
		_finddata_t finddata;
		int retval = _findnext(hCacheFind->LocalFind, &finddata);

		if (retval != -1)
		{
			pFindInfo->bIsDir = ((finddata.attrib & _A_SUBDIR) != 0);
			pFindInfo->uSizeOrCount = finddata.size;
			pFindInfo->bIsLocal = 1;
			pFindInfo->lCreationTime = (long)finddata.time_create;
			pFindInfo->lLastAccessTime = (long)finddata.time_access;
			pFindInfo->lLastModificationTime = (long)finddata.time_write;
			strcpy(pFindInfo->cszName, finddata.name);
			SteamClearError(pError);
			if (bLogging && bLogFS) Logger->Write("\tFound Local file (%s)\n", finddata.name);
		}

		return retval;
	}

	return -1;
}

STEAM_API int SteamFindClose(SteamHandle_t hDirectory, TSteamError* pError)
{
	ENTER_CRITICAL_SECTION;

	if (bLogging && bLogFS) Logger->Write("SteamFindClose\n");

	SteamClearError(pError);

	TFindHandle* hCacheFind = (TFindHandle*)hDirectory;
	int retval = -1;

	if (hCacheFind->IsFindLocal)
	{
		retval = _findclose(hCacheFind->LocalFind);
		delete hCacheFind;
	}
	else
	{
		retval = CacheManager->CacheFindClose(hCacheFind);
	}

	return retval;
}

STEAM_API int SteamStat(const char* cszFileName, TSteamElemInfo* pInfo, TSteamError* pError)
{
	ENTER_CRITICAL_SECTION;

	if (bLogging && bLogFS) Logger->Write("SteamStat (%s, 0x%p)\n", cszFileName, pInfo);

	SteamClearError(pError);

	if (strpbrk(cszFileName, "?*"))
	{
		pError->eSteamError = eSteamErrorNotFound;
		if (bLogging && bLogFS) Logger->Write("\tFile not found (%s)\n", cszFileName);
		return -1;
	}

	struct _stat buf;
	int retval = _stat(cszFileName, &buf);
	if (retval == 0)
	{
		pInfo->bIsDir = ((buf.st_mode & S_IFMT) == S_IFDIR);

		pInfo->uSizeOrCount = buf.st_size;
		pInfo->bIsLocal = 1;
		strcpy(pInfo->cszName, cszFileName);
		pInfo->lCreationTime = (long)buf.st_ctime;
		pInfo->lLastAccessTime = (long)buf.st_atime;
		pInfo->lLastModificationTime = (long)buf.st_mtime;
	}
	else if (bSteamFileSystem == true)
	{
		retval = CacheManager->CacheStat(cszFileName, pInfo);
	}

	if (retval != 0)
	{
		pError->eSteamError = eSteamErrorNotFound;
		if (bLogging && bLogFS) Logger->Write("\tFile not found (%s)\n", cszFileName);
	}

	return retval;
}


STEAM_API int SteamFlushFile(SteamHandle_t hFile, TSteamError* pError)
{
	ENTER_CRITICAL_SECTION;

	if (bLogging && bLogFS) Logger->Write("SteamFlushFile (0x%08X)\n", (long)hFile);

	SteamClearError(pError);

	TFileInCacheHandle* hCacheFile = (TFileInCacheHandle*)hFile;
	int retval = EOF;

	if (hCacheFile->IsFileLocal)
	{
		retval = fflush(hCacheFile->LocalFile);
	}
	else
	{
		// Should never happen.
		if (bLogging && bLogFS) Logger->Write("\tTried to flush cache file (0x%08X)\n", (long)hFile);
		pError->eSteamError = eSteamErrorAccessDenied;
	}

	return retval;
}

STEAM_API int SteamGetc(SteamHandle_t hFile, TSteamError* pError)
{
	ENTER_CRITICAL_SECTION;

	if (bLogging && bLogFS) Logger->Write("SteamGetc (0x%08X)\n", (long)hFile);

	SteamClearError(pError);

	TFileInCacheHandle* hCacheFile = (TFileInCacheHandle*)hFile;
	int retval = EOF;

	if (hCacheFile->IsFileLocal)
	{
		retval = fgetc(hCacheFile->LocalFile);
	}
	else
	{
		unsigned char cChar;
		if (CacheManager->CacheReadFile(&cChar, 1, 1, hCacheFile) == 1)
		{
			retval = (int)cChar;
		}
		else
		{
			retval = EOF;
		}
	}

	return retval;
}

STEAM_API SteamHandle_t SteamOpenTmpFile(TSteamError* pError)
{
	ENTER_CRITICAL_SECTION;

	if (bLogging && bLogFS) Logger->Write("SteamOpenTmpFile\n");

	SteamClearError(pError);

	TFileInCacheHandle* hCacheFile = NULL;
	FILE* pFile = tmpfile();

	if (pFile)
	{
		hCacheFile = new TFileInCacheHandle();
		memset(hCacheFile, 0, sizeof(TFileInCacheHandle));
		hCacheFile->IsFileLocal = 1;
		hCacheFile->LocalFile = pFile;
	}

	return (SteamHandle_t)hCacheFile;
}

STEAM_API int SteamPutc(int cChar, SteamHandle_t hFile, TSteamError* pError)
{
	ENTER_CRITICAL_SECTION;

	if (bLogging && bLogFS) Logger->Write("SteamPutc (%u, 0x%08X)\n", cChar, (long)hFile);

	SteamClearError(pError);

	TFileInCacheHandle* hCacheFile = (TFileInCacheHandle*)hFile;
	int retval = EOF;

	if (hCacheFile->IsFileLocal)
	{
		retval = fputc(cChar, hCacheFile->LocalFile);
	}
	else
	{
		// Should never happen.
		if (bLogging && bLogFS) Logger->Write("\tTried to write to cache file!!! (0x%08X)\n", (long)hFile);
		pError->eSteamError = eSteamErrorAccessDenied;
	}

	return retval;
}

STEAM_API int SteamSeekFile(SteamHandle_t hFile, long lOffset, ESteamSeekMethod esMethod, TSteamError* pError)
{
	ENTER_CRITICAL_SECTION;

	if (bLogging && bLogFS) Logger->Write("SteamSeekFile (0x%08X, %u, %u)\n", (long)hFile, lOffset, esMethod);

	SteamClearError(pError);

	TFileInCacheHandle* hCacheFile = (TFileInCacheHandle*)hFile;
	int retval = -1;

	if (hCacheFile->IsFileLocal)
	{
		retval = fseek(hCacheFile->LocalFile, lOffset, esMethod);
		if (retval != 0)
		{
			if (bLogging && bLogFS) Logger->Write("\tLocal seek failed (0x%08X)\n", (long)hFile);
		}
	}
	else
	{
		retval = CacheManager->CacheSeekFile(hCacheFile, lOffset, esMethod);
		if (retval != 0)
		{
			if (bLogging && bLogFS) Logger->Write("\tCache seek failed (0x%08X)\n", (long)hFile);
		}
	}

	return retval;
}

STEAM_API unsigned int SteamWriteFile(const void* pBuf, unsigned int uSize, unsigned int uCount, SteamHandle_t hFile, TSteamError* pError)
{
	ENTER_CRITICAL_SECTION;

	if (bLogging && bLogFS) Logger->Write("SteamWriteFile (0x%p, %u, %u, 0x%08X)\n", pBuf, uSize, uCount, (long)hFile);

	SteamClearError(pError);

	TFileInCacheHandle* hCacheFile = (TFileInCacheHandle*)hFile;
	unsigned int writeamount = 0;

	if (hCacheFile->IsFileLocal)
	{
		writeamount = fwrite(pBuf, uSize, uCount, hCacheFile->LocalFile);
		if (writeamount < uCount)
		{
			if (bLogging && bLogFS) Logger->Write("\tWrite failed (0x%08X)\n", (long)hFile);
		}
	}
	else
	{
		// Should never happen.
		if (bLogging && bLogFS) Logger->Write("\tTried to write to cache file!!! (0x%08X)\n", (long)hFile);
		pError->eSteamError = eSteamErrorAccessDenied;
	}

	return writeamount;
}

STEAM_API long SteamTellFile(SteamHandle_t hFile, TSteamError* pError)
{
	ENTER_CRITICAL_SECTION;

	if (bLogging && bLogFS) Logger->Write("SteamTellFile (0x%08X)\n", (long)hFile);

	SteamClearError(pError);

	TFileInCacheHandle* hCacheFile = (TFileInCacheHandle*)hFile;
	int retval = -1;

	if (hCacheFile->IsFileLocal)
	{
		retval = ftell(hCacheFile->LocalFile);
		if (retval == -1)
		{
			if (bLogging && bLogFS) Logger->Write("\tLocal Tell failed (0x%08X)\n", (long)hFile);
		}
	}
	else
	{
		retval = CacheManager->CacheTellFile(hCacheFile);
		if (retval == -1)
		{
			if (bLogging && bLogFS) Logger->Write("\tCache Tell failed (0x%08X)\n", (long)hFile);
		}
	}

	return retval;
}

STEAM_API long SteamSizeFile(SteamHandle_t hFile, TSteamError* pError)
{
	ENTER_CRITICAL_SECTION;

	if (bLogging && bLogFS) Logger->Write("SteamSizeFile (0x%08X)\n", (long)hFile);

	SteamClearError(pError);

	TFileInCacheHandle* hCacheFile = (TFileInCacheHandle*)hFile;
	int retval = -1;

	if (hCacheFile->IsFileLocal)
	{
		FILE* f = hCacheFile->LocalFile;
		int pos = ftell(f);
		if (pos >= 0)
		{
			fseek(f, 0, SEEK_END);
			retval = ftell(f);
			fseek(f, pos, SEEK_SET);
		}
	}
	else
	{
		retval = CacheManager->CacheSizeFile((TFileInCacheHandle*)hFile);
	}

	return retval;
}

STEAM_API int SteamGetLocalFileCopy(const char* cszFileName, TSteamError* pError)
{
	ENTER_CRITICAL_SECTION;

	if (bLogging && bLogFS) Logger->Write("SteamGetLocalFileCopy (%s)\n", cszFileName);

	SteamClearError(pError);

	if (!V_IsAbsolutePath(cszFileName))
	{
		char pathbuffer[MAX_PATH];
		_searchenv(cszFileName, "PATH", pathbuffer);
		if (*pathbuffer)
		{
			if (bLogging && bLogFS) Logger->Write("\tFound ENV (%s)\n", cszFileName);
			return 1;
		}
	}
	else
	{
		struct _stat buf;
		int retval = _stat(cszFileName, &buf);
		if (retval == 0 && (buf.st_mode & _S_IFREG))
		{
			if (bLogging && bLogFS) Logger->Write("\tFound Local (%s)\n", cszFileName);
			return 1;
		}
	}

	//Changed to always try cache if others fail - for dedicated server to work
	if (bSteamFileSystem)
	{
		TFileInCacheHandle* hFile = CacheManager->CacheOpenFileEx(cszFileName, "rb", NULL);
		if (hFile)
		{
			int retval = CacheManager->CacheExtractFile(hFile, NULL);
			if (retval != 0)
			{
				if (bLogging && bLogFS) Logger->Write("\tFound Cache (%s)\n", cszFileName);
				delete hFile;
				return 1;
			}
			else
			{
				delete hFile;
			}
		}
	}

	pError->eSteamError = eSteamErrorNotFound;
	if (bLogging && bLogFS) Logger->Write("\tFile not found (%s)\n", cszFileName);
	return 0;
}

STEAM_API int SteamIsFileImmediatelyAvailable(const char* cszName, TSteamError* pError)
{
	ENTER_CRITICAL_SECTION;

	if (bLogging && bLogFS) Logger->Write("SteamIsFileImmediatelyAvailable (%s)\n", cszName);

	SteamClearError(pError);

	TSteamElemInfo info;
	int retval = SteamStat(cszName, &info, pError);
	if (retval == 0)
	{
		if (bLogging && bLogFS) Logger->Write("\tFile is Local (%s)\n", cszName);
		return 1;
	}

	if (bLogging && bLogFS) Logger->Write("\tFile not Local (%s)\n", cszName);
	return 0;
}

STEAM_API int SteamPrintFile(SteamHandle_t hFile, TSteamError* pError, const char* cszFormat, ...)
{
	ENTER_CRITICAL_SECTION;

	if (bLogging && bLogFS) Logger->Write("SteamPrintFile (0x%08X)\n", (long)hFile);

	SteamClearError(pError);

	TFileInCacheHandle* hCacheFile = (TFileInCacheHandle*)hFile;
	int writeamount = 0;

	if (hCacheFile->IsFileLocal)
	{
		va_list ap;
		va_start(ap, cszFormat);
		writeamount = vfprintf(hCacheFile->LocalFile, cszFormat, ap);
		va_end(ap);
	}
	else
	{
		// Should never happen.
		if (bLogging && bLogFS) Logger->Write("\tTried to write to cache file!!! (0x%08X)\n", (long)hFile);
		pError->eSteamError = eSteamErrorAccessDenied;
	}

	return writeamount;
}

STEAM_API int STEAM_CALL SteamSetvBuf(SteamHandle_t hFile, void* pBuf, ESteamBufferMethod eMethod, unsigned int uBytes, TSteamError* pError)
{
	ENTER_CRITICAL_SECTION;

	if (bLogging && bLogFS) Logger->Write("SteamSetvBuf (0x%08X, 0x%p, %u, %u)\n", (long)hFile, pBuf, eMethod, uBytes);

	SteamClearError(pError);

	TFileInCacheHandle* hCacheFile = (TFileInCacheHandle*)hFile;
	int retval = -1;

	if (hCacheFile->IsFileLocal)
	{
		FILE* pFile = hCacheFile->LocalFile;
		int mode = 0;

		if (eMethod == eSteamBufferMethodFBF)
			mode = _IOFBF;
		else if (eMethod == eSteamBufferMethodNBF)
			mode = _IONBF;
		else
			return -1;

		retval = setvbuf(pFile, (char*)pBuf, mode, uBytes);
	}
	else
	{
		if (bLogging && bLogFS) Logger->Write("\tSteamSetvBuf not implemented for cache files (0x%08X)\n", (long)hFile);
		pError->eSteamError = eSteamErrorUnknown;
	}

	return retval;
}

STEAM_API int STEAM_CALL SteamHintResourceNeed(const char* cszHintList, int bForgetEverything, TSteamError* pError)
{
	if (bLogging && bLogFS) Logger->Write("SteamHintResourceNeed (%s, %d)\n", cszHintList, bForgetEverything);
	SteamClearError(pError);
	return 1;
}

STEAM_API int STEAM_CALL SteamForgetAllHints(TSteamError* pError)
{
	if (bLogging && bLogFS) Logger->Write("SteamForgetAllHints\n");
	SteamClearError(pError);
	return 1;
}

STEAM_API int STEAM_CALL SteamPauseCachePreloading(TSteamError* pError)
{
	if (bLogging && bLogFS) Logger->Write("SteamPauseCachePreloading\n");
	SteamClearError(pError);
	return 1;
}

STEAM_API int STEAM_CALL SteamResumeCachePreloading(TSteamError* pError)
{
	if (bLogging && bLogFS) Logger->Write("SteamResumeCachePreloading\n");
	SteamClearError(pError);
	return 1;
}

STEAM_API int STEAM_CALL SteamGetCacheFilePath(unsigned int uAppId, char* szFilePath, unsigned int uBufferLength, unsigned int* puRecievedLength, TSteamError* pError)
{
	if (bLogging && bLogFS) Logger->Write("SteamGetCacheFilePath\n");
	SteamClearError(pError);
	return 1;
}
