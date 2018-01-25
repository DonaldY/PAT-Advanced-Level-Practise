/**
    2018.1.25
    Donald
*/
//1015. Reversible Primes (20)

/**
    input : 整数N  进制数 D
    output: Yes or No

    在进制数D下的整数N 和 其反向数 是否均为质数
*/


#include<cstdio>
#include<queue>
#include <iostream>
using namespace std;

int N, D;
int reverse_N;
queue<char> reverse_Q;

void convertIntoDRedix(int n, int d) {
    int temp = 0;
    while (n){
        temp = n % d;
        n /= d;
        if (temp <= 9) {
            reverse_Q.push(temp + '0');
        } else {
            reverse_Q.push(temp - 10 + 'A');
        }
    }
}

int toInteger(int d) {
    int num = 0;
    int t = 0;
    char tempChar;

    while (!reverse_Q.empty()) {

        tempChar = reverse_Q.front();
        reverse_Q.pop();

        if (tempChar >= '0'&& tempChar <= '9'){
            t = tempChar - '0';
        } else {
            t = tempChar - 'A' + 10;
        }

        num = num * d + t;
    }
    return num;
}

bool isPrime(int n) {
    for (int i = 2; i * i <= n ; ++i) {
        if (n % i == 0) return false;
    }
    return n != 1;
}

int main(void) {

    while (scanf("%d", &N) == 1) {
        if (N < 0) {
            break;
        }

        scanf("%d", &D);

        convertIntoDRedix(N, D);

        reverse_N = toInteger(D);

        if (isPrime(N) && isPrime(reverse_N)) {
            puts("Yes");
        } else {
            puts("No");
        }
    }

    return 0;
}

