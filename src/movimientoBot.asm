; Copyright [2025] B. Alfaro, D. Orias, E. Ramírez, J. Rodríguez
section .bss
  position_ptr: resq 1 
  ball_position_ptr: resq 1
  ball_velocity_ptr: resq 1
  upperLimit: resd 1
  lowerLimit: resd 1
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
  direction: resd 1        ; para el movimiento autonomo
=======
>>>>>>> d4e465a (Movimiento de bot actualizado con ayuda de Enrique)
=======
  direction: resd 1        ; para el movimiento autonomo
>>>>>>> c027da1 (Ajustes para que se mueva bien el bot cuando la bola no viene hacia el)
=======
>>>>>>> d4e465a (Movimiento de bot actualizado con ayuda de Enrique)

section .data
  vel: dd 3.5 ; Velocidad de bot
  negOne: dd -1.0
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
  one: dd 1.0
  zero: dd 0.0
=======
>>>>>>> d4e465a (Movimiento de bot actualizado con ayuda de Enrique)
=======
  one: dd 1.0
  zero: dd 0.0
>>>>>>> c027da1 (Ajustes para que se mueva bien el bot cuando la bola no viene hacia el)
=======
>>>>>>> d4e465a (Movimiento de bot actualizado con ayuda de Enrique)

section .text

global moverBot
global initBotMovement

initBotMovement: 
  movss dword[upperLimit], xmm0 ; upperLimit
  movss dword[lowerLimit], xmm1 ; lowerLimit
  mov [position_ptr], rdi ; puntero a position
  mov [ball_position_ptr], rsi
  mov [ball_velocity_ptr], rdx
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
=======
>>>>>>> c027da1 (Ajustes para que se mueva bien el bot cuando la bola no viene hacia el)
  
  ; Dirección inicial del bot (para movimiento automático)
  mov eax, dword[one]
  mov dword[direction], eax
<<<<<<< HEAD
  ret

moverBot:
  mov r8, [ball_position_ptr]
  mov r9, [ball_velocity_ptr]
  mov r10, [position_ptr]

  ; Verificar dirección de la pelota
  movss xmm1, [r9]         ; vx pelota
  movss xmm2, [zero]       ; 0.0
  ucomiss xmm1, xmm2       ; comparar vx con 0
  ja .movimiento_automatico ; Si vx > 0, movimiento automático

  ; sino sigue la pelota, viene hacia el
  movss xmm0, [r8+4]       ; y pelota
  movss xmm1, [r10+4]      ; y bot

  subss xmm0, xmm1         ; diferencia
=======
=======
>>>>>>> c027da1 (Ajustes para que se mueva bien el bot cuando la bola no viene hacia el)
  ret

moverBot:
  mov r8, [ball_position_ptr]
  mov r9, [ball_velocity_ptr]
  mov r10, [position_ptr]

  ; Verificar dirección de la pelota
  movss xmm1, [r9]         ; vx pelota
  movss xmm2, [zero]       ; 0.0
  ucomiss xmm1, xmm2       ; comparar vx con 0
  ja .movimiento_automatico ; Si vx > 0, movimiento automático

<<<<<<< HEAD
  subss xmm0, xmm1 ; diferencia
>>>>>>> d4e465a (Movimiento de bot actualizado con ayuda de Enrique)
=======
  ; sino sigue la pelota, viene hacia el
  movss xmm0, [r8+4]       ; y pelota
  movss xmm1, [r10+4]      ; y bot

  subss xmm0, xmm1         ; diferencia
>>>>>>> c027da1 (Ajustes para que se mueva bien el bot cuando la bola no viene hacia el)
=======
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
>>>>>>> d4e465a (Movimiento de bot actualizado con ayuda de Enrique)
  ; Valor absoluto
  movss xmm3, xmm0
  movss xmm4, xmm0
  movss xmm5, [negOne]
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
  mulss xmm4, xmm5         ; -diferencia
  maxss xmm3, xmm4         ; |diferencia|
  
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
  jmp .aplicar_limites

  ; si la bola no viene hacia el, usa el movimiento anterior
