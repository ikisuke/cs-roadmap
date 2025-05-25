# キュー (Queue)

## 概要
FIFO（First In, First Out）方式のデータ構造

## 時間計算量
- enqueue: O(1)
- dequeue: O(1)
- front: O(1)

## 主要操作
- enqueue: 要素を追加
- dequeue: 要素を取り出し
- front: 先頭要素を確認
- isEmpty: キューが空かチェック

## 実装
- [queue.c](queue.c) - 配列ベースの実装
