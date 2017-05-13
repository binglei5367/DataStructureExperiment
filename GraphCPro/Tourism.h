#pragma once
#define VEX_FILE_NAME "Vex.txt"
#define EDGE_FILE_NAME "Edge.txt"


class CTourism
{
public:
	CTourism(void);
	~CTourism(void);

private:
	CGraph m_Graph;

public:
	//
	void CreatGraph(void);
	//
	void GetSpotInfo(void);
	//
	void TravelPath(void);
	//
	void FindShortPath(void);
};

