/**
    2017.3.8
    Donald
*/

//1011. World Cup Betting (20)

/**
    题意:
    求每行最大，输出W or T or L
    并按公式求出最大profit

    思路：
    ps：不用floor。
*/

#include<cstdio>
#include<iostream>
#include<algorithm>
#include<stack>
using namespace std;

#define MAXN 4

double maxnTimes[MAXN];


int main(void){

    double times, maxnTime;
    char betGame;
    int tag;

    for (int i = 0; i < 3; ++i){
        maxnTime = 0;
        tag = 0;
        for (int j = 0; j < 3; ++j){
            scanf("%lf", &times);
            if (times > maxnTime){
                maxnTime = times;
                tag = j;
            }
        }

        if (tag == 0)
            betGame = 'W';
        else if (tag == 1)
            betGame = 'T';
        else if (tag == 2)
            betGame = 'L';
        printf("%c ", betGame);
        maxnTimes[i] = maxnTime;
    }

    sort(maxnTimes, maxnTimes + 3);

    double ans = 1;
    for (int i = 0; i < 3; ++i)
        ans *= maxnTimes[i];
    ans = (ans * 0.65 - 1.0) * 2.0;
    printf("%.2lf", ans);
    return 0;
}
