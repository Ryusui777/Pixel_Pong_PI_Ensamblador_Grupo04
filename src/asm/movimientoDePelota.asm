section .bss
    velocity_ptr: resq 1
    position_ptr: resq 1
    upperLimit:   resd 1
    lowerLimit:   resd 1
section .data
    negSign: dd -1.0
section .text


global pelotaReverseX
global pelotaReverseY
global pelotaMove
global initPelotaMovement

;============================================
; Guarda los punteros hacia los vectores
; de posicion y velocidad. Ademas define los
; bordes inferiores y superiores tomando en 
; cuenta el tamano de la sprite.
; Parametros: 
; rdi -> puntero hacia el vector de velocidad
; rsi -> puntero hacia el vector de posicion
; edx -> el limite superior de la pantalla
; ecx -> el limite inferior de la pantalla
;============================================
initPelotaMovement: 
    mov [velocity_ptr], rdi
    mov [position_ptr], rsi
    mov [upperLimit], edx
    mov [lowerLimit], ecx
    ret
    

;============================================
; Actualiza la posicion de la pelota
;============================================
pelotaMove: 
    mov r8, [velocity_ptr]

    vmovss xmm0, [r8] ; velocity.x
    vmovss xmm1, [r8+4] ; velocity.y
    
    mov r9, [position_ptr]

    vmovss xmm2, [r9] ; position.x
    vmovss xmm3, [r9+4]; position.y

    vaddss xmm2, xmm0; position.x + velocity.x
    vaddss xmm3, xmm1; position.x + velocity.x
    
    vmovss dword[r9], xmm2
    vmovss dword[r9+4], xmm3


    ret

;============================================
; Invierte la direccion de la pelota en el
; eje x
;============================================
pelotaReverseX: 
    mov rax, [velocity_ptr]
    call reverse 
    ret

;============================================
; Invierte la direccion de la pelota en el
; eje y
;============================================
pelotaReverseY: 
    mov rax, [velocity_ptr]
    add rax, 4
    call reverse 
    ret

;============================================
; Cambia de signo el numero que este apuntado 
; por rax
;============================================
reverse: 
    vmovss xmm0, dword[rax]
    vmovss xmm1, dword[negSign]
    vmulss xmm2, xmm0, xmm1
    vmovss dword[rax], xmm2 
    ret
    