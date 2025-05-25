# アセンブリ言語 (Assembly Language)

## 概要
機械語に最も近い低レベルプログラミング言語

## 特徴
- **直接ハードウェア制御**: CPUレジスタとメモリを直接操作
- **高速実行**: オーバーヘッドが最小限
- **プラットフォーム依存**: CPU アーキテクチャに特化

## x86-64 アーキテクチャ

### 汎用レジスタ
- **RAX**: アキュムレータ（戻り値）
- **RBX**: ベースレジスタ
- **RCX**: カウンタ
- **RDX**: データレジスタ
- **RSI**: ソースインデックス
- **RDI**: デスティネーションインデックス
- **RSP**: スタックポインタ
- **RBP**: ベースポインタ
- **R8-R15**: 追加汎用レジスタ

### 基本命令
- **MOV**: データ移動
- **ADD/SUB**: 加算/減算
- **MUL/DIV**: 乗算/除算
- **CMP**: 比較
- **JMP/JE/JNE**: ジャンプ命令
- **CALL/RET**: 関数呼び出し/復帰
- **PUSH/POP**: スタック操作

## 実装例
- [hello_world.asm](hello_world.asm) - Hello World
- [array_operations.asm](array_operations.asm) - 配列操作
- [factorial.asm](factorial.asm) - 再帰関数
- [sorting.asm](sorting.asm) - バブルソート
- [linked_list.asm](linked_list.asm) - 連結リスト

## コンパイルと実行
```bash
# NASM + GCC (Linux)
nasm -f elf64 filename.asm -o filename.o
gcc filename.o -o filename
./filename

# NASM + LD (Linux)
nasm -f elf64 filename.asm -o filename.o
ld filename.o -o filename
./filename
```
