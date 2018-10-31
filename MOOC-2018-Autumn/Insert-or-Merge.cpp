/*
starting at 14:42
ending at
*/
#include <iostream>
#define MAXN 100

using namespace std;

int n;
int input[MAXN] = {0};
int seq[MAXN] = {0};
int sort[MAXN] = {0};

void printsort() {for (int i=0; i<n; i++) cout << sort[i] << ' '; cout << endl;}
void printinput() {for (int i=0; i<n; i++) cout << input[i] << ' '; cout << endl;}

void init();
bool cmp();
void myInsertSort(int i);     // 我理解的插入排序怎么好像和大家理解的不太一样orz
void InsertSort(int i);

int main(int argc, char const *argv[]) {
    freopen("D:\\SJTU\\Freshman Summer\\DS\\test.txt", "r", stdin);
    init();
    bool isInsert = false;
    int SortingPtr;
    for ( SortingPtr = 0; SortingPtr < n; SortingPtr++) {
        InsertSort(SortingPtr);
        // printsort();
        if (cmp()) {
            // cout << "arrived here" << endl;
            isInsert = true;
            break;
        }
    }
    if (isInsert) {
        cout << "Insertion Sort" << endl;
        InsertSort(SortingPtr + 1);
        for (int i = 0; i < n; i++) {
            cout << sort[i];
            if (i + 1 != n) cout << ' ';
        }
    }
    if (!isInsert) {
        /* merge section */
    }
    return 0;
}

void init() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> input[i];
        sort[i] = input[i];
    }
    for (int i = 0; i < n; i++) cin >> seq[i];
}

bool cmp() {
    bool eql = true;
    for (int i = 0; i < n; i++) {
        if (sort[i] != seq[i]) {
            eql = false;
            break;
        }
    }
    return eql;
}

void InsertSort(int i) {
    int insert = sort[i], ptr = 0;
    for ( ; ptr <= i; ptr++) {
        if (sort[ptr] >= insert) break;
    }
    for (int j = i; j > ptr; j--) {
        sort[j] = sort[j-1];
    }
    sort[ptr] = insert;

}

void myInsertSort(int i) {    // set the position i to sort
    int min = i;
    for (int j = i + 1; j < n; j++) {
        if (sort[j] < sort[min]) min = j;
    }
    int tmp = sort[min];
    sort[min] = sort[i];
    sort[i] = tmp;
}
