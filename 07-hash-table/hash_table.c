#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 10

// ハッシュテーブルのエントリ
typedef struct Entry {
    char* key;
    int value;
    struct Entry* next;  // チェイン法用
} Entry;

// ハッシュテーブル
typedef struct {
    Entry* buckets[TABLE_SIZE];
} HashTable;

// ハッシュ関数（単純な除算法）
int hash_function(const char* key) {
    int hash = 0;
    for (int i = 0; key[i] != '\0'; i++) {
        hash = (hash + key[i]) % TABLE_SIZE;
    }
    return hash;
}

// ハッシュテーブル初期化
void init_hash_table(HashTable* table) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        table->buckets[i] = NULL;
    }
}

// 新しいエントリを作成
Entry* create_entry(const char* key, int value) {
    Entry* entry = (Entry*)malloc(sizeof(Entry));
    entry->key = (char*)malloc(strlen(key) + 1);
    strcpy(entry->key, key);
    entry->value = value;
    entry->next = NULL;
    return entry;
}

// 挿入操作
void insert(HashTable* table, const char* key, int value) {
    int index = hash_function(key);
    Entry* entry = table->buckets[index];
    
    // 既存のキーがあるかチェック
    while (entry != NULL) {
        if (strcmp(entry->key, key) == 0) {
            entry->value = value;  // 値を更新
            return;
        }
        entry = entry->next;
    }
    
    // 新しいエントリを追加（チェインの先頭に）
    Entry* new_entry = create_entry(key, value);
    new_entry->next = table->buckets[index];
    table->buckets[index] = new_entry;
}

// 検索操作
int search(HashTable* table, const char* key) {
    int index = hash_function(key);
    Entry* entry = table->buckets[index];
    
    while (entry != NULL) {
        if (strcmp(entry->key, key) == 0) {
            return entry->value;
        }
        entry = entry->next;
    }
    
    return -1;  // 見つからない場合
}

// 削除操作
void delete_entry(HashTable* table, const char* key) {
    int index = hash_function(key);
    Entry* entry = table->buckets[index];
    Entry* prev = NULL;
    
    while (entry != NULL) {
        if (strcmp(entry->key, key) == 0) {
            if (prev == NULL) {
                table->buckets[index] = entry->next;
            } else {
                prev->next = entry->next;
            }
            free(entry->key);
            free(entry);
            return;
        }
        prev = entry;
        entry = entry->next;
    }
}

// ハッシュテーブルを表示
void print_hash_table(HashTable* table) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        printf("バケット[%d]: ", i);
        Entry* entry = table->buckets[i];
        
        while (entry != NULL) {
            printf("(%s: %d) -> ", entry->key, entry->value);
            entry = entry->next;
        }
        printf("NULL\n");
    }
}

// ハッシュテーブルを解放
void free_hash_table(HashTable* table) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        Entry* entry = table->buckets[i];
        while (entry != NULL) {
            Entry* temp = entry;
            entry = entry->next;
            free(temp->key);
            free(temp);
        }
    }
}

// ロードファクターを計算
float load_factor(HashTable* table) {
    int count = 0;
    for (int i = 0; i < TABLE_SIZE; i++) {
        Entry* entry = table->buckets[i];
        while (entry != NULL) {
            count++;
            entry = entry->next;
        }
    }
    return (float)count / TABLE_SIZE;
}

int main() {
    HashTable table;
    init_hash_table(&table);
    
    insert(&table, "apple", 10);
    insert(&table, "banana", 20);
    insert(&table, "orange", 30);
    insert(&table, "grape", 40);
    insert(&table, "kiwi", 50);
    
    printf("ハッシュテーブル:\n");
    print_hash_table(&table);
    
    int value = search(&table, "banana");
    if (value != -1) {
        printf("\nbananaの値: %d\n", value);
    }
    
    printf("ロードファクター: %.2f\n\n", load_factor(&table));
    
    delete_entry(&table, "orange");
    printf("orange削除後:\n");
    print_hash_table(&table);
    
    free_hash_table(&table);
    return 0;
}
