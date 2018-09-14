#include <iostream>

using namespace std;

bool check(int m, int n);

int main(int argc, char const *argv[]) {
    freopen("D:\\SJTU\\Freshman Summer\\DS\\test.txt", "r", stdin);
    int m, n, k;cin >> m >> n >> k;
    for (int i = 0; i < k; i++) {
        bool valid = check(m,n);
        if (valid) cout << "YES" << endl;
        else cout << "NO" << endl;
    }
    return 0;
}

bool check(int m, int n) {
    int * stack = new int [n], stk = -1;
    int * store = new int [n], str = 0;
    for (int i = 0; i < n; i++) {
        cin >> store[i];
    }
    bool valid = false;
    for (int topush = 1; topush <= n; topush++) {
        stack[++stk] = topush;
        if (stk==m) break;
        while (stk!=-1 && store[str]==stack[stk]) {
            stk--;str++;
        }
    }
    if (stk==-1) valid = true;
    delete [] stack;
    return valid;
}
