#pragma once

#include "CSubscriptionDiscountRecord.h"

typedef enum
{
	eSubSubscriptionId = 1,
	eSubName = 2,
	eSubBillingType = 3,
	eSubCostInCents = 4,
	eSubPeriodInMinutes = 5,
	eSubAppIds = 6,
	eSubRunAppId = 7,
	eSubOnSubscribeRunLaunchOptionIndex = 8,
	eSubRateLimitRecord = 9,
	eSubDiscounts = 10,
	eSubIsPreorder = 11,
	eSubRequiresShippingAddress = 12,
	eSubDomesticCostInCents = 13,
	eSubInternationalCostInCents = 14,
	eSubRequiredKeyType = 15,
	eSubIsCyberCafe = 16,
	eSubGameCode = 17,
	eSubGameCodeDescription = 18,
	eSubIsDisabled = 19,
	eSubRequiresCD = 20,
	eSubTerritoryCode = 21,
	eSubIsSteam3Subscription = 22,
	eSubExtendedInfoRecords = 23
}ESubscriptionFields;

typedef enum
{
	eSBTNoCost,
	eSBTBillOnceOnly,
	eSBTBillMonthly,
	eSBTProofOfPrepurchaseOnly,
	eSBTGuestPass,
	eSBTHardwarePromo
}ESubBillingType;

class CSubscriptionRecord
{
public:

	unsigned int SubscriptionId;
	char* Name;
	ESubBillingType BillingType;
	unsigned int CostInCents;
	int PeriodInMinutes;
	std::vector<int> AppIds;
	int RunAppId;
	int OnSubscribeRunLaunchOptionIndex;
	//CRateLimitRecord* RateLimitRecord;
	std::vector<CSubscriptionDiscountRecord*> Discounts;
	bool IsPreorder;
	bool RequiresShippingAddress;
	unsigned int DomesticCostInCents;
	unsigned int InternationalCostInCents;
	unsigned int RequiredKeyType;
	bool IsCyberCafe;
	int GameCode;
	char* GameCodeDescription;
	bool IsDisabled;
	bool RequiresCD;
	unsigned int TerritoryCode;
	bool IsSteam3Subscription;
	std::map<char*, char*> ExtendedInfoRecords;

	CSubscriptionRecord()
	{
		SubscriptionId = 0;
		Name = NULL;
		BillingType = eSBTNoCost;
		CostInCents = 0;
		PeriodInMinutes = 0;
		RunAppId = 0;
		OnSubscribeRunLaunchOptionIndex = 0;
		IsPreorder = false;
		RequiresShippingAddress = false;
		DomesticCostInCents = 0;
		InternationalCostInCents = 0;
		RequiredKeyType = 0;
		IsCyberCafe = false;
		GameCode = 0;
		GameCodeDescription = NULL;
		IsDisabled = false;
		RequiresCD = false;
		TerritoryCode = 0;
		IsSteam3Subscription = false;
	}

	~CSubscriptionRecord()
	{
		if (Name)
			delete[] Name;

		for (size_t i = 0; i < Discounts.size(); i++)
			delete Discounts[i];

		if (GameCodeDescription)
			delete[] GameCodeDescription;

		std::map<char*, char*>::iterator it;
		for (it = ExtendedInfoRecords.begin(); it != ExtendedInfoRecords.end(); it++)
		{
			delete[] it->first;
			delete[] it->second;
		}
	}

