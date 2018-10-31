/*
starting at 14:35
ending at 14:40
*/
#include <iostream>
#include <cstdlib>
using namespace std;
int cmp(const void * a, const void * b) {
    return *((int*)a) - *((int*)b);
}
int main(int argc, char const *argv[]) {
    int n;cin >> n;
    int * input = new int [n];
    for (int i = 0; i < n; i++) cin >> input[i];
    qsort(input,n,sizeof(int),cmp);
    for (int i = 0; i < n; i++) {
        cout << input[i];
        if (i + 1 != n) cout << ' ';
    }
    return 0;
}
