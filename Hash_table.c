#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 0x7FFFFFFF是一个用16进制表示的整型,是整型里面的最大值
 0x7FFFFFFF 0111 1111 1111 1111 1111 1111 1111 1111（前31一个1代表数值，在计算机中整型最高位（32位）是符号位 0代表正数，1代表负数）
 为什么不用math.abs呢 因为当这个hash被计算出来是一个最小负数-2^31 ，正整数中没有32位去表示这个最小负数，所以还是会返回一个负数 ，也就是说绝对值函数返回的还是一个负数
 所以 & 0x7FFFFFFF 最高位32，转为0，所以返回这个数的绝对值
 */

typedef struct Node {
    char *str; //数据域，字符串
    struct Node *next; //指针域
} Node;

typedef struct HashTable {
    Node **data; //存数据域地址
    int size;
} HashTable;

Node *init_node(char *str, Node *head) {
    Node *p = (Node *)malloc(sizeof(Node));
    p->str = strdup(str); //拷贝
    p->next = head; //头插法
    return p;
}

//工业级别哈希表空间利用率在70%-90%
HashTable *init_hashtable(int n) {
    HashTable *h = (HashTable *)malloc(sizeof(HashTable));
    h->size = n << 1; //扩大两倍
//    h->data = (Node **)malloc(sizeof(Node *) * h->size);
    h->data = (Node **)calloc(h->size, sizeof(Node *)); //calloc直接初始化
    return h;
}

int BKDRHash(char *str) {
    int seed = 31, hash = 0;
    for (int i = 0; str[i]; i++) {
        hash = hash * seed + str[i];//加上当前ascii值
    }
    //hash有可能是负数，通过&0x7fffffff 取正数
    return hash & 0x7fffffff;
}

int insert(HashTable *h, char *str) {
    int hash = BKDRHash(str);
    int ind = hash % h->size;
    h->data[ind] = init_node(str, h->data[ind]);
    return 1;
}

int search(HashTable *h, char *str) {
    int hash = BKDRHash(str);
    int ind = hash % h->size;
    Node *p = h->data[ind];
    while (p && strcmp(p->str, str)) {
        p = p->next;
    }
    return p != NULL;
}

void clear_node(Node *node) {
    if (node == NULL) return;
    Node *p = node, *q;
    while (p) {
        q = p->next;
        free(p->str);
        free(p);
        p = q;
    }
    return;
}
void clear_hashtable(HashTable *h) {
    if (h == NULL) return;
    for (int i = 0; i < h->size; i++) {
        clear_node(h->data[i]);
    }
    free(h->data);
    free(h);
    return;
}

int main() {
    int op;
#define MAX_N 100
    char str[MAX_N + 5] = {0};
    HashTable *h = init_hashtable(MAX_N + 5);
    while (~scanf("%d%s", &op, str)) {
        switch (op) {
            case 0:
                printf("insert %s to HashTable\n", str);
                insert(h, str);
                break;
            case 1:
                printf("search %s from HashTable result = %d\n", str, search(h, str));
                break;
            default:
                break;
        }
    }
#undef MAX_N
    clear_hashtable(h);
    
    return 0;
}
