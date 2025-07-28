
//*********** (C) Copyright 2002 Valve, L.L.C. All rights reserved. ***********
//
// The copyright to the contents herein is the property of Valve, L.L.C.
// The contents may be used and/or copied only with the written permission of
// Valve, L.L.C., or in accordance with the terms and conditions stipulated in
// the agreement/contract under which the contents have been supplied.
//
//*****************************************************************************
//
// Contents:
//
//		SteamUserID types.
//
//		This file is distributed to Steam application developers.
//
// Authors:	
//
// Target restrictions:
//
// Tool restrictions:
//
// Things to do:
//
//		
//
//*****************************************************************************

#ifndef INCLUDED_STEAM_COMMON_STEAMCOMMON_H
#define INCLUDED_STEAM_COMMON_STEAMCOMMON_H

#pragma once

#if defined(__x86_64__) || defined(_WIN64)
	#define X64BITS
#endif

typedef unsigned char uint8;
typedef signed char int8;

#if defined( _MSC_VER )

	typedef __int16 int16;
	typedef unsigned __int16 uint16;
	typedef __int32 int32;
	typedef unsigned __int32 uint32;
	typedef __int64 int64;
	typedef unsigned __int64 uint64;

	#ifdef X64BITS
		typedef __int64 intp;				// intp is an integer that can accomodate a pointer
		typedef unsigned __int64 uintp;		// (ie, sizeof(intp) >= sizeof(int) && sizeof(intp) >= sizeof(void *)
	#else
		typedef __int32 intp;
		typedef unsigned __int32 uintp;
	#endif

#else // _MSV_VER

	typedef short int16;
	typedef unsigned short uint16;
	typedef int int32;
	typedef unsigned int uint32;
	typedef long long int64;
	typedef unsigned long long uint64;
	#ifdef X64BITS
		typedef long long intp;
		typedef unsigned long long uintp;
	#else
		typedef int intp;
		typedef unsigned int uintp;
	#endif

#endif // else _MSC_VER

