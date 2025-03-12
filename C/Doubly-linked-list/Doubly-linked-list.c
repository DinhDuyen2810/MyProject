#include <stdio.h>
#include <stdlib.h>

struct NODE
{
    int data;
    struct NODE* prev,* next;
};
struct NODE* createNewNode(int data)
{
     struct NODE* newNode = (struct NODE*)malloc(sizeof(struct NODE));
     newNode->data = data;
     newNode->prev = NULL;
     newNode->next = NULL;
     return newNode;
}
void pushfront(struct NODE** head, int data,struct NODE** tail)
{
    struct NODE* newNode = createNewNode(data);
    if(*head == NULL){
        *tail = *head = newNode;
        return;
    }
    newNode->next = *head;
    (*head)->prev = newNode;
    *head = newNode;
}
void printlist1(struct NODE* head)
{
    printf("NULL -> ");
    while(head != NULL){
        printf("%d -> ",head->data);
        head = head->next;
    }
    printf("NULL\n");
}
void printlist2(struct NODE* tail){
    printf("NULL -> ");
    while(tail != NULL){
        printf("%d <- ",tail->data);
        tail = tail->prev;
    }
    printf("NULL\n");
}
void reverse(struct NODE** head, struct NODE ** tail)
{
    struct NODE* temp = *head;
    struct NODE* nextNode = NULL; 
    while(temp != NULL){
        nextNode = temp->next;
        temp->next = temp->prev;
        temp->prev = nextNode;
        temp = temp->prev;
    }
    temp = *head;
    *head = *tail;
    *tail = temp;
}
void func(struct NODE** head, struct NODE* p) {
    if (head == NULL || p == NULL || *head == p) {
        return;
    }

    // Disconnect p from its current position
    p->prev->next = p->next;
    p->next->prev = p->prev;

    // Find the last NODE
    struct NODE* last = (*head)->prev;

    // Make p the new head
    p->next = *head;
    p->prev = last;
    last->next = p;
    (*head)->prev = p;

    // Update the head pointer
    *head = p;
}

int main()
{
    struct NODE* head = NULL;
    struct NODE* tail = NULL;
    pushfront(&head,7,&tail);
    pushfront(&head,5,&tail);
    pushfront(&head,3,&tail);
    pushfront(&head,0,&tail);
    printlist1(head);
    func(&head, head->next);
    printlist1(head);

}