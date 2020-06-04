#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include"Graph.h"
#define MAX 10000
#define VexFile "Data/Vex.txt"
#define EdgeFile "Data/Edge.txt"
using namespace std;

void Graph::InitGraph()
{
	//读取顶点信息
	int num = 0;//记录读取的顶点数
	FILE* v_fp = NULL;
	if ((v_fp = fopen(VexFile, "rb")) == NULL)
	{
		cout<<"VexFile文件打开失败！"<<endl;
		return;
	}
	fscanf(v_fp, "%d", &vexNum);//读取总顶点数
	//cout << vexNum << endl;
	while (!feof(v_fp))
	{
		Vex vex;
		fscanf(v_fp, "%d %s %s", &vex.num, vex.name, vex.desc);//读取一个顶点信息
		InsertVex(vex, num);//加入读取的顶点到图中
		num++;
	}
	fclose(v_fp);//关闭文件

	//读取边信息
	
	for (int i = 0;i < vexNum;i++)
	{
		for (int j = 0;j < vexNum;j++)
		{
			adjMatrix[i][j] = MAX;
		}
	}

	FILE* e_fp = NULL;
	if ((e_fp = fopen(EdgeFile, "rb")) == NULL)
	{
		cout << "EdgeFile文件打开失败！" << endl;
		return;
	}
	while (!feof(e_fp))
	{
		Edge edge;
		fscanf(e_fp, "%d %d %d", &edge.vex1, &edge.vex2, &edge.weight);//读取一条边信息
		InsertEdge(edge);//加入读取的边到图中
	}
	cout << "创建景区成功！" << endl;
}

int Graph::GetVexNum()
{
	return this->vexNum;
}

void Graph::InsertVex(Vex& vex, int num)
{
	vexs[num] = vex;
}

void Graph::InsertEdge(Edge& edge)
{
	int a = edge.vex1;//获得第一个顶点的编号
	int b = edge.vex2;//获得第二个顶点的编号
	adjMatrix[a][b] = adjMatrix[b][a] = edge.weight;
}

Vex Graph::SearchVex(int nVex)
{
	for (int i = 0;i < vexNum;i++)
	{
		if (vexs[i].num == nVex)
		{
			return vexs[i];
		}
	}
}

int Graph::SearchEdges(int nVex, Edge aEdge[])
{
	int num = 0;//记录相邻的边数
	for (int i = 0;i < vexNum;i++)
	{
		if (adjMatrix[nVex][i] < MAX)
		{
			Edge edge = { nVex,i,adjMatrix[nVex][i] };//构造邻接矩阵中查到的相邻边
			aEdge[num] = edge;
			num++;
		}
	}
	return num;
}

void Graph::DFS(int nVex, int* bVisted, int nIndex, int* pList, int& ways)//深度遍历图，获得从指定景点开始的游览路径
{
	pList[nIndex] = nVex;
	bVisted[nVex] = 1;//访问过的景点标记为1
	if (nIndex == vexNum - 1)//全部遍历完毕
	{
		ways++;
		for (int i = 0;i < vexNum;i++)
		{
			cout << SearchVex(pList[i]).name;
			if (i < vexNum - 1)
				cout << "-->";
		}
		cout << endl;
	}
	else
	{
		for (int i = 0;i < vexNum;i++)
		{
			if (adjMatrix[nVex][i] < MAX && bVisted[i] == 0)//如果两点相连且访问点未被访问过
			{
				DFS(i, bVisted, nIndex + 1, pList, ways);//递归
			}
		}
	}
	bVisted[nVex] = 0;//还原状态
}

int Graph::FindShortPath(int nVexStart, int nVexEnd, Edge aPath[])//搜索最短路径
{
	int* dist = new int[vexNum];//存储当前求到的从顶点v 到顶点 j 的最短路径长度
	int* S = new int[vexNum];//存放已求得最短路径的顶点
	int* path = new int[vexNum];//存放求到的最短路径
	for (int i = 0;i < vexNum;i++)//初始化
	{
		dist[i] = adjMatrix[nVexStart][i];
		S[i] = 0;
		if (i != nVexStart && adjMatrix[nVexStart][i] < MAX)
			path[i] = nVexStart;
		else
			path[i] = -1;
	}
	S[nVexStart] = 1;//将起始点加入S
	dist[nVexStart] = 0;
	for (int i = 0;i < vexNum - 1;i++)//算法过程
	{
		int u;
		int min = MAX;
		for (int k = 0;k < vexNum;k++)//找到当前不在集合S中且具有最短路径的顶点
		{
			if (S[k] == 0 && dist[k] != -1 && dist[k] < min)
			{
				min = dist[k];
				u = k;
			}
		}
		S[u] = 1;//将u加入S
		for (int j = 0;j < vexNum;j++)//修改
		{
			if (S[j] == 0 && adjMatrix[u][j] < MAX && dist[u] + adjMatrix[u][j] < dist[j])
			{
				dist[j] = dist[u] + adjMatrix[u][j];
				path[j] = u;
			}
		}
	}
	/*for (int i = 0;i < vexNum;i++)
		cout << path[i] << " ";
	cout << endl;*/
	//返回最短路径
	int n = 0;
	int num = nVexEnd;
	while (true)
	{
		if (num == nVexStart)
			break;
		Edge edge = { num,path[num],adjMatrix[num][path[num]] };
		aPath[n++] = edge;
		num = path[num];
	}
	return n;
}

int Graph::FindMinTree(Edge aPath[])//构建最小生成树
{
	int n = 0;//存储边数
	int u = 0;//起始顶点
	int* lowcost = new int[vexNum];//距离
	int* vex = new int[vexNum];//最近顶点
	for (int v = 0;v < vexNum;v++)//初始化
	{
		vex[v] = u;
		lowcost[v] = adjMatrix[u][v];
	}
	for (int i = 0;i < vexNum - 1;i++)
	{
		int k;
		int min = MAX;
		for (int j = 1;j < vexNum;j++)//找当前最小边
		{
			if (lowcost[j] < min && lowcost[j] != 0)
			{
				min = lowcost[j];
				k = j;
			}
		}
		Edge edge = { vex[k],k,min };
		aPath[n++] = edge;				//加入最小生成树
		lowcost[k] = 0;
		for (int v = 0;v < vexNum;v++)//修改数组值
		{
			if (adjMatrix[k][v] < lowcost[v])
			{
				lowcost[v] = adjMatrix[k][v];
				vex[v] = k;
			}
		}
	}
	return n;
}