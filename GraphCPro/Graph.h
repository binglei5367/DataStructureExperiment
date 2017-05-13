//#pragma once
#define MAX_VERTEX_NUM 20
#define MAX_NAME_LEN 20
#define MAX_DESC_LEN 1024
#define MAX_DISTENCE 0x7FFFFFF

struct Vex
{
	int num;
	char name[MAX_NAME_LEN];
	char desc[MAX_DESC_LEN];
};

struct Edge
{
	int vex1;
	int vex2;
	int weight;
};


typedef struct Path
{
	int vexs[MAX_VERTEX_NUM];
	Path *next;
}*PathList;
 
class CGraph
{
public:
	CGraph();
	~CGraph();

private:
	int m_aAdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
	Vex m_aVex[MAX_VERTEX_NUM];
	int m_nVexNum;

public:
	void Init(void);
	bool InsertVex(Vex sVex);
	bool InsertEdge(Edge sEdge);
	Vex GetVex(int nVex);
	int FindEdge(int nVex, Edge aEdge[]);
	int GetVexnum(void);
	void DFS(int nVex, bool bVisited[], int & nIndex, PathList & pList);
	void DFSTraverse(int nVex, PathList & pList);
	int FindShortPath(int nVexStart, int nVexEnd, Edge aPath[]);
};

