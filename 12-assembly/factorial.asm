section .data
    input_num dq 5                  ; 計算する数値 (5!)
    result_msg db 'Result: ', 0
    newline db 0xA, 0

section .bss
    result resq 1                   ; 結果格納用

section .text
    global _start

; 階乗を計算する再帰関数
; 引数: rdi = n
; 戻り値: rax = n!
factorial:
    ; ベースケース: n <= 1 なら 1 を返す
    cmp rdi, 1
    jle base_case
    
    ; スタックフレームの設定
    push rbp
    mov rbp, rsp
    push rdi                        ; nを保存
    
    ; 再帰呼び出し: factorial(n-1)
    dec rdi                         ; n-1
    call factorial                  ; factorial(n-1)を計算
    
    ; raxにfactorial(n-1)の結果が入っている
    pop rdi                         ; 元のnを復元
    mul rdi                         ; rax = rax * rdi = factorial(n-1) * n
    
    ; スタックフレームの復元
    pop rbp
    ret

base_case:
    mov rax, 1                      ; 1を返す
    ret

; 反復版の階乗計算（比較用）
factorial_iterative:
    ; 引数: rdi = n
    ; 戻り値: rax = n!
    mov rax, 1                      ; 結果を1で初期化
    mov rcx, 1                      ; カウンタを1で初期化
    
factorial_loop:
    cmp rcx, rdi                    ; rcx > nなら終了
    jg factorial_iter_done
    
    mul rcx                         ; rax = rax * rcx
    inc rcx                         ; rcx++
    jmp factorial_loop
    
factorial_iter_done:
    ret

; フィボナッチ数列（再帰版）
; 引数: rdi = n
; 戻り値: rax = fib(n)
fibonacci:
    ; ベースケース: n <= 1 なら n を返す
    cmp rdi, 1
    jle fib_base_case
    
    ; スタックフレームの設定
    push rbp
    mov rbp, rsp
    push rdi                        ; nを保存
    
    ; fib(n-1)を計算
    dec rdi                         ; n-1
    call fibonacci
    push rax                        ; fib(n-1)を保存
    
    ; fib(n-2)を計算
    pop rax                         ; fib(n-1)を復元
    pop rdi                         ; nを復元
    push rax                        ; fib(n-1)を再度保存
    sub rdi, 2                      ; n-2
    call fibonacci                  ; fib(n-2)を計算
    
    ; fib(n-1) + fib(n-2)を計算
    pop rbx                         ; fib(n-1)をrbxに
    add rax, rbx                    ; rax = fib(n-2) + fib(n-1)
    
    ; スタックフレームの復元
    pop rbp
    ret

fib_base_case:
    mov rax, rdi                    ; nを返す
    ret

; 最大公約数（ユークリッドの互除法）
; 引数: rdi = a, rsi = b
; 戻り値: rax = gcd(a, b)
gcd:
    ; ベースケース: b == 0 なら a を返す
    test rsi, rsi                   ; b == 0?
    jz gcd_base_case
    
    ; スタックフレームの設定
    push rbp
    mov rbp, rsp
    
    ; a % b を計算
    mov rax, rdi                    ; a
    xor rdx, rdx                    ; rdxをクリア
    div rsi                         ; rax = a / b, rdx = a % b
    
    ; gcd(b, a % b)を再帰呼び出し
    mov rdi, rsi                    ; 第1引数 = b
    mov rsi, rdx                    ; 第2引数 = a % b
    call gcd
    
    ; スタックフレームの復元
    pop rbp
    ret

gcd_base_case:
    mov rax, rdi                    ; aを返す
    ret

; 数値を文字列に変換（10進数）
; 引数: rdi = 数値, rsi = バッファアドレス
; 戻り値: rax = 文字列の長さ
number_to_string:
    push rbp
    mov rbp, rsp
    push rbx
    push rcx
    push rdx
    
    mov rax, rdi                    ; 数値
    mov rbx, 10                     ; 基数
    mov rcx, 0                      ; 文字数カウンタ
    
    ; 数値が0の場合の特別処理
    test rax, rax
    jnz convert_loop
    mov byte [rsi], '0'             ; '0'を格納
    mov byte [rsi + 1], 0           ; null終端
    mov rax, 1                      ; 長さ1
    jmp convert_done
    
convert_loop:
    test rax, rax                   ; 数値が0になったか
    jz reverse_string
    
    xor rdx, rdx                    ; rdxをクリア
    div rbx                         ; rax = rax / 10, rdx = rax % 10
    add dl, '0'                     ; 数字を文字に変換
    mov [rsi + rcx], dl             ; バッファに格納
    inc rcx                         ; 文字数カウンタ++
    jmp convert_loop
    
reverse_string:
    ; 文字列を逆順にする
    mov rax, rcx                    ; 文字列の長さ
    dec rcx                         ; 最後のインデックス
    mov rdx, 0                      ; 最初のインデックス
    
reverse_loop:
    cmp rdx, rcx                    ; rdx >= rcx なら終了
    jge string_done
    
    ; 文字を交換
    mov bl, [rsi + rdx]
    mov bh, [rsi + rcx]
    mov [rsi + rdx], bh
    mov [rsi + rcx], bl
    
    inc rdx                         ; 前から++
    dec rcx                         ; 後ろから--
    jmp reverse_loop
    
string_done:
    mov byte [rsi + rax], 0         ; null終端
    
convert_done:
    pop rdx
    pop rcx
    pop rbx
    pop rbp
    ret

_start:
    ; 階乗を計算（再帰版）
    mov rdi, [input_num]            ; 入力値
    call factorial                  ; factorial(5)を計算
    mov [result], rax               ; 結果を保存
    
    ; 階乗を計算（反復版）- 比較用
    mov rdi, [input_num]            ; 入力値
    call factorial_iterative        ; factorial_iterative(5)を計算
    
    ; フィボナッチ数列を計算
    mov rdi, 10                     ; fib(10)を計算
    call fibonacci
    
    ; 最大公約数を計算
    mov rdi, 48                     ; a = 48
    mov rsi, 18                     ; b = 18
    call gcd                        ; gcd(48, 18) = 6
    
    ; プログラム終了
    mov rax, 60                     ; sys_exit
    mov rdi, 0                      ; 終了ステータス
    syscall
