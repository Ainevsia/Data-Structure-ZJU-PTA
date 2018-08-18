#include <iostream>
#define inf 10000

using namespace std;

int ** readGraph(int n, int m, int *** cost);
void deleteGraph(int ** G, int n, int ** cost);
void Floyd(int ** G, int n, int ** cost);

int main(int argc, char const *argv[]) {
    freopen("D:\\SJTU\\Freshman Summer\\DS\\test.txt", "r", stdin);
    int n, m, s, d, ** cost = NULL;
    cin >> n >> m >> s >> d;
    int ** G = readGraph(n,m,&cost);
    Floyd(G,n,cost);
    int length = G[s][d];
    int fee = cost[s][d];
    cout << length << ' ' << fee;
    deleteGraph(G,n,cost);
    return 0;
}

void Floyd(int ** G, int n, int ** cost) {
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (G[i][j] > G[i][k]+G[k][j]) {
                    G[i][j] = G[i][k] + G[k][j];
                    cost[i][j] = cost[i][k] + cost[k][j];
                }
                else if (G[i][j] == G[i][k]+G[k][j]) {
                    if (cost[i][j] > cost[i][k] + cost[k][j]) {
                        cost[i][j] = cost[i][k] + cost[k][j];
                    }
                }
            }
        }
    }
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
