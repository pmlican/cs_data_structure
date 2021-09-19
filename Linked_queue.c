
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//链队列: 优点不需要扩容，缺点是需要额外的空间存next指针
typedef struct Node {
    int data;
    struct Node *next;
} Node;

typedef struct Queue {
    Node head; //虚拟头结点
    Node *tail;
    int length;
} Queue;

Node *getNewNode(int val) {
    Node *p = (Node *)malloc(sizeof(Node));
    p->data = val;
    p->next = NULL;
    return p;
}

Queue *init_LinkQueue() {
    Queue *q = (Queue *)malloc(sizeof(Queue));
    q->head.next = NULL;
    q->tail = &(q->head);
    q->length = 0;
    return q;
}

void clear_node(Node *node) {
    if (node == NULL) return;
    free(node);
    return;
}

void clear(Queue *q) {
    if (q == NULL) return;
    Node *p = q->head.next, *temp;
    while (p != NULL) {
        temp = p->next;
        clear_node(p);
        p = temp;
    }
    free(q);
    return;
}

int push(Queue *q, int val) {
    if (q == NULL) return 0;
    Node *node = getNewNode(val);
    q->tail->next = node;
    q->tail = node;
    q->length += 1;
    return 1;
}
int empty(Queue *q) {
    return q->length == 0;
}
int front(Queue *q) {
    return q->head.next->data;
}
int pop(Queue *q) {
    if (q == NULL) return 0;
    if (empty(q)) return 0;
    Node *temp = q->head.next;
    q->head.next = temp->next;
    clear_node(temp);
    q->length -= 1;
    //解决报错问题
    if (q->length == 0) q->tail = &(q->head);
    return 1;
}

void output(Queue *q) {
    printf("Queue(%d) : [", q->length);
    for (Node *p = q->head.next; p != NULL; p = p->next) {
        p != q->head.next && printf(" ");
        printf("%d", p->data);
    }
    printf("]\n");
    return;
}

int main() {
    srand(time(0));
#define MAX_OP 10
    Queue *q = init_LinkQueue();
    for (int i = 0; i < MAX_OP; i++) {
        int val = rand() % 100;
        int op = rand() % 4;
        switch (op) {
            case 0:
            case 1:
            case 2: {
                printf("push %d to Queue = %d\n", val, push(q, val));
            }
                break;
            case 3: {
                if (empty(q)) {
                    printf("fail to pop!\n");
                } else {
                    printf("success to pop :%d\n", front(q));
                    pop(q);
                }
            }
                break;
            default:
                break;
        }
        output(q), printf("\n");
    }
#undef MAX_OP
    clear(q);
    return 0;
}