#ifdef __cplusplus
extern "C"
{
#endif

/* Applications should not define STEAM_EXPORTS. */

#if defined ( WIN32 )

#ifdef STEAM_EXPORTS
#define STEAM_API __declspec(dllexport)
#else
#define STEAM_API __declspec(dllimport)
#endif

#define STEAM_CALL __cdecl

#else

#define STEAM_API /* */
#define STEAM_CALL /* */

#endif


/******************************************************************************
**
** Exported macros and constants
**
******************************************************************************/

#define STEAM_USING_FILESYSTEM							(0x00000001)
#define STEAM_USING_LOGGING								(0x00000002)
#define STEAM_USING_USERID								(0x00000004)
#define STEAM_USING_ACCOUNT								(0x00000008)
#define STEAM_USING_ALL									(0x0000000f)
#define STEAM_MAX_PATH									(255)
#define STEAM_QUESTION_MAXLEN							(255)
#define STEAM_SALT_SIZE									(8)

#define STEAM_DATE_SIZE									(9)
#define STEAM_TIME_SIZE									(9)
#define STEAM_CARD_NUMBER_SIZE							(17)
#define STEAM_CONFIRMATION_CODE_SIZE					(16)
#define STEAM_CARD_HOLDERNAME_SIZE						(100)
#define STEAM_CARD_APPROVAL_CODE_SIZE					(100)
#define STEAM_CARD_EXPYEAR_SIZE							(4)
#define STEAM_CARD_LASTFOURDIGITS_SIZE					(4)
#define STEAM_CARD_EXPMONTH_SIZE						(2)
#define STEAM_CARD_CVV2_SIZE							(5)
#define STEAM_BILLING_ADDRESS1_SIZE						(128)
#define STEAM_BILLING_ADDRESS2_SIZE						(128)
#define STEAM_BILLING_CITY_SIZE							(50)
#define STEAM_BILLING_ZIP_SIZE							(16)
#define STEAM_BILLING_STATE_SIZE						(32)
#define STEAM_BILLING_COUNTRY_SIZE						(32)
#define STEAM_BILLING_PHONE_SIZE						(20)
#define STEAM_BILLING_EMAIL_SIZE						(100)
#define STEAM_TYPE_OF_PROOF_OF_PURCHASE_SIZE			(20)
#define STEAM_PROOF_OF_PURCHASE_TOKEN_SIZE				(200)
#define STEAM_EXTERNAL_ACCOUNTNAME_SIZE					(100)
#define STEAM_EXTERNAL_ACCOUNTPASSWORD_SIZE				(80)

/******************************************************************************
**
** Scalar type and enumerated type definitions.
**
******************************************************************************/

typedef unsigned int SteamHandle_t;

typedef void * SteamUserIDTicketValidationHandle_t;

typedef unsigned int SteamCallHandle_t;

#if defined(_MSC_VER)
	typedef __int64				SteamSigned64_t;
	typedef unsigned __int64	SteamUnsigned64_t;
#else
	typedef long long			SteamSigned64_t;
	typedef unsigned long long	SteamUnsigned64_t;
#endif

enum ESteamSeekMethod
{
	eSteamSeekMethodSet = 0,
	eSteamSeekMethodCur = 1,
	eSteamSeekMethodEnd = 2
};

enum ESteamBufferMethod
{
	eSteamBufferMethodFBF = 0,
	eSteamBufferMethodNBF = 1
};

enum ESteamError
{
	eSteamErrorNone													= 0,
	eSteamErrorUnknown												= 1,
	eSteamErrorLibraryNotInitialized								= 2,
	eSteamErrorLibraryAlreadyInitialized							= 3,
	eSteamErrorConfig												= 4,
	eSteamErrorContentServerConnect									= 5,
	eSteamErrorBadHandle											= 6,
	eSteamErrorHandlesExhausted										= 7,
	eSteamErrorBadArg												= 8,
	eSteamErrorNotFound												= 9,
	eSteamErrorRead													= 10,
	eSteamErrorEOF													= 11,
	eSteamErrorSeek													= 12,
	eSteamErrorCannotWriteNonUserConfigFile							= 13,
	eSteamErrorCacheOpen											= 14,
	eSteamErrorCacheRead											= 15,
	eSteamErrorCacheCorrupted										= 16,
	eSteamErrorCacheWrite											= 17,
	eSteamErrorCacheSession											= 18,
	eSteamErrorCacheInternal										= 19,
	eSteamErrorCacheBadApp											= 20,
	eSteamErrorCacheVersion											= 21,
	eSteamErrorCacheBadFingerPrint									= 22,

	eSteamErrorNotFinishedProcessing								= 23,
	eSteamErrorNothingToDo											= 24,
	eSteamErrorCorruptEncryptedUserIDTicket							= 25,
	eSteamErrorSocketLibraryNotInitialized							= 26,
	eSteamErrorFailedToConnectToUserIDTicketValidationServer		= 27,
	eSteamErrorBadProtocolVersion									= 28,
	eSteamErrorReplayedUserIDTicketFromClient						= 29,
	eSteamErrorReceiveResultBufferTooSmall							= 30,
	eSteamErrorSendFailed											= 31,
	eSteamErrorReceiveFailed										= 32,
	eSteamErrorReplayedReplyFromUserIDTicketValidationServer		= 33,
	eSteamErrorBadSignatureFromUserIDTicketValidationServer			= 34,
	eSteamErrorValidationStalledSoAborted							= 35,
	eSteamErrorInvalidUserIDTicket									= 36,
	eSteamErrorClientLoginRateTooHigh								= 37,
	eSteamErrorClientWasNeverValidated								= 38,
	eSteamErrorInternalSendBufferTooSmall							= 39,
	eSteamErrorInternalReceiveBufferTooSmall						= 40,
	eSteamErrorUserTicketExpired									= 41,
	eSteamErrorCDKeyAlreadyInUseOnAnotherClient						= 42,

	eSteamErrorNotLoggedIn											= 101,
	eSteamErrorAlreadyExists										= 102,
	eSteamErrorAlreadySubscribed									= 103,
	eSteamErrorNotSubscribed										= 104,
	eSteamErrorAccessDenied											= 105,
	eSteamErrorFailedToCreateCacheFile								= 106,
	eSteamErrorCallStalledSoAborted									= 107,
	eSteamErrorEngineNotRunning										= 108,
	eSteamErrorEngineConnectionLost									= 109,
	eSteamErrorLoginFailed											= 110,
	eSteamErrorAccountPending										= 111,
	eSteamErrorCacheWasMissingRetry									= 112,
	eSteamErrorLocalTimeIncorrect									= 113,
	eSteamErrorCacheNeedsDecryption									= 114,
	eSteamErrorAccountDisabled										= 115,
	eSteamErrorCacheNeedsRepair										= 116,
	eSteamErrorRebootRequired										= 117,

	eSteamErrorNetwork												= 200,
	eSteamErrorOffline												= 201

};

enum ESteamAppUpdateStatsQueryType
{
	ePhysicalBytesReceivedThisSession	= 1,
	eAppReadyToLaunchStatus				= 2,
	eAppPreloadStatus					= 3,
	eAppEntireDepot						= 4,
	eCacheBytesPresent					= 5,
};

enum ESteamServerType
{
	eSteamValveCDKeyValidationServer,
	eSteamHalfLifeMasterServer,
	eSteamFriendsServer,
	eSteamCSERServer,
	eSteamHalfLife2MasterServer,
	eSteamRDKFMasterServer,
	eMaxServerTypes
};

enum EDetailedPlatformErrorType
{
	eNoDetailedErrorAvailable,
	eStandardCerrno,
	eWin32LastError,
	eWinSockLastError,
	eDetailedPlatformErrorCount
};

enum ESteamFindFilter		/* Filter elements returned by SteamFind{First,Next} */
{
	eSteamFindLocalOnly,			/* limit search to local filesystem */
	eSteamFindRemoteOnly,			/* limit search to remote repository */
	eSteamFindAll					/* do not limit search (duplicates allowed) */
};

enum EBillingType
{
	eNoCost,
	eBillOnceOnly,
	eBillMonthly,
	eProofOfPrepurchaseOnly,
	eGuestPass,
	eHardwarePromo,
	eGift,
	eNumBillingTypes
};

/******************************************************************************
**
** Exported structure and complex type definitions.
**
******************************************************************************/


struct TSteamError
{
	ESteamError eSteamError;
	EDetailedPlatformErrorType eDetailedErrorType;
	int nDetailedErrorCode;
	char szDesc[STEAM_MAX_PATH];
};



struct TSteamElemInfo
{
	int bIsDir;						/* If non-zero, element is a directory; if zero, element is a file */
	unsigned int uSizeOrCount;		/* If element is a file, this contains size of file in bytes */
	int bIsLocal;					/* If non-zero, reported item is a standalone element on local filesystem */
	char cszName[STEAM_MAX_PATH];	/* Base element name (no path) */
	long lLastAccessTime;			/* Seconds since 1/1/1970 (like time_t) when element was last accessed */
	long lLastModificationTime;		/* Seconds since 1/1/1970 (like time_t) when element was last modified */
	long lCreationTime;				/* Seconds since 1/1/1970 (like time_t) when element was created */
};


struct TSteamSubscriptionStats
{
	unsigned int uNumSubscriptions;
	unsigned int uMaxNameChars;
	unsigned int uMaxApps;
};


typedef struct 
{
	unsigned int AppId;
	unsigned int IsRequired;
	char szMountName[STEAM_MAX_PATH];
} TSteamAppDependencyInfo;

struct TSteamAppStats
{
	unsigned int uNumApps;
	unsigned int uMaxNameChars;
	unsigned int uMaxVersionLabelChars;
	unsigned int uMaxLaunchOptions;
	unsigned int uMaxLaunchOptionDescChars;
	unsigned int uMaxLaunchOptionCmdLineChars;
	unsigned int uMaxNumIcons;
	unsigned int uMaxIconSize;
	unsigned int uMaxDependencies;
};

struct TSteamAppVersion
{
	char *szLabel;
	unsigned int uMaxLabelChars;
	unsigned int uVersionId;
	int bIsNotAvailable;
};

struct TSteamAppLaunchOption
{
	char *szDesc;
	unsigned int uMaxDescChars;
	char *szCmdLine;
	unsigned int uMaxCmdLineChars;
	unsigned int uIndex;
	int iIconIndex;
	int bNoDesktopShortcut;
	int bNoStartMenuShortcut;
	int bIsLongRunningUnattended;
};


struct TSteamApp
{
	char *szName;
	unsigned int uMaxNameChars;
	char *szLatestVersionLabel;
	unsigned int uMaxLatestVersionLabelChars;
	char *szCurrentVersionLabel;
	unsigned int uMaxCurrentVersionLabelChars;
	char *szCacheFile;
	unsigned int uMaxCacheFileChars;
	unsigned int uId;
	unsigned int uLatestVersionId;
	unsigned int uCurrentVersionId;
	unsigned int uMinCacheFileSizeMB;
	unsigned int uMaxCacheFileSizeMB;
	unsigned int uNumLaunchOptions;
	unsigned int uNumIcons;
	unsigned int uNumVersions;
	unsigned int uNumDependencies;
};

struct TSteamSubscription
{
	char* szName;
	unsigned int uMaxNameChars;
	unsigned int* puAppIds;
	unsigned int uMaxAppIds;
	unsigned int uId;
	unsigned int uNumApps;
	EBillingType eBillingType;
	unsigned int uCostInCents;
	unsigned int uNumDiscounts;
	int bIsPreorder;
	int bRequiresShippingAddress;
	unsigned int uDomesticShippingCostInCents;
	unsigned int uInternationalShippingCostInCents;
	bool bIsCyberCafeSubscription;
	unsigned int uGameCode;
	char szGameCodeDesc[STEAM_MAX_PATH];
	bool bIsDisabled;
	bool bRequiresCD;
	unsigned int uTerritoryCode;
	bool IsSteam3Subscription;
};

struct TSteamSubscriptionDiscount
{
	char szName[STEAM_MAX_PATH];
	unsigned int uDiscountInCents;
	unsigned int uNumQualifiers;
};

struct TSteamDiscountQualifier
{
	char szName[STEAM_MAX_PATH];
	unsigned int uRequiredSubscription;
	int bIsDisqualifier;
};

struct TSteamProgress
{
	int bValid;                      // non-zero if call provides progress info
	unsigned int uPercentDone;       // 0 to 100 if bValid
	char szProgress[STEAM_MAX_PATH]; // additional progress info
};

struct TSteamOfflineStatus
{
	int eOfflineNow;
	int eOfflineNextSession;
};

enum ESteamNotificationCallbackEvent
{
	eSteamNotifyTicketsWillExpire,
	eSteamNotifyAccountInfoChanged,
	eSteamNotifyContentDescriptionChanged,
	eSteamNotifyPleaseShutdown,
	eSteamNotifyNewSponsorUrl,
	eSteamNotifyAppVersionChanged
};

typedef void(*AddEntryToKeyValueFn)(const char* cszKeyName, const char* cszKeyValue, void* pvCKeyValue);
typedef void(*SteamNotificationCallback_t)(ESteamNotificationCallbackEvent eEvent, unsigned int nData);


typedef char SteamPersonalQuestion_t[ STEAM_QUESTION_MAXLEN + 1 ];

struct SteamSalt_t
{
	unsigned char uchSalt[STEAM_SALT_SIZE];
};

enum ESteamPaymentCardType
{
	eVisa				= 1,
	eMaster				= 2,
	eAmericanExpress	= 3,
	eDiscover			= 4,
	eDinnersClub		= 5,
	eJCB				= 6
};

struct TSteamPaymentCardInfo
{
	ESteamPaymentCardType eCardType;
	char szCardNumber[ STEAM_CARD_NUMBER_SIZE +1 ];
	char szCardHolderName[ STEAM_CARD_HOLDERNAME_SIZE + 1];
	char szCardExpYear[ STEAM_CARD_EXPYEAR_SIZE + 1 ];
	char szCardExpMonth[ STEAM_CARD_EXPMONTH_SIZE+ 1 ];
	char szCardCVV2[ STEAM_CARD_CVV2_SIZE + 1 ];
	char szBillingAddress1[ STEAM_BILLING_ADDRESS1_SIZE + 1 ];
	char szBillingAddress2[ STEAM_BILLING_ADDRESS2_SIZE + 1 ];
	char szBillingCity[ STEAM_BILLING_CITY_SIZE + 1 ];
	char szBillingZip[ STEAM_BILLING_ZIP_SIZE + 1 ];
	char szBillingState[ STEAM_BILLING_STATE_SIZE + 1 ];
	char szBillingCountry[ STEAM_BILLING_COUNTRY_SIZE + 1 ];
	char szBillingPhone[ STEAM_BILLING_PHONE_SIZE + 1 ];
	char szBillingEmailAddress[ STEAM_BILLING_EMAIL_SIZE + 1 ];
	unsigned int uExpectedCostInCents;
	unsigned int uExpectedTaxInCents;
	char szShippingName[ STEAM_CARD_HOLDERNAME_SIZE + 1];
	char szShippingAddress1[ STEAM_BILLING_ADDRESS1_SIZE + 1 ];
	char szShippingAddress2[ STEAM_BILLING_ADDRESS2_SIZE + 1 ];
	char szShippingCity[ STEAM_BILLING_CITY_SIZE + 1 ];
	char szShippingZip[ STEAM_BILLING_ZIP_SIZE + 1 ];
	char szShippingState[ STEAM_BILLING_STATE_SIZE + 1 ];
	char szShippingCountry[ STEAM_BILLING_COUNTRY_SIZE + 1 ];
	char szShippingPhone[ STEAM_BILLING_PHONE_SIZE + 1 ];
	unsigned int uExpectedShippingCostInCents;

};

struct TSteamPrepurchaseInfo
{
	char					szTypeOfProofOfPurchase[ STEAM_TYPE_OF_PROOF_OF_PURCHASE_SIZE + 1 ];

	// A ProofOfPurchase token is not necessarily a nul-terminated string; it may be binary data
	// (perhaps encrypted). Hence we need a length and an array of bytes.
	unsigned int			uLengthOfBinaryProofOfPurchaseToken;	
	char					cBinaryProofOfPurchaseToken[ STEAM_PROOF_OF_PURCHASE_TOKEN_SIZE + 1 ];
};

struct TSteamExternalBillingInfo
{
	char szAccountName[ STEAM_EXTERNAL_ACCOUNTNAME_SIZE + 1 ];
	char szPassword[ STEAM_EXTERNAL_ACCOUNTPASSWORD_SIZE + 1 ];
};

enum ESteamSubscriptionStatus
{
	eSteamSubscriptionOK,
	eSteamSubscriptionPending,
	eSteamSubscriptionPreorder,
	eSteamSubscriptionPrepurchaseTransferred,
	eSteamSubscriptionPrepurchaseInvalid,
	eSteamSubscriptionPrepurchaseRejected,
	eSteamSubscriptionPrepurchaseRevoked,
	eSteamSubscriptionPaymentCardDeclined,
	eSteamSubscriptionCancelledByUser,
	eSteamSubscriptionCancelledByVendor,
	eSteamSubscriptionPaymentCardUseLimit,
	eSteamSubscriptionPaymentCardAlert,
	eSteamSubscriptionFailed,
	eSteamSubscriptionPaymentCardAVSFailure,
	eSteamSubscriptionPaymentCardInsufficientFunds,
	eSteamSubscriptionRestrictedCountry
};

enum ESteamSubscriptionBillingInfoType
{
	ePaymentCardInfo		= 1,
	ePrepurchasedInfo		= 2,
	eAccountBillingInfo		= 3,
	eExternalBillingInfo	= 4		// indirect billing via ISP etc (not supported yet)
};

struct TSteamSubscriptionBillingInfo
{
	ESteamSubscriptionBillingInfoType	eBillingInfoType;
	union {
		TSteamPaymentCardInfo			PaymentCardInfo;
		TSteamPrepurchaseInfo			PrepurchaseInfo;
		TSteamExternalBillingInfo		ExternalBillingInfo;
		char							bUseAccountBillingInfo;
	};

};

struct TSteamPaymentCardReceiptInfo
{
	ESteamPaymentCardType eCardType;
	char szCardLastFourDigits[ STEAM_CARD_LASTFOURDIGITS_SIZE + 1 ];
	char szCardHolderName[ STEAM_CARD_HOLDERNAME_SIZE + 1 ];
	char szBillingAddress1[ STEAM_BILLING_ADDRESS1_SIZE + 1 ];
	char szBillingAddress2[ STEAM_BILLING_ADDRESS2_SIZE + 1 ];
	char szBillingCity[ STEAM_BILLING_CITY_SIZE + 1 ];
	char szBillingZip[ STEAM_BILLING_ZIP_SIZE + 1 ];
	char szBillingState[ STEAM_BILLING_STATE_SIZE + 1 ];
	char szBillingCountry[ STEAM_BILLING_COUNTRY_SIZE + 1 ];
	char szCardApprovalCode[ STEAM_CARD_APPROVAL_CODE_SIZE + 1 ];
	char szTransDate[ STEAM_DATE_SIZE + 1 ];
	char szTransTime[ STEAM_TIME_SIZE + 1 ];
	unsigned int uPriceWithoutTax;
	unsigned int uTaxAmount;
	unsigned int uShippingCost;
};

struct TSteamPrepurchaseReceiptInfo
{
	char szTypeOfProofOfPurchase[ STEAM_TYPE_OF_PROOF_OF_PURCHASE_SIZE + 1 ];
};

struct TSteamSubscriptionReceipt
{
	ESteamSubscriptionStatus eStatus;
	ESteamSubscriptionStatus ePreviousStatus;
	ESteamSubscriptionBillingInfoType eReceiptInfoType;
	char szConfirmationCode[ STEAM_CONFIRMATION_CODE_SIZE + 1 ];
	union
	{
		TSteamPaymentCardReceiptInfo PaymentCardReceiptInfo;
		TSteamPrepurchaseReceiptInfo PrepurchaseReceiptInfo;
	};
};

struct TSteamUpdateStats
{
	SteamUnsigned64_t uBytesTotal;
	SteamUnsigned64_t uBytesPresent;
};

/******************************************************************************
**
** More exported constants
**
******************************************************************************/


#ifdef __cplusplus

const SteamHandle_t										STEAM_INVALID_HANDLE = 0;
const SteamCallHandle_t									STEAM_INVALID_CALL_HANDLE = 0;
const SteamUserIDTicketValidationHandle_t				STEAM_INACTIVE_USERIDTICKET_VALIDATION_HANDLE = 0;
const unsigned int										STEAM_USE_LATEST_VERSION = 0xFFFFFFFF;

#else

#define STEAM_INVALID_HANDLE							((SteamHandle_t)(0))
#define STEAM_INVALID_CALL_HANDLE						((SteamCallHandle_t)(0))
#define	STEAM_INACTIVE_USERIDTICKET_VALIDATION_HANDLE	((SteamUserIDTicketValidationHandle_t)(0))
#define STEAM_USE_LATEST_VERSION						(0xFFFFFFFFu);

#endif


// Each Steam instance (licensed Steam Service Provider) has a unique SteamInstanceID_t.
//
// Each Steam instance as its own DB of users.
// Each user in the DB has a unique SteamLocalUserID_t (a serial number, with possible 
// rare gaps in the sequence).

typedef	unsigned short		SteamInstanceID_t;		// MUST be 16 bits


#if defined ( WIN32 )
typedef	unsigned __int64	SteamLocalUserID_t;		// MUST be 64 bits
#else
typedef	unsigned long long	SteamLocalUserID_t;		// MUST be 64 bits
#endif


// Applications need to be able to authenticate Steam users from ANY instance.
// So a SteamIDTicket contains SteamGlobalUserID, which is a unique combination of 
// instance and user id.

// SteamLocalUserID is an unsigned 64-bit integer.
// For platforms without 64-bit int support, we provide access via a union that splits it into 
// high and low unsigned 32-bit ints.  Such platforms will only need to compare LocalUserIDs 
// for equivalence anyway - not perform arithmetic with them.
struct __declspec(align(8)) TSteamSplitLocalUserID
{
	unsigned int	Low32bits;
	unsigned int	High32bits;
};

struct __declspec(align(8)) TSteamGlobalUserID
{
	SteamInstanceID_t		m_SteamInstanceID;

	union
	{
		SteamLocalUserID_t		As64bits;
		TSteamSplitLocalUserID	Split;
	} m_SteamLocalUserID;

};

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

enum EAccountType
{
	k_EAccountTypeInvalid = 0,			
	k_EAccountTypeIndividual = 1,		// single user account
	k_EAccountTypeMultiseat = 2,		// multiseat (e.g. cybercafe) account
	k_EAccountTypeGameServer = 3,		// game server account
	k_EAccountTypeAnonGameServer = 4,	// anonomous game server account
	k_EAccountTypePending = 5			// pending
};

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
 
	//-----------------------------------------------------------------------------
	// Purpose: Initializes a steam ID from a Steam2 ID structure
	// Input:	pTSteamGlobalUserID -	Steam2 ID to convert
	//			eUniverse -				universe this ID belongs to
	//-----------------------------------------------------------------------------
	void SetFromSteam2( TSteamGlobalUserID *pTSteamGlobalUserID, EUniverse eUniverse )
	{
		m_unAccountID = pTSteamGlobalUserID->m_SteamLocalUserID.Split.Low32bits * 2 + 
			pTSteamGlobalUserID->m_SteamLocalUserID.Split.High32bits;
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
		pTSteamGlobalUserID->m_SteamLocalUserID.Split.High32bits = m_unAccountID % 2;
		pTSteamGlobalUserID->m_SteamLocalUserID.Split.Low32bits = m_unAccountID / 2;
	}

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
	// Purpose: create an anonomous game server login to be filled in by the AM
	//-----------------------------------------------------------------------------
	void CreateBlankAnonLogon( EUniverse eUniverse )
	{
		m_unAccountID = 0;
		m_EAccountType = k_EAccountTypeAnonGameServer;
		m_EUniverse = eUniverse;
		m_unAccountInstance = 0;
	}

	//-----------------------------------------------------------------------------
	// Purpose: Is this an anonomous game server login that will be filled in?
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

	// simple accessors
	void SetAccountID( uint32 unAccountID )		{ m_unAccountID = unAccountID; }
	uint32 GetAccountID() const					{ return m_unAccountID; }
	uint32 GetUnAccountInstance() const			{ return m_unAccountInstance; }
	EAccountType GetEAccountType() const		{ return m_EAccountType; }
	EUniverse GetEUniverse() const				{ return m_EUniverse; }
	void SetEUniverse( EUniverse eUniverse )	{ m_EUniverse = eUniverse; }
	bool IsValid() const						{ return !( m_EAccountType == k_EAccountTypeInvalid ); }

	// this set of functions is hidden, will be moved out of class
	CSteamID( const char *pchSteamID, EUniverse eDefaultUniverse = k_EUniverseInvalid );
	char * Render() const;				// renders this steam ID to string
	static char * Render( uint64 ulSteamID );	// static method to render a uint64 representation of a steam ID to a string

	void SetFromString( const char *pchSteamID, EUniverse eDefaultUniverse );
	bool SetFromSteam2String( const char *pchSteam2ID, EUniverse eUniverse );

	bool operator==( const CSteamID &val ) const { return ( ( val.m_unAccountID == m_unAccountID ) && ( val.m_unAccountInstance == m_unAccountInstance )
													&& ( val.m_EAccountType == m_EAccountType ) &&  ( val.m_EUniverse == m_EUniverse ) ); } 
	bool operator!=( const CSteamID &val ) const { return !operator==( val ); }

	// DEBUG function
	bool BValidExternalSteamID() const;

private:

	// These are defined here to prevent accidental implicit conversion of a u32AccountID to a CSteamID.
	// If you get a compiler error about an ambiguous constructor/function then it may be because you're
	// passing a 32-bit int to a function that takes a CSteamID. You should explicitly create the SteamID
	// using the correct Universe and account Type/Instance values.
	CSteamID( uint32 );
	CSteamID( int32 );

	// 64 bits total
	uint32				m_unAccountID : 32;			// unique account identifier
	unsigned int		m_unAccountInstance : 20;	// dynamic instance ID (used for multiseat type accounts only)
	EAccountType		m_EAccountType : 4;			// type of account
	EUniverse			m_EUniverse : 8;			// universe this account belongs to
};

const int k_unSteamAccountIDMask = 0xFFFFFFFF;
const int k_unSteamAccountInstanceMask = 0x000FFFFF;

#ifdef __cplusplus
}
#endif

#endif
