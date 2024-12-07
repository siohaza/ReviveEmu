#include "CacheSystem\CacheSystemCommon.h"
#include "CacheSystem\Cache\CCache.h"
#include <direct.h>

#include "strtools.h"
//#include "Jenkins.h" // This doesn't produce unique ints for some reason - HL2DM - dm_resistance - pipecluster003a_small.mdl is wrongly identified as another files id
#include "GeneralHashFunctions.h"

	#if defined( _WIN32 ) || defined( WIN32 )
	#define PATHSEPARATOR(c) ((c) == '\\' || (c) == '/')
	#else	//_WIN32
	#define PATHSEPARATOR(c) ((c) == '/')
	#endif	//_WIN32


using namespace Common;


typedef struct
{
	FILE* fCacheFile;
	CCache* hCacheFile;
}TCacheHandle;

typedef struct
{
	bool IsFileLocal;
	union {
		FILE* LocalFile;
		TManifestEntriesInCache* FileInCache;
	};
	unsigned int Position;
	char mode[1];
}TFileInCacheHandle;

typedef struct
{
	bool IsFindLocal;
	union {
		unsigned int LocalFind;
		TManifestEntriesInCache* hFind;
	};
	ESteamFindFilter eFilter;
	char* szSearchString;
	int CurrentIndex;
	const char* cszPattern;
}TFindHandle;

class CCacheFileSystem
{
private:
	std::vector<const char*> Searches;

public:
	std::vector<TCacheHandle*> Caches;

	CCacheFileSystem()
	{
	}
	
	~CCacheFileSystem()
	{
	}

	unsigned int NumCaches()
	{
		return Caches.size();
	}

	CacheHandle MountCache(const char* cszFileName, unsigned int index, const char* ExtraMountPath)
	{

		std::string FullPath(cszFileName);
		int dot = FullPath.find_last_of('\\');
		std::string szTemp = FullPath.substr(dot + 1);

		std::vector<TCacheHandle*>::iterator CachesIterator;
		for( CachesIterator = Caches.begin(); CachesIterator != Caches.end(); CachesIterator++ ) 
		{
			CCache* CheckCacheFile = ((TCacheHandle*)*CachesIterator)->hCacheFile;

			if (strcmp(CheckCacheFile->Name,szTemp.c_str()) == 0)
			{

				if (bLogging && bLogFS)	Logger->Write("	Cache is already mounted: %s\n", cszFileName);

				return false;
			}
		}

		if(FILE* fCacheFile = fopen(cszFileName,"rb"))
		{
			CCache* CacheFile = new CCache(fCacheFile);
			CacheFile->Read(ExtraMountPath);
			CacheFile->Index = 0;
			CacheFile->bIsMounted = false;
			strcpy(CacheFile->Name,szTemp.c_str()); 
			TCacheHandle* hCache = new TCacheHandle;
			hCache->fCacheFile = fCacheFile;
			hCache->hCacheFile = CacheFile;
			Caches.push_back(hCache);
			
			BuildGlobalDirectoryTable(CacheFile);
		
			if (bLogging && bLogFS)	Logger->Write("	Mounted %s\n", cszFileName);

			return (unsigned int)hCache;

		}

		if (bLogging && bLogFS)	Logger->Write("	Failed to Mount %s\n", cszFileName);

		return false;

	}

	bool UnmountCache(CacheHandle hCache)
	{

		std::vector<TCacheHandle*>::iterator CachesIterator;

		for( CachesIterator = Caches.begin(); CachesIterator != Caches.end(); CachesIterator++ ) {
			if(((TCacheHandle*)*CachesIterator) == ((TCacheHandle*)hCache))
			{
				//if (bLogging && bLogFS) Logger->Write("	Unmounted %s\n", ((TCacheHandle*)*CachesIterator)->hCacheFile->Name);
				delete ((TCacheHandle*)*CachesIterator)->hCacheFile;
				fclose(((TCacheHandle*)*CachesIterator)->fCacheFile);
				delete ((TCacheHandle*)*CachesIterator);
				Caches.erase(CachesIterator);
				return true;
			}
		}

		return false;
	}

