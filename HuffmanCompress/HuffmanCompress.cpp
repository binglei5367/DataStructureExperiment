// HuffmanCompress.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <stdio.h>
using namespace std;





int main()
{
	char filename[256];
	cout << "Filename: " << endl;
	cin >> filename;

	int weight[SIZE] = { 0 };

	FILE *in;
	errno_t err = fopen_s(&in, filename, "rb");
	int intc;

	while ((intc = getc(in)) != EOF)
	{
		weight[intc]++;
	}
	fclose(in);

	printf("Byte\tWeight\n");
	for (int i = 0; i < SIZE; i++)
		printf("0x%02X\t%d\n", i, weight[i]);

	HuffmanTree pHT;
	HuffmanCode pHC;

	HuffmanCreat(pHT, weight, SIZE);
	TestHufTree(pHT);

	HuffmanCoding(pHT, pHC, SIZE);

	Compress(filename, weight, pHC);






	return 0;
}

