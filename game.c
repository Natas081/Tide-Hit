#include <stdlib.h>
#include <string.h>
#include "game.h"

#include "screen.h"
#include <stdio.h>

EstadoJogo* criarEstadoInicial(int largura, int altura) {

    EstadoJogo* e = malloc(sizeof(EstadoJogo));
    if(!e) return NULL;
//esse "e" é o estado
    e->telaLargura = largura;
    e->telaAltura = altura;
    e->pontuacao = 0;
    e->recordeTotal = 0;
    e->vidas = 3;
    e->nivel = 1;
    e->timerSpeed = 50;
    e->listaDeBlocos = NULL;

    e->jogador.largura = 7;
    e->jogador.pos.x = largura/2 - 3;
    e->jogador.pos.y = altura - 2;
    e->jogador.simbolo = "=======";

    e->bola.pos.x = largura/2;
    e->bola.pos.y = altura - 3;
    e->bola.vel.dx = 1;
    e->bola.vel.dy = -1;
    e->bola.simbolo = 'O';

    return e;
}

void liberarEstado(EstadoJogo* estado){
// esses voids eu vou atualzando dps
    free(estado);
}

void atualizarJogador(EstadoJogo* e, int tecla){


    if(tecla == 'a'){

    if(e->jogador.pos.x > 2){
            e->jogador.pos.x--;
        }
    } 
    else if (tecla == 'd') {

    int x_maximo = e->telaLargura - e->jogador.largura - 1;
    if(e->jogador.pos.x < x_maximo) {
        e->jogador.pos.x++;
    }
    }
}

void atualizarBola(EstadoJogo* e){

}

void verificarColisoes(EstadoJogo* e){

}

void desenharTudo(EstadoJogo* e){

    screenSetColor(WHITE, BLACK); 

    screenGotoxy(e->jogador.pos.x, e->jogador.pos.y);
    printf("%s", e->jogador.simbolo);



    screenSetColor(WHITE, BLACK);


    screenGotoxy(2, e->telaAltura - 1); 
    printf("RECORDE: %d    PONTOS: %d", e->recordeTotal, e->pontuacao);


    screenGotoxy(e->telaLargura - 10, e->telaAltura - 1);
    printf("VIDAS: %d", e->vidas);
}

void carregarNivel(EstadoJogo* e, int nivel){

}
