/**
    2017.3.5
    Donald
*/

//1008. Elevator (20)

/**
    思路：
    分三种情况. > < ==
*/
#include<cstdio>

using namespace std;

const int UPTIME   = 6;
const int DOWNTIME = 4;
const int STAYTIME = 5;
int N;

int main(void){

    int last = 0;   //last time floor
    int now;    //now floor
    int ans = 0;
    scanf("%d", &N);

    for(int i = 0; i < N; ++i){
        scanf("%d", &now);
        if(now > last){
            ans += (now - last) * UPTIME;
            last = now;
        }else if(now < last){
            ans += (last - now) * DOWNTIME;
            last = now;
        }
        ans += STAYTIME;
    }
    printf("%d", ans);
    return 0;
}
