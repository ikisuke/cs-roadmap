section .data
    newline db 0xA, 0
    arrow_msg db ' -> ', 0
    null_msg db 'NULL', 0xA, 0
    list_msg db 'List: ', 0

section .bss
    temp_buffer resb 20                        ; 数値→文字列変換用バッファ

section .text
    global _start

; ノード構造体のオフセット定義
%define NODE_DATA 0                            ; データ部のオフセット
%define NODE_NEXT 8                            ; nextポインタのオフセット
%define NODE_SIZE 16                           ; ノードのサイズ

; メモリ割り当て用のシンプルなアロケータ
; 引数: rdi = サイズ
; 戻り値: rax = 割り当てられたメモリのアドレス
simple_malloc:
    push rbp
    mov rbp, rsp
    
    ; システムコールmmap を使用してメモリを割り当て
    mov rax, 9                                 ; sys_mmap
    mov rdi, 0                                 ; addr = NULL
    mov rsi, 4096                              ; length = 4KB
    mov rdx, 3                                 ; prot = PROT_READ | PROT_WRITE
    mov r10, 34                                ; flags = MAP_PRIVATE | MAP_ANONYMOUS
    mov r8, -1                                 ; fd = -1
    mov r9, 0                                  ; offset = 0
    syscall
    
    pop rbp
    ret

; メモリ解放（簡略化のため実際には何もしない）
simple_free:
    ret

; 新しいノードを作成
; 引数: rdi = データ
; 戻り値: rax = 新しいノードのアドレス
create_node:
    push rbp
    mov rbp, rsp
    push rdi                                   ; データを保存
    
    ; ノード用のメモリを割り当て
    mov rdi, NODE_SIZE
    call simple_malloc
    
    ; データとnextポインタを設定
    pop rdi                                    ; データを復元
    mov [rax + NODE_DATA], rdi                 ; ノードのデータ部にデータを設定
    mov qword [rax + NODE_NEXT], 0             ; nextポインタをNULLに設定
    
    pop rbp
    ret

; リストの先頭に挿入
; 引数: rdi = headポインタのアドレス, rsi = データ
insert_at_head:
    push rbp
    mov rbp, rsp
    push rbx
    push rdi
    push rsi
    
    ; 新しいノードを作成
    mov rdi, rsi                               ; データ
    call create_node                           ; 新しいノードを作成
    mov rbx, rax                               ; 新しいノードのアドレス
    
    ; 現在のheadを新しいノードのnextに設定
    pop rsi
    pop rdi
    push rdi
    mov rax, [rdi]                             ; 現在のhead
    mov [rbx + NODE_NEXT], rax                 ; 新しいノード->next = 現在のhead
    
    ; headを新しいノードに更新
    mov [rdi], rbx                             ; head = 新しいノード
    
    pop rdi
    pop rbx
    pop rbp
    ret

; リストの末尾に挿入
; 引数: rdi = headポインタのアドレス, rsi = データ
insert_at_tail:
    push rbp
    mov rbp, rsp
    push rbx
    push rcx
    push rdi
    push rsi
    
    ; 新しいノードを作成
    mov rdi, rsi                               ; データ
    call create_node                           ; 新しいノードを作成
    mov rbx, rax                               ; 新しいノードのアドレス
    
    pop rsi
    pop rdi
    push rdi
    
    ; リストが空の場合
    mov rax, [rdi]                             ; head
    test rax, rax                              ; head == NULL?
    jnz find_tail
    
    ; 空のリストの場合、headに新しいノードを設定
    mov [rdi], rbx
    jmp insert_tail_done
    
find_tail:
    ; 末尾を見つける
    mov rcx, rax                               ; current = head
find_tail_loop:
    mov rax, [rcx + NODE_NEXT]                 ; current->next
    test rax, rax                              ; next == NULL?
    jz tail_found
    mov rcx, rax                               ; current = current->next
    jmp find_tail_loop
    
tail_found:
    ; 末尾ノードのnextに新しいノードを設定
    mov [rcx + NODE_NEXT], rbx
    
insert_tail_done:
    pop rdi
    pop rcx
    pop rbx
    pop rbp
    ret

; 指定したデータを持つノードを削除
; 引数: rdi = headポインタのアドレス, rsi = 削除するデータ
delete_node:
    push rbp
    mov rbp, rsp
    push rbx
    push rcx
    push rdx
    
    mov rax, [rdi]                             ; head
    test rax, rax                              ; head == NULL?
    jz delete_done                             ; 空のリストなら何もしない
    
    ; headノードをチェック
    cmp [rax + NODE_DATA], rsi                 ; head->data == target?
    jne search_node
    
    ; headノードを削除
    mov rbx, [rax + NODE_NEXT]                 ; head->next
    mov [rdi], rbx                             ; head = head->next
    
    ; ノードのメモリを解放
    mov rdi, rax
    call simple_free
    jmp delete_done
    