	TFileInCacheHandle* CacheOpenFileEx(const char *cszFileName, const char *cszMode, unsigned int *puSize)
	{


		TFileInCacheHandle* retval = NULL;

		if(TManifestEntriesInCache* FileToOpen = CacheFindFile(cszFileName, NULL))
		{
			retval = new TFileInCacheHandle();
			memset(retval, 0, sizeof(TFileInCacheHandle));
			retval->FileInCache = FileToOpen;

			if(puSize)
			{
				*puSize = FileToOpen->Size;
			}
			
			strcpy(retval->mode, cszMode);

			//LoggerFileOpened = true;

			//CCache* CacheFile = (CCache*)FileToOpen->pCache;
			//if (bLogging && bLogFS) Logger->Write("\tOpened 0x%08X from cache(%s) {%s} %s\n", (long)retval, cszMode, CacheFile->Name, cszFileName );
			//if (bLogging && bLogFS) Logger->Write("\tOpened 0x%08X from cache(%s) %s\n", (long)retval, cszMode, cszFileName );
			
			
		}
		return retval;
	}

	int CacheStat(const char *cszFileName, TSteamElemInfo *pInfo)
	{
	
		char szFileNamebuffer[MAX_PATH];
		strcpy(szFileNamebuffer,cszFileName);

		GetFilenameInCache(szFileNamebuffer);

		if(strlen(szFileNamebuffer) > 0)
		{

			if(TManifestEntriesInCache* ItemFound = FindItem(0,szFileNamebuffer))
			{

				pInfo->bIsDir = (ItemFound->Type == 0 ? 1 : 0);
				pInfo->uSizeOrCount = ItemFound->Size;
				pInfo->bIsLocal = 0;
				strcpy(pInfo->cszName, ItemFound->Name);
				pInfo->lCreationTime = 0x44444444;
				pInfo->lLastAccessTime = 0x44444444;
				pInfo->lLastModificationTime = 0x44444444;
				//if (bLogging && bLogFS) Logger->Write("\tStat succesfull from cache > %s\n", cszFileName);
	
				return 0;
			}

		}
		return -1;
	}

	int CacheCloseFile(TFileInCacheHandle* hFile)
	{
		if(hFile)
		{
			delete hFile;
			return 0;
		}
		return EOF;
	}

	unsigned int CacheExtractFile(TFileInCacheHandle* hFile, const char * czDest)
	{
		TManifestEntriesInCache *FileToExtract = hFile->FileInCache;
		char szFullPath[MAX_PATH];
		
		if (czDest)
		{
			strcpy(szFullPath, czDest);
		}
		else
		{
			//GetCurrentDirectoryA(MAX_PATH, szFullPath);
			strcpy(szFullPath, szRunFromPath);
		}

		V_ComposeFileName( szFullPath, FileToExtract->FullName, szFullPath, MAX_PATH );

		char szFilePath[MAX_PATH];
		V_ExtractFilePath(szFullPath, szFilePath, MAX_PATH);

		struct _stat filestat;

		int retval = _stat(szFilePath, &filestat);
		if(retval == -1)
		{
			CreateDir(szFilePath);
		}

		if(FILE* FileToWrite = fopen(szFullPath, "wb"))
		{
			unsigned int bytestoread = CacheSizeFile(hFile);
			unsigned int uBuffSize = 524288;
			char Buff[524288];
			while(bytestoread > 0)
			{
				if(bytestoread >= uBuffSize)
				{
					CacheReadFile(Buff, 1, uBuffSize, hFile);
					fwrite(Buff, 1, uBuffSize, FileToWrite);
					bytestoread -= uBuffSize;
				}
				else
				{
					CacheReadFile(Buff, 1, bytestoread, hFile);
					fwrite(Buff, 1, bytestoread, FileToWrite);
					bytestoread = 0;
				}
			}
			fclose(FileToWrite);
			//if (bLogging && bLogFS) Logger->Write("\tFound cache (%s) Extracted to > %s\n", FileToExtract->FullName,  szFilePath);
			return 1;
		}
		//if (bLogging && bLogFS) Logger->Write("\tFound cache (%s) FAILED to Extract to > %s\n", FileToExtract->FullName,  szFilePath);
		return 0;
	};

