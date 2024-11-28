#include "stdafx.h"
#include "SteamDLLAppsystem001.h"

CSteamDLLAppsystem001::CSteamDLLAppsystem001(){}
CSteamDLLAppsystem001::~CSteamDLLAppsystem001(){}

bool CSteamDLLAppsystem001::Dummy1(int arg1)
{
	return true;
}
void CSteamDLLAppsystem001::Dummy2()
{
	return;
}
int CSteamDLLAppsystem001::CreateSteamInterface(const char* cszSteamInterfaceVersion)
{
	return _f(cszSteamInterfaceVersion);
}
int CSteamDLLAppsystem001::Dummy3()
{
	return 1;
}
void CSteamDLLAppsystem001::Dummy4()
{
	return;
}

