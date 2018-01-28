/**
    2018.1.28
    Donald
*/
//1021. Deepest Root (25)

/**
    ������ͨͼ ���� ����һ����

    1. ��һ�����
        ��������м�����

    2. �ҵ�����(��)������root
        ���� sample 1��
            �� 3, 4, 5Ϊroot, ��ӵ���������

        ������ʽ���

*/


#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
using namespace std;
#define MAXN 10005

int N;
vector<int> graph[MAXN];
int par[MAXN];
int flag[MAXN];
int deep[MAXN];
int cnt;

int find(int x) {
    if (par[x] == x)
        return x;
    else
        return par[x] = find(par[x]);
}

void unite(int x, int y) {

    x = find(x) ;
    y = find(y) ;

    if (x == y) return ;

    par[x] = y;

}

int dfs(int n) {

    flag[n] = 1;
    int ans = 0;

    for (int i = 0; i < graph[n].size(); ++i) {
        if (flag[graph[n][i]] == 0) {
            int temp = dfs(graph[n][i]);
            ans = max(temp, ans);
        }
    }
    return ans + 1;
}

int main(void) {

    scanf("%d", &N);

    for (int i = 1; i <= N; ++i) {
        par[i] = i;
    }

    for (int i = 1; i < N; ++i) {
        int x, y;
        scanf("%d%d", &x, &y);
        graph[x].push_back(y);
        graph[y].push_back(x);
        unite(x, y);
    }

    int components = 0;
    for (int i = 1; i <= N; ++i) {
        if (par[i] == i) {
            components ++;
        }
    }

    if (components > 1) {
        printf("Error: %d components\n", components);
        return 0;
    }

    int maxDeep = -1;

    for (int i = 1; i <= N; ++i) {
        cnt = 0;
        memset(flag, 0, sizeof(flag));
        deep[i] = dfs(i);

        if (deep[i] > maxDeep) {
            maxDeep = deep[i];
        }
    }

    for (int i = 1; i <= N; ++i) {
        if (deep[i] == maxDeep) {
            printf("%d\n", i);
        }
    }

    return 0;
}

