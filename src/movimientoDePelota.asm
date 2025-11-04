; Copyright [2025] B. Alfaro, D. Orias, E. Ramírez, J. Rodríguez

; ===========================
; Sección BSS: punteros y límites (no inicializados)
; ===========================
section .bss
    velocity_ptr: resq 1        ; puntero (qword) al vector de velocidad {vx, vy}
    position_ptr: resq 1        ; puntero (qword) al vector de posición {x, y}
    upperLimit:   resd 1        ; límite superior pantalla (int)
    lowerLimit:   resd 1        ; límite inferior pantalla (int)

; ===========================
; Sección DATA: constantes y estado del juego
; ===========================
section .data
    game_dificulty: db 0        ; 0: easy, 1: medium, 2: hard

    negSign: dd -1.0            ; -1.0 (para invertir signos)
    one: dd 1.0                 ; 1.0

    ; Velocidad
    n10: dd 10.0
    speed: dd 10.0              ; velocidad actual de la bola

    easySpeedLimit:     dd 15.0
    mediumSpeedLimit:   dd 20.0
    hardSpeedLimit:     dd 20.0

    isOpposingPlayer: dd 0      ; bandera: 1 si el ángulo va hacia el oponente
    currentAngle: dd 0          ; ángulo actual en grados
    DEG2RAD:    dd 0.0174532925 ; conversión a radianes

    minAngle: dd 0              ; ángulo mínimo para aleatorio
    maxAngle: dd 360            ; ángulo máximo para aleatorio

    defaultAngle: dd 45.0       ; ángulo por defecto si cae en bandas prohibidas

    ; Grados de ayuda
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

    gSpin: dd 20.0              ; “efecto” para rebotes superior/inferior

; ===========================
; Sección TEXT: código
; ===========================
section .text
extern  GetRandomValue          ; int GetRandomValue(int min, int max)
extern  cosf                    ; float cosf(float)
extern  sinf                    ; float sinf(float)

; Exportadas a C++
global isBallOpossingPlayer
global pelotaMove
global initPelotaMovement
global resetBall
global pelotaReboto
global pelotaReverseX
global pelotaReverseY
global setBallSpeed
global setDifficulty
global getCurrentAngle
global getIsOpposingPlayer
global getGameDifficulty
global setCurrentAngle

; ------------------------------------------------------------
; _isBallOpossingPlayer (interno): evalúa si el ángulo ∈ [90,270]
;   - Si 90 <= angle <= 270 → isOpposingPlayer = 1
;   - Caso contrario → 0
; ------------------------------------------------------------
_isBallOpossingPlayer: 
    mov dword[isOpposingPlayer], 0

    movss xmm0, dword[currentAngle] ; xmm0 = angle
    movss xmm1, dword[g90]          ; xmm1 = 90

    ; if angle < 90 → salir (sigue en 0)
    ucomiss xmm0, xmm1
    jb .endCheck

.check2:
    movss xmm1, dword[g270]         ; xmm1 = 270
    ; if angle > 270 → salir (sigue en 0)
    ucomiss xmm0, xmm1
    ja .endCheck

    ; aquí: 90 <= angle <= 270
    mov dword[isOpposingPlayer], 1

.endCheck:
    ret

; ------------------------------------------------------------
; isBallOpossingPlayer(): retorna bandera isOpposingPlayer
; ------------------------------------------------------------
isBallOpossingPlayer: 
    xor rax, rax
    mov eax, dword[isOpposingPlayer]
    ret

; ------------------------------------------------------------
; setBallSpeed(xmm0): establece velocidad (float)
; ------------------------------------------------------------
setBallSpeed: 
    movss dword[speed], xmm0
    ret

; ------------------------------------------------------------
; setDifficulty(dil): cambia dificultad (0/1/2)
;   dil = registro bajo de rdi (char)
; ------------------------------------------------------------
setDifficulty: 
    mov byte[game_dificulty], dil
    ret

; ------------------------------------------------------------
; pelotaMove(): position += velocity
;   Usa velocity_ptr y position_ptr
; ------------------------------------------------------------
pelotaMove: 
    mov r8, [velocity_ptr]

    vmovss xmm0, [r8]        ; vx
    vmovss xmm1, [r8+4]      ; vy

    mov r9, [position_ptr]

    vmovss xmm2, [r9]        ; x
    vmovss xmm3, [r9+4]      ; y

    vaddss xmm2, xmm0        ; x += vx   (2-op: dst = dst + src)
    vaddss xmm3, xmm1        ; y += vy

    vmovss dword [r9],   xmm2
    vmovss dword [r9+4], xmm3

    ret

; ------------------------------------------------------------
; initPelotaMovement(rdi=vel*, rsi=pos*, edx=upper, ecx=lower)
; Guarda punteros y límites
; ------------------------------------------------------------
initPelotaMovement: 
    mov [velocity_ptr], rdi
    mov [position_ptr], rsi
    mov [upperLimit], edx
    mov [lowerLimit], ecx
    ret

