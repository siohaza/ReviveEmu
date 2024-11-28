#include "ContentDescriptionRecord\CAppRecord.h"
#include "ContentDescriptionRecord\CSubscriptionRecord.h"
#include "zlib/zlib.h"

#pragma once

typedef enum
{
	eCRDVersionNumber,
	eCRDApplicationsRecord,
	eCRDSubscriptionsRecord,
	eCRDLastChangedExistingAppOrSubscriptionTime,
	eCRDIndexAppIdToSubscriptionIdsRecord,
	eCRDAllAppsPublicKeysRecord,
	eCRDAllAppsEncryptedPrivateKeysRecord
}ECDRType;

class CContentDescriptionRecord
{

public:

	unsigned short VersionNumber;
	std::vector<CAppRecord*> ApplicationRecords;
	std::vector<CSubscriptionRecord*> SubscriptionsRecord;
	std::map<unsigned int, char*> AllAppsPublicKeysRecord;

	CContentDescriptionRecord(char* CDRBinary)
	{
		char* CDRData;
		char* NodeEnd; 

		TNodeHeader *NodeHeader = (TNodeHeader*)CDRBinary;


		if(NodeHeader->magic != NodeMagicNum)
		{
			TNodeHeaderCompressed *NodeHeaderCompressed = (TNodeHeaderCompressed*)CDRBinary;

			if(NodeHeaderCompressed->magic == NodeMagicNumCompressed)
			{

				WORD header=*(WORD*)CDRBinary;
				DWORD compressedSize=*(DWORD*)(CDRBinary+0x02);
				DWORD uncompressedSize=*(DWORD*)(CDRBinary+0x0A);
				WORD unknown2=*(WORD*)(CDRBinary+0x12);
				char * zData=CDRBinary+0x14;
				char * zbuffer= new char[(DWORD)uncompressedSize];
   
				int result=uncompress((unsigned char*)zbuffer,&uncompressedSize,(unsigned char*)zData,(DWORD)compressedSize);
			
				CDRData = zbuffer;
				NodeEnd = CDRData + NodeHeaderCompressed->datalength;
			}

		}
		else
		{
			CDRData = CDRBinary;
			NodeEnd = CDRData + NodeHeader->datalength;
		}
			
		CDRData += sizeof(TNodeHeader);
		while(CDRData < NodeEnd)
		{

			TDescriptorNode *DNode = (TDescriptorNode*)CDRData;
			CDRData += sizeof(TDescriptorNode);

			switch (DNode->type)
			{
				case eCRDVersionNumber:
					{
						VersionNumber = *(unsigned short*)CDRData;
						CDRData += DNode->datalength;
						break;
					}

				case eCRDApplicationsRecord:
					{
						TNodeHeader *AppNodeHeader = (TNodeHeader*)CDRData;
						if(AppNodeHeader->magic == NodeMagicNum)
						{
							char* AppRBinary = CDRData;
							char* AppNodeEnd = AppRBinary + AppNodeHeader->datalength;
							AppRBinary += sizeof(TNodeHeader);

							while(AppRBinary < AppNodeEnd)
							{
								AppRBinary += sizeof(TDescriptorNode);
								CAppRecord* newApp = new CAppRecord();
								AppRBinary = newApp->Enumerate(AppRBinary);
								ApplicationRecords.push_back(newApp);
							}
						}
						CDRData += DNode->datalength;
						break;
					}

				case eCRDSubscriptionsRecord :
					{
						TNodeHeader *SubNodeHeader = (TNodeHeader*)CDRData;
						if(SubNodeHeader->magic == NodeMagicNum)
						{
							char* SubRBinary = CDRData;
							char* SubNodeEnd = SubRBinary + SubNodeHeader->datalength;
							SubRBinary += sizeof(TNodeHeader);

							while(SubRBinary < SubNodeEnd)
							{
								SubRBinary += sizeof(TDescriptorNode);
								CSubscriptionRecord* newSub = new CSubscriptionRecord();
								SubRBinary = newSub->Enumerate(SubRBinary);
								SubscriptionsRecord.push_back(newSub);
							}
						}
						CDRData += DNode->datalength;
						break;
					}

				case eCRDLastChangedExistingAppOrSubscriptionTime:
					CDRData += DNode->datalength;
					break;

				case eCRDIndexAppIdToSubscriptionIdsRecord:
					CDRData += DNode->datalength;
					break;

				case eCRDAllAppsPublicKeysRecord:
					{
						TNodeHeader *APKRNodeHeader = (TNodeHeader*)CDRData;
						if(APKRNodeHeader->magic == NodeMagicNum)
						{
							char* APKRBinary = CDRData;
							char* APKRNodeEnd = APKRBinary + APKRNodeHeader->datalength;
							APKRBinary += sizeof(TNodeHeader);

							while(APKRBinary < APKRNodeEnd)
							{
								TDescriptorNode *APKRDNode = (TDescriptorNode*)APKRBinary;
								APKRBinary += sizeof(TDescriptorNode);
								unsigned int uAppId = APKRDNode->type;
								char* szKeyData = new char[APKRDNode->datalength];
								memcpy(szKeyData, APKRBinary, APKRDNode->datalength);
								APKRBinary += APKRDNode->datalength;
								AllAppsPublicKeysRecord[uAppId] = szKeyData;
							}
						}
						CDRData += DNode->datalength;
						break;
					}

				case eCRDAllAppsEncryptedPrivateKeysRecord:
					CDRData += DNode->datalength;
					break;

				default:
						CDRData += DNode->datalength;
						break;

			}
		}
	}

	~CContentDescriptionRecord()
	{
	}

};
