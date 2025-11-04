section .data
    puntajeJugador: dd 0
    puntajeBot: dd 0
section .text

extern  isBallOpossingPlayer

extern  anotacion
anotacion: 
    call  isBallOpossingPlayer
    cmp eax, 1 ; if(ball is oposing ply)
    jne  .bot
    add dword[puntajeJugador], 1
    jmp .end 
.bot:
    add dword[puntajeBot], 1
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

