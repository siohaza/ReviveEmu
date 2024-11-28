//===== Copyright © 1996-2005, Valve Corporation, All rights reserved. ======//
//
// Purpose: 
//
// $NoKeywords: $
//
//===========================================================================//
#include "StdAfx.h"
#include "strtools.h"


// NOTE: I have to include stdio + stdarg first so vsnprintf gets compiled in
#include <direct.h>
#include <stdio.h>
#include <stdarg.h>

namespace Common
{
	//-----------------------------------------------------------------------------
	// Finds a string in another string with a case insensitive test
	//-----------------------------------------------------------------------------
	char const* V_stristr( char const* pStr, char const* pSearch )
	{
		if (!pStr || !pSearch) 
			return 0;

		char const* pLetter = pStr;

		// Check the entire string
		while (*pLetter != 0)
		{
			// Skip over non-matches
			if (tolower((unsigned char)*pLetter) == tolower((unsigned char)*pSearch))
			{
				// Check for match
				char const* pMatch = pLetter + 1;
				char const* pTest = pSearch + 1;
				while (*pTest != 0)
				{
					// We've run off the end; don't bother.
					if (*pMatch == 0)
						return 0;

					if (tolower((unsigned char)*pMatch) != tolower((unsigned char)*pTest))
						break;

					++pMatch;
					++pTest;
				}

				// Found a match!
				if (*pTest == 0)
					return pLetter;
			}

			++pLetter;
		}

		return 0;
	}

	char* V_stristr( char* pStr, char const* pSearch )
	{
		return (char*)V_stristr( (char const*)pStr, pSearch );
	}

	//-----------------------------------------------------------------------------
	// Purpose: If COPY_ALL_CHARACTERS == max_chars_to_copy then we try to add the whole pSrc to the end of pDest, otherwise
	//  we copy only as many characters as are specified in max_chars_to_copy (or the # of characters in pSrc if thats's less).
	// Input  : *pDest - destination buffer
	//			*pSrc - string to append
	//			destBufferSize - sizeof the buffer pointed to by pDest
	//			max_chars_to_copy - COPY_ALL_CHARACTERS in pSrc or max # to copy
	// Output : char * the copied buffer
	//-----------------------------------------------------------------------------
	char *V_strncat(char *pDest, const char *pSrc, size_t destBufferSize, int max_chars_to_copy )
	{
		size_t charstocopy = (size_t)0;
		
		size_t len = strlen(pDest);
		size_t srclen = strlen( pSrc );
		if ( max_chars_to_copy <= COPY_ALL_CHARACTERS )
		{
			charstocopy = srclen;
		}
		else
		{
			charstocopy = (size_t)min( max_chars_to_copy, (int)srclen );
		}

		if ( len + charstocopy >= destBufferSize )
		{
			charstocopy = destBufferSize - len - 1;
		}

		if ( !charstocopy )
		{
			return pDest;
		}

		char *pOut = strncat( pDest, pSrc, charstocopy );
		pOut[destBufferSize-1] = 0;
		return pOut;
	}


	#if defined( _WIN32 ) || defined( WIN32 )
	#define PATHSEPARATOR(c) ((c) == '\\' || (c) == '/')
	#else	//_WIN32
	#define PATHSEPARATOR(c) ((c) == '/')
	#endif	//_WIN32


	//-----------------------------------------------------------------------------
	// Purpose: Extracts the base name of a file (no path, no extension, assumes '/' or '\' as path separator)
	// Input  : *in - 
	//			*out - 
	//			maxlen - 
	//-----------------------------------------------------------------------------
	void V_FileBase( const char *in, char *out, int maxlen )
	{
		if ( !in || !in[ 0 ] )
		{
			*out = 0;
			return;
		}

		int len, start, end;

		len = strlen( in );
		
		// scan backward for '.'
		end = len - 1;
		while ( end&& in[end] != '.' && !PATHSEPARATOR( in[end] ) )
		{
			end--;
		}
		
		if ( in[end] != '.' )		// no '.', copy to end
		{
			end = len-1;
		}
		else 
		{
			end--;					// Found ',', copy to left of '.'
		}

		// Scan backward for '/'
		start = len-1;
		while ( start >= 0 && !PATHSEPARATOR( in[start] ) )
		{
			start--;
		}

		if ( start < 0 || !PATHSEPARATOR( in[start] ) )
		{
			start = 0;
		}
		else 
		{
			start++;
		}

		// Length of new sting
		len = end - start + 1;

		int maxcopy = min( len + 1, maxlen );

		// Copy partial string
		strncpy( out, &in[start], maxcopy );
	}

