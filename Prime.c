#include <stdio.h>

int main() {
    
    return 0;
}

// 输出奇数合数
void composite_and_prime() {
    int digit;
    int divisor;
    int n;
    scanf("%d", &n);
    for (digit = 3; digit <= n; digit += 2) {
      for (divisor = 3; divisor < digit; divisor += 2) {
        if (digit % divisor == 0) {
          printf( "%d\n", digit); //输出奇数合数
          break;
        }
      }
    }
}

// 输出奇数质数
void odd_and_prime() {
    printf("2\n");
    int digit;
    int divisor;
    for (digit = 3; digit <= 15; digit += 2) {
        for (divisor = 3; divisor < digit; divisor += 2) {
            if (digit % divisor == 0){
                break;
            }
        }
        if (divisor == digit) {
            printf("%d\n", digit); // 输出奇数质数
        }
    }
}

void is_prime() {
    int N,n;
    scanf("%d", &N);
    // 质数大于， 只有1和本身能整除的，就是质数
    for(n = 2; n < N; n++) {
        if (N % n == 0) {
            // 说明还有其他数能整除
            break;
        }
    }
    if (N == n) {
        // 只有本身能整除
        printf("YES");
    } else {
        printf("NO");
    }
}


void prime() {
    int N, n, divisor;
    scanf("%d", &N);
    // 包含N，所以是小于等于
    for(n = 2; n <= N; n++) {
       for (divisor = 2; divisor < n; divisor++) {
           if (n % divisor == 0) {
               //如果有其他数整除
               break;
           }
       }
       if (n == divisor) {
           printf("%d\n", n);
       }
    }

}

//输出n的阶层正方形
void output_square() {
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (j < n) {
                printf("%d ", i);
            } else {
                printf("%d\n", i);
            }
        }
    }
}
/*
 1 1 1 1
 2 2 2
 3 3
 4
 */
void triangle() {
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        for (int j = n - i; j > 0; j--) {
            if (j != n - i) {
                printf(" ");
            }
            printf("%d", i + 1);
        }
        printf("\n");
    }
}

/*
 4 3 2 1
 3 2 1
 2 1
 1
 */
void triangle1() {
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        for (int j = n - i; j > 0; j--) {
            if (j != n - i) {
                printf(" "); // 中间加空格
            }
            printf("%d", j);
        }
        printf("\n");
    }
}
/*
 1*1=1    1*2=2    1*3=3
 2*2=4    2*3=6
 3*3=9
 */
void printf_nine() {
    int n;
    scanf("%d", &n);
    for(int i = 1; i <= n; i++) {
        for(int j = i;j <= n; j++) {
            printf("%d*%d=%d",i, j, i*j);
            if (j != n) {
                printf("\t");
            }
        }
        printf("\n");
    }
}

void filtrate() {
    int n = 15;
    int mark[16] = {
        1, 1, 0, 0,
        0, 0, 0, 0,
        0, 0, 0, 0,
        0, 0, 0, 0
    };
    int c;
    int j;

    for (c = 2; c * c <= n; c++) {
        if (mark[c] != 1) {
            for (j = 2; j <= n / c; j++) {
                mark[c * j] = 1;
            }
        }
    }
    for (c = 2; c <= n; c++) {
        if (mark[c] != 1) {
            printf("%d\n", c);
        }
    }
}
