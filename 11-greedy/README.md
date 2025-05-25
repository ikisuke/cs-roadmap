# 貪欲法 (Greedy Algorithms)

## 概要
各段階で局所的に最適な選択をして、全体的な最適解を目指すアルゴリズム設計手法

## 特徴
- **局所最適性**: 各段階で最良の選択をする
- **不可逆性**: 一度決めた選択は変更しない
- **効率性**: 多くの場合、単純で高速

## 貪欲法が有効な条件
- **貪欲選択性**: 局所最適選択が全体最適解に含まれる
- **最適部分構造**: 問題の最適解が部分問題の最適解を含む

## 典型的な問題
- 活動選択問題（Activity Selection）
- フラクショナルナップサック問題
- ハフマン符号化
- 最小全域木（Kruskal法、Prim法）
- 最短経路（ダイクストラ法）
- コイン問題（特定の硬貨システム）

## 実装
- [activity_selection.c](activity_selection.c) - 活動選択問題
- [fractional_knapsack.c](fractional_knapsack.c) - フラクショナルナップサック
- [coin_change_greedy.c](coin_change_greedy.c) - 貪欲法によるコイン問題
- [huffman.c](huffman.c) - ハフマン符号化
