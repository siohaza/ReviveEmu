/*
`vtable for'CAdapterSteamNetworking002
_ZN26CAdapterSteamNetworking00218CreateListenSocketEijtb ; CAdapterSteamNetworking002::CreateListenSocket(int,uint,ushort,bool)
_ZN26CAdapterSteamNetworking00225CreateP2PConnectionSocketE8CSteamIDiib
_ZN26CAdapterSteamNetworking00222CreateConnectionSocketEjti
_ZN26CAdapterSteamNetworking00213DestroySocketEjb
_ZN26CAdapterSteamNetworking00219DestroyListenSocketEjb
_ZN26CAdapterSteamNetworking00216SendDataOnSocketEjPvjb
_ZN26CAdapterSteamNetworking00223IsDataAvailableOnSocketEjPj
_ZN26CAdapterSteamNetworking00222RetrieveDataFromSocketEjPvjPj
_ZN26CAdapterSteamNetworking00215IsDataAvailableEjPjS0_
_ZN26CAdapterSteamNetworking00212RetrieveDataEjPvjPjS1_
_ZN26CAdapterSteamNetworking00213GetSocketInfoEjP8CSteamIDPiPjPt
_ZN26CAdapterSteamNetworking00219GetListenSocketInfoEjPjPt
_ZN26CAdapterSteamNetworking00223GetSocketConnectionTypeEj
_ZN26CAdapterSteamNetworking00216GetMaxPacketSizeEj
*/

#include "..\Common\steamclientpublic.h"
#include "..\Common\steamtypes.h"

class CSteamNetworking002
{
public:
	CSteamNetworking002();
	~CSteamNetworking002();

	virtual void CreateListenSocket(int, uint, ushort, bool);
	virtual void CreateP2PConnectionSocket(CSteamID, int, int, bool);
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
	virtual void GetSocketConnectionType(unsigned int);
	virtual void GetMaxPacketSize(unsigned int);
};