#pragma once
#include "creategraph.h"
#include <queue>
#include <stack>

typedef struct
{
	int vBegin = 0;
	int vEnd = 0;
	eInfoType eWeight = INF;
}EdgeType;  //边数组的类型

extern bool visited[];
extern int conVerID[];  //顶点连通分量编号数组
extern int path[MAX];
extern int dist[MAX];
extern int Dist[MAX][MAX];
extern int Path[MAX][MAX];
//打印图的边
void print_edge(Graph& G)
{
	EdgeNode* p;
	int i;
	cout << "顶点" << "\t" << "邻接点" << "\t";
	if (G.gKind == GraphKind::DN || G.gKind == GraphKind::UDN)
		cout << "权值" << "\t";
	cout << endl;
	for (i = 1; i <= G.VerNum; i++)
	{
		p = G.VerList[i].firstEdge;
		do
		{
			cout << G.VerList[i].data << "\t";
			if (p != NULL)
			{
				cout << G.VerList[p->adjVer].data << "\t";
				if (G.gKind == GraphKind::DN || G.gKind == GraphKind::UDN)
					cout << p->eInfo << "\t";
				cout << endl;
			}
			else
			{
				cout << endl;
				break;
			}
			p = p->next;
		} while (p != NULL);
	}
}

//打印生成森林边关系
void print_forest_edge(Graph& G, int v0)
{
	int i;
	EdgeNode* p;
	int count = 0;
	cout << "顶点" << "\t" << "邻接点" << "\t";
	if (G.gKind == GraphKind::DN || G.gKind == GraphKind::UDN)
		cout << "权值" << "\t";
	cout << endl;
	for (i = 1; i <= G.VerNum; i++)
		visited[i] = false;
	i = v0;
	do
	{
		p = G.VerList[i].firstEdge;
		do
		{
			cout << G.VerList[i].data << "\t";
			if (p != NULL)
			{
				cout << G.VerList[p->adjVer].data << "\t";
				if (G.gKind == GraphKind::DN || G.gKind == GraphKind::UDN)
					cout << p->eInfo << "\t";
				cout << endl;
			}
			else
			{
				cout << endl;
				break;
			}
			p = p->next;
		} while (p != NULL);
		visited[i] = true;
		i = i % G.VerNum + 1;
	} while (i != v0);
}

/*两种遍历开始---------------------------------------*/
//找到v的第一条边
int find_firstAdj(Graph& G, int v)
{
	int w = 0;
	if (G.VerList[v].firstEdge != NULL)
		w = G.VerList[v].firstEdge->adjVer;
	return w;
}

//找到v在w的后一条边
int find_nextAdj(Graph& G, int v, int w)
{
	EdgeNode* r = G.VerList[v].firstEdge;
	while (r->adjVer != w)
		r = r->next;
	r = r->next;
	if (r != NULL)
		return r->adjVer;
	return 0;
}

//深度优先遍历
void DFS_Travel(Graph& G, int v)
{
	int w;
	cout << G.VerList[v].data << " ";
	visited[v] = true;
	w = find_firstAdj(G, v);
	while (w != 0)
	{
		if (visited[w] == false)
		{
			DFS_Travel(G, w);
		}
		w = find_nextAdj(G, v, w);
	}
}

//一般深度优先遍历
void universal_DFS(Graph& G)
{
	int i;
	for (i = 1; i <= G.VerNum; i++)
		visited[i] = false;
	for (i = 1; i <= G.VerNum; i++)
	{
		if (visited[i] == false)
			DFS_Travel(G, i);
	}
}

//广度优先遍历
void BFS_Travel(Graph& G, int v0)
{
	int v = v0;
	int w;
	queue<int>Q;
	cout << G.VerList[v].data << " ";
	visited[v] = true;
	Q.push(v);
	while (true)
	{
		if (!Q.empty())
		{
			v = Q.front();
			Q.pop();
		}
		else
			return;
		w = find_firstAdj(G, v);
		while (w != 0)
		{
			if (visited[w] == false)
			{
				cout << G.VerList[v].data << " ";
				visited[w] = true;
				Q.push(w);
			}
			w = find_nextAdj(G, v, w);
		}
	}
}

