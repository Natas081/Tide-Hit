#ifndef GAME_H
#define GAME_H


typedef struct {

    int x;
    int y;
}
Posicao;

typedef struct {
    int dx;
    int dy;
}Velocidade ;

typedef struct {
    Posicao pos;
    Velocidade vel;
    char simbolo;
} Bola;

typedef struct {
    Posicao pos;
    int largura;
    char* simbolo;
}Jogador;

typedef struct {
    Posicao pos;
    int largura;
    int resistencia;
    char* simbolo;
}
Bloco;


typedef struct NoBloco {
    Bloco bloco;
    struct NoBloco* proximo;
} NoBloco;

typedef struct {
    Jogador jogador;
    Bola bola;
    NoBloco* listaDeBlocos;

int pontuacao;
int recordeTotal;
int vidas;
int nivel;
int timerSpeed;
int telaLargura;
int telaAltura;

} EstadoJogo;

EstadoJogo* criarEstadoInicial(int largura, int altura);

void liberarEstado(EstadoJogo* estado);

void carregarNivel(EstadoJogo* estado, int nivel);

void atualizarJogador(EstadoJogo* estado, int tecla);

void atualizarBola(EstadoJogo* estado);

void verificarColisoes(EstadoJogo* estado);

void desenharTudo(EstadoJogo* estado);


#endif
