section .data
    puntajeJugador: dd 0
    puntajeBot: dd 0
section .text

extern  isBallOpossingPlayer

global  anotacion
anotacion: 
    call  isBallOpossingPlayer
    cmp eax, 1 ; if(ball is oposing ply)
    jne  .bot
    add dword[puntajeJugador], 1
    cmp dword[puntajeJugador], 100
    jl .end
    mov dword[puntajeJugador], 99
    jmp .end 
.bot:
    add dword[puntajeBot], 1
    cmp dword[puntajeBot], 100
    jl .end
    mov dword[puntajeBot], 99
.end:
    ret
    
global getPlyScore
getPlyScore: 
    mov eax, dword[puntajeJugador]
    ret

global getBotScore
getBotScore: 
    mov eax, dword[puntajeBot]
    ret

global resetScore
resetScore: 
    mov dword[puntajeBot], 0
    mov dword[puntajeJugador], 0
    ret
