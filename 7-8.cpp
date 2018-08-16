#include <iostream>
#define inf 10000

using namespace std;

struct node {
    int element;
    int weight;
    node * next;
};

node * createGraph(int n);
void readGraph(node * G, int e);
int Dijkstra(node * G, int n, int s);
void deleteGraph(node * G, int n);

int main(int argc, char const *argv[]) {
    freopen("D:\\SJTU\\Freshman Summer\\DS\\test.txt", "r", stdin);
    int n, m;cin >> n >> m;
    node * G = createGraph(n);
    readGraph(G,m);
    int * shortest = new int [n];
    for (int i = 0; i < n; i++) shortest[i] = -1;    //if cannot reach all
    for (int i = 0; i < n; i++) {
        shortest[i] = Dijkstra(G,n,i);  //return
    }
    int animal = 0, length = inf;
    for (int i = 0; i < n; i++) {
        if (shortest[i]!=-1 && shortest[i]<length) {
            length = shortest[i];
            animal = i + 1;
        }
    }
    if (animal==0) {
        cout << 0;
    }else{
        cout << animal << ' ' << length;
    }
    deleteGraph(G,n);
    delete [] shortest;
    return 0;
}

int Dijkstra(node * G, int n, int s)
{
    int * dist = new int [n];
    int * path = new int [n];
    bool * collected = new bool [n];
    for (int i = 0; i < n; i++) {
        dist[i] = inf;
        path[i] = -1;
        collected[i] = false;
    }
    dist[s] = 0;
    collected[s] = true;
    node * ptr = G[s].next;
    while (ptr) {
        if (!collected[ptr->element]) {
            int w = ptr->element;
            if (dist[s]+ptr->weight<dist[w]) {
                dist[w] = dist[s] + ptr->weight;
                path[w] = s;
            }
        }
        ptr = ptr->next;
    }

    while (true) {
        int min = inf, v = -1;
        for (int i = 0; i < n; i++) {
            if (!collected[i] && dist[i]!=-1 && dist[i]<min) {
                min = dist[i];
                v = i;
            }
        }
        if (min==inf || v<0) break;
        collected[v] = true;
        node * ptr = G[v].next;
        while (ptr) {
            if (!collected[ptr->element]) {
                int w = ptr->element;
                if (dist[v]+ptr->weight<dist[w]) {
                    dist[w] = dist[v] + ptr->weight;
                    path[w] = v;
                }
            }
            ptr = ptr->next;
        }
    }

    int min = -1;
    for (int i = 0; i < n; i++) {
        if (dist[i]==inf) return -1;
        if (dist[i]>min) min = dist[i];
    }
    delete [] dist;
    delete [] path;
    delete [] collected;
    return min;
}

void deleteGraph(node * G, int n) {
    for (int i = 0; i < n; i++) {
        node * ptr = G[i].next;
        while (ptr) {
            node * temp = ptr->next;
            delete ptr;
            ptr = temp;
        }
    }
    delete [] G;
}

void insertEdge(node * G, int i, int j, int weight) {
    node * ptr = &G[i];
    while (ptr->next) {
        ptr = ptr->next;
    }
    ptr->next = new node;
    ptr = ptr->next;
    ptr->element = j;
    ptr->weight = weight;
    ptr->next = NULL;

    ptr = &G[j];
    while (ptr->next) {
        ptr = ptr->next;
    }
    ptr->next = new node;
    ptr = ptr->next;
    ptr->element = i;
    ptr->weight = weight;
    ptr->next = NULL;
}

void readGraph(node * G, int e) {
    int vi, vj, weight;
    for (int i = 0; i < e; i++) {
        cin >> vi >> vj >> weight;
        insertEdge(G, vi-1, vj-1, weight);
    }
}

node * createGraph(int n) {
    node * G = new node [n];
    for (int i = 0; i < n; i++) {
        G[i].element = i;
        G[i].weight = 0;
        G[i].next = NULL;
    }
    return G;
}
