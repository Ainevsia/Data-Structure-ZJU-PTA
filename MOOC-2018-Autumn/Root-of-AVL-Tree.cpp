#include <iostream>

using namespace std;

struct node {
    int key;
    int left;
    int right;
    int parent;
    int index;
    int factor;
};

node * init (int n);

int main(int argc, char const *argv[]) {
    freopen("D:\\SJTU\\Freshman Summer\\DS\\test.txt", "r", stdin);
    int n;cin >> n;
    node * tree = init(n), * ptr = NULL;
    for (size_t i = 0; i < n; i++) {
        cin >> tree[i].key;
        ptr = &tree[0];
        while (ptr->left!=-1 || ptr->right!=-1) {
            if (tree[i].key<ptr->key && ptr->left!=-1) {
                ptr = &tree[ptr->left];
            }else if (tree[i].key>ptr->key && ptr->right!=-1) {
                ptr = &tree[ptr->right];
            }else{
                break;
            }
        }
        tree[i].parent = ptr->index;
        if (tree[i].key<ptr->key) {
            ptr->left = i;
            ptr->factor++;

        }else if (tree[i].key>ptr->key) {
            ptr->right = i;
        }
    }

    for (size_t i = 0; i < n; i++) {
        printf("index=%d, key=%d, left=%d, right=%d, parent=%d\n",
        tree[i].index, tree[i].key, tree[i].left,
        tree[i].right, tree[i].parent);
    }
    delete [] tree;
    return 0;
}

node * init (int n)
{
    node * tree = new node [n];
    for (size_t i = 0; i < n; i++) {
        tree[i].parent  = -1;
        tree[i].left    = -1;
        tree[i].right   = -1;
        tree[i].index   = i;
        tree[i].factor  = 0;
    }
    return tree;
}
