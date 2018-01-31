/**
    2018.1.30
    Donald
*/
//1025. PAT Ranking (25)

/**
    根据分数进行排序
    1. 按分数从高到低
    2. 同分数
        若 location_number 和 local_rank 均相等，则同排名
*/


#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

struct RankNode {
    char registration_number[15];
    int final_rank;
    int location_number;
    int local_rank;
    int score;
};

int N;
int k;
int K;  //总数
RankNode List[30005];

bool complare(RankNode a, RankNode b) {
    return a.score != b.score ? a.score > b.score : strcmp(a.registration_number, b.registration_number) < 0;
}

void sortList(RankNode nodeList[], int n) {
    sort(nodeList, nodeList + n, complare);
    int local_rank = 1;
    int score = 101;
    for (int i = 0; i < n; ++i) {
        if (score > nodeList[i].score) {
            local_rank = i + 1;
            score = nodeList[i].score;
        }
        nodeList[i].local_rank = local_rank;
    }
}

void sortAll() {
    sort(List, List + K, complare);

    int score = 101;
    int final_rank = K;
    for (int i = 0; i < K; ++i) {
        if (score > List[i].score) {
            final_rank = i + 1;
            score = List[i].score;
        }
        List[i].final_rank = final_rank;
    }
}

int main(void) {

    int location = 1;

    scanf("%d", &N);

    for (int i = 0 ; i < N; ++i) {
        scanf("%d", &k);

        RankNode nodeList[305];
        for (int j = 0; j < k; ++j) {
            scanf("%s %d", &nodeList[j].registration_number, &nodeList[j].score);
            nodeList[j].location_number = location;
        }
        location ++;
        sortList(nodeList, k);



        for (int j = 0; j < k; ++j) {
            List[j + K] = nodeList[j];
        }
        K += k;
    }

    sortAll();

    printf("%d\n", K);
    for (int j = 0; j < K; ++j) {
        printf("%s %d %d %d\n", List[j].registration_number, List[j].final_rank
               , List[j].location_number, List[j].local_rank);
    }

    return 0;
}

