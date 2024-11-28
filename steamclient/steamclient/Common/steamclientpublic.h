//========= Copyright © 1996-2004, Valve LLC, All rights reserved. ============
//
// Purpose:
//
// $NoKeywords: $
//=============================================================================

#ifndef STEAMCLIENTPUBLIC_H
#define STEAMCLIENTPUBLIC_H
#ifdef _WIN32
#pragma once
#endif

#ifdef STEAMCLIENT_EXPORTS
#define STEAMCLIENT_API __declspec(dllexport)
#else
#define STEAMCLIENT_API __declspec(dllimport)
#endif
//lint -save -e1931 -e1927 -e1924 -e613 -e726

// This header file defines the interface between the calling application and the code that
// knows how to communicate with the connection manager (CM) from the Steam service 

// This header file is intended to be portable; ideally this 1 header file plus a lib or dll
// is all you need to integrate the client library into some other tree.  So please avoid
// including or requiring other header files if possible.  This header should only describe the 
// interface layer, no need to include anything about the implementation.

#include ".\steamtypes.h"

struct CallbackMsg_t
{
	HSteamUser m_hSteamUser;
	int m_iCallback;
	void* m_pubParam;
	int m_cubParam;
};

// General result codes
enum EResult
{
	k_EResultOK	= 1,							// success
	k_EResultFail = 2,							// generic failure 
	k_EResultNoConnection = 3,					// no/failed network connection
//	k_EResultNoConnectionRetry = 4,				// OBSOLETE - removed
	k_EResultInvalidPassword = 5,				// password/ticket is invalid
	k_EResultLoggedInElsewhere = 6,				// same user logged in elsewhere
	k_EResultInvalidProtocolVer = 7,			// protocol version is incorrect
	k_EResultInvalidParam = 8,					// a parameter is incorrect
	k_EResultFileNotFound = 9,					// file was not found
	k_EResultBusy = 10,							// called method busy - action not taken
	k_EResultInvalidState = 11,					// called object was in an invalid state
	k_EResultInvalidName = 12,					// name is invalid
	k_EResultInvalidEmail = 13,					// email is invalid
	k_EResultDuplicateName = 14,				// name is not unique
	k_EResultAccessDenied = 15,					// access is denied
	k_EResultTimeout = 16,						// operation timed out
	k_EResultBanned = 17,						// VAC2 banned
	k_EResultAccountNotFound = 18,				// account not found
	k_EResultInvalidSteamID = 19,				// steamID is invalid
	k_EResultServiceUnavailable = 20,			// The requested service is currently unavailable
	k_EResultNotLoggedOn = 21,					// The user is not logged on
	k_EResultPending = 22,						// Request is pending (may be in process, or waiting on third party)
	k_EResultEncryptionFailure = 23,			// Encryption or Decryption failed
	k_EResultInsufficientPrivilege = 24,		// Insufficient privilege
	k_EResultLimitExceeded = 25,				// Too much of a good thing
	k_EResultRevoked = 26,						// Access has been revoked (used for revoked guest passes)
	k_EResultExpired = 27,						// License/Guest pass the user is trying to access is expired
	k_EResultAlreadyRedeemed = 28,				// Guest pass has already been redeemed by account, cannot be acked again
	k_EResultDuplicateRequest = 29,				// The request is a duplicate and the action has already occurred in the past, ignored this time
	k_EResultAlreadyOwned = 30,					// All the games in this guest pass redemption request are already owned by the user
	k_EResultIPNotFound = 31,					// IP address not found
	k_EResultPersistFailed = 32,				// failed to write change to the data store
	k_EResultLockingFailed = 33,				// failed to acquire access lock for this operation
	k_EResultLogonSessionReplaced = 34,
	k_EResultConnectFailed = 35,
	k_EResultHandshakeFailed = 36,
	k_EResultIOFailure = 37,
	k_EResultRemoteDisconnect = 38,
};

// Result codes to GSHandleClientDeny/Kick
typedef enum
{
	k_EDenyInvalidVersion = 1,
	k_EDenyGeneric = 2,
	k_EDenyNotLoggedOn = 3,
	k_EDenyNoLicense = 4,
	k_EDenyCheater = 5,
	k_EDenyLoggedInElseWhere = 6,
	k_EDenyUnknownText = 7,
	k_EDenyIncompatibleAnticheat = 8,
	k_EDenyMemoryCorruption = 9,
	k_EDenyIncompatibleSoftware = 10,
	k_EDenySteamConnectionLost = 11,
	k_EDenySteamConnectionError = 12,
	k_EDenySteamResponseTimedOut = 13,
	k_EDenySteamValidationStalled = 14,
} EDenyReason;

// Steam universes.  Each universe is a self-contained Steam instance.
enum EUniverse
{
	k_EUniverseInvalid = 0,
	k_EUniversePublic = 1,
	k_EUniverseBeta = 2,
	k_EUniverseInternal = 3,
	k_EUniverseDev = 4,
	k_EUniverseRC = 5,

	k_EUniverseMax
};