search_node:
    ; リスト内を検索
    mov rcx, rax                               ; current = head
search_loop:
    mov rdx, [rcx + NODE_NEXT]                 ; next = current->next
    test rdx, rdx                              ; next == NULL?
    jz delete_done                             ; 見つからない
    
    cmp [rdx + NODE_DATA], rsi                 ; next->data == target?
    je found_node
    
    mov rcx, rdx                               ; current = next
    jmp search_loop
    
found_node:
    ; ノードを削除
    mov rax, [rdx + NODE_NEXT]                 ; next->next
    mov [rcx + NODE_NEXT], rax                 ; current->next = next->next
    
    ; ノードのメモリを解放
    mov rdi, rdx
    call simple_free
    
delete_done:
    pop rdx
    pop rcx
    pop rbx
    pop rbp
    ret

; リストを表示
; 引数: rdi = head
print_list:
    push rbp
    mov rbp, rsp
    push rbx
    
    ; "List: "を出力
    mov rax, 1                                 ; sys_write
    mov rdi, 1                                 ; stdout
    mov rsi, list_msg                          ; メッセージ
    mov rdx, 6                                 ; 長さ
    syscall
    
    pop rbx
    push rbx
    mov rbx, [rsp + 8]                         ; headを取得
    
print_loop:
    test rbx, rbx                              ; current == NULL?
    jz print_null
    
    ; ノードのデータを出力
    mov rdi, [rbx + NODE_DATA]                 ; current->data
    lea rsi, [temp_buffer]                     ; バッファ
    call number_to_string                      ; 数値を文字列に変換
    
    ; 文字列を出力
    mov rax, 1                                 ; sys_write
    mov rdi, 1                                 ; stdout
    lea rsi, [temp_buffer]                     ; バッファ
    mov rdx, rax                               ; 文字列の長さ
    syscall
    
    ; 次のノードへ
    mov rbx, [rbx + NODE_NEXT]                 ; current = current->next
    test rbx, rbx                              ; current == NULL?
    jz print_null
    
    ; " -> "を出力
    mov rax, 1                                 ; sys_write
    mov rdi, 1                                 ; stdout
    mov rsi, arrow_msg                         ; " -> "
    mov rdx, 4                                 ; 長さ
    syscall
    
    jmp print_loop
    
print_null:
    ; "NULL"を出力
    mov rax, 1                                 ; sys_write
    mov rdi, 1                                 ; stdout
    mov rsi, null_msg                          ; "NULL\n"
    mov rdx, 5                                 ; 長さ
    syscall
    
    pop rbx
    pop rbp
    ret

; リストを逆転
; 引数: rdi = headポインタのアドレス
reverse_list:
    push rbp
    mov rbp, rsp
    push rbx
    push rcx
    push rdx
    
    mov rax, [rdi]                             ; head
    mov rbx, 0                                 ; prev = NULL
    mov rcx, rax                               ; current = head
    
reverse_loop:
    test rcx, rcx                              ; current == NULL?
    jz reverse_done
    
    mov rdx, [rcx + NODE_NEXT]                 ; next = current->next
    mov [rcx + NODE_NEXT], rbx                 ; current->next = prev
    mov rbx, rcx                               ; prev = current
    mov rcx, rdx                               ; current = next
    jmp reverse_loop
    
reverse_done:
    mov [rdi], rbx                             ; head = prev
    
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

section .bss
    head resq 1                                ; リストのheadポインタ

_start:
    ; headを初期化
    mov qword [head], 0
    
    ; 要素を挿入
    lea rdi, [head]                            ; headポインタのアドレス
    mov rsi, 10                                ; データ
    call insert_at_tail
    
    lea rdi, [head]
    mov rsi, 20
    call insert_at_tail
    
    lea rdi, [head]
    mov rsi, 30
    call insert_at_tail
    
    lea rdi, [head]
    mov rsi, 5
    call insert_at_head
    
    ; リストを表示
    mov rdi, [head]
    call print_list
    
    ; 要素を削除
    lea rdi, [head]
    mov rsi, 20                                ; 20を削除
    call delete_node
    
    ; リストを表示
    mov rdi, [head]
    call print_list
    
    ; リストを逆転
    lea rdi, [head]
    call reverse_list
    
    ; リストを表示
    mov rdi, [head]
    call print_list
    
    ; プログラム終了
    mov rax, 60                                ; sys_exit
    mov rdi, 0                                 ; 終了ステータス
    syscall
