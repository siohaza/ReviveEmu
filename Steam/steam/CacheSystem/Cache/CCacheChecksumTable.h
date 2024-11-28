#pragma once

class CCacheChecksumTable
{
private:

	CCache* CacheFile;

public:

	TCacheChecksumTableHeader* Header;
	TCacheChecksumTableMapHeader* MapHeader;
	TCacheChecksumTableMapEntry* MapEntries;
	TCacheChecksumTableEntry* Entries;

	CCacheChecksumTable(CCache* lpCacheFile)
	{
		CacheFile = lpCacheFile;
	}

	~CCacheChecksumTable()
	{

		if (Header)
			delete Header;
		if (MapHeader)
			delete MapHeader;
		if(Entries)
			delete [] Entries;
		if(MapEntries)
			delete [] MapEntries;

	}

	bool Read(FILE* fCacheFile)
	{
		Header = new TCacheChecksumTableHeader;
		fread((void*)Header, sizeof(TCacheChecksumTableHeader), 1, fCacheFile);
		MapHeader = new TCacheChecksumTableMapHeader;
		fread((void*)MapHeader, sizeof(TCacheChecksumTableMapHeader), 1, fCacheFile);
		MapEntries = new TCacheChecksumTableMapEntry[MapHeader->ItemCount];

		for(unsigned int i = 0;i < MapHeader->ItemCount; i++)
		{
			fread((void*)&MapEntries[i], sizeof(TCacheChecksumTableMapEntry), 1, fCacheFile);
		}

		Entries = new TCacheChecksumTableEntry[MapHeader->ChecksumCount + 0x20];

		for(unsigned int i = 0;i < MapHeader->ChecksumCount + 0x20; i++)
		{
			fread((void*)&Entries[i], sizeof(TCacheChecksumTableEntry), 1, fCacheFile);
		}

		return true;
	}
};