; ------------------------------------------------------------
; pelotaReboto(): conmuta isOpposingPlayer
; ------------------------------------------------------------
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

; ------------------------------------------------------------
; pelotaReverseX(): invierte vx
; ------------------------------------------------------------
pelotaReverseX: 
    mov rax, [velocity_ptr] ; rax -> vx
    call  reverse
    ret

; ------------------------------------------------------------
; pelotaReverseY(): invierte vy
; ------------------------------------------------------------
pelotaReverseY: 
    mov rax, [velocity_ptr]
    add rax, 4              ; rax -> vy
    call  reverse
    ret

; ------------------------------------------------------------
; reverse(): *rax = -(*rax)  (float)
; ------------------------------------------------------------
reverse: 
    vmovss xmm0, dword[rax]     ; cargar valor
    vmovss xmm1, dword[negSign] ; -1.0
    vmulss xmm2, xmm0, xmm1     ; xmm2 = -valor
    vmovss dword[rax], xmm2     ; guardar
    ret

; ------------------------------------------------------------
; resetBall(): resetea velocidad/ángulo y calcula nueva velocidad
;             según ángulo aleatorio (evita bandas 60-120 y 240-300)
; ------------------------------------------------------------
resetBall: 
    ; velocidad por defecto
    movss xmm0, [n10]
    movss dword[speed], xmm0

    ; ángulo aleatorio en [minAngle, maxAngle]
    mov edi, [minAngle]
    mov esi, [maxAngle]
    call  GetRandomValue
    cvtsi2ss xmm0, eax       ; xmm0 = float(angle)

    ; Si 60 <= angle <= 120 → usar defaultAngle
    vmovss xmm1, dword[g60]
    ucomiss xmm0, xmm1
    jb .fine
    vmovss xmm1, dword[g120]
    ucomiss xmm0, xmm1
    ja .check2
    jmp .change

    ; DEBUG:
    ; movss xmm0, dword[g0]

; Si 240 <= angle <= 300 → usar defaultAngle
.check2:
    ; DEBUG:
    ; movss xmm0, dword[g180]
    vmovss xmm1, dword[g240]
    ucomiss xmm0, xmm1
    jb .fine
    vmovss xmm1, dword[g300]
    ucomiss xmm0, xmm1
    ja .fine

.change:
    ; DEBUG:
    ; movss xmm0, dword[g180]
    movss xmm0, [defaultAngle]

.fine:
    ; DEBUG:
    ; movss xmm0, dword[g90]

    ; Construir vector velocidad desde el ángulo y speed
    mov     r8, [velocity_ptr]
    sub     rsp, 16
    movss   [rsp], xmm0          ; guardar ángulo (grados) en la pila

    ; vx = cos(angle*DEG2RAD) * speed
    mulss   xmm0, dword [DEG2RAD]
    call    cosf
    mulss   xmm0, dword [speed]
    movss   dword [r8], xmm0

    ; vy = sin(angle*DEG2RAD) * speed
    movss   xmm0, dword [rsp]    ; restaurar ángulo (grados)
    mulss   xmm0, dword [DEG2RAD]
    call    sinf
    mulss   xmm0, dword [speed]
    movss   dword [r8+4], xmm0

    ; guardar ángulo global
    movss xmm0, dword[rsp]
    movss dword[currentAngle], xmm0
    add     rsp, 16

    ; actualizar bandera de oposición
    call  _isBallOpossingPlayer
    ret

; ------------------------------------------------------------
; normalize_angle(xmm0): normaliza xmm0 a [0, 360)
;   Entrada/Salida: xmm0 = ángulo
; ------------------------------------------------------------
normalize_angle: 
    ; if angle < 0 → +360
    ucomiss xmm0, dword [g0]
    jae .checkHigh
    addss   xmm0, dword [g360]
.checkHigh:
    ; if angle >= 360 → -360
    ucomiss xmm0, dword [g360]
    jb .done
    subss   xmm0, dword [g360]
.done:
    ret

; ------------------------------------------------------------
; base_reflect(): devuelve (180 - currentAngle) en xmm0
; ------------------------------------------------------------
base_reflect: 
    movss   xmm0, dword [g180]         ; 180
    movss   xmm1, dword [currentAngle] ; currentAngle
    subss   xmm0, xmm1                 ; 180 - angle
    ret

; ------------------------------------------------------------
; rebote_superior(): invierte vx y aplica reflejo “hacia arriba”
;   angle' = normalize((180 - angle) - spin)
; ------------------------------------------------------------
global rebote_superior
rebote_superior: 
    call    pelotaReverseX             ; invierte vx

    call    base_reflect               ; xmm0 = 180 - angle
    subss   xmm0, dword [gSpin]        ; - spin
    call    normalize_angle            ; normalizar

    movss   dword [currentAngle], xmm0 ; guardar nuevo ángulo
    call    pelotaReboto               ; alternar bandera de oposición
    ret

