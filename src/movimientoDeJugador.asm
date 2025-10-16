; Copyright [2025] B. Alfaro, D. Orias, E. Ramírez, J. Rodríguez
section .bss
    position_ptr: resq 1 
    upperLimit: resd 1
    lowerLimit: resd 1 

section .data
    vel: dd 8.0
section .text

global  moverJugadorArriba
global moverJugadorAbajo
global initPlayerMovement


;===========================
; Mueve el jugador hacia arriba
;===========================
moverJugadorArriba:
    mov rax, [position_ptr]
    movss   xmm0, dword [rax+4]      ; y
    movss   xmm1, dword [vel]    
    subss   xmm0, xmm1             ; y -= velocidad
    movss xmm1, dword[upperLimit] ; upperLimit
    ucomiss xmm0, xmm1            ; comparación
    jae .upperOk
    movss xmm0, xmm1
    .upperOk:
    movss   dword [rax+4], xmm0
    ret

;===========================
; Mueve el jugador hacia abajo
;===========================
moverJugadorAbajo:
    mov rax, [position_ptr]
    movss   xmm0, dword [rax+4]   ; y
    movss   xmm1, dword [vel]
    addss   xmm0, xmm1            ; y += velocidad
    movss xmm1, dword[lowerLimit] ; lowerLimit
    ucomiss xmm0, xmm1            ; comparación
    jbe .lowerOk
    movss xmm0, xmm1
    .lowerOk:
    movss   dword [rax+4], xmm0
    ret


;===================================
; Define los límites de la pantalla
; estos vienen ya contando el tamaño del
; sprite del jugador. 
; xmm0 -> upperLimit,
; xmm1 -> lowerLimit, 
; rdi -> puntero hacia la posición del jugador
;===================================
initPlayerMovement: 
    movss dword[upperLimit], xmm0
    movss dword[lowerLimit], xmm1
    mov [position_ptr], rdi
    ret
