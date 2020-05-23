#include<iostream>
#include"Tourism.h"
using namespace std;

int main()
{
	while (true)
	{
		int flag;
		menu();
		cin >> flag;
		switch (flag)
		{
			case 1:creatGraph();break;
			case 2:getSpotInfo();break;
			case 3:
			case 4:
			case 5:
			case 0:break;
			default:cout << "输入无效！请重新输入" << endl;break;
		}
	}
	return 0;
}