// Steam account types
enum EAccountType
{
	k_EAccountTypeInvalid = 0,			
	k_EAccountTypeIndividual = 1,		// single user account
	k_EAccountTypeMultiseat = 2,		// multiseat (e.g. cybercafe) account
	k_EAccountTypeGameServer = 3,		// game server account
	k_EAccountTypeAnonGameServer = 4,	// anonymous game server account
	k_EAccountTypePending = 5,			// pending
	k_EAccountTypeContentServer = 6,	// content server
	k_EAccountTypeClan = 7,
	k_EAccountTypeChat = 8,
	k_EAccountTypeP2PSuperSeeder = 9,	// a fake steamid used by superpeers to seed content to users of Steam P2P stuff

	// Max of 16 items in this field
	k_EAccountTypeMax
};


//-----------------------------------------------------------------------------
// types of user game stats fields
// WARNING: DO NOT RENUMBER EXISTING VALUES - STORED IN DATABASE
//-----------------------------------------------------------------------------
enum ESteamUserStatType
{
	k_ESteamUserStatTypeINVALID = 0,
	k_ESteamUserStatTypeINT = 1,
	k_ESteamUserStatTypeFLOAT = 2,
	// Read as FLOAT, set with count / session length
	k_ESteamUserStatTypeAVGRATE = 3,
	k_ESteamUserStatTypeACHIEVEMENTS = 4,
	k_ESteamUserStatTypeGROUPACHIEVEMENTS = 5,
};


//-----------------------------------------------------------------------------
// Purpose: Chat Entry Types (previously was only friend-to-friend message types)
//-----------------------------------------------------------------------------
enum EChatEntryType
{
	k_EChatEntryTypeChatMsg = 1,		// Normal text message from another user
	k_EChatEntryTypeTyping = 2,			// Another user is typing (not used in multi-user chat)
	k_EChatEntryTypeInviteGame = 3,		// DEPRECATED Invite from other user into that users current game
	k_EChatEntryTypeEmote = 4,			// text emote message
	// Above are previous FriendMsgType entries, now merged into more generic chat entry types
};


//-----------------------------------------------------------------------------
// Purpose: Chat Room Enter Responses
//-----------------------------------------------------------------------------
enum EChatRoomEnterResponse
{
	k_EChatRoomEnterResponseSuccess = 1,		// Success
	k_EChatRoomEnterResponseDoesntExist = 2,	// Chat doesn't exist (probably closed)
	k_EChatRoomEnterResponseNotAllowed = 3,		// General Denied - You don't have the permissions needed to join the chat
	k_EChatRoomEnterResponseFull = 4,			// Chat room has reached its maximum size
	k_EChatRoomEnterResponseError = 5,			// Unexpected Error
	k_EChatRoomEnterResponseBanned = 6,			// You are banned from this chat room and may not join
};


typedef void (*PFNLegacyKeyRegistration)( const char *pchCDKey, const char *pchInstallPath );
typedef bool (*PFNLegacyKeyInstalled)();


#pragma pack( push, 1 )		

// Steam ID structure (64 bits total)
class CSteamID
{
public:

	//-----------------------------------------------------------------------------
	// Purpose: Constructor
	//-----------------------------------------------------------------------------
	CSteamID()
	{
		m_unAccountID = 0;
		m_EAccountType = k_EAccountTypeInvalid;
		m_EUniverse = k_EUniverseInvalid;
		m_unAccountInstance = 0;
	}


	//-----------------------------------------------------------------------------
	// Purpose: Constructor
	// Input  : unAccountID -	32-bit account ID
	//			eUniverse -		Universe this account belongs to
	//			eAccountType -	Type of account
	//-----------------------------------------------------------------------------
	CSteamID( uint32 unAccountID, EUniverse eUniverse, EAccountType eAccountType )
	{
		Set( unAccountID, eUniverse, eAccountType );
	}


	//-----------------------------------------------------------------------------
	// Purpose: Constructor
	// Input  : unAccountID -	32-bit account ID
	//			unAccountInstance - instance 
	//			eUniverse -		Universe this account belongs to
	//			eAccountType -	Type of account
	//-----------------------------------------------------------------------------
	CSteamID( uint32 unAccountID, unsigned int unAccountInstance, EUniverse eUniverse, EAccountType eAccountType )
	{
#if defined(_SERVER) && defined(Assert)
		Assert( ! ( ( k_EAccountTypeIndividual == eAccountType ) && ( 1 != unAccountInstance ) ) );	// enforce that for individual accounts, instance is always 1
#endif // _SERVER
		InstancedSet( unAccountID, unAccountInstance, eUniverse, eAccountType );
	}


	//-----------------------------------------------------------------------------
	// Purpose: Constructor
	// Input  : ulSteamID -		64-bit representation of a Steam ID
	// Note:	Will not accept a uint32 or int32 as input, as that is a probable mistake.
	//			See the stubbed out overloads in the private: section for more info.
	//-----------------------------------------------------------------------------
	CSteamID( uint64 ulSteamID )
	{
		SetFromUint64( ulSteamID );
	}


