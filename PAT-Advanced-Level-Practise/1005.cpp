/**
    2017.3.2
    Donald
*/

//1005. Spell It Right (20)
/**
    思路：
    字符输入，求和(int 就可，< 100 个 10)
    按倒序输出。
*/

#include<cstdio>
#include<stack>
using namespace std;

stack<int> Stack;

void outputEnglish(int i){
    if(i == 0)
        printf("zero");
    else if(i == 1)
        printf("one");
    else if(i == 2)
        printf("two");
    else if(i == 3)
        printf("three");
    else if(i == 4)
        printf("four");
    else if(i == 5)
        printf("five");
    else if(i == 6)
        printf("six");
    else if(i == 7)
        printf("seven");
    else if(i == 8)
        printf("eight");
    else if(i == 9)
        printf("nine");
}


int main(void){
    char N;
    int ans = 0;
    while((N = getchar()) != '\n'){
        ans += N - '0';
    }
    if(ans == 0){
        printf("zero");
        return 0;
    }
    while(ans){
        Stack.push(ans % 10);
        ans /= 10;
    }
    outputEnglish(Stack.top());
    Stack.pop();
    while(!Stack.empty()){
        printf(" ");
        outputEnglish(Stack.top());
        Stack.pop();
    }
    return 0;
}
