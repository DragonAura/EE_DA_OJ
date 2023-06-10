#include <cstdio>
#include <vector>
#include <bitset>
#include <iostream>

#define max1 20010
#define max2 200010

using namespace std;

short N;
unsigned M;

unsigned dist[2 * max1];
int queue[2 * max2];
bitset<2 * max1> visited;

struct node
{
    short length;
    unsigned short next;
} __attribute__((packed));

node Vertices[2 * max1][30];

void MakeDist()
{
    for (int i = 1; i <= 2 * N; i++)
        dist[i] = 2147483647;
    dist[1] = 0;
    int front = 0;
    int rear = 0;
    queue[rear++] = 1;
    for (int i = 1; i <= 2 * N; i++)
        visited[i] = 0;
    visited[1] = 1;

    while (front != rear)
    {
        int current = queue[front++];
        for (int i = 1; i <= Vertices[current][0].length; i++)
        {
            unsigned short next = Vertices[current][i].next;
            int length = Vertices[current][i].length;
            if (length > dist[next])
                continue;
            if (dist[next] > dist[current] + length)
            {
                dist[next] = dist[current] + length;
                if (visited[next] == 0)
                {
                    visited[next] = 1;
                    queue[rear++] = next;
                }
            }
        }
        visited[current] = 0;
    }
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    cin >> N >> M;
    for (int i = 0; i < 2 * N; i++)
        Vertices[i][0].length = 0;
    for (int i = 0; i < M; i++)
    {
        short u, v, length;
        cin >> u >> v >> length;
        Vertices[u][++Vertices[u][0].length].length = length;
        Vertices[u][Vertices[u][0].length].next = v;
        Vertices[v + N][++Vertices[v + N][0].length].length = length;
        Vertices[v + N][Vertices[v + N][0].length].next = u + N;
    }
    for (int i = 1; i <= N; i++)
    {
        Vertices[i][++Vertices[i][0].length].length = 0;
        Vertices[i][Vertices[i][0].length].next = i + N;
    }
    MakeDist();
    for (int i = 2; i <= N; i++)
    {
        if (dist[i] == 2147483647 && dist[i + N] == 2147483647)
            cout << "-1 ";
        else
        {
            if (dist[i] < dist[i + N])
                cout << dist[i] << " ";
            else
                cout << dist[i + N] << " ";
        }
    }
}