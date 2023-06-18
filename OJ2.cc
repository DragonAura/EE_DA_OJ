#include <cstdio>
#include <cstring>
#define MAX 100000
using namespace std;

struct node
{
    node* next;
    char str[5];
    int ind;
} __attribute__((packed));

class Chain
{
public:
    Chain(node info[], unsigned long size)
    {
        inSize = size;
        unsigned long long aim = (inSize - 1) * inSize / 2 - 1;
        long long sum = 0;
        for (int i = 0; i < inSize; i++)
            sum += info[i].ind;
        unsigned first_ind = aim - sum;
        head = &info[first_ind];
        unsigned newInd = info[first_ind].ind;
        node* newNode = head;
        for (int i = 1; i < inSize; i++)
        {
            newNode->next = &info[newInd];
            newInd = info[newInd].ind;
            newNode = newNode->next;
        }
    }
    friend void Compare(Chain* g1, Chain* g2);

private:
    long long inSize;
    node* head = nullptr;
};

void Compare(Chain* g1, Chain* g2)
{
    if (g1->inSize < g2->inSize)  // 强制要求g2更短
    {
        Chain* temp = g1;
        g1 = g2;
        g2 = temp;
    }
    int dif = g1->inSize - g2->inSize;
    int LastNode = 0;
    node* n1 = g1->head;
    node* n2 = g2->head;
    for (int i = 0; i < dif; i++)
    {
        n1 = n1->next;
    }
    for (int i = 0; i < g2->inSize; i++)
    {
        int res = strcmp(n1->str, n2->str);
        if (res != 0)
            LastNode = i + 1;
        n1 = n1->next;
        n2 = n2->next;
    }
    if (LastNode == g2->inSize)
    {
        printf("-1");
    }
    else
    {
        printf("%d\n", LastNode);
        node* op = g2->head;
        for (int i = 0; i < LastNode; i++)
            op = op->next;
        while (op != nullptr)
        {
            printf("%s ", op->str);
            op = op->next;
        }
    }
}

int main()
{
    node node1[MAX];
    node node2[MAX];
    unsigned M, N;
    scanf("%u%u", &M, &N);
    for (int i = 0; i < M; i++)
        scanf("%s%d", node1[i].str, &node1[i].ind);
    Chain gM(node1, M);
    for (int i = 0; i < N; i++)
        scanf("%s%d", node2[i].str, &node2[i].ind);
    Chain gN(node2, N);
    Compare(&gM, &gN);
}