//一般广度优先遍历
void universal_BFS(Graph& G)
{
	int i;
	for (i = 1; i <= G.VerNum; i++)
		visited[i] = false;
	for (i = 1; i <= G.VerNum; i++)
	{
		if (visited[i] == false)
			BFS_Travel(G, i);
	}
}
/*两种遍历结束---------------------------------------*/


/*求给定图中的边（或弧）的数目开始-------------------*/
int count_edge(Graph& G)
{
	EdgeNode* p;
	int i;
	int Arcnum = 0;
	for (i = 1; i <= G.VerNum; i++)
	{
		p = G.VerList[i].firstEdge;
		while (p != NULL)
		{
			Arcnum++;
			p = p->next;
		}
	}
	if (G.gKind == GraphKind::UDG || G.gKind == GraphKind::UDN)
	{
		if (G.gKind == GraphKind::UDG)
			cout << "该图是无向图" << endl;
		else
			cout << "该图是无向网" << endl;
		Arcnum = Arcnum / 2;
	}
	else
	{
		if (G.gKind == GraphKind::DG)
			cout << "该图是有向图" << endl;
		else
			cout << "该图是有向网" << endl;
	}
	return Arcnum;
}

/*求给定图中的边（或弧）的数目结束-------------------*/


/*V0出发遍历图G，构造出生成树或生成森林开始--*/
//某一根结点被另一结点当作子结点，则将原连通分支属性改为新的根结点
void spread(Graph& G, int v0, int w0, int bk)  
{
	int v = v0;
	int w = w0;
	if (visited[w] == true)
	{
		conVerID[w] = conVerID[v];
		v = w;
		w = find_firstAdj(G, w);
		while (w != 0)
		{
			if (conVerID[w] == bk)
			{
				spread(G, v, w, bk);
			}
			w = find_nextAdj(G, v, w);
		}
	}
}

//深度优先生成树
void DFS_Generate_tree(Graph& G, int v, int tag)  //tag连通分支属性，常为生成树根结点
{
	int w;
	EdgeNode* p = NULL;
	EdgeNode* q = NULL;
	conVerID[v] = tag;
	w = find_firstAdj(G, v);  //找到v的第一条边
	while (w != 0)
	{
		if (visited[w] == false && conVerID[w] != conVerID[v])  //w没有被访问过
		{
			visited[w] = true;
			if (conVerID[w] == 0)  //w不是某一连通分支的根结点
			{
				DFS_Generate_tree(G, w, tag);
			}
			else
			{
				spread(G, v, w, conVerID[w]);
			}
			w = find_nextAdj(G, v, w);
		}
		else  //删除边
		{
			p = G.VerList[v].firstEdge;
			if (p->adjVer == w)  //已被访问边结点是firstEdge
			{
				G.VerList[v].firstEdge = p->next;
				delete p;
				p = G.VerList[v].firstEdge;
			}
			else
			{
				while (p->next->adjVer != w)
					p = p->next;
				q = p->next;
				p->next = q->next;
				delete q;
				p = p->next;
			}
			if (p != NULL)
				w = p->adjVer;
			else
				w = 0;
		}
	}
}

//深度优先生成森林
void DFS_generate_forest(Graph& G, int v0)
{
	int i;
	
	for (i = 1; i <= G.VerNum; i++)
	{
		visited[i] = false;
		conVerID[i] = 0;
	}
	i = v0;
	do
	{
		if (visited[i] == false)
		{
			DFS_Generate_tree(G, i, i);
		}
		i = i % G.VerNum + 1;
	} while (v0 != i);
}

