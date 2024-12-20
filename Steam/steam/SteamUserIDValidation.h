#pragma once

extern CLogFile* Logger;
extern BOOL bLogging;
extern BOOL bLogUserId;
extern BOOL bSteamDll;
extern BOOL bIsEnginePatched;
extern BOOL bSteamClient;
extern bool bAllowNonRev;
extern char szOrigSteamDll[MAX_PATH];

enum ERevClientType
{
	eClientRev = 0,
	eClientLegit,
	eClientUnknown
};

struct TRevUserValidationHandle
{
	ERevClientType ClientType;
	unsigned int ClientIP;
	unsigned int ClientLocalIP;
	SteamUserIDTicketValidationHandle_t LegitHandle;
	ESteamError ReturnCode;
};

std::vector<TRevUserValidationHandle *> RevUserValidations;

typedef ESteamError (STEAM_CALL *SteamInitializeUserIDTicketValidatorCall)(const char*, const char*, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int); 
typedef ESteamError (STEAM_CALL *SteamStartValidatingUserIDTicketCall)(void*, unsigned int, unsigned int, SteamUserIDTicketValidationHandle_t*);
typedef ESteamError (STEAM_CALL *SteamProcessOngoingUserIDTicketValidationCall)(SteamUserIDTicketValidationHandle_t Handle,
													  TSteamGlobalUserID*,
													  unsigned int*,
													  unsigned char*,
													  size_t,
													  size_t*);

STEAM_API ESteamError STEAM_CALL SteamGetEncryptedUserIDTicket(const void *pEncryptionKeyReceivedFromAppServer, unsigned int uEncryptionKeyLength, void *pOutputBuffer, unsigned int uSizeOfOutputBuffer, unsigned int *pReceiveSizeOfEncryptedTicket, TSteamError *pError)
{
	if (bLogging && bLogUserId) 
	{
		Logger->Write("SteamGetEncryptedUserIDTicket:\n");
		Logger->Write("\tKey Address: 0x%X\n", pEncryptionKeyReceivedFromAppServer);
		Logger->Write("\tKey Length: %u\n", uEncryptionKeyLength);
		Logger->Write("\tOutput Address: 0x%X\n", pOutputBuffer);
		Logger->Write("\tOutput Size: %u\n", uSizeOfOutputBuffer);
		Logger->Write("\tTicket Size Address: 0x%X\n", pReceiveSizeOfEncryptedTicket);
		Logger->Write("\tError Address: 0x%X\n", pError);
	}
	if (bLogging && bLogUserId) Logger->Write("\tSerial Number: %u\n", g_dwClientId);
	
	struct sRevTicket sGetRevTicket;
	sGetRevTicket.Signature = REVTICKET_SIGNATURE;
	sGetRevTicket.Version = REVTICKET_VERSION;
	sGetRevTicket.UserID = g_dwClientId;
	sGetRevTicket.LocalIP = 0; // TODO: Maybe set this?
	memcpy(pOutputBuffer, &sGetRevTicket, sizeof(sRevTicket));
	*pReceiveSizeOfEncryptedTicket = sizeof(sRevTicket);

	SteamClearError(pError);
	return eSteamErrorNone;
}


