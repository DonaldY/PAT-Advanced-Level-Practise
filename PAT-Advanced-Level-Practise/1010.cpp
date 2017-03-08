/**
    2017.3.7
    Donald
*/

//1010. Radix (25)

/**
    题意：input：N1，N2，Tag, Radix
        if Tag == 1，find K，if N1(Radix) == N2(K)
            若是  ：输出最小的K
            若不是：输出Impossible
        if Tag == 2, find K, if N2(Radix) == N1(K)
            若是  ：输出最小的K
            若不是：输出Impossible
*/
/**
    思路：
    若tag == 2， 交换N1，N2
    1.将N1转化为P的进制数
        使用按权展开
    2.找到K，能将N2转化为N1(Radix)。
        找上线，即N1(Radix)
        找下线，从0 ~ N( 每个digit > N，N++)

    另外测试用例：
        1.若N1 = N2  = 1， print 2；
        2.若N1 = N2 != 1， print radix;
*/

#include<cstdio>
#include<cstring>
using namespace std;
#define LL long long
#define MAXN 11

char N1[MAXN], N2[MAXN];
int Tag;
LL Radix;

void solve();
LL changeDec();
LL findLowRadix();
LL binarySearch(LL low, LL high, LL top);
int compare(LL radix, LL target);


int main(void){

    scanf("%s %s %d %lld", N1, N2, &Tag, &Radix);

    if(Tag == 2){
        char q[MAXN];
        strcpy(q, N1);
        strcpy(N1, N2);
        strcpy(N2, q);
    }
//    for(int i = 0 ; i < strlen(N1); ++i){
//        printf("%c ", N1[i]);
//    }
//    printf("\n");
//    for(int i = 0 ; i < strlen(N2); ++i){
//        printf("%c ", N2[i]);
//    }

    solve();

    return 0;
}

void solve(){
    LL target = changeDec();
    LL least  = findLowRadix();
    LL most   = (target + 1 > least + 1) ? target + 1 : least + 1;  //eg. 1, so +1;
    LL res = binarySearch(least, most, target);
    if(res == -1)
        printf("Impossible");
    else
        printf("%lld", res);

}

LL changeDec(){
    LL res = 0;
    LL cnt = 1;
    LL num;
    for(LL i = strlen(N1) - 1; i >= 0; --i){
        if(N1[i] >= 'a' && N1[i] <= 'z')
            num = N1[i] - 'a' + 10;
        else if(N1[i] >= '0' && N1[i] <= '9')
            num = N1[i] - '0';
        res += num * cnt;
        cnt *= Radix;
    }
    return res;
}

LL findLowRadix(){
    LL low = 0;
    LL num;
    for(LL i = strlen(N2) - 1; i >= 0; --i){
        if(N2[i] >= 'a' && N2[i] <= 'z')
            num = N2[i] - 'a' + 10;
        else if(N2[i] >= '0' && N2[i] <= '9')
            num = N2[i] - '0';
        if(num + 1 > low)
            low = num + 1;
    }
    return low;
}

LL binarySearch(LL low, LL high, LL top){
    LL mid = low;
    LL tmp;

    while(low <= high){
        tmp = compare(mid, top);
        if(tmp>0){
             high = mid - 1;
         }else if(tmp < 0 ){
             low = mid + 1;
         }
         else
             return mid;

         mid = (low + high) / 2;
    }
    return -1;
}


int compare(LL radix, LL target){
    LL cnt = 1;
    LL num = 1;
    LL sum = 0;
    for(LL i = strlen(N2) -1; i >= 0; --i){
        if(N2[i] >= 'a' && N2[i] <= 'z')
            num = N2[i] - 'a' + 10;
        else if(N2[i] >= '0' && N2[i] <= '9')
            num = N2[i] - '0';
        sum += num * cnt;
        cnt *= radix;
        if(sum > target)
            return 1;
    }
    if(sum > target)
        return 1;
    else if(sum < target)
        return -1;
    else
        return 0;
}
