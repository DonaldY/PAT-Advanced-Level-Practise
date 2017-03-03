
/**
    2017.3.1
    Donald
*/

//1004. Counting Leaves (30)
/**
    题意：每一层有几个叶子节点
    思路：
    用一数组维护记录每层层数，
    递归实现
*/

#include<cstdio>
#include<vector>
#include<map>
using namespace std;
#define MAXN 101

int N, M, K;
int levelLeaves[MAXN];              //记录每一层节点数
map<int , vector<int> > nodeMap;    //对应编号的节点有几个子节点


void dfs(int nodeId, int level){
    if(nodeMap[nodeId].empty()){
        levelLeaves[level] ++;
        return ;
    }
    vector<int>::iterator it = nodeMap[nodeId].begin();
    for (; it != nodeMap[nodeId].end(); ++it){
        dfs(*it, level + 1);
    }
}
int main(void){
    int id, childID;
    scanf("%d%d", &N, &M);
    for(int i = 0; i < M; ++i){
        scanf("%d%d", &id, &K);
        while(K--){
            scanf("%d", &childID);
            nodeMap[id].push_back(childID);
        }
    }
    dfs(1, 0);
    printf("%d", levelLeaves[0]);
    int cnt = levelLeaves[0];
    int leaves = N - M;         //叶节点数 = 总节点数 - 非叶节点数
    for(int i = 1;  cnt < leaves; ++i){
        printf(" %d", levelLeaves[i]);
        cnt += levelLeaves[i];
    }
    return 0;
}
