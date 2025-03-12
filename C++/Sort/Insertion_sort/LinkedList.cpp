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
void insertionSort(NODE** head)
{
    NODE* current = (*head)->next;
    while(current != NULL){
        NODE* prev = *head;
        NODE* front;
        NODE* next = current->next;
        while(prev != current){
            if(prev->data < current->data){
                front = prev;
                prev = prev->next;
                continue;
            }
            if(prev == *head){
                current->next = prev;
                *head = current;
            } else {
                front->next = current;
                current->next = prev;
            }
            while(prev->next != current){
                prev = prev->next;
            }
            prev->next = next;
            prev = current;
        }
        current = next;
    }
}
void insertionSort_fake(NODE* head)
{
    NODE* current = head->next;
    while(current!= NULL){
        NODE* key = current;
        NODE* prev = head;
        while(prev!= current){
            if(prev->data > key->data){
                int temp = prev->data;
                prev->data = key->data;
                key->data = temp;
            }
            prev = prev->next;
        }
        current = current->next;
    }
}
int main() {
    srand(time(NULL));
    NODE* head = createNewNode(rand() % 100);
    NODE* temp;
    for (int i = 1; i < 50; i++) {
        temp = createNewNode(rand() % 100);
        pushfront(&head, temp->data);
    }
    insertionSort(&head);
    printList(head);
    return 0;
}
