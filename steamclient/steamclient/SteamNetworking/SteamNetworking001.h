/*
`vtable for'CAdapterSteamNetworking001
_ZN26CAdapterSteamNetworking00118CreateListenSocketEijt ; CAdapterSteamNetworking001::CreateListenSocket(int,uint,ushort)
_ZN26CAdapterSteamNetworking00125CreateP2PConnectionSocketE8CSteamIDii
_ZN26CAdapterSteamNetworking00122CreateConnectionSocketEjti
_ZN26CAdapterSteamNetworking00113DestroySocketEjb
_ZN26CAdapterSteamNetworking00119DestroyListenSocketEjb
_ZN26CAdapterSteamNetworking00116SendDataOnSocketEjPvjb
_ZN26CAdapterSteamNetworking00123IsDataAvailableOnSocketEjPj
_ZN26CAdapterSteamNetworking00122RetrieveDataFromSocketEjPvjPj
_ZN26CAdapterSteamNetworking00115IsDataAvailableEjPjS0_
_ZN26CAdapterSteamNetworking00112RetrieveDataEjPvjPjS1_
_ZN26CAdapterSteamNetworking00113GetSocketInfoEjP8CSteamIDPiPjPt
_ZN26CAdapterSteamNetworking00119GetListenSocketInfoEjPjPt
*/
#include "..\Common\steamclientpublic.h"
#include "..\Common\steamtypes.h"

class CSteamNetworking001
{
public:
	CSteamNetworking001();
	~CSteamNetworking001();

	virtual void CreateListenSocket(int,uint,ushort);
	virtual void CreateP2PConnectionSocket(CSteamID, int, int);
	virtual void CreateConnectionSocket(unsigned int, unsigned short, int);
	virtual void DestroySocket(unsigned int, bool);
	virtual void DestroyListenSocket(unsigned int, bool);
	virtual void SendDataOnSocket(unsigned int, void *, unsigned int, bool);
	virtual void IsDataAvailableOnSocket(unsigned int, unsigned int *);
	virtual void RetrieveDataFromSocket(unsigned int, void *, unsigned int, unsigned int *);
	virtual void IsDataAvailable(unsigned int, unsigned int *, unsigned int *);
	virtual void RetrieveData(unsigned int, void *, unsigned int, unsigned int *, unsigned int *);
	virtual void GetSocketInfo(unsigned int, CSteamID *, int *, unsigned int *, unsigned short *);
	virtual void GetListenSocketInfo(unsigned int, unsigned int *, unsigned short *);
};