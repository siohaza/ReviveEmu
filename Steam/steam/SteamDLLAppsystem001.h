#pragma once

#include "Steam.h"

typedef void* (*CreateInterfaceFn)(const char* pName, int* pReturnCode);

enum InitReturnVal_t
{
	INIT_FAILED = 0,
	INIT_OK,

	INIT_LAST_VAL,
};

class CSteamDLLAppsystem001
{
public:
	CSteamDLLAppsystem001();
	~CSteamDLLAppsystem001();

	virtual bool Connect(CreateInterfaceFn factory);
	virtual void Disconnect();
	virtual void* QueryInterface(const char* pInterfaceName);
	virtual InitReturnVal_t Init();
	virtual void Shutdown();
};
