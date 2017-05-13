#include "stdafx.h"
using namespace std;

CTourism::CTourism(){}

CTourism::~CTourism(){}

void CTourism::CreatGraph()
{//读取文件，获得景点信息和道路信息
 //节点信息保存为结构体Vex，道路信息保存为结构体Edge
	m_Graph.Init();
	FILE *fvex;
	fopen_s(&fvex, VEX_FILE_NAME, "r");
	int n;
	fscanf_s(fvex, "%d", &n);
	printf("---Vex(total: %d)---\n", n);										//
	for (int i = 0; i < n; i++)
	{
		Vex sVex;
		fscanf_s(fvex, "%d%20s%1024s", &sVex.num, sVex.name, MAX_NAME_LEN, sVex.desc, MAX_DESC_LEN);
		printf("%d\t%s\t%s\n", sVex.num, sVex.name, sVex.desc);			//
		if (!m_Graph.InsertVex(sVex))
		{
			printf("Insert Vex failed!\n");
			continue;
		}
	}
	fclose(fvex);
	fvex = NULL;

	FILE *fedge;
	fopen_s(&fedge, EDGE_FILE_NAME, "r");
	printf("---Edge---\n");													//
	Edge sEdge;
	while (fscanf_s(fedge, "%d\t%d\t%d\n", &sEdge.vex1, &sEdge.vex2, &sEdge.weight) != EOF)
	{
		printf("%d\t%d\t%d\n", sEdge.vex1, sEdge.vex2, sEdge.weight);	//
		if (!m_Graph.InsertEdge(sEdge))
		{
			printf("Insert Edge failed!\n");
			continue;
		}
	}
	fclose(fedge);
	fedge = NULL;



}

void CTourism::GetSpotInfo(void)
{
	int mVexnum = m_Graph.GetVexnum();
	for (int i = 0; i < mVexnum; i++)
	{
		Vex nVex = m_Graph.GetVex(i);
		printf("Vex.%d-%s\n", nVex.num, nVex.name);
	}

	printf("Input Vex to check: ");
	int n;
	Vex sVex;
	cin >> n;
	printf("Check Vex: %d\n", n);										//
	sVex = m_Graph.GetVex(n);
	printf("%d\t%s\t%s\n", sVex.num, sVex.name, sVex.desc);

	Edge aEdge[MAX_VERTEX_NUM];
	int nEdgeNum = m_Graph.FindEdge(n, aEdge);
	printf("---\n");
	for (int i = 0; i < nEdgeNum; i++)
	{
		Vex vex1 = m_Graph.GetVex(aEdge[i].vex1);
		Vex vex2 = m_Graph.GetVex(aEdge[i].vex2);
		printf("%s->%s\t%d\n", vex1.name, vex2.name, aEdge[i].weight);
	}
}

void CTourism::TravelPath(void)
{
	printf("Input Vex num: ");
	int vexnum;
	cin >> vexnum;
	PathList pList = (PathList)malloc(20 * sizeof(Path));
	PathList head = pList;
	m_Graph.DFSTraverse(vexnum, pList);
	pList = head;
	printf("Routes:\n");
	while (pList->next)
	{
		for (int i = 0; i < m_Graph.GetVexnum(); i++)
		{
			int nvex = pList->vexs[i];
			printf("%s -> ", m_Graph.GetVex(nvex).name);
		}
		printf("\n");
		pList = pList->next;
	}
	
}

void CTourism::FindShortPath(void)
{
}
