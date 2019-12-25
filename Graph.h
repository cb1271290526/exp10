#pragma once
#include "creategraph.h"
#include <queue>
#include <stack>

typedef struct
{
	int vBegin = 0;
	int vEnd = 0;
	eInfoType eWeight = INF;
}EdgeType;  //�����������

extern bool visited[];
extern int conVerID[];  //������ͨ�����������
extern int path[MAX];
extern int dist[MAX];
extern int Dist[MAX][MAX];
extern int Path[MAX][MAX];
//��ӡͼ�ı�
void print_edge(Graph& G)
{
	EdgeNode* p;
	int i;
	cout << "����" << "\t" << "�ڽӵ�" << "\t";
	if (G.gKind == GraphKind::DN || G.gKind == GraphKind::UDN)
		cout << "Ȩֵ" << "\t";
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

//��ӡ����ɭ�ֱ߹�ϵ
void print_forest_edge(Graph& G, int v0)
{
	int i;
	EdgeNode* p;
	int count = 0;
	cout << "����" << "\t" << "�ڽӵ�" << "\t";
	if (G.gKind == GraphKind::DN || G.gKind == GraphKind::UDN)
		cout << "Ȩֵ" << "\t";
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

/*���ֱ�����ʼ---------------------------------------*/
//�ҵ�v�ĵ�һ����
int find_firstAdj(Graph& G, int v)
{
	int w = 0;
	if (G.VerList[v].firstEdge != NULL)
		w = G.VerList[v].firstEdge->adjVer;
	return w;
}

//�ҵ�v��w�ĺ�һ����
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

//������ȱ���
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

//һ��������ȱ���
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

//������ȱ���
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

//һ�������ȱ���
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
/*���ֱ�������---------------------------------------*/


/*�����ͼ�еıߣ��򻡣�����Ŀ��ʼ-------------------*/
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
			cout << "��ͼ������ͼ" << endl;
		else
			cout << "��ͼ��������" << endl;
		Arcnum = Arcnum / 2;
	}
	else
	{
		if (G.gKind == GraphKind::DG)
			cout << "��ͼ������ͼ" << endl;
		else
			cout << "��ͼ��������" << endl;
	}
	return Arcnum;
}

/*�����ͼ�еıߣ��򻡣�����Ŀ����-------------------*/


/*V0��������ͼG�������������������ɭ�ֿ�ʼ--*/
//ĳһ����㱻��һ��㵱���ӽ�㣬��ԭ��ͨ��֧���Ը�Ϊ�µĸ����
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

