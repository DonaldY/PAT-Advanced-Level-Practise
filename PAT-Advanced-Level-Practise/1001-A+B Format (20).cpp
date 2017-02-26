/**
    2017.2.26
    Donald
*/

//1001. A+B Format (20)

/**
    思路：
    若大于4位，每过3位（7 和 4），则用逗号隔开；否则不用
*/

#include<cstdio>
#include<cmath>
#include<stack>
using namespace std;

stack<char> S;

int main(void){
    int A, B;
    int SUM;
    scanf("%d%d", &A, &B);
    SUM = A + B;
    if(SUM < 0){
        printf("-");
        SUM = -SUM;
    }
    char temp;
    int cnt = 0;
    if(SUM == 0){
        printf("0");
        return 0;
    }
    while(SUM){
        temp = SUM % 10 + '0';
        S.push(temp);
        cnt++;
        SUM /= 10;
    }
    //printf("cnt=%d\n", cnt);
    while(!S.empty()){
        putchar(S.top());
        if(cnt == 7 || cnt == 4){
            putchar(',');
        }
        cnt--;
        S.pop();
    }
    return 0;
}
