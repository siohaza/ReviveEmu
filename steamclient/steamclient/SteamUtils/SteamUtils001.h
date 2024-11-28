class CSteamUtils001
{
public:
	CSteamUtils001();
	~CSteamUtils001();

	virtual void GetSecondsSinceAppActive(void);
	virtual void GetSecondsSinceComputerActive(void);
	virtual EUniverse GetConnectedUniverse(void);
	virtual void GetServerRealTime(void);
	virtual const char* GetIPCountry(void);
	virtual bool GetImageSize(int a1, unsigned int * a2, unsigned int * a3);
	virtual bool GetImageRGBA(int a1, unsigned char * a2, int a3);
};