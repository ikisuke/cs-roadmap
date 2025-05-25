#include <stdio.h>
#include <stdlib.h>

// 活動の構造体
typedef struct {
    int start;
    int finish;
    int id;
} Activity;

// 活動を終了時間でソートするための比較関数
int compare_activities(const void* a, const void* b) {
    Activity* act1 = (Activity*)a;
    Activity* act2 = (Activity*)b;
    return act1->finish - act2->finish;
}

// 活動選択問題（貪欲法）
void activity_selection_greedy(Activity activities[], int n) {
    // 終了時間でソート
    qsort(activities, n, sizeof(Activity), compare_activities);
    
    printf("=== 貪欲法による活動選択 ===\n");
    printf("選択された活動:\n");
    
    // 最初の活動を選択
    int selected_count = 1;
    int last_selected = 0;
    printf("活動%d: [%d, %d]\n", 
           activities[0].id, activities[0].start, activities[0].finish);
    
    // 貪欲選択：前の活動と重複しない最も早く終わる活動を選択
    for (int i = 1; i < n; i++) {
        if (activities[i].start >= activities[last_selected].finish) {
            printf("活動%d: [%d, %d]\n", 
                   activities[i].id, activities[i].start, activities[i].finish);
            last_selected = i;
            selected_count++;
        }
    }
    
    printf("選択された活動数: %d\n\n", selected_count);
}

// 動的プログラミングによる活動選択（比較用）
int activity_selection_dp(Activity activities[], int n) {
    // 終了時間でソート済みと仮定
    int* dp = (int*)calloc(n, sizeof(int));
    int* parent = (int*)malloc(n * sizeof(int));
    
    dp[0] = 1;
    parent[0] = -1;
    
    for (int i = 1; i < n; i++) {
        // i番目の活動を選ばない場合
        dp[i] = dp[i-1];
        parent[i] = i-1;
        
        // i番目の活動を選ぶ場合
        int include = 1;
        int latest_compatible = -1;
        
        // i番目の活動と重複しない最新の活動を探す
        for (int j = i-1; j >= 0; j--) {
            if (activities[j].finish <= activities[i].start) {
                include += dp[j];
                latest_compatible = j;
                break;
            }
        }
        
        // より良い解が見つかった場合
        if (include > dp[i]) {
            dp[i] = include;
            parent[i] = latest_compatible;
        }
    }
    
    int result = dp[n-1];
    
    // 選択された活動を復元
    printf("=== 動的プログラミングによる活動選択 ===\n");
    printf("最大活動数: %d\n", result);
    
    // 経路復元（簡略化）
    printf("（詳細な経路復元は省略）\n\n");
    
    free(dp);
    free(parent);
    return result;
}

// フラクショナルナップサック問題
typedef struct {
    int weight;
    int value;
    double ratio;  // 価値密度
    int id;
} Item;

int compare_items(const void* a, const void* b) {
    Item* item1 = (Item*)a;
    Item* item2 = (Item*)b;
    // 価値密度の降順でソート
    if (item1->ratio < item2->ratio) return 1;
    if (item1->ratio > item2->ratio) return -1;
    return 0;
}

double fractional_knapsack(Item items[], int n, int capacity) {
    // 価値密度を計算
    for (int i = 0; i < n; i++) {
        items[i].ratio = (double)items[i].value / items[i].weight;
    }
    
    // 価値密度でソート
    qsort(items, n, sizeof(Item), compare_items);
    
    printf("=== フラクショナルナップサック問題 ===\n");
    printf("容量: %d\n", capacity);
    printf("アイテム（価値密度順）:\n");
    for (int i = 0; i < n; i++) {
        printf("アイテム%d: 重さ=%d, 価値=%d, 密度=%.2f\n", 
               items[i].id, items[i].weight, items[i].value, items[i].ratio);
    }
    
    double total_value = 0.0;
    int current_weight = 0;
    
    printf("\n選択プロセス:\n");
    for (int i = 0; i < n; i++) {
        if (current_weight + items[i].weight <= capacity) {
            // アイテム全体を追加
            current_weight += items[i].weight;
            total_value += items[i].value;
            printf("アイテム%d: 100%% 追加（価値: %d）\n", 
                   items[i].id, items[i].value);
        } else {
            // アイテムの一部を追加
            int remaining_capacity = capacity - current_weight;
            if (remaining_capacity > 0) {
                double fraction = (double)remaining_capacity / items[i].weight;
                total_value += items[i].value * fraction;
                printf("アイテム%d: %.1f%% 追加（価値: %.1f）\n", 
                       items[i].id, fraction * 100, items[i].value * fraction);
                current_weight = capacity;
            }
            break;
        }
    }
    
    printf("最大価値: %.2f\n\n", total_value);
    return total_value;
}

int main() {
    // 活動選択問題の例
    Activity activities[] = {
        {1, 4, 1}, {3, 5, 2}, {0, 6, 3}, {5, 7, 4},
        {3, 9, 5}, {5, 9, 6}, {6, 10, 7}, {8, 11, 8},
        {8, 12, 9}, {2, 14, 10}, {12, 16, 11}
    };
    int n_activities = sizeof(activities) / sizeof(activities[0]);
    
    printf("元の活動リスト:\n");
    for (int i = 0; i < n_activities; i++) {
        printf("活動%d: [%d, %d]\n", 
               activities[i].id, activities[i].start, activities[i].finish);
    }
    printf("\n");
    
    activity_selection_greedy(activities, n_activities);
    activity_selection_dp(activities, n_activities);
    
    // フラクショナルナップサック問題の例
    Item items[] = {
        {20, 100, 0, 1}, {30, 120, 0, 2}, {10, 60, 0, 3}
    };
    int n_items = sizeof(items) / sizeof(items[0]);
    int capacity = 50;
    
    fractional_knapsack(items, n_items, capacity);
    
    return 0;
}
