#include <cstdio>
using namespace std;

int N;
int newData;
int nodeNum = 0;

struct node
{
    int data1 = -1;
    int data2 = -1;
    int left = -1;
    int right = -1;
};

node NodeList[100010];

int lastIndex = -1;

void InsertNode(int index)
{
    if (NodeList[index].data1 == -1)
        NodeList[nodeNum].data1 = newData;
    else
    {
        if (newData < NodeList[index].data1)
        {
            if (NodeList[index].left == -1)
                NodeList[index].left = ++nodeNum;
            InsertNode(NodeList[index].left);
        }
        else
        {
            if (NodeList[index].right == -1)
                NodeList[index].right = ++nodeNum;
            InsertNode(NodeList[index].right);
        }
    }
}

void BuildTree()
{
    scanf("%d", &newData);
    NodeList[0].data1 = newData;
    for (int i = 1; i < N; i++)
    {
        scanf("%d", &newData);
        InsertNode(0);
    }
}

unsigned GetLayer(int index, int res)
{
    if (index == -1)
        return 0;
    if (res > NodeList[index].data1)
        return GetLayer(NodeList[index].right, res) + 1;
    else if (res < NodeList[index].data1)
        return GetLayer(NodeList[index].left, res) + 1;
    else
        return 1;
}

void tryData(int index)
{
    if (lastIndex == -1)
    {
        lastIndex = index;
        return;
    }
    else
    {
        if (GetLayer(0, NodeList[lastIndex].data1) < GetLayer(0, NodeList[index].data1))
        {
            lastIndex = index;
            return;
        }
        else
        {
            NodeList[index].data2 = NodeList[lastIndex].data1;
            if (NodeList[lastIndex].left == -1 && NodeList[lastIndex].right == -1 && NodeList[lastIndex].data2 == -1)
            {
                NodeList[lastIndex].data1 = -2;
                NodeList[lastIndex].data2 = -2;
            }
            lastIndex = index;
            return;
        }
    }
}

void Zip(int index)
{
    if (index != -1)
    {
        Zip(NodeList[index].left);
        tryData(index);
        Zip(NodeList[index].right);
    }
}

void PrintData(int i)
{
    if (i == -1)
        printf("-");
    else if (i == -2)
        ;
    else
        printf("%d ", i);
}

void Output(int index)
{
    if (index != -1)
    {
        PrintData(NodeList[index].data1);
        PrintData(NodeList[index].data2);
        Output(NodeList[index].left);
        Output(NodeList[index].right);
    }
}

int main()
{
    scanf("%d", &N);
    BuildTree();
    Zip(0);
    Output(0);
}