	unsigned int CacheReadFile(void *pBuf, unsigned int uSize, unsigned int uCount, TFileInCacheHandle* hFile)
	{

		unsigned int readedlength = 0;

		if (hFile)
		{

			if (strchr(hFile->mode, 'b'))
			{
				readedlength = ReadBinary(pBuf, uSize, uCount, hFile);
			}
			else
			{
				readedlength = ReadText(pBuf, uSize, uCount, hFile);
			}
		}

		return readedlength; // needs to return count

	}

	 
    unsigned int ReadBinary(void *pBuf, unsigned int uSize, unsigned int uCount, TFileInCacheHandle* hFile)
    {
 
        CCache* hCacheFile = (CCache*)hFile->FileInCache->pCache;
        TManifestEntriesInCache* hFileInCache =  hFile->FileInCache;
 
        unsigned char* szBuff = reinterpret_cast<unsigned char*>(pBuf);
        unsigned int uReadedDataAmount = 0;
        unsigned int uTotalDataToRead = uSize * uCount;
       
        //unsigned int uActualSectorIndex = hFile->Position / hCacheFile->Sectors->Header->PhysicalSectorSize;
        __int64 uActualSectorIndex = hFile->Position / hCacheFile->Sectors->Header->PhysicalSectorSize;
 
        while(uReadedDataAmount < uTotalDataToRead)
        {
            unsigned int uOffset = hFile->Position % hCacheFile->Sectors->Header->PhysicalSectorSize;
            unsigned int uActualDataToRead = ((hCacheFile->Sectors->Header->PhysicalSectorSize - uOffset) >= (uTotalDataToRead - uReadedDataAmount) ? (uTotalDataToRead - uReadedDataAmount) : (hCacheFile->Sectors->Header->PhysicalSectorSize - uOffset));
 
            unsigned int uReadedData = BinaryReadSector(uActualSectorIndex, szBuff, uOffset, uActualDataToRead, hFile);
           
            hFile->Position += uReadedData;
            uReadedDataAmount += uReadedData;
 
            if(uActualDataToRead != uReadedData)
            {
                //set errno
                break;
            }
 
            szBuff += uReadedData;
 
            uActualSectorIndex++;
        }
 
        return uReadedDataAmount;   
    }
 
    int BinaryReadSector(__int64 iSectorIndex, void* pvBuff, unsigned int uOffset, unsigned int uSize, TFileInCacheHandle* hFile)
    //int BinaryReadSector(int iSectorIndex, void* pvBuff, unsigned int uOffset, unsigned int uSize, TFileInCacheHandle* hFile)
    {
 
        CCache* hCacheFile = (CCache*)hFile->FileInCache->pCache;
        FILE* fCacheFile = hCacheFile->fCacheFile;
        TManifestEntriesInCache* hFileInCache =  hFile->FileInCache;
 
        int retval = 0;
       
        if(hFile->Position + uSize > hFileInCache->Size)
            uSize = hFileInCache->Size - hFile->Position;
 
        if(uSize > 0)
        {
            //long lReadPosition = hCacheFile->Sectors->Header->FirstSectorOffset + (hFileInCache->Sectors[iSectorIndex] * hCacheFile->Sectors->Header->PhysicalSectorSize) + uOffset;
            __int64 lReadPosition = hCacheFile->Sectors->Header->FirstSectorOffset + (hFileInCache->Sectors[iSectorIndex] * hCacheFile->Sectors->Header->PhysicalSectorSize) + uOffset;
            //if(fseek(fCacheFile, lReadPosition, SEEK_SET))
            if(_fseeki64(fCacheFile, lReadPosition, SEEK_SET))
                return retval;
 
            retval = fread(pvBuff, 1, uSize, fCacheFile);
        }
 
        return retval;
    }
 
