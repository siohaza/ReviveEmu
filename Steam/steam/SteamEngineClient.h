/*#include "SteamFilesystem.h"
#include "SteamAccount.h"
#include "SteamLogging.h"
#include "SteamUserIDValidation.h"

class CSteamEngineClient
{
private:
	IFileSystem* m_pFileSystem;
	CSteamLogging* m_pLogging;
	CSteamUserID* m_pUserID;
	CSteamAccountManager* m_pAccount;
public:
	CSteamEngineClient()
		{
	this->m_pFileSystem = NULL;
	this->m_pLogging = NULL;
	this->m_pUserID = NULL;
	this->m_pAccount = NULL;
}
	~CSteamEngineClient()
		{
	if(this->m_pFileSystem)
		delete this->m_pFileSystem;

	if(this->m_pLogging)
		delete this->m_pLogging;

	if(this->m_pUserID)
		delete this->m_pUserID;

	if(this->m_pAccount)
		delete this->m_pAccount;
}

	bool InitFileSystem()
		{
	this->m_pFileSystem = new CLocalFileSystem();
	return (this->m_pFileSystem ? true : false);
}
	bool InitLogging()
		{
	this->m_pLogging = new CSteamLogging();
	return (this->m_pLogging ? true : false);
}
	bool InitUserID()
		{
	this->m_pUserID = new CSteamUserID();
	return (this->m_pUserID ? true : false);
}
	bool InitAccount()
		{
	this->m_pAccount = new CSteamAccountManager();

	return (this->m_pAccount ? true : false);
}
	
	IFileSystem* GetFileSystem() const
		{
	return this->m_pFileSystem;
}
	CSteamLogging* GetLogging() const
		{
	return this->m_pLogging;
}
	CSteamUserID* GetUserID() const
		{
	return this->m_pUserID;
}
	CSteamAccountManager* GetAccount() const
		{
	return this->m_pAccount;
}
};*/