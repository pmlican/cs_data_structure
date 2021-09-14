//
//  LinkedList.c
//  test_c
//
//  Created by di.chen on 2021/9/14.
//

#include <stdio.h>
#include <stdlib.h> //动态申请内存

typedef struct Node{ //节点定义
    int data;
    struct Node *next;
} Node;

typedef struct LinkedList {
//    Node *head; //头指针
    Node head; //虚拟头节点
    int length; //长度
} LinkedList;

Node *getNewNode(int val) {
    Node *p = (Node *)malloc(sizeof(Node));
    p->data = val;
    p->next = NULL;
    return p;
}
LinkedList *init() {
    LinkedList *l = (LinkedList *)malloc(sizeof(LinkedList));
//    l->head = NULL;
    l->head->next = NULL;
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
    return l;
    
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

int main() {
    
    return 0;
}
