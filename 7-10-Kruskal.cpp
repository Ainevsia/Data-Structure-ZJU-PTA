#include <iostream>
#define inf 10000

using namespace std;

struct edge {
    int smallcity;
    int largecity;
    int weight;
};

struct MinHeap {
    edge * elements;
    int size;
    int capacity;
};

int ** makeGraph(int n, int m);
void deleteGraph(int ** G, int n);
edge * createSet(int ** G, int n, int m);
void deleteSet(edge * E);

int main(int argc, char const *argv[]) {
    freopen("D:\\SJTU\\Freshman Summer\\DS\\test.txt", "r", stdin);
    int n, m;cin >> n >> m;
    int ** G = makeGraph(n,m);
    edge * E = createSet(G,n,m);

    deleteGraph(G,n);
    deleteSet(E);
    return 0;
}

edge deleteMin(MinHeap * H) {
    int parent = 1, child;
    edge minitem = H->elements[1], temp = H->elements[H->size--];
    for ( ; parent*2<=H->size; parent=child) {
        child = parent * 2;
        if (child!=H->size && H->elements[child].weight>H->elements[child+1].weight) {
            child++;
        }
        if (temp.weight>=H->elements[child].weight) {
            H->elements[parent] = H->elements[child];
        }else break;
    }
    H->elements[parent] = temp;
    return minitem;
}

void Insert(MinHeap * H, edge item) {
    int i = ++H->size;
    for ( ; H->elements[i/2].weight>item.weight; i/=2) {
        H->elements[i] = H->elements[i/2];
    }
    H->elements[i] = item;
}

MinHeap * creatHeap(edge * E, int m) {
    MinHeap * H = new MinHeap;
    H->elements = new edge [m+1];
    H->size = 0;
    H->capacity = m;
    H->elements[0].weight = inf;

    for (int i = 0; i < m; i++) {
        Insert(H,E[i]);
    }
    return H;
}

int Kruskal(int n, int m, edge * E) {
    edge * MST = new edge [n-1];
    int cntMST = 0, cntEdge = m, sum = 0;
    MinHeap * H = creatHeap(E,m);
    while (cntMST<n-1 && cntEdge) {
        deleteMin(H);
    }


    delete [] MST;
    return sum;
}

void deleteSet(edge * E) {
    delete [] E;
}

edge * createSet(int ** G, int n, int m) {
    edge * E = new edge [m];
    int cnt = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i+1; j < n; j++) {
            if (G[i][j]!=inf) {
                E[cnt].smallcity = i;
                E[cnt].largecity = j;
                E[cnt].weight = G[i][j];
                cnt++;
            }
        }
    }
    return E;
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
