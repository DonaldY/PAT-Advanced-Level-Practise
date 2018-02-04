/**
    2018.1.27
    Donald
*/
//1020. Tree Traversals (25)

/**
    找父节点

    从后序中找父节点
    从中序中划分左右子树

*/


#include<cstdio>
#include<cstring>
using namespace std;

int N;
int postArr[31], inOrderArr[31], levelOrderArr[100000];
int cnt;

void init() {

    scanf("%d", &N);

    for (int i = 0; i < N; ++i) {
        scanf("%d", &postArr[i]);
    }

    for (int i = 0; i < N; ++i) {
        scanf("%d", &inOrderArr[i]);
    }
}

void pre(int root, int start, int end, int index) {

    if(start > end) {
        return ;
    }

    int i = start;

    while(i < end && inOrderArr[i] != postArr[root]) {
        i++;
    }

    levelOrderArr[index] = postArr[root];

    pre(root - 1 - end + i, start, i - 1, 2 * index + 1);

    pre(root - 1, i + 1, end, 2 * index + 2);
}

int main(void) {

    init();

    pre(N - 1, 0, N - 1, 0);

    int cnt = 0;

    for(int i = 0; i < sizeof((levelOrderArr)) / sizeof(levelOrderArr)[0]; i++) {
        if (levelOrderArr[i] != 0) {
            if (cnt != 0) printf(" ");
            printf("%d", levelOrderArr[i]);
            cnt++;
        }
        if (cnt == N) break;
    }
    return 0;
}

