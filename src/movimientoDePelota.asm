; Copyright [2025] B. Alfaro, D. Orias, E. Ramírez, J. Rodríguez
section .bss
    velocity_ptr: resq 1
    position_ptr: resq 1
    upperLimit:   resd 1
    lowerLimit:   resd 1

section .data
    game_dificulty: db 0

    negSign: dd -1.0
    one: dd 1.0

    ; Speed related
    n10: dd 10.0
    speed: dd 10.0  ; Velocidad por defecto de la bola

    easySpeedLimit:     dd 15.0
    mediumSpeedLimit:   dd 20.0
    hardSpeedLimit:     dd 20.0

    isOpposingPlayer: dd 0
    currentAngle: dd 0  ; Ángulo actual de la bola
    DEG2RAD:    dd 0.0174532925
    minAngle: dd 0  ; Menor ángulo posible de la bola
    maxAngle: dd 360 ; Mayor ángulo posible de la bola

    defaultAngle: dd 45.0  ; Ángulo por defecto de la pelota

    g0:   dd 0.0
    g60:  dd 60.0
    g80:  dd 80.0
    g90:  dd 90.0
    g100: dd 100.0
    g120: dd 120.0
    g180: dd 180.0
    g240: dd 240.0
    g260: dd 260.0
    g270: dd 270.0
    g280: dd 280.0
    g300: dd 300.0
    g360: dd 360.0


    gSpin: dd 20.0
    
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
global setDifficulty


_isBallOpossingPlayer: 
    mov dword[isOpposingPlayer], 0

    movss xmm0, dword[currentAngle] ; el ángulo actual de la bola
    movss xmm1, dword[g90]          ; ángulo de 90

    ; angle > 90 
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

;============================================
; Cambia la dificultad del juego
; dil -> la dificultad que se quiere que este
;        el juego
;============================================
setDifficulty: 
    mov byte[game_dificulty], dil
    ret

;============================================
; Actualizar la posición de la bola
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
; Guarda los punteros hacia los vectores
; de posición y velocidad. Además, define los
; bordes inferiores y superiores; tomando en 
; cuenta el tamano de la sprite.
; Parámetros: 
; rdi -> puntero hacia el vector de velocidad
; rsi -> puntero hacia el vector de posicion
; edx -> el límite superior de la pantalla
; ecx -> el límite inferior de la pantalla
;============================================
initPelotaMovement: 
    mov [velocity_ptr], rdi
    mov [position_ptr], rsi
    mov [upperLimit], edx
    mov [lowerLimit], ecx
    ret

;============================================
; Cambia una variable que dice si el ángulo 
; de la bola va en dirección del jugador o 
; su dirección contraria
;============================================
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

;============================================
; Invierte la dirección de la pelota en el
; eje x
;============================================
pelotaReverseX: 
    mov rax, [velocity_ptr]
    call  reverse 
    ret

;============================================
; Invierte la dirección de la pelota en el
; eje y
;============================================
pelotaReverseY: 
    mov rax, [velocity_ptr]
    add rax, 4
    call  reverse 
    ret

;============================================
; Invierte a lo que apunte rax
;============================================
reverse: 
    vmovss xmm0, dword[rax]
    vmovss xmm1, dword[negSign]
    vmulss xmm2, xmm0, xmm1
    vmovss dword[rax], xmm2 
    ret

;============================================
; Resetea la velocidad, anglo y posicion de la
; pelota
;============================================
resetBall:    
    ; Resetea la velocidad de la pelota
    movss xmm0, [n10]
    movss dword[speed], xmm0
    mov edi, [minAngle]
    mov esi, [maxAngle]
    call  GetRandomValue 
    cvtsi2ss xmm0, eax
    ; Ángulo >= 80 y ángulo <= 100 
    vmovss xmm1, dword[g60]
    ucomiss xmm0, xmm1
    jb .fine
    vmovss xmm1, dword[g120]
    ucomiss xmm0, xmm1
    ja .check2
    jmp .change

    ; DEBUG 
    ; movss xmm0, dword[g0]
    ; DEBUG

