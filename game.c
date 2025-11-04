#include <stdlib.h>
#include <string.h>
#include "game.h"

EstadoJogo* criarEstadoInicial(int largura, int altura) {

    EstadoJogo* e = malloc(sizeof(EstadoJogo));
    if(!e) return NULL;
//esse "e" é o estado
    e->telaLargura = largura;
    e->telaAltura = altura;
    e->pontuacao = 0;
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

void liberarEstado(EstadoJogo* e){
// esses voids eu vou atualzando dps
    free(e);
}

void atualizarJogador(EstadoJogo* e, int tecla){

}

void atualizarBola(EstadoJogo* e){

}

void verificarColisoes(EstadoJogo* e){

}

void desenharTudo(EstadoJogo* e){
}

void carregarNivel(EstadoJogo* e, int nivel){

}
