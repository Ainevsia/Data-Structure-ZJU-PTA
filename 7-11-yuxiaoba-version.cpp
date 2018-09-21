//
// Created by xuzhp on 2018/9/21.
//

#include <iostream>
#define maxvertex 105
#define inf 10000

using namespace std;

int graph[maxvertex][maxvertex];
int earlytime[maxvertex];
int latetime[maxvertex];
int indegree[maxvertex];
int outdegree[maxvertex];
int nv, ne;

void init();
int FindMin(int a, int b);
int FindMax(int a, int b);
int EarlyTime();
void LateTime(int maxtime);

int main() {
    freopen("D:\\SJTU\\Freshman Summer\\DS\\test.txt", "r", stdin);
    cin >> nv >> ne;
    init();
    int time = EarlyTime();
    if (time<0) {cout << 0;return 0;}
    cout << time << endl;
    LateTime(time);
    for (int i = 0; i < nv; ++i) {
        if (earlytime[i]!=latetime[i]) continue;
        for (int j = nv - 1; j>= 0; --j) {
            if (graph[i][j]>=0 && earlytime[j]==latetime[j] && earlytime[i] + graph[i][j] == earlytime[j])
                cout << i + 1 << "->" << j + 1 << endl;
        }
    }
    return 0;
}

void init() {
    for (int i = 0; i < nv; ++i) {
        for (int j = 0; j < nv; ++j) {
            graph[i][j] = -1;
        }
        earlytime[i] = 0;
        latetime[i] = inf;
        indegree[i] = 0;
        outdegree[i] = 0;
    }
    int src, dest, cost;
    for (int k = 0; k < ne; ++k) {
        cin >> src >> dest >> cost;
        graph[src-1][dest-1] = cost;
        indegree[dest-1]++;
        outdegree[src-1]++;
    }
}

int EarlyTime() {
    int queue[nv];
    int first = -1, rear = -1, cnt = 0, temp, maxtime = -1;
    for (int i = 0; i < nv; ++i) if (indegree[i]==0) queue[++rear] = i;
    while (first < rear) {
        temp = queue[++first];
        cnt++;
        for (int i = 0; i < nv; ++i) {
            if (graph[temp][i] >= 0) { // for every node of i
                earlytime[i] = FindMax(earlytime[i],graph[temp][i]+earlytime[temp]);
                maxtime = FindMax(earlytime[i],maxtime);
                if (--indegree[i]==0) queue[++rear] = i;
            }
        }
    }
    if (cnt!=nv) return -1;
    else return maxtime;
}

void LateTime(int maxtime) {
    int queue[nv];
    int first = -1, rear = -1, temp;
    for (int i = 0; i < nv; ++i) {
        if (outdegree[i]==0) {
            queue[++rear] = i;
            latetime[i] = maxtime;
        }
    }
    while (first < rear) {
        temp = queue[++first];
        for (int i = 0; i < nv; ++i) {
            if (graph[i][temp] >= 0) { // for every node of i
                latetime[i] = FindMin(latetime[i],latetime[temp]-graph[i][temp]);
                if (--outdegree[i]==0) queue[++rear] = i;
            }
        }
    }

}

int FindMin(int a, int b) {
    if (a>b) return b;
    else return a;
}

int FindMax(int a, int b) {
    if (a<b) return b;
    else return a;
}