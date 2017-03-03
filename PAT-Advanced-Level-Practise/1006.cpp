/**
    2017.3.3
    Donald
*/
/**
    思路：
    找到最先到的人和最后离开的人。
*/
#include<cstdio>
#include<cstring>
using namespace std;
int M;
int hour, miniute, second;
int ehour = 24, eminiute = 0, esec = 0;
int lhour = 0,  lminiute = 0,  lsec = 0;
int compareE(){
    if(hour < ehour)
        return 1;
    else if(miniute < eminiute)
        return 1;
    else if(second < esec)
        return 1;
    return 0;
}

int compareL(){
    if(hour > lhour)
        return 1;
    else if(miniute > lminiute)
        return 1;
    else if(second > lsec)
        return 1;
    return 0;
}

int main(void){
    scanf("%d", &M);
    char ID_number[16];
    char earlier[16];
    char lastest[16];
    while(M--){
        scanf("%s ", ID_number);
        scanf("%d:%d:%d", &hour, &miniute, &second);
        if(compareE()){
            strcpy(earlier, ID_number);
            ehour = hour;
            eminiute = miniute;
            esec = second;
        }

        scanf("%d:%d:%d", &hour, &miniute, &second);
        if(compareL()){
             strcpy(lastest, ID_number);
             lhour = hour;
             lminiute = miniute;
             lsec = second;
        }

    }
    printf("%s %s", earlier, lastest);
    return 0;
}

