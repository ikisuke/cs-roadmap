#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_SIZE 100

// スタック構造体
typedef struct {
    int items[MAX_SIZE];
    int top;
} Stack;

// スタック初期化
void init_stack(Stack* stack) {
    stack->top = -1;
}

// スタックが空かチェック
bool is_empty(Stack* stack) {
    return stack->top == -1;
}

// スタックが満杯かチェック
bool is_full(Stack* stack) {
    return stack->top == MAX_SIZE - 1;
}

// プッシュ操作
void push(Stack* stack, int item) {
    if (is_full(stack)) {
        printf("スタックオーバーフロー\n");
        return;
    }
    stack->items[++stack->top] = item;
}

// ポップ操作
int pop(Stack* stack) {
    if (is_empty(stack)) {
        printf("スタックアンダーフロー\n");
        return -1;
    }
    return stack->items[stack->top--];
}

// 先頭要素を確認
int peek(Stack* stack) {
    if (is_empty(stack)) {
        printf("スタックが空です\n");
        return -1;
    }
    return stack->items[stack->top];
}

// スタックを表示
void print_stack(Stack* stack) {
    if (is_empty(stack)) {
        printf("スタックが空です\n");
        return;
    }
    
    printf("スタック: ");
    for (int i = stack->top; i >= 0; i--) {
        printf("%d ", stack->items[i]);
    }
    printf("\n");
}

int main() {
    Stack stack;
    init_stack(&stack);
    
    push(&stack, 10);
    push(&stack, 20);
    push(&stack, 30);
    
    print_stack(&stack);
    
    printf("先頭要素: %d\n", peek(&stack));
    
    printf("ポップ: %d\n", pop(&stack));
    print_stack(&stack);
    
    return 0;
}
