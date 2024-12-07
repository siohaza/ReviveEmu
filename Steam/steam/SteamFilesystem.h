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

int SteamOpenFile2(const char* cszFileName, const char* cszMode, int iArg3, unsigned int* puSize, int* piArg5, TSteamError *pError)
{
	ENTER_CRITICAL_SECTION;

	if (bLogging && bLogFS) Logger->Write("SteamOpenFileEx(%s, %s, %u, %u, %u)\n", cszFileName, cszMode, iArg3, puSize, piArg5);

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

	char filename[MAX_PATH];
	strcpy(filename, cszFileName);


	FILE* pFile = NULL;
	SteamClearError(pError);

	if(strpbrk(filename, "?*"))
	{
		pError->eSteamError = eSteamErrorNotFound;
		if (bLogging && bLogFS) Logger->Write("\tFile not found (%s)\n", cszFileName);
		return (SteamHandle_t)pFile;
	}

	char szFullPath[MAX_PATH];
	strcpy(szFullPath, "");
	std::string tmp = filename;
	strcpy(filename, tmp.c_str());

	if(filename[0] == '.' && filename[1] == '\\')
	{
		strcpy(filename, &filename[2]);
	}

	if(filename[1] != ':' && filename[2] != '\\')
	{
		GetCurrentDirectoryA(MAX_PATH, szFullPath);
		strcat(szFullPath, "\\");
	}

	strcat(szFullPath, filename);
	pFile = fopen(szFullPath, cszMode);

	if(pFile && puSize != NULL)
	{
		fseek(pFile,0,SEEK_END);
		*puSize = ftell(pFile);
		fseek(pFile,0,SEEK_SET);
	}

	TFileInCacheHandle* hFile = NULL;

	if(pFile == NULL)
	{
		if (bSteamFileSystem == true)
			hFile = CacheManager->CacheOpenFileEx(cszFileName, cszMode, puSize);

		if (!hFile)
		{
			pError->eSteamError = eSteamErrorNotFound;
			if (bLogging && bLogFS) Logger->Write("\tFile not found (%s)\n", cszFileName);
		}
		else
		{
			if (bLogging && bLogFS) Logger->Write("\tOpened 0x%08X from Cache(%s) %s\n", (long)hFile, cszMode, cszFileName);
		}
	}
	else
	{
		hFile = new TFileInCacheHandle();
		memset(hFile, 0, sizeof(TFileInCacheHandle));
		hFile->IsFileLocal = 1;
		hFile->LocalFile = pFile;

		if (bLogging && bLogFS) Logger->Write("\tOpened 0x%08X from Local(%s) %s >> %s\n", (long)hFile, cszMode, FileName.c_str(), PathName.c_str() );
		LoggerFileOpened = true;
	}

	return (SteamHandle_t)hFile;
}

