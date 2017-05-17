// GraphCPro.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
using namespace std;

int main()
{
	unsigned int choice = 0;
	bool bRunning = true;
	bool gCreated = false;
	CTourism m_Tourism;
	while(bRunning)
	{
		cout << "====景区信息管理系统====" << endl;
		cout << "1.创建景区景点图" << endl;
		cout << "2.查询景点信息" << endl;
		cout << "3.旅游景点导航" << endl;
		cout << "4.搜索最短路径" << endl;
		cout << "5.铺设电路规划" << endl;
		cout << "0.退出" << endl;
		cout << "输入操作编号: ";
		cin >> choice;

		switch (choice)
		{
		case 1:
			m_Tourism.CreatGraph();
			gCreated = true;
			break;
		case 2:
			if (gCreated)m_Tourism.GetSpotInfo();
			break;
		case 3:
			if (gCreated)m_Tourism.TravelPath();
			break;
		case 4:
			if (gCreated)m_Tourism.FindShortPath();
			break;
		case 5:
			if (gCreated)m_Tourism.DesignPath();
			break;
		case 0:
			bRunning = false;
			break;
		default:
			break;
		}
	}



    return 0;
}