STEAM_API ESteamError STEAM_CALL SteamInitializeUserIDTicketValidator(const char * pszOptionalPublicEncryptionKeyFilename, const char *	pszOptionalPrivateDecryptionKeyFilename, unsigned int ClientClockSkewToleranceInSeconds, unsigned int ServerClockSkewToleranceInSeconds, unsigned int MaxNumLoginsWithinClientClockSkewTolerancePerClient, unsigned int	HintPeakSimultaneousValidations, unsigned int AbortValidationAfterStallingForNProcessSteps)
{
// #ifdef DEBUG
	if (bLogging && bLogUserId) Logger->Write("SteamInitializeUserIDTicketValidator\n");
// #endif
// 
	//if (!bIsEnginePatched && !bSteamClient) PatchEngine();

	if (bSteamDll)
	{
		ESteamError retval = eSteamErrorNone;
		SteamInitializeUserIDTicketValidatorCall CallSteamInitializeUserIDTicketValidator;
		CallSteamInitializeUserIDTicketValidator = (SteamInitializeUserIDTicketValidatorCall) GetProcAddress(GetModuleHandleA(szOrigSteamDll), "SteamInitializeUserIDTicketValidator");
		retval = CallSteamInitializeUserIDTicketValidator(pszOptionalPublicEncryptionKeyFilename, pszOptionalPrivateDecryptionKeyFilename, ClientClockSkewToleranceInSeconds, ServerClockSkewToleranceInSeconds, MaxNumLoginsWithinClientClockSkewTolerancePerClient, HintPeakSimultaneousValidations, AbortValidationAfterStallingForNProcessSteps);
		if (bLogging && bLogUserId) Logger->Write("\t %u\n", (int)retval);
		return retval;
	}

	return eSteamErrorNone;
}

STEAM_API ESteamError STEAM_CALL SteamShutdownUserIDTicketValidator()
{
// #ifdef DEBUG
	if (bLogging && bLogUserId) Logger->Write("SteamShutdownUserIDTicketValidator\n");
// #endif

	for (TRevUserValidationHandle* hRevHandle : RevUserValidations)
	{
		delete hRevHandle;
	}
	RevUserValidations.clear();

	if (bSteamDll)
	{
		ESteamError retval = eSteamErrorNone;
		ESteamError (*fptr)();
		*(void **)(&fptr) = GetProcAddress(GetModuleHandleA(szOrigSteamDll), "SteamShutdownUserIDTicketValidator");
		retval = (*fptr)();
		if (bLogging && bLogUserId) Logger->Write("\t %u\n", (int)retval);
		return retval;
	}

	return eSteamErrorNone;
}

STEAM_API const unsigned char* STEAM_CALL SteamGetEncryptionKeyToSendToNewClient(unsigned int * pReceiveSizeOfEncryptionKey)
{
// #ifdef DEBUG
	if (bLogging && bLogUserId) Logger->Write("SteamGetEncryptionKeyToSendToNewClient (0x%X)\n", pReceiveSizeOfEncryptionKey);
// #endif

	if (bSteamDll)
	{
		const unsigned char* retval;
		const unsigned char* (*fptr)(unsigned int*);
		*(void **)(&fptr) = GetProcAddress(GetModuleHandleA(szOrigSteamDll), "SteamGetEncryptionKeyToSendToNewClient");
		retval = (*fptr)(pReceiveSizeOfEncryptionKey);
		if (bLogging && bLogUserId) Logger->Write("\t 0x%08X\n", (int)retval);
		return retval;
	}

	*pReceiveSizeOfEncryptionKey = 160;
	return m_key;
}

