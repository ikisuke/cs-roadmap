section .data
    array dq 10, 20, 30, 40, 50    ; 64ビット整数配列
    array_len equ 5                 ; 配列の長さ
    target dq 30                    ; 検索対象
    result_found db 'Found!', 0xA, 0
    result_not_found db 'Not found!', 0xA, 0
    newline db 0xA, 0

section .bss
    sum_result resq 1               ; 合計値用

section .text
    global _start

; 配列の要素を出力する関数
print_array:
    mov rcx, 0                      ; インデックス
print_loop:
    cmp rcx, array_len              ; 全要素をチェック
    jge print_done
    
    ; 数値を文字列に変換して出力（簡略化）
    mov rax, [array + rcx * 8]      ; array[i]を取得
    ; ここでは実際の数値出力は省略
    
    inc rcx
    jmp print_loop
print_done:
    ret

; 配列の合計を計算する関数
calculate_sum:
    mov rax, 0                      ; 合計値初期化
    mov rcx, 0                      ; インデックス
sum_loop:
    cmp rcx, array_len              ; 全要素をチェック
    jge sum_done
    
    add rax, [array + rcx * 8]      ; array[i]を合計に加算
    inc rcx
    jmp sum_loop
sum_done:
    mov [sum_result], rax           ; 結果を保存
    ret

; 線形探索関数
linear_search:
    mov rcx, 0                      ; インデックス
    mov rdx, [target]               ; 検索対象
search_loop:
    cmp rcx, array_len              ; 全要素をチェック
    jge not_found
    
    cmp [array + rcx * 8], rdx      ; array[i]と比較
    je found                        ; 等しければfoundへジャンプ
    
    inc rcx
    jmp search_loop

found:
    ; "Found!"を出力
    mov rax, 1                      ; sys_write
    mov rdi, 1                      ; stdout
    mov rsi, result_found           ; メッセージ
    mov rdx, 7                      ; 長さ
    syscall
    ret

not_found:
    ; "Not found!"を出力
    mov rax, 1                      ; sys_write
    mov rdi, 1                      ; stdout
    mov rsi, result_not_found       ; メッセージ
    mov rdx, 11                     ; 長さ
    syscall
    ret

; 配列の最大値を求める関数
find_max:
    mov rax, [array]                ; 最初の要素を最大値とする
    mov rcx, 1                      ; インデックス1から開始
max_loop:
    cmp rcx, array_len              ; 全要素をチェック
    jge max_done
    
    cmp rax, [array + rcx * 8]      ; 現在の最大値と比較
    jge no_update                   ; 現在の最大値が大きい場合
    mov rax, [array + rcx * 8]      ; 新しい最大値を設定
no_update:
    inc rcx
    jmp max_loop
max_done:
    ret                             ; raxに最大値が入っている

; 配列をコピーする関数（memcpy的な操作）
copy_array:
    ; 引数: rsi = ソース配列, rdi = デスティネーション配列, rdx = 要素数
    mov rcx, 0                      ; インデックス
copy_loop:
    cmp rcx, rdx                    ; 全要素をチェック
    jge copy_done
    
    mov rax, [rsi + rcx * 8]        ; ソースから読み込み
    mov [rdi + rcx * 8], rax        ; デスティネーションに書き込み
    
    inc rcx
    jmp copy_loop
copy_done:
    ret

_start:
    ; 配列の合計を計算
    call calculate_sum
    
    ; 線形探索を実行
    call linear_search
    
    ; 最大値を求める
    call find_max
    ; raxに最大値が入っている
    
    ; プログラム終了
    mov rax, 60                     ; sys_exit
    mov rdi, 0                      ; 終了ステータス
    syscall
