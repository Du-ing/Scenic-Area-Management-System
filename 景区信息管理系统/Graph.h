#pragma once
typedef struct Vex
{
	int num;//������
	char name[20];//��������
	char desc[1024];//��������
}Vex;

typedef struct Edge
{
	int vex1, vex2;//�ߵ���������
	int weight;//�ߵ�Ȩֵ
}Edge;

typedef struct Graph
{
	Vex vexs[20]; //��������
	int vexNum; //�������
	int adjMatrix[20][20]; //�ڽӾ���,�洢��

	void InitGraph();//��ʼ��ͼ
	int GetVexNum();//��ȡͼ�Ķ�����
	void InsertVex(Vex& vex, int num);//��������ӵ�����������
	void InsertEdge(Edge& edge);//���߱��浽�ڽӾ�����
	Vex SearchVex(int nVex);//���ݱ�Ų�ѯ������Ϣ
	int SearchEdges(int nVex, Edge aEdge[]);//��ѯָ�����������ı�
}Graph;//Graph�������ڴ洢��������ͼ

