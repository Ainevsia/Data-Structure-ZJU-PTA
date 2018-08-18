#include <iostream>
#define inf 10000

using namespace std;

int ** readGraph(int n, int m, int *** cost);
void deleteGraph(int ** G, int n, int ** cost);
int Dijkstra(int** G,int n,int s,int d,int** cost,int *spend);

int main(int argc, char const *argv[]) {
    freopen("D:\\SJTU\\Freshman Summer\\DS\\test.txt", "r", stdin);
    int n, m, s, d, ** cost = NULL, fee;
    cin >> n >> m >> s >> d;
    int ** G = readGraph(n,m,&cost);

    int length = Dijkstra(G,n,s,d,cost,&fee);
    cout << length << ' ' << fee;
    deleteGraph(G,n,cost);
    return 0;
}

int Dijkstra(int** G,int n,int s,int d,int** cost,int *spend)
{
    int * dist = new int [n];
    int * fee = new int [n];
    bool * collected = new bool [n];
    for (int i = 0; i < n; i++) {
        dist[i] = inf;
        fee[i] = inf;
        collected[i] = false;
    }
    dist[s] = 0;
    collected[s] = true;

    for (int i = 0; i < n; i++) {
        if(!collected[i] && G[s][i]!=inf) {
            dist[i] = G[s][i];
            fee[i] = cost[s][i];
        }
    }
    int v = -1;
    while (true) {
        int min = inf;
        v = -1;
        for (int i = 0; i < n; i++) {
            if (!collected[i] && dist[i]!=-1 && dist[i]<min) {
                min = dist[i];
                v = i;
            }
        }
        if (v==d || v==-1) break;
        collected[v] = true;

        for (int w = 0; w < n; w++) {
            if(!collected[w] && G[v][w]!=inf) {
                if (dist[v]+G[v][w]<dist[w]) {
                    dist[w] = dist[v] + G[v][w];
                    fee[w] = fee[v] + cost[v][w];
                }else if (dist[v]+G[v][w]==dist[w]) {
                    if (fee[w] > fee[v] + cost[v][w]) {
                        fee[w] = fee[v] + cost[v][w];
                    }
                }
            }
        }
    }

    int ret = dist[v];
    *spend = fee[v];
    delete [] dist;
    delete [] fee;
    delete [] collected;
    return ret;
}

void deleteGraph(int ** G, int n, int ** cost) {
    for (int i = 0; i < n; i++) {
        delete [] G[i];
        delete [] cost[i];
    }
    delete [] G;
    delete [] cost;
}

int ** readGraph(int n, int m, int *** cost) {
    int ** G = new int* [n];
    *cost = new int* [n];
    for (int i = 0; i < n; i++) {
        G[i] = new int [n];
        (*cost)[i] = new int [n];
    }
    for (int i = 0; i < n; i++) {
        G[i][i] = 0;
        (*cost)[i][i] = 0;
    }
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < i; j++) {
            G[i][j] = inf;
            G[j][i] = inf;
            (*cost)[i][j] = inf;
            (*cost)[j][i] = inf;
        }
    }

    int city1, city2, length, fee;
    for (int i = 0; i < m; i++) {
        cin >> city1 >> city2 >> length >> fee;
        G[city1][city2] = length;
        G[city2][city1] = length;
        (*cost)[city1][city2] = fee;
        (*cost)[city2][city1] = fee;
    }

    return G;
}
