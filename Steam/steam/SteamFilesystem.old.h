#pragma once

#include "SteamCommon.h"
#include <sys/stat.h>
#include <io.h>
#include <iostream>

extern CLogFile* Logger;
extern BOOL bLogging;
extern BOOL bSteamDll;
extern BOOL bLogFS;
extern BOOL bSteamFileSystem;
extern char szOrigSteamDll[MAX_PATH];

typedef int (STEAM_CALL *SteamStatCall)(const char*, TSteamElemInfo*, TSteamError*); 
typedef SteamHandle_t (STEAM_CALL *SteamOpenFileExCall)(const char*, const char*, unsigned int*, TSteamError*);
typedef SteamHandle_t (STEAM_CALL *SteamFindFirstCall)(const char*, ESteamFindFilter, TSteamElemInfo*, TSteamError*);
typedef SteamHandle_t (STEAM_CALL *SteamReadFileCall)(void*, unsigned int, unsigned int, SteamHandle_t, TSteamError*);

int SteamOpenFile2(const char* cszFileName, const char* cszMode, int iArg3, unsigned int* size, int* piArg5, TSteamError *pError)
{
	if (bLogging && bLogFS) Logger->Write("SteamOpenFile2(%s, %s, %u, %u, %u)\n", cszFileName, cszMode, iArg3, size, piArg5);
	if(cszFileName && cszMode)
	{
		FILE* pFile = fopen(cszFileName, cszMode);
		if((int)pFile != 0)
		{
			if (size)
			{
				fseek(pFile, 0, SEEK_END);
				*size = ftell(pFile);						// Return the size of file

				fseek(pFile, 0, SEEK_SET);					// Seek to the beginning
			}

			SteamClearError(pError);
			return (SteamHandle_t) pFile;				// return the adress of pointer to opened FILE
		}
		if (bLogging && bLogFS)Logger->Write("Failed to open file: %s\n", cszFileName);
		pError->eSteamError = eSteamErrorNotFound;
		pError->eDetailedErrorType = eNoDetailedErrorAvailable;
	}
    return 0;
}

int SteamOpenFile2(const char *cszFileName, const char *cszMode, unsigned int* size, TSteamError *pError)
{
	if (bLogging && bLogFS) Logger->Write("SteamOpenFile2(%s, %s, %u)\n", cszFileName, cszMode, size);
	if(cszFileName && cszMode)
	{
		FILE* pFile = fopen(cszFileName, cszMode);
		if((int)pFile != 0)
		{
			if (size)
			{
				fseek(pFile, 0, SEEK_END);
				*size = ftell(pFile);						// Return the size of file

				fseek(pFile, 0, SEEK_SET);					// Seek to the beginning
			}

			SteamClearError(pError);
			return (SteamHandle_t) pFile;				// return the adress of pointer to opened FILE
		}
		
		if (bLogging && bLogFS)Logger->Write("Failed to open file: %s\n", cszFileName);
		pError->eSteamError = eSteamErrorNotFound;
		pError->eDetailedErrorType = eNoDetailedErrorAvailable;
		
	}
    return 0;
}

STEAM_API int STEAM_CALL SteamMountAppFilesystem(TSteamError *pError)
{
// #ifdef DEBUG
	if (bLogging && bLogFS) Logger->Write("SteamMountAppFilesystem\n");
// #endif
	SteamClearError(pError);
	return 1;
}

STEAM_API int STEAM_CALL SteamUnmountAppFilesystem(TSteamError* pError)
{
// #ifdef DEBUG
	if (bLogging && bLogFS) Logger->Write("SteamUnmountAppFilesystem\n");
// #endif
	SteamClearError(pError);
	return 0;
}

STEAM_API int STEAM_CALL SteamMountFilesystem(unsigned int uAppId, const char *szMountPath, TSteamError *pError)
{
// #ifdef DEBUG
	if (bLogging) Logger->Write("SteamMountFilesystem AppId: %u Path: %s\n", uAppId, szMountPath);
// #endif	
	SteamClearError(pError);
	return 0;
}

