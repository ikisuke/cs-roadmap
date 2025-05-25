#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// 通常の再帰（非効率）
long long fibonacci_naive(int n) {
    if (n <= 1) {
        return n;
    }
    return fibonacci_naive(n - 1) + fibonacci_naive(n - 2);
}

// メモ化（Top-down DP）
long long fibonacci_memo_helper(int n, long long* memo) {
    if (n <= 1) {
        return n;
    }
    
    if (memo[n] != -1) {
        return memo[n];
    }
    
    memo[n] = fibonacci_memo_helper(n - 1, memo) + fibonacci_memo_helper(n - 2, memo);
    return memo[n];
}

long long fibonacci_memo(int n) {
    long long* memo = (long long*)malloc((n + 1) * sizeof(long long));
    for (int i = 0; i <= n; i++) {
        memo[i] = -1;
    }
    
    long long result = fibonacci_memo_helper(n, memo);
    free(memo);
    return result;
}

// ボトムアップ（Bottom-up DP）
long long fibonacci_dp(int n) {
    if (n <= 1) {
        return n;
    }
    
    long long* dp = (long long*)malloc((n + 1) * sizeof(long long));
    dp[0] = 0;
    dp[1] = 1;
    
    for (int i = 2; i <= n; i++) {
        dp[i] = dp[i - 1] + dp[i - 2];
    }
    
    long long result = dp[n];
    free(dp);
    return result;
}

// 空間最適化版（O(1)空間）
long long fibonacci_optimized(int n) {
    if (n <= 1) {
        return n;
    }
    
    long long prev2 = 0;  // F(i-2)
    long long prev1 = 1;  // F(i-1)
    long long current;
    
    for (int i = 2; i <= n; i++) {
        current = prev1 + prev2;
        prev2 = prev1;
        prev1 = current;
    }
    
    return current;
}

// 実行時間を測定する関数
double measure_time(long long (*func)(int), int n) {
    clock_t start = clock();
    long long result = func(n);
    clock_t end = clock();
    
    double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("F(%d) = %lld, 実行時間: %f秒\n", n, result, time_taken);
    return time_taken;
}

// フィボナッチ数列を表示
void print_fibonacci_sequence(int n) {
    printf("フィボナッチ数列（最初の%d項）:\n", n);
    for (int i = 0; i < n; i++) {
        printf("F(%d) = %lld\n", i, fibonacci_optimized(i));
    }
    printf("\n");
}

int main() {
    int n = 10;
    
    // フィボナッチ数列を表示
    print_fibonacci_sequence(n);
    
    // 各手法の比較
    printf("=== 各手法の性能比較 ===\n");
    
    // 小さい値での比較
    n = 35;
    printf("\n通常の再帰（n=%d）:\n", n);
    if (n <= 40) {  // 大きすぎると時間がかかりすぎる
        measure_time(fibonacci_naive, n);
    } else {
        printf("n=%dは大きすぎるためスキップ\n", n);
    }
    
    printf("\nメモ化（n=%d）:\n", n);
    measure_time(fibonacci_memo, n);
    
    printf("\nボトムアップDP（n=%d）:\n", n);
    measure_time(fibonacci_dp, n);
    
    printf("\n空間最適化版（n=%d）:\n", n);
    measure_time(fibonacci_optimized, n);
    
    // 大きな値での比較
    n = 50;
    printf("\n=== 大きな値での比較（n=%d）===\n", n);
    
    printf("メモ化:\n");
    measure_time(fibonacci_memo, n);
    
    printf("ボトムアップDP:\n");
    measure_time(fibonacci_dp, n);
    
    printf("空間最適化版:\n");
    measure_time(fibonacci_optimized, n);
    
    return 0;
}
