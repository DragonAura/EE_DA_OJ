#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

std::hash<std::string> hashFunc;

struct dsu
{
    std::vector<int> parent;
    std::vector<int> size;
    dsu(int n) :
        parent(n),
        size(n, 1)
    {
        for (int i = 0; i < n; i++)
            parent[i] = i;
    }
    int find(int x)
    {
        if (x != parent[x])
            parent[x] = find(parent[x]);
        return parent[x];
    }
    void merge(int x, int y)
    {
        x = find(x);
        y = find(y);
        if (x == y)
            return;
        if (size[x] < size[y])
            std::swap(x, y);
        parent[y] = x;
        size[x] += size[y];
    }
};

int main()
{
    ios::sync_with_stdio(false);
    unsigned short N, k;
    long sum = 0;
    cin >> N;
    if (N > 5000)
        return 0;
    string newString;
    std::vector<std::pair<std::string, long long>> resTable;
    resTable.reserve(285000);
    for (int i = 0; i < N; i++)
    {
        cin >> k;
        sum += k;
        for (int i = 0; i < k; i++)
        {
            cin >> newString;
            transform(newString.begin(), newString.end(), newString.begin(), ::tolower);
            long long hash = hashFunc(newString);
            resTable.emplace_back(std::make_pair(newString, hash));
        }
    }
    sort(resTable.begin(), resTable.end(), [](std::pair<std::string, long long> a, std::pair<std::string, long long> b)
         { return a.second < b.second; });
    dsu res(resTable.size());
    for (int i = 0; i < resTable.size(); i++)
    {
        auto it = find_if(resTable[i].first.begin(), resTable[i].first.end(), [](char c)
                          { return c == 'l'; });
        while (it != resTable[i].first.end())
        {
            if (it == resTable[i].first.end())
            {
                if (i != 0 && resTable[i].second == resTable[i - 1].second)
                {
                    res.merge(i, i - 1);
                }
                break;
            }
            auto tempString = resTable[i].first.substr(0, it - resTable[i].first.begin()) + resTable[i].first.substr(it - resTable[i].first.begin() + 1);
            auto tempHash = hashFunc(tempString);
            auto it2 = lower_bound(resTable.begin(), resTable.end(), std::make_pair(tempString, tempHash), [](std::pair<std::string, long long> a, std::pair<std::string, long long> b)
                                   { return a.second < b.second; });
            if (it2 != resTable.end() && it2->second == tempHash)
                res.merge(it2 - resTable.begin(), i);
            it = find_if(it + 1, resTable[i].first.end(), [](char c)
                         { return c == 'l'; });
        }
    }
    cout << *max_element(res.size.begin(), res.size.end());
}