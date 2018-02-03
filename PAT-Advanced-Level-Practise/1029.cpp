/**
    2018.2.3
    Donald
*/
//1029. Median (25)

/**


    12 13 14 15
*/


#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<set>
#include<iostream>
using namespace std;
#define MAXN 1000005

int N1, N2;
long seq1[MAXN];
long seq2[MAXN];

int main(void) {

    scanf("%d", &N1);
    for (int i = 1; i <= N1; ++i) {
        scanf("%lld", &seq1[i]);
    }

    scanf("%d", &N2);
    for (int i = 1; i <= N2; ++i) {
        scanf("%lld", &seq2[i]);
    }

    int seqMedianIndex1 = ceil(N1 * 1.0 / 2);
    int seqMedianIndex2 = ceil(N2 * 1.0 / 2);

    long seqMedianNum1 = seq1[seqMedianIndex1];
    long seqMedianNum2 = seq2[seqMedianIndex2];

    long *Seq1 = seq1;
    long *Seq2 = seq2;

    if (seqMedianNum1 > seqMedianNum2) {
        long *tempSeq = Seq1;
        Seq1 = seq2;
        Seq2 = tempSeq;
        int temp = N1;
        N1 = N2;
        N2 = temp;
        temp = seqMedianNum1;
        seqMedianNum1 = seqMedianNum2;
        seqMedianNum2 = temp;

    } else if (seqMedianNum1 == seqMedianNum2) {
        printf("%ld", seqMedianNum1);
        return 0;
    }

    set<long> Set;
    for (int i = 1; i <= N1; ++i) {
        if (Seq1[i] < seqMedianNum2 && Seq1[i] >= seqMedianNum1) {
            Set.insert(Seq1[i]);
        }
    }

    for (int i = 1; i <= N2; ++i) {
        if (Seq2[i] < seqMedianNum2 && Seq2[i] >= seqMedianNum1) {
            Set.insert(Seq2[i]);
        }
    }

    int index = ceil(Set.size() * 1.0 / 2);

    int cnt = 1;
    for (set<long>::iterator it = Set.begin(); it != Set.end(); ++it) {
        if (cnt++ == index) {
            printf("%ld", *it);
        }
    }

    return 0;
}

