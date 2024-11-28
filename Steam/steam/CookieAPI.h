#ifndef _COOKIE_API_
#define _COOKIE_API_

/*
	Cookie API - by steamCooker
	---------------------------------------------------------
	Can be freely used in any project. credits are welcome :)
 */


/*
	initialize the API. to be called before any other function below.
*/
int initCookieApi();

/*
	downloads the ContentDescriptionRecord from the specified server/port.
	char * server : steam config server host name
	int post      : steam config server port number
	int * cdrSize : will recieve the size of the downloaded ContentDescriptionRecord

    return value  : a pointer to a newly allocated buffer filled with the downloaded ContentDescriptionRecord. 

	error         : on error, the function returns a null pointer.
*/
char * downloadContentDescriptionRecord(char * server, int port, int * cdrSize);

/*
	import the ContentDescriptionRecord buffer in a .blob registry file.
	char * blobFile : the .blob path and file name. the file will be created if needed
	char * key      : the key where to import the ContentDescriptionRecord
	char * cdr      : the ContentDescriptionRecord buffer
	int cdrSize     : the ContentDescriptionRecord buffer size

    return value    : TRUE on success, FALSE otherwise.
*/
int importContentDescriptionRecordInBlob(char * blobFile, char * key, char * cdr, int cdrSize);

/*
	reads the ContentDescriptionRecord from the specified .blob registry file.
	char * blobFile : the .blob path and file name.  
	char * key      : the key where to read the ContentDescriptionRecord
	int * cdrSize   : will recieve the size of the read ContentDescriptionRecord

    return value    : a pointer to a newly allocated buffer filled with the read ContentDescriptionRecord. 

	error           : on error, the function returns a null pointer.
*/
char * getContentDescriptionRecordFromBlob(char * blobFile, char * key, int * cdrSize);

#endif