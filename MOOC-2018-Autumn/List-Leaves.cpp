#include <iostream>
#include <cstdlib>

using namespace std;

struct node {
    int data;
    bool leaf;
    unsigned int pos;
    char left;
    char right;
};

int readtree(node * tree, int n, int * num);
void attachweight(node * tree, int ptr, int weight);
void printleaf(node * tree, int n);
int cmp(const void * front, const void * rear);

int main(int argc, char const *argv[]) {
    freopen("D:\\SJTU\\Freshman Summer\\DS\\test.txt", "r", stdin);
    int n;cin >> n;
    node * tree = new node [n];
    int leafnum = 0;
    int head = readtree(tree,n,&leafnum);
    //cout << head;
    attachweight(tree,head,1);
    //cout << "attach done";
    qsort(tree,n,sizeof(node),cmp);
    //cout << "sorted";
    printleaf(tree,leafnum);
    delete [] tree;
    return 0;
}

void printleaf(node * tree, int n) {
    int cnt = 0;
    for (int i = 0; true; i++) {
        if (tree[i].leaf) {
            cout << tree[i].data;
            ++cnt;
            if (cnt!=n) {
                cout << ' ';
            }else return;
        }
    }
}

int cmp(const void * front, const void * rear) {
    int ret = ((node*)front)->pos - ((node*)rear)->pos;
    return ret;
}

void attachweight(node * tree, int ptr, int weight) {
    tree[ptr].pos = weight;
    if (tree[ptr].left!='-') {
        attachweight(tree,tree[ptr].left-'0',2*weight);
    }
    if (tree[ptr].right!='-') {
        attachweight(tree,tree[ptr].right-'0',2*weight+1);
    }
}

int readtree(node * tree, int n, int * num) {
    bool * ishead = new bool [n];
    for (int i = 0; i < n; i++) {
        ishead[i] = true;
    }
    for (int i = 0; i < n; i++) {
        tree[i].data = i;
        tree[i].leaf = true;
        cin >> tree[i].left >> tree[i].right;
        if (tree[i].left!='-') {
            tree[i].leaf = false;
            ishead[tree[i].left-'0'] = false;
        }
        if (tree[i].right!='-') {
            tree[i].leaf = false;
            ishead[tree[i].right-'0'] = false;
        }
        if (tree[i].leaf) {
            (*num)++;
        }
    }
    int head = 0;
    for (int i = 0; i < n; i++) {
        if (ishead[i]==true) {
            head = i;
            break;
        }
    }
    delete [] ishead;
    return head;
}
