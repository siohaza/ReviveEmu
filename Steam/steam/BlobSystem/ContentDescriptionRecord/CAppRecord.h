#pragma once

#include "CAppLaunchOptionRecord.h"
#include "CAppVersionRecord.h"
#include "CAppFilesystemRecord.h"
#include "CAppIconRecord.h"

typedef enum
{
	eAppAppId = 1,
	eAppName = 2,
	eAppInstallDirName = 3,
	eAppMinCacheFileSizeMB = 4,
	eAppMaxCacheFileSizeMB = 5,
	eAppLaunchOptionsRecord = 6,
	eAppAppIconsRecord = 7,
	eAppOnFirstLaunch = 8,
	eAppIsBandwidthGreedy = 9,
	eAppVersionsRecord = 10,
	eAppCurrentVersionId = 11,
	eAppFilesystemRecords = 12,
	eAppTrickleVersionId = 13,
	eAppUserDefinedRecords = 14,
	eAppBetaVersionPassword = 15,
	eAppBetaVersionId = 16,
	eAppLegacyInstallDirName = 17,
	eAppSkipMFPOverwrite = 18,
	eAppUseFilesystemDvr = 19,
	eAppManifestOnlyApp = 20,
	eAppAppOfManifestOnlyCache = 21,
}EApplicationFields;

class CAppRecord
{
public:

	unsigned int AppId;
	char* Name;
	char* InstallDirName;
	unsigned int MinCacheFileSizeMB;
	unsigned int MaxCacheFileSizeMB;
	std::vector<CAppLaunchOptionRecord*> LaunchOptionsRecord;
	std::vector<CAppIconRecord*> IconsRecord;
	int OnFirstLaunch;
	bool IsBandwidthGreedy;
	std::vector<CAppVersionRecord*> VersionsRecord;
	unsigned int CurrentVersionId;
	std::vector<CAppFilesystemRecord*> FilesystemsRecord;
	int TrickleVersionId;
	std::map<char*, char*> UserDefinedRecords;
	char* BetaVersionPassword;
	int BetaVersionId;
	char* LegacyInstallDirName;
	bool SkipMFPOverwrite;
	bool UseFilesystemDvr;
	bool ManifestOnlyApp;
	unsigned int AppOfManifestOnlyCache;

	CAppRecord()
	{
	}

	~CAppRecord()
	{
	}

