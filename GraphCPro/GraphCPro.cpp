// GraphCPro.cpp : �������̨Ӧ�ó������ڵ㡣
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
		cout << "====������Ϣ����ϵͳ====" << endl;
		cout << "1.������������ͼ" << endl;
		cout << "2.��ѯ������Ϣ" << endl;
		cout << "3.���ξ��㵼��" << endl;
		cout << "4.�������·��" << endl;
		cout << "5.�����·�滮" << endl;
		cout << "0.�˳�" << endl;
		cout << "����������: ";
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

