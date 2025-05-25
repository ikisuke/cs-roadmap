# データ構造とアルゴリズム教科書

## 目次

### データ構造
1. [配列 (Arrays)](01-arrays/)
2. [連結リスト (Linked Lists)](02-linked-list/)
3. [スタック (Stack)](03-stack/)
4. [キュー (Queue)](04-queue/)
5. [二分木 (Binary Tree)](05-binary-tree/)
6. [ヒープ (Heap)](06-heap/)
7. [ハッシュテーブル (Hash Table)](07-hash-table/)
8. [グラフ (Graph)](08-graph/)

### アルゴリズム
9. [ソート (Sorting)](09-sorting/)
10. [動的プログラミング (Dynamic Programming)](10-dynamic-programming/)
11. [貪欲法 (Greedy Algorithms)](11-greedy/)

## 概要

この教科書では、コンピュータサイエンスの基礎となるデータ構造とアルゴリズムを体系的に学習できます。各章には理論的な説明とC言語による実装例が含まれています。

## 学習の進め方

1. **基本データ構造**: 01-arrays から 04-queue まで順番に学習
2. **高度なデータ構造**: 05-binary-tree から 08-graph を学習
3. **アルゴリズム**: 09-sorting から 11-greedy を学習

各ディレクトリには以下が含まれています：
- `README.md`: 理論的説明と時間計算量
- `*.c`: 実装例とサンプルコード

## 時間計算量早見表

| データ構造 | 検索 | 挿入 | 削除 |
|------------|------|------|------|
| 配列 | O(n) | O(n) | O(n) |
| 連結リスト | O(n) | O(1) | O(1) |
| スタック | - | O(1) | O(1) |
| キュー | - | O(1) | O(1) |
| 二分探索木 | O(log n) | O(log n) | O(log n) |
| ハッシュテーブル | O(1) | O(1) | O(1) |

| ソートアルゴリズム | 平均 | 最悪 | 空間 |
|-------------------|------|------|------|
| バブルソート | O(n²) | O(n²) | O(1) |
| マージソート | O(n log n) | O(n log n) | O(n) |
| クイックソート | O(n log n) | O(n²) | O(log n) |
| ヒープソート | O(n log n) | O(n log n) | O(1) |

## コンパイルと実行

```bash
# 基本的なコンパイル
gcc filename.c -o output

# 数学ライブラリを使用する場合
gcc filename.c -o output -lm

# 実行
./output
```

## 参考資料

- Thomas H. Cormen et al. "Introduction to Algorithms"
- Robert Sedgewick "Algorithms in C"
- Donald E. Knuth "The Art of Computer Programming"

## Legacy Examples

従来のexamplesディレクトリも残されています：
- [examples/](examples/) - 初期バージョンの実装例
