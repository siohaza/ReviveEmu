#pragma once

typedef enum
{
	eFSRAppId = 1,
	eFSRMountName = 2,
	eFSRIsOptional = 3
}EFileSystemFields;

class CAppFilesystemRecord
{
public:

	unsigned int AppId;
	char* MountName;
	bool IsOptional;

	CAppFilesystemRecord()
	{
	}

	~CAppFilesystemRecord()
	{
	}

	char* Enumerate(char* FSRBinary)
	{
		TNodeHeader *NodeHeader = (TNodeHeader*)FSRBinary;
		if(NodeHeader->magic != NodeMagicNum)
		{
			return NULL;
		}
		else
		{
			char* NodeEnd = FSRBinary + NodeHeader->datalength;
			FSRBinary += sizeof(TNodeHeader);

			while(FSRBinary < NodeEnd)
			{
				TDescriptorNode *DNode = (TDescriptorNode*)FSRBinary;
				FSRBinary += sizeof(TDescriptorNode);
				switch (DNode->type)
				{

					case eFSRAppId:
						this->AppId = *(unsigned int*)FSRBinary;
						FSRBinary += DNode->datalength;
						break;

					case eFSRMountName:
						this->MountName = new char[DNode->datalength];
						memcpy(this->MountName, FSRBinary, DNode->datalength);
						FSRBinary += DNode->datalength;
						break;

					case eFSRIsOptional:
						this->IsOptional = *(bool*)FSRBinary;
						FSRBinary += DNode->datalength;
						break;

					default:
						FSRBinary += DNode->datalength;
						break;
				}
			}

			return (FSRBinary + NodeHeader->nullpadding);
		}
	}
};