//广度优先生成树
void BFS_Generate_tree(Graph& G, int v0, int tag)
{
	int v = v0;
	int w;
	EdgeNode* p = NULL;
	EdgeNode* q = NULL;
	queue<int>Q;
	Q.push(v);
	while (true)
	{
		if (!Q.empty())
		{
			v = Q.front();
			conVerID[v] = tag;
			Q.pop();
		}
		else
			return;
		w = find_firstAdj(G, v);
		while (w != 0)
		{
			if (visited[w] == false && conVerID[w] != conVerID[v])  //w没有被访问过
			{
				visited[w] = true;
				if (conVerID[w] == 0)  //w不是某一连通分支的根结点
				{
					Q.push(w);
				}
				else    //w是某一连通分支的根结点
				{
					spread(G, v, w, conVerID[w]);
				}
				w = find_nextAdj(G, v, w);
			}
			else  //删除边
			{
				p = G.VerList[v].firstEdge;
				if (p != NULL)
				{
					if (p->adjVer == w)  //已被访问边结点是firstEdge
					{
						G.VerList[v].firstEdge = p->next;
						delete p;
						p = G.VerList[v].firstEdge;
					}
					else if (p->next != NULL)
					{
						while (p->next->adjVer != w)
							p = p->next;
						q = p->next;
						p->next = q->next;
						delete q;
						p = p->next;
					}
					if (p != NULL)
						w = p->adjVer;
					else
						w = 0;
				}

			}
		}
	}
}

//广度优先生成森林
void BFS_generate_forest(Graph& G, int v0)  //tag连通分支属性，常为生成树根结点
{
	int i;

	for (i = 1; i <= G.VerNum; i++)
	{
		visited[i] = false;
		conVerID[i] = 0;
	}
	i = v0;
	do
	{
		if (visited[i] == false)
		{
			BFS_Generate_tree(G, i, i);
		}
		i = i % G.VerNum + 1;
	} while (v0 != i);
}

/*V0出发遍历图G，构造出生成树或生成森林结束--*/


/*实现Prim算法开始-------------------------------*/
//判断两点（vBegin,vEnd间）是否有边（弧），并返回权值，若无则权值返回INF
bool HasEdge(Graph& G, int vBegin, int vEnd, eInfoType& eWeight)
{
	EdgeNode* p;
	bool f = false;  //是否有边的标志
	eWeight = INF;  //权值初始化为无穷大
	p = G.VerList[vBegin].firstEdge;  //取得eBegin的边链表头指针
	while (p != NULL)
	{
		if (p->adjVer == vEnd)
		{  //有边返回true和权值
			f = true;
			eWeight = p->eInfo;
			break;
		}
		p = p->next;
	}
	return f;
}

//初始化边数组TE[]
void initial_TE(Graph& G, EdgeNode TE[], int vID)  //vID为prim算法起始顶点
{
	int i;
	eInfoType eWeight;
	for (i = 1; i <= G.VerNum; i++)
	{
		if (HasEdge(G, vID, i, eWeight))
		{
			TE[i].adjVer = vID;
			TE[i].eInfo = eWeight;
		}
		else
			TE[i].eInfo = INF;
	}
}

//从边集获取最小的侯选边
int GetMinEdge(Graph& G, EdgeNode TE[])
{
	eInfoType eMin = INF;
	int i, j = 0;
	for (i = 1; i <= G.VerNum; i++)
	{
		if (visited[i] == false && TE[i].eInfo < eMin)
		{
			j = i;
			eMin = TE[i].eInfo;
		}
	}
	return j;
}

//更新侯选边集合
void updateTE(Graph& G, EdgeNode TE[], int vID)
{
	//对于新选出来的vID顶点，更新侯选边集合
	int i;
	eInfoType eWeight;
	for (i = 1; i <= G.VerNum; i++)
	{
		if (visited[i] == false)
		{
			if (HasEdge(G, vID, i, eWeight) == true && eWeight < TE[i].eInfo)
			{
				//检查vID与未选顶点i是否有边，并检查vID与i间权值是否更小，更小则更新（vID，i）权值
				TE[i].adjVer = vID;
				TE[i].eInfo = eWeight;
			}
		}
	}
}