	//-----------------------------------------------------------------------------
	// Purpose: Sets parameters for steam ID
	// Input  : unAccountID -	32-bit account ID
	//			eUniverse -		Universe this account belongs to
	//			eAccountType -	Type of account
	//-----------------------------------------------------------------------------
	void Set( uint32 unAccountID, EUniverse eUniverse, EAccountType eAccountType )
	{
		m_unAccountID = unAccountID;
		m_EUniverse = eUniverse;
		m_EAccountType = eAccountType;
		m_unAccountInstance = 1;
	}


	//-----------------------------------------------------------------------------
	// Purpose: Sets parameters for steam ID
	// Input  : unAccountID -	32-bit account ID
	//			eUniverse -		Universe this account belongs to
	//			eAccountType -	Type of account
	//-----------------------------------------------------------------------------
	void InstancedSet( uint32 unAccountID, uint32 unInstance, EUniverse eUniverse, EAccountType eAccountType )
	{
		m_unAccountID = unAccountID;
		m_EUniverse = eUniverse;
		m_EAccountType = eAccountType;
		m_unAccountInstance = unInstance;
	}


	//-----------------------------------------------------------------------------
	// Purpose: Initializes a steam ID from its 52 bit parts and universe/type
	// Input  : ulIdentifier - 52 bits of goodness
	//-----------------------------------------------------------------------------
	void FullSet( uint64 ulIdentifier, EUniverse eUniverse, EAccountType eAccountType )
	{
		m_unAccountID = ( ulIdentifier & 0xFFFFFFFF );						// account ID is low 32 bits
		m_unAccountInstance = ( ( ulIdentifier >> 32 ) & 0xFFFFF );			// account instance is next 20 bits
		m_EUniverse = eUniverse;
		m_EAccountType = eAccountType;
	}


	//-----------------------------------------------------------------------------
	// Purpose: Initializes a steam ID from its 64-bit representation
	// Input  : ulSteamID -		64-bit representation of a Steam ID
	//-----------------------------------------------------------------------------
	void SetFromUint64( uint64 ulSteamID )
	{
		m_unAccountID = ( ulSteamID & 0xFFFFFFFF );							// account ID is low 32 bits
		m_unAccountInstance = ( ( ulSteamID >> 32 ) & 0xFFFFF );			// account instance is next 20 bits

		m_EAccountType = ( EAccountType ) ( ( ulSteamID >> 52 ) & 0xF );	// type is next 4 bits
		m_EUniverse = ( EUniverse ) ( ( ulSteamID >> 56 ) & 0xFF );			// universe is next 8 bits
	}


#if defined( INCLUDED_STEAM_COMMON_STEAMCOMMON_H ) 
	//-----------------------------------------------------------------------------
	// Purpose: Initializes a steam ID from a Steam2 ID structure
	// Input:	pTSteamGlobalUserID -	Steam2 ID to convert
	//			eUniverse -				universe this ID belongs to
	//-----------------------------------------------------------------------------
	void SetFromSteam2( TSteamGlobalUserID *pTSteamGlobalUserID, EUniverse eUniverse )
	{
		m_unAccountID = pTSteamGlobalUserID->Split.Low32bits * 2 + 
			pTSteamGlobalUserID->Split.High32bits;
		m_EUniverse = eUniverse;		// set the universe
		m_EAccountType = k_EAccountTypeIndividual; // Steam 2 accounts always map to account type of individual
		m_unAccountInstance = 1;	// individual accounts always have an account instance ID of 1
	}

	//-----------------------------------------------------------------------------
	// Purpose: Fills out a Steam2 ID structure
	// Input:	pTSteamGlobalUserID -	Steam2 ID to write to
	//-----------------------------------------------------------------------------
	void ConvertToSteam2( TSteamGlobalUserID *pTSteamGlobalUserID ) const
	{
		// only individual accounts have any meaning in Steam 2, only they can be mapped
		// Assert( m_EAccountType == k_EAccountTypeIndividual );

		pTSteamGlobalUserID->m_SteamInstanceID = 0;
		pTSteamGlobalUserID->Split.High32bits = m_unAccountID % 2;
		pTSteamGlobalUserID->Split.Low32bits = m_unAccountID / 2;
	}
#endif // defined( INCLUDED_STEAM_COMMON_STEAMCOMMON_H )

	//-----------------------------------------------------------------------------
	// Purpose: Converts steam ID to its 64-bit representation
	// Output : 64-bit representation of a Steam ID
	//-----------------------------------------------------------------------------
	uint64 ConvertToUint64() const
	{
		return (uint64) ( ( ( (uint64) m_EUniverse ) << 56 ) + ( ( (uint64) m_EAccountType ) << 52 ) + 
			( ( (uint64) m_unAccountInstance ) << 32 ) + m_unAccountID );
	}


