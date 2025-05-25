#include <stdio.h>
#include <stdlib.h>

// ノードの定義
typedef struct Node {
    int data;
    struct Node* next;
} Node;

// 新しいノードを作成
Node* create_node(int data) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

// リストの先頭に挿入
void insert_at_head(Node** head, int data) {
    Node* new_node = create_node(data);
    new_node->next = *head;
    *head = new_node;
}

// リストの末尾に挿入
void insert_at_tail(Node** head, int data) {
    Node* new_node = create_node(data);
    
    if (*head == NULL) {
        *head = new_node;
        return;
    }
    
    Node* current = *head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = new_node;
}

// 要素を削除
void delete_node(Node** head, int data) {
    if (*head == NULL) return;
    
    if ((*head)->data == data) {
        Node* temp = *head;
        *head = (*head)->next;
        free(temp);
        return;
    }
    
    Node* current = *head;
    while (current->next != NULL && current->next->data != data) {
        current = current->next;
    }
    
    if (current->next != NULL) {
        Node* temp = current->next;
        current->next = current->next->next;
        free(temp);
    }
}

// リストを表示
void print_list(Node* head) {
    Node* current = head;
    while (current != NULL) {
        printf("%d -> ", current->data);
        current = current->next;
    }
    printf("NULL\n");
}

// メモリ解放
void free_list(Node* head) {
    while (head != NULL) {
        Node* temp = head;
        head = head->next;
        free(temp);
    }
}

int main() {
    Node* head = NULL;
    
    insert_at_tail(&head, 1);
    insert_at_tail(&head, 2);
    insert_at_tail(&head, 3);
    insert_at_head(&head, 0);
    
    printf("リスト: ");
    print_list(head);
    
    delete_node(&head, 2);
    printf("要素2削除後: ");
    print_list(head);
    
    free_list(head);
    return 0;
}
