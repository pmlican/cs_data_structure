#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*
 参考资料讲解：
 1. https://zq99299.github.io/dsalg-tutorial/dsalg-java-hsp/10/03.html#%E4%BB%A3%E7%A0%81%E5%AE%9E%E7%8E%B0
 2. https://zhuanlan.zhihu.com/p/134184036
 */

//树的线索化，当我们不用递归遍历二叉树的时候，可以用线索化，因为递归，包含了向下递进，然后回溯。因为一个节点可以同过，左右树指针可以向下，但回溯的话需要一个前继指针回到它的根节点，可以利用度为0的叶子节点多出来的边，进行回溯
#define NORMAL 0
#define THREAD 1

typedef struct Node {
    int data;
    struct Node *lchild, *rchild;
    int ltag, rtag; //左线索， 右线索
} Node;

Node *getNewNode(int val) {
    Node *p = (Node *)malloc(sizeof(Node));
    p->data = val;
    p->lchild = NULL;
    p->rchild = NULL;
    p->ltag = NORMAL;
    p->rchild = NORMAL;
    return p;
}

//二叉树搜索树方式插入，因为中序遍历是升序
//线索化比递归方式遍历效率高
//递归涉及到压栈弹栈，需要耗费空间，并且有可能栈溢出
Node *insert(Node *root, int val) {
    if (root == NULL) return getNewNode(val);
    if (root->data == val) return root;
    if (val < root->data) root->lchild = insert(root->lchild, val);
    else root->rchild = insert(root->rchild, val);
    return root;
}

//中序遍历添加线索化
void build_thread(Node *root) {
    if (root == NULL) return;
    static Node *pre = NULL; //前驱
    //中序：先左、中、右
    build_thread(root->lchild);
    //当lchild为空时，则设置为前驱节点
    if (root->lchild == NULL) {
        root->lchild = pre;
        root->ltag = THREAD;
    }
    // 因为要设置后继节点，只有回到自己的后继节点的时候，才能把自己设置为前一个的后继节点
    // 当前一个节点的 rchild 为空时，则需要自己是后继节点
    if (pre != NULL && pre->rchild == NULL) {
        pre->rchild = root;
        pre->rtag = THREAD;
    }
    // 利用前一个节点 pre, 因为根据中序的顺序，左、自己、后。那么自己一定是前一个的后继
    pre = root;
    //右递归
    build_thread(root->rchild);
    return;
}

Node *most_left(Node *p) {
    while (p != NULL && p->ltag == NORMAL && p->lchild != NULL) {
        p = p->lchild;
    }
    return p;
}

void output(Node *root) {
    Node *p = most_left(root);
    while (p != NULL) {
        printf("%d ", p->data);
        if (p->rtag == THREAD) {
            p = p->rchild;
        } else {
            p = most_left(p->rchild);
        }
    }
    return;
}

void output1(Node *root) {
    //之前的递归中序不能用了，因为左右节点再也不为空了
    Node *node = root;
    while (node != NULL) {
        // 中序：左，中，右
        //先找到左边第一个线索化节点
        while (node->ltag == 0) {
            node = node->lchild;
        }
        //找到这个线索化节点后，打印
        printf("%d ", node->data);
        // 如果该节点右子节点也是线索化节点，则打印它
        while (node->rtag == 1) {
            node = node->rchild;
            printf("%d ", node->data);
        }
        //到达这里，就说明遇到一个不是线索化节点
        // 按中序的顺序来看，这里应该处理右侧了
        node = node->rchild;
    }
}


void in_order(Node *root) {
    if (root == NULL) return;
    if (root->ltag == NORMAL) in_order(root->lchild);
    printf("%d ", root->data);
    if (root->rtag == NORMAL) in_order(root->rchild);
    return;
}

void clear(Node *root) {
    if (root == NULL) return;
    if (root->ltag == NORMAL) clear(root->lchild);
    if (root->rtag == NORMAL) clear(root->rchild);
    free(root);
    return;
}

int main() {
    srand(time(0));
#define MAX_OP 20
    Node *root = NULL;
    for (int i = 0; i < MAX_OP; i++) {
        int val = rand() % 100;
        root = insert(root, val);
    }
    build_thread(root);
    output1(root), printf("\n");  // 线索化遍历
    in_order(root), printf("\n"); //递归遍历
    clear(root);
    return 0;
}
