; Copyright [2025] B. Alfaro, D. Orias, E. Ramírez, J. Rodríguez
section .bss
  position_ptr: resq 1 
  upperLimit: resd 1
  lowerLimit: resd 1 
  direction: resd 1
  ball_position_ptr: resq 1     ; Puntero a posicion de pelota
  ball_velocity_ptr: resq 1     ; Puntero a velocidad de pelota

section .data
  vel: dd 6.0 ; Velocidad de bot
  negOne: dd -1.0
  one: dd 1.0
  bot_speed: dd 6.0      
    
  valor_prediccion: dd 0.3
  prediction_min: dd 0.0
  prediction_max: dd 1.0
  abs_mask: dd 0x7FFFFFFF, 0, 0, 0

section .text

; Funciones que son llamadas desde C++
global moverBot
global initBotMovement


; Se inicializa el movimiento del bot
initBotMovement: 
  movss dword[upperLimit], xmm0 ; upperLimit
  movss dword[lowerLimit], xmm1 ; lowerLimit
  mov [position_ptr], rdi ; puntero a position
  
  ; Dirección inicial del bot
  mov eax, dword[one]
  mov dword[direction], eax
  mov [ball_position_ptr], rcx 
  mov [ball_velocity_ptr], r8
  ret

; El bot se mueve continuamente para arriba y abajo
; Cambia de direccion cuando toca los limites
moverBot:
  mov r8, [ball_position_ptr]
  movss xmm0, [r8+4]           ; y_actual de la pelota
    
  ; calcular posicion futura solo si la pelota viene hacia el bot (vx < 0)
  mov r9, [ball_velocity_ptr]
  movss xmm1, [r9]             ; vx de la pelota
  xorps xmm2, xmm2             ; xmm2 = 0.0
  ucomiss xmm1, xmm2 ;cmp
  jae .mover_sin_prediccion    ; Si vx >= 0, no aplicar prediccion
    
  ; Calcular prediccion: y_futura = y_actual + (vy * factor)
  movss xmm1, [r9+4]           ; vy de la pelota
  mulss xmm1, [valor_prediccion] ; vy * valor de prediccion
  addss xmm0, xmm1             ; y objetivo = y actual + (vy * valor de prediccion)
    
.mover_sin_prediccion:
    ;buscar que objetivo esta dentro de limites
    movss xmm1, [upperLimit]
    maxss xmm0, xmm1             ; max(y_objetivo, upperLimit)
    movss xmm1, [lowerLimit] 
    minss xmm0, xmm1             ; min(y_objetivo, lowerLimit)
    
    ;mover bot hacia y_objetivo
    mov r9, [position_ptr]       ; posicion actual del bot
    movss xmm1, [r9+4]           ; y_actual del bot
    
    ; Calcular dirección
    subss xmm0, xmm1             ; diferencia = objetivo - actual
    movss xmm2, xmm0             ; guardar diferencia para signo
    
    ; Valor absoluto de la diferencia
    movss xmm3, xmm0
    andps xmm3, [abs_mask]       ; |diferencia|
    
    ;cuantos pixeles se mueve, minimo entre movimiento necesario y maximo
    movss xmm4, [vel]
    minss xmm3, xmm4             ; min(|diferencia|, bot_speed)
    
    ; aplicar movimiento
    xorps xmm5, xmm5
    comiss xmm2, xmm5            ; comparar diferencia con 0
    jb .mover_abajo              ; si diferencia < 0, mover abajo
    
    ; mover arriba (diferencia > 0)
    addss xmm1, xmm3             ; y_bot += velocidad
    jmp .guardar_posicion
    
.mover_abajo:
    ; mover abajo (diferencia < 0)  
    subss xmm1, xmm3             ; y_bot -= velocidad
    
.guardar_posicion:
    ; guardar posicion
    movss [r9+4], xmm1
    
    ret
