
#include <stdio.h>
#include <stdlib.h>
// 按秩优化去掉，直接路径压缩，省掉空间
//#define swap(a, b) {\
//__typeof(a) __temp = a;\
//a = b; b = __temp;\
//}

// 海贼oj 朋友圈问题
typedef struct UnionSet {
    int *father;
//    int *size; //size 按秩优化
    int n;
} UnionSet;

UnionSet *init(int n) {
    UnionSet *u = (UnionSet *)malloc(sizeof(UnionSet));
    u->father = (int *)malloc(sizeof(int) * (n + 1)); //0号位置空出来
//    u->size = (int *)malloc(sizeof(int) * (n + 1)); //优化增加
    u->n = n;
    for (int i = 1; i <= n; i++) {
        u->father[i] = i;
//        u->size[i] = 1;  //优化增加
    }
    return u;
}

int find(UnionSet *u, int x) {
//    if (u->father[x] == x) return x;
////    return find(u, u->father[x]);
//    //路径压缩优化
//    return u->father[x] = find(u, u->father[x]);
    //优化成一行
    return u->father[x] = (u->father[x] == x ? x : find(u, u->father[x]));
}

int merge(UnionSet *u, int a, int b) {
    int fa = find(u, a), fb = find(u, b);
    if (fa == fb) return 0;
    //下列四步优化
//    u->father[fa] = fb;
//    if (u->size[fa] < u->size[fb]) swap(fa, fb);
    u->father[fb] = fa;
//    u->size[fa] += u->size[fb];
    return 1;
}

void clear(UnionSet *u) {
    if (u == NULL) return;
    free(u->father);
//    free(u->size); //优化增加
    free(u);
    return;
}


/*
 6 5
 1 1 2
 2 1 3
 1 2 4
 1 4 3
 2 1 3
 No
 Yes

 1948ms
 220ms
 152ms
 */
int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    UnionSet *u = init(n);
    for (int i = 0; i < m; i++) {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        switch (a) {
            case 1:
                merge(u, b, c);
                break;
            case 2:
                printf("%s\n", find(u, b) == find(u, c) ? "Yes" : "NO");
                break;
            default:
                break;
        }
    }
    clear(u);
    return 0;
}
