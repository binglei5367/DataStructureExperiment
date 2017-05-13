#include "stdafx.h"

using namespace std;

int Compress(const char *pFilename, int *weight, HuffmanCode &pHC)
{
	int nSize = 0;
	for (int i = 1; i < 256; i++)
	{
		nSize += weight[i] * strlen(pHC[i]);
	}
	nSize = (nSize % 8) ? nSize / 8 + 1 : nSize / 8;

	char *pBuffer = NULL;


	Encode(pFilename, pHC, pBuffer, nSize);
	if (!pBuffer)
	{
		printf("Encode faild!");
		exit(-1);
	}

	for (int i = 0; i < nSize; i++)
	{
		printf("%d", pBuffer[i]);
	}

	return 0;
}

char Str2byte(const char *pBinStr)
{
	char b = 0x00;
	for (int i = 0; i < 8; i++)
	{
		b = b << 1;
		if (pBinStr[i] == '1')
		{
			b = b | 0x01;
		}
	}
	return b;
}


int Encode(const char *pFilename, const HuffmanCode pHC, char *pBuffer, const int nSize)
{
	FILE *in;
	errno_t err = fopen_s(&in, pFilename, "rb");

	pBuffer = (char*)malloc((nSize) * sizeof(char));
	if (!pBuffer)
	{
		printf("pBuffer malloc faild!");
		exit(-1);
	}

	char code[SIZE] = { 0 };
	//char code[SIZE];
	int pos = 0;
	int ch;
	while ((ch = fgetc(in)) != EOF)
	{
		//strcat(code, pHC[ch]);
		
		strcat(code, pHC[ch + 1]);	//***数组操作越界



		while (strlen(code) >= 8)
		{
			pBuffer[pos++] = Str2byte(code);
			for (int i = 0; i < SIZE - 8; i++)
			{
				code[i] = code[i + 8];
			}
		}
	}
	fclose(in);
	if (strlen(code) > 0)
	{
		pBuffer[pos++] = Str2byte(code);
	}
	return 0;
}