    unsigned int ReadText(void *pBuf, unsigned int uSize, unsigned int uCount, TFileInCacheHandle* hFile)
    {
 
        CCache* hCacheFile = (CCache*)hFile->FileInCache->pCache;
        TManifestEntriesInCache* hFileInCache =  hFile->FileInCache;
 
        void* BufferedSector = new char[hCacheFile->Sectors->Header->PhysicalSectorSize];
        __int64 BufferedSectorIndex = 0xFFFFFFFFFFFFFFFF;
 
        unsigned char* szBuff = reinterpret_cast<unsigned char*>(BufferedSector);
        unsigned char* szBuffOut = reinterpret_cast<unsigned char*>(pBuf);
        unsigned int uReadedDataAmount = 0;
        unsigned int uReadedCharactersAmount = 0;
        unsigned int uDataAvailableToRead = 0;
        unsigned int uTotalDataToRead = uSize * uCount;
 
        //unsigned int uActualSectorIndex = hFile->Position / hCacheFile->Sectors->Header->PhysicalSectorSize;
        __int64 uActualSectorIndex = hFile->Position / hCacheFile->Sectors->Header->PhysicalSectorSize;
 
        while(uReadedDataAmount < uTotalDataToRead)
        {
            if(hFile->Position == hFileInCache->Size)//EOF
                break;
 
            if(BufferedSectorIndex != uActualSectorIndex)
            {
                if(TextReadSector(uActualSectorIndex, BufferedSector, hCacheFile->Sectors->Header->PhysicalSectorSize, hFile) != hCacheFile->Sectors->Header->PhysicalSectorSize)
                    break;
 
                BufferedSectorIndex = uActualSectorIndex;
            }
 
            unsigned int uOffset = hFile->Position % hCacheFile->Sectors->Header->PhysicalSectorSize;
            unsigned int uActualDataToRead = ((hCacheFile->Sectors->Header->PhysicalSectorSize - uOffset) > (uTotalDataToRead - uReadedDataAmount) ? (uTotalDataToRead - uReadedDataAmount) : (hCacheFile->Sectors->Header->PhysicalSectorSize - uOffset));
 
            uDataAvailableToRead = hCacheFile->Sectors->Header->PhysicalSectorSize - uOffset;
            if(uDataAvailableToRead > hFileInCache->Size - hFile->Position)
                uDataAvailableToRead = hFileInCache->Size - hFile->Position;
 
            unsigned int uReadedCharacters = 0;
 
            if(uActualDataToRead > 0)
            {
                unsigned int uReadedData = 0;
 
                do
                {
                    unsigned char ucChar = szBuff[uOffset + uReadedData];
                    if(ucChar != 0xD)
                    {
                        szBuffOut[uReadedCharactersAmount + uReadedCharacters] = ucChar;
                        uReadedCharacters++;
                    }
                    uReadedData++;
                }
                while(uReadedCharacters < uActualDataToRead && uReadedData < uDataAvailableToRead);
 
                hFile->Position += uReadedData;
                uReadedDataAmount += uReadedData;
                uReadedCharactersAmount += uReadedCharacters;
            }
 
            uActualSectorIndex++;
        }
 
        delete [] BufferedSector;
        return uReadedCharactersAmount;
    }
 
    //int TextReadSector(int iSectorIndex, void* pvBuff, unsigned int uSize, TFileInCacheHandle* hFile)
    int TextReadSector(__int64 iSectorIndex, void* pvBuff, unsigned int uSize, TFileInCacheHandle* hFile)
    {
 
        CCache* hCacheFile = (CCache*)hFile->FileInCache->pCache;
        FILE* fCacheFile = hCacheFile->fCacheFile;
        TManifestEntriesInCache* hFileInCache =  hFile->FileInCache;
 
        int retval = 0;
 
        //long lReadPosition = hCacheFile->Sectors->Header->FirstSectorOffset + (hFileInCache->Sectors[iSectorIndex] * hCacheFile->Sectors->Header->PhysicalSectorSize);
        __int64 lReadPosition = hCacheFile->Sectors->Header->FirstSectorOffset + (hFileInCache->Sectors[iSectorIndex] * hCacheFile->Sectors->Header->PhysicalSectorSize);
        //if(fseek(fCacheFile, lReadPosition, SEEK_SET))
        if(_fseeki64(fCacheFile, lReadPosition, SEEK_SET))
            return retval;
 
        retval = fread(pvBuff, 1, uSize, fCacheFile);
 
        return retval;
    }
 
