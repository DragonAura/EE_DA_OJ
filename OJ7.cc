#include <iostream>
#include <cmath>
#include <iomanip>
#include <algorithm>
#include <array>
#define DELTA 2e-47
#define DELTA2 3e-6
using namespace std;

short N;
long double matrix[61][61];
long double QMatrix[61][61];
long double QQMatrix[61][61];
long double RMatrix[61][61];
long double RRMatrix[61][61];

unsigned TIME = 0;

long double temp[61];
long double temp2[61];

inline void getCol(short i)
{
    for (short j = 0; j < N; j++)
        temp[j] = matrix[j][i];
}

inline void getQCol(short i)
{
    for (short j = 0; j < N; j++)
        temp2[j] = QMatrix[j][i];
}

inline long double VecTime(long double* a, long double* b)
{
    long double res = 0;
    for (int i = 0; i < N; i++)
        res += a[i] * b[i];
    return res;
}

inline void VecSub(long double* a, long double* b, long double t)
{
    for (short i = 0; i < N; i++)
        a[i] -= t * b[i];
}

inline void SetQ(short i, long double* col)
{
    long double t = 1 / std::sqrt(VecTime(col, col));
    for (short j = 0; j < N; j++)
    {
        QMatrix[j][i] = col[j];
        QQMatrix[j][i] = col[j] * t;
    }
}

inline void GetQ()
{
    for (short i = 0; i < N; i++)
    {
        getCol(i);
        for (short j = 0; j < i; j++)
        {
            getQCol(j);
            long double t = VecTime(temp, temp2) / VecTime(temp2, temp2);
            VecSub(temp, temp2, t);
        }
        SetQ(i, temp);
    }
}

inline long double GetMod(long double* a)
{
    long double res = 0;
    for (short i = 0; i < N; i++)
    {
        res += a[i] * a[i];
    }
    return sqrt(res);
}

inline void GetR()
{
    for (short i = 0; i < N; i++)
    {
        RMatrix[i][i] = 1;
        getQCol(i);
        long double t = GetMod(temp2);
        RRMatrix[i][i] = t;
        for (short j = i + 1; j < N; j++)
        {
            getCol(j);
            RMatrix[i][j] = VecTime(temp2, temp) / VecTime(temp2, temp2);
            RRMatrix[i][j] = RMatrix[i][j] * t;
        }
    }
}

inline void GetNewA()
{
    for (short i = 0; i < N; i++)
    {
        for (short j = 0; j < N; j++)
        {
            matrix[i][j] = 0;
            for (short k = 0; k < N; k++)
            {
                matrix[i][j] += RRMatrix[i][k] * QQMatrix[k][j];
            }
        }
    }
}

inline bool Check()
{
    unsigned short Num1 = 0;
    for (short i = 0; i < N; i += 2)
    {
        for (short j = 0; j < i; j += 2)
        {
            if (abs(matrix[i][j]) > DELTA2)
                return false;
            if (abs(matrix[i][j]) > DELTA)
                Num1++;
        }
    }
    int limit = (N * N / 40 - 20) > 0 ? (N * N / 40 - 20) : 0;
    if (Num1 > limit)
        return false;
    else
        return true;
}

void Trans()
{
    while (!Check())
    {
        GetQ();
        GetR();
        GetNewA();
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin >> N;
    for (short i = 0; i < N; i++)
    {
        for (short j = 0; j < N; j++)
        {
            cin >> matrix[i][j];
        }
    }
    Trans();
    std::array<long double, 61> res;
    for (short i = 0; i < N; i++)
    {
        res[i] = matrix[i][i];
    }
    std::sort(res.begin(), res.begin() + N);
    for (short i = 0; i < N; i++)
    {
        cout << std::fixed << std::setprecision(2) << res[i] << endl;
    }
}