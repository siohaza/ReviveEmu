#pragma once

#include "BlobSystemCommon.h"
#include "CBlobNode.h"
#include "CContentDescriptionRecord.h"

class CBlobFileSystem
{
private:
	char *BlobBinary;

public:
	FILE* BlobFile;
	CBlobNode *TopKey;

	CBlobFileSystem()
	{
	}

	~CBlobFileSystem()
	{
	}

	bool Open(const char* cszFileName)
	{
		if(BlobFile = fopen(cszFileName, "rb"))
		{
			fseek(BlobFile,0, SEEK_END);
			int BlobFileSize = ftell(BlobFile);
			fseek(BlobFile,0, SEEK_SET);
			BlobBinary = new char[BlobFileSize];
			unsigned int readedbytes = 0;
			if(fread(BlobBinary, 1, BlobFileSize, BlobFile))
			{
				TopKey = new CBlobNode();
				TopKey->Populate(BlobBinary);
			}
			Close();
			return true;
		}
		return false;
	}

	bool Close()
	{
		if(fclose(BlobFile) == 0)
		{
			delete BlobBinary;
			return true;
		}
		return false;
	}

	CBlobNode *GetNodeByPath(const char* cszNodePath)
	{
		char* szTempNodePath = new char[strlen(cszNodePath)+1];
		strcpy(szTempNodePath, cszNodePath);
		char* szNodeName = strtok(szTempNodePath, "\\");
		std::vector<CBlobNode*>::iterator NodesIterator = TopKey->Nodes.begin();
		std::vector<CBlobNode*>::iterator NodesEnd = TopKey->Nodes.end();
		for(; NodesIterator != NodesEnd; NodesIterator++ ) {
			if(strcmp(((CBlobNode*)*NodesIterator)->Name, szNodeName) == 0 && szNodeName != NULL)
			{
				szNodeName = strtok(NULL, "\\");
				if(szNodeName == NULL)
				{
					delete [] szTempNodePath;
					return (CBlobNode*)*NodesIterator;
				}
				if(((CBlobNode*)*NodesIterator)->Nodes.size() != 0)
				{
					std::vector<CBlobNode*>::iterator NodesIterator = ((CBlobNode*)*NodesIterator)->Nodes.begin();
					std::vector<CBlobNode*>::iterator NodesEnd = ((CBlobNode*)*NodesIterator)->Nodes.end();
				}
				else
				{
					break;
				}
			}
		}
		delete [] szTempNodePath;
		return NULL;
	}
};
