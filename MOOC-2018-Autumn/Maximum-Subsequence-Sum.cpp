#include <iostream>
using namespace std;
int main(int argc, char const *argv[]) {
    freopen("D:\\SJTU\\Freshman Summer\\DS\\test.txt", "r", stdin);
    int k;
    cin >> k;
    int* a = new int [k];
    for (int i = 0; i < k; i++) {
        cin >> a[i];
    }
    int maxsum = 0, sum = 0, first = 0, i, j, zeroposition;
    bool track = false, getzero = false;
    for (int cnt = 0; cnt < k; cnt++) {
        sum += a[cnt];
        if (sum<0 && track) {
            track = false;
        }else if (sum>0 && !track) {
            track = true;
            first = cnt;
        }else if (sum==0) {
            getzero = true;
            zeroposition = cnt;
        }
        if (sum>maxsum) {
            maxsum = sum;
            i = first;
            j = cnt;
        }
        else if(sum<0) {
            sum=0;
        }
    }
    if (maxsum>0) cout << maxsum << ' ' << a[i] << ' ' << a[j];
    else if (maxsum==0 && getzero) cout << 0 << ' ' << 0 << ' ' << 0;
    else cout << 0 << ' ' << a[0] << ' ' << a[k-1];
    delete [] a;
    return 0;
}
