#include "StdAfx.h"
#include "GameControl.h"


CGameControl::CGameControl(void)
{
}


CGameControl::~CGameControl(void)
{
}

void CGameControl::StartGame()
{
	gameLogic.InitMap(m_anMap);
}

int CGameControl::GetElement(int nRow, int nCol)
{
	return m_anMap[nRow][nCol];
}

void CGameControl::SetFirstPoint(int  nRow, int nCol)
{
	m_ptSelFirst.row = nRow;
	m_ptSelFirst.col = nCol;
}
void CGameControl::SetSecPoint(int  nRow, int nCol)
{
	m_ptSelSec.row = nRow;
	m_ptSelSec.col = nCol;
}

bool CGameControl::Link(Vertex avPath[2])
{
	//�ж�m_ptSelFirst��m_ptSelSec�Ƿ���ͨ
	if (m_ptSelFirst.row == m_ptSelSec.row && m_ptSelFirst.col == m_ptSelSec.col)
	{
		return false;
	}

	if (m_anMap[m_ptSelFirst.row][m_ptSelFirst.col] == m_anMap[m_ptSelSec.row][m_ptSelSec.col] && gameLogic.IsLink(m_anMap, m_ptSelFirst, m_ptSelSec))
	{
		//����ΪԪ����ͬʱ�������м�û���ڵ�
		for (int i = 0; i < gameLogic.m_nVertexNum; i++)
		{
			avPath[i] = gameLogic.m_avPath[i];
		}
		return true;
	}
	return false;
}

