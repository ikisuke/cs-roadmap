#include <stdio.h>
#include <stdlib.h>

// ノードの定義
typedef struct TreeNode {
    int data;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

// 新しいノードを作成
TreeNode* create_node(int data) {
    TreeNode* new_node = (TreeNode*)malloc(sizeof(TreeNode));
    new_node->data = data;
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}

// ノードを挿入
TreeNode* insert(TreeNode* root, int data) {
    if (root == NULL) {
        return create_node(data);
    }
    
    if (data < root->data) {
        root->left = insert(root->left, data);
    } else if (data > root->data) {
        root->right = insert(root->right, data);
    }
    
    return root;
}

// 要素を検索
TreeNode* search(TreeNode* root, int data) {
    if (root == NULL || root->data == data) {
        return root;
    }
    
    if (data < root->data) {
        return search(root->left, data);
    }
    
    return search(root->right, data);
}

// 最小値のノードを見つける
TreeNode* find_min(TreeNode* root) {
    while (root->left != NULL) {
        root = root->left;
    }
    return root;
}

// ノードを削除
TreeNode* delete_node(TreeNode* root, int data) {
    if (root == NULL) {
        return root;
    }
    
    if (data < root->data) {
        root->left = delete_node(root->left, data);
    } else if (data > root->data) {
        root->right = delete_node(root->right, data);
    } else {
        // 削除するノードが見つかった
        if (root->left == NULL) {
            TreeNode* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            TreeNode* temp = root->left;
            free(root);
            return temp;
        }
        
        // 2つの子を持つ場合
        TreeNode* temp = find_min(root->right);
        root->data = temp->data;
        root->right = delete_node(root->right, temp->data);
    }
    
    return root;
}

// 中順走査（昇順）
void inorder_traversal(TreeNode* root) {
    if (root != NULL) {
        inorder_traversal(root->left);
        printf("%d ", root->data);
        inorder_traversal(root->right);
    }
}

// 前順走査
void preorder_traversal(TreeNode* root) {
    if (root != NULL) {
        printf("%d ", root->data);
        preorder_traversal(root->left);
        preorder_traversal(root->right);
    }
}

// 後順走査
void postorder_traversal(TreeNode* root) {
    if (root != NULL) {
        postorder_traversal(root->left);
        postorder_traversal(root->right);
        printf("%d ", root->data);
    }
}

// 木の高さを計算
int height(TreeNode* root) {
    if (root == NULL) {
        return -1;
    }
    
    int left_height = height(root->left);
    int right_height = height(root->right);
    
    return 1 + (left_height > right_height ? left_height : right_height);
}

int main() {
    TreeNode* root = NULL;
    
    root = insert(root, 50);
    root = insert(root, 30);
    root = insert(root, 70);
    root = insert(root, 20);
    root = insert(root, 40);
    root = insert(root, 60);
    root = insert(root, 80);
    
    printf("中順走査: ");
    inorder_traversal(root);
    printf("\n");
    
    printf("前順走査: ");
    preorder_traversal(root);
    printf("\n");
    
    printf("後順走査: ");
    postorder_traversal(root);
    printf("\n");
    
    printf("木の高さ: %d\n", height(root));
    
    TreeNode* found = search(root, 40);
    if (found != NULL) {
        printf("要素40が見つかりました\n");
    }
    
    root = delete_node(root, 20);
    printf("要素20削除後の中順走査: ");
    inorder_traversal(root);
    printf("\n");
    
    return 0;
}
