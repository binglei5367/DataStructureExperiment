#pragma once
#include"global.h"


class CGameLogic
{
public:
	CGameLogic(void);
	~CGameLogic(void);

public:
	void InitMap(int anMap[][4]);
	bool IsLink(int anMap[][4], Vertex v1, Vertex v2);
	void Clear(int anMap[][4], Vertex v1, Vertex v2);

	bool LinkInRow(int anMap[][4], Vertex v1, Vertex v2);
	bool LinkInCol(int anMap[][4], Vertex v1, Vertex v2);

	bool LineX(int anMap[][4], int nRow, int nCol1, int nCol2);
	bool LineY(int anMap[][4], int nRow1, int nRow2, int nCol);

	bool LinkInTwice(int anMap[][4], Vertex v1, Vertex v2);
	bool LinkInThird(int anMap[][4], Vertex v1, Vertex v2);
	void AddVertex(Vertex v);
	void Delete();

	Vertex m_avPath[4];
	int m_nVertexNum;

};

