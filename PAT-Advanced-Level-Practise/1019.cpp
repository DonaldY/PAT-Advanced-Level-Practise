/**
    2018.1.26
    Donald
*/
//1019. General Palindromic Number (20)

/**
    回文数

    整型 -> 对应进制下数

    是否为回文

    output:
        是： YES
        否:  No
        对应进制下数
*/


#include<cstdio>
#include<cstring>
using namespace std;

int N, B;
int arr[32];
int cnt;

void init() {
    cnt = 0;
    memset(arr, 0 , sizeof(arr));
}

void convertIntoBRedix(int n, int b) {

    if(n == 0) {
        arr[0] = 0;
        cnt = 1;
        return ;
    }

    int temp = 0;
    while (n){
        temp = n % b;
        n /= b;
        arr[cnt++] = temp;
    }
}

bool isPalindromic() {

    for (int i = 0 ; i < cnt / 2; ++i) {
        if (arr[i] != arr[cnt - i - 1]) {
            return false;
        }
    }
    return true;
}

void printArray() {
    for (int i = cnt - 1 ; i >= 0; --i) {
        if (i == 0) {
            printf("%d", arr[i]);
        } else {
            printf("%d ", arr[i]);
        }
    }
}

int main(void) {

    while (scanf("%d %d", &N, &B) == 2) {

        init();

        convertIntoBRedix(N, B);

        if (isPalindromic()) {
            puts("Yes");
        } else {
            puts("No");
        }

        printArray();
    }

    return 0;
}

