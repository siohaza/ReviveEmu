#pragma once
#include "ServerManager.h"

struct TMasterRequest;
struct TServerMaster {
	void *				pServerMaster;		// Reference to CServerMaster
	TMasterRequest *	pMasterRequest;		// Request Options
};

class CServerManager;
class CServerInfo;

class CServerMaster
{
private:
	CServerManager * m_pServerManager;
	SOCKET m_sckMaster;

public:
	CServerMaster(CServerManager * pServerManager, TMasterRequest * pMasterRequest);
	~CServerMaster(void);
private:
	char * ConstructPacket(byte bytMessageType, 
		byte bytRegionCode,
		const char * cszIPIterator,
		const char * cszFilter,
		unsigned int * uPacketSize);
public:
	static void QueryThread(void * pQuery);
	void StartQuery(TMasterRequest * pRequest);
};
