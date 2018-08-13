#include <iostream>
#define _MIN_ -10001
using namespace std;

struct Heap {
    int * element;
    int size;
    int maxsize;
};

Heap * createHeap(int n);
void insertHeap(Heap * H, int value);

int main(int argc, char const *argv[]) {
    freopen("D:\\SJTU\\Freshman Summer\\DS\\test.txt", "r", stdin);
    int n, m, value, item;cin >> n >> m;
    Heap * H = createHeap(n);
    for (int i = 0; i < n; i++) {
        cin >> value;
        insertHeap(H,value);
    }
    for (int i = 0; i < m; i++) {
        cin >> item;
        while (item>1) {
            cout << H->element[item] << ' ';
            item /= 2;
        }
        cout << H->element[item] << endl;
    }
    return 0;
}

void insertHeap(Heap * H, int value)
{
    int i = ++H->size;
    for ( ; H->element[i/2] > value; i/=2 ) {
        H->element[i] = H->element[i/2];
    }
    H->element[i] = value;
}

Heap * createHeap(int n)
{
    Heap * H = new Heap;
    H->element = new int [n+1];
    H->element[0] = _MIN_;
    H->size = 0;
    H->maxsize = n;
    return H;
}
