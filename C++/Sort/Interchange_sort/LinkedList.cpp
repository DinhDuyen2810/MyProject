#include <iostream>
#include <cstdlib> 
#include <ctime>

using namespace std;

struct NODE
{
    int data;
    struct NODE* next;
};
NODE* createNewNode(int data)
{
    NODE* newNode = new NODE;
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}
void pushfront(NODE** head,int data)
{
    NODE* temp = *head;
    *head = createNewNode(data);
    (*head)->next = temp;
}
void printList(NODE* head)
{
    while (head != NULL ){
        cout << head->data << " ";
        head = head->next;
    }
}
void swap(NODE* first, NODE* second, NODE** head)
{
    if(first == *head){
        if(first->next == second){
            NODE* next = second->next;
            second->next = first;
            first->next = next;
            *head = second;
        } else {
            NODE* temp = *head;
            while(temp->next != second){
                temp = temp->next;
            }
            NODE* next = second->next;
            temp->next = first;
            second->next = first->next;
            first->next = next;
            *head = second;
        }
    } else {
        NODE* prev1;
        NODE* prev2;
        NODE* temp = *head;
        while(temp->next != second){
            if(temp->next == first){
                prev1 = temp;
            }
            temp = temp->next;
        }
        prev2 = temp;
        temp = second->next;
        if(prev2 == first){
            prev1->next = second;
            second->next = first;
            first->next = temp;
        } else {
            prev1->next = second;
            prev2->next = first;
            second->next = first->next;
            first->next = temp;
        }
    }
}

void interchangeSort(NODE** head)
{
    NODE* temp = *head;
    NODE* curr;
    while(temp != NULL){
        NODE* tmp = temp->next;
        while(tmp != NULL){
            if(tmp->data < temp->data){
                swap(temp, tmp, head);
                curr = temp;
                temp = tmp;
                tmp = curr;
            }
            tmp = tmp->next;
        }
        temp = temp->next;        
    }
}
int main() {
    srand(time(NULL));
    NODE* head = createNewNode(rand() % 100);
    NODE* temp;
    for (int i = 1; i < 15; i++) {
        temp = createNewNode(rand() % 100);
        pushfront(&head, temp->data);
    }
    interchangeSort(&head);
    printList(head);
    return 0;
}
