#include "StdAfx.h"
#include "GameLogic.h"


CGameLogic::CGameLogic(void)
{
	m_nVertexNum = 0;
}


CGameLogic::~CGameLogic(void)
{
}

void CGameLogic::InitMap(int anMap[][4])
{
	//游戏地图初始化，固定的值
	int anTemp[4][4] = { 2,0,1,3,2,2,1,3,2,1,0,0,1,3,0,3 };
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			anMap[i][j] = anTemp[i][j];
		}
	}
}

bool CGameLogic::IsLink(int anMap[][4], Vertex v1, Vertex v2)
{
	//一条直线连通
	int nRow1 = v1.row;
	int nCol1 = v1.col;
	int nRow2 = v2.row;
	int nCol2 = v2.col;

	AddVertex(v1);
	if (nRow1 == nRow2)
	{//判断是否在行向上连通
		if (LinkInRow(anMap, v1, v2) == true)
		{
			AddVertex(v2);
			return true;
		}
	}
	if (nCol1 == nCol2)
	{//判断是否在列向上连通
		if (LinkInCol(anMap, v1, v2) == true)
		{
			AddVertex(v2);
			return true;
		}
	}

	//两条直线连通
	if (LinkInTwice(anMap, v1, v2) == true)
	{
		AddVertex(v2);
		return true;
	}

	//三条直线连通
	if (LinkInThird(anMap, v1, v2) == true)
	{
		AddVertex(v2);
		return true;
	}

	Delete();//若不能消子，则将v1取出
	return false;

}

void CGameLogic::Clear(int anMap[][4], Vertex v1, Vertex v2)
{
	anMap[v1.row][v1.col] = BLANK;
	anMap[v2.row][v2.col] = BLANK;
}

bool CGameLogic::LinkInRow(int anMap[][4], Vertex v1, Vertex v2)
{
	int nRow = v1.row;
	int nCol1 = v1.col;
	int nCol2 = v2.col;

	if (nCol1 > nCol2)
	{
		int nColTemp = nCol1;
		nCol1 = nCol2;
		nCol2 = nColTemp;
	}

	for (int i = nCol1 + 1; i <= nCol2; i++)
	{
		if (i == nCol2)
		{
			return true;
		}
		if (anMap[nRow][i] != BLANK)
		{//两点间有一点不为空，跳出循环
			break;
		}

	}
	return false;
}

bool CGameLogic::LinkInCol(int anMap[][4], Vertex v1, Vertex v2)
{
	int nRow1 = v1.row;
	int nRow2 = v2.row;
	int nCol = v2.col;

	if (nRow1 > nRow2)
	{
		int nRowTemp = nRow1;
		nRow1 = nRow2;
		nRow2 = nRowTemp;
	}

	for (int i = nRow1 + 1; i <= nRow2; i++)
	{
		if (i == nRow2)
		{
			return true;
		}
		if (anMap[i][nCol] != BLANK)
		{//两点间有一点不为空，跳出循环
			break;
		}

	}
	return false;
}

bool CGameLogic::LinkInTwice(int anMap[][4], Vertex v1, Vertex v2)
{
	Vertex vTemp1, vTemp2, vTemp;
	vTemp1.col = v1.col;
	vTemp1.row = v2.row;
	vTemp2.col = v2.col;
	vTemp2.row = v1.row;

	if ((LinkInCol(anMap, v1, vTemp1) && LinkInRow(anMap, v2, vTemp1)) && (anMap[vTemp1.row][vTemp1.col] == BLANK))
	{
		vTemp.row = v2.row;
		vTemp.col = v1.col;
		AddVertex(vTemp);
		return true;
	}
	if ((LinkInCol(anMap, v2, vTemp2) && LinkInRow(anMap, v1, vTemp2)) && (anMap[vTemp2.row][vTemp2.col] == BLANK))
	{
		vTemp.row = v1.row;
		vTemp.col = v2.col;
		AddVertex(vTemp);
		return true;
	}
	return false;
}

bool CGameLogic::LineX(int anMap[][4], int nRow, int nCol1, int nCol2)
{
	if (nCol1 > nCol2)
	{
		int nColTemp = nCol1;
		nCol1 = nCol2;
		nCol2 = nColTemp;
	}

	for (int i = nCol1 + 1; i <= nCol2; i++)
	{
		if (i == nCol2)
		{
			return true;
		}
		if (anMap[nRow][i] != BLANK)
		{//两点间有一点不为空，跳出循环
			break;
		}

	}
	return false;
}

