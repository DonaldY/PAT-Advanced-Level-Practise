/**
    2018.2.2
    Donald
*/
//1028. List Sorting (25)

/**
    1. C == 1
        根据学号排序(升序)
    2. C == 2
        根据名字(升序)
    3. C == 3
        根据分数(升序)

    若有相同，则根据学号升序
*/


#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define MAXN 100005

struct Student {
    int id;
    char name[9];
    int score;
};

int N;
int C;
Student stu[MAXN];

bool compare1(Student a, Student b) {
    return a.id < b.id;
}

bool compare2(Student a, Student b) {
    return strcmp(a.name, b.name) != 0 ? strcmp(a.name, b.name) < 0 : a.id < b.id;
}

bool compare3(Student a, Student b) {
    return a.score != b.score ? a.score < b.score : a.id < b.id;
}

int main(void) {

    while (scanf("%d %d", &N, &C) == 2) {
        for (int i = 0; i < N; ++i) {
            scanf("%d %s %d", &stu[i].id, stu[i].name, &stu[i].score);
        }

        if (C == 1) {
            sort(stu, stu + N, compare1);
        } else if (C == 2) {
            sort(stu, stu + N, compare2);
        } else if (C == 3) {
            sort(stu, stu + N, compare3);
        }
        for (int i = 0; i < N; ++i) {
            printf("%06d %s %d\n", stu[i].id, stu[i].name, stu[i].score);
        }
    }


    return 0;
}

