#include <stdio.h>

// 二分探索（反復版）
int binary_search_iterative(int arr[], int n, int target) {
    int left = 0;
    int right = n - 1;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        if (arr[mid] == target) {
            return mid;
        }
        
        if (arr[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    
    return -1;  // 見つからない場合
}

// 二分探索（再帰版）
int binary_search_recursive(int arr[], int left, int right, int target) {
    if (left <= right) {
        int mid = left + (right - left) / 2;
        
        if (arr[mid] == target) {
            return mid;
        }
        
        if (arr[mid] > target) {
            return binary_search_recursive(arr, left, mid - 1, target);
        }
        
        return binary_search_recursive(arr, mid + 1, right, target);
    }
    
    return -1;
}

int main() {
    int arr[] = {2, 5, 8, 12, 16, 23, 38, 45, 56, 67, 78};
    int n = sizeof(arr) / sizeof(arr[0]);
    int target = 23;
    
    printf("ソート済み配列: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    
    // 反復版
    int result1 = binary_search_iterative(arr, n, target);
    if (result1 != -1) {
        printf("反復版: 要素%dはインデックス%dで見つかりました\n", target, result1);
    } else {
        printf("反復版: 要素%dは見つかりませんでした\n", target);
    }
    
    // 再帰版
    int result2 = binary_search_recursive(arr, 0, n - 1, target);
    if (result2 != -1) {
        printf("再帰版: 要素%dはインデックス%dで見つかりました\n", target, result2);
    } else {
        printf("再帰版: 要素%dは見つかりませんでした\n", target);
    }
    
    return 0;
}
