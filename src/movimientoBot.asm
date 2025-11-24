; Copyright [2025] B. Alfaro, D. Orias, E. Ramírez, J. Rodríguez
section .bss
  position_ptr: resq 1 
  ball_position_ptr: resq 1
  ball_velocity_ptr: resq 1
  upperLimit: resd 1
  lowerLimit: resd 1

section .data
  vel: dd 3.5 ; Velocidad de bot
  negOne: dd -1.0

section .text

; Funciones que son llamadas desde C++
global moverBot
global initBotMovement

; Se inicializa el movimiento del bot
initBotMovement: 
  movss dword[upperLimit], xmm0 ; upperLimit
  movss dword[lowerLimit], xmm1 ; lowerLimit
  mov [position_ptr], rdi ; puntero a position
  mov [ball_position_ptr], rsi
  mov [ball_velocity_ptr], rdx
  ret

; El bot se mueve continuamente para arriba y abajo
; Cambia de dirección cuando toca los límites
; El bot sigue a la pelota
moverBot:
  mov r8, [ball_position_ptr]
  mov r9, [position_ptr]

  movss xmm0, [r8+4] ; y pelota (para seguir la bola)
  movss xmm1, [r9+4] ; y bot

  subss xmm0, xmm1 ; diferencia
  ; Valor absoluto
  movss xmm3, xmm0
  movss xmm4, xmm0
  movss xmm5, [negOne]
  mulss xmm4, xmm5 ; -diferencia
  maxss xmm3, xmm4 ; max(diferencia, -diferencia) = |diferencia|
  
  ; Limitar velocidad
  movss xmm4, [vel]
  minss xmm3, xmm4
  
  ; Determinar dirección
  xorps xmm5, xmm5
  comiss xmm0, xmm5
  jb .mover_arriba
  
  addss xmm1, xmm3
  jmp .aplicar_limites
  
.mover_arriba:
  subss xmm1, xmm3
  
; limites de la ventana
.aplicar_limites:
  movss xmm2, [upperLimit]
  maxss xmm1, xmm2
  movss xmm2, [lowerLimit]
  minss xmm1, xmm2
  
  movss [r9+4], xmm1
  ret