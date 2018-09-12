#include <iostream>
#include <cstring>

using namespace std;

struct node {
    char address[6];
    int data;
    char next[6];
};

int getelement(node * list, int n, char * address);
void exchange(node * list, int element, int i);
void printlist(node * list, int n);
void reverse(node * list, int n, int k);

int main(int argc, char const *argv[]) {
    freopen("D:\\SJTU\\Freshman Summer\\DS\\test.txt", "r", stdin);
    char address[6];int n, k;cin >> address >> n >> k;
    node * list = new node [n];
    for (int i = 0; i < n; i++) {
        cin >> list[i].address >> list[i].data >> list[i].next;
    }
    // ranking problem
    for (int i = 0; i < n; i++) {
        int element = getelement(list,n,address);
        strcpy(address,list[element].next);
        exchange(list,element,i);
        if (address[0]=='-') {
            n = i + 1;
            break;
        }
    }

    reverse(list,n,k);
    printlist(list,n);
    return 0;
}

void reverse(node * list, int n, int k) {
    int start = 0, end = k-1;
    if (end+1 > n) return;
    // change next
    for (int i = end; i >= start; i--) {
        if (i==start) {
            if (end+1==n) {
                strcpy(list[i].next,"-1");
            }else{
                strcpy(list[i].next,list[end+1].address);
            }
        }
        else strcpy(list[i].next,list[i-1].address);
    }
    // change sequence
    for (int i = start, j = end; i<j; i++, j--) {
        exchange(list,i,j);
    }
}

void printlist(node * list, int n) {
    for (int i = 0; i < n; i++) {
        cout << list[i].address << ' ' << list[i].data;
        cout << ' ' << list[i].next << endl;
    }
}

int getelement(node * list, int n, char * address) {
    for (int i = 0; i < n; i++) {
        if ( strcmp(list[i].address,address)==0 ) {
            return i;
        }
    }
    return -1;
}

void exchange(node * list, int element, int i) {
    node temp = list[element];
    list[element] = list[i];
    list[i] = temp;
}
