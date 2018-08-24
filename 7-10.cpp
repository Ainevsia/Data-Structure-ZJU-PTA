#include <iostream>
#define inf 10000

using namespace std;

int ** makeGraph(int n, int m);
void deleteGraph(int ** G, int n);
int Prim(int ** G, int n);

int main(int argc, char const *argv[]) {
    freopen("D:\\SJTU\\Freshman Summer\\DS\\test.txt", "r", stdin);
    int n, m;cin >> n >> m;
    int ** G = makeGraph(n,m);
    cout << Prim(G,n);
    deleteGraph(G,n);
    return 0;
}

int Prim(int ** G, int n) {
    bool * collected = new bool [n];
    int * dist = new int [n], mincost = 0;
    for (int i = 0; i < n; i++) {
        collected[i] = false;
        dist[i] = inf;
    }
    collected[0] = true;
    dist[0] = 0;
    for (int i = 1; i < n; i++) {
        if (G[0][i]<dist[i]) {
            dist[i] = G[0][i];
        }
    }
    while (true) {
        bool found = false;
        int min = inf, v = 0;
        for (int i = 1; i < n; i++) {
            if (!collected[i] && dist[i]<min) {
                found = true;
                min = dist[i];
                v = i;
            }
        }
        if (!found) {
            break;
        }
        mincost += min;
        collected[v] = true;
        dist[v] = 0;
        // for every node w linking to the node v
        for (int w = 0; w < n; w++) {
            if (G[v][w]!=inf && !collected[w]) {
                if (G[v][w] < dist[w]) {
                    dist[w] = G[v][w];
                }
            }
        }

    }

    for (int i = 0; i < n; i++) {
        if (collected[i]==false) {
            return -1;
        }
    }
    return mincost;
}

void deleteGraph(int ** G, int n) {
    for (int i = 0; i < n; i++) {
        delete [] G[i];
    }
    delete [] G;
}

int ** makeGraph(int n, int m) {
    int ** G = new int* [n];
    for (int i = 0; i < n; i++) {
        G[i] = new int [n];
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            G[i][j] = inf;
        }
    }
    int city1, city2, cost;
    for (int i = 0; i < m; i++) {
        cin >> city1 >> city2 >> cost;
        G[city1-1][city2-1] = cost;
        G[city2-1][city1-1] = cost;
    }
    return G;
}