STEAM_API int STEAM_CALL SteamUnmountFilesystem(unsigned int uAppId, TSteamError *pError)
{
// #ifdef DEBUG
	if (bLogging && bLogFS) Logger->Write("SteamUnmountFilesystem\n");
// #endif
	SteamClearError(pError);
	return 0;
}

STEAM_API SteamHandle_t STEAM_CALL SteamOpenFileEx(const char *cszFileName, const char *cszMode, unsigned int *size, TSteamError *pError)
{
// #ifdef DEBUG
	if (bLogging && bLogFS) Logger->Write("SteamOpenFileEx: %s\n", cszFileName);
// #endif
	/*if (bSteamDll && bSteamFileSystem)
	{
		SteamHandle_t retval = 0;
		SteamOpenFileExCall CallSteamOpenFileEx;
		CallSteamOpenFileEx = (SteamOpenFileExCall) GetProcAddress(GetModuleHandleA(szOrigSteamDll), "SteamOpenFileEx");
		retval = CallSteamOpenFileEx(cszFileName, cszMode, size, pError);
		if (bLogging && bLogFS) Logger->Write("\t %u\n", retval);
		return retval;
	}*/
	return SteamOpenFile2(cszFileName, cszMode, size, pError);
}

STEAM_API SteamHandle_t STEAM_CALL SteamOpenFile(const char *cszFileName, const char *cszMode, TSteamError *pError)
{
	if (bLogging && bLogFS) Logger->Write("SteamOpenFile %s, %s\n", cszFileName, cszMode);
	/*if(bSteamDll && bSteamFileSystem)
	{
		SteamClearError(pError);
		SteamHandle_t retval = 0;
		SteamHandle_t (*fptr)(const char*, const char*, TSteamError*);
		*(void **)(&fptr) = GetProcAddress(GetModuleHandleA(szOrigSteamDll), "SteamOpenFile");
		retval = (*fptr)(cszFileName, cszMode, pError);
		if (bLogging && bLogFS) Logger->Write("\t %u\n", retval);
		return retval;
	}*/
	SteamClearError(pError);
	SteamHandle_t retval = (SteamHandle_t)fopen(cszFileName, cszMode);
	if (!retval)
	{
		pError->eSteamError = eSteamErrorNotFound;
		pError->eDetailedErrorType = eNoDetailedErrorAvailable;
		return 0;
	}
	return retval;
}

STEAM_API SteamHandle_t STEAM_CALL SteamOpenTmpFile(TSteamError *pError)
{
// #ifdef DEBUG
	if (bLogging && bLogFS) Logger->Write("SteamOpenTmpFile\n");
// #endif
	
	/*if(bSteamDll && bSteamFileSystem)
	{
		SteamHandle_t retval = 0;
		int (*fptr)(TSteamError*);
		*(void **)(&fptr) = GetProcAddress(GetModuleHandleA(szOrigSteamDll), "SteamOpenTmpFile");
		retval = (*fptr)(pError);
		if (bLogging && bLogFS) Logger->Write("\t %u\n", retval);
		return retval;

	}*/
	SteamClearError(pError);
	return NULL;
}

STEAM_API int STEAM_CALL SteamFlushFile(SteamHandle_t hFile, TSteamError *pError)
{
// #ifdef DEBUG
	if (bLogging && bLogFS) Logger->Write("SteamFlushFile\n");
// #endif
	/*if(bSteamDll && bSteamFileSystem)
	{
		int retval = 0;
		int (*fptr)(SteamHandle_t, TSteamError*);
		*(void **)(&fptr) = GetProcAddress(GetModuleHandleA(szOrigSteamDll), "SteamFlushFile");
		retval = (*fptr)(hFile, pError);
		if (bLogging && bLogFS) Logger->Write("\t %u\n", retval);
		return retval;
	}*/
	SteamClearError(pError);
	int retval = fflush(reinterpret_cast<FILE*>(hFile));
	if (retval != 0)
	{
		pError->eSteamError = eSteamErrorEOF;
		pError->eDetailedErrorType = eNoDetailedErrorAvailable;
	}
	return retval;
}

