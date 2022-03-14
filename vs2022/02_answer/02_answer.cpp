#include <stdio.h>
#include <cstdlib>
#define FIRST_COST 6
#define NEXT_COST 2

int main1(int argc, char** argv)
{
    int weight, cost;

    printf("重量\t价格\n");
    for (weight = 1, cost = FIRST_COST; weight <= 10; ++weight, cost = FIRST_COST + (weight - 1) * NEXT_COST)
        printf("%d\t¥%d\n", weight, cost);

    return 0;
}

int main(int argc, char** argv)
{
    for(int i = 0; i < 10; i++)
    {
        int a = rand(), b = rand(), c = rand(), max;
        // printf("请输入3个整数：");
        printf("%d,%d,%d", a, b, c);
        max = (c > ((a > b) ? a : b)) ? c : ((a > b) ? a : b);
        printf("3个整数中的最大的是：%d\n", max);
        max = a > b ? (a > c ? a : c) : (b > c ? b : c);
        printf("3个整数中的最大的是：%d\n", max);
    }

    return 0;
}