//打印最小生成树
void print_Min_Tree(Graph& G, EdgeNode TE[], int vID)
{
	queue<int>Q;
	int i, v;
	Q.push(vID);
	while (!Q.empty())
	{
		v = Q.front();
		Q.pop();
		for (i = 1; i <= G.VerNum; i++)
		{
			if (TE[i].adjVer == v)
			{
				Q.push(i);
				cout << v << "\t" << i << "\t" << TE[i].eInfo <<endl;
			}
		}
	}
}

//Prim算法
void Prim(Graph& G, int vID)
{
	EdgeNode TE[MAX];  //边集
	//TE[i].adjVer为选定边的起点
	int i;
	int curID;  //当前选择顶点编号
	for (i = 1; i <= G.VerNum; i++)
		visited[i] = false;
	initial_TE(G, TE, vID);
	visited[vID] = true;
	for (i = 1; i <= G.VerNum; i++)
	{
		//从TE中选出权值最小的侯选边，返回边终点端的顶点编号到curID
		curID = GetMinEdge(G, TE);
		visited[curID] = true;  //标记curID已被选
		updateTE(G, TE, curID);  //更新侯选边集合
	}
	cout << "顶点" << "\t" << "邻接点" << "\t" << "权值" << endl;
	print_Min_Tree(G, TE, vID);
}

/*实现Prim算法结束-------------------------------*/


/*实现Kruskal算法开始----------------------------*/

extern EdgeType edges[MAX * MAX];  //图的全部边集合及信息
extern EdgeType treeEdges[MAX];  //最小生成树的全部边及信息
extern bool edgeused[MAX * MAX];  //标记边是否被使用过

//边集合初始化
void initial_edges(Graph& G)
{
	int i;
	int M;
	if (G.gKind == GraphKind::UDG || G.gKind == GraphKind::UDN)
		M = G.ArcNum * 2;
	else
		M = G.ArcNum;
	for (i = 1; i <= M; i++)
	{
		edges[i].eWeight = INF;
	}
}

//获取图的边
void GetEdges(Graph& G)
{
	//edges[]下标代表边的终点，edges[i].adjVer代表边起点
	int i;
	int j = 1;
	EdgeNode* p;
	for (i = 1; i <= G.VerNum; i++)
	{
		p = G.VerList[i].firstEdge;
		while (p != NULL)
		{
			edges[j].vBegin = i;
			edges[j].vEnd = p->adjVer;
			edges[j].eWeight = p->eInfo;
			p = p->next;
			j++;
		}
	}
}

//获取最小边
EdgeType GetMinEdge(Graph& G, int& n)
{
	EdgeType minEdge;
	eInfoType wMin = INF;
	int i;
	int M;
	if (G.gKind == GraphKind::UDG || G.gKind == GraphKind::UDN)
		M = G.ArcNum * 2;
	else
		M = G.ArcNum;
	for (i = 1; i <= M; i++)
	{
		if (edgeused[i] == false && edges[i].eWeight < wMin)
		{
			wMin = edges[i].eWeight;
			minEdge.eWeight = edges[i].eWeight;
			minEdge.vBegin = edges[i].vBegin;
			minEdge.vEnd = edges[i].vEnd;
			n = i;
		}
	}
	return minEdge;
}

