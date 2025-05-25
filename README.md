# データ構造とアルゴリズム教科書

## 目次

1. [データ構造](#データ構造)
   - [配列](#配列)
   - [連結リスト](#連結リスト)
   - [スタック](#スタック)
   - [キュー](#キュー)
   - [二分探索木](#二分探索木)
   - [ハッシュテーブル](#ハッシュテーブル)

2. [アルゴリズム](#アルゴリズム)
   - [ソート](#ソート)
   - [探索](#探索)
   - [動的プログラミング](#動的プログラミング)
   - [グラフアルゴリズム](#グラフアルゴリズム)

## データ構造

### 配列

**概要**: 同じ型の要素を連続したメモリ領域に格納するデータ構造

**時間計算量**:
- アクセス: O(1)
- 検索: O(n)
- 挿入: O(n)
- 削除: O(n)

**実装例**: [array.c](examples/array.c)

### 連結リスト

**概要**: ノードがポインタで連結されたデータ構造

**時間計算量**:
- アクセス: O(n)
- 検索: O(n)
- 挿入: O(1)
- 削除: O(1)

**実装例**: [linked_list.c](examples/linked_list.c)

### スタック

**概要**: LIFO（Last In, First Out）方式のデータ構造

**主要操作**:
- push: 要素を追加
- pop: 要素を取り出し
- top: 先頭要素を確認

**実装例**: [stack.c](examples/stack.c)

### キュー

**概要**: FIFO（First In, First Out）方式のデータ構造

**主要操作**:
- enqueue: 要素を追加
- dequeue: 要素を取り出し
- front: 先頭要素を確認

**実装例**: [queue.c](examples/queue.c)

### 二分探索木

**概要**: 各ノードが最大2つの子を持ち、左の子は親より小さく、右の子は親より大きい

**時間計算量**（平均）:
- 検索: O(log n)
- 挿入: O(log n)
- 削除: O(log n)

**実装例**: [binary_search_tree.c](examples/binary_search_tree.c)

### ハッシュテーブル

**概要**: ハッシュ関数を使用してキーを配列のインデックスにマップ

**時間計算量**（平均）:
- 検索: O(1)
- 挿入: O(1)
- 削除: O(1)

**実装例**: [hash_table.c](examples/hash_table.c)

## アルゴリズム

### ソート

#### バブルソート
- **時間計算量**: O(n²)
- **空間計算量**: O(1)
- **実装例**: [bubble_sort.c](examples/bubble_sort.c)

#### マージソート
- **時間計算量**: O(n log n)
- **空間計算量**: O(n)
- **実装例**: [merge_sort.c](examples/merge_sort.c)

#### クイックソート
- **時間計算量**: O(n log n) 平均, O(n²) 最悪
- **空間計算量**: O(log n)
- **実装例**: [quick_sort.c](examples/quick_sort.c)

### 探索

#### 線形探索
- **時間計算量**: O(n)
- **実装例**: [linear_search.c](examples/linear_search.c)

#### 二分探索
- **時間計算量**: O(log n)
- **前提条件**: ソート済み配列
- **実装例**: [binary_search.c](examples/binary_search.c)

### 動的プログラミング

**概要**: 問題を部分問題に分割し、結果を記録して再利用

**例**:
- フィボナッチ数列
- ナップサック問題
- 最長共通部分列

**実装例**: [dynamic_programming.c](examples/dynamic_programming.c)

### グラフアルゴリズム

#### 深さ優先探索（DFS）
- **時間計算量**: O(V + E)
- **実装例**: [dfs.c](examples/dfs.c)

#### 幅優先探索（BFS）
- **時間計算量**: O(V + E)
- **実装例**: [bfs.c](examples/bfs.c)

#### ダイクストラ法
- **用途**: 最短経路問題
- **時間計算量**: O((V + E) log V)
- **実装例**: [dijkstra.c](examples/dijkstra.c)

## 参考資料

- Thomas H. Cormen et al. "Introduction to Algorithms"
- Robert Sedgewick "Algorithms in C"
- Donald E. Knuth "The Art of Computer Programming"