STEAM_API ESteamError STEAM_CALL SteamStartValidatingUserIDTicket(void *pEncryptedUserIDTicketFromClient, unsigned int uSizeOfEncryptedUserIDTicketFromClient, unsigned int ObservedClientIPAddr, SteamUserIDTicketValidationHandle_t *pReceiveHandle)
{
// #ifdef DEBUG
	if (bLogging && bLogUserId) Logger->Write("SteamStartValidatingUserIDTicket (0x%X, %u, %u, 0x%X)\n", ObservedClientIPAddr, uSizeOfEncryptedUserIDTicketFromClient, ObservedClientIPAddr, pReceiveHandle);
	// #endif

	if (bSteamDll)
	{
		SteamStartValidatingUserIDTicketCall StartValidating;
		ESteamError retval = eSteamErrorNone;
		StartValidating = (SteamStartValidatingUserIDTicketCall) GetProcAddress(GetModuleHandleA(szOrigSteamDll), "SteamStartValidatingUserIDTicket");
		retval = StartValidating(pEncryptedUserIDTicketFromClient, uSizeOfEncryptedUserIDTicketFromClient, ObservedClientIPAddr, pReceiveHandle);
		if (bLogging && bLogUserId) Logger->Write("\t %u\n", (int)retval);

		if (retval == eSteamErrorNone || retval == eSteamErrorNotFinishedProcessing)
		{
			if (bLogging && bLogUserId) Logger->Write("\t Client using legitimate STEAM account.\n");

			TRevUserValidationHandle* hRevHandle = new TRevUserValidationHandle();
			hRevHandle->ClientType = eClientLegit;
			hRevHandle->LegitHandle = *pReceiveHandle;
			RevUserValidations.push_back(hRevHandle);

			*pReceiveHandle = hRevHandle;
			if (bLogging && bLogUserId) Logger->Write("\t Returned handle 0x%X\n", hRevHandle);
			return retval;
		}
	}

	if (uSizeOfEncryptedUserIDTicketFromClient < 8)
	{
		*pReceiveHandle = STEAM_INACTIVE_USERIDTICKET_VALIDATION_HANDLE;
		return eSteamErrorUnknown;
	}

	uint32_t uCheckTicket = *(uint32_t*)pEncryptedUserIDTicketFromClient;
	if (uCheckTicket == REVTICKET_SIGNATURE)
	{
		if (bLogging && bLogUserId) Logger->Write("\t Client using REVOLUTiON emulator.\n");

		const sRevTicket* pRevTicket = (sRevTicket*)pEncryptedUserIDTicketFromClient;

		TRevUserValidationHandle* hRevHandle = new TRevUserValidationHandle();
		hRevHandle->ClientType = eClientRev;

		if (pRevTicket->Version == REVTICKET_VERSION)
		{
			if (uSizeOfEncryptedUserIDTicketFromClient == sizeof(sRevTicket))
			{
				hRevHandle->ClientIP = pRevTicket->UserID;
				hRevHandle->ClientLocalIP = pRevTicket->LocalIP;
				hRevHandle->ReturnCode = eSteamErrorNone;
			}
			else
			{
				if (bLogging && bLogUserId) Logger->Write("\t Malformed REVOLUTiON auth ticket.\n");
				hRevHandle->ReturnCode = eSteamErrorCorruptEncryptedUserIDTicket;
			}
		}
		else
		{
			if (bLogging && bLogUserId) Logger->Write("\t REVOLUTiON auth ticket version %u not supported.\n", pRevTicket->Version);
			hRevHandle->ReturnCode = eSteamErrorInvalidUserIDTicket;
		}

		RevUserValidations.push_back(hRevHandle);

		*pReceiveHandle = hRevHandle;
		if (bLogging && bLogUserId) Logger->Write("\t Returned handle 0x%X\n", hRevHandle);
	}
	else
	{
		if (bLogging && bLogUserId) Logger->Write("\t Client not using REVOLUTiON emulator.\n");

		TRevUserValidationHandle* hRevHandle = new TRevUserValidationHandle();
		hRevHandle->ClientType = eClientUnknown;
		hRevHandle->ClientIP = ObservedClientIPAddr;
		hRevHandle->ClientLocalIP = 0;
		hRevHandle->ReturnCode = bAllowNonRev ? eSteamErrorNone : eSteamErrorInvalidUserIDTicket;
		RevUserValidations.push_back(hRevHandle);

		*pReceiveHandle = hRevHandle;
		if (bLogging && bLogUserId) Logger->Write("\t Returned handle 0x%X\n", hRevHandle);
	}

	return eSteamErrorNotFinishedProcessing;
}

