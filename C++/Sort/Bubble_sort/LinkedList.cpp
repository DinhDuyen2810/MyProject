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
        NODE* next = second->next;
        second->next = first;
        first->next = next;
        *head = second;
    } else {
        NODE* prev1;
        NODE* temp = *head;
        while(temp->next != first){
            temp = temp->next;
        }
        prev1 = temp;
        temp = second->next;
        prev1->next = second;
        second->next = first;
        first->next = temp;
    }
}

void bubbleSort(NODE** head, int n)
{
    NODE* curr;
    int i = 0;
    int j = 0;
    int swapped = 0;
    do{
        i = 0;
        swapped = 0;
        NODE* tmp = *head;
        while(i < n - j - 1 && tmp != NULL){
            if(tmp->data > tmp->next->data){
                curr = tmp->next;
                swap(tmp, curr, head);
                tmp = curr;
                swapped = 1;
            }
            i++;
            tmp = tmp->next;
        }
        j++;    
    } while(swapped);
}
int main() {
    srand(time(NULL));
    NODE* head = createNewNode(rand() % 100);
    NODE* temp;
    for (int i = 1; i < 15; i++) {
        temp = createNewNode(rand() % 100);
        pushfront(&head, temp->data);
    }
    bubbleSort(&head, 15);
    printList(head);
    return 0;
}