	//-----------------------------------------------------------------------------
	// Purpose: Converts the static parts of a steam ID to a 64-bit representation.
	//			For multiseat accounts, all instances of that account will have the
	//			same static account key, so they can be grouped together by the static
	//			account key.
	// Output : 64-bit static account key
	//-----------------------------------------------------------------------------
	uint64 GetStaticAccountKey() const
	{
		// note we do NOT include the account instance (which is a dynamic property) in the static account key
		return (uint64) ( ( ( (uint64) m_EUniverse ) << 56 ) + ((uint64) m_EAccountType << 52 ) + m_unAccountID );
	}


	//-----------------------------------------------------------------------------
	// Purpose: create an anonymous game server login to be filled in by the AM
	//-----------------------------------------------------------------------------
	void CreateBlankAnonLogon( EUniverse eUniverse )
	{
		m_unAccountID = 0;
		m_EAccountType = k_EAccountTypeAnonGameServer;
		m_EUniverse = eUniverse;
		m_unAccountInstance = 0;
	}

	//-----------------------------------------------------------------------------
	// Purpose: Is this an anonymous game server login that will be filled in?
	//-----------------------------------------------------------------------------
	bool BBlankAnonAccount() const
	{
		return m_unAccountID == 0 && 
			m_EAccountType == k_EAccountTypeAnonGameServer &&
			m_unAccountInstance == 0;
	}

	//-----------------------------------------------------------------------------
	// Purpose: Is this a game server account id?
	//-----------------------------------------------------------------------------
	bool BGameServerAccount() const
	{
		return m_EAccountType == k_EAccountTypeGameServer || m_EAccountType == k_EAccountTypeAnonGameServer;
	}

	//-----------------------------------------------------------------------------
	// Purpose: Is this a content server account id?
	//-----------------------------------------------------------------------------
	bool BContentServerAccount() const
	{
		return m_EAccountType == k_EAccountTypeContentServer;
	}


	//-----------------------------------------------------------------------------
	// Purpose: Is this a clan account id?
	//-----------------------------------------------------------------------------
	bool BClanAccount() const
	{
		return m_EAccountType == k_EAccountTypeClan;
	}


	//-----------------------------------------------------------------------------
	// Purpose: Is this a chat account id?
	//-----------------------------------------------------------------------------
	bool BChatAccount() const
	{
		return m_EAccountType == k_EAccountTypeChat;
	}


	//-----------------------------------------------------------------------------
	// Purpose: Is this an individual user account id?
	//-----------------------------------------------------------------------------
	bool BIndividualAccount() const
	{
		return m_EAccountType == k_EAccountTypeIndividual;
	}


	// simple accessors
	void SetAccountID( uint32 unAccountID )		{ m_unAccountID = unAccountID; }
	uint32 GetAccountID() const					{ return m_unAccountID; }
	uint32 GetUnAccountInstance() const			{ return m_unAccountInstance; }
	EAccountType GetEAccountType() const		{ return ( EAccountType ) m_EAccountType; }
	EUniverse GetEUniverse() const				{ return m_EUniverse; }
	void SetEUniverse( EUniverse eUniverse )	{ m_EUniverse = eUniverse; }
	bool IsValid() const						{ return ( m_EAccountType != k_EAccountTypeInvalid && m_EUniverse != k_EUniverseInvalid ); }

	// this set of functions is hidden, will be moved out of class
	explicit CSteamID( const char *pchSteamID, EUniverse eDefaultUniverse = k_EUniverseInvalid );
	char * Render() const;				// renders this steam ID to string
	static char * Render( uint64 ulSteamID );	// static method to render a uint64 representation of a steam ID to a string

	void SetFromString( const char *pchSteamID, EUniverse eDefaultUniverse );
	bool SetFromSteam2String( const char *pchSteam2ID, EUniverse eUniverse );

	bool operator==( const CSteamID &val ) const
	{
		return ( ( val.m_unAccountID == m_unAccountID ) && ( val.m_unAccountInstance == m_unAccountInstance )
			&& ( val.m_EAccountType == m_EAccountType ) &&  ( val.m_EUniverse == m_EUniverse ) );
	} 

	bool operator!=( const CSteamID &val ) const { return !operator==( val ); }
	bool operator<( const CSteamID &val ) const { return ConvertToUint64() < val.ConvertToUint64(); }

	// DEBUG function
	bool BValidExternalSteamID() const;

private:
	// These are defined here to prevent accidental implicit conversion of a u32AccountID to a CSteamID.
	// If you get a compiler error about an ambiguous constructor/function then it may be because you're
	// passing a 32-bit int to a function that takes a CSteamID. You should explicitly create the SteamID
	// using the correct Universe and account Type/Instance values.
	CSteamID( uint32 );
	CSteamID( int32 );

#ifdef _WIN32
#pragma warning(push)
#pragma warning(disable:4201)	// nameless union is nonstandard
	// 64 bits total
	union
	{
		struct
		{
#endif
			uint32				m_unAccountID : 32;			// unique account identifier
			unsigned int		m_unAccountInstance : 20;	// dynamic instance ID (used for multiseat type accounts only)
			unsigned int		m_EAccountType : 4;			// type of account - can't show as EAccountType, due to signed / unsigned difference
			EUniverse			m_EUniverse : 8;			// universe this account belongs to
#ifdef _WIN32
		};

