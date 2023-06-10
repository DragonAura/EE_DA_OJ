#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <ctype.h>
int find(int x, int arr[])
{
    int y = 0;
    for (y = 0;; y++)
        if (arr[y] == x)
            return y;
}
int main()
{
    int M, N;
    scanf("%d", &M);
    scanf("%d", &N);
    char arr1[100000][4];
    char arr2[100000][4];
    int pointm[100000];
    int pointn[100000];
    char output[100000][4];
    int i = 0;
    for (i = 0; i < M; i++)
    {
        scanf("%s", arr1[i]);
        scanf("%d", &pointm[i]);
    }
    int j = 0;
    for (j = 0; j < N; j++)
    {
        scanf("%s", arr2[j]);
        scanf("%d", &pointn[j]);
    }
    int k = 0;
    int flag = 0;
    int time = 0;
    int pm = -1;
    int pn = -1;
    int ppm = 0;
    int ppn = 0;
    for (k = 0;; k++)
    {
        ppm = find(pm, pointm);
        ppn = find(pn, pointn);
        flag = strcmp(arr1[ppm], arr2[ppn]);
        if (flag == 0)
        {
            strcpy(output[k], arr1[ppm]);
            pm = ppm;
            pn = ppn;
            time++;
        }
        else
            break;
    }
    if (time == 0)
        printf("-1");
    else
    {
        if (M < N)
            printf("%d\n", M - time);
        else
            printf("%d\n", N - time);
        int s = time - 1;
        for (s = time - 1; s >= 0; s--)
        {
            printf("%s ", output[s]);
        }
    }
    return 0;
}