//�������������
void DFS_Generate_tree(Graph& G, int v, int tag)  //tag��ͨ��֧���ԣ���Ϊ�����������
{
	int w;
	EdgeNode* p = NULL;
	EdgeNode* q = NULL;
	conVerID[v] = tag;
	w = find_firstAdj(G, v);  //�ҵ�v�ĵ�һ����
	while (w != 0)
	{
		if (visited[w] == false && conVerID[w] != conVerID[v])  //wû�б����ʹ�
		{
			visited[w] = true;
			if (conVerID[w] == 0)  //w����ĳһ��ͨ��֧�ĸ����
			{
				DFS_Generate_tree(G, w, tag);
			}
			else
			{
				spread(G, v, w, conVerID[w]);
			}
			w = find_nextAdj(G, v, w);
		}
		else  //ɾ����
		{
			p = G.VerList[v].firstEdge;
			if (p->adjVer == w)  //�ѱ����ʱ߽����firstEdge
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

//�����������ɭ��
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

//�������������
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
			if (visited[w] == false && conVerID[w] != conVerID[v])  //wû�б����ʹ�
			{
				visited[w] = true;
				if (conVerID[w] == 0)  //w����ĳһ��ͨ��֧�ĸ����
				{
					Q.push(w);
				}
				else    //w��ĳһ��ͨ��֧�ĸ����
				{
					spread(G, v, w, conVerID[w]);
				}
				w = find_nextAdj(G, v, w);
			}
			else  //ɾ����
			{
				p = G.VerList[v].firstEdge;
				if (p != NULL)
				{
					if (p->adjVer == w)  //�ѱ����ʱ߽����firstEdge
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

//�����������ɭ��
void BFS_generate_forest(Graph& G, int v0)  //tag��ͨ��֧���ԣ���Ϊ�����������
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

/*V0��������ͼG�������������������ɭ�ֽ���--*/


/*ʵ��Prim�㷨��ʼ-------------------------------*/
//�ж����㣨vBegin,vEnd�䣩�Ƿ��бߣ�������������Ȩֵ��������Ȩֵ����INF
bool HasEdge(Graph& G, int vBegin, int vEnd, eInfoType& eWeight)
{
	EdgeNode* p;
	bool f = false;  //�Ƿ��бߵı�־
	eWeight = INF;  //Ȩֵ��ʼ��Ϊ�����
	p = G.VerList[vBegin].firstEdge;  //ȡ��eBegin�ı�����ͷָ��
	while (p != NULL)
	{
		if (p->adjVer == vEnd)
		{  //�б߷���true��Ȩֵ
			f = true;
			eWeight = p->eInfo;
			break;
		}
		p = p->next;
	}
	return f;
}

//��ʼ��������TE[]
void initial_TE(Graph& G, EdgeNode TE[], int vID)  //vIDΪprim�㷨��ʼ����
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

//�ӱ߼���ȡ��С�ĺ�ѡ��
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

//���º�ѡ�߼���
void updateTE(Graph& G, EdgeNode TE[], int vID)
{
	//������ѡ������vID���㣬���º�ѡ�߼���
	int i;
	eInfoType eWeight;
	for (i = 1; i <= G.VerNum; i++)
	{
		if (visited[i] == false)
		{
			if (HasEdge(G, vID, i, eWeight) == true && eWeight < TE[i].eInfo)
			{
				//���vID��δѡ����i�Ƿ��бߣ������vID��i��Ȩֵ�Ƿ��С����С����£�vID��i��Ȩֵ
				TE[i].adjVer = vID;
				TE[i].eInfo = eWeight;
			}
		}
	}
}

//��ӡ��С������
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

//Prim�㷨
void Prim(Graph& G, int vID)
{
	EdgeNode TE[MAX];  //�߼�
	//TE[i].adjVerΪѡ���ߵ����
	int i;
	int curID;  //��ǰѡ�񶥵���
	for (i = 1; i <= G.VerNum; i++)
		visited[i] = false;
	initial_TE(G, TE, vID);
	visited[vID] = true;
	for (i = 1; i <= G.VerNum; i++)
	{
		//��TE��ѡ��Ȩֵ��С�ĺ�ѡ�ߣ����ر��յ�˵Ķ����ŵ�curID
		curID = GetMinEdge(G, TE);
		visited[curID] = true;  //���curID�ѱ�ѡ
		updateTE(G, TE, curID);  //���º�ѡ�߼���
	}
	cout << "����" << "\t" << "�ڽӵ�" << "\t" << "Ȩֵ" << endl;
	print_Min_Tree(G, TE, vID);
}

/*ʵ��Prim�㷨����-------------------------------*/


/*ʵ��Kruskal�㷨��ʼ----------------------------*/

extern EdgeType edges[MAX * MAX];  //ͼ��ȫ���߼��ϼ���Ϣ
extern EdgeType treeEdges[MAX];  //��С��������ȫ���߼���Ϣ
extern bool edgeused[MAX * MAX];  //��Ǳ��Ƿ�ʹ�ù�

//�߼��ϳ�ʼ��
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

//��ȡͼ�ı�
void GetEdges(Graph& G)
{
	//edges[]�±����ߵ��յ㣬edges[i].adjVer��������
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

//��ȡ��С��
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

//Kruskal�㷨
void Kruskal(Graph& G, EdgeType edges[], EdgeType treeEdges[], bool edgeused[])
{
	EdgeType minEdge;  //������С��
	int i, j;
	int k = 0;
	int conID;  //�ߵ��յ����ͨ�������
	int n;  //������С����edges[]���±�
	initial_edges(G);
	GetEdges(G);  //��ȡͼ�ı�ȫ����Ϣ
	int M;  //�������бߵ�ѭ��
	if (G.gKind == GraphKind::UDG || G.gKind == GraphKind::UDN)
		M = G.ArcNum * 2;  //����ͼ�����ı���ѭ����ʵ�ʱ���2��
	else
		M = G.ArcNum;
	for (i = 1; i <= M; i++)
		edgeused[i] = false;  //������б߶�����
	for (i = 1; i <= G.VerNum; i++)
		conVerID[i] = i;  //��ͨ�������==������
	for (i = 1; i < G.VerNum; i++)
	{
		minEdge = GetMinEdge(G, n);
		while (conVerID[minEdge.vBegin] == conVerID[minEdge.vEnd])
		{
			//����γɻ�·
			edgeused[n] = true;  //��Ǹñ߲�����
			minEdge = GetMinEdge(G, n);  //������ȡ��С��
		}
		//�����γɻ�·�򽫸���С�߼�����С������
		treeEdges[i] = minEdge;  //����С�߼�����С������
		conID = conVerID[minEdge.vEnd];  //��ȡ��С���յ����ͨ�������
		for (j = 1; j <= G.VerNum; j++)
		{
			if (conVerID[j] == conID)
				conVerID[j] = conVerID[minEdge.vBegin];
		}
		edgeused[n] = true;
	}
	cout << "����" << "\t" << "�ڽӵ�" << "\t" << "Ȩֵ" << endl;
	for (i = 1; i < G.VerNum; i++)
	{
		cout << treeEdges[i].vBegin << "\t" << treeEdges[i].vEnd << "\t" << treeEdges[i].eWeight << endl;
	}
}

/*ʵ��Kruskal�㷨����----------------------------*/


/*ʵ��Dijkstra�㷨��ʼ---------------------------*/
void Dijkstra(Graph& G, int vID)
{
	int solved[MAX];
	int i, j, v;
	eInfoType minDist;  //������̾���
	EdgeNode* p;  //ָ�������Ľ��
	//��ʼ������⼯��S����������dist[]��·������path[]
	for (i = 1; i <= G.VerNum; i++)
	{
		solved[i] = 0;  //���ж����δ����
		dist[i] = INF;  //���ж����ʼ��������Ϊ�����
		path[i] = -1;  //���ж���ǰ������Ϊ-1������ǰ��
	}
	//������vID
	solved[vID] = 1;  //���vID�Ѵ���
	dist[vID] = 0;
	path[vID] = -1;
	//���ڽӱ��ʼ��dist[]��path[]
	p = G.VerList[vID].firstEdge;
	while (p != NULL)
	{
		v = p->adjVer;  //ȡ�ö���vID���ڽӶ�����
		dist[v] = p->eInfo;
		path[v] = vID;
		p = p->next;
	}
	//�����ҳ�����n-1�������������⼯��S��
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
		//�ѽⶥ�㼯��s��δ�ⶥ�㼯��v-sû�����ڵĶ��㣬�㷨�˳�
		if (minDist == INF)
			return;
		//�������ѡ��Ķ������
		cout << "ѡ�񶥵㣺" << G.VerList[v].data << "--���룺" << minDist << endl;
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

//Dijkstra�㷨���
void Print_Dijkstra(Graph& G, int vID)
{
	int sPath[MAX];  //����vID��Ŀ�궥��i�����·������
	int vPre;  //ǰ�������
	int top = -1;  //�������·���ϵĶ���������Կ���������·��
	int i, j;
	for (i = 1; i <= G.VerNum; i++)
	{
		if (i == vID)
			continue;
		cout << G.VerList[vID].data << "-->" << G.VerList[i].data;
		if (dist[i] == INF)
			cout << "�޿ɴ�·��" << endl;
		else
		{
			cout << "��̾��룺" << dist[i] << endl;
			cout << "          ·����";
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

/*ʵ��Dijkstra�㷨����---------------------------*/


/*ʵ��Floyd�㷨��ʼ------------------------------*/
//���������Ȩֵ������ͼ���ڽӾ���
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

//Floyd�㷨
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
					//������̾���
					Dist[i][j] = Dist[i][m] + Dist[m][j];
					Path[i][j] = Path[m][j];
				}
			}
		}
	}
}

//Floyd�㷨���
void print_Floyd(Graph& G)
{
	int sPath[MAX];  //����vID��Ŀ�궥��i�����·������
	int vPre;  //ǰ�������
	int top = -1;  //�������·���ϵĶ���������Կ���������·��
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
				cout << "�޿ɴ�·��" << endl;
			else
			{
				cout << "��̾��룺" << Dist[i][j] << endl;
				cout << "          ·����";
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

/*ʵ��Floyd�㷨��ʼ------------------------------*/


/*���ͼG���������п�ʼ--------------------------*/
//��ȡ������ԭʼ���
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

/*���ͼG���������п�ʼ--------------------------*/


/*���AOE���Ĺؼ�·����ʼ------------------------*/
//���㶥���¼����緢��ʱ��
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
			inds[p->adjVer]--;  //�ȼ�1
			if (inds[p->adjVer] == 0)  //��Ϊ0����ջ
				S.push(p->adjVer);
			p = p->next;
		}
	}
	if (vCount == G.VerNum)
		return true;
	else
		return false;
}

//��ȡ������ԭʼ����
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

//���㶥���¼�������ʱ��
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
			outds[p->adjVer]--;  //�ȼ�1
			if (outds[p->adjVer] == 0)  //��Ϊ0����ջ
				S.push(p->adjVer);
			p = p->next;
		}
	}
	if (vCount == G.VerNum)
		return true;
	else
		return false;
}

/*���AOE���Ĺؼ�·������------------------------*/