#include <stdio.h>
#include <stdlib.h>

// 配列の基本操作
void print_array(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

// 線形探索
int linear_search(int arr[], int size, int target) {
    for (int i = 0; i < size; i++) {
        if (arr[i] == target) {
            return i;  // インデックスを返す
        }
    }
    return -1;  // 見つからない場合
}

// 配列の挿入（最後に追加）
void insert_at_end(int arr[], int *size, int element, int capacity) {
    if (*size < capacity) {
        arr[*size] = element;
        (*size)++;
    } else {
        printf("配列が満杯です\n");
    }
}

int main() {
    int arr[10] = {1, 3, 5, 7, 9};
    int size = 5;
    
    printf("初期配列: ");
    print_array(arr, size);
    
    // 要素の検索
    int index = linear_search(arr, size, 5);
    if (index != -1) {
        printf("要素5はインデックス%dにあります\n", index);
    }
    
    // 要素の追加
    insert_at_end(arr, &size, 11, 10);
    printf("要素追加後: ");
    print_array(arr, size);
    
    return 0;
}
