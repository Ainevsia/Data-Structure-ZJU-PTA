#include <iostream>
#define MAXN 50

using namespace std;
int maxheight = 0;
int n;
char preorder[MAXN], inorder[MAXN];
void calheight(int height, int prestart, int preend, int instart, int inend);

int main(){
    cin >> n >> preorder >> inorder;
    calheight(0,0,n-1,0,n-1);
    cout << maxheight;
    return 0;
}

void calheight(int height, int prestart, int preend, int instart, int inend) {
    int currentheight = height + 1, num = inend - instart + 1;
    if (currentheight > maxheight ) maxheight = currentheight;
//    cout << "here";
    if (instart>inend || prestart>preend) return;
//    cout << "hello";
    char rootchar = preorder[prestart];
    int rootofinorder = instart;
    for ( ; rootofinorder <= inend; ++rootofinorder) {
        if (inorder[rootofinorder] == rootchar) {
            break;
        }
    }
//    cout << rootofinorder << endl;
    //search the right tree!
    if (rootofinorder!=inend) {
        int numofright = inend - rootofinorder;
        calheight(currentheight,prestart+num-numofright,preend,rootofinorder+1,inend);
    }
    if (rootofinorder!=instart) {
        int numofleft = rootofinorder - instart;
        calheight(currentheight,prestart+1,prestart+numofleft,instart,rootofinorder-1);
    }

}