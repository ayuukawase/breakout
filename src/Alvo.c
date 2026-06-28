#include "raylib/raylib.h"
#include "Alvo.h"

void desenharAlvo(Alvo *alvo){
    if(alvo->hp > 0){
        DrawRectangleRec(alvo->ret, alvo->cor);
    }
}

void desenharAlvos(Alvo *alvos, int quantidade){
    for(int i = 0; i < quantidade; i++){
        desenharAlvo(&alvos[i]);
    }
}