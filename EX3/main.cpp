#pragma warning(disable:4996)
#include<stdio.h>
#include<stdlib.h>

const int sourcenum = 3;
const int processnum = 5;

int Available[sourcenum] = { 3,3,2 };
int Max[processnum][sourcenum] = { 7,5,3,3,2,2,9,0,2,2,2,2,4,3,3 };
int Allocation[processnum][sourcenum] = { 0,1,0,2,0,0,3,0,2,2,1,1,0,2,2 };
int Need[processnum][sourcenum] = { 7,4,3,1,2,2,6,0,0,0,1,1,4,3,1 };

int Request[processnum][sourcenum];

int sort[processnum];//存放安全序列
bool Finish[processnum];

void init();//数据初始化
void Bank();//银行家算法
bool Safe();//判断是否处于安全状态
void print();//输出函数

int main()
{
	int inp;
	print();//输出开始状态
	Bank();
	while (true)
	{
		printf("还想继续分配嘛？？继续请输入1，退出输入0\n");
		scanf("%d", &inp);
		switch (inp)
		{
		case 1:
			init();
			Bank();
		case 0:
			exit(0);
		}
	}
	return 0;
}
void init()
{
	int Available[sourcenum] = { 3,3,2 };
	int Max[processnum][sourcenum] = { 7,5,3,3,2,2,9,0,2,2,2,2,4,3,3 };
	int Allocation[processnum][sourcenum] = { 0,1,0,2,0,0,3,0,2,2,1,1,0,2,2 };
	int Need[processnum][sourcenum] = { 7,4,3,1,2,2,6,0,0,0,1,1,4,3,1 };

}
void print()
{
	printf("PROCESS\t\tMAX\t\tALLOCATION\tNEED\n");
	int i, j;
	for (i = 0; i < 5; i++)
	{
		printf("P%d\t\t", i);
		for (j = 0; j < 3; j++)
		{
			printf("%d ", Max[i][j]);
		}
		printf("\t\t");
		for (j = 0; j < 3; j++)
		{
			printf("%d ", Allocation[i][j]);
		}
		printf("\t\t");
		for (j = 0; j < 3; j++)
		{
			printf("%d ", Need[i][j]);
		}
		printf("\n");
	}
}
void Bank()
{
	int pronum;
	int j;
	printf("请输入待申请资源进程的进程号\n");
	scanf("%d", &pronum);
	printf("请输入进程资源需求矩阵\n");
	for (j = 0; j < sourcenum; j++)
	{
		scanf("%d", &Request[pronum][j]);
	}

	for (j = 0; j < sourcenum; j++)
	{
		if (Request[pronum][j] > Need[pronum][j])
		{
			printf("所请求资源数超过宣布最大值，请求失败\n");
			return;
		}
		if (Request[pronum][j] > Available[j])
		{
			printf("所请求资源数超过系统当前资源数，请等待\n");
			return;
		}
	}
	int i;
	for (i = 0; i < sourcenum; i++)//试探分配
	{
		Available[i] -= Request[pronum][i];
		Allocation[pronum][i] += Request[pronum][i];
		Need[pronum][i] -= Request[pronum][i];
	}
	printf("试探分配结果：\n");
	print();
	if (Safe())
	{
		printf("分配后处安全状态，同意分配\n");
	}
	else
	{
		printf("分配后系统不安全，分配失败\n");
		for (i = 0; i < sourcenum; i++)
		{
			Available[i] += Request[pronum][i];
			Allocation[pronum][i] -= Request[pronum][i];
			Need[pronum][i] += Request[pronum][i];
		}
		printf("恢复至未分配状态：\n");
		print();
	}
}
bool Safe()//判断分配后是否安全
{
	int i, j;
	int count;
	int l = 0;
	int c = 0;

	int Work[sourcenum];
	for (i = 0; i < sourcenum; i++)
	{
		Work[i] = Available[i];
	}
	for (i = 0; i < processnum; i++)
	{
		Finish[i] = false;
	}

	for (i = 0; i < processnum; i++)
	{
		if(Finish[i] == false)
		{
			for (j = 0; j < sourcenum; j++)
			{
				if (Need[i][j] <= Work[j])
				{
					c++;
				}
			}
		}
		if (c == sourcenum)
		{
			for (j = 0; j < sourcenum; j++)
			{
				Work[j] += Allocation[i][j];
			}
			Finish[i] = true;
			sort[l] = i;
			l++;
			c = 0;
		}
		else
		{
			c = 0;
		}
		}
	for (i = 0; i < processnum; i++)
	{
		if (Finish[i] == false)
		{
			for (j = 0; j < sourcenum; j++)
			{
				if (Need[i][j] <= Work[j])
				{
					c++;
				}
			}
		}
		if (c == sourcenum)
		{
			for (j = 0; j < sourcenum; j++)
			{
				Work[j] += Allocation[i][j];
			}
			Finish[i] = true;
			sort[l] = i;
			l++;
			c = 0;
		}
		else
		{
			c = 0;
		}
	}
	if (l == processnum)
	{
		printf("分配后处于安全状态\n");
		printf("某一安全序列如下：\n");
		for (count = 0; count < processnum; count++)
		{
			printf("%d  ", sort[count]);
		}
		printf("\n");
		return true;
	}
	else
		printf("分配后进程无法继续\n");
	return false;
}


