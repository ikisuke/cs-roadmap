#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

// 最大ヒープ構造体
typedef struct {
    int data[MAX_SIZE];
    int size;
} MaxHeap;

// ヒープ初期化
void init_heap(MaxHeap* heap) {
    heap->size = 0;
}

// 親のインデックス
int parent(int i) {
    return (i - 1) / 2;
}

// 左の子のインデックス
int left_child(int i) {
    return 2 * i + 1;
}

// 右の子のインデックス
int right_child(int i) {
    return 2 * i + 2;
}

// 要素を交換
void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// 上向きヒープ化（挿入時）
void heapify_up(MaxHeap* heap, int index) {
    while (index > 0 && heap->data[parent(index)] < heap->data[index]) {
        swap(&heap->data[parent(index)], &heap->data[index]);
        index = parent(index);
    }
}

// 下向きヒープ化（削除時）
void heapify_down(MaxHeap* heap, int index) {
    int largest = index;
    int left = left_child(index);
    int right = right_child(index);
    
    // 左の子と比較
    if (left < heap->size && heap->data[left] > heap->data[largest]) {
        largest = left;
    }
    
    // 右の子と比較
    if (right < heap->size && heap->data[right] > heap->data[largest]) {
        largest = right;
    }
    
    // 最大値が現在のノードでない場合、交換して再帰
    if (largest != index) {
        swap(&heap->data[index], &heap->data[largest]);
        heapify_down(heap, largest);
    }
}

// 要素を挿入
void insert(MaxHeap* heap, int value) {
    if (heap->size >= MAX_SIZE) {
        printf("ヒープが満杯です\n");
        return;
    }
    
    heap->data[heap->size] = value;
    heapify_up(heap, heap->size);
    heap->size++;
}

// 最大値を取得（削除）
int extract_max(MaxHeap* heap) {
    if (heap->size <= 0) {
        printf("ヒープが空です\n");
        return -1;
    }
    
    int max = heap->data[0];
    heap->data[0] = heap->data[heap->size - 1];
    heap->size--;
    heapify_down(heap, 0);
    
    return max;
}

// 最大値を取得（削除しない）
int peek_max(MaxHeap* heap) {
    if (heap->size <= 0) {
        printf("ヒープが空です\n");
        return -1;
    }
    return heap->data[0];
}

// ヒープを表示
void print_heap(MaxHeap* heap) {
    printf("ヒープ: ");
    for (int i = 0; i < heap->size; i++) {
        printf("%d ", heap->data[i]);
    }
    printf("\n");
}

// 配列からヒープを構築
void build_heap(MaxHeap* heap, int arr[], int n) {
    if (n > MAX_SIZE) {
        printf("配列のサイズが大きすぎます\n");
        return;
    }
    
    heap->size = n;
    for (int i = 0; i < n; i++) {
        heap->data[i] = arr[i];
    }
    
    // 最後の非葉ノードから開始して下向きヒープ化
    for (int i = (n / 2) - 1; i >= 0; i--) {
        heapify_down(heap, i);
    }
}

int main() {
    MaxHeap heap;
    init_heap(&heap);
    
    // 要素を挿入
    insert(&heap, 10);
    insert(&heap, 20);
    insert(&heap, 15);
    insert(&heap, 40);
    insert(&heap, 50);
    insert(&heap, 100);
    insert(&heap, 25);
    
    printf("挿入後のヒープ:\n");
    print_heap(&heap);
    
    printf("最大値: %d\n", peek_max(&heap));
    
    printf("最大値を削除: %d\n", extract_max(&heap));
    print_heap(&heap);
    
    // 配列からヒープを構築
    printf("\n配列からヒープを構築:\n");
    int arr[] = {3, 9, 2, 1, 4, 5};
    int n = sizeof(arr) / sizeof(arr[0]);
    
    MaxHeap heap2;
    build_heap(&heap2, arr, n);
    print_heap(&heap2);
    
    return 0;
}
