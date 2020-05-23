#include<iostream>
#include"Graph.h"
using namespace std;

Graph graph;//存储图的全局变量

void menu()//显示菜单
{
	cout << "=====景区信息管理系统=====" << endl;
	cout << "1.创建景区景点图" << endl;
	cout << "2.查询景点信息" << endl;
	cout << "3.旅游景点导航" << endl;
	cout << "4.搜索最短路径" << endl;
	cout << "5.铺设电路规划" << endl;
	cout << "0.退出系统" << endl;
	cout << "==========================" << endl;
	cout << "请输入操作编号(0~5):";
}

void creatGraph()//创建一个景区
{
	graph.InitGraph();
}

void getSpotInfo()//查询景点相关信息
{
	int nVex;
	cout << "请输入想要了解的景点编号:";
	cin >> nVex;
	Vex vex = graph.SearchVex(nVex);//获得编号对应的景点
	cout << "景点信息如下:" << endl;
	cout << "==========================" << endl;
	cout << vex.name << endl;
	cout << vex.desc << endl;
	
	Edge edges[10];//存储顶点相邻的边
	int n = graph.SearchEdges(nVex, edges);//返回相邻的边数
	cout << "-----景点周边景区-----" << endl;
	for (int i = 0;i < n;i++)
	{
		int a = edges[i].vex1;//顶点一的编号
		int b = edges[i].vex2;//顶点二的编号
		Vex v1 = graph.SearchVex(a);//顶点一
		Vex v2 = graph.SearchVex(b);//顶点二
		cout << v1.name << "-->" << v2.name << ":" << edges[i].weight << "m" << endl;	
	}
}