	char* Enumerate(char* AppRBinary)
	{
		TNodeHeader *NodeHeader = (TNodeHeader*)AppRBinary;
		if(NodeHeader->magic != NodeMagicNum)
		{
			return NULL;
		}
		else
		{
			char* NodeEnd = AppRBinary + NodeHeader->datalength;
			AppRBinary += sizeof(TNodeHeader);

			while(AppRBinary < NodeEnd)
			{
				TDescriptorNode *DNode = (TDescriptorNode*)AppRBinary;
				AppRBinary += sizeof(TDescriptorNode);

				switch (DNode->type)
				{
					case eAppAppId:
						this->AppId = *(unsigned int*)AppRBinary;
						AppRBinary += DNode->datalength;
						break;

					case eAppName:
						this->Name = new char[DNode->datalength];
						memcpy(this->Name, AppRBinary, DNode->datalength);
						AppRBinary += DNode->datalength;
						break;

					case eAppInstallDirName:
						this->InstallDirName = new char[DNode->datalength];
						memcpy(this->InstallDirName, AppRBinary, DNode->datalength);
						AppRBinary += DNode->datalength;
						break;

					case eAppMinCacheFileSizeMB:
						this->MinCacheFileSizeMB = *(unsigned int*)AppRBinary;
						AppRBinary += DNode->datalength;
						break;

					case eAppMaxCacheFileSizeMB:
						this->MaxCacheFileSizeMB = *(unsigned int*)AppRBinary;
						AppRBinary += DNode->datalength;
						break;

					case eAppLaunchOptionsRecord:
						{
							TNodeHeader *LONodeHeader = (TNodeHeader*)AppRBinary;

							if(LONodeHeader->magic == NodeMagicNum)
							{

								char* LOBinary = AppRBinary;
								char* LONodeEnd = LOBinary + LONodeHeader->datalength;
								LOBinary += sizeof(TNodeHeader);

								while(LOBinary < LONodeEnd)
								{
									LOBinary += sizeof(TDescriptorNode);
									CAppLaunchOptionRecord* newLO = new CAppLaunchOptionRecord();
									LOBinary = newLO->Enumerate(LOBinary);
									LaunchOptionsRecord.push_back(newLO);
								}
							}

							AppRBinary += DNode->datalength;
							break;
						}

					case eAppAppIconsRecord:
						AppRBinary += DNode->datalength;
						break;

					case eAppOnFirstLaunch:
						this->OnFirstLaunch = *(int*)AppRBinary;
						AppRBinary += DNode->datalength;
						break;

					case eAppIsBandwidthGreedy:
						this->IsBandwidthGreedy = *(bool*)AppRBinary;
						AppRBinary += DNode->datalength;
						break;

					case eAppVersionsRecord:
						{
							TNodeHeader *VRNodeHeader = (TNodeHeader*)AppRBinary;

							if(VRNodeHeader->magic == NodeMagicNum)
							{
								char* VRBinary = AppRBinary;
								char* VRNodeEnd = VRBinary + VRNodeHeader->datalength;
								VRBinary += sizeof(TNodeHeader);

								while(VRBinary < VRNodeEnd)
								{
									VRBinary += sizeof(TDescriptorNode);
									CAppVersionRecord* newVR = new CAppVersionRecord();
									VRBinary = newVR->Enumerate(VRBinary);
									VersionsRecord.push_back(newVR);
								}
							}

							AppRBinary += DNode->datalength;
							break;
						}

					case eAppCurrentVersionId:
						this->CurrentVersionId = *(unsigned int*)AppRBinary;
						AppRBinary += DNode->datalength;
						break;

					case eAppFilesystemRecords:
						{
							TNodeHeader *FSRNodeHeader = (TNodeHeader*)AppRBinary;

							if(FSRNodeHeader->magic == NodeMagicNum)
							{
								char* FSRBinary = AppRBinary;
								char* FSRNodeEnd = FSRBinary + FSRNodeHeader->datalength;
								FSRBinary += sizeof(TNodeHeader);

								while(FSRBinary < FSRNodeEnd)
								{
									FSRBinary += sizeof(TDescriptorNode);
									CAppFilesystemRecord* newFSR = new CAppFilesystemRecord();
									FSRBinary = newFSR->Enumerate(FSRBinary);
									FilesystemsRecord.push_back(newFSR);
								}
							}

							AppRBinary += DNode->datalength;
							break;
						}

					case eAppTrickleVersionId:
						this->TrickleVersionId = *(int*)AppRBinary;
						AppRBinary += DNode->datalength;
						break;

					case eAppUserDefinedRecords:
						{
							TNodeHeader *UDRNodeHeader = (TNodeHeader*)AppRBinary;

							if(UDRNodeHeader->magic == NodeMagicNum)
							{
								char* UDRBinary = AppRBinary;
								char* UDRNodeEnd = UDRBinary + UDRNodeHeader->datalength;
								UDRBinary += sizeof(TNodeHeader);

								while(UDRBinary < UDRNodeEnd)
								{
									TNode *UDRNode = (TNode*)UDRBinary;
									UDRBinary += sizeof(TNode);
									char* szKeyName = new char[UDRNode->descriptorlength + 1];
									memset(szKeyName, 0, UDRNode->descriptorlength + 1);
									memcpy(szKeyName, UDRBinary, UDRNode->descriptorlength);
									UDRBinary += UDRNode->descriptorlength;
									char* szValue = new char[UDRNode->datalength];
									memcpy(szValue, UDRBinary, UDRNode->datalength);
									UDRBinary += UDRNode->datalength;
									UserDefinedRecords[szKeyName] = szValue;
								}
							}

							AppRBinary += DNode->datalength;
							break;
						}

					case eAppBetaVersionPassword:
						this->BetaVersionPassword = new char[DNode->datalength];
						memcpy(this->BetaVersionPassword, AppRBinary, DNode->datalength);
						AppRBinary += DNode->datalength;
						break;

					case eAppBetaVersionId:
						this->BetaVersionId = *(int*)AppRBinary;
						AppRBinary += DNode->datalength;
						break;

					case eAppLegacyInstallDirName:
						this->LegacyInstallDirName = new char[DNode->datalength];
						memcpy(this->LegacyInstallDirName, AppRBinary, DNode->datalength);
						AppRBinary += DNode->datalength;
						break;

					case eAppSkipMFPOverwrite:
						this->SkipMFPOverwrite = *(bool*)AppRBinary;
						AppRBinary += DNode->datalength;
						break;

					case eAppUseFilesystemDvr:
						this->UseFilesystemDvr = *(bool*)AppRBinary;
						AppRBinary += DNode->datalength;
						break;

					case eAppManifestOnlyApp:
						this->ManifestOnlyApp = *(bool*)AppRBinary;
						AppRBinary += DNode->datalength;
						break;

					case eAppAppOfManifestOnlyCache:
						this->AppOfManifestOnlyCache = *(unsigned int*)AppRBinary;
						AppRBinary += DNode->datalength;
						break;

					default:
						AppRBinary += DNode->datalength;
						break;
				}
			}
			return (AppRBinary + NodeHeader->nullpadding);
		}
	}
};
