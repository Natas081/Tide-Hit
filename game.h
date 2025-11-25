#ifndef GAME_H
#define GAME_H

#include "raylib.h" 

#define MAX_SCORES 3
#define BLOCO_LINHAS 5
#define BLOCO_COLUNAS 10
#define MAX_PARTICULAS 200
#define MAX_BOLAS 6

#define TELA_MENU 0
#define TELA_JOGO 1
#define TELA_NOME_RECORDE 3
#define TELA_EXIBIR_RECORDE 4



#define LARGURA_TELA 800
#define ALTURA_TELA 600

typedef struct {
    float x;
    
    float y;
} Posicao;

typedef struct {
    float dx;
    float dy;
} Velocidade;

typedef struct {
    Posicao pos;
    int largura;
    char* simbolo;
} Jogador;

typedef struct {
    Posicao pos;
    Velocidade vel;
    char simbolo;
    Color cor;
    bool ativa;
} Bola;

typedef struct {
    char nome[4];
    int pontuacao;
} RegistroScore;

typedef struct Bloco {
    Rectangle rect;
    bool ativo;
    Color cor;
    int hp;
    struct Bloco *proximo;
} Bloco;

typedef struct {
    Vector2 pos;
    Vector2 vel;
    Color cor;
    float vida;
    bool ativa;
} Particula;

typedef struct {
    Vector2 pos;
    bool ativo;
    int tipo; 
} PowerUp;

typedef struct EstadoJogo {
    int telaLargura;
    int telaAltura;
    int pontuacao;
    int vidas;
    int nivel;
    int timerSpeed;
    int deveSair;
    int telaAtual;
    
    Jogador jogador;
    Bola bolas[MAX_BOLAS];
    Bloco *listaDeBlocos;
    
    int blocosAtivos;
    int blocosParaRespawnar;
    float timerAceleracao;
    float timerRespawn;

    float alturaMare;
    int nivelVelocidade;

    RegistroScore topScores[MAX_SCORES];
    char entradaNome[4];
    int indiceLetra;

    bool mostrarDicaControle;
    float timerDicaControle;

    Particula particulas[MAX_PARTICULAS];
    PowerUp powerupDrop;
    int tipoPowerupAtivo; 
    float timerPowerup;
    
    bool bolaPerfurante;
    float timerAncora;

} EstadoJogo;

EstadoJogo* criarEstadoInicial(int largura, int altura);
void liberarEstado(EstadoJogo* estado);
void atualizarJogo(EstadoJogo* estado);
void desenharTudo(EstadoJogo* estado, Texture2D logo, Texture2D imgRecorde, Texture2D imgTopScores);
void salvarTopScores(EstadoJogo* estado);


#endif
