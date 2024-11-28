#pragma once

class CCacheBlock
{

private:
	
	CCache* CacheFile;

public:

	TCacheBlockHeader* Header;
	TCacheBlockEntry* Entries;

	CCacheBlock(CCache* lpCacheFile)
	{
		CacheFile = lpCacheFile;
	}

	~CCacheBlock()
	{
	
		if (Header)
			delete Header;
		if(Entries)
			delete [] Entries;

	}

	bool Read(FILE* fCacheFile)
	{
		Header = new TCacheBlockHeader;
		fread((void*)Header, sizeof(TCacheBlockHeader), 1, fCacheFile);
		Entries = new TCacheBlockEntry[Header->BlockCount];

		for(unsigned int i = 0;i < Header->BlockCount; i++)
		{
			fread((void*)&Entries[i], sizeof(TCacheBlockEntry), 1, fCacheFile);
		}

		return true;
	}
};
