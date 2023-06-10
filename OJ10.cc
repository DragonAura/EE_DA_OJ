#include <iostream>
#include <bitset>
#include <queue>
using namespace std;

bitset<1024> map[1024];
bitset<1024> visited[1024][4];
short lx, ly;
short ax, ay, az, bx, by, bz, cx, cy, cz;
string outputPath;

short goal[4][2] = {{-1, 0}, {0, -1}, {1, 0}, {0, 1}};

short temp;

struct point
{
    short x, y, z;
    // int length;
    string path;
};

void Search()
{
    for (short i = 0; i < ly + 4; i++)
        for (short j = 0; j < 4; j++)
            visited[i][j].reset();
    point start, next, current;
    start.x = ax, start.y = ay, start.z = az, start.path = "";
    queue<point> q;
    q.push(start);
    while (!q.empty())
    {
        current = q.front();
        if (current.x == bx && current.y == by && current.z == bz)
        {
            outputPath = current.path;
            // return current.length;
        }
        q.pop();
        if (map[current.y + goal[current.z][0]][current.x + goal[current.z][1]] == 0 && visited[current.y + goal[current.z][0]][current.z][current.x + goal[current.z][1]] == 0)  // F
        {
            next.x = current.x + goal[current.z][1];
            next.y = current.y + goal[current.z][0];
            next.z = current.z;
            // next.length = current.length + 1;
            next.path = current.path + 'F';
            q.push(next);
            visited[current.y + goal[current.z][0]][current.z][current.x + goal[current.z][1]] = 1;
        }
        if (map[current.y + goal[current.z][0]][current.x + goal[current.z][1]] == 0 && map[current.y + 2 * goal[current.z][0]][current.x + 2 * goal[current.z][1]] == 0 && visited[current.y + 2 * goal[current.z][0]][current.z][current.x + 2 * goal[current.z][1]] == 0)  // F2
        {
            next.x = current.x + 2 * goal[current.z][1];
            next.y = current.y + 2 * goal[current.z][0];
            next.z = current.z;
            // next.length = current.length + 1;
            next.path = current.path + '2';
            q.push(next);
            visited[current.y + 2 * goal[current.z][0]][current.z][current.x + 2 * goal[current.z][1]] = 1;
        }
        if (visited[current.y][(current.z + 1) % 4][current.x] == 0)  // L
        {
            next.x = current.x;
            next.y = current.y;
            next.z = (current.z + 1) % 4;
            // next.length = current.length + 1;
            next.path = current.path + 'L';
            q.push(next);
            visited[current.y][(current.z + 1) % 4][current.x] = 1;
        }
        if (visited[current.y][(current.z + 3) % 4][current.x] == 0)  // R
        {
            next.x = current.x;
            next.y = current.y;
            next.z = (current.z + 3) % 4;
            // next.length = current.length + 1;
            next.path = current.path + 'R';
            q.push(next);
            visited[current.y][(current.z + 3) % 4][current.x] = 1;
        }
    }
    // return 114514;
}

void Search2()
{
    for (short i = 0; i < ly + 4; i++)
        for (short j = 0; j < 4; j++)
            visited[i][j].reset();
    point start, next, current;
    start.x = bx, start.y = by, start.z = bz, start.path = "";
    queue<point> q;
    q.push(start);
    while (!q.empty())
    {
        current = q.front();
        if (current.x == cx && current.y == cy && current.z == cz)
        {
            outputPath += current.path;
            // return current.length;
        }
        q.pop();
        if (map[current.y + goal[current.z][0]][current.x + goal[current.z][1]] == 0 && visited[current.y + goal[current.z][0]][current.z][current.x + goal[current.z][1]] == 0)  // F
        {
            next.x = current.x + goal[current.z][1];
            next.y = current.y + goal[current.z][0];
            next.z = current.z;
            // next.length = current.length + 1;
            next.path = current.path + 'F';
            q.push(next);
            visited[current.y + goal[current.z][0]][current.z][current.x + goal[current.z][1]] = 1;
        }
        if (map[current.y + goal[current.z][0]][current.x + goal[current.z][1]] == 0 && map[current.y + 2 * goal[current.z][0]][current.x + 2 * goal[current.z][1]] == 0 && visited[current.y + 2 * goal[current.z][0]][current.z][current.x + 2 * goal[current.z][1]] == 0)  // F2
        {
            next.x = current.x + 2 * goal[current.z][1];
            next.y = current.y + 2 * goal[current.z][0];
            next.z = current.z;
            // next.length = current.length + 1;
            next.path = current.path + '2';
            q.push(next);
            visited[current.y + 2 * goal[current.z][0]][current.z][current.x + 2 * goal[current.z][1]] = 1;
        }
        if (map[current.y][current.x] == 0 && visited[current.y][(current.z + 1) % 4][current.x] == 0)  // L
        {
            next.x = current.x;
            next.y = current.y;
            next.z = (current.z + 1) % 4;
            // next.length = current.length + 1;
            next.path = current.path + 'L';
            q.push(next);
            visited[current.y][(current.z + 1) % 4][current.x] = 1;
        }
        if (visited[current.y][(current.z + 3) % 4][current.x] == 0)  // R
        {
            next.x = current.x;
            next.y = current.y;
            next.z = (current.z + 3) % 4;
            // next.length = current.length + 1;
            next.path = current.path + 'R';
            q.push(next);
            visited[current.y][(current.z + 3) % 4][current.x] = 1;
        }
    }
    // return 114514;
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    cin >> lx >> ly;
    for (short i = 0; i < ly + 4; i++)
    {
        map[i][0] = 1;
        map[i][1] = 1;
        map[i][lx + 2] = 1;
        map[i][lx + 3] = 1;
    }
    for (short i = 0; i < lx + 4; i++)
    {
        map[0][i] = 1;
        map[1][i] = 1;
        map[ly + 1][i] = 1;
        map[ly + 2][i] = 1;
    }
    for (short i = 2; i <= ly + 1; i++)
        for (short j = 2; j <= lx + 1; j++)
        {
            cin >> temp;
            map[i][j] = temp;
        }
    cin >> ax >> ay >> az >> bx >> by >> bz >> cx >> cy >> cz;
    ax += 2, ay += 2, bx += 2, by += 2, cx += 2, cy += 2, az--, bz--, cz--;
    Search();
    Search2();
    int res = outputPath.length();
    cout << res << endl;
    for (auto i : outputPath)
    {
        switch (i)
        {
            case 'F':
                cout << "F" << endl;
                break;
            case '2':
                cout << "F2" << endl;
                break;
            case 'L':
                cout << "L" << endl;
                break;
            case 'R':
                cout << "R" << endl;
                break;
        }
    }
}