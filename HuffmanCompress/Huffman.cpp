#include "stdafx.h"

//HuffmanTree CreatHuffmanTree(int *weight, int n)
//{
//	int total = 2 * n - 1;
//	HuffmanTree pHT = (HuffmanTree)malloc((total) * sizeof(HTNode));
//	if (!pHT)
//	{
//		printf("HuffmanTree malloc faild!");
//		exit(-1);
//	}
//	int i;
//	for (i = 0; i < n; i++)
//	{
//		pHT[i].weight = *weight++;
//		pHT[i].parent = -1;
//		pHT[i].lchild = -1;
//		pHT[i].rchild = -1;
//	}
//	for (; i < total; i++)
//	{
//		pHT[i].weight = 0;
//		pHT[i].parent = -1;
//		pHT[i].lchild = -1;
//		pHT[i].rchild = -1;
//	}
//	int min1, min2;
//	min1 = Select(pHT, i - 1);
//	pHT[min1].parent = i;
//	pHT[i].lchild = min1;
//	min2 = Select(pHT, i - 1);
//	pHT[min2].parent = i;
//	pHT[i].rchild = min2;
//	pHT[i].weight = pHT[min1].weight + pHT[min2].weight;
//
//	return pHT;
//
//
//	//HuffmanTree p;
//	//int i;
//	//for (p = pHT, i = 1; i < 256; ++i, ++p)
//	//{
//	//	*p = { weight[i - 1], 0, 0, 0 };
//	//}
//	//for (; i < 512; ++i, ++p)
//	//{
//	//	*p = { 0,0,0,0 };
//	//}
//	//for (i = 256; i < 512; ++i)
//	//{
//	//	int s1 = Select(pHT, i - 1);
//	//	pHT[s1].parent = i;
//	//	int s2 = Select(pHT, i - 1);
//	//	pHT[s2].parent = i;
//	//	pHT[i].lchild = s1;
//	//	pHT[i].rchild = s2;
//	//	pHT[i].weight = pHT[s1].weight + pHT[s2].weight;
//	//}
//
//	//return 511;
//}

//int Select(HuffmanTree pHT, int nSize)
//{
//	int minValue = 0x7FFFFFFF;
//	int min = 0;
//
//	for (int i = 1; i <= nSize; i++)
//	{
//		if (pHT[i].parent == 0 && pHT[i].weight < minValue)
//		{
//			minValue = pHT[i].weight;
//			min = i;
//		}
//	}
//	return min;
//}

//HuffmanTree CreatHuffmanTree(int *weight, int n)
//{
//	int total = 2 * n - 1;
//	HuffmanTree pHT = (HuffmanTree)malloc((total+1) * sizeof(HTNode));
//	if (!pHT)
//	{
//		printf("HuffmanTree malloc faild!");
//		exit(-1);
//	}
//	int i;
//
//	for (i = 1; i<=n; i++)
//	{
//		pHT[i].weight = *weight;
//		pHT[i].parent = 0;
//		pHT[i].lchild = 0;
//		pHT[i].rchild = 0;
//		
//		weight++;
//	}
//
//	for (; i<=total; i++)
//	{
//		pHT[i].parent = 0;
//		pHT[i].lchild = 0;
//		pHT[i].rchild = 0;
//		pHT[i].weight = 0;
//	}
//
//	int min1, min2; 
//	for (i = n+1; i<total; i++)
//	{
//		Select(pHT, i, min1, min2);
//		pHT[min1].parent = i;
//		pHT[min2].parent = i;
//		pHT[i].lchild = min1;
//		pHT[i].rchild = min2;
//		pHT[i].weight = pHT[min1].weight + pHT[min2].weight;
//	}
//	return pHT;
//}



void Select(HuffmanTree pHT, int k, int &min1, int &min2)
{
	min1 = min(pHT, k);
	min2 = min(pHT, k);
}
int min(HuffmanTree pHT, int k)
{
	int i = 0;
	int min;
	int min_weight;

	while (pHT[i].parent != 0 || pHT[i].weight == 0)
		i++;
	min_weight = pHT[i].weight;
	min = i;

	for (; i<k; i++)
	{
		if (pHT[i].weight<min_weight && pHT[i].parent == 0)
		{
			min_weight = pHT[i].weight;
			min = i;
		}
	}

	pHT[min].parent = -1;

	return min;
}


int HuffmanCreat(HuffmanTree &pHT, int *w, int n)
{
	if (n <= 1) return 0;
	int m = n * 2 - 1;
	int s1 = 0, s2 = 0;
	HuffmanTree p;
	pHT = (HuffmanTree)malloc((m + 1) * sizeof(HTNode));

	int i = 0;

	for (p = pHT + 1, i = 1; i <= n; ++i, ++p, ++w)
	{
		p->weight = *w;
		p->parent = 0;
		p->lchild = 0;
		p->rchild = 0;

	}
	for (; i <= m; ++i, ++p)
	{
		p->weight = 0;
		p->parent = 0;
		p->lchild = 0;
		p->rchild = 0;

	}
	for (i = n + 1; i <= m; ++i)
	{
		Select(pHT, i - 1, s1, s2);
		pHT[s1].parent = i;
		pHT[s2].parent = i;
		pHT[i].lchild = s1;
		pHT[i].rchild = s2;
		pHT[i].weight = pHT[s1].weight + pHT[s2].weight;
	}
	return 1;
}


