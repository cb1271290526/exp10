#ifndef _CREATEGRAPH_H_
#define _CREATEGRAPH_H_

#include <iostream>
#include <iomanip>
#include <string.h>

using namespace std;
constexpr auto MAX = 101;
constexpr auto INF = 65535;
typedef char elementType;  //������������
typedef int eInfoType;  //Ȩֵ��������
enum class GraphKind { UDG, UDN, DG, DN };  //ͼ���ͣ�����ͼ��������������ͼ��������

typedef struct eNode
{
	int adjVer;  //�ڽӶ�����Ϣ����1��ʼ
	eInfoType eInfo;  //�������бߵ���Ϣ
	struct eNode* next;  //��ʾ��һ����
}EdgeNode;  //������

typedef struct vNode
{
	elementType data = 0;  //��������
	EdgeNode* firstEdge = NULL;  //��������ĵ�һ����
}VerNode;  //��������

typedef struct GraphAdjLinkList
{
	VerNode VerList[MAX + 1];  //�����
	int VerNum = 0;  //������
	int ArcNum = 0;  //�����ߣ���
	GraphKind gKind = GraphKind::DG;  //ͼ���ͣ�0-����ͼ��1-��������3-����ͼ��4-������
}Graph;  //ͼ���ͽṹ

void strLTrim(char* str);  //ɾ���ַ�����߿ո�

