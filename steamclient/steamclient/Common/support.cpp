#include ".\commonincludes.h"
#include ".\support.h"

//
// Support
//

char* strrstr(char *x,char *y) 
{
	int m = strlen(x);
	int n = strlen(y);
	char *X = (char*)malloc(m+1);
	char *Y = (char*)malloc(n+1);
	int i;
	for (i=0; i<m; i++) X[m-1-i] = x[i]; X[m] = 0;
	for (i=0; i<n; i++) Y[n-1-i] = y[i]; Y[n] = 0;
	char *Z = strstr(X,Y);
	if (Z) 
	{
		int ro = Z-X;
		int lo = ro+n-1;
		int ol = m-1-lo;
		Z = x+ol;
	}
	free(X); free(Y);
	return Z;
}

#define NUL '\0'

char *_stristr(const char *String, const char *Pattern)
{
	char *pptr, *sptr, *start;

	for (start = (char *)String; *start != NUL; start++)
	{
		/* find start of pattern in string */
		for ( ; ((*start!=NUL) && (toupper(*start) != toupper(*Pattern))); start++)
			;
		if (NUL == *start)
			return NULL;

		pptr = (char *)Pattern;
		sptr = (char *)start;

		while (toupper(*sptr) == toupper(*pptr))
		{
			sptr++;
			pptr++;

			/* if end of pattern then pattern was found */

			if (NUL == *pptr)
				return (start);
		}
	}
	return NULL;
}
