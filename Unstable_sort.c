
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//#define swap(a, b) {\
//    a ^= b; b ^= a; a ^= b;\
//}
#define swap(a, b) { \
__typeof(a) __temp = a; a = b; b = __temp; \
}

//测试函数，args可变参数
#define TEST(arr, n, func, args...) {\
    int *num = (int *)malloc(sizeof(int) * n);\
    memcpy(num, arr, sizeof(int) * n);\
    output(num, n);\
    printf("%s = ", #func);\
    func(args);\
    output(num, n);\
    free(num);\
    printf("\n");\
}

void select_sort(int *num, int n) {
    for (int i = 0; i < n - 1; i++) {
        int ind = i;
        for (int j = i + 1; j < n; j++) {
            if (num[j] < num[ind]) ind = j;
        }
        swap(num[ind], num[i]); //选择排序会出现 a ^ a的情况
    }
    return;
}

void quick_sort(int *num, int l, int r) {
    if (l > r) return;
    int x = l, y = r, z = num[x];
    while (x < y) {
        while (x < y && num[y] > z) {
            y--;
        }
        if (x < y) {
            num[x++] = num[y];
        }
        while (x < y && num[x] < z) {
            x++;
        }
        if (x < y) {
            num[y--] = num[x];
        }
    }
    num[x] = z;
    quick_sort(num, l, x - 1);
    quick_sort(num, x + 1, r);
    return;
}

//单边递归
void quick_sort_optimize(int *num, int l, int r) {
    while (l < r) {
        int x = l, y = r, z = num[(l + r) >> 1]; //基准值取中间
        do {
            while (num[x] < z) { //无监督
                x++;
            }
            while (num[y] > z) {
                y--;
            }
            if (x <= y) {
                swap(num[x], num[y]);
                x++;
                y--;
            }
        } while (x <= y);
        quick_sort_optimize(num, l, y);
        l = x;
    }
    return;
}


void output(int *num, int n) {
    printf("[");
    for (int i = 0; i < n; i++) {
        i && printf(" ");
        printf("%d", num[i]);
    }
    printf("]\n");
    return;
}

//生成随机数组
void randint(int *num, int n) {
    while (n--) num[n] = rand() % 100;
}

void test_quick_sort() {
    srand(time(0));
#define MAX_N 20
    int arr[MAX_N];
    randint(arr, MAX_N);
    TEST(arr, MAX_N, select_sort, num, MAX_N);
    TEST(arr, MAX_N, quick_sort, num, 0, MAX_N - 1);
#undef MAX_N
}

#define TEST_MAX 100000

void init_arr(int *arr, int n) {
    for (int i = 0; i < n; i++) {
        arr[i] = n - i;
    }
}
// time ./a.out > out1
//分别测试1000 10000 100000
// ./a.out > out1  0.00s user 0.00s system 49% cpu 0.009 total
// ./a.out > out1  0.13s user 0.00s system 8% cpu 1.586 total
// ./a.out > out1  12.81s user 0.05s system 91% cpu 14.089 total
// ./a.out > out2  0.02s user 0.00s system 4% cpu 0.699 total

int main() {
    int arr[TEST_MAX] = {0};
    init_arr(arr, TEST_MAX);
    quick_sort_optimize(arr, 0, TEST_MAX - 1);
    output(arr, TEST_MAX);
    return 0;
}



