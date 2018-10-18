#include <iostream>
#include <cstdlib>

struct node {
    double dis;
};

using namespace std;

int cmp (const void * a, const void * b) {
    return int((*((node**)a))->dis - (*((node**)b))->dis);
}

int intcmp (const void * a, const void * b) {
    return *(int*)b - *(int*)a;
}


int main() {
    node a, b, c;
    a.dis = 2.0; b.dis = 1.0; c.dis = 3.0;
    node * list[3];
    list[0] = &a;
    list[1] = &b;
    list[2] = &c;
    int intlist[3] = {1,2,3};
    qsort(list, 3, sizeof(node*), cmp);
    for (int i = 0; i < 3; ++i) {
        cout << list[i]->dis << endl;
    }
    qsort(intlist, 3, sizeof(int), intcmp);
    for (int i = 0; i < 3; ++i) {
        cout << intlist[i] << endl;
    }
}