STEAM_API int STEAM_CALL SteamCloseFile(SteamHandle_t hFile, TSteamError *pError)
{
// #ifdef DEBUG
	if (bLogging && bLogFS) Logger->Write("SteamCloseFile 0x%08X\n", (long)hFile);
// #endif
	/*if(bSteamDll && bSteamFileSystem)
	{
		int retval = 0;
		int (*fptr)(SteamHandle_t, TSteamError*);
		*(void **)(&fptr) = GetProcAddress(GetModuleHandleA(szOrigSteamDll), "SteamCloseFile");
		retval = (*fptr)(hFile, pError);
		if (bLogging && bLogFS) Logger->Write("\t %u\n", retval);
		return retval;
	}*/
	SteamClearError(pError);
	int retval = fclose(reinterpret_cast<FILE*>(hFile));
	if (retval != 0)
	{
		pError->eSteamError = eSteamErrorEOF;
		pError->eDetailedErrorType = eNoDetailedErrorAvailable;
	}
	return retval;
}

STEAM_API int STEAM_CALL SteamSetvBuf(SteamHandle_t hFile, void* pBuf, ESteamBufferMethod eMethod, unsigned int uBytes, TSteamError *pError)
{
// #ifdef DEBUG
	if (bLogging && bLogFS) Logger->Write("SteamSetvBuf\n");
// #endif
	/*if(bSteamDll && bSteamFileSystem)
	{
		int retval = 0;
		int (*fptr)(SteamHandle_t, void*, ESteamBufferMethod, unsigned int, TSteamError*);
		*(void **)(&fptr) = GetProcAddress(GetModuleHandleA(szOrigSteamDll), "SteamSetvBuf");
		retval = (*fptr)(hFile, pBuf, eMethod, uBytes, pError);
		if (bLogging && bLogFS) Logger->Write("\t %u\n", retval);
		return retval;
	}*/
	SteamClearError(pError);
	return 0;
}

STEAM_API int STEAM_CALL SteamGetc(SteamHandle_t hFile, TSteamError *pError)
{
// #ifdef DEBUG
	if (bLogging && bLogFS) Logger->Write("SteamGetc\n");
// #endif
	/*if(bSteamDll && bSteamFileSystem)
	{
		int retval = 0;
		int (*fptr)(SteamHandle_t, TSteamError*);
		*(void **)(&fptr) = GetProcAddress(GetModuleHandleA(szOrigSteamDll), "SteamGetc");
		retval = (*fptr)(hFile, pError);
		if (bLogging && bLogFS) Logger->Write("\t %u\n", retval);
		return retval;
	}*/
	SteamClearError(pError);
	int retval = fgetc(reinterpret_cast<FILE*>(hFile));
	if (ferror(reinterpret_cast<FILE*>(hFile)))
	{
		pError->eSteamError = eSteamErrorEOF;
		pError->eDetailedErrorType = eNoDetailedErrorAvailable;
	}
	return retval;
}

STEAM_API int STEAM_CALL SteamPutc(int cChar, SteamHandle_t hFile, TSteamError *pError)
{
// #ifdef DEBUG
	if (bLogging && bLogFS) Logger->Write("SteamPutc\n");
// #endif
	/*if(bSteamDll && bSteamFileSystem)
	{
		int retval = 0;
		int (*fptr)(int, SteamHandle_t, TSteamError*);
		*(void **)(&fptr) = GetProcAddress(GetModuleHandleA(szOrigSteamDll), "SteamPutc");
		retval = (*fptr)(cChar, hFile, pError);
		if (bLogging && bLogFS) Logger->Write("\t %u\n", retval);
		return retval;
	}*/
	SteamClearError(pError);
	int retval = fputc(cChar, reinterpret_cast<FILE*>(hFile));
	if (ferror(reinterpret_cast<FILE*>(hFile)))
	{
		pError->eSteamError = eSteamErrorEOF;
		pError->eDetailedErrorType = eNoDetailedErrorAvailable;
	}
	return retval;
}

