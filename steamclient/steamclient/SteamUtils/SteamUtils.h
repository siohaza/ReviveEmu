#pragma once

class CSteamUtils
{
public:
	CSteamUtils();
	~CSteamUtils();

	virtual void GetSecondsSinceAppActive(void);
	virtual void GetSecondsSinceComputerActive(void);
	virtual EUniverse GetConnectedUniverse(void);
	virtual void GetServerRealTime(void);
	virtual const char* GetIPCountry(void);
	virtual bool GetImageSize(int a1, unsigned int * a2, unsigned int * a3);
	virtual bool GetImageRGBA(int a1, unsigned char * a2, int a3);
	virtual void GetCSERIPPort(unsigned int * a1, unsigned short * a2);
	virtual void GetCurrentBatteryPower(void);
	virtual int GetAppId(void);
	virtual void GetNumRunningApps(void);
	virtual void GetOfflineMode(void);
	virtual void SetOfflineMode(bool a1);
};

CSteamUtils* GSteamUtils();