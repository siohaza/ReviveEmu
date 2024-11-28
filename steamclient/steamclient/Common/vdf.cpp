#include "commonincludes.h"
#include "io.h"
#include "stdio.h"
#include "string.h"
#include "malloc.h"
#include "vdf.h"

VdfKey * parseVdfKey(FILE * file)
{
	char line[1024];
	if (fscanf(file,"%s",line)<=0) return 0;
	if (line[0]!='"' || line[0]=='}') return 0;
	VdfKey * key=new VdfKey;
	key->value=0;
	key->firstChild=0;
	key->nextSibiling=0;
	key->name=(char*)malloc(strlen(line)-1);
	memcpy(key->name,line+1,strlen(line)-2);
	key->name[strlen(line)-2]=0;

	if (fscanf(file,"%s",line)<=0) 
	{
		free(key->name);
		delete(key);
		return 0;
	}
	switch (line[0])
	{
	case '"':{
		key->value=(char*)malloc(strlen(line)-1);
		memcpy(key->value,line+1,strlen(line)-2);
		key->value[strlen(line)-2]=0;
		return key;
		break;
			 }
	case '{':{
		VdfKey * tmp=0;
		VdfKey * tmp2=0;

		while (tmp2=parseVdfKey(file))
		{
			if (!tmp)
				key->firstChild=tmp2;
			else
				tmp->nextSibiling=tmp2;
			tmp=tmp2;
		}
		return key;
		break;
			 }
	default:{
		free(key->name);
		delete(key);
		return 0;
			}
	}
	return key;
}



VdfKey * parseVdf(char * fileName)
{
	FILE * file=fopen(fileName,"r");
	if (!file)
		return 0;
	VdfKey * res=parseVdfKey(file);
	fclose(file);
	return res;
}

void freeVdf(VdfKey * root)
{
	if (root->firstChild) {
		freeVdf(root->firstChild);
		delete(root->firstChild);
	}
	if (root->nextSibiling) {
		freeVdf(root->nextSibiling);
		delete(root->nextSibiling);
	}
	if (root->name) free(root->name);
	if (root->value) free(root->value);
}

int saveVdfKey(FILE * file, VdfKey * key,char * indent)
{
	if (key->value)	fprintf(file,"%s\"%s\"\t\t\"%s\"\r\n\n",indent,key->name,key->value);
	else
		if (key->firstChild)
		{
			fprintf(file,"%s\"%s\"\r\n\n",indent,key->name);
			fprintf(file,"%s{\n",indent);
			VdfKey * tmp=key->firstChild;
			strcat(indent,"  ");
			while(tmp)
			{
				saveVdfKey(file,tmp,indent);
				tmp=tmp->nextSibiling;
			}
			indent[strlen(indent)-2]=0;
			fprintf(file,"%s}\n",indent);
		}
		return 0;
}

int saveVdf(char * fileName,VdfKey * root)
{
	char indent[100];
	memset(indent,0,100);
	FILE * file=fopen(fileName,"w");
	if (!file) return 1;
	int res=saveVdfKey(file,root,indent);
	fclose(file);
	return res;
}