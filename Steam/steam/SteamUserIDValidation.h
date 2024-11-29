#pragma once

extern CLogFile* Logger;
extern BOOL bLogging;
extern BOOL bLogUserId;
extern BOOL bSteamDll;
extern BOOL bIsEnginePatched;
extern BOOL bSteamClient;
extern bool bAllowNonRev;
extern char szOrigSteamDll[MAX_PATH];

unsigned int uClientIpAddr = 0;
unsigned int uSteamInstanceID = 1;
bool bLegitClient = false;
bool bRevClient = false;

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
		Logger->Write("\tKey Address: 0x%08X\n", pEncryptionKeyReceivedFromAppServer);
		Logger->Write("\tKey Length: %u\n", uEncryptionKeyLength);
		Logger->Write("\tOutput Address: 0x%08X\n", pOutputBuffer);
		Logger->Write("\tOutput Size: %u\n", uSizeOfOutputBuffer);
		Logger->Write("\tTicket Size: %u\n", *pReceiveSizeOfEncryptedTicket);
		Logger->Write("\tError Address: %u\n", pError);
	}
	DWORD uVolumeSerialNumber = 0;
	GetVolumeInformationA(NULL, NULL, NULL, &uVolumeSerialNumber, NULL, NULL, NULL, NULL);
	if (bLogging && bLogUserId) Logger->Write("--\n\tSerial Number: %u\n", uVolumeSerialNumber);
	
	struct sRevTicket sGetRevTicket;
	sGetRevTicket.uTicketID = 0xFFFF;
	sGetRevTicket.uAccountType = 0;
	sGetRevTicket.uAccountID = uVolumeSerialNumber;
	memcpy(pOutputBuffer, &sGetRevTicket, 10);
	*pReceiveSizeOfEncryptedTicket = 10;

	SteamClearError(pError);
	return eSteamErrorNone;
}


STEAM_API ESteamError STEAM_CALL SteamInitializeUserIDTicketValidator(const char * pszOptionalPublicEncryptionKeyFilename, const char *	pszOptionalPrivateDecryptionKeyFilename, unsigned int ClientClockSkewToleranceInSeconds, unsigned int ServerClockSkewToleranceInSeconds, unsigned int MaxNumLoginsWithinClientClockSkewTolerancePerClient, unsigned int	HintPeakSimultaneousValidations, unsigned int AbortValidationAfterStallingForNProcessSteps)
{
// #ifdef DEBUG
	if (bLogging && bLogUserId) Logger->Write("SteamInitializeUserIDTicketValidator\n");
// #endif
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
	if (bLogging && bLogUserId) Logger->Write("SteamGetEncryptionKeyToSendToNewClient (%u)\n", *pReceiveSizeOfEncryptionKey);
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
	if (bLogging && bLogUserId) Logger->Write("SteamStartValidatingUserIDTicket (%u, %u)\n", ObservedClientIPAddr, (int)*pReceiveHandle);
// #endif
	if (bSteamDll)
	{
		SteamStartValidatingUserIDTicketCall StartValidating;
		ESteamError retval = eSteamErrorNone;
		StartValidating = (SteamStartValidatingUserIDTicketCall) GetProcAddress(GetModuleHandleA(szOrigSteamDll), "SteamStartValidatingUserIDTicket");
		retval = StartValidating(pEncryptedUserIDTicketFromClient, uSizeOfEncryptedUserIDTicketFromClient, ObservedClientIPAddr, pReceiveHandle);
		if (bLogging && bLogUserId) Logger->Write("\t %u\n", (int)retval);

		if (retval == 23) 
		{
			bLegitClient = true;
			return retval;
		}
		if (retval == 0)
		{
			bLegitClient = true;
			if (bLogging && bLogUserId) Logger->Write("\t Client using legitimate STEAM account.\n");
			return retval;
		}
	}
	unsigned short int uCheckTicket;
	memcpy(&uCheckTicket, pEncryptedUserIDTicketFromClient, 2);
	if (uCheckTicket == 0xFFFF)
	{
		struct sRevTicket sGetRevTicket;
		memcpy(&sGetRevTicket, pEncryptedUserIDTicketFromClient, 10);
		uClientIpAddr = sGetRevTicket.uAccountID;
		uSteamInstanceID = 0;
		if (bLogging && bLogUserId) Logger->Write("\t Client using REVOLUTiON emulator.\n");
		bRevClient = true;
		bLegitClient = false;
	}
	else
	{
		uClientIpAddr = ObservedClientIPAddr;
		uSteamInstanceID = 1;
		if (bLogging && bLogUserId) Logger->Write("\t Client not using REVOLUTiON emulator.\n");
		bLegitClient = false;
		if (!bAllowNonRev) return eSteamErrorInvalidUserIDTicket;
	}
	return eSteamErrorNone;
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
		return retval;
	}
	return eSteamErrorNone;
}