	//-----------------------------------------------------------------------------
	// Purpose: 
	// Input  : *ppath - 
	//-----------------------------------------------------------------------------
	void V_StripTrailingSlash( char *ppath )
	{
		int len = strlen( ppath );
		if ( len > 0 )
		{
			if ( PATHSEPARATOR( ppath[ len - 1 ] ) )
			{
				ppath[ len - 1 ] = 0;
			}
		}
	}

	//-----------------------------------------------------------------------------
	// Purpose: 
	// Input  : *in - 
	//			*out - 
	//			outSize - 
	//-----------------------------------------------------------------------------
	void V_StripExtension( const char *in, char *out, int outSize )
	{
		// Find the last dot. If it's followed by a dot or a slash, then it's part of a 
		// directory specifier like ../../somedir/./blah.
		const char *pLastExt = in;
		const char *pTest = strrchr( pLastExt, '.' );
		if ( pTest )
		{
			// This handles things like ".\blah" or "c:\my@email.com\abc\def\geh"
			// Which would otherwise wind up with "" and "c:\my@email", respectively.
			if ( strrchr( in, '\\' ) < pTest && strrchr( in, '/' ) < pTest )
			{
				pLastExt = pTest + 1;
			}
		}

		// Copy up to the last dot.
		if ( pLastExt > in )
		{
			int nChars = pLastExt - in - 1;
			nChars = min( nChars, outSize-1 );
			memcpy( out, in, nChars );
			out[nChars] = 0;
		}
		else
		{
			if ( out != in )
			{
				strncpy( out, in, outSize );
			}
		}
	}

	//-----------------------------------------------------------------------------
	// Purpose: 
	// Input  : *path - 
	//			*extension - 
	//			pathStringLength - 
	//-----------------------------------------------------------------------------
	void V_DefaultExtension( char *path, const char *extension, int pathStringLength )
	{
		char    *src;

		// if path doesn't have a .EXT, append extension
		// (extension should include the .)
		src = path + strlen(path) - 1;

		while ( !PATHSEPARATOR( *src ) && ( src > path ) )
		{
			if (*src == '.')
			{
				// it has an extension
				return;                 
			}
			src--;
		}

		// Concatenate the desired extension
		V_strncat( path, extension, pathStringLength, COPY_ALL_CHARACTERS );
	}

	//-----------------------------------------------------------------------------
	// Purpose: Force extension...
	// Input  : *path - 
	//			*extension - 
	//			pathStringLength - 
	//-----------------------------------------------------------------------------
	void V_SetExtension( char *path, const char *extension, int pathStringLength )
	{
		V_StripExtension( path, path, pathStringLength );
		V_DefaultExtension( path, extension, pathStringLength );
	}

	//-----------------------------------------------------------------------------
	// Purpose: Remove final filename from string
	// Input  : *path - 
	// Output : void  V_StripFilename
	//-----------------------------------------------------------------------------
	void V_StripFilename (char *path)
	{
		int             length;

		length = strlen( path )-1;
		if ( length <= 0 )
			return;

		while ( length > 0 && 
			!PATHSEPARATOR( path[length] ) )
		{
			length--;
		}

		path[ length ] = 0;
	}

	#ifdef _WIN32
	#define CORRECT_PATH_SEPARATOR '\\'
	#define INCORRECT_PATH_SEPARATOR '/'
	#elif _LINUX
	#define CORRECT_PATH_SEPARATOR '/'
	#define INCORRECT_PATH_SEPARATOR '\\'
	#endif

