#include ".\SteamMatchMaking.h"

class CSteamMatchMaking001
{
public:
	CSteamMatchMaking001();
	~CSteamMatchMaking001();

	virtual int GetFavoriteGameCount(void);
	virtual bool GetFavoriteGame(int a1, unsigned int * a2, unsigned int * a3, unsigned short * a4, unsigned int * a5, unsigned int * a6);
	virtual int AddFavoriteGame(unsigned int a1, unsigned int a2, unsigned short a3, unsigned int a4, unsigned int a5);
	virtual bool RemoveFavoriteGame(unsigned int a1, unsigned int a2, unsigned short a3, unsigned int a4);
	virtual bool GetFavoriteGame2(int a1, unsigned int * a2, unsigned int * a3, unsigned short * a4, unsigned short * a5, unsigned int * a6, unsigned int * a7);
	virtual int AddFavoriteGame2(unsigned int a1, unsigned int a2, unsigned short a3, unsigned short a4, unsigned int a5, unsigned int a6);
	virtual bool RemoveFavoriteGame2(unsigned int a1, unsigned int a2, unsigned short a3, unsigned short a4, unsigned int a5);
	virtual void RequestLobbyList(unsigned long long a1, MatchMakingKeyValuePair_t * a2, unsigned int a3);
	virtual CSteamID GetLobbyByIndex(int a1);
	virtual void CreateLobby(unsigned long long a1, bool a2);
	virtual void JoinLobby(CSteamID a1);
	virtual void LeaveLobby(CSteamID a1);
	virtual bool InviteUserToLobby(CSteamID a1, CSteamID a2);
	virtual int GetNumLobbyMembers(CSteamID a1);
	virtual CSteamID GetLobbyMemberByIndex(CSteamID a1, int a2);
	virtual const char* GetLobbyData(CSteamID a1, char  const* a2);
	virtual void SetLobbyData(CSteamID a1, char  const* a2, char  const* a3);
	virtual const char* GetLobbyMemberData(CSteamID a1, CSteamID a2, char  const* a3);
	virtual void SetLobbyMemberData(CSteamID a1, char  const* a2, char  const* a3);
	virtual void ChangeLobbyAdmin(CSteamID a1, CSteamID a2);
	virtual bool SendLobbyChatMsg(CSteamID a1, void  const* a2, int a3);
	virtual int GetLobbyChatEntry(CSteamID a1, int a2, CSteamID* a3, void * a4, int a5, EChatEntryType * a6);
};
