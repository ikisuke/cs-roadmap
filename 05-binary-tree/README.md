# 二分木 (Binary Tree)

## 概要
各ノードが最大2つの子（左の子、右の子）を持つ木構造

## 二分探索木 (Binary Search Tree)
左の子 < 親 < 右の子 の性質を持つ

## 時間計算量 (平均)
- 検索: O(log n)
- 挿入: O(log n)
- 削除: O(log n)

## 走査方法
- 前順走査 (Preorder): 根 → 左 → 右
- 中順走査 (Inorder): 左 → 根 → 右 (昇順)
- 後順走査 (Postorder): 左 → 右 → 根

## 実装
- [binary_search_tree.c](binary_search_tree.c) - 二分探索木の実装