		uint64 m_unAll64Bits;
	};
#pragma warning(pop)			// no more anonymous unions until next time
#endif
};

const int k_unSteamAccountIDMask = 0xFFFFFFFF;
const int k_unSteamAccountInstanceMask = 0x000FFFFF;


// Special flags for Chat accounts - they go in the top 8 bits
// of the steam ID's "instance", leaving 12 for the actual instances
enum EChatSteamIDInstanceFlags
{
	k_EChatAccountInstanceMask = 0x00000FFF, // top 8 bits are flags

	k_EChatInstanceFlagClan = ( k_unSteamAccountInstanceMask + 1 ) >> 1,	// top bit
	k_EChatInstanceFlagLobby = ( k_unSteamAccountInstanceMask + 1 ) >> 2,	// next one down, etc

	// Max of 8 flags
};


// generic invalid CSteamID
const CSteamID k_steamIDNil;

// This steamID comes from a user game connection to an out of date GS that hasnt implemented the protocol
// to provide its steamID
const CSteamID k_steamIDOutofDateGS( 0, 0, k_EUniverseInvalid, k_EAccountTypeInvalid );
// This steamID comes from a user game connection to an sv_lan GS
const CSteamID k_steamIDLanModeGS( 0, 0, k_EUniversePublic, k_EAccountTypeInvalid );
// This steamID can come from a user game connection to a GS that has just booted but hasnt yet even initialized
// its steam3 component and started logging on.
const CSteamID k_steamIDNotInitYetGS( 1, 0, k_EUniverseInvalid, k_EAccountTypeInvalid );


#ifdef STEAM
// Returns the matching chat steamID, with the default instance of 0
// If the steamID passed in is already of type k_EAccountTypeChat it will be returned with the same instance
CSteamID ChatIDFromSteamID( CSteamID &steamID );
// Returns the matching clan steamID, with the default instance of 0
// If the steamID passed in is already of type k_EAccountTypeClan it will be returned with the same instance
CSteamID ClanIDFromSteamID( CSteamID &steamID );
// Asserts steamID type before conversion
CSteamID ChatIDFromClanID( CSteamID &steamIDClan );
// Asserts steamID type before conversion
CSteamID ClanIDFromChatID( CSteamID &steamIDChat );

#endif // _STEAM


//-----------------------------------------------------------------------------
// Purpose: encapsulates an appID/modID pair
//-----------------------------------------------------------------------------
class CGameID
{
public:
	CGameID()
	{
		m_ulGameID = 0;
	}

	explicit CGameID( uint64 ulGameID )
	{
		m_ulGameID = ulGameID;
	}

	explicit CGameID( int32 nAppID )
	{
		m_ulGameID = 0;
		m_gameID.m_nAppID = nAppID;
	}

	explicit CGameID( uint32 nAppID )
	{
		m_ulGameID = 0;
		m_gameID.m_nAppID = nAppID;
	}

	CGameID( uint32 nAppID, uint32 nModID )
	{
		m_ulGameID = 0;
		m_gameID.m_nAppID = nAppID;
		m_gameID.m_nModID = nModID;
		m_gameID.m_nType = k_EGameIDTypeGameMod;
	}

	// Hidden functions used only by Steam
	explicit CGameID( const char *pchGameID );
	char * Render() const;				// renders this Game ID to string
	static char * Render( uint64 ulGameID );	// static method to render a uint64 representation of a Game ID to a string

	// must include checksum_crc.h first to get this functionality
#if defined( CHECKSUM_CRC_H )
	CGameID( uint32 nAppID, const char *pchModPath )
	{
		m_ulGameID = 0;
		m_gameID.m_nAppID = nAppID;
		m_gameID.m_nType = k_EGameIDTypeGameMod;

		char rgchModDir[MAX_PATH];
		Q_FileBase( pchModPath, rgchModDir, sizeof( rgchModDir ) );
		CRC32_t crc32;
		CRC32_Init( &crc32 );
		CRC32_ProcessBuffer( &crc32, rgchModDir, Q_strlen( rgchModDir ) );
		CRC32_Final( &crc32 );

		// set the high-bit on the mod-id 
		// reduces crc32 to 31bits, but lets us use the modID as a guaranteed unique
		// replacement for appID's
		m_gameID.m_nModID = crc32 | (0x80000000);
	}

	CGameID( const char *pchExePath, const char *pchAppName )
	{
		m_ulGameID = 0;
		m_gameID.m_nAppID = 0;
		m_gameID.m_nType = k_EGameIDTypeShortcut;

		CRC32_t crc32;
		CRC32_Init( &crc32 );
		CRC32_ProcessBuffer( &crc32, pchExePath, Q_strlen( pchExePath ) );
		CRC32_ProcessBuffer( &crc32, pchAppName, Q_strlen( pchAppName ) );
		CRC32_Final( &crc32 );

		// set the high-bit on the mod-id 
		// reduces crc32 to 31bits, but lets us use the modID as a guaranteed unique
		// replacement for appID's
		m_gameID.m_nModID = crc32 | (0x80000000);
	}
#endif

