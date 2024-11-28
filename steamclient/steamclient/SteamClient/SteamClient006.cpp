#include "..\Common\commonincludes.h"
#include "..\Common\steamclientpublic.h"
#include ".\SteamClient006.h"
#include ".\SteamClient.h"

extern bool g_bLogging;
extern CLogFile* Logger;

extern CSteamClient* g_pSteamClient;

CSteamClient006::CSteamClient006()
{
}

CSteamClient006::~CSteamClient006()
{
}

HSteamPipe CSteamClient006::CreateSteamPipe() 
{ 
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamClient = GSteamClient();
	return g_pSteamClient->CreateSteamPipe(); 
}

bool CSteamClient006::BReleaseSteamPipe( HSteamPipe hSteamPipe )
{ 
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamClient = GSteamClient();
	return g_pSteamClient->BReleaseSteamPipe(hSteamPipe); 
}

HSteamUser CSteamClient006::CreateGlobalUser( HSteamPipe *phSteamPipe )
{ 
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamClient = GSteamClient();
	return g_pSteamClient->CreateGlobalUser( phSteamPipe ); 
}

HSteamUser CSteamClient006::ConnectToGlobalUser( HSteamPipe hSteamPipe )
{ 
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamClient = GSteamClient();
	return g_pSteamClient->ConnectToGlobalUser( hSteamPipe ); 
}

HSteamUser CSteamClient006::CreateLocalUser( HSteamPipe *phSteamPipe )
{ 
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamClient = GSteamClient();
	return g_pSteamClient->CreateLocalUser( phSteamPipe );
}

void CSteamClient006::ReleaseUser( HSteamPipe hSteamPipe, HSteamUser hUser )
{ 
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamClient = GSteamClient();
	return g_pSteamClient->ReleaseUser( hSteamPipe, hUser );
}

int CSteamClient006::GetISteamUser( HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char *pchVersion ) 
{ 
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamClient = GSteamClient();
	return g_pSteamClient->GetISteamUser( hSteamUser, hSteamPipe, pchVersion ); 
}

int CSteamClient006::GetIVAC( HSteamUser hSteamUser )
{ 
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamClient = GSteamClient();
	return g_pSteamClient->GetIVAC( hSteamUser ); 
}

int CSteamClient006::GetISteamGameServer( HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char *pchVersion ) 
{ 
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamClient = GSteamClient();
	return g_pSteamClient->GetISteamGameServer( hSteamUser, hSteamPipe, pchVersion ); 
}

void CSteamClient006::SetLocalIPBinding( uint32 unIP, uint16 usPort )
{ 
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamClient = GSteamClient();
	return g_pSteamClient->SetLocalIPBinding( unIP, usPort ); 
}

const char*	CSteamClient006::GetUniverseName( EUniverse eUniverse ) 
{ 
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamClient = GSteamClient();
	return g_pSteamClient->GetUniverseName( eUniverse ); 
}

int CSteamClient006::GetISteamFriends( HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char *pchVersion )
{ 
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamClient = GSteamClient();
	return g_pSteamClient->GetISteamFriends( hSteamUser, hSteamPipe, pchVersion ); 
}

int CSteamClient006::GetISteamUtils( HSteamPipe hSteamPipe, const char *pchVersion ) 
{ 
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamClient = GSteamClient();
	return g_pSteamClient->GetISteamUtils( hSteamPipe, pchVersion ); 
}

int CSteamClient006::GetISteamBilling( HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char *pchVersion )
{ 
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamClient = GSteamClient();
	return g_pSteamClient->GetISteamBilling( hSteamUser, hSteamPipe, pchVersion );
}

int CSteamClient006::GetISteamMatchMaking(int a1, int a2, char  const* a3)
{ 
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamClient = GSteamClient();
	return g_pSteamClient->GetISteamMatchMaking(a1, a2, a3); 
}

int CSteamClient006::GetISteamContentServer(int a1, int a2, char  const* a3)
{ 
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamClient = GSteamClient();
	return g_pSteamClient->GetISteamContentServer(a1, a2, a3);
}

int CSteamClient006::GetISteamApps(int a1, int a2, char  const* a3)
{ 
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	return 0;
}

int CSteamClient006::GetISteamMasterServerUpdater(int a1, int a2, char  const* a3)
{ 
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamClient = GSteamClient();
	return g_pSteamClient->GetISteamMasterServerUpdater(a1, a2, a3); 
}

int CSteamClient006::GetISteamMatchMakingServers(int a1, int a2, char  const* a3)
{ 
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamClient = GSteamClient();
	return g_pSteamClient->GetISteamMatchMakingServers(a1, a2, a3); 
}

void CSteamClient006::RunFrame(void)
{ 
	//if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamClient = GSteamClient();
	return g_pSteamClient->RunFrame();
}

int CSteamClient006::GetIPCCallCount(void)
{ 
	if (g_bLogging) Logger->Write("%s\n", __FUNCTION__); 
	g_pSteamClient = GSteamClient();
	return g_pSteamClient->GetIPCCallCount(); 
};
