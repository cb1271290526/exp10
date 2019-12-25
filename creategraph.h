#ifndef _CREATEGRAPH_H_
#define _CREATEGRAPH_H_

#include <iostream>
#include <iomanip>
#include <string.h>

using namespace std;
constexpr auto MAX = 101;
constexpr auto INF = 65535;
typedef char elementType;  //顶点数据类型
typedef int eInfoType;  //权值数据类型
enum class GraphKind { UDG, UDN, DG, DN };  //图类型；无向图，无向网，有向图，有向网

typedef struct eNode
{
	int adjVer;  //邻接顶点信息，从1开始
	eInfoType eInfo;  //边链表中边的信息
	struct eNode* next;  //表示下一条边
}EdgeNode;  //边类型

typedef struct vNode
{
	elementType data = 0;  //顶点数据
	EdgeNode* firstEdge = NULL;  //顶点关联的第一条边
}VerNode;  //顶点类型

typedef struct GraphAdjLinkList
{
	VerNode VerList[MAX + 1];  //顶点表
	int VerNum = 0;  //顶点数
	int ArcNum = 0;  //弧（边）数
	GraphKind gKind = GraphKind::DG;  //图类型；0-无向图，1-无向网，3-有向图，4-有向网
}Graph;  //图类型结构

void strLTrim(char* str);  //删除字符串左边空格