.movimiento_automatico:
  mov rax, [position_ptr]
  movss xmm1, dword [rax+4]  ; Posición actual en y
  movss xmm0, dword [vel]    ; Velocidad
  movss xmm2, dword [direction]  ; Dirección
  
  ; vel x direccion
  mulss xmm0, xmm2
  addss xmm1, xmm0
  
  ; limite superior
  movss xmm3, dword [upperLimit]
  ucomiss xmm1, xmm3
  jae .checkLower
  
  ; invertir
  movss xmm1, xmm3          ; y = upperLimit
  movss xmm4, dword [direction]   
  movss xmm5, dword [negOne]
  mulss xmm4, xmm5          ; direction * -1
  movss dword [direction], xmm4
  jmp .aplicar_limites
  
.checkLower:
  ; Verifica límite inferior
  movss xmm3, dword [lowerLimit]
  ucomiss xmm1, xmm3
  jbe .aplicar_limites
  
  ; invertir 
  movss xmm1, xmm3          ; y = lowerLimit
  movss xmm4, dword [direction]
  movss xmm5, dword [negOne]
  mulss xmm4, xmm5          ; direction * -1
  movss dword [direction], xmm4


=======
  mulss xmm4, xmm5 ; -diferencia
  maxss xmm3, xmm4 ; max(diferencia, -diferencia) = |diferencia|
=======
  mulss xmm4, xmm5         ; -diferencia
  maxss xmm3, xmm4         ; |diferencia|
>>>>>>> c027da1 (Ajustes para que se mueva bien el bot cuando la bola no viene hacia el)
  
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
  jmp .aplicar_limites

  ; si la bola no viene hacia el, usa el movimiento anterior
.movimiento_automatico:
  mov rax, [position_ptr]
  movss xmm1, dword [rax+4]  ; Posición actual en y
  movss xmm0, dword [vel]    ; Velocidad
  movss xmm2, dword [direction]  ; Dirección
  
<<<<<<< HEAD
; limites de la ventana
>>>>>>> d4e465a (Movimiento de bot actualizado con ayuda de Enrique)
=======
  ; vel x direccion
  mulss xmm0, xmm2
  addss xmm1, xmm0
  
  ; limite superior
  movss xmm3, dword [upperLimit]
  ucomiss xmm1, xmm3
  jae .checkLower
  
  ; invertir
  movss xmm1, xmm3          ; y = upperLimit
  movss xmm4, dword [direction]   
  movss xmm5, dword [negOne]
  mulss xmm4, xmm5          ; direction * -1
  movss dword [direction], xmm4
  jmp .aplicar_limites
  
.checkLower:
  ; Verifica límite inferior
  movss xmm3, dword [lowerLimit]
  ucomiss xmm1, xmm3
  jbe .aplicar_limites
  
  ; invertir 
  movss xmm1, xmm3          ; y = lowerLimit
  movss xmm4, dword [direction]
  movss xmm5, dword [negOne]
  mulss xmm4, xmm5          ; direction * -1
  movss dword [direction], xmm4


>>>>>>> c027da1 (Ajustes para que se mueva bien el bot cuando la bola no viene hacia el)
.aplicar_limites:
  movss xmm2, [upperLimit]
  maxss xmm1, xmm2
  movss xmm2, [lowerLimit]
  minss xmm1, xmm2
  
<<<<<<< HEAD
<<<<<<< HEAD
  movss [r10+4], xmm1
=======
  movss [r9+4], xmm1
>>>>>>> d4e465a (Movimiento de bot actualizado con ayuda de Enrique)
=======
  movss [r10+4], xmm1
>>>>>>> c027da1 (Ajustes para que se mueva bien el bot cuando la bola no viene hacia el)
=======
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
>>>>>>> d4e465a (Movimiento de bot actualizado con ayuda de Enrique)
  ret