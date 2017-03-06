**
    2017.3.6
    Donald
*/

//1009. Product of Polynomials (25)

/**
    Tips：
    数组开平方
*/
#include<cstdio>

using namespace std;

#define EPS 1e-10
#define MAXN 1000001

double A[MAXN];
double B[MAXN];
double Ans[MAXN];

void solve(int STARTA, int STARTB){

    for(int  i = STARTA; i >= 0; --i){
        for(int j = STARTB; j >= 0; --j){
            Ans[i + j] += A[i] * B[j];
        }
    }

    int cnt = 0;
    for(int i = MAXN - 1; i >= 0; --i){
        if(!(Ans[i] >= -EPS && Ans[i] <= EPS))
            cnt++;
    }
    printf("%d", cnt);

    for(int i = MAXN - 1; i >= 0; i--)
        if(!(Ans[i] >= -EPS && Ans[i] <= EPS))
            printf(" %d %.1lf", i, Ans[i]);
}

int main(void){

    int K;
    int N;
    int startA, startB;
    scanf("%d", &K);
    scanf("%d", &N);
    startA = N;
    scanf("%lf", &A[N]);
    for(int i = 1; i < K; ++i){
        scanf("%d", &N);
        scanf("%lf", &A[N]);
    }

    scanf("%d", &K);
    scanf("%d", &N);
    startB = N;
    scanf("%lf", &B[N]);
    for(int i = 1; i < K; ++i){
        scanf("%d", &N);
        scanf("%lf", &B[N]);
    }

    solve(startA, startB);
    return 0;
}
