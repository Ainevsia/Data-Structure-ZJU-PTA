#include <iostream>
using namespace std;
const int MAX = 1003;
struct node{
    int coef;//系数
    int expo;//指数
    node * next;
};
node * CreatList(node * head);                              //单链表的读入与创建
void PrintList(node * head);                                //输出以head为头结点的链表
node * MultiplyList(node * p1, node *p2);                   //多项式乘法
void Attach(int coef, int expo, node **nodepointer);        //插入一个节点至nodepointer后
node * AddList(node * p1, node *p2);                        //多项式加法
void FreeList(node * p);                                    //内存释放

int main(int argc, char const *argv[]) {
    freopen("D:\\SJTU\\Freshman Summer\\DS\\test.txt", "r", stdin);
    node *head1 = NULL, *head2 = NULL;
    head1 = CreatList(head1);
    head2 = CreatList(head2);
    node *multi = MultiplyList(head1, head2);
    node *add = AddList(head1, head2);
    PrintList(multi);cout << endl;
    PrintList(add);
    FreeList(head1);FreeList(head2);FreeList(multi);FreeList(add);
    return 0;
}

node * CreatList(node * head)
{
    int coef, expo, k;
    node * p;
    head = new node;
    cin >> k;
    if ( !k ) return NULL;
    cin >> coef >> expo;
    head->coef = coef;
    head->expo = expo;
    head->next = NULL;
    p = head;
    for (size_t i = 1; i < k; i++) {
        cin >> coef >> expo;
        node *temp = new node;
        p->next = temp;
        temp->coef = coef;
        temp->expo = expo;
        temp->next = NULL;
        p = temp;
    }
    return head;
}

void PrintList(node * head)
{
    if ( !head ) {
        cout << "0 0";
    }
    while ( head ) {
        cout << head->coef << " " << head->expo;
        head = head->next;
        if ( head ) cout << " ";
    }
}
//by inserting to the right place 2 loops
node * MultiplyList(node * p1, node *p2)//p is the pointor
{                                       //poining to the current node
    node *head = new node;
    head->expo = MAX;
    head->next = NULL;
    while ( p1 ) {
        node *p = p2;
        while ( p ) {
            //PrintList(head->next);
            //cout << endl << endl;
            int coef = p1->coef * p->coef;
            int expo = p1->expo + p->expo;
            node *temp = head;
            while ( true ) {    //point to one in front
                // cout << "once ";
                if ( !(temp->next) || temp->next->expo<=expo ) break;
                temp = temp->next;
            }
            //now temp points to the insert place ahead
            // cout << "now expo is " << expo;
            // cout << "my temp->expo = " << temp->expo << endl;
            if ( temp->next && temp->next->expo == expo ) {
                if ( temp->next->coef + coef == 0 ) {   //delete
                    node * tobefreed = temp->next;
                    temp->next = tobefreed->next;
                    delete tobefreed;
                }else {                                 //join together
                    temp->next->coef += coef;
                }
            }else Attach(coef, expo, &temp);
            p = p->next;
        }
        p1 = p1->next;
    }
    node * tobedeleted = head;
    head = head->next;
    delete tobedeleted;
    return head;
}

void Attach(int coef, int expo, node **nodepointer)
{
    // cout << "now coef=" << coef << " expo=" << expo <<
    // " inserted after expo=" << (*nodepointer)->expo << endl;
    node * temp = new node;
    temp->coef = coef;
    temp->expo = expo;
    temp->next = (*nodepointer)->next;
    (*nodepointer)->next = temp;//here
    // cout << "now temp->next=" << temp->next;
    // cout << " *nodepointer points to expo" << (*nodepointer)->expo;
}

node * AddList(node * p1, node *p2)     //receive 2 pointers and return the AddList
{                                       //head is a pointer to the head node
    node * p, * head;
    head = new node;                    //head is a head noder contains
    p = head;                           //nothing but a next pointor
    head->coef = 0;
    head->expo = 0;
    head->next = NULL;
    while ( p1 && p2 ) {
        int expo1, expo2;
        expo1 = p1->expo;
        expo2 = p2->expo;
        if ( expo1 > expo2 ) {//copy
            p->next = new node;
            p = p->next;
            p->next = NULL;
            p->expo = p1->expo;
            p->coef = p1->coef;
            p1 = p1->next;
        }else if ( expo1 < expo2 ) {
            p->next = new node;
            p = p->next;
            p->next = NULL;
            p->expo = p2->expo;
            p->coef = p2->coef;
            p2 = p2->next;
        }else {
            int coef = p1->coef + p2->coef;
            if ( coef ) {
                p->next = new node;
                p = p->next;
                p->next = NULL;
                p->expo = p1->expo;
                p->coef = coef;
            }
            p1 = p1->next;
            p2 = p2->next;
        }
    }
    while ( p2 ) {
        p->next = new node;
        p = p->next;
        p->next = NULL;
        p->expo = p2->expo;
        p->coef = p2->coef;
        p2 = p2->next;
    }
    while ( p1 ) {
        p->next = new node;
        p = p->next;
        p->next = NULL;
        p->expo = p1->expo;
        p->coef = p1->coef;
        p1 = p1->next;
    }
    //cout << head->next;
    p = head;
    head = head->next;
    delete p;
    return head;
    // if ( head->next ) {
    // }else {
    //     return head;
    // }
}

void FreeList(node * p)
{
    node * next;
    while ( p ) {
        next = p->next;
        delete p;
        p = p->next;
    }
}

/*
程序最后的两个细节问题
1- 当加法结果为零时的输出
2- 当有一个k为零时的输出
*/
