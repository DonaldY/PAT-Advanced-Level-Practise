/**
    2017.3.12
    Donald
*/
//1013. Battle Over Cities (25)

/**
    meaning of the title:
    N: city   M：highway，K：neek checked cities number

    thinking：
    并查集
*/


#include<cstdio>

using namespace std;
#define MAXN 500000

int N, M, K;
int par[MAXN];
int startEdge[MAXN], endEdge[MAXN];

void init(int n) {
    for (int i = 1; i <= n; ++i) {
        par[i] = i;
    }
}

int find(int x) {
    if (par[x] == x) {
        return x;
    } else {
        int temp = find(par[x]);
        par[x] = temp;
        return temp;
    }
}

int main(void) {

    int c1 , c2, checkCity;
    scanf("%d%d%d", &N, &M, &K);

    for (int i = 1; i <= M; ++i) {
        scanf("%d%d", &c1, &c2);
        startEdge[i] = c1;
        endEdge[i] = c2;
    }
    int cnt = 0;
    while (K --) {
        init(N);
        scanf("%d", &checkCity);
        cnt = 0;
        for (int i = 1; i <= M; ++i) {
            if (startEdge[i] != checkCity && endEdge[i] != checkCity) {
                c1 = find(startEdge[i]);
                c2 = find(endEdge[i]);
                if (c1 != c2)
                    par[c2] = c1;
            }
        }
        for (int i = 1; i <= N; ++i) {
            if (par[i] == i && par[i] != checkCity)
                cnt++;
        }
        printf("%d\n", cnt - 1);
    }
    return 0;
}

