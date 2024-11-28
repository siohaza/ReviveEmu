#pragma once

class CCacheAllocationTable
{
private:

	CCache* CacheFile;

public:

	TCacheAllocationTableHeader* Header;
	TCacheAllocationTableEntry* Entries;

	CCacheAllocationTable(CCache* lpCacheFile)
	{
		CacheFile = lpCacheFile;
	}

	~CCacheAllocationTable()
	{
		if (Header)
			delete Header;
		if(Entries)
			delete [] Entries;
	}

	bool Read(FILE* fCacheFile)
	{
		Header = new TCacheAllocationTableHeader;
		fread((void*)Header, sizeof(TCacheAllocationTableHeader), 1, fCacheFile);
		Entries = new TCacheAllocationTableEntry[CacheFile->Header->SectorCount];

		for(unsigned int i = 0;i < CacheFile->Header->SectorCount; i++)
		{
			fread((void*)&Entries[i], sizeof(TCacheAllocationTableEntry), 1, fCacheFile);
		}

		return true;
	}
};
