#include<bits/stdc++.h>
using namespace std;
#define MAX 500

/* dijkstra 计算最短距离的伪代码

#define MAX 500
int Graph[MAX][MAX];
int dist[MAX];  
bool visit[MAX];

void dijkstra(int start)
{
    初始化dist          (1)                            
    for(循环n次) 
    {
        u = dist[MAX]中最小且没被访问过的顶点   (2)
        visit[u] = true
        for(从u出发能到达的所有顶点k)   (3)
        {
            if(k没被访问过 && 以u为中转点的start-->k的距离比dist[k]小)   (4)
            {
                更新dist[k]    (5)
            }
        }
    }
}
*/

int Graph[MAX][MAX];
int dist[MAX];
bool visit[MAX];

void dijkstra_1(int start){ // dijkstra计算最短距离

    // （1）. 初始化dist
    fill(dist,dist+MAX,INT_MAX); 
    dist[start] = 0;

    // （2）.找到dist[]中最小且没被访问过的点

    for(int i = 0; i < MAX;i++)
    {
        int u = -1, minDist = INT_MIN;
        for(int j = 0;j < MAX;j++)
        {
            if(!visit[j] && dist[j]<minDist)
            {
                u = j;
                minDist = dist[j];
            }
        }
    
        // （3）. 如果找不到更小的dist[]，说明不连通，如果找到，则标记visit[u]为true
        if(u == -1) return;
        visit[u] = true;

        // （4）. 遍历从u能到达的所有点并更新dist[]
        for(int k = 0;k < MAX;k++)
        {
            // k没被访问过 && u与k之间是连通的  &&  “起点-->u-->k”的距离比现有的“起点-->k”更短
            if(!visit[k] && Graph[u][k]!=INT_MAX && dist[u] + Graph[u][k] < dist[k])
            {
                dist[k] = dist[u] + Graph[u][k];
            }
        }
    }
}


/* 修改： dijkstra 解最短路径

需要增添一个 preNode[MAX],记录点k的前驱
代码上只需要在第一部分伪代码的序号（5）后面增加一条：

    "令k的前驱为u"    (6)

void dijkstra(int start)
{
    初始化dist          (1)                            
    for(循环n次) 
    {
        u = dist[MAX]中最小且没被访问过的顶点   (2)
        visit[u] = true
        for(从u出发能到达的所有顶点k)   (3)
        {
            if(k没被访问过 && 以u为中转点的start-->k的距离比dist[k]小)   (4)
            {
                更新dist[k]    (5)
                令k的前驱为u    (6)
            }
        }
    }
}

但是preNode中得到的是每个顶点的直接前驱，想要得到完整的最短路径，需要用 DFS不断递归寻找前驱，直到到达 start

*/

int preNode[MAX];

void dijkstra_2(int start)
{
    // （1）初始化 dist[] 和 preNode[]
    fill(dist,dist+MAX,INT_MAX);
    dist[start] = 0;
    for(int i = 0;i < MAX;i++) preNode[i] = i;

    // （2）.找到dist[]中最小且没被访问过的点
    for(int i = 0; i < MAX;i++)
    {
        int u = -1, minDist = INT_MIN;
        for(int j = 0;j < MAX;j++)
        {
            if(!visit[j] && dist[j]<minDist)
            {
                u = j;
                minDist = dist[j];
            }
        }
    
        // （3）. 如果找不到更小的dist[]，说明不连通，如果找到，则标记visit[u]为true
        if(u == -1) return;
        visit[u] = true;

        // （4）. 遍历从u能到达的所有点并更新dist[]
        for(int k = 0;k < MAX;k++)
        {
            // k没被访问过 && u与k之间是连通的  &&  “起点-->u-->k”的距离比现有的“起点-->k”更短
            if(!visit[k] && Graph[u][k]!=INT_MAX && dist[u] + Graph[u][k] < dist[k])
            {
                dist[k] = dist[u] + Graph[u][k];
                preNode[k] = u;   // 更新前驱
            }
        } 
    }       
}


/* 附加条件：如果对每条边增加一个边权(额外开销)，求在最短路径有多少条时要求路径上的花费之和最大/小

新增一个开销矩阵 Cost[MAX][MAX]
并对第一段伪代码的序号 （3）修改
*/

int C[MAX][MAX];
int cost[MAX];

