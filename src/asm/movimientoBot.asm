; Copyright [2025] B. Alfaro, D. Orias, E. Ramírez, J. Rodríguez
section .bss
  position_ptr: resq 1 
  upperLimit: resd 1
  lowerLimit: resd 1 
  direction: resd 1

section .data
  vel: dd 4.0
  negOne: dd -1.0

section .text

global moverBot
global initBotMovement

; Se inicializa el movimiento del bot
initBotMovement: 
  movss dword[upperLimit], xmm0 ; upperLimit
  movss dword[lowerLimit], xmm1 ; lowerLimit
  mov [position_ptr], rdi ; puntero a position
  
  ; Dirección inicial
  mov dword[direction], __?float32?__(1.0)
  ret

; El bot se mueve continuamente para arriba y abajo
; Cambia de dirección cuando toca los límites
moverBot:
  mov rax, [position_ptr]
  movss xmm0, dword [rax+4]        ; Poscion actual en eje y
  movss xmm1, dword [vel]          ; Velocidad
  movss xmm2, dword [direction]    ; Dirección
  
  ; Multiplica velocidad por dirección
  mulss xmm1, xmm2                 ; vel * direction
  addss xmm0, xmm1                 ; y += vel * direction
  
  ; Verifica si se llegó a límite superior
  movss xmm3, dword [upperLimit]
  ucomiss xmm0, xmm3
  jae .checkLower               ; si y >= upperLimit, chequea limite inferior
  
  ; Si, tocó el límite superior, invierte la dirección
  movss xmm0, xmm3                 ; y = upperLimit
  movss xmm4, dword [direction]   
  movss xmm5, dword [negOne]
  mulss xmm4, xmm5                 ; direction * -1
  movss dword [direction], xmm4
  jmp .updatePosition
  
.checkLower:
  ; Verifica límite inferior
  movss xmm3, dword [lowerLimit]
  ucomiss xmm0, xmm3
  jbe .updatePosition              ; si y <= lowerLimit, todo bien
  
  ; Si tocó el límite inferior, invierte dirección
  movss xmm0, xmm3                 ; y = lowerLimit
  movss xmm4, dword [direction]
  movss xmm5, dword [negOne]
  mulss xmm4, xmm5                 ; direction * -1
  movss dword [direction], xmm4
  
.updatePosition:
  movss dword [rax+4], xmm0
  ret