STEAM_API int SteamMountFilesystem(unsigned int uAppId, const char *szMountPath, TSteamError *pError) {
	if (bLogging) Logger->Write("SteamMountFilesystem (%u, %s)\n", uAppId, szMountPath);

	ENTER_CRITICAL_SECTION;

	if (!*appid)
		_itoa(uAppId, appid, 10);

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
					if (bLogging && bLogFS)
						Logger->Write("Loading Default Cache Requirements for AppID(%u)\n", CDR->ApplicationRecords[uAppRecord]->FilesystemsRecord[x]->AppId);

					MountFileSystemByID(GetAppRecordID(CDR->ApplicationRecords[uAppRecord]->FilesystemsRecord[x]->AppId),CDR->ApplicationRecords[uAppRecord]->FilesystemsRecord[x]->MountName);

				}
			}
			else
			{
				// Language Caches must be processed by calculating the rootAppID as some mods call this function directly
				// rootAppID was recorded on the last enumerate app call as this would populate the enumerations for the root app

				int urootAppRecord = GetAppRecordID(rootAppID);

				if (urootAppRecord)
				{
					MountExtraLanguageCaches(CDR->ApplicationRecords[urootAppRecord]->Name, szLanguage, true);
					MountExtraCaches(rootAppID);
				}

				if (bLogging && bLogFS)
					Logger->Write("Loading Default Cache Requirements for AppID(%s)\n", appid);

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

STEAM_API int SteamUnmountFilesystem(unsigned int uAppID, TSteamError *pError ) {
	if (bLogging) Logger->Write("SteamUnmountFilesystem (%u)\n", uAppID);
	SteamClearError(pError);

	return 1;
}

STEAM_API int SteamMountAppFilesystem(TSteamError *pError) {
	if (bLogging) Logger->Write("SteamMountAppFilesystem\n");

	SteamClearError(pError);

	if (bSteamFileSystem == true)
	{
		if (!*appid)
		{
			MessageBoxA(NULL, "You are trying to launch an unknown App ID, please specify -appid on the command line.", "AppID?", 0);
			ExitProcess(0xffffffff);
		}

		if (bSteamBlobSystem == true && ClientRegistryBlob && CDR)
		{
			return SteamMountFilesystem(atoi(appid), "", pError);
		}
		else
		{
			CIniFile AppIni(szAppIni);
			char szKey[MAX_PATH];
			char buffer[MAX_PATH];
			char szPath[MAX_PATH];
			char *szGCF;
			int i;

			for(i = 1; i < 50; i++)
			{
				for (unsigned int uIndex = 0; uIndex < CacheLocations.size(); uIndex++)
				{
					strcpy(szPath, CacheLocations[uIndex]);

					strcpy(szKey,"GCF");
					_itoa(i, buffer, 10);
					strcat(szKey, buffer);

					szGCF = AppIni.IniReadValue(appid, szKey);

					if(szGCF != NULL)
					{
						strcat(szPath, "\\");
						strcat(szPath, szGCF);

						MountFileSystemByName(szPath);
						delete[] szGCF;
					}
					else
					{
						break;
					}

					memset(szKey,0,255);
				}
			}
		}
	}

	return 1;
}


STEAM_API int SteamUnmountAppFilesystem(TSteamError* pError) {

	ENTER_CRITICAL_SECTION;

	if (bLogging) Logger->Write("SteamUnmountAppFilesystem\n");

	if(bSteamFileSystem == true)
	{
		for(unsigned int i = 0; i < vecGCF.size(); i++)
		{
			if(CacheManager->UnmountCache(vecGCF[i]) == true)
			{
			}
		}

		if (bLogging && bLogFS) Logger->Write("Cache Unmounted for AppID %s\n", appid);
	}

	SteamClearError(pError);
	return 1;
}


STEAM_API SteamCallHandle_t SteamOpenFileEx(const char *cszFileName, const char *cszMode, unsigned int *puSize, TSteamError *pError) {

	return SteamOpenFile2(cszFileName, cszMode, NULL, puSize, NULL, pError);

}

STEAM_API SteamCallHandle_t SteamOpenFile(const char *cszFileName, const char *cszMode, TSteamError *pError) {

	return SteamOpenFile2(cszFileName, cszMode, NULL, NULL, NULL, pError);

}

STEAM_API unsigned int SteamReadFile(void *pBuf, unsigned int uSize, unsigned int uCount, SteamHandle_t hFile, TSteamError *pError ) {

	ENTER_CRITICAL_SECTION;

	SteamClearError(pError);
	int readedbytes;

	 if(((TFileInCacheHandle*)hFile)->IsFileLocal)
	 {
		  readedbytes = fread(pBuf, uSize, uCount, ((TFileInCacheHandle*)hFile)->LocalFile);

	 } else {
		  readedbytes = CacheManager->CacheReadFile(pBuf,uSize,uCount, (TFileInCacheHandle*)hFile);
	 }

	 if(readedbytes != uSize * uCount) {
		pError->eSteamError = eSteamErrorEOF;
		return readedbytes;
	 }
	 //return readedbytes;
	 return readedbytes;

}

STEAM_API int SteamCloseFile(SteamHandle_t hFile, TSteamError *pError) {

	ENTER_CRITICAL_SECTION;

	if (bLogging && bLogFS) Logger->Write("SteamCloseFile(0x%08X)\n", (long)hFile);

	SteamClearError(pError);

	DWORD dwRet = 0;
	if(((TFileInCacheHandle*)hFile)->IsFileLocal)
	{
		FILE *pFile = ((TFileInCacheHandle*)hFile)->LocalFile;
		dwRet = fclose(pFile);
	}
	else
	{
		dwRet = CacheManager->CacheCloseFile((TFileInCacheHandle*)hFile);
	}

	return dwRet;
}

STEAM_API SteamCallHandle_t SteamFindFirst(const char *cszPattern, ESteamFindFilter eFilter, TSteamElemInfo *pFindInfo, TSteamError *pError ) {

	ENTER_CRITICAL_SECTION;

	if (bLogging && bLogFS) Logger->Write("SteamFindFirst(%s)\n", cszPattern);

	char filename[MAX_PATH];
	strcpy(filename, cszPattern);

	SteamClearError(pError);
	int hRetVal = 0;

	switch(eFilter)
	{
	case eSteamFindRemoteOnly:
	case eSteamFindAll:
		{
			if (bSteamFileSystem)
				hRetVal = (SteamHandle_t)CacheManager->CacheFindFirst((char*)filename, eFilter, pFindInfo);

			if (hRetVal)
				return hRetVal;

			if (eFilter == eSteamFindRemoteOnly)
			{
				pError->eSteamError = eSteamErrorNotFound;
			}
		}

	case eSteamFindLocalOnly:
		{
			_finddata_t finddata;
			hRetVal = _findfirst(filename, &finddata);
			if (hRetVal < 0)
			{
				pError->eSteamError = eSteamErrorNotFound;
				if (bLogging && bLogFS) Logger->Write("\tFile not found (%s)\n", filename);
				return 0;
			}
			pFindInfo->bIsDir = ((finddata.attrib & _A_SUBDIR) != 0);
			pFindInfo->uSizeOrCount = finddata.size;
			pFindInfo->bIsLocal = TRUE;
			pFindInfo->lCreationTime = (long)finddata.time_create;
			pFindInfo->lLastAccessTime = (long)finddata.time_access;
			pFindInfo->lLastModificationTime = (long)finddata.time_write;
			strcpy(pFindInfo->cszName, finddata.name);
			SteamClearError(pError);

			TFindHandle* hFind = new TFindHandle();
			memset(hFind, 0, sizeof(TFindHandle));

			hFind->IsFindLocal = 1;
			hFind->LocalFind = hRetVal;
			hFind->eFilter = eFilter;
			hFind->szSearchString = new char[strlen(filename)+1];
			strcpy(hFind->szSearchString,filename);
			hFind->cszPattern = new char[strlen(cszPattern)+1];
			strcpy((char*)hFind->cszPattern, cszPattern);
			if (bLogging && bLogFS) Logger->Write("\tFound Local file (%s) using pattern (%s)\n", finddata.name, filename);

			return (SteamHandle_t)hFind;
		}
	default:
		{
			pError->eSteamError = eSteamErrorBadArg;
			if (bLogging && bLogFS) Logger->Write("\tFile not found (%s) <BAD ARGUMENT>\n", filename);
			return hRetVal;
		}
	}
}

STEAM_API int SteamFindNext(SteamHandle_t hDirectory, TSteamElemInfo *pFindInfo, TSteamError *pError ) {

	ENTER_CRITICAL_SECTION;

	if (bLogging && bLogFS) Logger->Write("SteamFindNext\n");

	SteamClearError(pError);

	int hRetVal = -1;

	//bItemFound = false;

	TFindHandle* pFind = reinterpret_cast<TFindHandle*>(hDirectory);

	if (!strpbrk(pFind->cszPattern, "?*"))
	{
		return -1;
	}

	if (!pFind->IsFindLocal && (pFind->eFilter == eSteamFindAll || pFind->eFilter == eSteamFindRemoteOnly))
	{
		hRetVal = CacheManager->CacheFindNext(((TFindHandle*)hDirectory), pFindInfo);

		if(hRetVal == -1 && pFind->eFilter == eSteamFindAll)
		{
			//switch to local search
			_finddata_t finddata;
			hRetVal = _findfirst(pFind->cszPattern, &finddata);

			if(hRetVal != (int)INVALID_HANDLE_VALUE)
			{
				pFindInfo->bIsDir = ((finddata.attrib & _A_SUBDIR) != 0);
				pFindInfo->uSizeOrCount = finddata.size;
				pFindInfo->bIsLocal = TRUE;
				pFindInfo->lCreationTime = (long)finddata.time_create;
				pFindInfo->lLastAccessTime = (long)finddata.time_access;
				pFindInfo->lLastModificationTime = (long)finddata.time_write;
				strcpy(pFindInfo->cszName, finddata.name);

				pFind->IsFindLocal = true;
				pFind->LocalFind = hRetVal;

				SteamClearError(pError);
				if (bLogging && bLogFS) Logger->Write("\tFound Local file (%s)\n", finddata.name);

				return 0;
			}
		}
	}

	if ((pFind->IsFindLocal && (pFind->eFilter == eSteamFindAll || pFind->eFilter == eSteamFindLocalOnly)) || !bSteamFileSystem)
	{
		_finddata_t finddata;
		hRetVal = _findnext(pFind->LocalFind, &finddata);

		if (hRetVal != -1)
		{
			pFindInfo->bIsDir = ((finddata.attrib & _A_SUBDIR) != 0);
			pFindInfo->uSizeOrCount = finddata.size;
			pFindInfo->bIsLocal = TRUE;
			pFindInfo->lCreationTime = (long)finddata.time_create;
			pFindInfo->lLastAccessTime = (long)finddata.time_access;
			pFindInfo->lLastModificationTime = (long)finddata.time_write;
			strcpy(pFindInfo->cszName, finddata.name);
			SteamClearError(pError);
			if (bLogging && bLogFS) Logger->Write("\tFound Local file (%s)\n", finddata.name);
		}
	}

	return hRetVal;
}

STEAM_API int SteamFindClose(SteamHandle_t hDirectory, TSteamError *pError ) {

	ENTER_CRITICAL_SECTION;

	if (bLogging && bLogFS) Logger->Write("SteamFindClose\n");

	SteamClearError(pError);

	int retval = 0;

	if(((TFindHandle*)hDirectory)->IsFindLocal)
	{
		retval = _findclose(((TFindHandle*)hDirectory)->LocalFind);
	}
	else
	{
		retval = CacheManager->CacheFindClose(((TFindHandle*)hDirectory));
	}

	if (retval == -1)
		pError->eSteamError = eSteamErrorNotFound;

	return retval;
}

STEAM_API int SteamStat(const char* cszFileName, TSteamElemInfo *pInfo, TSteamError *pError) {

	ENTER_CRITICAL_SECTION;

	if (bLogging && bLogFS) Logger->Write("SteamStat(%s, 0x%p, 0x%p)\n", cszFileName, pInfo, pError);

	char filename[MAX_PATH];
	strcpy(filename, cszFileName);


	SteamClearError(pError);

	struct _stat buf;
	int dwRet = -1;

	if(strpbrk(filename, "?*")) {
		pError->eSteamError = eSteamErrorNotFound;
		if (bLogging && bLogFS) Logger->Write("\tFile not found (%s)\n", filename);
		return dwRet;
	}

	dwRet = _stat(filename, &buf);
	if(!dwRet)
	{
		pInfo->bIsDir = ((buf.st_mode & S_IFMT) == S_IFDIR);

		pInfo->uSizeOrCount = buf.st_size;
		pInfo->bIsLocal = 1;
		strcpy(pInfo->cszName, filename);
		pInfo->lCreationTime = (long)buf.st_ctime;
		pInfo->lLastAccessTime = (long)buf.st_atime;
		pInfo->lLastModificationTime = (long)buf.st_mtime;

	}
	else if (bSteamFileSystem == true)
	{
		dwRet = CacheManager->CacheStat(filename, pInfo);
		if (dwRet != 0)
		{
			pError->eSteamError = eSteamErrorNotFound;
			if (bLogging && bLogFS) Logger->Write("\tFile not found (%s)\n", filename);
		}
	}
	return dwRet;
}


STEAM_API int SteamFlushFile(SteamHandle_t hFile, TSteamError *pError ) {
	if (bLogging && bLogFS) Logger->Write("SteamFlushFile(0x%08X)\n", (long)hFile);
	SteamClearError(pError);

	int hRetVal = -1;

	if (!((TFileInCacheHandle*)hFile)->IsFileLocal)
	{

		if (bLogging && bLogFS) Logger->Write("\tFlush Cache File not yet written\n");

		/*if (CacheManager->CacheReadFile(&cChar, 1, 1, (TFileInCacheHandle*)hFile) == 1)
		{
			return (int)cChar;
		}
		return hRetVal;*/
	}
	else
	{
		hRetVal =  fflush(((TFileInCacheHandle*)hFile)->LocalFile);
	}


	return hRetVal;
}

STEAM_API int SteamGetc(SteamHandle_t hFile, TSteamError *pError ) {

	ENTER_CRITICAL_SECTION;

	if (bLogging && bLogFS) Logger->Write("SteamGetc(0x%08X)\n", (long)hFile);

	SteamClearError(pError);

	int hRetVal = -1;

	unsigned char cChar;

	if (!((TFileInCacheHandle*)hFile)->IsFileLocal)
	{
		if (CacheManager->CacheReadFile(&cChar, 1, 1, (TFileInCacheHandle*)hFile) == 1)
		{
			return (int)cChar;
		}
		return hRetVal;
	}
	else
	{
		return fgetc(((TFileInCacheHandle*)hFile)->LocalFile);
	}
}

STEAM_API SteamCallHandle_t SteamOpenTmpFile(TSteamError *pError ) {
	if (bLogging && bLogFS) Logger->Write("SteamOpenTmpFile\n");
	SteamClearError(pError);

	return 0;
}

STEAM_API int SteamPutc(int cChar, SteamHandle_t hFile, TSteamError *pError ) {

	if (bLogging && bLogFS) Logger->Write("SteamPutc(%u, 0x%08X)\n", cChar, (long)hFile);
	SteamClearError(pError);

	return -1;
}

STEAM_API int SteamSeekFile(SteamHandle_t hFile, long lOffset, ESteamSeekMethod esMethod, TSteamError *pError ) {

	ENTER_CRITICAL_SECTION;

	if (bLogging && bLogFS) Logger->Write("SteamSeekFile(0x%08X, %u, %u)\n", (long)hFile, lOffset, esMethod);

	int retval = -1;
	SteamClearError(pError);
	if(((TFileInCacheHandle*)hFile)->IsFileLocal)
	{

		retval = fseek(((TFileInCacheHandle*)hFile)->LocalFile, lOffset, esMethod);
		if (retval != 0)
		{
			pError->eSteamError = eSteamErrorSeek;
			if (bLogging && bLogFS) Logger->Write("\tLocal seek failed (0x%08X)\n", (long)hFile);
		}
	}
	else
	{
		retval = CacheManager->CacheSeekFile(((TFileInCacheHandle*)hFile),lOffset,esMethod);
		if (retval != 0)
		{
			pError->eSteamError = eSteamErrorSeek;
			if (bLogging && bLogFS) Logger->Write("\tCache seek failed (0x%08X)\n", (long)hFile);
		}
	}
	return retval;
}

STEAM_API unsigned int SteamWriteFile(const void *pBuf, unsigned int uSize, unsigned int uCount, SteamHandle_t hFile, TSteamError *pError)
{
	ENTER_CRITICAL_SECTION;


	if (bLogging && bLogFS) Logger->Write("SteamWriteFile(0x%08X, %u, %u, 0x%08X)\n", pBuf, uSize, uCount, (long)hFile);

	SteamClearError(pError);
	unsigned int res = 0;
		res = fwrite(pBuf, uSize, uCount, ((TFileInCacheHandle*)hFile)->LocalFile);
		if (res < uCount) {
			if (bLogging && bLogFS) Logger->Write("\tWrite failed (0x%08X)\n", (long)hFile);
			pError->eSteamError = eSteamErrorUnknown;
			return 0;
		}
	return res;
}

STEAM_API long SteamTellFile(SteamHandle_t hFile, TSteamError *pError) {

	ENTER_CRITICAL_SECTION;


	long retval = -1;
	SteamClearError(pError);

	if(((TFileInCacheHandle*)hFile)->IsFileLocal)
	{
		retval = ftell(((TFileInCacheHandle*)hFile)->LocalFile);
		if (retval == -1)
		{
			pError->eSteamError = eSteamErrorUnknown;
			if (bLogging && bLogFS) Logger->Write("\tLocal Tell failed (0x%08X)\n", (long)hFile);
		}
		else
		{
			if (bLogging && bLogFS) Logger->Write("SteamTellFile(0x%08X) %u\n",(long)hFile, retval);
		}
	}
	else
	{
		retval = CacheManager->CacheTellFile(((TFileInCacheHandle*)hFile));
		if (retval == -1)
		{
			pError->eSteamError = eSteamErrorUnknown;
			if (bLogging && bLogFS) Logger->Write("\tCache Tell failed (0x%08X)\n", (long)hFile);
		}
		else
		{
			if (bLogging && bLogFS) Logger->Write("SteamTellFile(0x%08X) %u\n",(long)hFile, retval);
		}
	}

	return retval;
}

STEAM_API long SteamSizeFile(SteamHandle_t hFile, TSteamError *pError ) {

	ENTER_CRITICAL_SECTION;

	if (bLogging && bLogFS) Logger->Write("SteamSizeFile(0x%08X)\n", (long)hFile);

	SteamClearError(pError);

	if(((TFileInCacheHandle*)hFile)->IsFileLocal)
	{
		FILE *f = ((TFileInCacheHandle*)hFile)->LocalFile;
		if(f)
		{
			int pos = ftell(f);
			fseek(f, 0, SEEK_END);
			int size = ftell(f);
			fseek(f, pos, SEEK_SET);
			return size;
		} else {
			pError->eSteamError = eSteamErrorNotFound;
			if (bLogging && bLogFS) Logger->Write("\tHandle not valid (0x%08X)\n", (long)hFile);
			return -1;
		}
	}
	else
	{
		return CacheManager->CacheSizeFile((TFileInCacheHandle*)hFile);
	}
}

STEAM_API int SteamGetLocalFileCopy(const char* cszFileName, TSteamError* pError) {

	ENTER_CRITICAL_SECTION;

	if (bLogging && bLogFS) Logger->Write("SteamGetLocalFileCopy(%s)\n", cszFileName);

	char filename[MAX_PATH];
	strcpy(filename, cszFileName);


	SteamClearError(pError);

	if(filename[1] != ':')
	{
		char pathbuffer[MAX_PATH];
		_searchenv(filename, "PATH", pathbuffer);
		if(pathbuffer[0] != 0)
		{
			if (bLogging && bLogFS) Logger->Write("\tFound ENV (%s)\n", filename);
			return 1;
		}
	} else if(FILE* file = fopen(filename, "r")) {
		fclose(file);
		if (bLogging && bLogFS) Logger->Write("\tFound Local (%s)\n", filename);
		return 1;
	}

	//Changed to always try cache if others fail - for dedicated server to work
	if (bSteamFileSystem)
	{
		TFileInCacheHandle* hFile = CacheManager->CacheOpenFileEx(filename, "rb", NULL);
		if (hFile)
		{
			int retval = CacheManager->CacheExtractFile(hFile, NULL);
			if (retval != 0)
			{
				if (bLogging && bLogFS) Logger->Write("\tFound Cache (%s)\n", filename);
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
	if (bLogging && bLogFS) Logger->Write("\tFile not found (%s)\n", filename);
	return 0;
}


STEAM_API int SteamIsFileImmediatelyAvailable(const char *cszName, TSteamError *pError ) {

	ENTER_CRITICAL_SECTION;

	if (bLogging && bLogFS) Logger->Write("SteamIsFileImmediatelyAvailable(%s)\n", cszName);

	char filename[MAX_PATH];
	strcpy(filename, cszName);


	struct stat buf;
	int i = stat ( filename, &buf );
	if ( i == 0 )
	{
		SteamClearError(pError);
		if (bLogging && bLogFS) Logger->Write("\tFile is Local (%s)\n", filename);
		return 1;
	}
	if (bLogging && bLogFS) Logger->Write("\tFile not Local (%s)\n", filename);
	return 0;
}



STEAM_API int SteamPrintFile(SteamHandle_t hFile, TSteamError *pError, const char *cszFormat, ... ) {

	ENTER_CRITICAL_SECTION;

	if (bLogging && bLogFS) Logger->Write("SteamPrintFile(0x%08X)\n", (long)hFile);

	FILE *f = (FILE*)hFile;
	va_list ap;
	va_start(ap, cszFormat);
	vfprintf(f,cszFormat,ap);
	va_end(ap);
	SteamClearError(pError);

	return 1;
}

STEAM_API int STEAM_CALL SteamSetvBuf(SteamHandle_t hFile, void* pBuf, ESteamBufferMethod eMethod, unsigned int uBytes, TSteamError *pError)
{
	if (bLogging && bLogFS) Logger->Write("SteamSetvBuf\n");
	SteamClearError(pError);
	return 0;
}

STEAM_API int STEAM_CALL SteamHintResourceNeed(const char *cszHintList, int bForgetEverything, TSteamError *pError)
{
	if (bLogging && bLogFS) Logger->Write("SteamHintResourceNeed: %s, %d\n", cszHintList, bForgetEverything);
	SteamClearError(pError);
	return TRUE;
}

STEAM_API int STEAM_CALL SteamForgetAllHints(TSteamError *pError)
{
	if (bLogging && bLogFS) Logger->Write("SteamForgetAllHints\n");
	SteamClearError(pError);
	return TRUE;
}

STEAM_API int STEAM_CALL SteamPauseCachePreloading(TSteamError *pError)
{
	if (bLogging && bLogFS) Logger->Write("SteamPauseCachePreloading\n");
	SteamClearError(pError);
	return 1;
}

STEAM_API int STEAM_CALL SteamResumeCachePreloading(TSteamError *pError)
{
	if (bLogging && bLogFS) Logger->Write("SteamResumeCachePreloading\n");
	SteamClearError(pError);
	return 1;
}

STEAM_API int STEAM_CALL SteamGetCacheFilePath(unsigned int uAppId,  char* szFilePath, unsigned int uBufferLength, unsigned int* puRecievedLength, TSteamError *pError)
{
	if (bLogging && bLogFS) Logger->Write("SteamGetCacheFilePath\n");
	SteamClearError(pError);
	return 1;
}
