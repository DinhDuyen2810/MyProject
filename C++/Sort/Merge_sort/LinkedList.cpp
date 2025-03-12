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
void merge(NODE** head, NODE* second)
{
    NODE* temp = *head;
    NODE* tmp = second;
    if(temp == second){
        return;
    }
    NODE* newHead;
    if(temp->data < tmp->data){
        newHead = temp;
        temp = temp->next;
    } else {
        newHead = tmp;
        tmp = tmp->next;
    }
    NODE* newNode1;
    newNode1 = newHead;
    NODE* newNode2;
    while(temp != NULL && tmp != NULL){
        if(temp->data < tmp->data){
            newNode2 = temp;
            temp = temp->next;
        } else {
            newNode2 = tmp;
            tmp = tmp->next;
        }
        newNode1->next = newNode2;
        newNode1 = newNode2;
    }
    if(temp != NULL){
        newNode1->next = temp;
    }
    if(tmp != NULL){
        newNode1->next = tmp;
    }
    *head = newHead;
}

void mergeSort(NODE** head)
{
    if (*head == NULL || (*head)->next == NULL) {
        return;
    }
    NODE* temp = *head;
    NODE* curr = (*head)->next;
    while(curr->next != NULL &&curr->next->next != NULL){
        temp = temp->next;
        curr = curr->next->next;
    }
    NODE* second = temp->next;
    temp->next = NULL;
    mergeSort(head);
    mergeSort(&second);
    merge(head, second);
}
int main() {
    srand(time(NULL));
    NODE* head = createNewNode(rand() % 100);
    NODE* temp;
    for (int i = 1; i < 15; i++) {
        temp = createNewNode(rand() % 100);
        pushfront(&head, temp->data);
    }
    mergeSort(&head);
    printList(head);
    return 0;
}
