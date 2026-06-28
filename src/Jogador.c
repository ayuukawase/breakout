#include <stdlib.h>

#include "raylib/raylib.h"

#include "Jogador.h"

void entradaJogador(Jogador *j){
    int esquerda = IsKeyDown(KEY_LEFT) ? -1 : 0;
    int direita = IsKeyDown(KEY_RIGHT) ? 1 : 0;
    int movimento = esquerda + direita;

    j->velocidadeAtual = j->velocidadeBase * movimento;
}

void atualizarJogador(Jogador *j, float delta){
    j->ret.x += j->velocidadeAtual * delta;

    if(j->ret.x <= 0){
        j->ret.x = 0;
    }else if(j->ret.x + j->ret.width >= GetScreenWidth()){
        j->ret.x = GetScreenWidth() - j->ret.width;
    }
}

void desenharJogador(Jogador *j){
    DrawRectangleRec(j->ret, j->cor);
}