#include "raylib/raylib.h"
#include "Bolinha.h"

void atualizarBolinha(Bolinha *bolinha, float delta){
    bolinha->centro.x += bolinha->vel.x * delta;
    bolinha->centro.y += bolinha->vel.y * delta;

    if(bolinha->centro.x - bolinha->raio <= 0){
        bolinha->centro.x = bolinha->raio;
        bolinha->vel.x = -bolinha->vel.x;
    }else if(bolinha->centro.x + bolinha->raio >=GetScreenWidth()){
        bolinha->centro.x = GetScreenWidth() - bolinha->raio;
        bolinha->vel.x = -bolinha->vel.x;
    }

    if(bolinha->centro.y - bolinha->raio <= 0){
        bolinha->centro.y = bolinha->raio;
        bolinha->vel.y = -bolinha->vel.y;
    }else if(bolinha->centro.y + bolinha->raio >=GetScreenHeight()){
        bolinha->centro.y = GetScreenHeight() - bolinha->raio;
        bolinha->vel.y = -bolinha->vel.y;
    }
}
void desenharBolinha(Bolinha *bolinha){
    DrawCircleV(bolinha->centro, bolinha->raio, bolinha->cor);
}