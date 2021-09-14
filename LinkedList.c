
//
//  LinkedList.c
//  test_c
//
//  Created by di.chen on 2021/9/14.
//

#include <stdio.h>
#include <stdlib.h> //动态申请内存
#include <time.h>

typedef struct Node{ //节点定义
    int data;
    struct Node *next;
} Node;

typedef struct LinkedList {
//    Node *head; //头指针
    Node head; //虚拟头节点
    int length; //长度
} LinkedList;
Node *getNewNode(int);
LinkedList *init();
void clear_node(Node *);
void clear(LinkedList *);
int insert(LinkedList *, int, int);
int erase(LinkedList *, int);

Node *getNewNode(int val) {
    Node *p = (Node *)malloc(sizeof(Node));
    p->data = val;
    p->next = NULL;
    return p;
}
LinkedList *init() {
    LinkedList *l = (LinkedList *)malloc(sizeof(LinkedList));
//    l->head = NULL;
    l->head.next = NULL;
    l->length = 0;
    return l;
}

int insert(LinkedList *l, int ind, int val) {
    if (l == NULL) return 0;
    if (ind < 0 || ind > l->length) return 0; //两个异常判断
    //插入链表需要获取前一个节点
    Node *p = &(l->head), *node = getNewNode(val);
    while (ind--) p = p->next; //虚拟头结点好处
    node->next = p->next;  // 修改指向关系
    p->next = node;
    l->length += 1;
    return 1;
    
}
int erase(LinkedList *l, int ind) {
    //删除
    if (l == NULL) return 0;
    if (ind < 0 || ind > l->length) return 0; //两个异常判断
    Node *p = &(l->head), *q;
    while (ind--) p = p->next; //虚拟头结点好处
    q = p->next;
    p->next = q->next;
    clear_node(q);
    l->length -= 1;
    return 1;
}

void clear_node(Node *node) {
    if (node == NULL) {
        return;
    }
    free(node);
    return;
}

void clear(LinkedList *l) {
    if (l == NULL) return;
//    Node *p = l->head, *q;
    Node *p = l->head.next, *q;
    while (p != NULL) { //遍历链表把所有节点释放掉
        q = p->next;
        clear_node(p);
        p = q;
    }
    free(l);
    return;
}
void output(LinkedList *l) {
    if (l == NULL) {
        return;
    }
    printf("List(%d): ", l->length);
    for (Node *p = l->head.next; p != NULL; p = p->next) {
        printf("%d->", p->data);
    }
    printf("NULL\n");
    return;
}

int main() {
    srand(time(0));
#define MAX_OP 20
    LinkedList *l = init();
    for (int i = 0; i < MAX_OP; i++) {
        int op = rand() % 4;
        int val = rand() % 100;
        int ind = rand() % (l->length + 3) - 1;//左右扩大两个，两个无效的数字-1和length+1
        switch (op) {
            case 0:
            case 1:
            case 2: {
                printf("insert %d at %d to list = %d\n", val, ind, insert(l, ind, val));
            }
                break;
            case 3: {
                printf("erase a item at %d from List = %d\n", ind, erase(l, ind));
            }
                break;
            default:
                break;
        }
        output(l), printf("\n");
    }
#undef MAX_OP
    clear(l);
    return 0;
}
