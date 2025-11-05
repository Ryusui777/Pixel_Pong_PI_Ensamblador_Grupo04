; Copyright [2025] B. Alfaro, D. Orias, E. Ramírez, J. Rodríguez
section .bss
    velocity_ptr: resq 1
    position_ptr: resq 1
    upperLimit:   resd 1
    lowerLimit:   resd 1

section .data
    negSign: dd -1.0
    speed: dd 10.0  ; Velocidad por defecto de la bola
    isOpposingPlayer: dd 0
    currentAngle: dd 0  ; Ángulo actual de la bola
    DEG2RAD:    dd 0.0174532925 ; para convertir de grados a radianes
    minAngle: dd 0  ; Menor ángulo posible de la bola
    maxAngle: dd 360 ; Mayor ángulo posible de la bola

    defaultAngle: dd 45.0  ; Ángulo por defecto de la pelota

    g80:  dd 80.0
    g90:  dd 90.0
    g100: dd 100.0
    g260: dd 260.0
    g270: dd 270.0
    g280: dd 280.0

section .text
extern  GetRandomValue
extern  cosf
extern  sinf

; Funciones que se llaman desde C++
global isBallOpossingPlayer
global pelotaMove
global initPelotaMovement
global resetBall
global pelotaReboto
global pelotaReverseX
global pelotaReverseY
global setBallSpeed
global getCurrentAngle
global getIsOpposingPlayer
global setCurrentAngle
_isBallOpossingPlayer: 
    mov dword[isOpposingPlayer], 0
    movss xmm0, dword[currentAngle] ; el ángulo actual de la bola
    movss xmm1, dword[g90] ; ángulo de 90

    ; ángulo > 90
    ucomiss xmm0, xmm1
    jb .endCheck
.check2:
    movss xmm1, dword[g270]
    ucomiss xmm0, xmm1
    ja .endCheck
    mov dword[isOpposingPlayer], 1

.endCheck:
    ret

isBallOpossingPlayer:
    xor rax, rax
    mov eax, dword[isOpposingPlayer]
    ret

; Establecer la velocidad de la bola
setBallSpeed:
    movss dword[speed], xmm0  ; nuevo valor de velocidad (float)
    ret

; Actualizar la posición de la bola
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

; Guarda punteros y límites
initPelotaMovement: 
    mov [velocity_ptr], rdi
    mov [position_ptr], rsi
    mov [upperLimit], edx
    mov [lowerLimit], ecx
    ret

; Cambia una variable que dice si el ángulo de la bola va en dirección del
; jugador o su dirección contraria
pelotaReboto: 
    mov r8d, dword[isOpposingPlayer]
    cmp r8d, 0
    je  .noOpposing
    jmp .opposing
.noOpposing:
    mov dword[isOpposingPlayer], 1
    jmp .end
.opposing:
    mov dword[isOpposingPlayer], 0
.end:
    ret

; Invierte la dirección de la pelota en el eje x
pelotaReverseX: 
    mov rax, [velocity_ptr]
    call  reverse 
    ret

; Invierte la dirección de la pelota en el eje y
pelotaReverseY: 
    mov rax, [velocity_ptr]
    add rax, 4
    call  reverse 
    ret

reverse: 
    vmovss xmm0, dword[rax]
    vmovss xmm1, dword[negSign]
    vmulss xmm2, xmm0, xmm1
    vmovss dword[rax], xmm2 
    ret

resetBall:    
    mov edi, [minAngle]
    mov esi, [maxAngle]
    call  GetRandomValue 
    cvtsi2ss xmm0, eax
    ; Ángulo >= 80 y ángulo <= 100 
    vmovss xmm1, dword[g80]
    ucomiss xmm0, xmm1
    jb .fine
    vmovss xmm1, dword[g100]
    ucomiss xmm0, xmm1
    ja .check2
    jmp .change

; Ángulo >= 260 y ángulo <= 100 
.check2:
    vmovss xmm1, dword[g260]
    ucomiss xmm0, xmm1
    jb .fine
    vmovss xmm1, dword[g280]
    ucomiss xmm0, xmm1
    ja .fine

.change:
    movss xmm0, [defaultAngle]

.fine:
    mov     r8, [velocity_ptr]
    sub     rsp, 16 ; este espacio se va usar para guardar el ángulo y alinear la pila
    movss   [rsp], xmm0 

    ; cos(angle * DEG2RAD) * speed
    mulss   xmm0, dword [DEG2RAD] ; pasa el ángulo a radianes
    call    cosf                  
    mulss   xmm0, dword [speed]   
    movss   dword [r8], xmm0      

    ; sin(angle * DEG2RAD) * speed
    movss   xmm0, dword [rsp]     ; guardo el ángulo en la pila
    mulss   xmm0, dword [DEG2RAD] ; a radianes
    call    sinf                  ; xmm0 = sin(angle_rad)
    mulss   xmm0, dword [speed]
    movss   dword [r8+4], xmm0    ; velocity.y

    movss xmm0, dword[rsp]
    movss dword[currentAngle], xmm0
    add     rsp, 16
    call  _isBallOpossingPlayer

    ret

getCurrentAngle:
    movss xmm0, [currentAngle]
    ret
getIsOpposingPlayer:
    mov eax, [isOpposingPlayer]
    ret
setCurrentAngle:
    movss dword [currentAngle], xmm0
    ret
