#pragma once

#include "BlobSystemCommon.h"
#include "CBlobNode.h"
#include "CContentDescriptionRecord.h"

class CBlobFileSystem
{
public:
	CBlobNode *TopKey;

	CBlobFileSystem()
	{
		TopKey = NULL;
	}

	~CBlobFileSystem()
	{
		if (TopKey)
			delete TopKey;
	}

	bool Open(const char* cszFileName)
	{
		if (FILE* BlobFile = fopen(cszFileName, "rb"))
		{
			fseek(BlobFile, 0, SEEK_END);
			int BlobFileSize = ftell(BlobFile);
			fseek(BlobFile, 0, SEEK_SET);
			char* BlobBinary = new char[BlobFileSize];
			unsigned int readedbytes = 0;
			if (fread(BlobBinary, 1, BlobFileSize, BlobFile))
			{
				TopKey = new CBlobNode();
				TopKey->Populate(BlobBinary);
			}
			fclose(BlobFile);
			delete[] BlobBinary;
			return true;
		}
		return false;
	}

	CBlobNode* GetNodeByPath(const char* cszNodePath) const
	{
		char szTempNodePath[MAX_PATH];
		strcpy(szTempNodePath, cszNodePath);
		char* szNodeName = strtok(szTempNodePath, "\\");

		for (CBlobNode* pNode : TopKey->Nodes)
		{
			if (strcmp(pNode->Name, szNodeName) == 0 && szNodeName != NULL)
			{
				szNodeName = strtok(NULL, "\\");
				if (szNodeName == NULL)
				{
					return pNode;
				}

				if (pNode->Nodes.size() != 0)
				{
					// TODO: Search recursively.
				}
				else
				{
					break;
				}
			}
		}

		return NULL;
	}
};
