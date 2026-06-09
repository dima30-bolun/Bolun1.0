global bolun_asm_add

section .text
bolun_asm_add:
    mov rax, rdi
    add rax, rsi
    ret

section .note.GNU-stack noalloc noexec nowrite progbits
