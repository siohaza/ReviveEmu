#pragma once

#include "CSubscriptionDiscountQualifier.h"

typedef enum
{
	eSDRName = 1,
	eSDRDiscountInCents = 2,
	eSDRDiscountQualifiers = 3
}ESubDiscountFields;

class CSubscriptionDiscountRecord
{
public:

	unsigned int DiscountId;
	char* Name;
	unsigned int DiscountInCents;
	std::vector<CSubscriptionDiscountQualifier*> DiscountQualifiers;

	CSubscriptionDiscountRecord()
	{
	}

	~CSubscriptionDiscountRecord()
	{
	}

	char* Enumerate(char* SDRBinary)
	{
		TNodeHeader *NodeHeader = (TNodeHeader*)SDRBinary;
		if(NodeHeader->magic != NodeMagicNum)
		{
			return NULL;
		}
		else
		{
			char* NodeEnd = SDRBinary + NodeHeader->datalength;
			SDRBinary += sizeof(TNodeHeader);

			while(SDRBinary < NodeEnd)
			{
				TDescriptorNode *DNode = (TDescriptorNode*)SDRBinary;
				SDRBinary += sizeof(TDescriptorNode);

				switch (DNode->type)
				{
					case eSDRName:
						this->Name = new char[DNode->datalength];
						memcpy(this->Name, SDRBinary, DNode->datalength);
						SDRBinary += DNode->datalength;
						break;

					case eSDRDiscountInCents:
						this->DiscountInCents = *(unsigned int*)SDRBinary;
						SDRBinary += DNode->datalength;
						break;

					case eSDRDiscountQualifiers:
						{
							TNodeHeader *SDQNodeHeader = (TNodeHeader*)SDRBinary;
							if(SDQNodeHeader->magic == NodeMagicNum)
							{
								char* SDQBinary = SDRBinary;
								char* SDQNodeEnd = SDQBinary + SDQNodeHeader->datalength;
								SDQBinary += sizeof(TNodeHeader);

								while(SDQBinary < SDQNodeEnd)
								{
									CSubscriptionDiscountQualifier* newSDQ = new CSubscriptionDiscountQualifier();
									TDescriptorNode* SDQDNode = (TDescriptorNode*)SDQBinary;
									newSDQ->QualifierId = SDQDNode->type;
									SDQBinary += sizeof(TDescriptorNode);
									SDQBinary = newSDQ->Enumerate(SDQBinary);
									DiscountQualifiers.push_back(newSDQ);
								}
							}

							SDRBinary += DNode->datalength;
							break;
						}

					default:
						SDRBinary += DNode->datalength;
						break;
				}
			}
			return (SDRBinary + NodeHeader->nullpadding);
		}
	}
};