bool CGameLogic::LineY(int anMap[][4], int nRow1, int nRow2, int nCol)
{
	if (nRow1 > nRow2)
	{
		int nRowTemp = nRow1;
		nRow1 = nRow2;
		nRow2 = nRowTemp;
	}

	for (int i = nRow1 + 1; i <= nRow2; i++)
	{
		if (i == nRow2)
		{
			return true;
		}
		if (anMap[i][nCol] != BLANK)
		{//两点间有一点不为空，跳出循环
			break;
		}

	}
	return false;
}

bool CGameLogic::LinkInThird(int anMap[][4], Vertex v1, Vertex v2)
{
	for (int nCol = 0; nCol < 4; nCol++)
	{
		//找到一条与Y轴平行的连通线段
		if (anMap[v1.row][nCol] == BLANK && anMap[v2.row][nCol] == BLANK)
		{
			if (LineY(anMap, v1.row, v2.row, nCol))
			{
				if (LineX(anMap, v1.row, v1.col, nCol) && LineX(anMap, v2.row, v2.col, nCol))
				{
					//保存节点
					Vertex Vx1 = { v1.row,nCol,BLANK };
					Vertex Vx2 = { v2.row,nCol,BLANK };
					AddVertex(Vx1);
					AddVertex(Vx2);
					return true;
				}
			}
		}
	}
	for (int nRow = 0; nRow < 4; nRow++)
	{
		//找到一条与X轴平行的连通线段
		if (anMap[nRow][v1.col] == BLANK && anMap[nRow][v2.col] == BLANK)
		{
			if (LineX(anMap, nRow, v1.col, v2.col))
			{
				if (LineY(anMap, nRow, v1.row, v1.col) && LineY(anMap, nRow, v2.row, v2.col))
				{
					//保存节点
					Vertex Vx1 = { nRow,v1.col,BLANK };
					Vertex Vx2 = { nRow,v2.col,BLANK };
					AddVertex(Vx1);
					AddVertex(Vx2);
					return true;
				}
			}
		}
	}

	//平行于Y轴的线段在图外面的情况
	bool empty1 = true;
	for (int nCol = 0; nCol < v1.col; nCol++)
	{
		if (anMap[v1.row][nCol] != BLANK)
			empty1 = false;
	}
	for (int nCol = 0; nCol < v2.col; nCol++)
	{
		if (anMap[v2.row][nCol] != BLANK)
			empty1 = false;
	}
	if (empty1 == true)
	{
		Vertex Vx1 = { v1.row,-1,BLANK };
		Vertex Vx2 = { v2.row,-1,BLANK };
		AddVertex(Vx1);
		AddVertex(Vx2);
		return true;
	}

	bool empty2 = true;
	for (int nCol = v1.col + 1; nCol < 4; nCol++)
	{
		if (anMap[v1.row][nCol] != BLANK)
			empty2 = false;
	}
	for (int nCol = v2.col + 1; nCol < 4; nCol++)
	{
		if (anMap[v2.row][nCol] != BLANK)
			empty2 = false;
	}
	if (empty2 == true)
	{
		Vertex Vx1 = { v1.row,4,BLANK };
		Vertex Vx2 = { v2.row,4,BLANK };
		AddVertex(Vx1);
		AddVertex(Vx2);
		return true;
	}

	//平行于X轴的线段在图外面的情况
	bool empty3 = true;
	for (int nRow = 0; nRow < v1.row; nRow++)
	{
		if (anMap[nRow][v1.col] != BLANK)
			empty3 = false;
	}
	for (int nRow = 0; nRow < v2.row; nRow++)
	{
		if (anMap[nRow][v2.col] != BLANK)
			empty3 = false;
	}
	if (empty3 == true)
	{
		Vertex Vx1 = { -1,v1.col,BLANK };
		Vertex Vx2 = { -1,v2.col,BLANK };
		AddVertex(Vx1);
		AddVertex(Vx2);
		return true;
	}

	bool empty4 = true;
	for (int nRow = v1.row + 1; nRow < 4; nRow++)
	{
		if (anMap[nRow][v1.col] != BLANK)
			empty4 = false;
	}
	for (int nRow = v2.row + 1; nRow < 4; nRow++)
	{
		if (anMap[nRow][v2.col] != BLANK)
			empty4 = false;
	}
	if (empty4 == true)
	{
		Vertex Vx1 = { 4,v1.col,BLANK };
		Vertex Vx2 = { 4,v2.col,BLANK };
		AddVertex(Vx1);
		AddVertex(Vx2);
		return true;
	}

	return false;
}

void CGameLogic::AddVertex(Vertex v)
{
	m_avPath[m_nVertexNum] = v;
	m_nVertexNum++;
}

void CGameLogic::Delete()
{
	m_nVertexNum--;
}