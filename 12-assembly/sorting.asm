section .data
    array dq 64, 34, 25, 12, 22, 11, 90, 5    ; ソート対象の配列
    array_len equ 8                            ; 配列の長さ
    space db ' ', 0
    newline db 0xA, 0
    before_msg db 'Before sorting: ', 0
    after_msg db 'After sorting: ', 0

section .bss
    temp_buffer resb 20                        ; 数値→文字列変換用バッファ

section .text
    global _start

; 配列を表示する関数
; 引数: rdi = 配列のアドレス, rsi = 要素数
print_array:
    push rbp
    mov rbp, rsp
    push rbx
    push rcx
    push rdi
    push rsi
    
    mov rcx, 0                                 ; インデックス
print_loop:
    cmp rcx, rsi                               ; 全要素をチェック
    jge print_array_done
    
    ; 数値を文字列に変換して出力
    mov rdi, [rdi + rcx * 8]                   ; array[i]を取得
    lea rsi, [temp_buffer]                     ; バッファアドレス
    call number_to_string                      ; 数値を文字列に変換
    
    ; 文字列を出力
    mov rax, 1                                 ; sys_write
    mov rdi, 1                                 ; stdout
    lea rsi, [temp_buffer]                     ; バッファ
    mov rdx, rax                               ; 文字列の長さ
    syscall
    
    ; スペースを出力
    mov rax, 1                                 ; sys_write
    mov rdi, 1                                 ; stdout
    mov rsi, space                             ; スペース
    mov rdx, 1                                 ; 長さ
    syscall
    
    ; 次の要素へ
    inc rcx
    pop rsi
    pop rdi
    push rdi
    push rsi
    jmp print_loop

print_array_done:
    ; 改行を出力
    mov rax, 1                                 ; sys_write
    mov rdi, 1                                 ; stdout
    mov rsi, newline                           ; 改行
    mov rdx, 1                                 ; 長さ
    syscall
    
    pop rsi
    pop rdi
    pop rcx
    pop rbx
    pop rbp
    ret

; バブルソート関数
; 引数: rdi = 配列のアドレス, rsi = 要素数
bubble_sort:
    push rbp
    mov rbp, rsp
    push rbx
    push rcx
    push rdx
    push r8
    push r9
    
    ; 外側のループ (i = 0; i < n-1; i++)
    mov rcx, 0                                 ; i = 0
outer_loop:
    mov rax, rsi
    dec rax                                    ; n-1
    cmp rcx, rax                               ; i < n-1?
    jge bubble_sort_done
    
    ; 内側のループ (j = 0; j < n-i-1; j++)
    mov rdx, 0                                 ; j = 0
inner_loop:
    mov rax, rsi
    sub rax, rcx                               ; n-i
    dec rax                                    ; n-i-1
    cmp rdx, rax                               ; j < n-i-1?
    jge inner_loop_done
    
    ; array[j] と array[j+1] を比較
    mov r8, [rdi + rdx * 8]                    ; array[j]
    mov r9, [rdi + rdx * 8 + 8]                ; array[j+1]
    cmp r8, r9                                 ; array[j] > array[j+1]?
    jle no_swap                                ; 交換不要
    
    ; 要素を交換
    mov [rdi + rdx * 8], r9                    ; array[j] = array[j+1]
    mov [rdi + rdx * 8 + 8], r8                ; array[j+1] = temp
    
no_swap:
    inc rdx                                    ; j++
    jmp inner_loop
    
inner_loop_done:
    inc rcx                                    ; i++
    jmp outer_loop
    
bubble_sort_done:
    pop r9
    pop r8
    pop rdx
    pop rcx
    pop rbx
    pop rbp
    ret

; 選択ソート関数
; 引数: rdi = 配列のアドレス, rsi = 要素数
selection_sort:
    push rbp
    mov rbp, rsp
    push rbx
    push rcx
    push rdx
    push r8
    push r9
    push r10
    
    ; 外側のループ (i = 0; i < n-1; i++)
    mov rcx, 0                                 ; i = 0
sel_outer_loop:
    mov rax, rsi
    dec rax                                    ; n-1
    cmp rcx, rax                               ; i < n-1?
    jge selection_sort_done
    
    ; 最小値のインデックスを初期化
    mov r8, rcx                                ; min_idx = i
    
    ; 内側のループ (j = i+1; j < n; j++)
    mov rdx, rcx
    inc rdx                                    ; j = i+1
sel_inner_loop:
    cmp rdx, rsi                               ; j < n?
    jge sel_inner_loop_done
    
    ; array[j] < array[min_idx]?
    mov r9, [rdi + rdx * 8]                    ; array[j]
    mov r10, [rdi + r8 * 8]                    ; array[min_idx]
    cmp r9, r10
    jge sel_no_update
    
    ; 新しい最小値のインデックスを更新
    mov r8, rdx                                ; min_idx = j
    
sel_no_update:
    inc rdx                                    ; j++
    jmp sel_inner_loop
    
