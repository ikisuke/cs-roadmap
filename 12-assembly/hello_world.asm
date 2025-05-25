section .data
    hello db 'Hello, World!', 0xA, 0    ; 文字列 + 改行 + null終端
    hello_len equ $ - hello - 1          ; 文字列の長さ（null文字除く）

section .text
    global _start

_start:
    ; write システムコール
    mov rax, 1          ; sys_write
    mov rdi, 1          ; stdout
    mov rsi, hello      ; メッセージのアドレス
    mov rdx, hello_len  ; バイト数
    syscall             ; システムコール実行

    ; exit システムコール
    mov rax, 60         ; sys_exit
    mov rdi, 0          ; 終了ステータス
    syscall             ; システムコール実行
