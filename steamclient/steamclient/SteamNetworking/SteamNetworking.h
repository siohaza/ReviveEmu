class CSteamNetworking
{
public:
	CSteamNetworking();
	~CSteamNetworking();

	virtual void CreateListenSocket(int,uint,ushort);
	virtual void CreateListenSocket(int,uint,ushort, bool);
	virtual void CreateP2PConnectionSocket(CSteamID, int, int);
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
};