#pragma once

typedef enum
{
	eLODescription = 1,
	eLOCommandLine = 2,
	eLOIconIndex = 3,
	eLONoDesktopShortcut = 4,
	eLONoStartMenuShortcut = 5,
	eLOLongRunningUnattended = 6
}ELaunchOptionFields;

class CAppLaunchOptionRecord
{
public:
	char* Description;
	char* CommandLine;
	int IconIndex;
	bool NoDesktopShortcut;
	bool NoStartMenuShortcut;
	bool LongRunningUnattended;

	CAppLaunchOptionRecord()
	{
	}

	~CAppLaunchOptionRecord()
	{
	}

	char* Enumerate(char* LOBinary)
	{
		TNodeHeader *NodeHeader = (TNodeHeader*)LOBinary;
		if(NodeHeader->magic != NodeMagicNum)
		{
			return NULL;
		}
		else
		{
			char* NodeEnd = LOBinary + NodeHeader->datalength;
			LOBinary += sizeof(TNodeHeader);

			while(LOBinary < NodeEnd)
			{
				TDescriptorNode *DNode = (TDescriptorNode*)LOBinary;
				LOBinary += sizeof(TDescriptorNode);

				switch (DNode->type)
				{

					case eLODescription:
						this->Description = new char[DNode->datalength];
						memcpy(this->Description, LOBinary, DNode->datalength);
						LOBinary += DNode->datalength;
						break;
					
					case eLOCommandLine:
						this->CommandLine = new char[DNode->datalength];
						memcpy(this->CommandLine, LOBinary, DNode->datalength);
						LOBinary += DNode->datalength;
						break;

					case eLOIconIndex:
						this->IconIndex = *(int*)LOBinary;
						LOBinary += DNode->datalength;
						break;

					case eLONoDesktopShortcut:
						this->NoDesktopShortcut = *(bool*)LOBinary;
						LOBinary += DNode->datalength;
						break;

					case eLONoStartMenuShortcut:
						this->NoStartMenuShortcut = *(bool*)LOBinary;
						LOBinary += DNode->datalength;
						break;

					case eLOLongRunningUnattended:
						this->LongRunningUnattended = *(bool*)LOBinary;
						LOBinary += DNode->datalength;
						break;

					default:
						LOBinary += DNode->datalength;
						break;
				}
			}

			return (LOBinary + NodeHeader->nullpadding);
		}
	}
};
