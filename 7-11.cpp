#include <iostream>
#define inf 10000

using namespace std;

struct node {
    int index;
    node * next;
};

node * Prim(int ** Graph, int n);

int main(int argc, char const *argv[]) {
    freopen("D:\\SJTU\\Freshman Summer\\DS\\test.txt", "r", stdin);
    int n, m;cin >> n >> m;
    int ** Graph = new int * [n];
    for (int i = 0; i < n; i++) {
        Graph[i] = new int [n];
        for (int j = 0; j < n; j++) {
            Graph[i][j] = inf;
        }
    }
    int src, dest, consume;
    for (int i = 0; i < m; i++) {
        cin >> src >> dest >> consume;
        Graph[src-1][dest-1] = consume;
    }
    node * header = Prim(Graph,n);
    if (!header->index) {
        cout << 0;
    }else{
        cout << header->index << endl;
        node * ptr = header->next;
        while (ptr->next) {
            src = ptr->index + 1;
            dest = ptr->next->index + 1;
            cout << src << "->" << dest << endl;
            ptr = ptr->next;
        }
    }
    for (int i = 0; i < n; i++) {
        delete [] Graph[i];
    }
    delete [] Graph;
    return 0;
}

node * Prim(int ** Graph, int n) {
    node * header = new node;
    header->index = 0;header->next = new node;
    node * ptr = header->next;
    ptr->index = 0;ptr->next = NULL;
    int * dist = new int [n];
    bool * collected = new bool [n];
    for (int i = 1; i < n; i++) {
        dist[i] = inf;
        collected[i] = false;
    }
    dist[0] = 0;
    collected[0] = true;
    for (int i = 0; i < n; i++) {
        if (Graph[0][i]!=inf) dist[i] = Graph[0][i];
    }
    while (true) {
        int min = inf, v = -1;
        for (int i = 0; i < n; i++) {
            if (!collected[i] && dist[i]<min) {
                v = i;
                min = dist[i];
            }
        }
        if (min==inf) break;
        collected[v] = true;
        header->index += dist[v];
        dist[v] = 0;
        ptr->next = new node;ptr = ptr->next;
        ptr->index = v;ptr->next = NULL;
        for (int i = 0; i < n; i++) {
            if (!collected[i] && Graph[v][i]<dist[i]) {
                dist[i] = Graph[v][i];
            }
            if (dist[n-1]!=inf) {
                header->index += dist[n-1];
                ptr->next = new node;ptr = ptr->next;
                ptr->index = n-1;ptr->next = NULL;
                return header;
            }
        }
    }
    if (!collected[n-1]) header->index = 0;
    delete [] dist;
    delete [] collected;
    return header;
}
