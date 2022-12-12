#include <stdio.h>
#include <conio.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX_PAGE_FRAME 16 // ���ҳ����
#define CMD_NUM 2400      // ���и���
#define MAX_FREQUENCY 4   // ���������
int command[CMD_NUM];     // ҳ������
int page_num[CMD_NUM];    // ÿ����Ŷ�Ӧ��ҳ���
int page_frame_num;       // ҳ����
// ��ʼ��������ҳ���
void initialize()
{
    srand((unsigned int)time(NULL) * 10);
    for (int i = 0; i < CMD_NUM; i++)
    {
        command[i] = rand();
        page_num[i] = command[i] % MAX_PAGE_FRAME + 1; // 1-16ҳ���
    }
}
// FIFO�㷨
int FIFO()
{
    int frame[MAX_PAGE_FRAME] = {0}; // ҳ��
    int longest_frame = 0;           // ��¼ͣ���ʱ���ҳ��
    int miss_num = 0;                // ȱҳ����
    bool flag = true;                // ����Ƿ�ȱҳ
    for (int i = 0; i < CMD_NUM; i++)
    {
        flag = true;
        // �ж��Ƿ�����
        for (int j = 0; j < page_frame_num; j++)
            if (frame[j] == page_num[i])
            {
                flag = false;
                break;
            }
        // δ����
        if (flag)
        {
            frame[longest_frame] = page_num[i];

            longest_frame = (longest_frame + 1) % page_frame_num; // ���ƶ����Ƚ��ȳ�
            miss_num++;
        }
    }
    return miss_num;
}

int LRU()
{
    int frame[MAX_PAGE_FRAME] = {0};       // ҳ��
    int longest_unused = 0;                // �ʱ��δʹ�õ�ҳ��
    int max_time = 0;                      // �δʹ��ʱ��
    int miss_num = 0;                      // ȱҳ����
    int unused_time[MAX_PAGE_FRAME] = {0}; // δʹ�õ�ʱ��
    bool flag = true;                      // ����Ƿ�ȱҳ
    for (int i = 0; i < CMD_NUM; i++)
    {
        flag = true;
        // �ж��Ƿ�����
        for (int j = 0; j < page_frame_num; j++)
            if (frame[j] == page_num[i])
            {
                flag = false;
                unused_time[j] = 0; // δʹ��ʱ������
                break;
            }
        // δ����
        if (flag)
        {
            longest_unused = 0;
            max_time = 0;
            for (int j = 0; j < page_frame_num; j++)
            {
                // �пյ�ҳ��
                if (!frame[j])
                {
                    longest_unused = j;
                    break;
                }
                // �ҵ�δʹ��ʱ�����ҳ
                if (unused_time[j] > longest_unused)
                {
                    longest_unused = j;
                    max_time = unused_time[j];
                }
            }
            // ���¶�Ӧҳ���
            frame[longest_unused] = page_num[i];
            unused_time[longest_unused] = 0; // δʹ��ʱ����Ϊ��
            miss_num++;
        }
        // ÿ��ҳ��δʹ��ʱ���һ
        for (int j = 0; j < page_frame_num; j++)
            unused_time[j]++;
    }
    return miss_num;
}
int main()
{
    float count; // ƽ��ȱҳ����
    float rate;  // ȱҳ��
    int choice = 0;
    while (true)
    {
        system("cls");
        printf("1��FIFO�㷨\n2��LRU�㷨\n3������\n��ѡ��");
        scanf("%d", &choice);
        for (int i = 0; i < 49; i++)
            printf("-");
        printf("\n|   ҳ����   \t|   ȱҳ����   \t|   ȱҳ��   \t|\n");
        for (int i = 0; i < 49; i++)
            printf("-");
        printf("\n");
        for (page_frame_num = 3; page_frame_num < 16; page_frame_num++)
        {
            // ������ȡƽ��ֵ
            count = 0;
            for (int i = 0; i < MAX_FREQUENCY; i++)
            {
                initialize();
                if (choice == 1)
                    count += FIFO();
                else
                    count += LRU();
            }
            count /= 4;
            rate = (count / CMD_NUM) * 100;
            printf("|   %d   \t|   %g   \t|   %.1f%%   \t|\n", page_frame_num, count, rate);
        }
        for (int i = 0; i < 49; i++)
            printf("-");
        printf("\n");
        system("pause");
    }
    return 0;
}
