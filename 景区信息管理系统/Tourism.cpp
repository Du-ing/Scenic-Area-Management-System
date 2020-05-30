#include<iostream>
#include"Graph.h"
using namespace std;

Graph graph;//�洢ͼ��ȫ�ֱ���

void menu()//��ʾ�˵�
{
	cout << "=====������Ϣ����ϵͳ=====" << endl;
	cout << "1.������������ͼ" << endl;
	cout << "2.��ѯ������Ϣ" << endl;
	cout << "3.���ξ��㵼��" << endl;
	cout << "4.�������·��" << endl;
	cout << "5.�����·�滮" << endl;
	cout << "0.�˳�ϵͳ" << endl;
	cout << "==========================" << endl;
	cout << "������������(0~5):";
}

void creatGraph()//����һ������
{
	graph.InitGraph();
}

void getSpotInfo()//��ѯ���������Ϣ
{
	int nVex;
	cout << "��������Ҫ�˽�ľ�����:";
	cin >> nVex;
	Vex vex = graph.SearchVex(nVex);//��ñ�Ŷ�Ӧ�ľ���
	cout << "������Ϣ����:" << endl;
	cout << "==========================" << endl;
	cout << vex.name << endl;
	cout << vex.desc << endl;
	
	Edge edges[10];//�洢�������ڵı�
	int n = graph.SearchEdges(nVex, edges);//�������ڵı���
	cout << "-----�����ܱ߾���-----" << endl;
	for (int i = 0;i < n;i++)
	{
		int a = edges[i].vex1;//����һ�ı��
		int b = edges[i].vex2;//������ı��
		Vex v1 = graph.SearchVex(a);//����һ
		Vex v2 = graph.SearchVex(b);//�����
		cout << v1.name << "-->" << v2.name << ":" << edges[i].weight << "m" << endl;	
	}
}

void travlePath()//���ξ��㵼��
{
	cout << "=====���ξ��㵼��=====" << endl;
	for (int i = 0;i < graph.GetVexNum();i++)//���ͼ�����о���
	{
		Vex v = graph.SearchVex(i);
		cout << i << "--" << v.name << endl;
	}
	cout << "=====================" << endl;
	cout << "��������ʼ����ı��:";
	int start;
	cin >> start;

	int* bVisted = new int[graph.GetVexNum()];//��Ǿ����Ƿ���ʹ�
	for (int i = 0;i < graph.GetVexNum();i++)
		bVisted[i] = 0;
	int* pList = new int[graph.GetVexNum()];//��¼����·��
	for (int i = 0;i < graph.GetVexNum();i++)
		pList[i] = 0;
	int ways = 0;
	cout << "��" << graph.SearchVex(start).name << "��ʼ�ĵ���·������:" << endl;
	graph.DFS(start, bVisted, 0, pList, ways);
}