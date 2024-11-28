#pragma once

#include "Steam.h"

class CSteamDLLAppsystem001
{
public:
	CSteamDLLAppsystem001();
	~CSteamDLLAppsystem001();

	virtual bool Dummy1(int arg1);
	virtual void Dummy2();
	virtual int CreateSteamInterface(const char* cszSteamInterfaceVersion);
	virtual int Dummy3();
	virtual void Dummy4();
};
