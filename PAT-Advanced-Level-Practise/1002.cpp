/**
    2017.2.27
    Donald
*/
/**
    多项式求和
    系数过小不要
*/
#include<cstdio>

using namespace std;
#define MAXN 1001
#define EPS 1e-8
double A[MAXN];
int K;
int main(void){
    int T = 2;
    int n, cnt = 0;
    double An;
    while(T--){
        scanf("%d", &K);
        while(K--){
            scanf("%d %lf", &n, &An);
            A[n] += An;
        }
    }
    for(int i = MAXN; i >= 0; i--)
        if(!(A[i] >= -EPS && A[i] <= EPS))
            cnt++;
    printf("%d", cnt);
    for(int i = MAXN; i >= 0; i--)
        if(!(A[i] >= -EPS && A[i] <= EPS))
            printf(" %d %.1lf", i, A[i]);
    return 0;
}