//Kruskal算法
void Kruskal(Graph& G, EdgeType edges[], EdgeType treeEdges[], bool edgeused[])
{
	EdgeType minEdge;  //保存最小边
	int i, j;
	int k = 0;
	int conID;  //边的终点的连通分量编号
	int n;  //返回最小边在edges[]的下标
	initial_edges(G);
	GetEdges(G);  //获取图的边全部信息
	int M;  //关于所有边的循环
	if (G.gKind == GraphKind::UDG || G.gKind == GraphKind::UDN)
		M = G.ArcNum * 2;  //无向图、网的边数循环是实际边数2倍
	else
		M = G.ArcNum;
	for (i = 1; i <= M; i++)
		edgeused[i] = false;  //标记所有边都可用
	for (i = 1; i <= G.VerNum; i++)
		conVerID[i] = i;  //连通分量编号==顶点编号
	for (i = 1; i < G.VerNum; i++)
	{
		minEdge = GetMinEdge(G, n);
		while (conVerID[minEdge.vBegin] == conVerID[minEdge.vEnd])
		{
			//如果形成回路
			edgeused[n] = true;  //标记该边不可用
			minEdge = GetMinEdge(G, n);  //继续获取最小边
		}
		//当不形成回路则将该最小边加入最小生成树
		treeEdges[i] = minEdge;  //将最小边加入最小生成树
		conID = conVerID[minEdge.vEnd];  //获取最小边终点的连通分量编号
		for (j = 1; j <= G.VerNum; j++)
		{
			if (conVerID[j] == conID)
				conVerID[j] = conVerID[minEdge.vBegin];
		}
		edgeused[n] = true;
	}
	cout << "顶点" << "\t" << "邻接点" << "\t" << "权值" << endl;
	for (i = 1; i < G.VerNum; i++)
	{
		cout << treeEdges[i].vBegin << "\t" << treeEdges[i].vEnd << "\t" << treeEdges[i].eWeight << endl;
	}
}

/*实现Kruskal算法结束----------------------------*/


/*实现Dijkstra算法开始---------------------------*/
void Dijkstra(Graph& G, int vID)
{
	int solved[MAX];
	int i, j, v;
	eInfoType minDist;  //保存最短距离
	EdgeNode* p;  //指向边链表的结点
	//初始化以求解集合S，距离数组dist[]，路径数组path[]
	for (i = 1; i <= G.VerNum; i++)
	{
		solved[i] = 0;  //所有顶点均未处理
		dist[i] = INF;  //所有顶点初始距离设置为无穷大
		path[i] = -1;  //所有顶点前驱设置为-1，即无前驱
	}
	//处理顶点vID
	solved[vID] = 1;  //标记vID已处理
	dist[vID] = 0;
	path[vID] = -1;
	//从邻接表初始化dist[]和path[]
	p = G.VerList[vID].firstEdge;
	while (p != NULL)
	{
		v = p->adjVer;  //取得顶点vID的邻接顶点编号
		dist[v] = p->eInfo;
		path[v] = vID;
		p = p->next;
	}
	//依次找出余下n-1个顶点加入以求解集合S中
	for (i = 1; i < G.VerNum; i++)
	{
		minDist = INF;
		for (j = 1; j <= G.VerNum; j++)
		{
			if (solved[j] == 0 && dist[j] < minDist)
			{
				v = j;
				minDist = dist[j];
			}
		}
		//已解顶点集合s与未解顶点集合v-s没有相邻的顶点，算法退出
		if (minDist == INF)
			return;
		//输出本次选择的顶点距离
		cout << "选择顶点：" << G.VerList[v].data << "--距离：" << minDist << endl;
		solved[v] = 1;
		p = G.VerList[v].firstEdge;
		while (p != NULL)
		{
			j = p->adjVer;
			if (solved[j] == 0 && minDist + p->eInfo < dist[j])
			{
				dist[j] = minDist + p->eInfo;
				path[j] = v;
			}
			p = p->next;
		}
	}
}

//Dijkstra算法输出
void Print_Dijkstra(Graph& G, int vID)
{
	int sPath[MAX];  //保存vID到目标顶点i的最短路径顶点
	int vPre;  //前驱结点编号
	int top = -1;  //保存最短路径上的顶点个数，以控制输出最短路径
	int i, j;
	for (i = 1; i <= G.VerNum; i++)
	{
		if (i == vID)
			continue;
		cout << G.VerList[vID].data << "-->" << G.VerList[i].data;
		if (dist[i] == INF)
			cout << "无可达路径" << endl;
		else
		{
			cout << "最短距离：" << dist[i] << endl;
			cout << "          路径：";
		}
		top++;
		sPath[top] = i;
		vPre = path[i];
		while (vPre != -1)
		{
			top++;
			sPath[top] = vPre;
			vPre = path[vPre];
		}
		if (dist[i] != INF)
		{
			for (j = top; j >= 0; j--)
			{
				cout << G.VerList[sPath[j]].data << " ";
			}
		}
		top = -1;
		cout << endl;
	}
}

