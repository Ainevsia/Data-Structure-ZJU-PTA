#include <iostream>
using namespace std;
struct node{
    int coef;//系数
    int expo;//指数
    node * next;
};
node * CreatList(node * head, int k);
void PrintList(node * head);
node * MultiplyList(node * p1, node *p2);
node * AddList(node * p1, node *p2);

int main(int argc, char const *argv[]) {
    int k1, k2;
    cin >> k1;
    node *head1 = NULL, *head2 = NULL;
    head1 = CreatList(head1, k1);
    cin >> k2;
    head2 = CreatList(head2, k2);
    //node *multi = MultiplyList(head1, head2);
    node *add = AddList(head1, head2);
    PrintList(add->next);
    return 0;
}

node * CreatList(node * head, int k)
{
    int coef, expo;
    node * p;
    cin >> coef >> expo;
    head = new node;
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
    while ( head ) {
        cout << head->coef << " " << head->expo;
        head = head->next;
        if ( head ) cout << " ";
    }
}
//receive the two pointers and return the required header
node * MultiplyList(node * p1, node *p2)//p is the pointor
{                                       //poining to the current node
    node *head = new node;
    head->expo = p1->expo + p2->expo;
    head->coef = p1->coef * p2->coef;
    head->next = NULL;
    if ( !p1->next && !p2->next ) return head;
    if ( !p1->next ) p2 = p2->next;
    else if ( !p2->next ) p1 = p1->next;
    else {
        int larger_expo, p1larger, p2larger;
        p1larger = p1->next->expo + p2->expo;
        p2larger = p2->next->expo + p1->expo;
        if ( p1larger > p2larger ) {
            p1 = p1->next;
            larger_expo = p1larger;
        }
        else if ( p1larger < p2larger ) {
            p2 = p2->next;
            larger_expo = p2larger;
        }else {                             //3 1
            larger_expo = p1larger;         //3 1
            head->next = new node;
            head->next->expo = larger_expo;
            head->next->coef = p1->coef * p2->next->coef + p2->coef * p1->next->coef;
            head = head->next;
        }
    }
    head->next = MultiplyList(p1, p2);
    return head;
}

node * AddList(node * p1, node *p2)     //receive 2 pointers and return the AddList
{                                       //head is a pointer to the head node
    node * p, * head;
    head = new node;
    p = head;
    int expo1, expo2;
    while ( p1->next || p2->next ) {
        expo1 = p1->expo;
        expo2 = p2->expo;
        p->next = new node;
        p->next = NULL;
        if ( expo1 > expo2 ) {
            p->expo = p1->expo;
            p->coef = p1->coef;
            p1 = p1->next;
        }else if ( expo1 < expo2 ) {
            p->expo = p2->expo;
            p->coef = p2->coef;
            p2 = p2->next;
        }else {
            p->expo = p1->expo;
            p->coef = p1->coef + p2->coef;
            p1 = p1->next;
            p2 = p2->next;
        }
        p = p->next;
    }
    return head;
}