; ------------------------------------------------------------
; rebote_inferior(): invierte vx y aplica reflejo “hacia abajo”
;   angle' = normalize((180 - angle) + spin)
; ------------------------------------------------------------
global rebote_inferior
rebote_inferior: 
    call    pelotaReverseX

    call    base_reflect               ; xmm0 = 180 - angle
    addss   xmm0, dword [gSpin]        ; + spin
    call    normalize_angle

    movss   dword [currentAngle], xmm0
    call   pelotaReboto
    ret

; ------------------------------------------------------------
; rebote_central(): rebote en zona central de la paleta
;   - Invierte vx
;   - Fija ángulo exactamente a 0° si vx>=0, o 180° si vx<0
;   (NÓTESE: aquí no hay easing, es un “snap” duro por diseño actual)
; ------------------------------------------------------------
global rebote_central
rebote_central: 
    ; invierte la velocidad X
    call    pelotaReverseX

    mov     r8, [velocity_ptr]         ; cargar vx
    movss   xmm1, dword [r8]           ; xmm1 = vx

    ; si vx < 0 → 180°, si no → 0°
    ucomiss xmm1, dword [g0]
    jb      .going_left
    movss   xmm0, dword [g0]           ; target = 0°
    jmp     .store_angle

.going_left:
    movss   xmm0, dword [g180]         ; target = 180°

.store_angle:
    movss   dword [currentAngle], xmm0 ; guardar nuevo ángulo
    call   pelotaReboto
    ret

; ------------------------------------------------------------
; incrementar_velocidad(): speed += 1, saturada por dificultad
;   - easy:  <= 15
;   - medium:<= 20
;   - hard:  <= 20
; ------------------------------------------------------------
global incrementar_velocidad
incrementar_velocidad: 
   ; Guardar speed viejo
    vmovss xmm4, dword [speed]      ; xmm4 = old_speed

    ; Aumentar la velocidad 1
    vmovss xmm0, dword [one]        ; 1.0
    vmovss xmm1, dword [speed]      ; xmm1 = speed
    addss  xmm1, xmm0               ; xmm1 = speed + 1

    mov    al, byte [game_dificulty]

    ; easy (0)
    cmp    al, 0
    jne    .checkMedium
    ucomiss xmm1, dword [easySpeedLimit]
    jb     .storeNew
    vmovss xmm1, dword [easySpeedLimit]
    jmp    .storeNew

.checkMedium:
    ; medium (1)
    cmp    al, 1
    jne    .checkHard
    ucomiss xmm1, dword [mediumSpeedLimit]
    jb     .storeNew
    vmovss xmm1, dword [mediumSpeedLimit]
    jmp    .storeNew

.checkHard:
    ; hard (2)
    ucomiss xmm1, dword [hardSpeedLimit]
    jb     .storeNew
    vmovss xmm1, dword [hardSpeedLimit]

.storeNew:
    ; Escribir nueva speed
    vmovss dword [speed], xmm1      ; [speed] = new_speed

    ; === Re-escalar el vector de velocidad ===
    ; Si old_speed == 0 → recalcular con trig (evitar /0)
    ucomiss xmm4, dword [g0]        ; old_speed ? 0.0
    jne    .scaleVector

    ; old_speed == 0.0 → recomputar vx,vy desde currentAngle
    ; vx = cos(angle*DEG2RAD)*speed ; vy = sin(...) * speed
    vmovss xmm0, dword [currentAngle]
    mulss  xmm0, dword [DEG2RAD]
    call   cosf
    mulss  xmm0, dword [speed]
    mov    r8, [velocity_ptr]
    vmovss dword [r8], xmm0         ; vx

    vmovss xmm0, dword [currentAngle]
    mulss  xmm0, dword [DEG2RAD]
    call   sinf
    mulss  xmm0, dword [speed]
    vmovss dword [r8+4], xmm0       ; vy
    ret

.scaleVector:
    ; factor = new_speed / old_speed
    divss  xmm1, xmm4               ; xmm1 = factor

    mov    r8, [velocity_ptr]

    ; vx *= factor
    vmovss xmm0, dword [r8]
    mulss  xmm0, xmm1
    vmovss dword [r8], xmm0

    ; vy *= factor
    vmovss xmm0, dword [r8+4]
    mulss  xmm0, xmm1
    vmovss dword [r8+4], xmm0

    ret

getCurrentAngle:
    movss xmm0, [currentAngle]
    ret

getIsOpposingPlayer:
    mov eax, [isOpposingPlayer]
    ret

getGameDifficulty:
    movzx eax, byte [game_dificulty]
    ret

setCurrentAngle:
    movss dword [currentAngle], xmm0
    ret