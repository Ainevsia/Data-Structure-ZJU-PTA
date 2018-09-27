#include <iostream>

using namespace std;

struct node {
    int key;
    node * left;
    node * right;
    int height;
};

node * insert(node * ptr, int x);
int max(int a, int b);
int getHeight(node * ptr);

int main(int argc, char const *argv[]) {
    freopen("D:\\SJTU\\Freshman Summer\\DS\\test.txt", "r", stdin);
    int n, x;cin >> n;
    node * tree = NULL;
    for (int i = 0; i < n; i++) {
        cin >> x;
        tree = insert(tree,x);
    }
    cout << tree->key;
    return 0;
}

node * SingleLeftRotation(node * a) {
    node * b = a->left;
    a->left = b->right;
    b->right = a;
    a->height = max(getHeight(a->left),getHeight(a->right)) + 1;
    b->height = max(getHeight(b->left),getHeight(b->right)) + 1;
    return b;
}

node * SingleRightRotation(node * a) {
    node * b = a->right;
    a->right = b->left;
    b->left = a;
    a->height = max(getHeight(a->left),getHeight(a->right)) + 1;
    b->height = max(getHeight(b->left),getHeight(b->right)) + 1;
    return b;
}

node * LeftRightRotation(node * a) {
    a->left = SingleRightRotation(a->left);
    return SingleLeftRotation(a);
}

node * RightLeftRotation(node * a) {
    a->right = SingleLeftRotation(a->right);
    return SingleRightRotation(a);
}

node * insert(node * ptr, int x) {
    if (!ptr) {
        ptr = new node;
        ptr->key = x;
        ptr->left = ptr->right = NULL;
        ptr->height = 0;
    }else if(ptr->key<x) {
        ptr->right = insert(ptr->right,x);
        if (getHeight(ptr->left)-getHeight(ptr->right) == -2) {
            if (x>ptr->right->key) {
                ptr = SingleRightRotation(ptr);
            }else{
                ptr = RightLeftRotation(ptr);
            }
        }
    }else if(ptr->key>x) {
        ptr->left = insert(ptr->left,x);
        if (getHeight(ptr->left)-getHeight(ptr->right) == 2) {
            if (x<ptr->left->key) {
                ptr = SingleLeftRotation(ptr);
            }else{
                ptr = LeftRightRotation(ptr);
            }
        }
    }
    ptr->height = max( getHeight(ptr->left), getHeight(ptr->right) ) + 1;
    return ptr;
}

int max(int a, int b) {
    return a > b ? a : b;
}

int getHeight(node * ptr) {
    if (!ptr) {
        return 0;
    }else{
        return ptr->height;
    }
}