	int CacheSeekFile(TFileInCacheHandle* hFile, long lOffset, ESteamSeekMethod esMethod)
	{
		int retval = -1;

		switch(esMethod)
		{
		case eSteamSeekMethodSet:
			if(lOffset <= (long)hFile->FileInCache->Size)
			{
				hFile->Position = lOffset;
				retval = 0;
			}
			break;
		case eSteamSeekMethodCur:
			if((hFile->Position + lOffset) >= 0 && (hFile->Position + lOffset) <= hFile->FileInCache->Size)
			{
				hFile->Position += lOffset;
				retval = 0;
			}
			break;
		case eSteamSeekMethodEnd:
			if(lOffset <= (long)hFile->FileInCache->Size)
			{
				hFile->Position = hFile->FileInCache->Size - lOffset;
				retval = 0;
			}
			break;
		default:
			break;
		}

		return retval;
	}


	int CacheTellFile(TFileInCacheHandle* hFile)
	{
		if(hFile)
		{
			return hFile->Position;
		}
		return -1;
	}


	int CacheSizeFile(TFileInCacheHandle* hFile)
	{
		if(hFile)
		{
			return hFile->FileInCache->Size;
		}
		return -1;
	}

	void CreateDir(char* Path) { 

		char DirName[256];
		char* p = const_cast<char*>(Path);
		char* q = DirName; 
		while(*p)
		{
			if (('\\' == *p) || ('/' == *p))
			{
				if (':' != *(p-1))
				{
					CreateDirectoryA(DirName, 0);
				}
			}
			*q++ = *p++;
			*q = '\0';
		}
		CreateDirectoryA(DirName, 0);
	}

	TFindHandle* CacheFindFirst(const char *cszPattern, ESteamFindFilter eFilter, TSteamElemInfo *pFindInfo)
	{		
		char szFileNamebuffer[MAX_PATH];
		strcpy(szFileNamebuffer,cszPattern);
		
		GetFilenameInCache(szFileNamebuffer);

		if(strlen(szFileNamebuffer) > 0)
		{
			if(TManifestEntriesInCache* ItemFound = FindItem(0,szFileNamebuffer))
			{
				pFindInfo->bIsDir = (ItemFound->Type == 0 ? 1 : 0);
				pFindInfo->bIsLocal = 0;
				strcpy(pFindInfo->cszName, ItemFound->Name);
				pFindInfo->uSizeOrCount = ItemFound->Size;
				pFindInfo->lCreationTime = 0x44444444;
				pFindInfo->lLastAccessTime = 0x44444444;
				pFindInfo->lLastModificationTime = 0x44444444;

				TFindHandle* hFind = new TFindHandle();
				hFind->IsFindLocal = 0;
				hFind->hFind = ItemFound;
				hFind->eFilter = eFilter;
				hFind->szSearchString = new char[strlen(szFileNamebuffer)+1];
				strcpy(hFind->szSearchString,szFileNamebuffer);
				hFind->cszPattern = new char[strlen(cszPattern)+1];
				strcpy((char*)hFind->cszPattern, cszPattern);

				hFind->CurrentIndex = GlobalIndexCounter;

				//if (bLogging && bLogFS) Logger->Write("\tFound first file {%s} (%s) using pattern (%s)\n", ((CCache*)hFind->hFind->pCache)->Name, ItemFound->Name, szFileNamebuffer);

				return hFind;
			}

		}
		return (TFindHandle*)0;
	}

