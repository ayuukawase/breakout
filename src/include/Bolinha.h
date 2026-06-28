#pragma once

#include "raylib/raylib.h"

typedef struct Bolinha{
    Vector2 centro;
    float raio;
    Vector2 vel;
    Color cor;
} Bolinha;

void atualizarBolinha(Bolinha *bolinha, float delta);
void desenharBolinha(Bolinha *bolinha);