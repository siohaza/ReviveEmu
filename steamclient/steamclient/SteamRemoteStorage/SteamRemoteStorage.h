/*
`vtable for'CAdapterSteamRemoteStorage
_ZN26CAdapterSteamRemoteStorage9FileWriteEPKcPKvi ; CAdapterSteamRemoteStorage::FileWrite(char  const*,void  const*,int)
_ZN26CAdapterSteamRemoteStorage11GetFileSizeEPKc
_ZN26CAdapterSteamRemoteStorage8FileReadEPKcPvi
_ZN26CAdapterSteamRemoteStorage10FileExistsEPKc
_ZN26CAdapterSteamRemoteStorage10FileDeleteEPKc
_ZN26CAdapterSteamRemoteStorage12GetFileCountEv
_ZN26CAdapterSteamRemoteStorage18GetFileNameAndSizeEiPi
_ZN26CAdapterSteamRemoteStorage8GetQuotaEPiS0_
*/

class CSteamRemoteStorage
{
public:
	CSteamRemoteStorage();
	~CSteamRemoteStorage();

	virtual void FileWrite(char  const* pchFileName, void  const* pvData, int iBytes);
	virtual void GetFileSize(char  const* pchFileName);
	virtual void FileRead(char  const* pchFileName, void * pvData, int iBytes);
	virtual void FileExists(char  const* pchFileName);
	virtual void FileDelete(char  const* pchFileName);
	virtual void GetFileCount(void);
	virtual void GetFileNameAndSize(int, int * piSize);
	virtual void GetQuota(int * a1, int * a2);
};