#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include"Graph.h"
#define MAX 10000
#define VexFile "Data/Vex.txt"
#define EdgeFile "Data/Edge.txt"
using namespace std;

void Graph::InitGraph()
{
	//��ȡ������Ϣ
	int num = 0;//��¼��ȡ�Ķ�����
	FILE* v_fp = NULL;
	if ((v_fp = fopen(VexFile, "rb")) == NULL)
	{
		cout<<"VexFile�ļ���ʧ�ܣ�"<<endl;
		return;
	}
	fscanf(v_fp, "%d", &vexNum);//��ȡ�ܶ�����
	//cout << vexNum << endl;
	while (!feof(v_fp))
	{
		Vex vex;
		fscanf(v_fp, "%d %s %s", &vex.num, vex.name, vex.desc);//��ȡһ��������Ϣ
		InsertVex(vex, num);//�����ȡ�Ķ��㵽ͼ��
		num++;
	}
	fclose(v_fp);//�ر��ļ�

	//��ȡ����Ϣ
	
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
		cout << "EdgeFile�ļ���ʧ�ܣ�" << endl;
		return;
	}
	while (!feof(e_fp))
	{
		Edge edge;
		fscanf(e_fp, "%d %d %d", &edge.vex1, &edge.vex2, &edge.weight);//��ȡһ������Ϣ
		InsertEdge(edge);//�����ȡ�ıߵ�ͼ��
	}
	cout << "���������ɹ���" << endl;
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
	int a = edge.vex1;//��õ�һ������ı��
	int b = edge.vex2;//��õڶ�������ı��
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
	int num = 0;//��¼���ڵı���
	for (int i = 0;i < vexNum;i++)
	{
		if (adjMatrix[nVex][i] < MAX)
		{
			Edge edge = { nVex,i,adjMatrix[nVex][i] };//�����ڽӾ����в鵽�����ڱ�
			aEdge[num] = edge;
			num++;
		}
	}
	return num;
}

void Graph::DFS(int nVex, int* bVisted, int nIndex, int* pList, int& ways)//��ȱ���ͼ����ô�ָ�����㿪ʼ������·��
{
	pList[nIndex] = nVex;
	bVisted[nVex] = 1;//���ʹ��ľ�����Ϊ1
	if (nIndex == vexNum - 1)//ȫ���������
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
			if (adjMatrix[nVex][i] < MAX && bVisted[i] == 0)//������������ҷ��ʵ�δ�����ʹ�
			{
				DFS(i, bVisted, nIndex + 1, pList, ways);//�ݹ�
			}
		}
	}
	bVisted[nVex] = 0;//��ԭ״̬
}

int Graph::FindShortPath(int nVexStart, int nVexEnd, Edge aPath[])//�������·��
{
	int* dist = new int[vexNum];//�洢��ǰ�󵽵ĴӶ���v ������ j �����·������
	int* S = new int[vexNum];//�����������·���Ķ���
	int* path = new int[vexNum];//����󵽵����·��
	for (int i = 0;i < vexNum;i++)//��ʼ��
	{
		dist[i] = adjMatrix[nVexStart][i];
		S[i] = 0;
		if (i != nVexStart && adjMatrix[nVexStart][i] < MAX)
			path[i] = nVexStart;
		else
			path[i] = -1;
	}
	S[nVexStart] = 1;//����ʼ�����S
	dist[nVexStart] = 0;
	for (int i = 0;i < vexNum - 1;i++)//�㷨����
	{
		int u;
		int min = MAX;
		for (int k = 0;k < vexNum;k++)//�ҵ���ǰ���ڼ���S���Ҿ������·���Ķ���
		{
			if (S[k] == 0 && dist[k] != -1 && dist[k] < min)
			{
				min = dist[k];
				u = k;
			}
		}
		S[u] = 1;//��u����S
		for (int j = 0;j < vexNum;j++)//�޸�
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
	//�������·��
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

int Graph::FindMinTree(Edge aPath[])//������С������
{
	int n = 0;//�洢����
	int u = 0;//��ʼ����
	int* lowcost = new int[vexNum];//����
	int* vex = new int[vexNum];//�������
	for (int v = 0;v < vexNum;v++)//��ʼ��
	{
		vex[v] = u;
		lowcost[v] = adjMatrix[u][v];
	}
	for (int i = 0;i < vexNum - 1;i++)
	{
		int k;
		int min = MAX;
		for (int j = 1;j < vexNum;j++)//�ҵ�ǰ��С��
		{
			if (lowcost[j] < min && lowcost[j] != 0)
			{
				min = lowcost[j];
				k = j;
			}
		}
		Edge edge = { vex[k],k,min };
		aPath[n++] = edge;				//������С������
		lowcost[k] = 0;
		for (int v = 0;v < vexNum;v++)//�޸�����ֵ
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