#include <stdio.h>
#include <stdlib.h>

/**
 * 1) 单链表反转
 * 2) 链表中环的检测
 * 3) 两个有序的链表合并
 * 4) 删除链表倒数第 n 个结点
 * 5) 求链表的中间结点
 */

struct Node{
    int value;
    struct Node *next;
};

struct Node* createNode(int value) {
    struct Node *p = (struct Node *)malloc(sizeof(struct Node));
    p->value = value;
    p->next = NULL;
    return p;
}

struct Node* insertNode(struct Node* head, struct Node* newNode) {
    struct Node* p = head;
    if ( head == NULL ) {
        head = newNode;
    }else{ 
        while ( p->next != NULL ) {
            p = p->next;
        }
        p->next = newNode;
    }
    return head;
}
struct Node* createNodeList(int number) {
    struct Node *head = NULL;
    for(int i=1;i<=number;i++) {
        struct Node *newNode = createNode(i); 
        head = insertNode(head, newNode);
    }
    return head;
}
void display(struct Node *head) {
    if(head == NULL)
        return;
    struct Node *p= NULL;
    p = head;
    while (p != NULL){
        if (p->next != NULL)
            printf("%d,",p->value);
        else
            printf("%d\n",p->value);
        p = p->next;
    }
}
struct Node* reverse(struct Node* head) {

    if(head == NULL)
        return head;

    struct Node *pre= NULL;
    struct Node *cur= head;
    struct Node *pnext= head->next;
    
    while (cur != NULL) {
        cur -> next = pre;
        pre = cur;
        cur = pnext;
        if (pnext != NULL)
            pnext = pnext -> next;
    }
    return pre;    

}
struct Node* freeList(struct Node* head) {
    struct Node* p = NULL;
    while (head) {
        p = head;
        head = head->next; 
        free(p);
    }
    return head;
}
int checkCircle(struct Node* head) {
    int isCircle = 0;
    struct Node* slow = head;
    struct Node* fast = head;
    while(fast != NULL && fast->next != NULL) {
        fast = fast->next->next;
        slow = slow->next;
        if(slow == fast) {
            isCircle = 1;
            break;
        } 
    }
    if(isCircle)
        printf("circled list\n"); 
    else
        printf("non-circled list\n"); 
    return isCircle; 
}

void demoCheckCircleLinkedList() {
    checkCircle(NULL);

    struct Node* node_self_circled = createNode(1);
    node_self_circled -> next = node_self_circled;
    checkCircle(node_self_circled);

    struct Node* node_1 = createNode(1);
    struct Node* node_2 = createNode(1);
    struct Node* node_3 = createNode(1);
    node_1->next = node_2;
    node_2->next = node_3;
    node_3->next = node_2;
    checkCircle(node_1);

    node_3->next = NULL;
    checkCircle(node_1);
    
}

void demoReverseSinglyLinkedList() {
    struct Node *head= NULL;
    struct Node *p= NULL;
    head = createNodeList(10);
    printf("original:\n");
    display(head);
    head = reverse(head);
    printf("reversed:\n");
    display(head);
    printf("free list\n");
    head = freeList(head);
    display(head);
}

void deleteLastKth(struct Node *head, int k) {
    if (!head)
        return;

    printf("before delete, the list:");
    display(head);
    struct Node *tmp = NULL;
    struct Node * reversed_node = reverse(head);
    for(int i=0;i<k && reversed_node != NULL;i++) {
        tmp = reversed_node;
        reversed_node = reversed_node -> next;
        free(tmp);
    }
    head = reverse(reversed_node);
    printf("after delete, the list:");
    display(head);
}

void demoDeleteLastKth() {
    deleteLastKth(createNodeList(10), 0);
    deleteLastKth(createNodeList(10), 1);
    deleteLastKth(createNodeList(10), 2);
    deleteLastKth(createNodeList(10), 12);
}
void main() {
    //demoReverseSinglyLinkedList();
    //demoCheckCircleLinkedList();
    demoDeleteLastKth();
}
