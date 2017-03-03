/**
    2017.2.28
    Donald
*/

/**
    思路：
    2: 0 -> 2有多少不同最短的路径;
    4: 这路径中救援队最多;
    dfs
*/

#include<cstdio>
#include<cstring>
using namespace std;
#define MAXN 505
#define INF 100000000
int pic[MAXN][MAXN];
int flag[MAXN];
int N, M, C1, C2;
int rescueTeam[MAXN];
int cnt;
int Team;
int MinPath = INF;

void dfs(int c, int team, int path){
    if(c == C2){
        if(path < MinPath){
            MinPath = path;
            Team = team;
            cnt = 1;
        }else if(path == MinPath){
            cnt++;
            if(team > Team) Team = team;
        }
        return ;
    }

    if(path > MinPath)  return ;

    for(int i = 0; i < N; ++i){
        if(pic[c][i] != 0 && flag[i] == 0){
            flag[i] = 1;
            dfs(i, team + rescueTeam[i], path + pic[c][i]);
            flag[i] = 0;
        }
    }

    return ;
}

int main(void){
    int c1, c2, L;
    scanf("%d%d%d%d", &N, &M, &C1, &C2);
    for(int i = 0; i < N; ++i)
        scanf("%d", &rescueTeam[i]);
    for(int i = 0; i < M; ++i){
        scanf("%d%d%d", &c1, &c2, &L);
            pic[c1][c2] = L;
            pic[c2][c1] = L;
    }
    flag[C1] = 1;
    dfs(C1, rescueTeam[C1], 0);
    printf("%d %d", cnt, Team);
    return 0;
}
