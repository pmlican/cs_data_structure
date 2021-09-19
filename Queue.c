#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//循环队列，解决假溢出问题
#define COLOR(a, b) "\033[" #b "m" a "\033[0m"
#define GREEN(a) COLOR(a, 32)

typedef struct Queue {
    int *data;
    int head, tail, length;
    //改造为循环队列
    int count;
} Queue;

Queue *init(int n) {
    Queue *q = (Queue *)malloc(sizeof(Queue));
    q->data = (int *)malloc(sizeof(int) * n); //分配空间，开辟n长度的连续，返回首地址
    q->length = n;
    q->head = q->tail = 0; //对尾指针指向最后一个元素的下一个空位置
    //FIXME: 循环队列修改
    q->count = 0;
    return q;
}
int expand(Queue *q) {
    //不能用realloc扩容了，因为循环队列，head不一定在0位置，不能保证顺序
    int extr_size = q->length;
    int *p; //新地址
    while (extr_size) {
        p = (int *)malloc(sizeof(int) * (q->length + extr_size));
        if (q != NULL) break;
        extr_size >>= 1; //减小一半
    }
    if (p == NULL) return 0;
    for (int i = q->head, j = 0; j < q->count; j++) {
        p[j] = q->data[(i + j) % q->length]; //按顺序拷贝到新地址
    }
    //释放旧空间
    free(q->data);
    q->data = p; //指向新地址
    //重置
    q->head = 0, q->tail = q->count;
    q->length += extr_size;
    return 1;
}

int push(Queue *q, int val) {
    if (q == NULL) return 0;
//    if (q->tail == q->length) return 0;
    //FIXME: 循环队列修改
//    if (q->count == q->length) return 0;
    //扩容操作
    if (q->count == q->length) {
        if (!expand(q)) {
            return 0;
        }
        printf(GREEN("success to expand! the size = %d\n"), q->length);
    }
//    q->data[q->tail] = val;
//    q->tail += 1;
    //等价于下面一行代码
    q->data[q->tail++] = val;
    //FIXME: 循环队列修改
    if (q->tail == q->length) q->tail = 0;
    q->count += 1;
    return 1;
}

int front(Queue *q) {
    return q->data[q->head];
}

int empty(Queue *q) {
//    return q->head == q->tail;
    //FIXME: 循环队列修改
    return q->count == 0;
}

int pop(Queue *q) {
    if (q == NULL) return 0;
    if (empty(q)) return 0;
    q->head += 1;
    //FIXME: 循环队列修改
    if (q->head == q->length) q->head = 0;
    q->count -= 1;
    return 1;
}

void clear(Queue *q) {
    if (q == NULL) return;
    free(q->data);//释放数据区
    free(q); //释放q指针
}

void output(Queue *q) {
    printf("Queue: [");
//    for (int i = q->head; i < q->tail; i++) {
//        i != q->head && printf(" ");
//        printf("%d", q->data[i]);
//    }
    //FIXME: 循环队列修改
    for (int i = q->head, j = 0; j < q->count; j++) {
        j && printf(" ");
        printf("%d", q->data[(i + j) % q->length]);
    }
    printf("]\n");
    return;
}

int main() {
    srand(time(0));
#define MAX_OP 20
//    Queue *q = init(MAX_OP);
    //FIXME: 循环队列修改
//    Queue *q = init(10); //模拟循环队列情况
    // 模拟不断扩容
    Queue *q = init(1);
    for (int i = 0; i < MAX_OP; i++) {
        int op = rand() % 4;
        int val = rand() % 100;
        switch (op) {
            case 0:
            case 1:
            case 2: {
                printf("push %d to Queue = %d\n", val, push(q, val));
            }
                break;
            case 3: {
                if (empty(q)) {
                    printf("fail to pop a item!\n");
                } else {
                    printf("success to pop a item: %d\n", front(q));
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
