#pragma once
#include"global.h"
#include"GameLogic.h"


class CGameControl
{
public:
	CGameControl(void);
	~CGameControl(void);

	void StartGame();								//开始游戏
	int GetElement(int nRow, int nCol);				//获得地图中某行某列的元素
	void SetFirstPoint(int  nRow, int nCol);
	void SetSecPoint(int  nRow, int nCol);
	bool Link(Vertex avPath[2]);					//判断第一个点和第二个点是否相同
	CGameLogic gameLogic;

public:
	int m_anMap[4][4];		//初始游戏地图为4行、4列
	Vertex m_ptSelFirst;	//选中的第一个点
	Vertex m_ptSelSec;		//选中的第二个点
};

