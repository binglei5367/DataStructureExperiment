#include "stdafx.h"

CGraph::CGraph(){}
CGraph::~CGraph() {}

void CGraph::Init(void)
{//权值信息初始化为0
	for (int i = 0; i < MAX_VERTEX_NUM; i++)
	{
		for (int j = 0; j < MAX_VERTEX_NUM; j++)
		{
			m_aAdjMatrix[i][j] = 0;
		}
	}
	m_nVexNum = 0;
	
}

bool CGraph::InsertVex(Vex sVex)
{
	if (m_nVexNum == MAX_VERTEX_NUM)
	{
		//顶点已满
		return false;
	}
	m_aVex[m_nVexNum++] = sVex;
	return true;
}

bool CGraph::InsertEdge(Edge sEdge)
{
	if (sEdge.vex1 < 0 || sEdge.vex1 >= m_nVexNum || sEdge.vex2 < 0 || sEdge.vex2 >= m_nVexNum)
	{
		//下标越界
		return false;
	}
	m_aAdjMatrix[sEdge.vex1][sEdge.vex2] = sEdge.weight;
	m_aAdjMatrix[sEdge.vex2][sEdge.vex1] = sEdge.weight;
	return true;
}

Vex CGraph::GetVex(int nVex)
{
	return m_aVex[nVex];
}

int CGraph::FindEdge(int nVex, Edge aEdge[])
{
	int k = 0;
	for (int i = 0; i < m_nVexNum; i++)
	{
		if (m_aAdjMatrix[nVex][i] != 0)
		{
			Edge aedge;
			aedge.vex1 = nVex;
			aedge.vex2 = i;
			aedge.weight = m_aAdjMatrix[nVex][i];
			aEdge[k] = aedge;
			k++;
		}
	}
	return k;
}

int CGraph::GetVexnum(void)
{
	return m_nVexNum;
}

void CGraph::DFS(int nVex, bool bVisited[], int & nIndex, PathList & pList)
{
	bVisited[nVex] = true;
	pList->vexs[nIndex++] = nVex;
	int nVexNum = 0;
	for (int i = 0; i < m_nVexNum; i++)
	{
		if (bVisited[i]) nVexNum++;
	}
	if (nVexNum == m_nVexNum)
	{
		pList->next = (PathList)malloc(sizeof(Path));
		for (int i = 0; i < m_nVexNum; i++)
		{
			pList->next->vexs[i] = pList->vexs[i];
		}
		pList = pList->next;
		pList->next = NULL;
	}
	else
	{
		for (int i = 0; i < m_nVexNum; i++)
		{
			if ((!bVisited[i]) && (m_aAdjMatrix[nVex][i] > 0))
			{
				DFS(i, bVisited, nIndex, pList);
				bVisited[i] = false;
				nIndex--;
			}
		}
	}
}

void CGraph::DFSTraverse(int nVex, PathList &pList)
{
	int nIndex = 0;
	bool aVisited[MAX_VERTEX_NUM] = { false };
	DFS(nVex, aVisited, nIndex, pList);
}

int CGraph::FindShortPath(int nVexStart, int nVexEnd, Edge aPath[])
{
	int nShortPath[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
	int nShortDistence[MAX_VERTEX_NUM];
	bool aVisited[MAX_VERTEX_NUM];
	int v;

	//初始化最短路径和最短距离
	for (v = 0; v < m_nVexNum; v++)
	{
		aVisited[v] = false;
		if (m_aAdjMatrix[nVexStart][v])
		{
			nShortDistence[v] = m_aAdjMatrix[nVexStart][v];
		}
		else
		{
			nShortDistence[v] = MAX_DISTENCE;
		}
		nShortPath[v][0] = nVexStart;
		for (int i = 1; i < m_nVexNum; i++)
		{
			nShortPath[v][i] = -1;
		}

	}

	aVisited[nVexStart] = true;
	for (int i = 1; i < m_nVexNum; i++)
	{
		bool canAdd = false;
		int minDis = MAX_DISTENCE;
		for (int w = 0; w < m_nVexNum; w ++ )
		{
			if (!aVisited[w])
			{
				if (nShortDistence[w] < minDis)
				{
					v = w;
					minDis = nShortDistence[w];
					canAdd = true;
				}
			}
			if (!canAdd)break;
		}
		//将点加入集合
		aVisited[i] = true;
	}


	return 0;
}


int CGraph::MiniSpanTree(Edge aPath[])
{
	bool bVisited[MAX_VERTEX_NUM] = { false };
	int min = INT16_MAX;
	int k = 0;
	bVisited[0] = true;
	int nVex1, nVex2, n = 0;
	for (k = 0; k < this->m_nVexNum - 1; k++)
	{
		min = INT16_MAX;
		for (int i = 0; i < this->m_nVexNum; i++)
		{
			if (bVisited[i])
			{
				n++;
				for (int j = 0; j < this->m_nVexNum; j++)
				{
					if ((!bVisited[j]) && (this->m_aAdjMatrix[i][j] < min) && (this->m_aAdjMatrix[j][i] < min))
					{
						min = this->m_aAdjMatrix[i][j];
						nVex1 = i; nVex2 = j;
					}
				}
			}
		}
		aPath[k].vex1 = nVex1;
		aPath[k].vex2 = nVex2;
		aPath[k].weight = min;
		bVisited[nVex1] = true;
		bVisited[nVex2] = true;
	}
	return k;
}