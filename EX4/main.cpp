#pragma  warning(disable:4996)
#include<stdlib.h> 
#include<stdio.h>
#include<time.h>
#include <iostream>

using namespace std;


void rand(int n, int max, int p[]);//随机产生n个不超过max的数存入p[]
int search(int s1[], int s, int frame);//在主存中查找是否有匹配页
int maxs(int p[], int frame);//寻找最近最久未使用的下标
void FIFO(int max, int frame, int p[]);//先进先出页面置换算法
void cFIFO(int max, int frame, int p[]);
void LRU(int max, int frame, int p[]);//最近最久未使用页面置换算法
void cLRU(int max, int frame, int p[]);
int main()
{
    int i;
    int sorts[1001];
    int sort[100] = {7,0,1,2,0,3,0,4,2,3,0,3,2,5,4,3,6,5,3,2};
    printf("请输入页框数：\n");
    int frame;
    scanf("%d", &frame);
    printf("请输入最大逻辑页号：\n");
    int max;
    scanf("%d", &max);
    printf("请输入访问序列长度：\n");
    int length;
    scanf("%d",&length);
    if (length == 1000)
    {
        rand(length, max, sorts);//随机生成
        printf("输出页面访问序列：\n");
        for (i = 0; i < length; i++)
        {
            printf("%d", sorts[i]);
        }
        printf("\n");
        printf("FIFO算法如下：\n");
        cFIFO(length, frame, sorts);
        printf("LRU算法如下：\n");
        cLRU(length, frame, sorts);
    }
    else 
    {
        printf("输出页面访问序列：\n");
        for (i = 0; i < length; i++)
        {
            printf("%d", sort[i]);
        }
        printf("\n");
        printf("FIFO算法如下：\n");
        FIFO(length, frame, sort);
        printf("LRU算法如下：\n");
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
            printf("第%d个页面%d在主存中找到\n", i + 1,p[i]);
        }
        else 
        {
            n = n % frame;
            printf("主存%d被替换，替换前页号:%d，替换后页号:%d\n", n, str[n], p[i]);
            str[n] = p[i];
            count++;
            n++;
        }
    }
    printf("缺页数为%d\n", (int)count);
    printf("缺页率为%.2f\n", count / max);
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
            printf("第%d个页面%d在主存中找到\n", i + 1, p[i]);
            time[x]=0;
        }
        else
        {
            n = maxs(time, frame);
            printf("主存%d被替换，替换前页号:%d，替换后页号:%d\n", n, str[n], p[i]);
            time[n] = 0;
            str[n] = p[i];
            count++;
            n++;
        }
    }
    printf("缺页数为%d\n", (int)count);
    printf("缺页率为%.2f\n", count / max);
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
            //printf("第%d个页面%d在主存中找到\n", i + 1, p[i]);
        }
        else
        {
            n = n % frame;
            //printf("主存%d被替换，替换前页号:%d，替换后页号:%d\n", n, str[n], p[i]);
            str[n] = p[i];
            count++;
            n++;
        }
    }
    printf("缺页数为%d\n", (int)count);
    printf("缺页率为%.4f\n", count / max);
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
            //printf("第%d个页面%d在主存中找到\n", i + 1, p[i]);
            time[x] = 0;
        }
        else
        {
            n = maxs(time, frame);
            //printf("主存%d被替换，替换前页号:%d，替换后页号:%d\n", n, str[n], p[i]);
            time[n] = 0;
            str[n] = p[i];
            count++;
            n++;
        }
    }
    printf("缺页数为%d\n", (int)count);
    printf("缺页率为%.4f\n", count / max);
}