sel_inner_loop_done:
    ; array[i] と array[min_idx] を交換
    cmp r8, rcx                                ; min_idx == i?
    je sel_no_swap                             ; 交換不要
    
    mov r9, [rdi + rcx * 8]                    ; temp = array[i]
    mov r10, [rdi + r8 * 8]                    ; array[min_idx]
    mov [rdi + rcx * 8], r10                   ; array[i] = array[min_idx]
    mov [rdi + r8 * 8], r9                     ; array[min_idx] = temp
    
sel_no_swap:
    inc rcx                                    ; i++
    jmp sel_outer_loop
    
selection_sort_done:
    pop r10
    pop r9
    pop r8
    pop rdx
    pop rcx
    pop rbx
    pop rbp
    ret

; 挿入ソート関数
; 引数: rdi = 配列のアドレス, rsi = 要素数
insertion_sort:
    push rbp
    mov rbp, rsp
    push rbx
    push rcx
    push rdx
    push r8
    push r9
    
    ; ループ (i = 1; i < n; i++)
    mov rcx, 1                                 ; i = 1
ins_outer_loop:
    cmp rcx, rsi                               ; i < n?
    jge insertion_sort_done
    
    ; key = array[i]
    mov r8, [rdi + rcx * 8]                    ; key = array[i]
    
    ; j = i - 1
    mov rdx, rcx
    dec rdx                                    ; j = i - 1
    
ins_inner_loop:
    ; j >= 0 && array[j] > key?
    cmp rdx, 0
    jl ins_inner_loop_done                     ; j < 0なら終了
    
    mov r9, [rdi + rdx * 8]                    ; array[j]
    cmp r9, r8                                 ; array[j] > key?
    jle ins_inner_loop_done                    ; array[j] <= keyなら終了
    
    ; array[j+1] = array[j]
    mov [rdi + rdx * 8 + 8], r9
    
    dec rdx                                    ; j--
    jmp ins_inner_loop
    
ins_inner_loop_done:
    ; array[j+1] = key
    inc rdx                                    ; j+1
    mov [rdi + rdx * 8], r8
    
    inc rcx                                    ; i++
    jmp ins_outer_loop
    
insertion_sort_done:
    pop r9
    pop r8
    pop rdx
    pop rcx
    pop rbx
    pop rbp
    ret

; 数値を文字列に変換
; 引数: rdi = 数値, rsi = バッファアドレス
; 戻り値: rax = 文字列の長さ
number_to_string:
    push rbp
    mov rbp, rsp
    push rbx
    push rcx
    push rdx
    
    mov rax, rdi                               ; 数値
    mov rbx, 10                                ; 基数
    mov rcx, 0                                 ; 文字数カウンタ
    
    ; 数値が0の場合
    test rax, rax
    jnz convert_loop
    mov byte [rsi], '0'
    mov byte [rsi + 1], 0
    mov rax, 1
    jmp convert_done
    
convert_loop:
    test rax, rax
    jz reverse_string
    
    xor rdx, rdx
    div rbx                                    ; rax = rax / 10, rdx = rax % 10
    add dl, '0'                                ; 数字を文字に変換
    mov [rsi + rcx], dl
    inc rcx
    jmp convert_loop
    
reverse_string:
    mov rax, rcx                               ; 文字列の長さ
    dec rcx                                    ; 最後のインデックス
    mov rdx, 0                                 ; 最初のインデックス
    
reverse_loop:
    cmp rdx, rcx
    jge string_done
    
    mov bl, [rsi + rdx]
    mov bh, [rsi + rcx]
    mov [rsi + rdx], bh
    mov [rsi + rcx], bl
    
    inc rdx
    dec rcx
    jmp reverse_loop
    
string_done:
    mov byte [rsi + rax], 0                    ; null終端
    
convert_done:
    pop rdx
    pop rcx
    pop rbx
    pop rbp
    ret

_start:
    ; "Before sorting: "を出力
    mov rax, 1                                 ; sys_write
    mov rdi, 1                                 ; stdout
    mov rsi, before_msg                        ; メッセージ
    mov rdx, 16                                ; 長さ
    syscall
    
    ; ソート前の配列を表示
    mov rdi, array                             ; 配列のアドレス
    mov rsi, array_len                         ; 要素数
    call print_array
    
    ; バブルソートを実行
    mov rdi, array                             ; 配列のアドレス
    mov rsi, array_len                         ; 要素数
    call bubble_sort
    
    ; "After sorting: "を出力
    mov rax, 1                                 ; sys_write
    mov rdi, 1                                 ; stdout
    mov rsi, after_msg                         ; メッセージ
    mov rdx, 15                                ; 長さ
    syscall
    
    ; ソート後の配列を表示
    mov rdi, array                             ; 配列のアドレス
    mov rsi, array_len                         ; 要素数
    call print_array
    
    ; プログラム終了
    mov rax, 60                                ; sys_exit
    mov rdi, 0                                 ; 終了ステータス
    syscall