STEAM_API ESteamError STEAM_CALL SteamStartValidatingNewValveCDKey(void *pEncryptedNewValveCDKeyFromClient, unsigned int uSizeOfEncryptedNewValveCDKeyFromClient, unsigned int ObservedClientIPAddr, struct sockaddr *pPrimaryValidateNewCDKeyServerSockAddr, struct sockaddr *pSecondaryValidateNewCDKeyServerSockAddr, SteamUserIDTicketValidationHandle_t *pReceiveHandle)
{
// #ifdef DEBUG
	if (bLogging && bLogUserId) Logger->Write("SteamStartValidatingNewValveCDKey\n");
// #endif

	if (bSteamDll)
	{
		ESteamError retval = eSteamErrorNone;
		ESteamError (*fptr)(void*, unsigned int, unsigned int, struct sockaddr*, struct sockaddr*, SteamUserIDTicketValidationHandle_t*);
		*(void **)(&fptr) = GetProcAddress(GetModuleHandleA(szOrigSteamDll), "SteamStartValidatingNewValveCDKey");
		retval = (*fptr)(pEncryptedNewValveCDKeyFromClient, uSizeOfEncryptedNewValveCDKeyFromClient, ObservedClientIPAddr, pPrimaryValidateNewCDKeyServerSockAddr, pSecondaryValidateNewCDKeyServerSockAddr, pReceiveHandle);
		if (bLogging && bLogUserId) Logger->Write("\t 0x%08X\n", (int)retval);
		
		if (retval == eSteamErrorNone || retval == eSteamErrorNotFinishedProcessing)
		{
			if (bLogging && bLogUserId) Logger->Write("\t Client using legitimate STEAM account.\n");

			TRevUserValidationHandle* hRevHandle = new TRevUserValidationHandle();
			hRevHandle->ClientType = eClientLegit;
			hRevHandle->LegitHandle = *pReceiveHandle;
			RevUserValidations.push_back(hRevHandle);

			*pReceiveHandle = hRevHandle;
			return retval;
		}
	}

	// TODO
	*pReceiveHandle = STEAM_INACTIVE_USERIDTICKET_VALIDATION_HANDLE;
	return eSteamErrorUnknown;
}

STEAM_API ESteamError STEAM_CALL SteamProcessOngoingUserIDTicketValidation(SteamUserIDTicketValidationHandle_t Handle, TSteamGlobalUserID *pReceiveValidSteamGlobalUserID, unsigned int *pReceiveClientLocalIPAddr, unsigned char *pOptionalReceiveProofOfAuthenticationToken, size_t SizeOfOptionalAreaToReceiveProofOfAuthenticationToken, size_t *pOptionalReceiveSizeOfProofOfAuthenticationToken)
{
// #ifdef DEBUG
	if (bLogging && bLogUserId) Logger->Write("SteamProcessOngoingUserIDTicketValidation (0x%X)\n", Handle);
// #endif

	if (Handle == STEAM_INACTIVE_USERIDTICKET_VALIDATION_HANDLE)
		return eSteamErrorNothingToDo;

	TRevUserValidationHandle* hRevHandle = (TRevUserValidationHandle*)Handle;

	if (bSteamDll && hRevHandle->ClientType == eClientLegit)
	{
		ESteamError retval = eSteamErrorNone;
		ESteamError (*fptr)(SteamUserIDTicketValidationHandle_t, TSteamGlobalUserID*, unsigned int*, unsigned char*, size_t, size_t*);
		*(void **)(&fptr) = GetProcAddress(GetModuleHandleA(szOrigSteamDll), "SteamProcessOngoingUserIDTicketValidation");
		retval = (*fptr)(hRevHandle->LegitHandle, pReceiveValidSteamGlobalUserID, pReceiveClientLocalIPAddr, pOptionalReceiveProofOfAuthenticationToken, SizeOfOptionalAreaToReceiveProofOfAuthenticationToken, pOptionalReceiveSizeOfProofOfAuthenticationToken);
		if (bLogging && bLogUserId) Logger->Write("\t 0x%08X\n", (int)retval);
		return retval;
	}

	if (hRevHandle->ReturnCode != eSteamErrorNone)
		return hRevHandle->ReturnCode;

	if (bLogging && bLogUserId) Logger->Write("\t Received ID: %u -> Account ID: %u\n", hRevHandle->ClientIP, hRevHandle->ClientIP / 2);
	if (hRevHandle->ClientType == eClientRev)
	{
		pReceiveValidSteamGlobalUserID->m_SteamInstanceID = 0;
		pReceiveValidSteamGlobalUserID->Split.High32bits = 0;
		pReceiveValidSteamGlobalUserID->Split.Low32bits = hRevHandle->ClientIP / 2;
	}
	else
	{
		pReceiveValidSteamGlobalUserID->m_SteamInstanceID = 0;
		pReceiveValidSteamGlobalUserID->Split.High32bits = hRevHandle->ClientIP % 2;
		pReceiveValidSteamGlobalUserID->Split.Low32bits = hRevHandle->ClientIP / 2;
	}

	if (pReceiveClientLocalIPAddr)
		*pReceiveClientLocalIPAddr = hRevHandle->ClientLocalIP;

	if (pOptionalReceiveSizeOfProofOfAuthenticationToken)
		*pOptionalReceiveSizeOfProofOfAuthenticationToken = 0;

	return eSteamErrorNone;
}

