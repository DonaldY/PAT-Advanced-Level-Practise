/**
    2018.1.29
    Donald
*/
//1023. Have Fun with Numbers (20)

/**

    k 位的数

    1. 数 * 2
    2. 判断新数是否由原来的数组成
*/


#include<cstdio>
#include<cstring>
#include<stack>
using namespace std;

int flagOrigin[11];
int flagResult[11];
stack<int> Stack;
char str[21];

int main(void) {

    int cnt = 0;
    char temp =0;

    while ((temp = getchar()) != '\n') {
        str[cnt++] = temp;
        flagOrigin[temp - '0'] ++;
    }

    int tempNum = 0;
    for (int i = cnt - 1; i >= 0; --i) {
        tempNum += (str[i] - '0') * 2;
        Stack.push(tempNum % 10);
        tempNum /= 10;
    }

    while (tempNum != 0) {
        Stack.push(tempNum % 10);
        tempNum /= 10;
    }

    int j = 0;
    while (!Stack.empty()) {
        flagResult[Stack.top()] ++;
        str[j++] = Stack.top() + '0';
        Stack.pop();
    }

    if (cnt != j) {
        printf("No\n");
        printf("%s", str);
        return 0;
    }

    for (int i = 1; i <= 9; ++i) {
        if (flagResult[i] != flagOrigin[i]) {
            printf("No\n");
            printf("%s", str);
            return 0;
        }
    }

    printf("Yes\n");
    printf("%s", str);

    return 0;
}

