#pragma once
#pragma pack (2)

typedef enum
{
	Key = 1,
	Value = 2
}ESteamBlobNodeType;

typedef enum
{
	String,
	dword,
	RawBinaryData
}ESteamBlobValueType;

typedef struct
{
    unsigned short magic;
    unsigned int datalength;
    unsigned int nullpadding;
}TNodeHeader;

typedef struct
{
    unsigned short magic;
    unsigned int datalength;
    unsigned int nullpadding;
    unsigned int compresseddatalength;
    unsigned int nullpadding2;
    unsigned short Unknown;
}TNodeHeaderCompressed;

typedef struct
{
    unsigned short descriptorlength;
    unsigned int datalength;
	ESteamBlobNodeType type;
}TDescriptorNode;

typedef struct
{
    unsigned short descriptorlength;
    unsigned int  datalength;
}TNode;

typedef struct
{
	ESteamBlobValueType Type;
	unsigned int ValueSize;
	char *Value;
}TNodeValue;

#pragma pack (4)

const unsigned short NodeMagicNum = 0x5001;
const unsigned short NodeMagicNumCompressed = 0x4301;
