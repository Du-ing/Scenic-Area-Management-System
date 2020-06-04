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

void travlePath()//旅游景点导航
{
	cout << "=====旅游景点导航=====" << endl;
	for (int i = 0;i < graph.GetVexNum();i++)//输出图中所有景点
	{
		Vex v = graph.SearchVex(i);
		cout << i << "--" << v.name << endl;
	}
	cout << "=====================" << endl;
	cout << "请输入起始景点的编号:";
	int start;
	cin >> start;

	int* bVisted = new int[graph.GetVexNum()];//标记景点是否访问过
	for (int i = 0;i < graph.GetVexNum();i++)
		bVisted[i] = 0;
	int* pList = new int[graph.GetVexNum()];//记录导航路线
	for (int i = 0;i < graph.GetVexNum();i++)
		pList[i] = 0;
	int ways = 0;
	cout << "从" << graph.SearchVex(start).name << "开始的导航路线如下:" << endl;
	graph.DFS(start, bVisted, 0, pList, ways);
}

void FindShortPath()
{
	cout << "=====搜索最短路径=====" << endl;
	for (int i = 0;i < graph.GetVexNum();i++)//输出图中所有景点
	{
		Vex v = graph.SearchVex(i);
		cout << i << "--" << v.name << endl;
	}

	int start, end;
	cout << "请输入起点的编号:";
	cin >> start;
	cout << "请输入终点的编号:";
	cin >> end;
	cout << "最短路线如下:" << endl;
	Edge* aPath = new Edge[graph.GetVexNum()];//存储最短的路径
	int n = graph.FindShortPath(start, end, aPath);
	int length = 0;//路径长度
	for (int i = n - 1;i >= 0;i--)
	{
		Vex v = graph.SearchVex(aPath[i].vex2);
		cout << v.name << "-->";
		length += aPath[i].weight;
	}
	Vex v = graph.SearchVex(aPath[0].vex1);
	cout << v.name << endl;
	cout << "最短距离为:" << length << "m" << endl;
}

void DesignPath()
{
	cout << "=====铺设电路规划=====" << endl;
	cout << "铺设电路规划如下:" << endl;
	Edge* path = new Edge[graph.GetVexNum()];
	int n = graph.FindMinTree(path);
	int sum = 0;
	for (int i = 0;i < n;i++)
	{
		Vex v1 = graph.SearchVex(path[i].vex1);
		Vex v2 = graph.SearchVex(path[i].vex2);
		cout << v1.name << "==" << v2.name << "  " << path[i].weight << "m" << endl;
		sum += path[i].weight;
	}
	cout << "铺设电路总长度为:" << sum << "m" << endl;
}

void ExitSystem()
{
	cout << "景区管理系统已退出，感谢使用！" << endl;
	exit(0);
}