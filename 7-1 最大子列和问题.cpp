#include <iostream>
using namespace std;
int main(int argc, char const *argv[]) {
    int k;
    cin >> k;
    int* a = new int [k];
    for (size_t i = 0; i < k; i++) {
        cin >> a[i];
    }
    int maxsum = 0, sum = 0;
    for (size_t i = 0; i < k; i++) {
        sum += a[i];
        if (sum>maxsum) maxsum = sum;
        else if(sum<0)sum=0;
    }
    if (maxsum>0) cout << maxsum;
    else cout << 0;
    delete [] a;
    return 0;
}