//���ı��ļ������ڽӱ��ʾ��ͼ  
bool CreateGrpFromFile1(char fileName[], Graph& G)
{
	FILE* pFile;     //����˳�����ļ�ָ��
	char str[1000];  //��Ŷ���һ���ı����ַ���
	char strTemp[10]; //�ж��Ƿ�ע����
	int i = 0, j = 0;
	int edgeNum = 0;  //�ߵ�����
	GraphKind graphType;  //ͼ����ö�ٱ���
	eInfoType eWeight;  //�ߵ���Ϣ����ΪȨֵ
	char filepath[100] = "D:\\VS\\exp10\\grpData\\";
	strcat_s(filepath, sizeof(filepath), fileName);
	strcat_s(filepath, sizeof(filepath), ".grp");
	
	fopen_s(&pFile, filepath, "r");
	if (!pFile)
	{
		cout << "�����ļ�" << filepath << "��ʧ�ܡ�\n";
		return false;
	}
	while (fgets(str, 1000, pFile) != NULL)  //�������к�ע��
	{
		//ɾ����߿ո�
		strLTrim(str);
		if (str[0] == '\n')  //��������
			continue;

		strncpy_s(strTemp, str, 2);
		strTemp[2] = '\0';
		if (strstr(strTemp, "//") != NULL)  //ע��������
			continue;
		else  //��ע�ͣ��ǿ�����
			break;
	}

	//�ж��ļ���ʶ
	if (strstr(str, "Graph") == NULL)
	{
		cout << "���󣺴򿪵��ļ���ʽ����\n";
		fclose(pFile); //�ر��ļ�
		return false;
	}

	//��ȡͼ�����ͣ�����ע���кͿ���
	while (fgets(str, 1000, pFile) != NULL)
	{
		//ɾ����߿ո�
		strLTrim(str);
		if (str[0] == '\n')  //��������
			continue;

		strncpy_s(strTemp, str, 2);
		strTemp[2] = '\0';
		if (strstr(strTemp, "//") != NULL)  //ע��������
			continue;
		else  //������
			break;
	}

	//����ͼ������
	if (strstr(str, "UDG"))
		graphType = GraphKind::UDG;  //����ͼ
	else if (strstr(str, "UDN"))
		graphType = GraphKind::UDN;  //������
	else if (strstr(str, "DG"))
		graphType = GraphKind::DG;   //����ͼ
	else if (strstr(str, "DN"))
		graphType = GraphKind::DN;   //������
	else
	{
		cout << "���󣺶�ȡͼ�����ͱ��ʧ��\n";
		fclose(pFile); //�ر��ļ�
		return false;
	}


	//��ȡ����Ԫ�أ���������
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

	//�������ݷ���ͼ�Ķ�������
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

	//ѭ����ȡ������
	int nRow = 1;  //�������±�
	int nCol = 1;  //�������±�
	EdgeNode* eR;  //���б�βָ��
	EdgeNode* p;

	elementType Nf, Ns; //�߻򻡵�2�����ڶ���
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
			cout << "���󣺶�ȡͼ�ı����ݴ���\n";
			fclose(pFile);
			return false;
		}
		Nf = *token;  //��ȡ�ߵĵ�һ������

		token = strtok_s(NULL, " ", &next_token);  //��ȡ�ڶ�������
		if (token == NULL)  //�ָ�ʧ���˳�
		{
			cout << "���󣺶�ȡͼ�ı����ݴ���\n";
			fclose(pFile);
			return false;
		}

		Ns = *token;  //��ȡ�ڶ�������
			//�ӵ�һ�������ȡ�к�	
		for (nRow = 1; nRow <= nNum; nRow++)
		{
			if (G.VerList[nRow].data == Nf)  //�Ӷ����б��ҵ���һ������ı��
				break;
		}
		//�ӵڶ��������ȡ�к�
		for (nCol = 1; nCol <= nNum; nCol++)
		{
			if (G.VerList[nCol].data == Ns)  //�Ӷ����б��ҵ��ڶ�������ı��
				break;
		}

		//���Ϊ������ȡȨֵ
		if (graphType == GraphKind::UDN || graphType == GraphKind::DN)
		{
			token = strtok_s(NULL, " ", &next_token);  //��ȡ�ߵ���Ϣ
			if (token == NULL)  //�ָ�Ϊ�մ�
			{
				cout << "���󣺶�ȡͼ�ı����ݴ���\n";
				fclose(pFile);
				return false;
			}
			eWeight = atoi(token);  //�߻�ȡ�ߵ���Ϣ
		}


		eR = G.VerList[nRow].firstEdge;
		while (eR != NULL && eR->next != NULL)
		{
			eR = eR->next;  //���Ʊ�����ָ�룬ֱ��β���
		}

		p = new EdgeNode;  //�����������
		p->adjVer = nCol;   //����ı�ţ���1��ʼ
		if (graphType == GraphKind::UDN || graphType == GraphKind::DN) //�ߵĸ�����Ϣ������Ȩͼ����Ȩֵ����Ȩͼ����1
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
			eR = p;  //�µ�βָ��
		}
		edgeNum++;   //������1
	}

	G.VerNum = nNum;  //ͼ�Ķ�����
	if (graphType == GraphKind::UDG || graphType == GraphKind::UDN)
		G.ArcNum = edgeNum / 2;  //����ͼ�����ı�������ͳ�����ֳ�2
	else
		G.ArcNum = edgeNum;

	G.gKind = graphType;  //ͼ������

	fclose(pFile);
	return true;
}

//ɾ���ַ������ַ�������߿ո�
void strLTrim(char* str)
{
	int i, j;
	size_t n = 0;
	n = strlen(str) + 1;
	for (i = 0; i < n; i++)
	{
		if (str[i] != ' ')  //�ҵ������һ���ǿո�λ��
			break;
	}
	//�Ե�һ���ǿո��ַ�Ϊ���ַ��ƶ��ַ���
	for (j = 0; j < n; j++)
	{
		str[j] = str[i];
		i++;
	}
}

//����ͼ
void DestroyGraph(Graph& G)
{
	EdgeNode* p, * u;
	int vID;
	for (vID = 1; vID <= G.VerNum; vID++)  //ѭ��ɾ��ÿ������ı�����
	{
		p = G.VerList[vID].firstEdge;
		G.VerList[vID].firstEdge = NULL;
		while (p)  //ѭ��ɾ����ǰ�������еĹ����� 
		{
			u = p->next;  //uָ����һ���߽��
			delete(p);  //ɾ����ǰ�߽��
			p = u;
		}
	}
	p = NULL;
	u = NULL;
	G.VerNum = 0;  //�༭ͼ�Ѿ�����
}
#endif
