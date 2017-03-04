/**
    2017.3.4
    Donald
*/

//1007. Maximum Subsequence Sum (25)

/**
    ˼·��
    first ʲôʱ���ı䣬 last ʲôʱ���ı�
    first �� sum > ans ʱ�����Ի�Ҫ�ø�����temp��ָ��
    last  �� sum > ans ʱ����ת����ǰ��i
*/

#include<cstdio>

using namespace std;
#define MAXN 100001

int Num[MAXN];

int main(void){
    int N;
    scanf("%d", &N);
    for(int i = 0 ; i < N; ++i)
        scanf("%d", &Num[i]);
    int thisSum = 0;
    int maxnSum = Num[0];
    int first = 0, last = 0, temp = 0;
    for(int i = 0 ; i < N; ++i){
        thisSum += Num[i];
        if(thisSum > maxnSum){
            maxnSum = thisSum;
            last = i;
            first = temp;
        }

        if(thisSum < 0){
            thisSum = 0;
            temp = i + 1;
        }
    }
    if(maxnSum < 0){
        first = 0;
        last = N - 1;
        maxnSum = 0;
    }
    printf("%d %d %d", maxnSum, Num[first], Num[last]);
    return 0;
}

