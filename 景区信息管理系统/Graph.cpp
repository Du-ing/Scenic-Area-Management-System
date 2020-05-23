#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include"Graph.h"
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
	cout << "创建级景区成功！" << endl;
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
		if (adjMatrix[nVex][i] != 0)
		{
			Edge edge = { nVex,i,adjMatrix[nVex][i] };//构造邻接矩阵中查到的相邻边
			aEdge[num] = edge;
			num++;
		}
	}
	return num;
}