; Ángulo >= 260 y ángulo <= 100 
.check2:
    ; DEBUG 
    ; movss xmm0, dword[g180]
    ; DEBUG
    vmovss xmm1, dword[g240]
    ucomiss xmm0, xmm1
    jb .fine
    vmovss xmm1, dword[g300]
    ucomiss xmm0, xmm1
    ja .fine

.change:
    ; DEBUG 
    ; movss xmm0, dword[g180]
    ; DEBUG
    movss xmm0, [defaultAngle]

.fine:
    ; DEBUG 
    ; movss xmm0, dword[g90]
    ; DEBUG

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


;============================================
; Normaliza el angulo entre [0, 360]
;============================================
normalize_angle: 
     ; if angle < 0: angle += 360
    ucomiss xmm0, dword [g0]
    jae .checkHigh           ; if angle >= 0 
    addss   xmm0, dword [g360]
.checkHigh:
    ; if angle >= 360  angle -= 360
    ucomiss xmm0, dword [g360]
    jb .done
    subss   xmm0, dword [g360]
.done:
    ret

;============================================
; Calucula el reflejo del angulo
;============================================
base_reflect: 
    movss   xmm0, dword [g180]         ; xmm0 = 180
    movss   xmm1, dword [currentAngle] ; xmm1 = old angle
    subss   xmm0, xmm1                 ; xmm0 = 180 - angle
    ret



;============================================
; Cambia la direccion de la pelota si rebota
; en la parte superior de la paleta
;============================================
global rebote_superior
rebote_superior: 
     ; invierte vx
    call    pelotaReverseX

    ; angle' = 180 - angle
    call    base_reflect        ; xmm0 = 180 - currentAngle

    ; angle' -= spin
    subss   xmm0, dword [gSpin]

    ; normalizar
    call    normalize_angle

    ; guardar
    movss   dword [currentAngle], xmm0

    ; actualizar bandera
    call    pelotaReboto

    ret
    

;============================================
; Cambia la direccion de la pelota si rebota
; en la parte inferior de la paleta
;============================================
global rebote_inferior
rebote_inferior: 
    ; invierte vx
    call    pelotaReverseX

    ; angle' = 180 - angle
    call    base_reflect        ; xmm0 = 180 - currentAngle

    ; angle' += spin
    addss   xmm0, dword [gSpin]

    ; normalizar
    call    normalize_angle

    ; guardar
    movss   dword [currentAngle], xmm0

    ; actualizar bandera
    call   pelotaReboto 

    ret

;============================================
; Cambia la direccion de la pelota si rebota
; en la parte central de la paleta
;============================================
global rebote_central
rebote_central: 

  ; 1. invierte la velocidad X
    call    pelotaReverseX

    mov     r8, [velocity_ptr]    ; velocity_vector
    movss   xmm1, dword [r8]          ; xmm1 = vx

    ucomiss xmm1, dword [g0]
    jb      .going_left          ; if vx < 0

    ; vx >= 0
    movss   xmm0, dword [g0]
    jmp     .store_angle

.going_left:
    ; vx < 0 
    movss   xmm0, dword [g180]

.store_angle:
    ; guardar nuevo ángulo global
    movss   dword [currentAngle], xmm0


    call   pelotaReboto 

    ret

global incrementar_velocidad
incrementar_velocidad: 

    ; Aumentar la velocidad 1
    movss xmm0, dword[one]
    movss xmm1, dword[speed]
    addss xmm1, xmm0 ; speed += 1

    mov al, byte[game_dificulty]

    ; easy level 
    cmp al, 0
    jne .checkMedium
    ucomiss xmm1, dword[easySpeedLimit]
    jb .endIncrementar
    movss xmm1, dword[easySpeedLimit]
    jmp .endIncrementar
.checkMedium:
    ; medium level
    cmp al, 1
    jne .checkHard
    ucomiss xmm1, dword[mediumSpeedLimit]
    jb .endIncrementar
    movss xmm1, dword[mediumSpeedLimit]
    jmp .endIncrementar
.checkHard:
    ; hard level
    ucomiss xmm1, dword[hardSpeedLimit]
    jb .endIncrementar
    movss xmm1, dword[hardSpeedLimit]

.endIncrementar:
    movss dword[speed], xmm1

    ret
    