	//-----------------------------------------------------------------------------
	// Purpose: Changes all '/' or '\' characters into separator and removes multiple slashes
	// Input  : *pname - 
	//			separator - 
	//-----------------------------------------------------------------------------
	void V_FixSlashes( char *pname, char separator /* = CORRECT_PATH_SEPARATOR */)
	{
		char* pIn = pname;
		char* pOut = pname;

		while(*pIn)
		{
			if(PATHSEPARATOR(*pIn))
			{
				*pOut = separator;
				pOut++;
				pIn++;

				while(PATHSEPARATOR(*pIn))
				{
					pIn++;
				}
			}
			
			*pOut = *pIn;
			pOut++;
			pIn++;
		}

		*pOut = 0;
	}

	//-----------------------------------------------------------------------------
	// Purpose: Strip off the last directory from dirName
	// Input  : *dirName - 
	//			maxlen - 
	// Output : Returns true on success, false on failure.
	//-----------------------------------------------------------------------------
	bool V_StripLastDir( char *dirName, int maxlen )
	{
		if( dirName[0] == 0 || 
			!_stricmp( dirName, "./" ) || 
			!_stricmp( dirName, ".\\" ) )
			return false;
		
		int len = strlen( dirName );

		// skip trailing slash
		if ( PATHSEPARATOR( dirName[len-1] ) )
		{
			len--;
		}

		while ( len > 0 )
		{
			if ( PATHSEPARATOR( dirName[len-1] ) )
			{
				dirName[len] = 0;
				V_FixSlashes( dirName, CORRECT_PATH_SEPARATOR );
				return true;
			}
			len--;
		}

		// Allow it to return an empty string and true. This can happen if something like "tf2/" is passed in.
		// The correct behavior is to strip off the last directory ("tf2") and return true.
		if( len == 0 )
		{
			_snprintf( dirName, maxlen, ".%c", CORRECT_PATH_SEPARATOR );
			return true;
		}

		return true;
	}


	//-----------------------------------------------------------------------------
	// Purpose: Returns a pointer to the beginning of the unqualified file name 
	//			(no path information)
	// Input:	in - file name (may be unqualified, relative or absolute path)
	// Output:	pointer to unqualified file name
	//-----------------------------------------------------------------------------
	const char * V_UnqualifiedFileName( const char * in )
	{
		// back up until the character after the first path separator we find,
		// or the beginning of the string
		const char * out = in + strlen( in ) - 1;
		while ( ( out > in ) && ( !PATHSEPARATOR( *( out-1 ) ) ) )
			out--;
		return out;
	}


	//-----------------------------------------------------------------------------
	// Purpose: Composes a path and filename together, inserting a path separator
	//			if need be
	// Input:	path - path to use
	//			filename - filename to use
	//			dest - buffer to compose result in
	//			destSize - size of destination buffer
	//-----------------------------------------------------------------------------
	void V_ComposeFileName( const char *path, const char *filename, char *dest, int destSize )
	{
		strncpy( dest, path, destSize );
		V_AppendSlash( dest, destSize );
		strncat( dest, filename, destSize);
		V_FixSlashes( dest );
	}


	//-----------------------------------------------------------------------------
	// Purpose: 
	// Input  : *path - 
	//			*dest - 
	//			destSize - 
	// Output : void V_ExtractFilePath
	//-----------------------------------------------------------------------------
	bool V_ExtractFilePath (const char *path, char *dest, int destSize )
	{
		if ( destSize < 1 )
		{
			return false;
		}

		// Last char
		int len = strlen(path);
		const char *src = path + (len ? len-1 : 0);

		// back up until a \ or the start
		while ( src != path && !PATHSEPARATOR( *(src-1) ) )
		{
			src--;
		}

		int copysize = min( src - path, destSize - 1 );
		memcpy( dest, path, copysize );
		dest[copysize] = 0;

		return copysize != 0 ? true : false;
	}

	//-----------------------------------------------------------------------------
	// Purpose: 
	// Input  : *path - 
	//			*dest - 
	//			destSize - 
	// Output : void V_ExtractFileExtension
	//-----------------------------------------------------------------------------
	void V_ExtractFileExtension( const char *path, char *dest, int destSize )
	{
		*dest = NULL;
		const char * extension = V_GetFileExtension( path );
		if ( NULL != extension )
			strncpy( dest, extension, destSize );
	}