	int CacheFindNext(TFindHandle* hFind, TSteamElemInfo *pFindInfo)
	{
		if(TManifestEntriesInCache* ItemFound = FindItem(hFind->CurrentIndex + 1, hFind->szSearchString))
		{
			pFindInfo->bIsDir = (ItemFound->Type == 0 ? 1 : 0);
			pFindInfo->bIsLocal = 0;
			strcpy(pFindInfo->cszName, ItemFound->Name);
			pFindInfo->uSizeOrCount = ItemFound->Size;
			pFindInfo->lCreationTime = 0x44444444;
			pFindInfo->lLastAccessTime = 0x44444444;
			pFindInfo->lLastModificationTime = 0x44444444;
			hFind->hFind = ItemFound;
			hFind->CurrentIndex = GlobalIndexCounter;

			//if (bLogging && bLogFS) Logger->Write("\tFound next file {%s} (%s) using pattern (%s)\n", ((CCache*)hFind->hFind->pCache)->Name, ItemFound->Name, hFind->szSearchString);
			
			return 0;
		}
			
		return -1;
	}

	int CacheFindClose(TFindHandle* hFind)
	{
		if (hFind) 
		{
			delete hFind;
		}
		return 0;
	}

private:
	TManifestEntriesInCache* FindItem(unsigned int LastIndex, char* cszPattern)
	{
		if(strpbrk(cszPattern, "?*"))
		{
			GlobalIndexCounter = LastIndex;
			while(GlobalIndexCounter < GlobalDirectoryTableSize)
			{		
				TGlobalDirectory &FindItem = GlobalDirectoryTable[GlobalIndexCounter];

				if(IsMatchingWithMask(FindItem.FullName, cszPattern))
				{
					CCache* CacheFile = (CCache*)FindItem.pCache;
					TManifestEntriesInCache* ItemFound = &CacheFile->DirectoryTable[FindItem.Index];
					return ItemFound;
				}

				GlobalIndexCounter++;
			}
		}
		else
		{
			//unsigned int EntryHash = JenkinsHash((unsigned char*)cszPattern, strlen(cszPattern), 0);
			unsigned int EntryHash = JSHash(cszPattern);
			
			std::map<unsigned int, TGlobalDirectory>::iterator HashIterator = HashTable.find(EntryHash);

			if(HashIterator != HashTable.end())
			{
				TGlobalDirectory &FindItem = HashIterator->second;

				CCache* CacheFile = (CCache*)FindItem.pCache;
				TManifestEntriesInCache* ItemFound = &CacheFile->DirectoryTable[FindItem.Index];
				if (ItemFound)
				{
					return ItemFound;
				}
			}
		}

		return NULL;
	}

	bool IsMatchingWithMask(char* szString, char* szMask)
	{

		while(*szString != 0 || *szMask != 0)
		{

			if(*szMask == '*')
			{
				szMask++;
				while(*szMask != *szString)
				{
					if (*szString == 0)
					{
						break;
					}
					else if (*szString == '\\')
					{
						break;
					}
					else
					{
						szString++;
					}
				}
			}
			else if(*szString == 0 && *szMask == 0)
			{
				break;
			}
			else if(*szString == 0 && *szMask != 0)
			{
				if(*szMask == '.')
				{
					szMask++;
				}
				if(*szMask == '*')
				{
					szMask++;
				}
				if(*szString == 0 && *szMask != 0)
				{
					return false;
				}
				else
				{
					break;
				}
			}
			else if(*szString != 0 && *szMask == 0)
			{
				return false;
			}
			else if(*szMask == '?')
			{
				szString++;
				szMask++;
			}
			else if(*szString == *szMask)
			{
				szString++;
				szMask++;
			}
			else
			{
				return false;
			}
		}

		return true;
	}


