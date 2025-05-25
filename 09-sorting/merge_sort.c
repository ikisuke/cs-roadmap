#include <stdio.h>
#include <stdlib.h>

// 配列をマージする関数
void merge(int arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    
    // 一時配列を作成
    int* left_arr = (int*)malloc(n1 * sizeof(int));
    int* right_arr = (int*)malloc(n2 * sizeof(int));
    
    // データを一時配列にコピー
    for (int i = 0; i < n1; i++) {
        left_arr[i] = arr[left + i];
    }
    for (int j = 0; j < n2; j++) {
        right_arr[j] = arr[mid + 1 + j];
    }
    
    // 一時配列をマージして元の配列に戻す
    int i = 0, j = 0, k = left;
    
    while (i < n1 && j < n2) {
        if (left_arr[i] <= right_arr[j]) {
            arr[k] = left_arr[i];
            i++;
        } else {
            arr[k] = right_arr[j];
            j++;
        }
        k++;
    }
    
    // 残りの要素をコピー
    while (i < n1) {
        arr[k] = left_arr[i];
        i++;
        k++;
    }
    
    while (j < n2) {
        arr[k] = right_arr[j];
        j++;
        k++;
    }
    
    free(left_arr);
    free(right_arr);
}

// マージソート本体
void merge_sort(int arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        
        // 左半分をソート
        merge_sort(arr, left, mid);
        
        // 右半分をソート
        merge_sort(arr, mid + 1, right);
        
        // マージ
        merge(arr, left, mid, right);
    }
}

// 配列を表示
void print_array(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

// マージソートのステップを可視化
void merge_sort_visual(int arr[], int left, int right, int depth) {
    if (left < right) {
        // インデントでレベルを表示
        for (int i = 0; i < depth; i++) {
            printf("  ");
        }
        printf("分割: [%d..%d] ", left, right);
        for (int i = left; i <= right; i++) {
            printf("%d ", arr[i]);
        }
        printf("\n");
        
        int mid = left + (right - left) / 2;
        
        merge_sort_visual(arr, left, mid, depth + 1);
        merge_sort_visual(arr, mid + 1, right, depth + 1);
        
        merge(arr, left, mid, right);
        
        // マージ後の結果を表示
        for (int i = 0; i < depth; i++) {
            printf("  ");
        }
        printf("マージ: [%d..%d] ", left, right);
        for (int i = left; i <= right; i++) {
            printf("%d ", arr[i]);
        }
        printf("\n");
    }
}

int main() {
    int arr[] = {64, 34, 25, 12, 22, 11, 90};
    int n = sizeof(arr) / sizeof(arr[0]);
    
    printf("ソート前: ");
    print_array(arr, n);
    
    merge_sort(arr, 0, n - 1);
    
    printf("ソート後: ");
    print_array(arr, n);
    
    // 可視化バージョン
    printf("\n=== マージソートの可視化 ===\n");
    int arr2[] = {38, 27, 43, 3, 9, 82, 10};
    int n2 = sizeof(arr2) / sizeof(arr2[0]);
    
    printf("初期配列: ");
    print_array(arr2, n2);
    printf("\n");
    
    merge_sort_visual(arr2, 0, n2 - 1, 0);
    
    printf("\n最終結果: ");
    print_array(arr2, n2);
    
    return 0;
}