	//-----------------------------------------------------------------------------
	// Purpose: Returns a pointer to the file extension within a file name string
	// Input:	in - file name 
	// Output:	pointer to beginning of extension (after the "."), or NULL
	//				if there is no extension
	//-----------------------------------------------------------------------------
	const char * V_GetFileExtension( const char * path )
	{
		const char    *src;

		src = path + strlen(path) - 1;

	//
	// back up until a . or the start
	//
		while (src != path && *(src-1) != '.' )
			src--;

		// check to see if the '.' is part of a pathname
		if (src == path || PATHSEPARATOR( *src ) )
		{		
			return NULL;  // no extension
		}

		return src;
	}

	bool V_RemoveDotSlashes( char *pFilename )
	{
		// Get rid of "./"'s
		char *pIn = pFilename;
		char *pOut = pFilename;
		while ( *pIn )
		{
			// The logic on the second line is preventing it from screwing up "../"
			if ( pIn[0] == '.' && PATHSEPARATOR( pIn[1] ) &&
				(pIn == pFilename || pIn[-1] != '.') )
			{
				pIn += 2;
			}
			else
			{
				*pOut = *pIn;
				++pIn;
				++pOut;
			}
		}
		*pOut = 0;


		// Get rid of a trailing "/." (needless).
		int len = strlen( pFilename );
		if ( len > 2 && pFilename[len-1] == '.' && PATHSEPARATOR( pFilename[len-2] ) )
		{
			pFilename[len-2] = 0;
		}

		// Each time we encounter a "..", back up until we've read the previous directory name,
		// then get rid of it.
		pIn = pFilename;
		while ( *pIn )
		{
			if ( pIn[0] == '.' && 
				 pIn[1] == '.' && 
				 (pIn == pFilename || PATHSEPARATOR(pIn[-1])) &&	// Preceding character must be a slash.
				 (pIn[2] == 0 || PATHSEPARATOR(pIn[2])) )			// Following character must be a slash or the end of the string.
			{
				char *pEndOfDots = pIn + 2;
				char *pStart = pIn - 2;

				// Ok, now scan back for the path separator that starts the preceding directory.
				while ( 1 )
				{
					if ( pStart < pFilename )
						return false;

					if ( PATHSEPARATOR( *pStart ) )
						break;

					--pStart;
				}

				// Now slide the string down to get rid of the previous directory and the ".."
				memmove( pStart, pEndOfDots, strlen( pEndOfDots ) + 1 );

				// Start over.
				pIn = pFilename;
			}
			else
			{
				++pIn;
			}
		}
		
		V_FixSlashes( pFilename );	
		return true;
	}

	void V_AppendSlash( char *pStr, int strSize )
	{
		int len = strlen( pStr );
		if ( len > 0 && !PATHSEPARATOR(pStr[len-1]) )
		{	
			pStr[len] = CORRECT_PATH_SEPARATOR;
			pStr[len+1] = 0;
		}
	}

	void V_FullPathToRelativePath(const char* cszFullPath, char* szRelativePath, const char* cszBaseDirectory)
	{
		char szTempBaseDir[MAX_PATH];
		const char* cszBaseDir = cszBaseDirectory;

		if(!cszBaseDir)
		{
			_getcwd(szTempBaseDir, MAX_PATH);
			cszBaseDir = szTempBaseDir;
		}

		if(strstr(cszFullPath, cszBaseDir) == cszFullPath)
		{
			const char* szStartRelativeFilePath = cszFullPath + strlen(cszBaseDir);
			while(PATHSEPARATOR(*szStartRelativeFilePath) || *szStartRelativeFilePath == 0)
			{
				szStartRelativeFilePath++;
			}

			strcpy(szRelativePath, szStartRelativeFilePath);
		}
	}