STEAM_API int STEAM_CALL SteamPrintFile(SteamHandle_t hFile, TSteamError *pError, const char *cszFormat, ...)
{
// #ifdef DEBUG
	if (bLogging && bLogFS) Logger->Write("SteamPrintFile\n");
// #endif
	/*int (*fptr)(SteamHandle_t, TSteamError*, const char*, ...);
	*(void **)(&fptr) = GetProcAddress(GetModuleHandleA(szOrigSteamDll), "SteamPrintFile");
	return (*fptr)(hFile, pError, cszFormat);*/
	SteamClearError(pError);
	return -1;
}

STEAM_API unsigned int STEAM_CALL SteamReadFile(void *pBuf, unsigned int uSize, unsigned int uCount, SteamHandle_t hFile, TSteamError *pError)
{
// #ifdef DEBUG
	if (bLogging && bLogFS) Logger->Write("SteamReadFile 0x%08x 0x%08x\n", hFile, uSize * uCount);
// #endif
	/*if(bSteamDll && bSteamFileSystem)
	{
		int retval = 0;
		SteamReadFileCall CallSteamReadFile;
		CallSteamReadFile = (SteamReadFileCall) GetProcAddress(GetModuleHandleA(szOrigSteamDll), "SteamReadFile");
		retval = CallSteamReadFile(pBuf, uSize, uCount, hFile, pError);
		if (bLogging && bLogFS) Logger->Write("\t %u\n", retval);
		return retval;
	}*/
	SteamClearError(pError);
	unsigned int retval = fread(pBuf, uSize, uCount, reinterpret_cast<FILE*>(hFile));
	if (ferror(reinterpret_cast<FILE*>(hFile)))
	{
		pError->eSteamError = eSteamErrorEOF;
		pError->eDetailedErrorType = eNoDetailedErrorAvailable;
	}
	return retval;
}

STEAM_API unsigned int STEAM_CALL SteamWriteFile(const void *pBuf, unsigned int uSize, unsigned int uCount, SteamHandle_t hFile, TSteamError *pError)
{
// #ifdef DEBUG
	if (bLogging && bLogFS) Logger->Write("SteamWriteFile (0x%08X, %u, %u, 0x%08X)\n", pBuf, uSize, uCount, (int)hFile);
// #endif
	/*if(bSteamDll && bSteamFileSystem)
	{
		unsigned int retval = 0;
		unsigned int (*fptr)(const void*, unsigned int, unsigned int, SteamHandle_t, TSteamError*);
		*(void **)(&fptr) = GetProcAddress(GetModuleHandleA(szOrigSteamDll), "SteamWriteFile");
		retval = (*fptr)(pBuf, uSize, uCount, hFile, pError);
		if (bLogging && bLogFS) Logger->Write("\t %u\n", retval);
		return retval;
	}*/
	FILE* pFile = (FILE*) hFile;

	if(pFile && pBuf && pError)
	{
		int nBytes = fwrite(pBuf, uSize, uCount, (FILE*)hFile);

		if(nBytes == uCount)
		{
			SteamClearError(pError);
			return nBytes;
		}
	}
	pError->eSteamError = eSteamErrorEOF;
	pError->eDetailedErrorType = eNoDetailedErrorAvailable;
    return 0;
}

STEAM_API int STEAM_CALL SteamSeekFile(SteamHandle_t hFile, long lOffset, ESteamSeekMethod esMethod, TSteamError *pError)
{
// #ifdef DEBUG
	if (bLogging && bLogFS) Logger->Write("SteamSeekFile: 0x%08X, 0x%08X\n", (long)hFile, lOffset);
// #endif
	/*if(bSteamDll && bSteamFileSystem)
	{
		int retval = 0;
		int (*fptr)(SteamHandle_t, long, ESteamSeekMethod, TSteamError*);
		*(void **)(&fptr) = GetProcAddress(GetModuleHandleA(szOrigSteamDll), "SteamSeekFile");
		retval = (*fptr)(hFile, lOffset, esMethod, pError);
		if (bLogging && bLogFS) Logger->Write("\t %u\n", retval);
		return retval;
	}*/
	SteamClearError(pError);
	int retval = fseek(reinterpret_cast<FILE*>(hFile), lOffset, esMethod);
	if (retval != 0)
	{
		pError->eSteamError = eSteamErrorSeek;
		pError->eDetailedErrorType = eNoDetailedErrorAvailable;
	}
	return retval;
}

