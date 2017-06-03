#pragma once
#include"global.h"
#include"GameLogic.h"


class CGameControl
{
public:
	CGameControl(void);
	~CGameControl(void);

	void StartGame();								//��ʼ��Ϸ
	int GetElement(int nRow, int nCol);				//��õ�ͼ��ĳ��ĳ�е�Ԫ��
	void SetFirstPoint(int  nRow, int nCol);
	void SetSecPoint(int  nRow, int nCol);
	bool Link(Vertex avPath[2]);					//�жϵ�һ����͵ڶ������Ƿ���ͬ
	CGameLogic gameLogic;

public:
	int m_anMap[4][4];		//��ʼ��Ϸ��ͼΪ4�С�4��
	Vertex m_ptSelFirst;	//ѡ�еĵ�һ����
	Vertex m_ptSelSec;		//ѡ�еĵڶ�����
};

