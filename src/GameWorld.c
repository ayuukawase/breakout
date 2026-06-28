/**
 * @file GameWorld.c
 * @author Prof. Dr. David Buzatto
 * @brief GameWorld implementation.
 * 
 * @copyright Copyright (c) 2026
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "raylib/raylib.h"
//#include "raylib/raymath.h"
//#define RAYGUI_IMPLEMENTATION    // to use raygui, comment these three lines.
//#include "raylib/raygui.h"       // other compilation units must only include
//#undef RAYGUI_IMPLEMENTATION     // raygui.h

#include "Alvo.h"
#include "Bolinha.h"
#include "GameWorld.h"
#include "Jogador.h"
#include "ResourceManager.h"

void resolverColisaoBolinhaAlvos(Bolinha *b, Alvo * alvos, int quantidade, int *pontuacao);
void resolverColisaoBolinhaJogador(Bolinha *b, Jogador *j);

/**
 * @brief Creates a dinamically allocated GameWorld struct instance.
 */
GameWorld *createGameWorld(void){

    GameWorld *gw = (GameWorld*) malloc(sizeof(GameWorld));
    gw->pontuacao = 0;

    int largura = 150;
    int altura = 20;

    gw->jogador = (Jogador){
        .ret = {
            GetScreenWidth() / 2 - largura / 2, 
            GetScreenHeight() - 3 * altura,
            largura,
            altura
        },
        .velocidadeBase = 200,
        .velocidadeAtual = 0,
        .cor = WHITE
    };

    gw->bolinha = (Bolinha){
        .centro = {
            GetScreenWidth() / 2,
            gw->jogador.ret.y - gw->jogador.ret.width
        },
        .raio = 10,
        .vel = {200, -200},
        .cor = WHITE
    };

    gw->lin = 10;
    gw->col = 6;
    gw->alvos = (Alvo*) malloc(sizeof(Alvo) * gw->lin * gw->col);

    Color cores[10] = {
        GetColor(0xCC2F00FF), // #CC2F00
        GetColor(0xDB6600FF), // #DB6600
        GetColor(0xE39E00FF), // #E39E00
        GetColor(0x76B80DFF), // #76B80D
        GetColor(0x007668FF), // #007668
        GetColor(0x006486FF), // #006486
        GetColor(0x007CB5FF), // #007CB5
        GetColor(0x465AB2FF), // #465AB2
        GetColor(0x6D47B1FF), // #6D47B1
        GetColor(0x873B9CFF)  // #873B9C
    }; //{0, 255, 0, 255}rgb ou GetColor(0x0099ccff)
    //  (muda a cor dos alvos de maneira individual)

    int larguraAlvo = 80; //tamanho dos alvos
    int alturaAlvo = 20;
    int espaco = 5;
    int larguraTotal = larguraAlvo * gw->col + espaco * (gw->col - 1);
    int xIni = GetScreenWidth() / 2 - larguraTotal / 2;
    int yIni = 150;

    for(int i = 0; i < gw->lin; i++){
        for(int j = 0; j < gw->col; j++){
            int p = i * gw->col + j;
            gw->alvos[p] = (Alvo){
                .ret = {
                    .x = xIni + j * (larguraAlvo + espaco),
                    .y = yIni + i * (alturaAlvo + espaco),
                    .width = larguraAlvo,
                    .height = alturaAlvo,
                },
                .cor = cores[i],
                .hp = 1
            };
        }
    }

    return gw;
}

/**
 * @brief Destroys a GameWindow object and its dependecies.
 */
void destroyGameWorld(GameWorld *gw){
    free(gw->alvos); //libera os alvos antes de liberar o gw, nhe só boa pratica
    free(gw);
}

/**
 * @brief Reads user input and updates the state of the game.
 */
void updateGameWorld(GameWorld *gw, float delta){
    entradaJogador(&gw->jogador);
    atualizarJogador(&gw->jogador, delta);
    atualizarBolinha(&gw->bolinha, delta);

    resolverColisaoBolinhaAlvos(&gw->bolinha, gw->alvos, gw->lin * gw->col, &gw->pontuacao);
    resolverColisaoBolinhaJogador(&gw->bolinha, &gw->jogador);
}

/**
 * @brief Draws the state of the game.
 */
void drawGameWorld(GameWorld *gw){
    BeginDrawing();
    ClearBackground(BLACK);

    desenharJogador(&gw->jogador);
    desenharBolinha(&gw->bolinha);
    desenharAlvos(gw->alvos, gw->lin * gw->col);

    DrawText(TextFormat("Pontuação: %04d", gw->pontuacao), 20, 20, 25, WHITE);
    //texto, pos x, pos y, tamanho, cor

    EndDrawing();
}

void resolverColisaoBolinhaAlvos(Bolinha *b, Alvo * alvos, int quantidade, int *pontuacao){
    for(int i = 0; i < quantidade ; i++){
        Alvo *alvo = &alvos[i];
        if(alvo->hp > 0 && CheckCollisionCircleRec(b->centro, b->raio, alvo->ret)){
            alvo->hp--;
            *pontuacao += 10; //10p a cada alvo


            b->centro.y = alvo->ret.y + alvo->ret.height + b->raio;
            b->vel.y = fabs(b->vel.y);
            break; //um alvo por vez
        }
    }
}

void resolverColisaoBolinhaJogador(Bolinha *b, Jogador *j){
    if(CheckCollisionCircleRec(b->centro, b->raio, j->ret)){
        if(b->vel.y > 0){
            b->centro.y = j->ret.y - b->raio;
            b->vel.y = -fabs(b->vel.y); //faz a bolinha subir

            //muda a direção da bolinha dependendo de onde ela bateu no jogador
            float centroJogador = j->ret.x + j->ret.width / 2.0f;
            float distanciaCentro = b->centro.x - centroJogador;

            //muda a velx de acordo com a distancia do centro do j... frescurinhas
            b->vel.x = (distanciaCentro / (j->ret.width / 2.0f)) * 250.0f;
        }
    }
}