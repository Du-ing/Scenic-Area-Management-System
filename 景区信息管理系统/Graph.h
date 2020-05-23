#pragma once
typedef struct Vex
{
	int num;//景点编号
	char name[20];//景点名称
	char desc[1024];//景点描述
}Vex;

typedef struct Edge
{
	int vex1, vex2;//边的两个顶点
	int weight;//边的权值
}Edge;

typedef struct Graph
{
	Vex vexs[20]; //顶点数组
	int vexNum; //顶点个数
	int adjMatrix[20][20]; //邻接矩阵,存储边

	void InitGraph();//初始化图
	int GetVexNum();//获取图的顶点数
	void InsertVex(Vex& vex, int num);//将顶点添加到顶点数组中
	void InsertEdge(Edge& edge);//将边保存到邻接矩阵中
	Vex SearchVex(int nVex);//根据编号查询顶点信息
	int SearchEdges(int nVex, Edge aEdge[]);//查询指定顶点相连的边
}Graph;//Graph对象，用于存储景区景点图