	void R_FullPathToRelativePath(const char* cszFullPath, char* szRelativePath, const char* cszBaseDirectory)
	{
		char szTempBaseDir[MAX_PATH];
		const char* cszBaseDir = cszBaseDirectory;

		if(!cszBaseDir)
		{
			strcpy(szTempBaseDir, szRunFromPath);
			//_getcwd(szTempBaseDir, MAX_PATH);
			cszBaseDir = szTempBaseDir;
		}

		if(strstr(cszFullPath, cszBaseDir) == cszFullPath)
		{
			const char* szStartRelativeFilePath = cszFullPath + strlen(cszBaseDir);
			while(PATHSEPARATOR(*szStartRelativeFilePath) || *szStartRelativeFilePath == 0)
			{
				szStartRelativeFilePath++;
			}

			strcpy(szRelativePath, szStartRelativeFilePath);
		}
	}


	void GetFilenameInCache(char * cszFileName)
	{

		_strlwr(cszFileName);

		char szCWD[MAX_PATH];
		strcpy(szCWD, szRunFromPath);

		/*
		if(_getcwd(szCWD, sizeof(szCWD)))
		{
			_strlwr(szCWD);
			V_FixSlashes(szCWD);
		}
		*/

		V_RemoveDotSlashes(cszFileName);

		if(V_IsAbsolutePath(cszFileName))
			R_FullPathToRelativePath(cszFileName, cszFileName, szCWD);

		if(cszFileName[1] == ':') {

			if(strstr(cszFileName, szCWD) == cszFileName)
			{
				cszFileName = cszFileName + strlen(szCWD);
			}
		}
		else
		{
			if(cszFileName[0] != '\\')
			{
				char fName[MAX_PATH];
				strcpy(fName,cszFileName);
				strcpy(cszFileName,"\\");
				strcat(cszFileName,fName);
			}
		}

		while(char* doubleslash = strstr(cszFileName, "\\\\"))
		{
			strcpy(doubleslash + 1, doubleslash + 2);
		}

		//if (bLogging && bLogFS)Logger->Write("\tSearching cache with (%s - %s)\n", cszFileName, szCWD);

	}


	TManifestEntriesInCache* CacheFindFile(const char *cszFileName, CCache* pCache)
	{

		char szFileNamebuffer[MAX_PATH];
		strcpy(szFileNamebuffer,cszFileName);

		GetFilenameInCache(szFileNamebuffer);

		if(strlen(szFileNamebuffer) > 0)
		{

			if(TManifestEntriesInCache* ItemFound = FindItem(0,szFileNamebuffer))
			{	
				return ItemFound;
			}
		}

		return NULL;
	}


private:
	void BuildGlobalDirectoryTable(CCache* CacheFile)
	{
		if (!CacheFile->bIsMounted)
		{
			TManifestEntriesInCache* DirectoryTable = CacheFile->DirectoryTable;
			TManifestEntriesInCache* ActualDirEntry;

			for(unsigned int CacheIndex = 1; CacheIndex < CacheFile->Manifest->Header->ItemCount ; CacheIndex++)
			{
				TGlobalDirectory FindThisItem;
				ActualDirEntry = &DirectoryTable[CacheIndex];

				//unsigned int EntryHash = JenkinsHash((unsigned char*)ActualDirEntry->FullName, strlen(ActualDirEntry->FullName), 0);
				unsigned int EntryHash = JSHash(ActualDirEntry->FullName);

				FindThisItem.pCache = ActualDirEntry->pCache;
				FindThisItem.FullName = ActualDirEntry->FullName;
				FindThisItem.Index = CacheIndex;

				if (!HashTable.count(EntryHash))
				{
					HashTable[EntryHash] = FindThisItem;

					GlobalDirectoryTable.push_back(FindThisItem);
					GlobalIndexCounter++;

					//if (bLogging && bLogFS) Logger->Write("\tAdd to Global Directory: %s\n", ActualDirEntry->FullName);
				}
				else
				{
					//if (bLogging && bLogFS) Logger->Write("\tExcluded from Global Directory: %s\n", ActualDirEntry->FullName);
				}
			}

			CacheFile->bIsMounted = true;

			GlobalDirectoryTableSize = HashTable.size();
		}
	}
};

