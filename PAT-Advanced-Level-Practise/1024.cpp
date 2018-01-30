/**
    2018.1.30
    Donald
*/
//1024. Palindromic Number (25)

/**
    判断是不是回文数

    1. 是
        output 最终数 和 花费的步数
    2. 不是
        直至为回文数或步数消耗完
        output: 最终数 和 总步数
*/


#include<cstdio>
#include<cstring>
#include<cmath>
#include<stack>
using namespace std;
#define MAXN 5000

int sum;
char str[5000];
char rev[5000];
stack<char> Stack;

bool isParlindromic() {

    int len = strlen(str);

    for (int i = 0 ;i < len / 2; ++i) {
        if (str[i] != str[len - i - 1]) {
            return false;
        }
    }

    return true;
}

void reverseStr() {
    int len = strlen(str);

    for (int i = 0; i < len; ++i) {
        rev[i] = str[len - i - 1];
    }
}

void addReverse() {
    int temp = 0;
    int in = 0;
    int len =strlen(str);

    for (int i = len - 1 ; i >= 0 ; --i) {
        temp = (str[i] - '0') + (rev[i] - '0') + in;
        Stack.push((temp % 10) + '0');
        in = temp / 10;
    }

    if (in != 0) {
        Stack.push(in + '0');
    }

    int j = 0;
    while (!Stack.empty()) {
        str[j++] = Stack.top();
        Stack.pop();
    }

}

int main(void) {

    scanf("%s %d", &str, &sum);

    int cnt = 0;

    while (!isParlindromic() && cnt != sum) {

        reverseStr();

        addReverse();

        cnt ++;
    }

    printf("%s\n%d", str, cnt);

    return 0;
}

