#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_SIZE 100

// キュー構造体
typedef struct {
    int items[MAX_SIZE];
    int front;
    int rear;
    int count;
} Queue;

// キュー初期化
void init_queue(Queue* queue) {
    queue->front = 0;
    queue->rear = -1;
    queue->count = 0;
}

// キューが空かチェック
bool is_empty(Queue* queue) {
    return queue->count == 0;
}

// キューが満杯かチェック
bool is_full(Queue* queue) {
    return queue->count == MAX_SIZE;
}

// エンキュー操作
void enqueue(Queue* queue, int item) {
    if (is_full(queue)) {
        printf("キューオーバーフロー\n");
        return;
    }
    
    queue->rear = (queue->rear + 1) % MAX_SIZE;
    queue->items[queue->rear] = item;
    queue->count++;
}

// デキュー操作
int dequeue(Queue* queue) {
    if (is_empty(queue)) {
        printf("キューアンダーフロー\n");
        return -1;
    }
    
    int item = queue->items[queue->front];
    queue->front = (queue->front + 1) % MAX_SIZE;
    queue->count--;
    return item;
}

// 先頭要素を確認
int front(Queue* queue) {
    if (is_empty(queue)) {
        printf("キューが空です\n");
        return -1;
    }
    return queue->items[queue->front];
}

// キューを表示
void print_queue(Queue* queue) {
    if (is_empty(queue)) {
        printf("キューが空です\n");
        return;
    }
    
    printf("キュー: ");
    for (int i = 0; i < queue->count; i++) {
        int index = (queue->front + i) % MAX_SIZE;
        printf("%d ", queue->items[index]);
    }
    printf("\n");
}

int main() {
    Queue queue;
    init_queue(&queue);
    
    enqueue(&queue, 10);
    enqueue(&queue, 20);
    enqueue(&queue, 30);
    
    print_queue(&queue);
    
    printf("先頭要素: %d\n", front(&queue));
    
    printf("デキュー: %d\n", dequeue(&queue));
    print_queue(&queue);
    
    return 0;
}
