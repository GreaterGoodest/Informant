SECTION .DATA
    helloString:        db 'Hello world!',10 ; 10 = \n
    helloStringLength:  equ $-helloString    ; $ = current location.

SECTION .TEXT
    GLOBAL _start

_start:
    mov rax, 4                  ; 4 = write
    mov rbx, 1                  ; file descriptor = stdout
    mov rcx, helloString 
    mov rdx, helloStringLength
    int 80h                     ; syscall

    mov rax, 1                  ; exit for now (TODO: recover)
    mov rbx, 0                  ; exit code
    int 80h                     ; syscall