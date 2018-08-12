#include <iostream>

using namespace std;

struct node {
    int value;
    node * left;
    node * right;
    int select;
};

node * maketree(int n);
void deletetree(node * tree);
bool treecmp(node * tree, int n);

int main(int argc, char const *argv[]) {
    freopen("D:\\SJTU\\Freshman Summer\\DS\\test.txt", "r", stdin);
    int n;cin >> n;
    while (n) {
        int l;cin >> l;
        node * tree = maketree(n);
        for (int i = 0; i < l; i++) {
            if (treecmp(tree,n))    cout << "Yes" << endl;
            else                    cout << "No"  << endl;
        }
        deletetree(tree);
        cin >> n;
    }
    return 0;
}

bool check(node * tree, int v)
{
    if (!tree) return false;
    if (tree->value==v) {
        tree->select = 1;
        return true;
    }
    if (tree->select==0) {
        return false;
    }
    if (tree->value>v) {
        return check(tree->left,v);
    }else{
        return check(tree->right,v);
    }
}

void settree(node * tree)
{
    if (!tree) return;
    if (tree->left)    settree(tree->left) ;
    if (tree->right)   settree(tree->right);
    tree->select = 0;
}

bool treecmp(node * tree, int n)
{
    settree(tree);
    int v;
    bool ret = true;
    for (int i = 0; i < n; i++) {
        cin >> v;
        if (!check(tree,v)) ret = false;
    }
    return ret;
}

void deletetree(node * tree)
{
    if (!tree) return;
    if (tree->left)    deletetree(tree->left) ;
    if (tree->right)   deletetree(tree->right);
    delete tree;
}

node * newnode(int value)
{
    node * treenode = new node;
    treenode->left      = NULL  ;
    treenode->right     = NULL  ;
    treenode->value     = value ;
    treenode->select    = 0     ;
    return treenode;
}

node * attachnode(node * tree, int value)
{
    if (!tree) {
        return newnode(value);
    }else{
        if (tree->value>value)
                tree->left = attachnode(tree->left ,value);
        else    tree->right= attachnode(tree->right,value);
        return tree;
    }
}

node * maketree(int n)
{
    int value;
    node * tree = NULL;
    for (int i = 0; i < n; i++) {
        cin >> value;
        tree = attachnode(tree,value);
    }
    return tree;
}