STEAM_API void STEAM_CALL SteamAbortOngoingUserIDTicketValidation(SteamUserIDTicketValidationHandle_t Handle)
{
// #ifdef DEBUG
	if (bLogging && bLogUserId) Logger->Write("SteamAbortOngoingUserIDTicketValidation (0x%X)\n", Handle);
// #endif

	if (Handle == STEAM_INACTIVE_USERIDTICKET_VALIDATION_HANDLE)
		return;

	TRevUserValidationHandle* hRevHandle = (TRevUserValidationHandle*)Handle;

	if (bSteamDll && hRevHandle->ClientType == eClientLegit)
	{
		void (*fptr)(SteamUserIDTicketValidationHandle_t);
		*(void **)(&fptr) = GetProcAddress(GetModuleHandleA(szOrigSteamDll), "SteamAbortOngoingUserIDTicketValidation");
		(*fptr)(hRevHandle->LegitHandle);
		if (bLogging && bLogUserId) Logger->Write("\t returned.\n");
	}

	for (auto it = RevUserValidations.begin(); it != RevUserValidations.end(); it++)
	{
		if (hRevHandle == *it)
		{
			delete hRevHandle;
			RevUserValidations.erase(it);
			break;
		}
	}
}

STEAM_API ESteamError STEAM_CALL SteamOptionalCleanUpAfterClientHasDisconnected(unsigned int ObservedClientIPAddr, unsigned int ClientLocalIPAddr)
{
// #ifdef DEBUG
	if (bLogging && bLogUserId) Logger->Write("SteamOptionalCleanUpAfterClientHasDisconnected\n");
// #endif
	if (bSteamDll)
	{
		ESteamError retval = eSteamErrorNone;
		ESteamError (*fptr)(unsigned int, unsigned int);
		*(void **)(&fptr) = GetProcAddress(GetModuleHandleA(szOrigSteamDll), "SteamOptionalCleanUpAfterClientHasDisconnected");
		retval = (*fptr)(ObservedClientIPAddr, ClientLocalIPAddr);
		if (bLogging && bLogUserId) Logger->Write("\t %u\n", (int)retval);
		return retval;
	}
	return eSteamErrorNone;
}

