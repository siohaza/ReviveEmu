#pragma once

class CCacheManifest
{
private:

	CCache* CacheFile;

public:

	TCacheManifestHeader* Header;
	TCacheManifestEntry* Entries;
	char* FileNames;
	TCacheManifestInfo1Entry* Info1Entries;
	TCacheManifestInfo2Entry* Info2Entries;
	TCacheManifestCopyEntry* CopyEntries;
	TCacheManifestLocalEntry* LocalEntries;
	TCacheManifestMapHeader* MapHeader;
	TCacheManifestMapEntry* MapEntries;

	CCacheManifest(CCache* lpCacheFile)
	{
		CacheFile = lpCacheFile;
	}

	~CCacheManifest()
	{
		if (Header)
			delete Header;
		if(Entries)
			delete [] Entries;
		if(FileNames)
			delete [] FileNames;
		if(Info1Entries)
			delete [] Info1Entries;
		if(Info2Entries)
			delete [] Info2Entries;
		if(CopyEntries)
			delete [] CopyEntries;
		if(LocalEntries)
			delete [] LocalEntries;
		if (MapHeader)
			delete MapHeader;
		if(MapEntries)
			delete [] MapEntries;

	}

	bool Read(FILE* fCacheFile)
	{
		Header = new TCacheManifestHeader;
		fread((void*)Header, sizeof(TCacheManifestHeader), 1, fCacheFile);
		Entries = new TCacheManifestEntry[Header->ItemCount];

		for(unsigned int i = 0;i < Header->ItemCount; i++)
		{
			fread((void*)&Entries[i], sizeof(TCacheManifestEntry), 1, fCacheFile);
		}

		FileNames = new char[Header->NameSize];
		fread((void*)FileNames, Header->NameSize, 1, fCacheFile);
		Info1Entries = new TCacheManifestInfo1Entry[Header->Info1Count];

		for(unsigned int i = 0;i < Header->Info1Count; i++)
		{
			fread((void*)&Info1Entries[i], sizeof(TCacheManifestInfo1Entry), 1, fCacheFile);
		}

		Info2Entries = new TCacheManifestInfo2Entry[Header->ItemCount];

		for(unsigned int i = 0;i < Header->ItemCount; i++)
		{
			fread((void*)&Info2Entries[i], sizeof(TCacheManifestInfo2Entry), 1, fCacheFile);
		}

		CopyEntries = new TCacheManifestCopyEntry[Header->CopyCount];

		for(unsigned int i = 0;i < Header->CopyCount; i++)
		{
			fread((void*)&CopyEntries[i], sizeof(TCacheManifestCopyEntry), 1, fCacheFile);
		}

		LocalEntries = new TCacheManifestLocalEntry[Header->LocalCount];

		for(unsigned int i = 0;i < Header->LocalCount; i++)
		{
			fread((void*)&LocalEntries[i], sizeof(TCacheManifestLocalEntry), 1, fCacheFile);
		}

		MapHeader = new TCacheManifestMapHeader;
		fread((void*)MapHeader, sizeof(TCacheManifestMapHeader), 1, fCacheFile);
		MapEntries = new TCacheManifestMapEntry[Header->ItemCount];

		for(unsigned int i = 0;i < Header->ItemCount; i++)
		{
			fread((void*)&MapEntries[i], sizeof(TCacheManifestMapEntry), 1, fCacheFile);
		}

		return true;
	}
};
