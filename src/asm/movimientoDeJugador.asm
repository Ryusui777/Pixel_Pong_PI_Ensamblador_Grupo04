section .data
    vel: dd 8.0
    upperLimit: dd 0
    lowerLimit: dd 0 
    Yptr: dq 0 
section .text

global  moverJugadorArriba
global moverJugadorAbajo
global initPlayerMovement


; void moverJugadorArriba(float*);
moverJugadorArriba:
    movss   xmm0, dword [rdi]      ; y
    movss   xmm1, dword [vel]    
    subss   xmm0, xmm1             ; y -= velocidad
    movss xmm1, dword[upperLimit] ; upperLimit
    ucomiss xmm0, xmm1            ; comparacion
    jae .upperOk                  ; si es mayor o igual todo bien
    movss xmm0, xmm1
    .upperOk:
    movss   dword [rdi], xmm0
    ret

; void moverJugadorAbajo(float*);
moverJugadorAbajo:
    movss   xmm0, dword [rdi]      ; y
    movss   xmm1, dword [vel]    
    addss   xmm0, xmm1             ; y += velocidad
    movss xmm1, dword[lowerLimit] ; lowerLimit
    ucomiss xmm0, xmm1            ; comparacion
    jbe .lowerOk                  ; si es mayor o igual todo bien
    movss xmm0, xmm1
    .lowerOk:
    movss   dword [rdi], xmm0
    ret


; Define los limites de la pantalla
; estos vienen ya contando el tamano del
; sprite del jugador. 
; edi -> upperLimit, esi -> lowerLimit
; void initPlayerMovement(float, float, float*);
initPlayerMovement: 
    movss dword[upperLimit], xmm0
    movss dword[lowerLimit], xmm1
    ret
    



