#include <iostream>
#define MAXN 100
using namespace std;

struct Node {
    int index;
    int earliest;
    int latest;
};

struct Edge {
    int src;
    int dst;
    int time;
};

struct EdgePtr {
    int src;    //indegree when as a header
    int time;
    EdgePtr * next;
};

int n, m;
EdgePtr * Graph[MAXN];
Node node[MAXN];
Edge edge[MAXN*(MAXN-1)/2];
Node * queue[MAXN];
int front = 0, rear = -1;

void init();
void test();
int GetIndegree(int index);

int main(int argc, char const *argv[]) {
    freopen("D:\\SJTU\\Freshman Summer\\DS\\test.txt", "r", stdin);
    cin >> n >> m;
    init();
    TopSort();
    return 0;
}

void TopSort() {
    int cnt = 0;
    for (size_t i = 0; i < n; i++) {
        if (GetIndegree(node[i].index)==0) {
            Enqueue(&node);
        }
    }
    while (!IsEmpty()) {
        Node * v = Dequeue();cnt++;
        //do something
        EdgePtr ptr = Graph[v->index]->next;
        while (ptr) {
            if
        }
    }
}

bool IsEmpty() {
    return front == rear + 1;
}

void Enqueue(Node * ptr) {
    queue[++rear] = ptr;
}

Node * Dequeue() {
    return queue[front++];
}

void init() {
    for (int i = 0; i < n; i++) {
        node[i].index = i;
        node[i].earliest = node[i].latest = 0;
        Graph[i] = new EdgePtr;
        Graph[i]->src = 0;   //indegree
        Graph[i]->next = NULL;
    }
    for (int i = 0; i < m; i++) {
        cin >> edge[i].src >> edge[i].dst >> edge[i].time;
    }
    for (int i = m; i < MAXN; i++) {
        edge[i].src = edge[i].dst = edge[i].time = 0;
    }
    for (int i = 0; i < m; i++) {
        /* insest */
        EdgePtr * temp = new EdgePtr, * header = Graph[edge[i].dst];
        temp->src = edge[i].src;
        temp->next = header->next;
        header->next = temp;
        header->src++;
    }
}

void test() {
    for (int i = 0; i < m; i++) {
        cout << Graph[i]->src << endl;
    }
}

int GetIndegree(int index) {
    return Graph[index]->src;
}
