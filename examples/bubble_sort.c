#include <stdio.h>

// バブルソート
void bubble_sort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int swapped = 0;
        
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                // 要素を交換
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                swapped = 1;
            }
        }
        
        // 交換が発生しなかった場合、配列はソート済み
        if (swapped == 0) {
            break;
        }
    }
}

void print_array(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    int arr[] = {64, 34, 25, 12, 22, 11, 90};
    int n = sizeof(arr) / sizeof(arr[0]);
    
    printf("ソート前: ");
    print_array(arr, n);
    
    bubble_sort(arr, n);
    
    printf("ソート後: ");
    print_array(arr, n);
    
    return 0;
}
