//#pragma once
//
//
struct fHEAD
{
	char type[4];
	int weight[256];
	int length;
};

unsigned char *pBuffer;
//
//
//int Compress(const char *pFilename);
//
int Compress(const char *pFilename, int *weight, HuffmanCode &pHC);
char Str2byte(const char *pBinStr);
int Encode(const char *pFilename, const HuffmanCode pHC, char *pBuffer, const int nSize);
