
/**
    2017.3.1
    Donald
*/

//1004. Counting Leaves (30)
/**
    ���⣺ÿһ���м���Ҷ�ӽڵ�
    ˼·��
    ��һ����ά����¼ÿ�������
    �ݹ�ʵ��
*/

#include<cstdio>
#include<vector>
#include<map>
using namespace std;
#define MAXN 101

int N, M, K;
int levelLeaves[MAXN];              //��¼ÿһ��ڵ���
map<int , vector<int> > nodeMap;    //��Ӧ��ŵĽڵ��м����ӽڵ�


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
    int leaves = N - M;         //Ҷ�ڵ��� = �ܽڵ��� - ��Ҷ�ڵ���
    for(int i = 1;  cnt < leaves; ++i){
        printf(" %d", levelLeaves[i]);
        cnt += levelLeaves[i];
    }
    return 0;
}
