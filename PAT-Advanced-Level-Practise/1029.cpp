/**
    2018.2.3
    Donald
*/
//1029. Median (25)

/**
    求中位数。

    把两个序列合并后，求中间即可

    9 10 11 12 13 14 15 16 17

    9个数，中间数 (9 - 1) / 2 == 4; [下标0开始]
*/


#include<cstdio>
#include<vector>
using namespace std;
#define MAXN 1000005

int N1, N2;
long seq1[MAXN];
long seq2[MAXN];
vector<long> Vec;

int main(void) {

    scanf("%d", &N1);
    for (int i = 0; i < N1; ++i) {
        scanf("%ld", &seq1[i]);
    }

    scanf("%d", &N2);
    for (int i = 0; i < N2; ++i) {
        scanf("%ld", &seq2[i]);
    }

    int i = 0, j = 0, k = 0;
    while ( i < N1 && j < N2) {
        if (seq1[i]  == seq2[j]) {
            Vec.push_back(seq1[i++]);
            Vec.push_back(seq2[j++]);
        } else if (seq1[i] < seq2[j]) {
            Vec.push_back(seq1[i++]);
        } else {
            Vec.push_back(seq2[j++]);
        }
    }

    while (i < N1) {
        Vec.push_back(seq1[i++]);
    }

    while (j < N2) {
        Vec.push_back(seq2[j++]);
    }

    printf("%ld", Vec[(Vec.size() - 1) / 2]);

    return 0;
}