/*实现Dijkstra算法结束---------------------------*/


/*实现Floyd算法开始------------------------------*/
//返回两点间权值，代替图的邻接矩阵
eInfoType Graphinfo(Graph& G, int i, int j)
{
	EdgeNode* p;
	if (i == j)
		return 0;
	p = G.VerList[i].firstEdge;
	while (p != NULL)
	{
		if (p->adjVer == j)
			return p->eInfo;
		p = p->next;
	}
	p = G.VerList[j].firstEdge;
	while (p != NULL)
	{
		if (p->adjVer == i)
			return p->eInfo;
		p = p->next;
	}
	return INF;
}

//Floyd算法
void Floyd(Graph& G)
{
	int i, j, m;
	eInfoType x;
	for (i = 1; i <= G.VerNum; i++)
	{
		for (j = 1; j <= G.VerNum; j++)
		{
			x = Graphinfo(G, i, j);
			Dist[i][j] = x;
			if (i != j && x < INF)
				Path[i][j] = i;
			else
				Path[i][j] = -1;
		}
	}

	for (m = 1; m <= G.VerNum; m++)
	{
		for (i = 1; i <= G.VerNum; i++)
		{
			for (j = 1; j <= G.VerNum; j++)
			{
				if (i != j && Dist[i][m] + Dist[m][j] < Dist[i][j])
				{
					//更新最短距离
					Dist[i][j] = Dist[i][m] + Dist[m][j];
					Path[i][j] = Path[m][j];
				}
			}
		}
	}
}

//Floyd算法输出
void print_Floyd(Graph& G)
{
	int sPath[MAX];  //保存vID到目标顶点i的最短路径顶点
	int vPre;  //前驱结点编号
	int top = -1;  //保存最短路径上的顶点个数，以控制输出最短路径
	int i, j, k;
	for (i = 1; i <= G.VerNum; i++)
	{
		if (G.gKind == GraphKind::UDG || G.gKind == GraphKind::UDN)
			j = i + 1;
		else
			j = 1;
		for (j; j <= G.VerNum; j++)
		{
			if (i == j)
				continue;
			cout << G.VerList[i].data << "-->" << G.VerList[j].data;
			if (Dist[i][j] == INF)
				cout << "无可达路径" << endl;
			else
			{
				cout << "最短距离：" << Dist[i][j] << endl;
				cout << "          路径：";
			}
			top++;
			sPath[top] = j;
			vPre = Path[i][j];
			while (vPre != -1)
			{
				top++;
				sPath[top] = vPre;
				vPre = Path[i][vPre];
			}
			if (Dist[i][j] != INF)
			{
				for (k = top; k >= 0; k--)
				{
					cout << G.VerList[sPath[k]].data << " ";
				}
			}
			top = -1;
			cout << endl;
		}
	}

}

/*实现Floyd算法开始------------------------------*/


/*求解图G的拓扑序列开始--------------------------*/
//获取各顶点原始入度
void GetInDegree(Graph& G, int inds[])
{
	int i, j;
	EdgeNode* p;
	for (i = 1; i <= G.VerNum; i++)
	{
		for (j = 1; j <= G.VerNum; j++)
		{
			p = G.VerList[j].firstEdge;
			while (p != NULL)
			{
				if (p->adjVer == i)
				{
					inds[i]++;
					break;
				}
				else
					p = p->next;
			}
		}
	}
}

