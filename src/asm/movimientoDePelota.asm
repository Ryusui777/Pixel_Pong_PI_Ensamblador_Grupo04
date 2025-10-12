section .data
    negSign: dd -1.0

section .text

global pelotaReverseX
global pelotaReverseY




pelotaReverseX: 
    ret


; rdi -> puntero hacia la coordenada y de velocidad de la pelota
pelotaReverseY: 
    vmovss xmm0, dword[rdi]
    vmovss xmm1, dword[negSign]
    vmulss xmm2, xmm0, xmm1
    vmovss dword[rdi], xmm2 
    ret