	void SetAsShortcut()
	{
		m_gameID.m_nAppID = 0;
		m_gameID.m_nType = k_EGameIDTypeShortcut;
	}

	void SetAsP2PFile()
	{
		m_gameID.m_nAppID = 0;
		m_gameID.m_nType = k_EGameIDTypeP2P;
	}

	uint64 ToUint64() const
	{
		return m_ulGameID;
	}

	uint64 *GetUint64Ptr()
	{
		return &m_ulGameID;
	}

	bool IsMod() const
	{
		return ( m_gameID.m_nType == k_EGameIDTypeGameMod );
	}

	bool IsShortcut() const
	{
		return ( m_gameID.m_nType == k_EGameIDTypeShortcut );
	}

	bool IsP2PFile() const
	{
		return ( m_gameID.m_nType == k_EGameIDTypeP2P );
	}

	bool IsSteamApp() const
	{
		return ( m_gameID.m_nType == k_EGameIDTypeApp );
	}
		


	uint32 ModID() const
	{
		return m_gameID.m_nModID;
	}

	uint32 AppID() const
	{
		return m_gameID.m_nAppID;
	}

	bool operator == ( const CGameID &rhs ) const
	{
		return m_ulGameID == rhs.m_ulGameID;
	}

	bool operator != ( const CGameID &rhs ) const
	{
		return !(*this == rhs);
	}

	bool operator < ( const CGameID &rhs ) const
	{
		return ( m_ulGameID < rhs.m_ulGameID );
	}

	bool IsValid() const
	{
		return ( m_ulGameID != 0 );
	}

	void Reset() 
	{
		m_ulGameID = 0;
	}



private:
	enum EGameIDType
	{
		k_EGameIDTypeApp		= 0,
		k_EGameIDTypeGameMod	= 1,
		k_EGameIDTypeShortcut	= 2,
		k_EGameIDTypeP2P		= 3,
	};

	struct GameID_t
	{
		unsigned int m_nAppID : 24;
		unsigned int m_nType : 8;
		unsigned int m_nModID : 32;
	};

	union
	{
		uint64 m_ulGameID;
		GameID_t m_gameID;
	};
};

#pragma pack( pop )

const int k_cchGameExtraInfoMax = 64;


// Max number of credit cards stored for one account
const int k_nMaxNumCardsPerAccount = 1;

//-----------------------------------------------------------------------------
// Purpose: Base values for callback identifiers, each callback must
//			have a unique ID.
//-----------------------------------------------------------------------------
enum { k_iSteamUserCallbacks = 100 };
enum { k_iSteamGameServerCallbacks = 200 };
enum { k_iSteamFriendsCallbacks = 300 };
enum { k_iSteamBillingCallbacks = 400 };
enum { k_iSteamMatchmakingCallbacks = 500 };
enum { k_iSteamContentServerCallbacks = 600 };
enum { k_iSteamUtilsCallbacks = 700 };
enum { k_iClientFriendsCallbacks = 800 };
enum { k_iClientUserCallbacks = 900 };
enum { k_iSteamAppsCallbacks = 1000 };
enum { k_iSteamUserStatsCallbacks = 1100 };


//-----------------------------------------------------------------------------
// Constants used for query ports.
//-----------------------------------------------------------------------------

#define QUERY_PORT_NOT_INITIALIZED		0xFFFF	// We haven't asked the GS for this query port's actual value yet.
#define QUERY_PORT_ERROR				0xFFFE	// We were unable to get the query port for this server.

const unsigned char m_key[160] = {
		0x30, 0x81, 0x9D, 0x30, 0x0D, 0x06, 0x09, 0x2A, 0x86, 0x48, 0x86,
        0xF7, 0x0D, 0x01, 0x01, 0x01, 0x05, 0x00, 0x03, 0x81, 0x8B, 0x00,
        0x30, 0x81, 0x87, 0x02, 0x81, 0x81, 0x00, 0xC1, 0x7E, 0xE4, 0xCC,
        0x16, 0x61, 0xB4, 0x19, 0x1F, 0x6A, 0x88, 0xDA, 0x8D, 0xC9, 0x5F,
        0x68, 0x32, 0x53, 0x00, 0x7F, 0xF9, 0x46, 0x5B, 0x89, 0x10, 0xC6,
        0xCB, 0x30, 0xBD, 0x7B, 0x95, 0xD6, 0xB4, 0xBA, 0x52, 0xF1, 0x77,
        0x1F, 0x41, 0x2E, 0x10, 0x13, 0xF2, 0x12, 0x6E, 0x88, 0x45, 0x4D,
        0x97, 0x57, 0x5C, 0x78, 0x76, 0x44, 0xBE, 0xD2, 0xEB, 0x4A, 0xF2,
        0xD9, 0x04, 0x76, 0x72, 0x7D, 0xA2, 0x12, 0xB2, 0xAF, 0xB3, 0x3E,
        0x60, 0xE4, 0xE1, 0x17, 0x13, 0x78, 0xCA, 0x9F, 0x06, 0x08, 0x19,
        0x76, 0xEF, 0x89, 0x98, 0x5A, 0xDA, 0xB3, 0x03, 0xE8, 0x51, 0x33,
        0xB2, 0x34, 0x28, 0xA0, 0x96, 0x1F, 0x66, 0xE4, 0x99, 0xA2, 0x86,
        0x97, 0xE6, 0xEF, 0xE1, 0x5E, 0x81, 0xAF, 0xE8, 0x38, 0x02, 0xCE,
        0x61, 0x54, 0x7A, 0xC5, 0x95, 0x4B, 0x87, 0x6D, 0xA2, 0x46, 0xDF,
        0x19, 0x57, 0xE9, 0x02, 0x01, 0x11
};

