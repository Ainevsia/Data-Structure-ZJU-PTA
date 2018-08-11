#include <iostream>
#include <cmath>
using namespace std;

struct node {
    char element;
    char left;
    char right;     //note : char to int conversion!
};
char * maketree();
void print(char * head);
bool childcmp(char* tree1, char* tree2);

int main(int argc, char const *argv[]) {
    freopen("D:\\SJTU\\Freshman Summer\\DS\\test.txt", "r", stdin);
    char *tree1 = maketree();
    print(tree1);
    cout << endl;
    char *tree2 = maketree();
    print(tree2);
    bool similar = true;
    if (*tree1!=*tree2) similar = false;
    else {
        similar = childcmp(tree1,tree2);
    }
    if (similar) cout << "Yes";
    else cout << "No";
    return 0;
}

char * writecmp(char * cmp, char * tree)
{
    static int cnt = 1;

}

bool childcmp(char* tree1, char* tree2)
{
    int length = tree1[0]
    char * cmp = new char [length+1];
    cmp[0] = (char)length;
    writecmp(cmp,tree1);
}

void print(char * head)
{
    int n = head[0];
    int cnt = 0, i=1;
    while (cnt<n) {
        if (head[i]>='A' && head[i]<='J') {
            cout << head[i] << " ";
            cnt++;
        }
        i++;
    }
}

void setnode(char * head, int pos, char element)
{
    head[pos] = element;
}

char * addfamilytotree(node * giventree, int n, char * head, int pos)
{
    //cout << "adding " << n << " to " << pos << endl;
    node * src = &giventree[n];
    if (src->left!=-1) {
        addfamilytotree(giventree,src->left,head,pos*2);
    }else{
        setnode(head,pos*2,0);
    }
    setnode(head,pos,src->element);
    if (src->right!=-1) {
        addfamilytotree(giventree,src->right,head,pos*2+1);
    }else{
        setnode(head,pos*2+1,0);
    }
    return head;
}

char * maketree()
{
    int n;cin >> n;
    node *giventree = new node [n];
    int *select = new int [n];
    char ele, lef, rig;
    for (size_t i = 0; i < n; i++) select[i] = 0;
    for (size_t i = 0; i < n; i++) {
        cin >> ele >> lef >> rig;
        if (lef!='-') {giventree[i].left = lef - '0';select[giventree[i].left] = 1;}
        else giventree[i].left = -1;
        if (rig!='-') {giventree[i].right = rig - '0';select[giventree[i].right] = 1;}
        else giventree[i].right = -1;

        giventree[i].element = ele;
    }
    int root = 0;
    for (size_t i = 0; i < n; i++) {
        if (select[i]==0) {
            root = (int)i;
            break;
        }
    }
    int max = (int)pow(2,n);
    char * tree = new char [max];
    tree[0] = (char)n;
    char * head = addfamilytotree(giventree,root,tree,1);
    return head;
}
