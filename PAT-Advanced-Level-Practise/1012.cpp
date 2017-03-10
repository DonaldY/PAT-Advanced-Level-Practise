/**
    2017.3.10
    Donald
*/

//1012. The Best Rank (25)

/**
    题意：
    找到最好成绩，按 A > C > M > E，输出：科目 排名
    如果 不在榜上， 则输出 N / A

    思路：

*/

#include<cstdio>
#include<iostream>
using namespace std;
#define MAXN 2001
struct Student {
    int id;
    int C;
    int M;
    int E;
    int A;
    char subject;
    int bestRank;
};

int N, Mi;
Student student[MAXN];

int main(void) {

    int A, C, M, E, id;
    scanf("%d%d", &N, &Mi);
    for (int i = 0; i < N; ++i) {
        scanf("%d%d%d%d", &id, &C, &M, &E);
        student[i].id = id;
        student[i].C  = C;
        student[i].M  = M;
        student[i].E  = E;
        student[i].A  = (C + M + E) / 3;
    }

    for (int i = 0; i < N; ++i) {
        int Arank = 1, Mrank = 1, Crank = 1, Erank = 1;
        for (int j = 0; j < N; ++j) {
            if (student[i].A < student[j].A)
                Arank ++;
            if (student[i].C < student[j].C)
                Crank ++;
            if (student[i].M < student[j].M)
                Mrank ++;
            if (student[i].E < student[j].E)
                Erank ++;
        }
        student[i].bestRank = Arank;
        student[i].subject = 'A';
        if (Arank > Crank) {
            student[i].bestRank = Crank;
            student[i].subject = 'C';
        }
        if (Crank > Mrank && Arank > Mrank) {
            student[i].bestRank = Mrank;
            student[i].subject = 'M';
        }
        if (Mrank > Erank && Crank > Erank && Arank > Erank) {
            student[i].bestRank = Erank;
            student[i].subject = 'E';
        }
    }
    int flag = 0;
    for (int i = 0 ; i < Mi; ++i) {
        scanf("%d", &id);
        flag = 0;
        for (int j = 0; j < N; ++j) {
            if (student[j].id == id) {
                printf("%d %c\n", student[j].bestRank, student[j].subject);
                flag = 1;
                break;
            }
        }
        if (flag){
            continue;
        }
        printf("N/A\n");
    }
    return 0;
}