void PatchEngine(void)
{
	if(HMODULE hGameEngine = GetModuleHandleA("engine.dll"))
	{
		char* pGameEngineImage = reinterpret_cast<char*>(hGameEngine);
		IMAGE_DOS_HEADER* pDOS_Header = reinterpret_cast<IMAGE_DOS_HEADER*>(pGameEngineImage);
		if(pDOS_Header->e_magic != IMAGE_DOS_SIGNATURE)
		{
			CloseHandle(hGameEngine);
			return;
		}

		IMAGE_NT_HEADERS* pNT_Header = reinterpret_cast<IMAGE_NT_HEADERS*>(pGameEngineImage + pDOS_Header->e_lfanew);
		if(pNT_Header->Signature != IMAGE_NT_SIGNATURE)
		{
			CloseHandle(hGameEngine);
			return;
		}

		IMAGE_SECTION_HEADER* pSection_Header = reinterpret_cast<IMAGE_SECTION_HEADER*>(pGameEngineImage + pDOS_Header->e_lfanew + sizeof(IMAGE_NT_HEADERS));
		char* szFirstSection = pGameEngineImage + pSection_Header->VirtualAddress - 0x1000;

		HANDLE hProcess = OpenProcess(PROCESS_VM_READ, TRUE, GetCurrentProcessId());
		void *vEngineDll = malloc(pSection_Header->SizeOfRawData);
		unsigned char* pEngineDll;
		pEngineDll = (unsigned char *) malloc (pSection_Header->SizeOfRawData);
		SIZE_T pEngineBytesRead = 0;
		if (ReadProcessMemory(hProcess, hGameEngine, vEngineDll, pSection_Header->SizeOfRawData, &pEngineBytesRead))
	{
		memcpy(pEngineDll, vEngineDll, pSection_Header->SizeOfRawData); 
		const unsigned char pSearchBytes[6] = { 0xF7, 0xC1, 0x00, 0x00, 0x00, 0xFF };
		const unsigned char pSearchBytes2[2] = { 0x39, 0x2D };
		unsigned int i = 0;
		unsigned char j;
		DWORD dwOldProtect = 0;
		const unsigned char pPatchBytes[6] = { 0x81, 0xFD, 0x01, 0x00, 0x00, 0x00 };
		SIZE_T pEngineBytesToWrite = 6;
		SIZE_T pEngineBytesWritten = 0;
		unsigned int saved;

Start1:
		while (i < pEngineBytesRead)
		{
			for (j = 0; j < 6; j++)
			{
				if (pEngineDll[i+j] != pSearchBytes[j])
				{
					i++;
					goto Start1;
				}
			}
			//if(bLogging) Logger->Write("Search pattern found at: 0x%08X (offset 0x%08X)\n", szFirstSection+i, i);
			saved = i;
			goto Next1;
		}
		//if(bLogging) Logger->Write("Search pattern not found\n");
		goto Fail1;

Next1:
		i = i - 180;

Start2:
		while (i < saved)
		{
			for (j = 0; j < 2; j++)
			{
				if (pEngineDll[i+j] != pSearchBytes2[j])
				{
					i++;
					goto Start2;
				}
			}
			//if (bLogging) Logger->Write("Needed instruction found at: 0x%08X (offset 0x%08X)\n", szFirstSection+i, i);
			saved = i;
			goto Next2;
		}
		//if(bLogging) Logger->Write("Search pattern not found\n");
		goto Fail1;

Next2:

		HANDLE k = szFirstSection+i;
		if (VirtualProtect(k, 6, PAGE_EXECUTE_READWRITE, &dwOldProtect))
		{
			memcpy(k, &pPatchBytes, 6);
			//if(bLogging) Logger->Write("Memory successfully modified.\n");
			VirtualProtect(k, 6, dwOldProtect, &dwOldProtect);
			bIsEnginePatched = TRUE;
		}
		//else
		//{
		//	if(bLogging) Logger->Write("Unable to change memory access. The error was 0x%08X\n", GetLastError());
		//}
	}

	//else { if(bLogging) Logger->Write("ReadProcessMemory failed with error 0x%08X\n", GetLastError()); }


Fail1:
	CloseHandle(hProcess);
	free(pEngineDll);
	free(vEngineDll);
	return;
	}

	else if(HMODULE hGameEngine = GetModuleHandleA("swds.dll"))
	{
		char* pGameEngineImage = reinterpret_cast<char*>(hGameEngine);
		IMAGE_DOS_HEADER* pDOS_Header = reinterpret_cast<IMAGE_DOS_HEADER*>(pGameEngineImage);
		if(pDOS_Header->e_magic != IMAGE_DOS_SIGNATURE)
		{
			CloseHandle(hGameEngine);
			return;
		}

		IMAGE_NT_HEADERS* pNT_Header = reinterpret_cast<IMAGE_NT_HEADERS*>(pGameEngineImage + pDOS_Header->e_lfanew);
		if(pNT_Header->Signature != IMAGE_NT_SIGNATURE)
		{
			CloseHandle(hGameEngine);
			return;
		}

		IMAGE_SECTION_HEADER* pSection_Header = reinterpret_cast<IMAGE_SECTION_HEADER*>(pGameEngineImage + pDOS_Header->e_lfanew + sizeof(IMAGE_NT_HEADERS));
		char* szFirstSection = pGameEngineImage + pSection_Header->VirtualAddress - 0x1000;

		HANDLE hProcess = OpenProcess(PROCESS_VM_READ, TRUE, GetCurrentProcessId());
		void *vEngineDll = malloc(pSection_Header->SizeOfRawData);
		unsigned char* pEngineDll;
		pEngineDll = (unsigned char *) malloc (pSection_Header->SizeOfRawData);
		SIZE_T pEngineBytesRead = 0;
		if (ReadProcessMemory(hProcess, hGameEngine, vEngineDll, pSection_Header->SizeOfRawData, &pEngineBytesRead))
	{
		memcpy(pEngineDll, vEngineDll, pSection_Header->SizeOfRawData); 
		const unsigned char pSearchBytes[6] = { 0x81, 0xE3, 0x00, 0x00, 0xF0, 0xFF };
		const unsigned char pSearchBytes2[1] = { 0xA1 };
		unsigned int i = 0;
		unsigned char j;
		DWORD dwOldProtect = 0;
		const unsigned char pPatchBytes[5] = { 0x33, 0xC0, 0x90, 0x90, 0x90 };
		SIZE_T pEngineBytesToWrite = 6;
		SIZE_T pEngineBytesWritten = 0;
		unsigned int saved;

BStart1:
		while (i < pEngineBytesRead)
		{
			for (j = 0; j < 6; j++)
			{
				if (pEngineDll[i+j] != pSearchBytes[j])
				{
					i++;
					goto BStart1;
				}
			}
			//if(bLogging) Logger->Write("Search pattern found at: 0x%08X (offset 0x%08X)\n", szFirstSection+i, i);
			saved = i;
			goto BNext1;
		}
		//if(bLogging) Logger->Write("Search pattern not found\n");
		goto Fail2;

BNext1:
		i = i - 180;

BStart2:
		while (i < saved)
		{
				if (pEngineDll[i] != pSearchBytes2[0])
				{
					i++;
					goto BStart2;
				}
			//if (bLogging) Logger->Write("Needed instruction found at: 0x%08X (offset 0x%08X)\n", szFirstSection+i, i);
			saved = i;
			goto BNext2;
		}
		//if(bLogging) Logger->Write("Search pattern not found\n");
		goto Fail2;

BNext2:

		HANDLE k = szFirstSection+i;
		if (VirtualProtect(k, 5, PAGE_EXECUTE_READWRITE, &dwOldProtect))
		{
			memcpy(k, &pPatchBytes, 5);
			//if(bLogging) Logger->Write("Memory successfully modified.\n");
			VirtualProtect(k, 5, dwOldProtect, &dwOldProtect);
			bIsEnginePatched = TRUE;
		}
		//else
		//{
		//	if(bLogging) Logger->Write("Unable to change memory access. The error was 0x%08X\n", GetLastError());
		//}
	}

	//else { if(bLogging) Logger->Write("ReadProcessMemory failed with error 0x%08X\n", GetLastError()); }


Fail2:
	CloseHandle(hProcess);
	free(pEngineDll);
	free(vEngineDll);
	return;
	}

	else if(HMODULE hGameEngine = GetModuleHandleA("hl.exe"))
	{
		char* pGameEngineImage = reinterpret_cast<char*>(hGameEngine);
		IMAGE_DOS_HEADER* pDOS_Header = reinterpret_cast<IMAGE_DOS_HEADER*>(pGameEngineImage);
		if(pDOS_Header->e_magic != IMAGE_DOS_SIGNATURE)
		{
			CloseHandle(hGameEngine);
			return;
		}

		IMAGE_NT_HEADERS* pNT_Header = reinterpret_cast<IMAGE_NT_HEADERS*>(pGameEngineImage + pDOS_Header->e_lfanew);
		if(pNT_Header->Signature != IMAGE_NT_SIGNATURE)
		{
			CloseHandle(hGameEngine);
			return;
		}

		IMAGE_SECTION_HEADER* pSection_Header = reinterpret_cast<IMAGE_SECTION_HEADER*>(pGameEngineImage + pDOS_Header->e_lfanew + sizeof(IMAGE_NT_HEADERS));
		char* szFirstSection = pGameEngineImage + pSection_Header->VirtualAddress - 0x1000;

		HANDLE hProcess = OpenProcess(PROCESS_VM_READ, TRUE, GetCurrentProcessId());
		void *vEngineDll = malloc(0x2000000);
		unsigned char* pEngineDll;
		pEngineDll = (unsigned char *) malloc (0x2000000);
		SIZE_T pEngineBytesRead = 0;
		if (ReadProcessMemory(hProcess, hGameEngine, vEngineDll, 0x2000000, &pEngineBytesRead))
	{
		memcpy(pEngineDll, vEngineDll, 0x2000000); 
		const unsigned char pSearchBytes[6] = { 0x81, 0xE7, 0x00, 0x00, 0xF0, 0xFF };
		const unsigned char pSearchBytes2[1] = { 0xA1 };
		unsigned int i = 0;
		unsigned char j;
		DWORD dwOldProtect = 0;
		const unsigned char pPatchBytes[5] = { 0x33, 0xC0, 0x90, 0x90, 0x90 };
		SIZE_T pEngineBytesToWrite = 6;
		SIZE_T pEngineBytesWritten = 0;
		unsigned int saved;

CStart1:
		while (i < pEngineBytesRead)
		{
			for (j = 0; j < 6; j++)
			{
				if (pEngineDll[i+j] != pSearchBytes[j])
				{
					i++;
					goto CStart1;
				}
			}
			//if(bLogging) Logger->Write("Search pattern found at: 0x%08X (offset 0x%08X)\n", szFirstSection+i, i);
			saved = i;
			goto CNext1;
		}
		//if(bLogging) Logger->Write("Search pattern not found\n");
		goto Fail3;

CNext1:
		i = i - 180;

CStart2:
		while (i < saved)
		{
				if (pEngineDll[i] != pSearchBytes2[0])
				{
					i++;
					goto CStart2;
				}
			//if (bLogging) Logger->Write("Needed instruction found at: 0x%08X (offset 0x%08X)\n", szFirstSection+i, i);
			saved = i;
			goto CNext2;
		}
		//if(bLogging) Logger->Write("Search pattern not found\n");
		goto Fail3;

CNext2:

		HANDLE k = szFirstSection+i;
		if (VirtualProtect(k, 5, PAGE_EXECUTE_READWRITE, &dwOldProtect))
		{
			memcpy(k, &pPatchBytes, 5);
			//if(bLogging) Logger->Write("Memory successfully modified.\n");
			VirtualProtect(k, 5, dwOldProtect, &dwOldProtect);
			bIsEnginePatched = TRUE;
		}
		//else
		//{
		//	if(bLogging) Logger->Write("Unable to change memory access. The error was 0x%08X\n", GetLastError());
		//}
	}

		//else { if(bLogging) Logger->Write("ReadProcessMemory failed with error 0x%08X. Bytes read: 0x%08X\n", GetLastError(), pEngineBytesRead); }


Fail3:
		CloseHandle(hProcess);
		free(pEngineDll);
		free(vEngineDll);
		return;
	}

	return;
}