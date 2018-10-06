#include <iostream>
#include <cstring>
#define max 6999
char c[max] = {0};
int f[max] = {0};

using namespace std;

struct node {
    int freq;
    node * left;
    node * right;
};

struct MinHeap {
    node * h[max];
    int cap;
};

void insert(MinHeap * heap, node * fnode) {
    int i = ++heap->cap;
    while (heap->h[i/2]->freq > fnode->freq) {
        heap->h[i] = heap->h[i/2];
        i /= 2;
    }
    heap->h[i] = fnode;
//    cout << "inserting " << fnode->freq << endl;
}

node * pop(MinHeap * heap) {
    node * ret = heap->h[1];
    heap->h[1] = heap->h[heap->cap--];
    bool btl, btr;
    int i = 1;
    while (true) {
        if (i * 2 > heap->cap) break;
        if (i * 2 + 1 > heap->cap) {
            btl = heap->h[i]->freq > heap->h[i * 2]->freq;
            if (btl) {
                node * tmp = heap->h[i];
                heap->h[i] = heap->h[i*2];
                heap->h[i*2] = tmp;
            }
            break;
        }
        btl = heap->h[i]->freq > heap->h[i * 2]->freq;
        btr = heap->h[i]->freq > heap->h[i * 2 + 1]->freq;
        if (btl && btr) {
            if (heap->h[i*2]->freq - heap->h[i*2+1]->freq > 0) {
                btl = false;
            }else btr = false;
        }
        if (btl && !btr) {
            node * tmp = heap->h[i];
            heap->h[i] = heap->h[i*2];
            heap->h[i*2] = tmp;
            i *= 2;
        }else if (!btl && btr) {
            node * tmp = heap->h[i];
            heap->h[i] = heap->h[i*2+1];
            heap->h[i*2+1] = tmp;
            i = i * 2 + 1;
        }else if (!btl && !btr) {
            break;
        }
    }
//    cout << "poping " << ret->freq << endl;
    return ret;
}

int codelen(node * p, int depth) {
    if (!p->left) return depth * p->freq;
    else return codelen(p->left,depth+1) + codelen(p->right,depth+1);
}

int main(int argc, char const *argv[]) {
    freopen("../test.txt", "r", stdin);
    int n;
    cin >> n;
    MinHeap heap;heap.cap = 0;heap.h[0] = new node;
    heap.h[0]->freq = 0;
    for (int i = 0; i < n; ++i) {
        cin >> c[i] >> f[i];
        node * temp = new node;
        temp->left = temp->right = NULL;temp->freq = f[i];
        insert(&heap,temp);
    }
    while (heap.cap > 1) {
        node * n1 = pop(&heap);
        node * n2 = pop(&heap);
        node * newnode = new node;
        newnode->freq = n1->freq + n2->freq;
        newnode->left = n1;
        newnode->right = n2;
        insert(&heap,newnode);
    }
    int standlen = codelen(heap.h[1],0);
//    cout << standlen;
    int m;cin >> m;
    for (int j = 0; j < m; ++j) {
//        cout << "setting falg true";
        bool flag = true;
        char c, str[max];
        int tree[max*2+1], sum = 0;
        for (int i = 0; i < max*2+1; ++i) {
            tree[i] = -1;
        }
        for (int k = 0; k < n; ++k) {
            cin >> c >> str;
            sum += strlen(str) * f[k];
            if (sum > standlen) {
                flag = false;
                continue;
            }
            char * ptr = str;int i = 1;
            while (*ptr!='\0' && flag) {
                if (*ptr++ == '0') i *= 2;
                else i = i * 2 + 1;
                if (*ptr == '\0') {
                    if (tree[i * 2 + 1] != -1 || tree[i * 2] != -1) flag = false;
                    else if (tree[i]==-1) tree[i] = 1;
                    else if (tree[i]==0 || tree[i]==1) flag = false;
                }else{
                    if (tree[i]==-1) tree[i]=0;
                    if (tree[i]== 1) flag = false;
                }
            }
        }
        switch (flag) {
            case true:
                cout << "Yes" << endl;
                break;
            case false:
                cout << "No" << endl;
                break;
        }
    }
    return 0;
}