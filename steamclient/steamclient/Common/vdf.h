#ifndef _VDH_H_
#define _VDH_H_

typedef struct VdfKey
{
	char * name;
	char * value;
	VdfKey * nextSibiling;
	VdfKey * firstChild;
	
} VdfKey;

VdfKey * parseVdf(char * fileName);

void freeVdf(VdfKey * root);

int saveVdf(char * fileName,VdfKey * root);
#endif