STEAM_API long STEAM_CALL SteamSizeFile(SteamHandle_t hFile, TSteamError *pError)
{
// #ifdef DEBUG
		if (bLogging && bLogFS) Logger->Write("SteamSizeFile: %d\n", hFile);
// #endif
	/*if(bSteamDll && bSteamFileSystem)
	{
		long retval = 0;
		long (*fptr)(SteamHandle_t, TSteamError*);
		*(void **)(&fptr) = GetProcAddress(GetModuleHandleA(szOrigSteamDll), "SteamSizeFile");
		retval = (*fptr)(hFile, pError);
		if (bLogging && bLogFS) Logger->Write("\t %u\n", retval);
		return retval;
	}*/
	SteamClearError(pError);
	FILE* pFile = reinterpret_cast<FILE*>(hFile);
	return _filelength(pFile->_file);
}

STEAM_API long STEAM_CALL SteamTellFile(SteamHandle_t hFile, TSteamError *pError)
{
// #ifdef DEBUG
	if (bLogging && bLogFS) Logger->Write("SteamTellFile %u\n", hFile);
// #endif
	/*if(bSteamDll && bSteamFileSystem)
	{
		long retval = 0;
		long (*fptr)(SteamHandle_t, TSteamError*);
		*(void **)(&fptr) = GetProcAddress(GetModuleHandleA(szOrigSteamDll), "SteamTellFile");
		retval = (*fptr)(hFile, pError);
		if (bLogging && bLogFS) Logger->Write("\t %u\n", retval);
		return retval;
	}*/
	SteamClearError(pError);
	return ftell(reinterpret_cast<FILE*>(hFile));
}

STEAM_API int STEAM_CALL SteamStat(const char *cszFileName, TSteamElemInfo *pInfo, TSteamError *pError)
{
// #ifdef DEBUG
	if (bLogging && bLogFS) Logger->Write("SteamStat %s, 0x%p, 0x%p\n", cszFileName, pInfo, pError);
// #endif
	/*if(bSteamDll && bSteamFileSystem)
	{
		int retval = 0;
		SteamStatCall CallSteamStat;
		CallSteamStat = (SteamStatCall) GetProcAddress(GetModuleHandleA(szOrigSteamDll), "SteamStat");
		retval = CallSteamStat(cszFileName, pInfo, pError);
		if (bLogging && bLogFS) Logger->Write("\t %u\n", retval);
		return retval;
	}*/

	struct _stat mystat;

	if(_stat(cszFileName, &mystat) == 0)
	{
		pInfo->bIsDir = ((mystat.st_mode & S_IFMT) == S_IFDIR);

		pInfo->bIsLocal = 1;

		char* Period = (char*) strrchr(cszFileName, '\\');
		strcpy( pInfo->cszName, Period + 1 );

		pInfo->lCreationTime = mystat.st_ctime;
		pInfo->lLastAccessTime = mystat.st_atime;
		pInfo->lLastModificationTime = mystat.st_mtime;
		pInfo->uSizeOrCount = mystat.st_size;

		SteamClearError(pError);
		return 0;
	}
	pError->eSteamError = eSteamErrorNotFound;
	pError->eDetailedErrorType = eNoDetailedErrorAvailable;
	return -1;
}


STEAM_API int STEAM_CALL SteamFindClose(SteamHandle_t hFind, TSteamError *pError)
{
// #ifdef DEBUG
	if (bLogging && bLogFS) Logger->Write("SteamFindClose\n");
// #endif
	/*if(bSteamDll && bSteamFileSystem)
	{
		int retval = 0;
		int (*fptr)(SteamHandle_t, TSteamError*);
		*(void **)(&fptr) = GetProcAddress(GetModuleHandleA(szOrigSteamDll), "SteamFindClose");
		retval = (*fptr)(hFind, pError);
		if (bLogging && bLogFS) Logger->Write("\t %u\n", retval);
		return retval;
	}*/
	SteamClearError(pError);
	return _findclose(hFind);
}

