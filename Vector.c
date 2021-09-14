
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// gcc vector.c 编译文件
// ./a.o 执行文件

//加颜色宏
#define COLOR(a, b) "\033[" #b "m" a "\033[0m"
#define GREEN(a) COLOR(a, 32)
//顺序表定义
typedef struct Vector {
    int *data;
    int size, length;
} Vector;

Vector *init(int n) {
    Vector *v = (Vector *)malloc(sizeof(Vector));
    //分配空间返回首地址，表示开辟n大小的连续控件
    v->data = (int *)malloc(sizeof(int) * n);
    v->size = n;
    v->length = 0;
    return v;
}

void clear(Vector *v) {
    if (v == NULL) {
        return;
    }
    free(v->data);
    free(v);
    return;
}

int expand(Vector *v) {
    // malloc(申请，可能不干净) calloc（申请，初始化为0） realloc（重新分配）
    // realloc工作原理：
    //1.如果能在原来地址扩容，就直接扩容，返回原来的首地址
    //2.如果不能在原地址扩容，需要新申请满足的新空间，然后把旧内容拷贝过来，然后释放，返回新地址。
    //3. 如果扩容失败，返回NULL.
    /*
    v->data = (int *)realloc(v->data, sizeof(int) * (v->size * 2));
    v->size <<= 1;// 扩大两倍
    */
    // 正确扩容操作，先尝试扩容，如果失败就减半。
    int extr_size = v->size;
    int *p;
    while (extr_size) {
        p = (int *)realloc(v->data, sizeof(int) * (v->size + extr_size));
        if (p != NULL) break;
        //减半
        extr_size >>= 1;
    }
    //如果还是为NULL，返回失败
    if (p == NULL) return 0;
    v->data = p;
    v->size += extr_size;
    return 1;
}

int insert(Vector *v, int ind, int val) {
    if (v == NULL) return 0;
//    if (v->length == v-> size - 1) return 0;
    //实现扩容操作
    if (v->length == v->size - 1) {
        if (!expand(v)) return 0;
        printf(GREEN("success to expand! the size = %d\n"), v->size);
    }
    if (ind < 0 || ind > v-> length) return 0;
    //要倒序插入，如果顺序插入容易导致覆盖
    for (int i = v->length; i > ind; i--) {
        v->data[i] = v->data[i-1];
    }
    v->data[ind] = val;
    v->length += 1;
    return 1;
}
int erase(Vector *v, int ind) {
    if (v == NULL) return 0;
    if (ind < 0 || ind >= v->length) return 0;
    for (int i = ind; i < v->length; i++) {
        v->data[i] = v->data[i + 1];
    }
    v->length -= 1;
    return 1;
}
void output(Vector *v) {
    if (v == NULL) return;
    printf("Vector : [");
    for (int i = 0; i < v->length; i++) {
        //输出i, 并且加空格
        i && printf(" ");
        printf("%d", v->data[i]);
    }
    printf("]\n");
    return;
}
int main() {
    //用随机数，需要初始化一个时间种子
    srand(time(0));
#define MAX_OP 20
    Vector *v = init(1); //调试扩容操作
    for (int i = 0; i < MAX_OP; i++) {
        //定义随机op为0:插入操作，1为删除操作
//        int op = rand() % 2;
        //提高插入几率
        int op = rand() % 4;
        int val = rand() % 100;
        // 下标覆盖不完美
//        int ind = rand() % (v->length + 1);
        // [-1, v->length + 1]
        int ind = rand() % (v->length + 3) - 1;
        switch (op) {
            case 0:
            case 1:
            case 2:{
                printf("insert %d at %d to Vector = %d\n", val, ind, insert(v, ind, val));
            }
                break;
            case 3: {
                printf("erase a item at %d from Vector = %d\n", ind, erase(v, ind));
            }
                break;
            default:
                break;
        }
        output(v), printf("\n");
    }
#undef MAX_OP
    clear(v);
    return 0;
}
