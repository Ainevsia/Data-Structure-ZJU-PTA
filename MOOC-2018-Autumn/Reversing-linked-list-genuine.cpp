#include <iostream>
#include <iomanip>
#define max 100005

using namespace std;

struct node {
    int ads;
    int data;
    int next;
};

node memory[max];

int getlength(node * head);
node * reverse(node * head, int k);
void print(node * head, int length);

int main(int argc, char const *argv[]) {
    freopen("D:\\SJTU\\Freshman Summer\\DS\\test.txt", "r", stdin);
    int ads, n, k;cin >> ads >> n >> k;
    int address, data, next;
    for (int i = 0; i < n; i++) {
        cin >> address >> data >> next;
        memory[address].ads = address;
        memory[address].data = data;
        memory[address].next = next;
    }
    node head, *headptr;
    head.next = ads;
    headptr = &head;
    int length = getlength(headptr);
    for (size_t i = k; i <= length; i+=k) {
        int front = headptr->next;
        headptr->next = reverse(headptr,k)->ads;
        headptr = &memory[front];
        //print(&head,length);cout << endl;

    }
    headptr = &head;
    print(headptr,length);

    return 0;
}

node * reverse(node * head, int k) {
    node * front = &memory[head->next];
    node * rear = &memory[front->next];
    node * temp;
    int cnt = 1;
    while (cnt<k) {
        temp = &memory[rear->next];
        rear->next = front->ads;
        front = rear;
        rear = temp;
        cnt++;
    }
    memory[head->next].next = rear->ads;
    return front;
}

int getlength(node * head) {
    int cnt = 0, adds = head->next;
    while (adds!=-1) {
        cnt++;
        adds = memory[adds].next;
    }
    return cnt;
}

void print(node * head, int length) {
    node * ptr = &memory[head->next];
    for (size_t i = 0; i < length; i++) {
        cout << setw(5) << setfill('0') << ptr->ads;
        cout << ' ' << ptr->data << ' ';
        if ( i==length-1 ) cout << "-1";
        else cout << setw(5) << setfill('0') << ptr->next << endl;
        ptr = &memory[ptr->next];
    }
}