//从文本文件创建邻接表表示的图  
bool CreateGrpFromFile1(char fileName[], Graph& G)
{
	FILE* pFile;     //定义顺序表的文件指针
	char str[1000];  //存放读出一行文本的字符串
	char strTemp[10]; //判断是否注释行
	int i = 0, j = 0;
	int edgeNum = 0;  //边的数量
	GraphKind graphType;  //图类型枚举变量
	eInfoType eWeight;  //边的信息，常为权值
	char filepath[100] = "D:\\VS\\exp10\\grpData\\";
	strcat_s(filepath, sizeof(filepath), fileName);
	strcat_s(filepath, sizeof(filepath), ".grp");
	
	fopen_s(&pFile, filepath, "r");
	if (!pFile)
	{
		cout << "错误：文件" << filepath << "打开失败。\n";
		return false;
	}
	while (fgets(str, 1000, pFile) != NULL)  //跳过空行和注释
	{
		//删除左边空格
		strLTrim(str);
		if (str[0] == '\n')  //空行跳过
			continue;

		strncpy_s(strTemp, str, 2);
		strTemp[2] = '\0';
		if (strstr(strTemp, "//") != NULL)  //注释行跳过
			continue;
		else  //非注释，非空跳出
			break;
	}

	//判断文件标识
	if (strstr(str, "Graph") == NULL)
	{
		cout << "错误：打开的文件格式错误\n";
		fclose(pFile); //关闭文件
		return false;
	}

	//读取图的类型，跳过注释行和空行
	while (fgets(str, 1000, pFile) != NULL)
	{
		//删除左边空格
		strLTrim(str);
		if (str[0] == '\n')  //空行跳过
			continue;

		strncpy_s(strTemp, str, 2);
		strTemp[2] = '\0';
		if (strstr(strTemp, "//") != NULL)  //注释行跳过
			continue;
		else  //非杂行
			break;
	}

	//设置图的类型
	if (strstr(str, "UDG"))
		graphType = GraphKind::UDG;  //无向图
	else if (strstr(str, "UDN"))
		graphType = GraphKind::UDN;  //无向网
	else if (strstr(str, "DG"))
		graphType = GraphKind::DG;   //有向图
	else if (strstr(str, "DN"))
		graphType = GraphKind::DN;   //有向网
	else
	{
		cout << "错误：读取图的类型标记失败\n";
		fclose(pFile); //关闭文件
		return false;
	}


	//读取顶点元素，跳过杂行
	while (fgets(str, 1000, pFile) != NULL)
	{
		strLTrim(str);
		if (str[0] == '\n')
			continue;

		strncpy_s(strTemp, str, 2);
		strTemp[2] = '\0';
		if (strstr(strTemp, "//") != NULL)
			continue;
		else
			break;
	}

	//顶点数据放入图的顶点数组
	char* next_token = NULL;
	char* token = strtok_s(str, " ", &next_token);
	int nNum = 0;
	while (token != NULL)
	{
		G.VerList[nNum + 1].data = *token;
		G.VerList[nNum + 1].firstEdge = NULL;
		token = strtok_s(NULL, " ", &next_token);
		nNum++;
	}

	//循环读取边数据
	int nRow = 1;  //矩阵行下标
	int nCol = 1;  //矩阵列下标
	EdgeNode* eR;  //边列表尾指针
	EdgeNode* p;

	elementType Nf, Ns; //边或弧的2个相邻顶点
	while (fgets(str, 1000, pFile) != NULL)
	{
		strLTrim(str);
		if (str[0] == '\n')
			continue;

		strncpy_s(strTemp, str, 2);
		strTemp[2] = '\0';
		if (strstr(strTemp, "//") != NULL)
			continue;

		char* next_token = NULL;
		char* token = strtok_s(str, " ", &next_token);

		if (token == NULL)
		{
			cout << "错误：读取图的边数据错误\n";
			fclose(pFile);
			return false;
		}
		Nf = *token;  //获取边的第一个顶点

		token = strtok_s(NULL, " ", &next_token);  //获取第二个顶点
		if (token == NULL)  //分割失败退出
		{
			cout << "错误：读取图的边数据错误\n";
			fclose(pFile);
			return false;
		}

		Ns = *token;  //获取第二个顶点
			//从第一个顶点获取行号	
		for (nRow = 1; nRow <= nNum; nRow++)
		{
			if (G.VerList[nRow].data == Nf)  //从顶点列表找到第一个顶点的编号
				break;
		}
		//从第二个顶点获取列号
		for (nCol = 1; nCol <= nNum; nCol++)
		{
			if (G.VerList[nCol].data == Ns)  //从顶点列表找到第二个顶点的编号
				break;
		}

		//如果为网，读取权值
		if (graphType == GraphKind::UDN || graphType == GraphKind::DN)
		{
			token = strtok_s(NULL, " ", &next_token);  //读取边的信息
			if (token == NULL)  //分割为空串
			{
				cout << "错误：读取图的边数据错误\n";
				fclose(pFile);
				return false;
			}
			eWeight = atoi(token);  //边获取边的信息
		}


		eR = G.VerList[nRow].firstEdge;
		while (eR != NULL && eR->next != NULL)
		{
			eR = eR->next;  //后移边链表指针，直至尾结点
		}

		p = new EdgeNode;  //申请边链表结点
		p->adjVer = nCol;   //顶点的编号，从1开始
		if (graphType == GraphKind::UDN || graphType == GraphKind::DN) //边的附加信息，对有权图保存权值，无权图保存1
			p->eInfo = eWeight;
		else
			p->eInfo = 1;
		p->next = NULL;

		if (G.VerList[nRow].firstEdge == NULL)
		{
			G.VerList[nRow].firstEdge = p;
			eR = p;
		}
		else
		{
			eR->next = p;
			eR = p;  //新的尾指针
		}
		edgeNum++;   //边数加1
	}

	G.VerNum = nNum;  //图的顶点数
	if (graphType == GraphKind::UDG || graphType == GraphKind::UDN)
		G.ArcNum = edgeNum / 2;  //无向图过网的边数等于统计数字除2
	else
		G.ArcNum = edgeNum;

	G.gKind = graphType;  //图的类型

	fclose(pFile);
	return true;
}

//删除字符串、字符数组左边空格
void strLTrim(char* str)
{
	int i, j;
	size_t n = 0;
	n = strlen(str) + 1;
	for (i = 0; i < n; i++)
	{
		if (str[i] != ' ')  //找到左起第一个非空格位置
			break;
	}
	//以第一个非空格字符为手字符移动字符串
	for (j = 0; j < n; j++)
	{
		str[j] = str[i];
		i++;
	}
}

//销毁图
void DestroyGraph(Graph& G)
{
	EdgeNode* p, * u;
	int vID;
	for (vID = 1; vID <= G.VerNum; vID++)  //循环删除每个顶点的边链表
	{
		p = G.VerList[vID].firstEdge;
		G.VerList[vID].firstEdge = NULL;
		while (p)  //循环删除当前顶点所有的关联边 
		{
			u = p->next;  //u指向下一个边结点
			delete(p);  //删除当前边结点
			p = u;
		}
	}
	p = NULL;
	u = NULL;
	G.VerNum = 0;  //编辑图已经销毁
}
#endif