bool TopologicalSorts(Graph& G, int topoList[])
{
	int inds[MAX];
	stack<int>S;
	int i;
	int v;
	int vCount = 0;
	EdgeNode* p;
	for (i = 1; i <= G.VerNum; i++)
	{
		inds[i] = 0;
		topoList[i] = -1;
	}
	GetInDegree(G, inds);
	for (i = 1; i <= G.VerNum; i++)
	{
		if (inds[i] == 0)
			S.push(i);
	}
	while (!S.empty())
	{
		v = S.top();
		S.pop();
		vCount++;
		topoList[vCount] = v;
		p = G.VerList[v].firstEdge;
		while (p != NULL)
		{
			v = p->adjVer;
			inds[v]--;
			if (inds[v] == 0)
				S.push(v);
			p = p->next;
		}
	}
	if (vCount == G.VerNum)
		return true;
	else
		return false;
}

/*求解图G的拓扑序列开始--------------------------*/


/*求解AOE网的关键路径开始------------------------*/
//计算顶点事件最早发生时间
bool GetVer_EarlistTime(Graph& G, int VerEarlist_time[])
{
	int inds[MAX];
	stack<int>S;
	int i;
	int v;
	int vCount = 0;
	EdgeNode* p;
	for (i = 1; i <= G.VerNum; i++)
	{
		inds[i] = 0;
		VerEarlist_time[i] = 0;
	}
	GetInDegree(G, inds);
	for (i = 1; i <= G.VerNum; i++)
	{
		if (inds[i] == 0)
		{
			S.push(i);
			break;
		}
	}
	while (!S.empty())
	{
		v = S.top();
		S.pop();
		vCount++;
		p = G.VerList[v].firstEdge;
		while (p != NULL)
		{
			if (VerEarlist_time[v] + p->eInfo > VerEarlist_time[p->adjVer])
				VerEarlist_time[p->adjVer] = VerEarlist_time[v] + p->eInfo;
			inds[p->adjVer]--;  //度减1
			if (inds[p->adjVer] == 0)  //度为0，入栈
				S.push(p->adjVer);
			p = p->next;
		}
	}
	if (vCount == G.VerNum)
		return true;
	else
		return false;
}

//获取各顶点原始出度
void GetOutDegree(Graph& G, int outds[])
{
	int i;
	EdgeNode* p;
	for (i = 1; i <= G.VerNum; i++)
	{
		p = G.VerList[i].firstEdge;
		while (p != NULL)
		{
			outds[i]++;
			p = p->next;
		}
	}
}

void GetPreVers(Graph& G, int PreVers[], int vID)
{
	int i, j;
	j = 0;
	EdgeNode* p;
	for (i = 1; i <= G.VerNum; i++)
	{
		p = G.VerList[i].firstEdge;
		while (p != NULL)
		{
			if (p->adjVer == vID)
			{
				j++;
				PreVers[j] = i;
			}
			p = p->next;
		}
	}
	PreVers[j + 1] = INF;
}

//计算顶点事件最晚发生时间
bool GetVer_LatestTime(Graph& G, int VerLatest_time[], int totaltime)
{
	int outds[MAX];
	stack<int>S;
	int i;
	int v;
	int vCount = 0;
	EdgeNode* p;
	for (i = 1; i <= G.VerNum; i++)
	{
		outds[i] = 0;
		VerLatest_time[i] = 0;
	}
	GetOutDegree(G, outds);
	for (i = 1; i <= G.VerNum; i++)
	{
		if (outds[i] == 0)
		{
			S.push(i);
			break;
		}
	}
	VerLatest_time[i] = totaltime;
	while (!S.empty())
	{
		v = S.top();
		S.pop();
		vCount++;
		p = G.VerList[v].firstEdge;
		while (p != NULL)
		{
			if (VerLatest_time[v] + p->eInfo > VerLatest_time[p->adjVer])
				VerLatest_time[p->adjVer] = VerLatest_time[v] + p->eInfo;
			outds[p->adjVer]--;  //度减1
			if (outds[p->adjVer] == 0)  //度为0，入栈
				S.push(p->adjVer);
			p = p->next;
		}
	}
	if (vCount == G.VerNum)
		return true;
	else
		return false;
}

/*求解AOE网的关键路径结束------------------------*/