	const char* Enumerate(const char* SubRBinary)
	{
		TNodeHeader *NodeHeader = (TNodeHeader*)SubRBinary;
		if(NodeHeader->magic != NodeMagicNum)
		{
			return NULL;
		}
		else
		{
			const char* NodeEnd = SubRBinary + NodeHeader->datalength;
			SubRBinary += sizeof(TNodeHeader);

			while(SubRBinary < NodeEnd)
			{
				TDescriptorNode *DNode = (TDescriptorNode*)SubRBinary;
				SubRBinary += sizeof(TDescriptorNode);
				
				switch (DNode->type)
				{

					case eSubSubscriptionId:
						this->SubscriptionId = *(unsigned int*)SubRBinary;
						SubRBinary += DNode->datalength;
						break;

					case eSubName:
						this->Name = new char[DNode->datalength];
						memcpy(this->Name, SubRBinary, DNode->datalength);
						SubRBinary += DNode->datalength;
						break;

					case eSubBillingType:
						{
						short billingtype = *(unsigned short*)SubRBinary;
						this->BillingType = (ESubBillingType)billingtype;
						SubRBinary += DNode->datalength;
						break;
						}

					case eSubCostInCents:
						this->CostInCents = *(unsigned int*)SubRBinary;
						SubRBinary += DNode->datalength;
						break;

					case eSubPeriodInMinutes:
						this->PeriodInMinutes = *(int*)SubRBinary;
						SubRBinary += DNode->datalength;
						break;

					case eSubAppIds:
						SubRBinary += DNode->datalength;
						break;

					case eSubRunAppId:
						this->RunAppId = *(int*)SubRBinary;
						SubRBinary += DNode->datalength;
						break;

					case eSubOnSubscribeRunLaunchOptionIndex:
						this->OnSubscribeRunLaunchOptionIndex = *(int*)SubRBinary;
						SubRBinary += DNode->datalength;
						break;

					case eSubRateLimitRecord:
						SubRBinary += DNode->datalength;
						break;

					case eSubDiscounts:
						{
							TNodeHeader *SDNodeHeader = (TNodeHeader*)SubRBinary;

							if(SDNodeHeader->magic == NodeMagicNum)
							{
								const char* SDBinary = SubRBinary;
								const char* SDNodeEnd = SDBinary + SDNodeHeader->datalength;
								SDBinary += sizeof(TNodeHeader);

								while(SDBinary < SDNodeEnd)
								{
									CSubscriptionDiscountRecord* newSD = new CSubscriptionDiscountRecord();
									TDescriptorNode* SDDNode = (TDescriptorNode*)SDBinary;
									newSD->DiscountId = SDDNode->type;
									SDBinary += sizeof(TDescriptorNode);
									SDBinary = newSD->Enumerate(SDBinary);
									Discounts.push_back(newSD);
								}
							}

							SubRBinary += DNode->datalength;
							break;
						}

					case eSubIsPreorder:
						this->IsPreorder = *(bool*)SubRBinary;
						SubRBinary += DNode->datalength;
						break;

					case eSubRequiresShippingAddress:
						this->RequiresShippingAddress = *(bool*)SubRBinary;
						SubRBinary += DNode->datalength;
						break;

					case eSubDomesticCostInCents:
						this->DomesticCostInCents = *(unsigned int*)SubRBinary;
						SubRBinary += DNode->datalength;
						break;

					case eSubInternationalCostInCents:
						this->InternationalCostInCents = *(unsigned int*)SubRBinary;
						SubRBinary += DNode->datalength;
						break;

					case eSubRequiredKeyType:
						this->RequiredKeyType = *(unsigned int*)SubRBinary;
						SubRBinary += DNode->datalength;
						break;

					case eSubIsCyberCafe:
						this->IsCyberCafe = *(bool*)SubRBinary;
						SubRBinary += DNode->datalength;
						break;

					case eSubGameCode:
						this->GameCode = *(int*)SubRBinary;
						SubRBinary += DNode->datalength;
						break;

					case eSubGameCodeDescription:
						this->GameCodeDescription = new char[DNode->datalength];
						memcpy(this->GameCodeDescription, SubRBinary, DNode->datalength);
						SubRBinary += DNode->datalength;
						break;

					case eSubIsDisabled:
						this->IsDisabled = *(bool*)SubRBinary;
						SubRBinary += DNode->datalength;
						break;

					case eSubRequiresCD:
						this->RequiresCD = *(bool*)SubRBinary;
						SubRBinary += DNode->datalength;
						break;

					case eSubTerritoryCode:
						this->TerritoryCode = *(unsigned int*)SubRBinary;
						SubRBinary += DNode->datalength;
						break;

					case eSubIsSteam3Subscription:
						this->IsSteam3Subscription = *(bool*)SubRBinary;
						SubRBinary += DNode->datalength;
						break;

					case eSubExtendedInfoRecords:
						{
							TNodeHeader *EIRNodeHeader = (TNodeHeader*)SubRBinary;

							if(EIRNodeHeader->magic == NodeMagicNum)
							{
								const char* EIRBinary = SubRBinary;
								const char* EIRNodeEnd = EIRBinary + EIRNodeHeader->datalength;
								EIRBinary += sizeof(TNodeHeader);

								while(EIRBinary < EIRNodeEnd)
								{
									TNode *EIRNode = (TNode*)EIRBinary;
									EIRBinary += sizeof(TNode);
									char* szKeyName = new char[EIRNode->descriptorlength + 1];
									memset(szKeyName, 0, EIRNode->descriptorlength + 1);
									memcpy(szKeyName, EIRBinary, EIRNode->descriptorlength);
									EIRBinary += EIRNode->descriptorlength;
									char* szValue = new char[EIRNode->datalength];
									memcpy(szValue, EIRBinary, EIRNode->datalength);
									EIRBinary += EIRNode->datalength;
									ExtendedInfoRecords[szKeyName] = szValue;
								}
							}

							SubRBinary += DNode->datalength;
							break;
						}

					default:
						SubRBinary += DNode->datalength;
						break;
				}
			}
			return (SubRBinary + NodeHeader->nullpadding);
		}
	}
};