void dijkstra_3(int start)
{
    // （1）初始化 dist[] 
    fill(dist,dist+MAX,INT_MAX);
    dist[start] = 0;

    // （2）.找到dist[]中最小且没被访问过的点
    for(int i = 0; i < MAX;i++)
    {
        int u = -1, minDist = INT_MIN;
        for(int j = 0;j < MAX;j++)
        {
            if(!visit[j] && dist[j]<minDist)
            {
                u = j;
                minDist = dist[j];
            }
        }
    
        // （3）. 如果找不到更小的dist[]，说明不连通，如果找到，则标记 visit[u]为 true
        if(u == -1) return;
        visit[u] = true;

        // （4）.在更新 dist[] 的同时，更新 cost[]
        for(int k = 0;k < MAX;k++)
        {
            if(!visit[k] && Graph[u][k] != INT_MAX)
            {
                if(dist[u] + Graph[u][k] < dist[k])   // 先找最短距离
                {
                    dist[k] = dist[u] + Graph[u][k];
                    cost[k] = cost[u] + C[u][k];
                } 
                else if(dist[u] + Graph[u][k] == dist[k] && cost[u] + C[u][k] < cost[k]){  // 是最短距离，但开销更小/大
                    cost[k] = cost[u] + C[u][k];
                }
            }
        }
    }
}

/* 附加条件：如果对每个点都增加点权，球最短路径有多条时，要求点权之和最大
与上面的边权类似，依然对（3）修改，增加一个 W[MAX],每次在更新最短距离时更新 weight[]

*/

int W[MAX];
int weight[MAX];

void dijkstra_4(int start)
{
    // （1）初始化 dist[] 
    fill(dist,dist+MAX,INT_MAX);
    dist[start] = 0;

    // （2）.找到dist[]中最小且没被访问过的点
    for(int i = 0; i < MAX;i++)
    {
        int u = -1, minDist = INT_MIN;
        for(int j = 0;j < MAX;j++)
        {
            if(!visit[j] && dist[j]<minDist)
            {
                u = j;
                minDist = dist[j];
            }
        }
    
        // （3）. 如果找不到更小的dist[]，说明不连通，如果找到，则标记 visit[u]为 true
        if(u == -1) return;
        visit[u] = true;

        // （4）.在更新 dist[] 的同时，更新 cost[]
        for(int k = 0;k < MAX;k++)
        {
            if(!visit[k] && Graph[u][k] != INT_MAX)
            {
                if(dist[u] + Graph[u][k] < dist[k])   // 先找最短距离
                {
                    dist[k] = dist[u] + Graph[u][k];
                    weight[k] = weight[u] + W[k];
                } 
                else if(dist[u] + Graph[u][k] == dist[k] && weight[u] + W[k] < weight[k]){  // 是最短距离，但开销更小/大
                    weight[k] = weight[u] + W[k];
                }
            }
        } 
    }   
}

/* 附加： 当最短路径不止一条，求最短路径条数
增加一个记录 start-->u 的最短路径条数的数组  roadNum[MAX]
初始条件下，roadNum[start]=1,其它为0；
每次更新最短距离时，令 roadNum[k]继承 roadNum[u]；
当最短距离相同，将 roadNum[u] 加到 roadNum[k]上

修改的位置依旧是  （3）

*/

int roadNum[MAX];

void dijkstra_5(int start)
{
    // （1）初始化 dist[] ，roadNum[]
    fill(dist,dist+MAX,INT_MAX);
    fill(roadNum,roadNum+MAX,0);
    dist[start] = 0;
    roadNum[start] = 1;


    // （2）.找到dist[]中最小且没被访问过的点
    for(int i = 0; i < MAX;i++)
    {
        int u = -1, minDist = INT_MIN;
        for(int j = 0;j < MAX;j++)
        {
            if(!visit[j] && dist[j]<minDist)
            {
                u = j;
                minDist = dist[j];
            }
        }
    

        // （3）. 如果找不到更小的dist[]，说明不连通，如果找到，则标记 visit[u]为 true
        if(u == -1) return;
        visit[u] = true;

        // （4）.在判定计算最短距离后更新最短路径条数
        for(int k = 0;k < MAX;k++)
        {
            if(!visit[k] && Graph[u][k] != INT_MAX)
            {
                if(dist[u] + Graph[u][k] < dist[k])
                {
                    dist[k] = dist[u] + Graph[u][k];
                    roadNum[k] = roadNum[u];
                }
                else if(dist[u] + Graph[u][k] == dist[k])
                {
                    roadNum[k] = roadNum[k] + roadNum[u];
                }
            }
        }
    }
}