STEAM_API ESteamError STEAM_CALL SteamProcessOngoingUserIDTicketValidation(SteamUserIDTicketValidationHandle_t Handle, TSteamGlobalUserID *pReceiveValidSteamGlobalUserID, unsigned int *pReceiveClientLocalIPAddr, unsigned char *pOptionalReceiveProofOfAuthenticationToken, size_t SizeOfOptionalAreaToReceiveProofOfAuthenticationToken, size_t *pOptionalReceiveSizeOfProofOfAuthenticationToken)
{
// #ifdef DEBUG
	if (bLogging && bLogUserId) Logger->Write("SteamProcessOngoingUserIDTicketValidation (%u)\n", (int)Handle);
// #endif
	if (bSteamDll && bLegitClient)
	{
		ESteamError retval = eSteamErrorNone;
		ESteamError (*fptr)(SteamUserIDTicketValidationHandle_t, TSteamGlobalUserID*, unsigned int*, unsigned char*, size_t, size_t*);
		*(void **)(&fptr) = GetProcAddress(GetModuleHandleA(szOrigSteamDll), "SteamProcessOngoingUserIDTicketValidation");
		retval = (*fptr)(Handle, pReceiveValidSteamGlobalUserID, pReceiveClientLocalIPAddr, pOptionalReceiveProofOfAuthenticationToken, SizeOfOptionalAreaToReceiveProofOfAuthenticationToken, pOptionalReceiveSizeOfProofOfAuthenticationToken);
		if (bLogging && bLogUserId) Logger->Write("\t 0x%08X\n", (int)retval);
		return retval;
	}

	if (bLogging && bLogUserId) Logger->Write("\t Received ID: %u -> Account ID: %u\n", uClientIpAddr, uClientIpAddr/2);
	if (bRevClient)
	{
		pReceiveValidSteamGlobalUserID->m_SteamInstanceID = 0;
		pReceiveValidSteamGlobalUserID->Split.High32bits = 0;
		pReceiveValidSteamGlobalUserID->Split.Low32bits = uClientIpAddr / 2;
	}
	else
	{
		pReceiveValidSteamGlobalUserID->m_SteamInstanceID = 0;
		pReceiveValidSteamGlobalUserID->Split.High32bits = uClientIpAddr % 2;
		pReceiveValidSteamGlobalUserID->Split.Low32bits = uClientIpAddr / 2;
	}

	return eSteamErrorNone;
}

STEAM_API void STEAM_CALL SteamAbortOngoingUserIDTicketValidation(SteamUserIDTicketValidationHandle_t Handle)
{
// #ifdef DEBUG
	if (bLogging && bLogUserId) Logger->Write("SteamAbortOngoingUserIDTicketValidation (%u)\n", Handle);
// #endif
	if (bSteamDll)
	{
		void (*fptr)(SteamUserIDTicketValidationHandle_t);
		*(void **)(&fptr) = GetProcAddress(GetModuleHandleA(szOrigSteamDll), "SteamAbortOngoingUserIDTicketValidation");
		(*fptr)(Handle);
		if (bLogging && bLogUserId) Logger->Write("\t returned.\n");
		return;
	}
	return;
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