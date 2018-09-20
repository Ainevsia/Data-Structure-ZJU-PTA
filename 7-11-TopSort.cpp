#include <iostream>

using namespace std;

struct Vertex {
    int index;
    int earliest_finish_time;
    int latest_finish_time;
};

struct Edge {
    int required_time;
    int flexible_time;
};


int main(int argc, char const *argv[]) {
    freopen("D:\\SJTU\\Freshman Summer\\DS\\test.txt", "r", stdin);
    int n, m;cin >> n >> m;
    Edge ** Graph = new Edge * [n];
    Vertex * vertexlist = new Vertex [n];
    int * indegree = new int [n];
    for (int i = 0; i < n; i++) {
        Graph[i] = new Edge [n];
        for (int j = 0; j < n; j++) {
            Graph[i][j].required_time = 0;
            Graph[i][j].flexible_time = 0;
        }
        vertexlist[i].index = i;
        vertexlist[i].earliest_finish_time = 0;
        vertexlist[i].latest_finish_time = 0;
        indegree[i] = 0;
    }
    int src, dest, consume;
    for (int i = 0; i < m; i++) {
        cin >> src >> dest >> consume;
        Graph[src-1][dest-1].required_time = consume;
        indegree[dest-1]++;
    }


    for (int i = 0; i < n; i++) delete [] Graph[i];
    delete [] Graph;
    delete [] vertexlist;
    delete [] indegree;
    return 0;
}

/* 邻接表存储 - 拓扑排序算法 */

bool TopSort( LGraph Graph, Vertex TopOrder[] )
{ /* 对Graph进行拓扑排序,  TopOrder[]顺序存储排序后的顶点下标 */
    int Indegree[MaxVertexNum], cnt;
    Vertex V;
    PtrToAdjVNode W;
       Queue Q = CreateQueue( Graph->Nv );

    /* 初始化Indegree[] */
    for (V=0; V<Graph->Nv; V++)
        Indegree[V] = 0;

    /* 遍历图，得到Indegree[] */
    for (V=0; V<Graph->Nv; V++)
        for (W=Graph->G[V].FirstEdge; W; W=W->Next)
            Indegree[W->AdjV]++; /* 对有向边<V, W->AdjV>累计终点的入度 */

    /* 将所有入度为0的顶点入列 */
    for (V=0; V<Graph->Nv; V++)
        if ( Indegree[V]==0 )
            AddQ(Q, V);

    /* 下面进入拓扑排序 */
    cnt = 0;
    while( !IsEmpty(Q) ){
        V = DeleteQ(Q); /* 弹出一个入度为0的顶点 */
        TopOrder[cnt++] = V; /* 将之存为结果序列的下一个元素 */
        /* 对V的每个邻接点W->AdjV */
        for ( W=Graph->G[V].FirstEdge; W; W=W->Next )
            if ( --Indegree[W->AdjV] == 0 )/* 若删除V使得W->AdjV入度为0 */
                AddQ(Q, W->AdjV); /* 则该顶点入列 */
    } /* while结束*/

    if ( cnt != Graph->Nv )
        return false; /* 说明图中有回路, 返回不成功标志 */
    else
        return true;
}
