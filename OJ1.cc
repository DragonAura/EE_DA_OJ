#include <cstdio>
#define delta 0.001
using namespace std;

float A, B, C, D;

struct Point
{
    float x, y, z;
};

inline bool OnPlane(Point pt)  // 判断输入点是否在面上
{
    return (A * pt.x + B * pt.y + C * pt.z + D) < delta && (A * pt.x + B * pt.y + C * pt.z + D) > -delta;
}

inline void FixPlane(Point pt1, Point pt2, Point pt3)  // 按照输入的三个点构建平面
{
    A = ((pt2.y - pt1.y) * (pt3.z - pt1.z) - (pt2.z - pt1.z) * (pt3.y - pt1.y));
    B = ((pt2.z - pt1.z) * (pt3.x - pt1.x) - (pt2.x - pt1.x) * (pt3.z - pt1.z));
    C = ((pt2.x - pt1.x) * (pt3.y - pt1.y) - (pt2.y - pt1.y) * (pt3.x - pt1.x));
    D = (0 - (A * pt1.x + B * pt1.y + C * pt1.z));
}

int main()
{
    unsigned N = 5;
    scanf("%u", &N);
    Point* PtList = new Point[N];
    for (int i = 0; i < N; i++)
    {
        scanf("%f%f%f", &PtList[i].x, &PtList[i].y, &PtList[i].z);
    }
    FixPlane(PtList[0], PtList[1], PtList[2]);
    if (OnPlane(PtList[3]) == false)
    {
        FixPlane(PtList[5], PtList[1], PtList[2]);
        if (OnPlane(PtList[0]) == false && OnPlane(PtList[3]) == false)
        {
            FixPlane(PtList[5], PtList[0], PtList[3]);
            if (OnPlane(PtList[1]) == false)
                printf("%d", 1);
            else
                printf("%d", 2);
        }
        else
        {
            if (OnPlane(PtList[0]) == false)
                printf("%d", 0);
            else
                printf("%d", 3);
        }
    }
    else
        for (int i = 4; i < N; i++)
        {
            if (OnPlane(PtList[i]) == false)
                printf("%d", i);
        }
}