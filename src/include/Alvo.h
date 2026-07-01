#pragma once

#include "raylib/raylib.h"

typedef struct Alvo{
    Rectangle ret;
    Color cor;
    int hp;
    int tipo; //para alvos que vão valer mais
} Alvo;

void desenharAlvo(Alvo *alvo);
void desenharAlvos(Alvo *alvo, int quantidade);