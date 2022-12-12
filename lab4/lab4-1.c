#include <stdio.h>
#include <conio.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX_PAGE_FRAME 16 // 最大页框数
#define CMD_NUM 2400      // 序列个数
#define MAX_FREQUENCY 4   // 最大计算次数
int command[CMD_NUM];     // 页面序列
int page_num[CMD_NUM];    // 每个序号对应的页框号
int page_frame_num;       // 页框数
// 初始化序列与页框号
void initialize()
{
    srand((unsigned int)time(NULL) * 10);
    for (int i = 0; i < CMD_NUM; i++)
    {
        command[i] = rand();
        page_num[i] = command[i] % MAX_PAGE_FRAME + 1; // 1-16页框号
    }
}
// FIFO算法
int FIFO()
{
    int frame[MAX_PAGE_FRAME] = {0}; // 页框
    int longest_frame = 0;           // 记录停留最长时间的页面
    int miss_num = 0;                // 缺页次数
    bool flag = true;                // 标记是否缺页
    for (int i = 0; i < CMD_NUM; i++)
    {
        flag = true;
        // 判断是否命中
        for (int j = 0; j < page_frame_num; j++)
            if (frame[j] == page_num[i])
            {
                flag = false;
                break;
            }
        // 未命中
        if (flag)
        {
            frame[longest_frame] = page_num[i];

            longest_frame = (longest_frame + 1) % page_frame_num; // 类似队列先进先出
            miss_num++;
        }
    }
    return miss_num;
}

int LRU()
{
    int frame[MAX_PAGE_FRAME] = {0};       // 页框
    int longest_unused = 0;                // 最长时间未使用的页面
    int max_time = 0;                      // 最长未使用时间
    int miss_num = 0;                      // 缺页次数
    int unused_time[MAX_PAGE_FRAME] = {0}; // 未使用的时间
    bool flag = true;                      // 标记是否缺页
    for (int i = 0; i < CMD_NUM; i++)
    {
        flag = true;
        // 判断是否命中
        for (int j = 0; j < page_frame_num; j++)
            if (frame[j] == page_num[i])
            {
                flag = false;
                unused_time[j] = 0; // 未使用时间置零
                break;
            }
        // 未命中
        if (flag)
        {
            longest_unused = 0;
            max_time = 0;
            for (int j = 0; j < page_frame_num; j++)
            {
                // 有空的页框
                if (!frame[j])
                {
                    longest_unused = j;
                    break;
                }
                // 找到未使用时间最长的页
                if (unused_time[j] > longest_unused)
                {
                    longest_unused = j;
                    max_time = unused_time[j];
                }
            }
            // 更新对应页框号
            frame[longest_unused] = page_num[i];
            unused_time[longest_unused] = 0; // 未使用时间置为零
            miss_num++;
        }
        // 每个页的未使用时间加一
        for (int j = 0; j < page_frame_num; j++)
            unused_time[j]++;
    }
    return miss_num;
}
int main()
{
    float count; // 平均缺页次数
    float rate;  // 缺页率
    int choice = 0;
    while (true)
    {
        system("cls");
        printf("1、FIFO算法\n2、LRU算法\n3、结束\n请选择：");
        scanf("%d", &choice);
        for (int i = 0; i < 49; i++)
            printf("-");
        printf("\n|   页框数   \t|   缺页次数   \t|   缺页率   \t|\n");
        for (int i = 0; i < 49; i++)
            printf("-");
        printf("\n");
        for (page_frame_num = 3; page_frame_num < 16; page_frame_num++)
        {
            // 计算多次取平均值
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
