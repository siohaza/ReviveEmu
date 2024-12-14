#pragma once

typedef enum
{
	eSDQName = 1,
	eSDQSubscriptionId = 2
}ESubDiscountQualifierFields;

class CSubscriptionDiscountQualifier
{
public:

	unsigned int QualifierId;
	char* Name;
	unsigned int SubscriptionId;

	CSubscriptionDiscountQualifier()
	{
		QualifierId = 0;
		Name = NULL;
		SubscriptionId = 0;
	}

	~CSubscriptionDiscountQualifier()
	{
		if (Name)
			delete[] Name;
	}

	char* Enumerate(char* SDQBinary)
	{
		TNodeHeader *NodeHeader = (TNodeHeader*)SDQBinary;

		if(NodeHeader->magic != NodeMagicNum)
		{
			return NULL;
		}
		else
		{
			char* NodeEnd = SDQBinary + NodeHeader->datalength;
			SDQBinary += sizeof(TNodeHeader);

			while(SDQBinary < NodeEnd)
			{
				TDescriptorNode *DNode = (TDescriptorNode*)SDQBinary;
				SDQBinary += sizeof(TDescriptorNode);

				switch (DNode->type)
				{
					case eSDQName:
						this->Name = new char[DNode->datalength];
						memcpy(this->Name, SDQBinary, DNode->datalength);
						SDQBinary += DNode->datalength;
						break;

					case eSDQSubscriptionId:
						this->SubscriptionId = *(unsigned int*)SDQBinary;
						SDQBinary += DNode->datalength;
						break;

					default:
						SDQBinary += DNode->datalength;
						break;
				}
			}

			return (SDQBinary + NodeHeader->nullpadding);

		}
	}
};
