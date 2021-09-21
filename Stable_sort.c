
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define swap(a, b) {\
    a ^= b; b ^= a; a ^= b;\
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

void insert_sort(int *num, int n) {
    for (int i = 1; i < n; i++) {
        for (int j = i; j > 0 && num[j] < num[j - 1]; j--) {
            swap(num[j], num[j - 1]);
        }
    }
}
void bubble_sort(int *num, int n) {
    int times = 1; //优化冒泡，如果没有发生交换，就提前退出循环
    for (int i = 1; i < n && times; i++) {
        times = 0;
        for (int j = 0; j < n - i; j++) {
//            if(num[j] > num[j + 1]) {
//                swap(num[j], num[j + 1])
//            }
            //可以反过来写,简化代码
            if (num[j] <= num[j + 1]) continue;
            swap(num[j], num[j + 1]);
            times = 1;
        }
    }
    return;
}

//归并排序
void merge_sort(int *num, int l, int r) {
    if (r - l <= 1) { //递归出口
        if (r - l == 1 && num[r] < num[l]) { // 当为两个时，r<l交换
            swap(num[r], num[l])
        }
        return;
    }
    int mid = (l + r) >> 1; // 平分一半
    merge_sort(num, l , mid);
    merge_sort(num, mid + 1, r);
    int *temp = (int *)malloc(sizeof(int) * (r - l + 1));
    int p1 = l, p2 = mid + 1, k = 0;
    while (p1 <= mid || p2 <= r) {
        if (p2 > r || (p1 <= mid && num[p1] <= num[p2])) {
            temp[k++] = num[p1++];
        } else {
            temp[k++] = num[p2++];
        }
    }
    //拷贝到原数组
    memcpy(num + l, temp, sizeof(int) * (r - l + 1));
    free(temp);
    return;
}

void merge(int num[], int temp[], int l, int mid, int r) {
    int i = l, j = mid + 1, k = l;
    while (i != mid + 1 && j != r + 1) {
        if (num[i] > num[j]) {
            temp[k++] = num[j++];
        } else {
            temp[k++] = num[i++];
        }
    }
    while (i != mid + 1) {
        temp[k++] = num[i++];
    }
    while (j != r + 1) {
        temp[k++] = num[j++];
    }
    //拷贝回原数组
    for (i = l; i <= r; i++) {
        num[i] = temp[i];
    }
}

//百度百科易懂版本
void mergeSort(int num[], int temp[], int l, int r) {
    if (l < r) {
        int mid = l + (r - l) / 2; //避免溢出int
        mergeSort(num, temp, l, mid);
        mergeSort(num, temp, mid + 1, r);
        merge(num, temp, l, mid, r);
    }
}

//生成随机数组
void randint(int *num, int n) {
    while (n--) num[n] = rand() % 100;
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

int main() {
    srand(time(0));
#define MAX_N 20
    int arr[MAX_N];
    randint(arr, MAX_N);
    TEST(arr, MAX_N, insert_sort, num, MAX_N);
    TEST(arr, MAX_N, bubble_sort, num, MAX_N);
    TEST(arr, MAX_N, merge_sort, num, 0, MAX_N - 1);
    int temp[MAX_N];
    TEST(arr, MAX_N, mergeSort, num, temp, 0, MAX_N - 1);
//    mergeSort(arr, temp, 0, MAX_N - 1);
//    for (int i = 0; i < MAX_N; i++) {
//        printf("%d ",arr[i]);
//    }
    
#undef MAX_N
    
    return 0;
}
