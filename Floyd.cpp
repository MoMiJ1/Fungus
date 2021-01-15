#include<bits/stdc++.h>
#include<algorithm>
using namespace std;

/*
原理：
    如果有一个点 K ，使得  i-->K-->j 的距离小于 i-->j 的距离
    则：用点 K作为点(i,j)的中介点

伪代码：
    void Floyd() {
        枚举顶点 K：
            以 K作为中介点，枚举顶点 i，j：
                if (dist[i][k] + dist[k][j] < dist[i][j])
                {
                    dist[i][j] = dist[i][k] + dist[k][j]
                }
    }
*/

const int MAX = 200;
int n, m;
int dist[MAX][MAX]; // 默认为 INT_MAX

// 算法
void Floyd() {
    for (int k = 0; k < n; k++)
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                if(dist[i][k] != INT_MAX && dist[k][j] != INT_MAX && dist[i][k]+dist[k][j]<dist[i][j])
                    dist[i][j] = dist[i][k] + dist[k][j];
}

int main() {
    int x,y,w;
    fill(dist[0],dist[0]+MAX*MAX,INT_MAX);
    scanf("%d%d",&n,&m); // 顶点数与边数
    for (int i = 0; i < n; i++){ 
        // 点到自己的距离为 0
        dist[i][i] = 0;
    }
    for (int i = 0; i < m; i++)
    {
        // 输入边的权重与边的两顶点
        scanf("%d%d%d",&x,&y,&w);
        dist[x][y] = w;
    }
    Floyd();
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            if (dist[i][j] != INT_MAX)
                printf("%d--%d = %d\n",i,j,dist[i][j]);
        }
        // printf("\n");
    }  
    return 0;
}