enum EServerMode
{
	eServerModeNoAuthentication = 1,
	eServerModeAuthentication = 2,
	eServerModeAuthenticationAndSecure = 3,
};

static unsigned char m_encrypted[648] = {
	0x00,0x01,0x00,0x80,0x06,0x05,0xED,0x69,0x5E,
	0xA7,0x82,0x53,0x50,0x05,0x9D,0x10,0xC3,
	0x9F,0xC7,0x53,0x91,0x75,0xF8,0xE7,0x54,
	0x81,0x3D,0x14,0xF9,0x2A,0x1B,0xAD,0xC7,
0x29,
0x45,
0x6,
0x12,
0x25,
0x10,
0x4C,
0x90,
0xA2,
0xE4,
0xD6,
0xD,
0x8A,
0xC1,
0xCA,
0x70,
0x8A,
0xCA,
0x4A,
0x7B,
0xDB,
0x5,
0x4,
0xE2,
0x3C,
0xA,
0x83,
0xA4,
0xC9,
0x7F,
0x9B,
0x33,
0xD7,
0xBC,
0x40,
0x49,
0x2A,
0xD0,
0x27,
0x3D,
0x2A,
0x6A,
0x30,
0xFA,
0x8C,
0xEB,
0xD2,
0x19,
0xF6,
0xAE,
0xBF,
0xD7,
0x25,
0xA3,
0x60,
0x8E,
0x36,
0xFB,
0x87,
0x9F,
0x4F,
0xB1,
0x41,
0x66,
0x3F,
0x56,
0x1B,
0x1E,
0xAB,
0x35,
0xC,
0x92,
0xB8,
0x63,
0xAB,
0x11,
0xAB,
0x68,
0xA1,
0xB1,
0xDD,
0x2C,
0x8C,
0x7E,
0x78,
0xAD,
0x8F,
0x62,
0x94,
0xBE,
0xDF,
0xA7,
0xC8,
0xF4,
0x1F,
0x67,
0x9A,
0x71,
0x7A,
0xE8,
0xC3,
0x4F,
0xAB,
0xC1,
0x7,
0xBD,
0x7E,
0xD,
0x44,
0xE0,
0xBD,
0x27,
0xA0,
0xD4,
0x65,
0x1,
0xEF,
0x1,
0xF0,
0xD0,
0x13,
0xB1,
0x9,
0xBB,
0x32,
0x71,
0x81,
0xDB,
0xBD,
0xB3,
0x6C,
0x6C,
0xA7,
0xF2,
0xA7,
0x31,
0x2A,
0xF1,
0x1A,
0x36,
0xAE,
0x4E,
0xC8,
0x20,
0x40,
0x52,
0xF7,
0x6D,
0x5E,
0xA6,
0x25,
0x1,
0x35,
0xB6,
0x8E,
0x46,
0x75,
0xB2,
0xAF,
0x11,
0xF8,
0x63,
0xE4,
0xC9,
0x80,
0x7,
0xC9,
0xAD,
0xDF,
0xAE,
0x27,
0x8F,
0x5F,
0xFF,
0xF0,
0x65,
0x1E,
0x5D,
0x5F,
0x2E,
0x59,
0xC2,
0x13,
0x94,
0x7A,
0x53,
0xA6,
0xE0,
0x8D,
0xAB,
0x9E,
0x3F,
0x8D,
0x76,
0x40,
0xB2,
0x25,
0x7B,
0x2A,
0x99,
0x7,
0x5B,
0xBE,
0xA1,
0xD9,
0xCE,
0x33,
0x21,
0xC2,
0x2A,
0x26,
0x99,
0x14,
0x66,
0xD1,
0xF6,
0x38,
0x93,
0x93,
0x0,
0x92,
0xCF,
0xE0,
0x4B,
0x42,
0x4,
0x9B,
0xB7,
0xCD,
0x75,
0xC2,
0xE,
0x94,
0x8C,
0xB3,
0xD3,
0x10,
0x52,
0x72,
0x19,
0x6F,
0x6C,
0xD8,
0x69,
0x3,
0xD2,
0x95,
0x71,
0xA9,
0xBC,
0x2E,
0x8,
0x94,
0xB5,
0x23,
0x42,
0xF5,
0xEC,
0x7F,
0x2A,
0xAC,
0x46,
0x29,
0xE4,
0x98,
0xD,
0x8A,
0x8A,
0x1C,
0xEC,
0x49,
0x4B,
0x7,
0xAA,
0xE6,
0x97,
0xCF,
0x19,
0x39,
0x51,
0x12,
0x7C,
0x9F,
0xB5,
0xEC,
0x72,
0xBC,
0xE5,
0xAF,
0x29,
0x7B,
0x8A,
0xC,
0xA3,
0xAE,
0x9,
0x84,
0x65,
0xF7,
0xFC,
0xFC,
0x8D,
0x8D,
0x3E,
0x18,
0x38,
0x44,
0xA8,
0xD3,
0x6C,
0xF4,
0xA,
0x81,
0xC3,
0xB2,
0x79,
0xBF,
0x26,
0xC3,
0x61,
0x2F,
0xB1,
0x1C,
0x42,
0xC7,
0x73,
0xAC,
0x45,
0x6D,
0x51,
0x7B,
0xDB,
0xE8,
0x33,
0x23,
0x27,
0x17,
0x3D,
0xE0,
0x80,
0x61,
0x65,
0x94,
0xDC,
0xBC,
0x42,
0x64,
0x73,
0xDD,
0x2F,
0xAB,
0xFC,
0xEF,
0x36,
0xEA,
0x3B,
0x72,
0x51,
0x6D,
0x89,
0xF0,
0x38,
0xFA,
0xD2,
0x4A,
0x9E,
0x5A,
0x9A,
0xC6,
0x21,
0x68,
0x2F,
0x69,
0xCB,
0x60,
0xC0,
0x89,
0x86,
0x9,
0x7D,
0xCB,
0xF0,
0xE3,
0xD,
0xB9,
0x13,
0xEA,
0x87,
0x43,
0x41,
0x1A,
0x69,
0xA1,
0xCF,
0xC5,
0xA0,
0x85,
0x8C,
0x9C,
0x4C,
0xFE,
0x86,
0x18,
0x3,
0x89,
0xB,
0x4,
0xC7,
0x39,
0x63,
0xFA,
0x2,
0x1B,
0x19,
0xBC,
0x8A,
0x1B,
0x75,
0x2A,
0x80,
0x46,
0x60,
0x43,
0xA5,
0xB0,
0xE4,
0xAE,
0xE8,
0x29,
0x41,
0x3F,
0xE4,
0x3A,
0x6,
0x2C,
0x9,
0x74,
0x44,
0x97,
0xC0,
0xCE,
0x98,
0xCA,
0xE1,
0x88,
0x67,
0x5C,
0x85,
0x59,
0xE8,
0x13,
0x84,
0x34,
0x45,
0x51,
0x1D,
0xF4,
0xA0,
0x49,
0x96,
0x42,
0xF1,
0xE6,
0x3B,
0x50,
0x57,
0xA2,
0x75,
0x7B,
0x26,
0xF,
0xE8,
0xB6,
0x81,
0xC9,
0xD8,
0x25,
0x71,
0x99,
0x0A,
0x43,
0xE2,
0xD9,
0x57,
0x99,
0x29,
0xBD,
0x01,
0x19,
0x78,
0x92,
0xCB,
0x9C,
0xBF,
0x8F,
0x3A,
0xF5,
0x28,
0x32,
0xE6,
0xDB,
0xF6,
0x5C,
0xEB,
0xF5,
0x5E,
0xA2,
0x20,
0x95,
0x84,
0x52,
0x79,
0x1A,
0xD1,
0xB,
0xD5,
0x80,
0x48,
0x50,
0x4B,
0x62,
0xFA,
0x75,
0x4A,
0x54,
0x7E,
0x9D,
0xC3,
0x22,
0x28,
0x06,
0x65,
0x52,
0x19,
0x06,
0x85,
0xCE,
0x1F,
0x6D,
0xA5,
0x79,
0x56,
0xAF,
0xF3,
0xCB,
0xB0,
0xF3,
0x84,
0xC1,
0x8A,
0x82,
0xCB,
0xAA,
0x51,
0x31,
0x54,
0x1C,
0xBA,
0xFD,
0xE9,
0x2B,
0x88,
0x32,
0x25,
0x4E,
0x18,
0x45,
0x0B,
0x18,
0xD7,
0x66,
0x45,
0xAF,
0xC,
0x24,
0x53,
0xAA,
0xD1,
0x4C,
0x3D,
0xBB,
0x6E,
0x72,
0xDC,
0xCD,
0x7B,
0xE3,
0x70,
0x21,
0xF7,
0x8E,
0x15,
0x88,
0x3A,
0x75,
0x34,
0x84,
0x74,
0x9E,
0x3E,
0xBE,
0xF0,
0x17,
0xF1,
0x39,
0xD2,
0x9E,
0x23,
0x53,
0xC5,
0xEF,
0x74,
0x3B,
0x7A,
0xDE
};

struct CTicket
{
	unsigned int m_Version;
	unsigned int m_UserID;
	unsigned int m_Signature;
};

#endif // STEAMCLIENTPUBLIC_H
