
section .bss
    velocity_ptr: resq 1
section .data
    negSign: dd -1.0
section .text


global pelotaReverseX
global pelotaReverseY
global setVelocityPtr


setVelocityPtr: 
    mov [velocity_ptr], rdi
    ret

; void
pelotaReverseX: 
    mov rax, [velocity_ptr]
    vmovss xmm0, dword[rax]
    vmovss xmm1, dword[negSign]
    vmulss xmm2, xmm0, xmm1
    vmovss dword[rax], xmm2 
    ret

; void 
pelotaReverseY: 
    mov rax, [velocity_ptr]
    vmovss xmm0, dword[rax+4]
    vmovss xmm1, dword[negSign]
    vmulss xmm2, xmm0, xmm1
    vmovss dword[rax+4], xmm2 
    ret
