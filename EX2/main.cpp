#pragma warning(disable:4996)

#include<stdio.h>
#include<stdlib.h>
#include<iostream>

using namespace std;

struct homework {
	int hnum;//��ҵ���
	char hname[3];//��ҵ����
	int come_time;//����ʱ��
	int begin_time;//��ʼʱ��     
	int run_time;//����ʱ��   
	int end_time;//����ʱ��
	int order;//���д���
	int serflag;//���б�־
}homeworks[5];

int put();//����
int putout();//���
int fcfs();//�����ȷ���
int sjf();//����ҵ����
int hrrn();//����Ӧ��

int main()
{
    int num;
    printf("�������Ӧ������ţ�1-FCFS��2-SJF��3-HRRN��0-�˳�\n");
    
    while (true) {
        scanf("%d", &num);
        switch (num)
        {
        case 1:
            put();
            printf("�����ȷ���\n");
            fcfs();
            putout();
            break;
        case 2:
            put();
            printf("����ҵ���ȣ�\n");
            sjf();
            putout();
            break;
        case 3:
            put();
            printf("����Ӧ�����ȣ�\n");
            hrrn();
            putout();
            break;
        case 0:
            printf("���н���");
            exit(0);
        }
    }
    return 0;
}
int fcfs()//�����ȷ���
{
    int time_temp = 0;
    int i;
    int number_schedul;
    time_temp = homeworks[0].come_time;
    for (i = 0; i < 5; i++) {
        homeworks[i].begin_time = time_temp;
        homeworks[i].end_time = homeworks[i].begin_time + homeworks[i].run_time;
        homeworks[i].serflag = 1;
        time_temp = homeworks[i].end_time;
        number_schedul = i;
        homeworks[number_schedul].order = i + 1;
    }
    return 0;
}
int sjf()//����ҵ����
{
    float temp_time = 0;
        int i = 0, j;
        int number_schedul, temp_counter;
        float run_time;
        run_time = homeworks[i].run_time;
        j = 1;
        while ((j < 5) && (homeworks[i].come_time == homeworks[j].come_time)) {//���ҵ�һ�������ȵĽ���
            if (homeworks[j].run_time < homeworks[i].run_time) {
                run_time = homeworks[j].run_time;
                i = j;
            }
            j++;
        }
        //�Ե�һ�������ȵĽ�������Ӧ�Ĳ���
        number_schedul = i;
        homeworks[number_schedul].begin_time = homeworks[number_schedul].come_time;
        homeworks[number_schedul].end_time = homeworks[number_schedul].begin_time + homeworks[number_schedul].run_time;
        homeworks[number_schedul].serflag = 1;
        temp_time = homeworks[number_schedul].end_time;
        homeworks[number_schedul].order = 1; temp_counter = 1;
        while (temp_counter < 5) {
            for (j = 0; j < 5; j++) {
                if ((homeworks[j].come_time <= temp_time) && (!homeworks[j].serflag)) {
                    run_time = homeworks[j].run_time;
                    number_schedul = j;
                    break;
                }
            }
            for (j = 0; j < 5; j++) {//������һ�������ȵĽ���
                if ((homeworks[j].come_time <= temp_time) && (!homeworks[j].serflag))
                    if (homeworks[j].run_time < run_time) {
                        run_time = homeworks[j].run_time;
                        number_schedul = j;
                    }
            }
            //���ҵ�����һ�������ȵĽ�������Ӧ�Ĳ���  
            homeworks[number_schedul].begin_time = temp_time;
            homeworks[number_schedul].end_time = homeworks[number_schedul].begin_time + homeworks[number_schedul].run_time;
            homeworks[number_schedul].serflag = 1;
            temp_time = homeworks[number_schedul].end_time;
            temp_counter++;
            homeworks[number_schedul].order = temp_counter;
        }
        return 0;
}
int hrrn()//����Ӧ��
{
    int j, number_schedul, temp_counter;
        float temp_time, respond_rate, max_respond_rate;
        //��һ�����̱����� 
        homeworks[0].begin_time = homeworks[0].come_time;
        homeworks[0].end_time = homeworks[0].begin_time + homeworks[0].run_time;
        temp_time = homeworks[0].end_time;
        homeworks[0].serflag = 1;
        homeworks[0].order = 1;
        temp_counter = 1;//������������
        while (temp_counter < 5) {
            max_respond_rate = 0;
            for (j = 1; j < 5; j++) {
                if ((homeworks[j].come_time <= temp_time) && (!homeworks[j].serflag))
                {
                    respond_rate = (temp_time - homeworks[j].come_time) / homeworks[j].run_time;
                    if (respond_rate > max_respond_rate) {
                        max_respond_rate = respond_rate;
                        number_schedul = j;
                    }
                }
            }
            //����Ӧ�ȸߵĽ���
            homeworks[number_schedul].begin_time = temp_time;
            homeworks[number_schedul].end_time = homeworks[number_schedul].begin_time + homeworks[number_schedul].run_time;
            temp_time = homeworks[number_schedul].end_time;
            homeworks[number_schedul].serflag = 1;
            temp_counter += 1;
            homeworks[number_schedul].order = temp_counter;
        }
        return 0;
}
int put()//����
{
    int i;
    for (i = 0; i < 5; i++)
    {
        homeworks[i].hnum = i + 1;
        homeworks[i].begin_time = 0;
        homeworks[i].end_time = 0;
        homeworks[i].order = 0;
        homeworks[i].serflag = 0;
    }
    strcpy(homeworks[0].hname, "JA");
    strcpy(homeworks[1].hname, "JB");
    strcpy(homeworks[2].hname, "JC");
    strcpy(homeworks[3].hname, "JD");
    strcpy(homeworks[4].hname, "JE");
    homeworks[0].run_time = 20;
    homeworks[1].run_time = 30;
    homeworks[2].run_time = 10;
    homeworks[3].run_time = 24;
    homeworks[4].run_time = 6;
    homeworks[0].come_time = 160;
    homeworks[1].come_time = 170;
    homeworks[2].come_time = 175;
    homeworks[3].come_time = 180;
    homeworks[4].come_time = 185;
    return 0;
}
int putout()//���
{
    int i;
    int f1 = 0;
    float turn_round_time = 0, w = 0;
    printf("���� ��� ����ʱ�� ����ʱ�� ��ʼʱ�� ����ʱ��  ���� ��תʱ��\n");
    for (i = 0; i < 5; i++) {
        f1 = homeworks[i].end_time - homeworks[i].come_time;
        turn_round_time += f1;
        w += ((float)f1/(float)homeworks[i].run_time);
        printf("%s\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n", homeworks[i].hname, homeworks[i].hnum, homeworks[i].come_time, homeworks[i].run_time, homeworks[i].begin_time, homeworks[i].end_time, homeworks[i].order, f1);
    }
    printf("ƽ����תʱ��=%5.2f\n", turn_round_time/5);
    printf("ƽ����Ȩ��תʱ��=%5.5f\n", w/5);
    return 0;
}