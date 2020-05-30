#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include"Graph.h"
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
		if (adjMatrix[nVex][i] != 0)
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
			if (adjMatrix[nVex][i] != 0 && bVisted[i] == 0)//������������ҷ��ʵ�δ�����ʹ�
			{
				DFS(i, bVisted, nIndex + 1, pList, ways);//�ݹ�
			}
		}
	}
	bVisted[nVex] = 0;//��ԭ״̬
}