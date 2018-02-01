/**
    2018.2.1
    Donald
*/
//1027. Colors in Mars (20)

/**
    给出3个2位数，转化为13进制数
*/


#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

int Red, Green, Blue;
char red[3], green[3], blue[3];

void turnToRadix13(int Color, char color[]) {
    int temp = 0;
    int cnt = 1;
    while (Color != 0) {
        temp = Color % 13;
        Color /= 13;
        if (temp > 9) {
            color[cnt--] = temp - 10 + 'A';
        } else {
            color[cnt--] = temp + '0';
        }

    }
    if (cnt >= 0) {
        for (int i = 0; i <= cnt; ++i) {
            color[i] = '0';
        }
    }
}

int main(void) {

    scanf("%d %d %d", &Red, &Green, &Blue);

    turnToRadix13(Red, red);
    turnToRadix13(Green, green);
    turnToRadix13(Blue, blue);

    printf("#%s%s%s", red, green, blue);


    return 0;
}

