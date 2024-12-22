#pragma once

extern CLogFile* Logger;
extern BOOL bLogging;
extern BOOL bLogUserId;
extern BOOL bSteamDll;
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
