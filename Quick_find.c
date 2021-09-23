
#include <stdio.h>
#include <stdlib.h>

// 海贼oj 朋友圈问题
typedef struct UnionSet {
    int *color;
    int n;
} UnionSet;

UnionSet *init(int n) {
    UnionSet *u = (UnionSet *)malloc(sizeof(UnionSet));
    u->color = (int *)malloc(sizeof(int) * (n + 1)); //0号位置空出来
    u->n = n;
    for (int i = 1; i <= n; i++) {
        u->color[i] = i;
    }
    return u;
}

int find(UnionSet *u, int x) {
    return u->color[x];
}

int merge(UnionSet *u, int a, int b) {
    if (find(u, a) == find(u, b)) return 0;
    int color_a = u->color[a];
    for (int i = 1; i <= u->n; i++) {
//        if (u->color[i] == color_a) {
//            u->color[i] = u->color[b];
//        }
        // - 号不等于
        if (u->color[i] - color_a) continue;
        u->color[i] = u->color[b];
    }
    return 1;
}

void clear(UnionSet *u) {
    if (u == NULL) return;
    free(u->color);
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