void HuffmanCoding(HuffmanTree pHT, HuffmanCode &pHC, int n)
{
	int m = 2 * n - 1;

	pHC = (HuffmanCode)malloc((n + 1) * sizeof(char *));
	if (!pHC)
	{
		printf("HuffmanCode malloc faild!");
		exit(-1);
	}

	//char *code;
	//code = (char *)malloc(n * sizeof(char));

	//if (!code)
	//{
	//	printf("code malloc faild!");
	//	exit(-1);
	//}

	char code[256];

	code[n - 1] = '\0';

	for (int i = 1; i <= n; ++i)
	{
		int start = n - 1;
		int c = i, f = pHT[i].parent;
		while (f != 0)
		{
			if (pHT[f].lchild == c)
				code[--start] = '0';
			else
				code[--start] = '1';
			c = f;
			f = pHT[f].parent;
		}
		pHC[i] = (char*)malloc((n - start) * sizeof(char));
		//strcpy_s(pHC[i], n, &code[start]); // stackoverflow!!
		/**/
		for (int j = 0; j < n - start; j++)
		{
			pHC[i][j] = code[start + j];
		}
		printf("\n编码为：%d, 权值为：%d的哈夫曼编码为：", i, pHT[i].weight); puts(pHC[i]);
	}

	//delete(code); 
}


//无栈非递归
int HuffmanCoding(HuffmanTree &pHT, HuffmanCode &pHC)
{

	char cd[256] = { '\0' };
	int cdlen = 0;
	for (int i = 1; i < 512; i++)
	{
		pHT[i].weight = 0;
	}

	int p = 511;
	while (p != 0)
	{
		if (pHT[p].weight == 0)
		{
			pHT[p].weight = 1;
			if (pHT[p].lchild != 0)
			{
				p = pHT[p].lchild;
				cd[cdlen++] = '\0';
			}
			else if (pHT[p].rchild == 0)
			{
				printf("p=%d\n", p);
				//pHC[p] = new char(cdlen + 1);
				pHC[p] = (char *)malloc((cdlen + 1) * sizeof(char));
				cd[cdlen] = '\0';
				errno_t err = strcpy_s(pHC[p], 256, cd);
				printf("\n编码为：%d, 权值为：%d的哈夫曼编码为：", p, pHT[p].weight); puts(pHC[p]);
			}
		}
		else if (pHT[p].weight == 1)
		{
			pHT[p].weight = 2;
			if (pHT[p].rchild != 0)
			{
				p = pHT[p].rchild;
				cd[cdlen++] = '1';
			}
		}
		else
		{
			pHT[p].weight = 0;
			p = pHT[p].parent;
			--cdlen;
		}
	}
	return 1;
}




//void HuffmanGet(HuffmanTree &pHT, HuffmanCode &pHC, int n)
//{
//	char* code;
//	int i, c, f;
//	int start;
//	pHC = (HuffmanCode)malloc((n + 1) * sizeof(char*));
//	code = (char*)malloc(n * sizeof(char));
//	code[n - 1] = '\0';
//	for (i = 1; i < n; i++)
//	{
//		start = n - 1;
//		for (c = i, f = pHT[i].parent; f != 0; c = f, f = pHT[f].parent)
//		{
//			if (pHT[f].lchild == c)
//				code[--start] = '0';
//			else
//				code[--start] = '1';
//		}
//		pHC[i] = (char*)malloc((n - start) * sizeof(char));
//		strcpy_s(pHC[i], n, code + start);
//		printf("\n编码为：%d, 权值为：%d的哈夫曼编码为：", i, pHT[i].weight); puts(pHC[i]);
//
//	}
//	free(code);
//}


void TestHufTree(HuffmanTree pHT)
{
	for (int i = 1; i < 512; i++)
	{
		printf("pHT[%d]\t%d\t%d\t%d\t%d\n", i, pHT[i].weight, pHT[i].parent, pHT[i].lchild, pHT[i].rchild);
	}
}

void TestHufCode(int root, HuffmanTree pHT, HuffmanCode pHC)
{
	if (pHT[root].lchild == 0 && pHT[root].rchild == 0)
	{
		printf("0x%02X %s\n", root - 1, pHC[root] - 1);
	}
	if (pHT[root].lchild)
	{
		TestHufCode(pHT[root].lchild, pHT, pHC);
	}
	if (pHT[root].rchild)
	{
		TestHufCode(pHT[root].rchild, pHT, pHC);
	}
}