STEAM_API SteamHandle_t STEAM_CALL SteamFindFirst(const char *cszPattern, ESteamFindFilter eFilter, TSteamElemInfo *pFindInfo, TSteamError *pError)
{
// #ifdef DEBUG
	if (bLogging && bLogFS) Logger->Write("SteamFindFirst: %s\n", cszPattern);
// #endif
	/*if(bSteamDll && bSteamFileSystem)
	{
		SteamHandle_t retval = 0;
		SteamFindFirstCall CallSteamFindFirst;
		CallSteamFindFirst = (SteamFindFirstCall) GetProcAddress(GetModuleHandleA(szOrigSteamDll), "SteamFindFirst");
		retval = CallSteamFindFirst(cszPattern, eFilter, pFindInfo, pError);
		if (bLogging && bLogFS) Logger->Write("\t %u\n", retval);
		return retval;
	}*/
	_finddata_t finddata;

	int retval = _findfirst(cszPattern, &finddata);

	if(retval != (int)INVALID_HANDLE_VALUE)
	{
		pFindInfo->bIsDir = ((finddata.attrib & _A_SUBDIR) != 0);
		pFindInfo->uSizeOrCount = finddata.size;
		pFindInfo->bIsLocal = TRUE;
		pFindInfo->lCreationTime = (long)finddata.time_create;
		pFindInfo->lLastAccessTime = (long)finddata.time_access;
		pFindInfo->lLastModificationTime = (long)finddata.time_write;
		strcpy(pFindInfo->cszName, finddata.name);
		SteamClearError(pError);
	}
	else
	{
		pError->eSteamError = eSteamErrorBadArg;
		pError->eDetailedErrorType = eNoDetailedErrorAvailable;
	}
	return retval;
}

STEAM_API int STEAM_CALL SteamFindNext(SteamHandle_t hFind, TSteamElemInfo *pFindInfo, TSteamError *pError)
{
// #ifdef DEBUG
	if (bLogging && bLogFS) Logger->Write("SteamFindNext %s\n", pFindInfo->cszName);
// #endif
	/*if(bSteamDll && bSteamFileSystem)
	{
		int retval = 0;
		int (*fptr)(SteamHandle_t, TSteamElemInfo*, TSteamError*);
		*(void **)(&fptr) = GetProcAddress(GetModuleHandleA(szOrigSteamDll), "SteamFindNext");
		retval = (*fptr)(hFind, pFindInfo, pError);
		if (bLogging && bLogFS) Logger->Write("\t %u\n", retval);
		return retval;
	}*/
	struct _finddata_t finddata;

	int retval = _findnext(hFind, &finddata);

	if(retval != -1)
	{
		pFindInfo->bIsDir = ((finddata.attrib & _A_SUBDIR) != 0);
		pFindInfo->uSizeOrCount = finddata.size;
		pFindInfo->bIsLocal = TRUE;
		pFindInfo->lCreationTime = (long)finddata.time_create;
		pFindInfo->lLastAccessTime = (long)finddata.time_access;
		pFindInfo->lLastModificationTime = (long)finddata.time_write;
		strcpy(pFindInfo->cszName, finddata.name);
		SteamClearError(pError);
	}
	pError->eSteamError = eSteamErrorNotFound;
	pError->eDetailedErrorType = eNoDetailedErrorAvailable;
	return retval;
}

