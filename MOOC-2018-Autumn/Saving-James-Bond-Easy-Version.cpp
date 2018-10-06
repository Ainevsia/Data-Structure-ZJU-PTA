#include <iostream>
#include <cmath>
#define max 100
#define r 50

struct node {
    int x, y;
    bool flag, visited;
};

node croco[max];
bool found = false;

using namespace std;

double getdis(int x1, int y1, int x2, int y2) {
    double ret = sqrt((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2));
    return ret;
}
void dfs(node * ptr, int n, int d);

int main(int argc, char const *argv[]) {
    freopen("../test.txt", "r", stdin);
    int n, d;cin >> n >> d;
    for (int i = 0; i < n; ++i) {
        cin >> croco[i].x >> croco[i].y;
        croco[i].flag = r - abs(croco[i].x) <= d || r - abs(croco[i].y) <= d;
        croco[i].visited = false;
    }
    for (int i = 0; i < n && !found; ++i) {
        if (!croco[i].visited && getdis(0,0,croco[i].x,croco[i].y)<=7.5+d)
            dfs(&croco[i],n,d);
    }
    if (!found) cout << "No";
    return 0;
}

void dfs(node * ptr, int n, int d) {
    if (ptr->flag) {
        found = true;
        cout << "Yes";
        return;
    }
    ptr->visited = true;
    for (int i = 0; i < n && !found; ++i) {
        if (!croco[i].visited && getdis(ptr->x,ptr->y,croco[i].x,croco[i].y)<=d)
            dfs(&croco[i],n,d);
    }
}