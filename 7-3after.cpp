#include <iostream>
#define max 10
#define null -1
using namespace std;

struct node {
    char element;
    int left;
    int right;
}tree1[max], tree2[max];

int build(node * tree);
bool isomorphic(int r1, int r2);

int main(int argc, char const *argv[]) {
    freopen("D:\\SJTU\\Freshman Summer\\DS\\test.txt", "r", stdin);
    int r1 = 0, r2 = 0;
    r1 = build(tree1);
    r2 = build(tree2);
    if (r1!=-1 && r2!=-1) {
        if (isomorphic(r1,r2)) cout << "Yes";
        else cout << "No";
    }else if (r1==-1 && r2==-1) {
        cout << "Yes";
    }else cout << "No";
    return 0;
}

bool isomorphic(int r1, int r2)
{
    if (r1==null && r2==null) return true;
    if (r1==null || r2==null) return false;
    int n1 = 0, n2 = 0;
    if (tree1[r1].left==null) n1++;
    if (tree1[r1].right==null) n1++;
    if (tree2[r2].left==null) n2++;
    if (tree2[r2].right==null) n2++;
    if (n1!=n2) return false;
    if (tree1[r1].element!=tree2[r2].element) return false;
    if (n1==2) return true;
    else if (n1==1) {
        if (tree1[r1].left==null&&tree2[r2].left==null) {
            return isomorphic(tree1[r1].right,tree2[r2].right);
        }
        else if (tree1[r1].left==null&&tree2[r2].right==null) {
            return isomorphic(tree1[r1].right,tree2[r2].left);
        }
        else if (tree1[r1].right==null&&tree2[r2].left==null) {
            return isomorphic(tree1[r1].left,tree2[r2].right);
        }
        else if (tree1[r1].right==null&&tree2[r2].right==null) {
            return isomorphic(tree1[r1].left,tree2[r2].left);
        }
    }
    else if (n1==0) {
        if (tree1[tree1[r1].left].element==tree2[tree2[r2].left].element) {
            return isomorphic(tree1[r1].left,tree2[r2].left) && isomorphic(tree1[r1].right,tree2[r2].right);
        }else{
            return isomorphic(tree1[r1].left,tree2[r2].right) && isomorphic(tree1[r1].right,tree2[r2].left);
        }
    }
    return true;
}

int build(node * tree)
{
    int n;cin >> n;
    if (n==0) return -1;
    int * select = new int [n];
    char le, ri;
    for (int i = 0; i < n; i++) select[i] = 0;
    for (int i = 0; i < n; i++) {
        cin >> tree[i].element >> le >> ri;
        if (le!='-') {
            tree[i].left = le - '0';
            select[tree[i].left] = 1;
        }else tree[i].left = null;
        if (ri!='-') {
            tree[i].right = ri - '0';
            select[tree[i].right] = 1;
        }else tree[i].right = null;
    }
    int ret = 0;
    for (int i = 0; i < n; i++) {
        if (select[i]==0) {
            ret = i;
            break;
        }
    }
    delete [] select;
    return ret;
}