STEAM_API int STEAM_CALL SteamGetLocalFileCopy(const char *cszFileName, TSteamError *pError)
{
// #ifdef DEBUG
	if (bLogging && bLogFS) Logger->Write("SteamGetLocalFileCopy: %s\n", cszFileName);
// #endif
	/*if(bSteamDll && bSteamFileSystem)
	{
		int retval = 0;
		int (*fptr)(const char*, TSteamError*);
		*(void **)(&fptr) = GetProcAddress(GetModuleHandleA(szOrigSteamDll), "SteamGetLocalFileCopy");
		retval = (*fptr)(cszFileName, pError);
		if (bLogging && bLogFS) Logger->Write("\t %u\n", retval);
		return retval;
	}*/
	if(cszFileName[1] != ':')
	{
		char pathbuffer[MAX_PATH];
		pathbuffer[0] = 0;
		_searchenv(cszFileName, "PATH", pathbuffer);
		if(pathbuffer[0] != 0)
		{
			SteamClearError(pError);
			return 1;
		}
	}
	else if(FILE* file = fopen(cszFileName, "r"))
	{
		SteamClearError(pError);
		fclose(file);
		return 1;
	}
	Logger->Write("SteamGetLocalFileCopy: %s Failed\n", cszFileName);
	return 0;
}

STEAM_API int STEAM_CALL SteamIsFileImmediatelyAvailable(const char *cszName, TSteamError *pError)
{
// #ifdef DEBUG
	if (bLogging && bLogFS) Logger->Write("SteamIsFileImmediatelyAvailable\n");
// #endif
	/*if(bSteamDll && bSteamFileSystem)
	{
		int retval = 0;
		int (*fptr)(const char*, TSteamError*);
		*(void **)(&fptr) = GetProcAddress(GetModuleHandleA(szOrigSteamDll), "SteamIsFileImmediatelyAvailable");
		retval = (*fptr)(cszName, pError);
		if (bLogging && bLogFS) Logger->Write("\t %u\n", retval);
		return retval;
	}*/
	SteamClearError(pError);
	return 1;
}

STEAM_API int STEAM_CALL SteamHintResourceNeed(const char *cszHintList, int bForgetEverything, TSteamError *pError)
{
// #ifdef DEBUG
	if (bLogging && bLogFS) Logger->Write("SteamHintResourceNeed: %s, %d\n", cszHintList, bForgetEverything);
// #endif
	/*if(bSteamDll && bSteamFileSystem)
	{
		int retval = 0;
		int (*fptr)(const char*, int, TSteamError*);
		*(void **)(&fptr) = GetProcAddress(GetModuleHandleA(szOrigSteamDll), "SteamHintResourceNeed");
		retval =(*fptr)(cszHintList, bForgetEverything, pError);
		if (bLogging && bLogFS) Logger->Write("\t %u\n", retval);
		return retval;
	}*/
	SteamClearError(pError);
	return TRUE;
}

STEAM_API int STEAM_CALL SteamForgetAllHints(TSteamError *pError)
{
// #ifdef DEBUG
	if (bLogging && bLogFS) Logger->Write("SteamForgetAllHints\n");
// #endif
	/*if(bSteamDll && bSteamFileSystem)
	{
		int retval = 0;
		int (*fptr)(TSteamError*);
		*(void **)(&fptr) = GetProcAddress(GetModuleHandleA(szOrigSteamDll), "SteamForgetAllHints");
		retval = (*fptr)(pError);
		if (bLogging && bLogFS) Logger->Write("\t %u\n", retval);
		return retval;
	}*/
	SteamClearError(pError);
	return TRUE;
}

STEAM_API int STEAM_CALL SteamPauseCachePreloading(TSteamError *pError)
{
// #ifdef DEBUG
	if (bLogging && bLogFS) Logger->Write("SteamPauseCachePreloading\n");
// #endif
	SteamClearError(pError);
	return 1;
}

STEAM_API int STEAM_CALL SteamResumeCachePreloading(TSteamError *pError)
{
// #ifdef DEBUG
	if (bLogging && bLogFS) Logger->Write("SteamResumeCachePreloading\n");
// #endif
	SteamClearError(pError);
	return 1;
}

STEAM_API SteamCallHandle_t STEAM_CALL SteamWaitForResources(const char *cszMasterList, TSteamError *pError)
{
// #ifdef DEBUG
	if (bLogging && bLogFS) Logger->Write("SteamWaitForResources\n");
// #endif
	SteamClearError(pError);
	return 0;
}

