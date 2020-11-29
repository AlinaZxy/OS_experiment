#pragma  warning(disable:4996)
#include<stdlib.h> 
#include<stdio.h>
#include<time.h>
#include <iostream>

using namespace std;


void rand(int n, int max, int p[]);//�������n��������max��������p[]
int search(int s1[], int s, int frame);//�������в����Ƿ���ƥ��ҳ
int maxs(int p[], int frame);//Ѱ��������δʹ�õ��±�
void FIFO(int max, int frame, int p[]);//�Ƚ��ȳ�ҳ���û��㷨
void cFIFO(int max, int frame, int p[]);
void LRU(int max, int frame, int p[]);//������δʹ��ҳ���û��㷨
void cLRU(int max, int frame, int p[]);
int main()
{
    int i;
    int sorts[1001];
    int sort[100] = {7,0,1,2,0,3,0,4,2,3,0,3,2,5,4,3,6,5,3,2};
    printf("������ҳ������\n");
    int frame;
    scanf("%d", &frame);
    printf("����������߼�ҳ�ţ�\n");
    int max;
    scanf("%d", &max);
    printf("������������г��ȣ�\n");
    int length;
    scanf("%d",&length);
    if (length == 1000)
    {
        rand(length, max, sorts);//�������
        printf("���ҳ��������У�\n");
        for (i = 0; i < length; i++)
        {
            printf("%d", sorts[i]);
        }
        printf("\n");
        printf("FIFO�㷨���£�\n");
        cFIFO(length, frame, sorts);
        printf("LRU�㷨���£�\n");
        cLRU(length, frame, sorts);
    }
    else 
    {
        printf("���ҳ��������У�\n");
        for (i = 0; i < length; i++)
        {
            printf("%d", sort[i]);
        }
        printf("\n");
        printf("FIFO�㷨���£�\n");
        FIFO(length, frame, sort);
        printf("LRU�㷨���£�\n");
        LRU(length, frame, sort);
    }
	return 0;
}
void rand(int n, int max,int p[])
{
    int v;
    int i;
    srand(time(NULL));
    for (i = 0; i < n; i++)
    {
        v = rand() % (max + 1);
        p[i] = v;
    }
}
int search(int s1[],int s,int frame)
{
    int i;
    for (i = 0; i < frame; i++)
    {
        if (s == s1[i])
            return i;
    }
    return -1;
}
int maxs(int p[],int frame)
{
    int max = p[0];
    int s=0;
    int i;
    for (i = 1; i < frame ; i++)
    {
        if (p[i] > max)
        {
            s = i;
            max = p[i];
        }
    }

    return s;
}
void FIFO(int max,int frame,int p[])
{
    int i;
    int n=0;
    double count = 0;
    int str[3];
    for (i = 0; i < frame; i++)
    {
        str[i] = p[i];
    }
    for (i = frame; i < max; i++)
    {
        if ((search(str, p[i], frame)) >= 0)
        {
            printf("��%d��ҳ��%d���������ҵ�\n", i + 1,p[i]);
        }
        else 
        {
            n = n % frame;
            printf("����%d���滻���滻ǰҳ��:%d���滻��ҳ��:%d\n", n, str[n], p[i]);
            str[n] = p[i];
            count++;
            n++;
        }
    }
    printf("ȱҳ��Ϊ%d\n", (int)count);
    printf("ȱҳ��Ϊ%.2f\n", count / max);
}
void LRU(int max, int frame, int p[])//max=20
{
    int i,n;
    double count=0;
    int time[3] = { 3,2,1 };
    int str[3];
    for (i = 0; i < frame; i++)
    {
        str[i] = p[i];
    }
    for (i = frame; i < max; i++)
    {
        for (int j = 0; j < frame; j++)
        {
            time[j] += 1;
        }
        if ((search(str, p[i], frame)) >= 0)
        {
            int x;
            x = search(str, p[i], frame);
            printf("��%d��ҳ��%d���������ҵ�\n", i + 1, p[i]);
            time[x]=0;
        }
        else
        {
            n = maxs(time, frame);
            printf("����%d���滻���滻ǰҳ��:%d���滻��ҳ��:%d\n", n, str[n], p[i]);
            time[n] = 0;
            str[n] = p[i];
            count++;
            n++;
        }
    }
    printf("ȱҳ��Ϊ%d\n", (int)count);
    printf("ȱҳ��Ϊ%.2f\n", count / max);
}
void cFIFO(int max, int frame, int p[])
{
    int i;
    int n = 0;
    double count = 0;
    int str[3];
    for (i = 0; i < frame; i++)
    {
        str[i] = p[i];
    }
    for (i = frame; i < max; i++)
    {
        if ((search(str, p[i], frame)) >= 0)
        {
            //printf("��%d��ҳ��%d���������ҵ�\n", i + 1, p[i]);
        }
        else
        {
            n = n % frame;
            //printf("����%d���滻���滻ǰҳ��:%d���滻��ҳ��:%d\n", n, str[n], p[i]);
            str[n] = p[i];
            count++;
            n++;
        }
    }
    printf("ȱҳ��Ϊ%d\n", (int)count);
    printf("ȱҳ��Ϊ%.4f\n", count / max);
}
void cLRU(int max, int frame, int p[])//max=20
{
    int i, n;
    double count = 0;
    int time[3] = { 3,2,1 };
    int str[3];
    for (i = 0; i < frame; i++)
    {
        str[i] = p[i];
    }
    for (i = frame; i < max; i++)
    {
        for (int j = 0; j < frame; j++)
        {
            time[j] += 1;
        }
        if ((search(str, p[i], frame)) >= 0)
        {
            int x;
            x = search(str, p[i], frame);
            //printf("��%d��ҳ��%d���������ҵ�\n", i + 1, p[i]);
            time[x] = 0;
        }
        else
        {
            n = maxs(time, frame);
            //printf("����%d���滻���滻ǰҳ��:%d���滻��ҳ��:%d\n", n, str[n], p[i]);
            time[n] = 0;
            str[n] = p[i];
            count++;
            n++;
        }
    }
    printf("ȱҳ��Ϊ%d\n", (int)count);
    printf("ȱҳ��Ϊ%.4f\n", count / max);
}