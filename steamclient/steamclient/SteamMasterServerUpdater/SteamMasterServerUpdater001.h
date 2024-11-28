class CSteamMasterServerUpdater001
{
public:
	CSteamMasterServerUpdater001();
	~CSteamMasterServerUpdater001();

	virtual void SetActive(bool a1);
	virtual void SetHeartbeatInterval(int a1);
	virtual bool HandleIncomingPacket(void  const* a1, int a2, unsigned int a3, unsigned short a4);
	virtual int GetNextOutgoingPacket(void * a1, int a2, unsigned int * a3, unsigned short * a4);
	virtual int SetBasicServerData(unsigned short a1, bool a2, char  const* a3, char  const* a4, unsigned short a5, bool a6, char  const* a7);
	virtual void ClearAllKeyValues(void);
	virtual int SetKeyValue(char  const* a1, char  const* a2);
	virtual void NotifyShutdown(void);
	virtual bool WasRestartRequested(void);
	virtual void ForceHeartbeat(void);
	virtual bool AddMasterServer(char  const* a1);
	virtual bool RemoveMasterServer(char  const* a1);
	virtual int GetNumMasterServers(void);
	virtual bool GetMasterServerAddress(int a1, char * a2, int a3);
};