STEAM_API SteamCallHandle_t STEAM_CALL SteamFlushCache(unsigned int uAppId, TSteamError *pError)
{
// #ifdef DEBUG
	if (bLogging && bLogFS) Logger->Write("SteamFlushCache\n");
// #endif
	SteamClearError(pError);
	return 1;
}

STEAM_API int STEAM_CALL SteamGetCacheDecryptionKey()
{
// #ifdef DEBUG
	if (bLogging && bLogFS) Logger->Write("SteamGetCacheDecryptionKey\n");
// #endif
	return 1;
}

STEAM_API int STEAM_CALL SteamGetCacheDefaultDirectory(char *szPath, TSteamError *pError)
{
// #ifdef DEBUG
	if (bLogging && bLogFS) Logger->Write("SteamGetCacheDefaultDirectory\n");
// #endif
	SteamClearError(pError);
	return 1;
}

STEAM_API int STEAM_CALL SteamSetCacheDefaultDirectory(const char *szPath, TSteamError *pError)
{
// #ifdef DEBUG
	if (bLogging && bLogFS) Logger->Write("SteamSetCacheDefaultDirectory\n");
// #endif
	SteamClearError(pError);
	return 1;
}

STEAM_API int STEAM_CALL SteamGetCacheFilePath(unsigned int uAppId,  char* szFilePath, unsigned int uBufferLength, unsigned int* puRecievedLength, TSteamError *pError)
{
// #ifdef DEBUG
	if (bLogging && bLogFS) Logger->Write("SteamGetCacheFilePath\n");
// #endif
	SteamClearError(pError);
	return 1;
}

STEAM_API int STEAM_CALL SteamIsFileNeededByCache()
{
// #ifdef DEBUG
	if (bLogging && bLogFS) Logger->Write("SteamIsFileNeededByCache\n");
// #endif
	return 1;
}

STEAM_API int STEAM_CALL SteamRepairOrDecryptCaches()
{
// #ifdef DEBUG
	if (bLogging && bLogFS) Logger->Write("SteamRepairOrDecryptCaches\n");
// #endif
	return 1;
}

STEAM_API int STEAM_CALL SteamCreateCachePreloaders(TSteamError *pError)
{
// #ifdef DEBUG
	if (bLogging && bLogFS) Logger->Write("SteamCreateCachePreloaders\n");
// #endif
	SteamClearError(pError);
	return 1;
}

STEAM_API int STEAM_CALL SteamIsCacheLoadingEnabled(unsigned int uAppId, int *pbIsLoading, TSteamError *pError)
{
// #ifdef DEBUG
	if (bLogging && bLogFS) Logger->Write("SteamIsCacheLoadingEnabled\n");
// #endif
	SteamClearError(pError);
	return 1;
}

STEAM_API SteamCallHandle_t STEAM_CALL SteamLoadCacheFromDir(unsigned int uAppId, const char *szPath, TSteamError *pError)
{
// #ifdef DEBUG
	if (bLogging && bLogFS) Logger->Write("SteamLoadCacheFromDir\n");
// #endif
	SteamClearError(pError);
	return 1;
}

STEAM_API int STEAM_CALL SteamLoadFileToCache()
{
// #ifdef DEBUG
	if (bLogging && bLogFS) Logger->Write("SteamLoadFileToCache\n");
// #endif
	return 1;
}

STEAM_API SteamCallHandle_t STEAM_CALL SteamStartLoadingCache(unsigned int uAppId, TSteamError *pError)
{
// #ifdef DEBUG
	if (bLogging && bLogFS) Logger->Write("SteamStartLoadingCache\n");
// #endif
	SteamClearError(pError);
	return 1;
}

STEAM_API SteamCallHandle_t STEAM_CALL SteamStopLoadingCache(unsigned int uAppId, TSteamError *pError)
{
// #ifdef DEBUG
	if (bLogging && bLogFS) Logger->Write("SteamStopLoadingCache\n");
// #endif
	SteamClearError(pError);
	return 1;
}