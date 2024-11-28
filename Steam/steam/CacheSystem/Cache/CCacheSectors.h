#pragma once

class CCacheSectors
{

private:

	CCache* CacheFile;

public:

	TCacheSectorsHeader* Header;

	CCacheSectors(CCache* lpCacheFile)
	{
		CacheFile = lpCacheFile;
	}

	~CCacheSectors()
	{
		if(Header)
			delete Header;
	}

	bool ReadHeader(FILE* fCacheFile)
	{
		Header = new TCacheSectorsHeader;
		fread((void*)Header, sizeof(TCacheSectorsHeader), 1, fCacheFile);
		return true;
	}
};
