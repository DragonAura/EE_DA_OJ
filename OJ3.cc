#include <cstdio>

using namespace std;

struct Rem
{
    unsigned size;
    short x;
    short y;
};

struct pt
{
    unsigned short x;
    unsigned short y;
};

bool Mat[1000][1000];
bool AddedMat[1000][1000] = {false};
unsigned N;
unsigned maxSize = 0;
Rem arr[100000];
pt PtList[100000];
unsigned PtInd = 0;
unsigned currentInd = 0;

unsigned GetSize(short x, short y)
{
    if (x < 0 || y < 0 || x >= N || y >= N || Mat[x][y] == false || AddedMat[x][y] == true)
        return 0;
    else
    {
        AddedMat[x][y] = true;
        unsigned l1, l2, l3, l4, l5, l6, l7, l8;
        l1 = GetSize(x - 1, y - 1);
        l2 = GetSize(x - 1, y);
        l3 = GetSize(x - 1, y + 1);
        l4 = GetSize(x, y - 1);
        l5 = GetSize(x, y + 1);
        l6 = GetSize(x + 1, y - 1);
        l7 = GetSize(x + 1, y);
        l8 = GetSize(x + 1, y + 1);
        return l1 + l2 + l3 + l4 + l5 + l6 + l7 + l8 + 1;
    }
}

inline void GetMax()
{
    for (short i = 0; i < N; i++)
        for (short j = 0; j < N; j++)
            if (Mat[i][j] == true && AddedMat[i][j] == false)
            {
                unsigned sizee = GetSize(i, j);
                if (currentInd > 0)
                {
                    if (sizee > arr[currentInd - 1].size)
                    {
                        arr[0].x = i;
                        arr[0].y = j;
                        arr[0].size = sizee;
                        currentInd = 1;
                    }
                    else if (sizee == arr[currentInd - 1].size)
                    {
                        arr[currentInd].x = i;
                        arr[currentInd].y = j;
                        arr[currentInd].size = sizee;
                        currentInd++;
                    }
                    else
                        continue;
                }
                else
                {
                    arr[0].x = i;
                    arr[0].y = j;
                    arr[0].size = sizee;
                    currentInd++;
                }
            }
}

void GetPtList(unsigned x, unsigned y)
{
    if (x < 0 || y < 0 || x >= N || y >= N || Mat[x][y] == false || AddedMat[x][y] == true)
        return;
    else
    {
        AddedMat[x][y] = true;
        PtList[PtInd].x = x;
        PtList[PtInd].y = y;
        PtInd++;
        GetPtList(x - 1, y - 1);
        GetPtList(x - 1, y);
        GetPtList(x - 1, y + 1);
        GetPtList(x, y - 1);
        GetPtList(x, y + 1);
        GetPtList(x + 1, y - 1);
        GetPtList(x + 1, y);
        GetPtList(x + 1, y + 1);
    }
}

void PtListSort()
{
    for (unsigned i = 0; i < PtInd; i++)
    {
        unsigned minInd = i;
        for (unsigned j = i; j < PtInd; j++)
        {
            if (PtList[j].x < PtList[minInd].x || (PtList[j].x == PtList[minInd].x && PtList[j].y < PtList[minInd].y))
                minInd = j;
        }
        if (minInd != i)
        {
            pt temp = PtList[minInd];
            PtList[minInd] = PtList[i];
            PtList[i] = temp;
        }
    }
}

inline void Output()
{
    printf("%u", arr[0].size);
    for (int i = 0; i < currentInd; i++)
    {
        for (unsigned short j = 0; j < N; j++)
            for (unsigned short k = 0; k < N; k++)
                AddedMat[j][k] = false;
        PtInd = 0;
        GetPtList(arr[i].x, arr[i].y);
        PtListSort();
        for (unsigned j = 0; j < PtInd; j++)
            printf("(%hu,%hu)", PtList[j].x, PtList[j].y);
        printf("\n");
    }
}

int main()
{
    scanf("%u", &N);
    for (unsigned i = 0; i < N; i++)
        for (unsigned j = 0; j < N; j++)
        {
            int c = 0;
            scanf("%d", &c);
            if (c == 1)
                Mat[i][j] = true;
            else
                Mat[i][j] = false;
        }
    GetMax();
    if (currentInd == 0)
        printf("-1");
    else
        Output();
}