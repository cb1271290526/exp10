#include "Graph.h"

bool visited[MAX] = { 0 };
int conVerID[MAX] = { 0 };  //代表结点所属的连通分支
EdgeType edges[MAX * MAX];
EdgeType treeEdges[MAX];
bool edgeused[MAX * MAX];  //标记边是否被使用过
int path[MAX];
int dist[MAX];
int Dist[MAX][MAX];
int Path[MAX][MAX];
int main(void)
{
	int choice;
	Graph G;
	char fileName[20];  //文件名

	while (true)
	{
		cout << "0.退出" << endl;
		cout << "1.打印出图（网）的两种遍历序" << endl;
		cout << "2.求给定图中的边（或弧）的数目" << endl;
		cout << "3.V0出发深度优先遍历图G，构造出生成树或生成森林" << endl;
		cout << "4.V0出发广度优先遍历图G，构造出生成树或生成森林" << endl;
		cout << "5.实现Prim算法" << endl;
		cout << "6.实现Kruskal算法" << endl;
		cout << "7.实现Dijkstra算法" << endl;
		cout << "8.实现Floyd算法" << endl;
		cout << "9.求解图G的拓扑序列" << endl;
		cout << "10.求解AOE网的关键路径" << endl;
		cout << "请输入选项：";
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
				cout << "请输入文件名（#退出）：";
				cin >> fileName;
				if (strcmp(fileName, "#") == 0)
					break;
				if (CreateGrpFromFile1(fileName, G) == false)
				{
					system("pause");
					break;
				}
				cout << "深度优先遍历" << endl;
				universal_DFS(G);
				cout << endl;
				cout << "广度优先遍历" << endl;
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
				cout << "请输入文件名（#退出）：";
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
				cout << "改图的边（弧）数：" << Arcnum << endl;
				DestroyGraph(G);
			}
			break;
		}
		case 3:
		{
			while (true)
			{
				int v0;
				cout << "请输入文件名（#退出）：";
				cin >> fileName;
				if (strcmp(fileName, "#") == 0)
					break;
				if (CreateGrpFromFile1(fileName, G) == false)
				{
					system("pause");
					break;
				}
				cout << "请输入起点v0"<<"(1~"<<G.VerNum<<")：";
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
				cout << "请输入文件名（#退出）：";
				cin >> fileName;
				if (strcmp(fileName, "#") == 0)
					break;
				if (CreateGrpFromFile1(fileName, G) == false)
				{
					system("pause");
					break;
				}
				cout << "请输入起点v0" << "(1~" << G.VerNum << ")：";
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
				cout << "请输入文件名（#退出）：";
				cin >> fileName;
				if (strcmp(fileName, "#") == 0)
					break;
				if (CreateGrpFromFile1(fileName, G) == false)
				{
					system("pause");
					break;
				}
				cout << "请输入起点v0" << "(1~" << G.VerNum << ")：";
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
				cout << "请输入文件名（#退出）：";
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
				cout << "请输入文件名（#退出）：";
				cin >> fileName;
				if (strcmp(fileName, "#") == 0)
					break;
				if (CreateGrpFromFile1(fileName, G) == false)
				{
					system("pause");
					break;
				}
				cout << "请输入起点：";
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
				cout << "请输入文件名（#退出）：";
				cin >> fileName;
				if (strcmp(fileName, "#") == 0)
					break;
				if (CreateGrpFromFile1(fileName, G) == false)
				{
					system("pause");
					break;
				}
				cout << "请输入起点：";
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
				cout << "请输入文件名（#退出）：";
				cin >> fileName;
				if (strcmp(fileName, "#") == 0)
					break;
				if (CreateGrpFromFile1(fileName, G) == false)
				{
					system("pause");
					break;
				}
				if (TopologicalSorts(G, topoList) == false)
					cout << "该图无拓扑序列" << endl;
				else
				{
					cout << "该图拓扑序列为：";
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