#include "Graph.h"

bool visited[MAX] = { 0 };
int conVerID[MAX] = { 0 };  //��������������ͨ��֧
EdgeType edges[MAX * MAX];
EdgeType treeEdges[MAX];
bool edgeused[MAX * MAX];  //��Ǳ��Ƿ�ʹ�ù�
int path[MAX];
int dist[MAX];
int Dist[MAX][MAX];
int Path[MAX][MAX];
int main(void)
{
	int choice;
	Graph G;
	char fileName[20];  //�ļ���

	while (true)
	{
		cout << "0.�˳�" << endl;
		cout << "1.��ӡ��ͼ�����������ֱ�����" << endl;
		cout << "2.�����ͼ�еıߣ��򻡣�����Ŀ" << endl;
		cout << "3.V0����������ȱ���ͼG�������������������ɭ��" << endl;
		cout << "4.V0����������ȱ���ͼG�������������������ɭ��" << endl;
		cout << "5.ʵ��Prim�㷨" << endl;
		cout << "6.ʵ��Kruskal�㷨" << endl;
		cout << "7.ʵ��Dijkstra�㷨" << endl;
		cout << "8.ʵ��Floyd�㷨" << endl;
		cout << "9.���ͼG����������" << endl;
		cout << "10.���AOE���Ĺؼ�·��" << endl;
		cout << "������ѡ�";
		cin >> choice;
		system("cls");
		
		switch (choice)
		{
		case 0:
		{
			if (G.VerNum > 0)
				DestroyGraph(G);
			return 0;
		}
		case 1:
		{
			while (true)
			{
				cout << "�������ļ�����#�˳�����";
				cin >> fileName;
				if (strcmp(fileName, "#") == 0)
					break;
				if (CreateGrpFromFile1(fileName, G) == false)
				{
					system("pause");
					break;
				}
				cout << "������ȱ���" << endl;
				universal_DFS(G);
				cout << endl;
				cout << "������ȱ���" << endl;
				universal_BFS(G);
				cout << endl;
				DestroyGraph(G);
			}
			break;
		}
		case 2:
		{
			while (true)
			{
				int Arcnum;
				cout << "�������ļ�����#�˳�����";
				cin >> fileName;
				if (strcmp(fileName, "#") == 0)
					break;
				if (CreateGrpFromFile1(fileName, G) == false)
				{
					system("pause");
					break;
				}
				Arcnum = count_edge(G);
				print_edge(G);
				cout << "��ͼ�ıߣ���������" << Arcnum << endl;
				DestroyGraph(G);
			}
			break;
		}
		case 3:
		{
			while (true)
			{
				int v0;
				cout << "�������ļ�����#�˳�����";
				cin >> fileName;
				if (strcmp(fileName, "#") == 0)
					break;
				if (CreateGrpFromFile1(fileName, G) == false)
				{
					system("pause");
					break;
				}
				cout << "���������v0"<<"(1~"<<G.VerNum<<")��";
				cin >> v0;
				print_edge(G);
				BFS_generate_forest(G, v0);
				print_forest_edge(G, v0);
				DestroyGraph(G);
			}
			break;
		}
		case 4:
		{
			while (true)
			{
				int v0;
				cout << "�������ļ�����#�˳�����";
				cin >> fileName;
				if (strcmp(fileName, "#") == 0)
					break;
				if (CreateGrpFromFile1(fileName, G) == false)
				{
					system("pause");
					break;
				}
				cout << "���������v0" << "(1~" << G.VerNum << ")��";
				cin >> v0;
				print_edge(G);
				DFS_generate_forest(G, v0);
				print_forest_edge(G, v0);
				DestroyGraph(G);
			}
			break;
		}
		case 5:
		{
			while (true)
			{
				int v0;
				cout << "�������ļ�����#�˳�����";
				cin >> fileName;
				if (strcmp(fileName, "#") == 0)
					break;
				if (CreateGrpFromFile1(fileName, G) == false)
				{
					system("pause");
					break;
				}
				cout << "���������v0" << "(1~" << G.VerNum << ")��";
				cin >> v0;
				print_edge(G);
				Prim(G, v0);
				DestroyGraph(G);
			}
			break;
		}
		case 6:
		{
			while (true)
			{
				cout << "�������ļ�����#�˳�����";
				cin >> fileName;
				if (strcmp(fileName, "#") == 0)
					break;
				if (CreateGrpFromFile1(fileName, G) == false)
				{
					system("pause");
					break;
				}
				print_edge(G);
				Kruskal(G, edges, treeEdges, edgeused);
				DestroyGraph(G);
			}
			break;
		}
		case 7:
		{
			while (true)
			{
				int vID;
				cout << "�������ļ�����#�˳�����";
				cin >> fileName;
				if (strcmp(fileName, "#") == 0)
					break;
				if (CreateGrpFromFile1(fileName, G) == false)
				{
					system("pause");
					break;
				}
				cout << "��������㣺";
				cin >> vID;
				Dijkstra(G, vID);
				Print_Dijkstra(G, vID);
				DestroyGraph(G);
			}
			break;
		}
		case 8:
		{
			while (true)
			{
				int vID;
				cout << "�������ļ�����#�˳�����";
				cin >> fileName;
				if (strcmp(fileName, "#") == 0)
					break;
				if (CreateGrpFromFile1(fileName, G) == false)
				{
					system("pause");
					break;
				}
				cout << "��������㣺";
				cin >> vID;
				Floyd(G);
				print_Floyd(G);
				DestroyGraph(G);
			}
			break;
		}
		case 9:
		{
			while (true)
			{
				int topoList[MAX];
				cout << "�������ļ�����#�˳�����";
				cin >> fileName;
				if (strcmp(fileName, "#") == 0)
					break;
				if (CreateGrpFromFile1(fileName, G) == false)
				{
					system("pause");
					break;
				}
				if (TopologicalSorts(G, topoList) == false)
					cout << "��ͼ����������" << endl;
				else
				{
					cout << "��ͼ��������Ϊ��";
					for (int i = 1; i <= G.VerNum; i++)
						cout << G.VerList[topoList[i]].data << " ";
					cout << endl;
				}
			}
			break;
		}
		}
		system("cls");
	}
}