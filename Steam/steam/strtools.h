//===== Copyright © 1996-2005, Valve Corporation, All rights reserved. ======//
//
// Purpose: 
//
// $NoKeywords: $
//
//===========================================================================//
#ifdef _WIN32
#pragma once
#endif

//#include <string.h>
#include <stdlib.h>

namespace Common
{
	char*		V_stristr( char* pStr, const char* pSearch );
	const char*	V_stristr( const char* pStr, const char* pSearch );

	#define COPY_ALL_CHARACTERS -1
	char *V_strncat(char *, const char *, size_t destBufferSize, int max_chars_to_copy=COPY_ALL_CHARACTERS );

	// Tools for working with filenames
	// Extracts the base name of a file (no path, no extension, assumes '/' or '\' as path separator)
	void V_FileBase( const char *in, char *out,int maxlen );
	// Remove the final characters of ppath if it's '\' or '/'.
	void V_StripTrailingSlash( char *ppath );
	// Remove any extension from in and return resulting string in out
	void V_StripExtension( const char *in, char *out, int outLen );
	// Make path end with extension if it doesn't already have an extension
	void V_DefaultExtension( char *path, const char *extension, int pathStringLength );
	// Strips any current extension from path and ensures that extension is the new extension
	void V_SetExtension( char *path, const char *extension, int pathStringLength );
	// Removes any filename from path ( strips back to previous / or \ character )
	void V_StripFilename( char *path );
	// Remove the final directory from the path
	bool V_StripLastDir( char *dirName, int maxlen );
	// Returns a pointer to the unqualified file name (no path) of a file name
	const char * V_UnqualifiedFileName( const char * in );
	// Given a path and a filename, composes "path\filename", inserting the (OS correct) separator if necessary
	void V_ComposeFileName( const char *path, const char *filename, char *dest, int destSize );

	// Copy out the path except for the stuff after the final pathseparator
	bool V_ExtractFilePath( const char *path, char *dest, int destSize );
	// Copy out the file extension into dest
	void V_ExtractFileExtension( const char *path, char *dest, int destSize );

	const char *V_GetFileExtension( const char * path );

	// This removes "./" and "../" from the pathname. pFilename should be a full pathname.
	// Returns false if it tries to ".." past the root directory in the drive (in which case 
	// it is an invalid path).
	bool V_RemoveDotSlashes( char *pFilename );

	void V_FullPathToRelativePath(const char* cszFullPath, char* szRelativePath, const char* szBaseDirectory = NULL);

	// If pPath is a relative path, this function makes it into an absolute path
	// using the current working directory as the base, or pStartingDir if it's non-NULL.
	// Returns false if it runs out of room in the string, or if pPath tries to ".." past the root directory.
	void V_MakeAbsolutePath( char *pOut, int outLen, const char *pPath, const char *pStartingDir = NULL );

	// Adds a path separator to the end of the string if there isn't one already. Returns false if it would run out of space.
	void V_AppendSlash( char *pStr, int strSize );

	// Returns true if the path is an absolute path.
	bool V_IsAbsolutePath( const char *pPath );

	// This function takes a slice out of pStr and stores it in pOut.
	// It follows the Python slice convention:
	// Negative numbers wrap around the string (-1 references the last character).
	// Large numbers are clamped to the end of the string.
	void V_StrSlice( const char *pStr, int firstChar, int lastCharNonInclusive, char *pOut, int outSize );

	// Chop off the left nChars of a string.
	void V_StrLeft( const char *pStr, int nChars, char *pOut, int outSize );

	// Chop off the right nChars of a string.
	void V_StrRight( const char *pStr, int nChars, char *pOut, int outSize );


	#ifdef _WIN32
	#define CORRECT_PATH_SEPARATOR '\\'
	#define INCORRECT_PATH_SEPARATOR '/'
	#elif _LINUX
	#define CORRECT_PATH_SEPARATOR '/'
	#define INCORRECT_PATH_SEPARATOR '\\'
	#endif

	// Force slashes of either type to be = separator character
	void V_FixSlashes( char *pname, char separator = CORRECT_PATH_SEPARATOR );

	bool V_IsMatchingWithMask(const char* cszString, const char* cszMask);
}
