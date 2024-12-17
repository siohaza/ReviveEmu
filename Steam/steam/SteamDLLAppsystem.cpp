#include "stdafx.h"
#include "SteamDLLAppsystem001.h"

CSteamDLLAppsystem001::CSteamDLLAppsystem001(){}
CSteamDLLAppsystem001::~CSteamDLLAppsystem001(){}

bool CSteamDLLAppsystem001::Connect(CreateInterfaceFn factory)
{
	return true;
}
void CSteamDLLAppsystem001::Disconnect()
{
	return;
}
void* CSteamDLLAppsystem001::QueryInterface(const char* pInterfaceName)
{
	return _f(pInterfaceName);
}
InitReturnVal_t CSteamDLLAppsystem001::Init()
{
	return INIT_OK;
}
void CSteamDLLAppsystem001::Shutdown()
{
	return;
}
