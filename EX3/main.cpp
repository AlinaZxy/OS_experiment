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

int sort[processnum];//��Ű�ȫ����
bool Finish[processnum];

void init();//���ݳ�ʼ��
void Bank();//���м��㷨
bool Safe();//�ж��Ƿ��ڰ�ȫ״̬
void print();//�������

int main()
{
	int inp;
	print();//�����ʼ״̬
	Bank();
	while (true)
	{
		printf("������������������������1���˳�����0\n");
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
	printf("�������������Դ���̵Ľ��̺�\n");
	scanf("%d", &pronum);
	printf("�����������Դ�������\n");
	for (j = 0; j < sourcenum; j++)
	{
		scanf("%d", &Request[pronum][j]);
	}

	for (j = 0; j < sourcenum; j++)
	{
		if (Request[pronum][j] > Need[pronum][j])
		{
			printf("��������Դ�������������ֵ������ʧ��\n");
			return;
		}
		if (Request[pronum][j] > Available[j])
		{
			printf("��������Դ������ϵͳ��ǰ��Դ������ȴ�\n");
			return;
		}
	}
	int i;
	for (i = 0; i < sourcenum; i++)//��̽����
	{
		Available[i] -= Request[pronum][i];
		Allocation[pronum][i] += Request[pronum][i];
		Need[pronum][i] -= Request[pronum][i];
	}
	printf("��̽��������\n");
	print();
	if (Safe())
	{
		printf("����󴦰�ȫ״̬��ͬ�����\n");
	}
	else
	{
		printf("�����ϵͳ����ȫ������ʧ��\n");
		for (i = 0; i < sourcenum; i++)
		{
			Available[i] += Request[pronum][i];
			Allocation[pronum][i] -= Request[pronum][i];
			Need[pronum][i] += Request[pronum][i];
		}
		printf("�ָ���δ����״̬��\n");
		print();
	}
}
bool Safe()//�жϷ�����Ƿ�ȫ
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
		printf("������ڰ�ȫ״̬\n");
		printf("ĳһ��ȫ�������£�\n");
		for (count = 0; count < processnum; count++)
		{
			printf("%d  ", sort[count]);
		}
		printf("\n");
		return true;
	}
	else
		printf("���������޷�����\n");
	return false;
}