	void V_MakeAbsolutePath( char *pOut, int outLen, const char *pPath, const char *pStartingDir )
	{
		if ( V_IsAbsolutePath( pPath ) )
		{
			// pPath is not relative.. just copy it.
			strncpy( pOut, pPath, outLen );
		}
		else
		{
			// Make sure the starting directory is absolute..
			if ( pStartingDir && V_IsAbsolutePath( pStartingDir ) )
			{
				strncpy( pOut, pStartingDir, outLen );
			}
			else
			{
				if ( pStartingDir )
				{
					V_AppendSlash( pOut, outLen );
					strncat( pOut, pStartingDir, outLen );
				}
			}

			// Concatenate the paths.
			V_AppendSlash( pOut, outLen );
			strncat( pOut, pPath, outLen );
		}

		V_FixSlashes( pOut );
	}


	// small helper function shared by lots of modules
	bool V_IsAbsolutePath( const char *pStr )
	{
		return ( pStr[0] && pStr[1] == ':' ) || PATHSEPARATOR(pStr[0]);
	}


	// Copies at most nCharsToCopy bytes from pIn into pOut.
	// Returns false if it would have overflowed pOut's buffer.
	static bool CopyToMaxChars( char *pOut, int outSize, const char *pIn, int nCharsToCopy )
	{
		if ( outSize == 0 )
			return false;

		int iOut = 0;
		while ( *pIn && nCharsToCopy > 0 )
		{
			if ( iOut == (outSize-1) )
			{
				pOut[iOut] = 0;
				return false;
			}
			pOut[iOut] = *pIn;
			++iOut;
			++pIn;
			--nCharsToCopy;
		}
		
		pOut[iOut] = 0;
		return true;
	}

	// This function takes a slice out of pStr and stores it in pOut.
	// It follows the Python slice convention:
	// Negative numbers wrap around the string (-1 references the last character).
	// Numbers are clamped to the end of the string.
	void V_StrSlice( const char *pStr, int firstChar, int lastCharNonInclusive, char *pOut, int outSize )
	{
		if ( outSize == 0 )
			return;
		
		int length = strlen( pStr );

		// Fixup the string indices.
		if ( firstChar < 0 )
		{
			firstChar = length - (-firstChar % length);
		}
		else if ( firstChar >= length )
		{
			pOut[0] = 0;
			return;
		}

		if ( lastCharNonInclusive < 0 )
		{
			lastCharNonInclusive = length - (-lastCharNonInclusive % length);
		}
		else if ( lastCharNonInclusive > length )
		{
			lastCharNonInclusive %= length;
		}

		if ( lastCharNonInclusive <= firstChar )
		{
			pOut[0] = 0;
			return;
		}

		int copyLen = lastCharNonInclusive - firstChar;
		if ( copyLen <= (outSize-1) )
		{
			memcpy( pOut, &pStr[firstChar], copyLen );
			pOut[copyLen] = 0;
		}
		else
		{
			memcpy( pOut, &pStr[firstChar], outSize-1 );
			pOut[outSize-1] = 0;
		}
	}


	void V_StrLeft( const char *pStr, int nChars, char *pOut, int outSize )
	{
		if ( nChars == 0 )
		{
			if ( outSize != 0 )
				pOut[0] = 0;

			return;
		}

		V_StrSlice( pStr, 0, nChars, pOut, outSize );
	}


	void V_StrRight( const char *pStr, int nChars, char *pOut, int outSize )
	{
		int len = strlen( pStr );
		if ( nChars >= len )
		{
			strncpy( pOut, pStr, outSize );
		}
		else
		{
			V_StrSlice( pStr, -nChars, strlen( pStr ), pOut, outSize );
		}
	}

	bool V_IsMatchingWithMask(const char* cszString, const char* cszMask)
	{
		const char *cp = NULL, *mp = NULL;

		while ((*cszString) && (*cszMask != '*'))
		{
			if ((*cszMask != *cszString) && (*cszMask != '?'))
			{
				return 0;
			}

			cszMask++;
			cszString++;
		}

		while (*cszString)
		{
			if (*cszMask == '*')
			{
				if (!*++cszMask)
				{
					return 1;
				}

				mp = cszMask;
				cp = cszString+1;
			}
			else if ((*cszMask == *cszString) || (*cszMask == '?'))
			{
				cszMask++;
				cszString++;
			}
			else
			{
				cszMask = mp;
				cszString = cp++;
			}
		}

		while (*cszMask == '*')
		{
			cszMask++;
		}

		return (!*cszMask ? true : false);
	}
}