#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//线性建堆 O(n)，自上向下调整

#define swap(a, b) { \
__typeof(a) __temp = a; \
a = b; b = __temp; \
}

/*
 原数组：    [ 5, 13, 2, 25, 7, 17, 20, 8, 4 ]
 构建最大堆： [ 25, 13, 20, 8, 7, 17, 2, 5, 4 ]
 排序：
 1. 0和n-1交换
 [ 4, 13, 20, 8, 7, 17, 2, 5, 25 ]
   *                          *
 2. 修复成最大堆
 [20, 13, 17, 8, 7, 4, 2, 5 | 25]
 3. |前面的部分，开始首尾交换
 [5, 13, 17, 8, 7, 4, 2, 20 | 25]
  *                      *
 4. 修复成最大堆
 [17, 13, 5, 8, 7, 4, 2 | 20, 25]

 */

void downUpdate(int *arr, int n, int ind) {
    while ((ind << 1) <= n) {
        int temp = ind, l = ind << 1, r = ind << 1 | 1;
        if (arr[l] > arr[temp]) temp = l;
        if (r <= n && arr[r] > arr[temp]) temp = r;
        if (temp == ind) break;
        swap(arr[ind], arr[temp]);
        ind = temp;
    }
    return ;
}

void heap_sort(int *arr, int n) {
    arr -= 1;
    //构建最大堆
    for (int i = n >> 1; i >= 1; i--) {
        downUpdate(arr, n, i);
    }
    //排序
    for (int i = n; i > 1; i--) {
        swap(arr[i], arr[1]);
        downUpdate(arr, i - 1, 1);
    }
    return;
}

void output(int *arr, int n) {
    printf("[");
    for (int i = 0; i < n; i++) {
        i && printf(" ");
        printf("%d", arr[i]);
    }
    printf("]\n");
    return;
}

int main() {
    srand(time(0));
#define MAX_N 20
    int *arr = (int *)malloc(sizeof(int) * MAX_N);
    for (int i = 0; i < MAX_N; i++) {
        arr[i] = rand() % 100;
    }
    output(arr, MAX_N);
    printf("\n");
    heap_sort(arr, MAX_N);
    output(arr, MAX_N);
#undef MAX_N
    free(arr);
    return 0;
}