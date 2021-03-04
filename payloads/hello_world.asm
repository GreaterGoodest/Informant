SECTION .TEXT
    GLOBAL _start

_start:
    mov rax, 4                  ; 4 = write
    mov rbx, 1                  ; file descriptor = stdout
    mov rcx, 'hello'
    mov rdx, 5
    int 80h                     ; syscall

    mov rax, 1                  ; exit for now (TODO: recover)
    mov rbx, 0                  ; exit code
    int 80h                     ; syscall
