#include <iostream>

using namespace std;

struct node {
    int element;
    node * next;
};

struct Queue {
    int * queue;
    int head;
    int tail;
    int size;
};

node * createGraph(int n);
void readGraph(node * G, int e);
void DFSlistComponents(node * G, int n);
void deleteGraph(node * G, int n);
void BFSlistComponents(node * G, int n);

int main(int argc, char const *argv[]) {
    freopen("D:\\SJTU\\Freshman Summer\\DS\\test.txt", "r", stdin);
    int n, e;cin >> n >> e;
    node * G = createGraph(n);
    readGraph(G,e);
    DFSlistComponents(G,n);
    BFSlistComponents(G,n);
    deleteGraph(G,n);
    return 0;
}

int findMin(node * ptr, bool * visited) {
    int min;
	while (ptr->next && visited[ptr->next->element])
	{
		ptr = ptr->next;
	}
    if (ptr->next==NULL) return -1;
    else min = ptr->next->element;
    ptr = ptr->next->next;
    while (ptr) {
        if (ptr->element<min && !visited[ptr->element]) {
            min = ptr->element;
        }
        ptr = ptr->next;
    }
    return min;
}

bool remains(node * ptr, bool * visited) {
    while (ptr->next) {
        if (!visited[ptr->next->element]) {
            return true;
        }
        ptr = ptr->next;
    }
    return false;
}

Queue * creatQueue(int n) {
    Queue * q = new Queue;
    q->size = n;
    q->queue = new int [n];
    q->head = 0;
    q->tail = -1;
    return q;
}

void deleteQueue(Queue * q) {
    delete [] q->queue;
    delete q;
}

void enQueue(Queue * q, int element) {
    q->queue[++q->tail] = element;
}

int deQueue(Queue * q) {
    return q->queue[q->head++];
}

void push(Queue * q, node * ptr, bool * visited) {
    while (remains(ptr,visited)) {
        int min = findMin(ptr,visited);
        if (min==-1) return;
        enQueue(q,min);
        visited[min] = true;
    }
}

void BFSlistComponents(node * G, int n) {
    Queue * q = creatQueue(n);
    bool * visited = new bool [n];
    for (int i = 0; i < n; i++) {
        visited[i] = false;
    }
    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            cout << "{ ";
            enQueue(q,i);
            visited[i] = true;
            while (q->head!=q->tail+1) {
                int popelement = deQueue(q);
                cout << popelement <<" ";
                push(q,&G[popelement],visited);
            }
            cout << '}' << endl;
        }
    }
    delete [] visited;
    deleteQueue(q);
}

void DFS(node * G, int i, bool * visited) {
    while (remains(&G[i],visited)) {
        int min = findMin(&G[i],visited);
        if (min==-1) return;
        cout << min <<" ";
        visited[min] = true;
        DFS(G,min,visited);
    }
}

void DFSlistComponents(node * G, int n) {
    bool * visited = new bool [n];
    for (int i = 0; i < n; i++) {
        visited[i] = false;
    }
    for (int i = 0; i < n; i++) {
        if (visited[i]) continue;
        cout << "{ ";
        if (!visited[i]) {
            cout << i <<" ";
            visited[i] = true;
            DFS(G,i,visited);
        }
        cout << "}" << endl;
    }
    delete [] visited;
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

void insertEdge(node * G, int i, int j) {
    node * ptr = &G[i];
    while (ptr->next) {
        ptr = ptr->next;
    }
    ptr->next = new node;
    ptr = ptr->next;
    ptr->element = j;
    ptr->next = NULL;

    ptr = &G[j];
    while (ptr->next) {
        ptr = ptr->next;
    }
    ptr->next = new node;
    ptr = ptr->next;
    ptr->element = i;
    ptr->next = NULL;
}

void readGraph(node * G, int e) {
    int vi, vj;
    for (int i = 0; i < e; i++) {
        cin >> vi >> vj;
        insertEdge(G, vi, vj);
    }
}

node * createGraph(int n) {
    node * G = new node [n];
    for (int i = 0; i < n; i++) {
        G[i].element = i;
        G[i].next = NULL;
    }
    return G;
}
