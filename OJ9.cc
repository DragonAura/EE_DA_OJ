#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

unsigned short N, M;

unsigned short need;
unsigned short haveNum[40000];
unsigned short have[40000];

unsigned temp;
unsigned short temp2;

unsigned char dp[65536];

unsigned short output[65536][2];

int main()
{
    ios::sync_with_stdio(false);
    cin >> N >> M;
    for (unsigned short i = 0; i < M; i++)
        cin >> haveNum[i];
    need = 0;
    for (unsigned short i = 0; i < N; i++)
    {
        cin >> temp;
        need += 1 << temp;
    }
    for (unsigned short i = 0; i < M; i++)
    {
        have[i] = 0;
        for (unsigned short j = 0; j < haveNum[i]; j++)
        {
            cin >> temp;
            have[i] += 1 << temp;
        }
    }
    for (unsigned i = 0; i < 65536; i++)
    {
        if ((i | have[0]) == have[0])
            dp[i] = 1;
        else
            dp[i] = 200;
    }
    for (unsigned short i = 1; i < M; i++)
    {
        for (unsigned j = 0; j < 65536; j++)
        {
            temp = j & have[i];
            if (temp == j)
            {
                dp[j] = 1;
                output[j][0] = i;
            }
            else if (temp == 0)
                continue;
            else
            {
                temp2 = j ^ temp;
                if (dp[j] < dp[temp2] + 1)
                    continue;
                else
                {
                    dp[j] = dp[temp2] + 1;
                    memcpy(output[j], output[temp2], 2);
                    output[j][dp[j] - 1] = i;
                }
            }
        }
        if (dp[need] <= 2)
            break;
    }
    if (dp[need] > 2)
        cout << -1;
    else
        for (unsigned short i = 0; i < dp[need]; i++)
            cout << output[need][i] << ' ';
}