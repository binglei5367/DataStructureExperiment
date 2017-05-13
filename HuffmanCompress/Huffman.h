#pragma once
int weight[256];

typedef struct
{
	int weight;
	int parent;
	int lchild;
	int rchild;
}HTNode, *HuffmanTree;
typedef char **HuffmanCode;



void Select(HuffmanTree HT, int k, int &min1, int &min2);
int min(HuffmanTree HT, int k);


int HuffmanCreat(HuffmanTree &pHT, int *w, int n);
void HuffmanCoding(HuffmanTree pHT, HuffmanCode &pHC, int n);
int HuffmanCoding(HuffmanTree &pHT, HuffmanCode &pHC);




void TestHufTree(HuffmanTree pHT);
void TestHufCode(int root, HuffmanTree pHT, HuffmanCode pHC);