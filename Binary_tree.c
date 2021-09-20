#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//结构定义
typedef struct Node {
    int data;
    struct Node *lchild, *rchild;
} Node;

typedef struct Tree {
    Node *root;
    int length; //节点个数
} Tree;

//结构操作
Node *getNewNode(int val) {
    Node *p = (Node *)malloc(sizeof(Node));
    p->data = val;
    p->lchild = p->rchild = NULL;
    return p;
}

Tree *getNewTree() {
    Tree *tree = (Tree *)malloc(sizeof(Tree));
    tree->root = NULL;
    tree->length = 0;
    return tree;
}

Node *insert_node(Node *root, int val, int *flag) {
    if (root == NULL) {
        *flag = 1;
        return getNewNode(val);
    }
    if (root->data == val) return root; //不会重复插入
    if (root->data > val) root->lchild = insert_node(root->lchild, val, flag); //递归插入左子树
    else root->rchild = insert_node(root->rchild, val, flag); //递归右子树
    return root;
}

// 二叉搜索树
void insert(Tree *tree, int val) {
    if (tree == NULL) return;
    int flag = 0; //标记位，是否插入成功
    tree->root = insert_node(tree->root, val, &flag);
    tree->length += flag;
    return;
}

void clear_node(Node *root) {
    if (root == NULL) return;
    clear_node(root->lchild); //递归释放左节点
    clear_node(root->rchild); //递归释放右节点
    free(root); //回溯回来释放当前根节点
    return;
}

void clear_tree(Tree *tree) {
    if (tree == NULL) return;
    clear_node(tree->root);
    free(tree);
    return;
}
void pre_order_node(Node *root) {
    if (root == NULL) return;
    printf("%d ", root->data);
    pre_order_node(root->lchild);
    pre_order_node(root->rchild);
    return;
}

void pre_order(Tree *tree) {
    if (tree == NULL) return;
    printf("pre_order :");
    pre_order_node(tree->root);
    printf("\n");
    return;
}

void in_order_node(Node *root) {
    if (root == NULL) return;
    in_order_node(root->lchild);
    printf("%d ", root->data);
    in_order_node(root->rchild);
    return;
}

void in_order(Tree *tree) {
    if (tree == NULL) return;
    printf("in_order :");
    in_order_node(tree->root);
    printf("\n");
    return;
}

void post_order_node(Node *root) {
    if (root == NULL) return;
    post_order_node(root->lchild);
    post_order_node(root->rchild);
    printf("%d ", root->data);
    return;
}

void post_order(Tree *tree) {
    if (tree == NULL) return;
    printf("post_order :");
    post_order_node(tree->root);
    printf("\n");
    return;
}

//A(B,C)
void output_node(Node *root) {
    if (root == NULL) return;
    printf("%d", root->data);
    if (root->lchild == NULL && root->rchild == NULL) return;
    printf("(");
    output_node(root->lchild);
    printf(",");
    output_node(root->rchild);
    printf(")");
    return;
}

//用广义表来表示
void output(Tree *tree) {
    if (tree == NULL) {
        return;
    }
    printf("tree(%d) : ", tree->length);
    output_node(tree->root);
    printf("\n");
    return;
}

int main() {
    srand((unsigned)time(0));
    Tree *tree = getNewTree();
#define MAX_OP 10
    for (int i = 0; i < MAX_OP; i++) {
        int val = rand() % 100;
        insert(tree, val);
        output(tree);
    }
    pre_order(tree);
    in_order(tree);
    post_order(tree);
    clear_tree(tree);
#undef MAX_OP
    return 0;
}
