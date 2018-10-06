#include <iostream>
#include <cstdlib>
#include <cmath>
#define max 1003

int element[max] = {0}, cbs[max] = {0};

using namespace std;

int cmp(const void * a, const void * b);
int pos(int n);
void setroot(int start, int end, int position);

int main(int argc, char const *argv[]) {
    freopen("../test.txt", "r", stdin);
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> element[i];
    }
    qsort(element, n, sizeof(int), cmp);
    setroot(0, n-1, 1);
    for (int i = 1; i <= n; ++i) {
        cout << cbs[i];
        if (i != n) cout << ' ';
    }
    return 0;
}

int cmp(const void * a, const void * b) {
    return *(int*)a - *(int*)b;
}

int pos(int n) {
    int fulldepth = 0, setoff, origin = n;
    while (n > 1) {
        fulldepth++;
        n /= 2;
    }
    int conditioncmp = (int)pow(2,fulldepth-1) - (int)(origin - pow(2,fulldepth) + 1);
    setoff = pow(2,fulldepth - 1) - 1;
    if ( conditioncmp < 0) {
        setoff -= conditioncmp;
    }
//    cout << "returning " << setoff << endl;
    return setoff;
}

void setroot(int start, int end, int position) {
    if (end == start) {
        cbs[position] = element[start];
        return;
    }
    int n = end - start + 1;
    int rootpos = end - pos(n);
    int root = element[rootpos];
    cbs[position] = root;
//    cout << "cbs[" << position << "] gets value: " << root << endl;
    if (rootpos > start) {
        setroot(start, rootpos - 1, position * 2);
    }
    if (rootpos < end) {
        setroot(rootpos + 1, end, position * 2 + 1);
    }
}
