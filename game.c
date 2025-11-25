#include <stdlib.h>
#include <string.h>
#include "raylib.h"
#include "game.h"
#include <stdio.h> 
#include <math.h> 

#define SCORE_FILE "scores.dat"

void desenharTelaJogo(EstadoJogo* e);

void carregarTopScores(EstadoJogo* e) {
    FILE *f = fopen(SCORE_FILE, "rb");
    if (f) {
        size_t lidos = fread(e->topScores, sizeof(RegistroScore), MAX_SCORES, f);
        fclose(f);
        if (lidos != MAX_SCORES) {
             for(int i=0; i<MAX_SCORES; i++) {
                strcpy(e->topScores[i].nome, "---");
                e->topScores[i].pontuacao = 0;
            }
        }
    } else {
        for(int i=0; i<MAX_SCORES; i++) {
            strcpy(e->topScores[i].nome, "---");
            e->topScores[i].pontuacao = 0;
        }
    }
}

void salvarTopScores(EstadoJogo* e) {
    FILE *f = fopen(SCORE_FILE, "wb");
    if (f) {
        fwrite(e->topScores, sizeof(RegistroScore), MAX_SCORES, f);
        fclose(f);
    }
}

void inserirNovoRecorde(EstadoJogo* e) {
    int pos = -1;
    for(int i=0; i<MAX_SCORES; i++) {
        if(e->pontuacao > e->topScores[i].pontuacao) {
            pos = i;
            break;
        }
    }

    if(pos != -1) {
        for(int i = MAX_SCORES-1; i > pos; i--) {
            e->topScores[i] = e->topScores[i-1];
        }
        e->entradaNome[3] = '\0';
        strcpy(e->topScores[pos].nome, e->entradaNome);
        e->topScores[pos].pontuacao = e->pontuacao;
        salvarTopScores(e);
    }
}

void spawnarPowerUp(EstadoJogo* e, float x, float y) {
    if (!e->powerupDrop.ativo && (rand() % 100 < 15)) { 
        e->powerupDrop.ativo = true;
        e->powerupDrop.pos = (Vector2){ x, y };
        int r = rand() % 3;
        if (r == 0) e->powerupDrop.tipo = 1; 
        else if (r == 1) e->powerupDrop.tipo = 2; 
        else e->powerupDrop.tipo = 3; 
    }
}

void desenharFundoPraia(int largura, int altura) {
    Color areiaSeca  = (Color){ 245, 235, 215, 255 }; 
    Color areiaUmida = (Color){ 225, 200, 160, 255 }; 
    DrawRectangleGradientV(0, 0, largura, altura, areiaSeca, areiaUmida);
}

void limparBlocos(EstadoJogo* e) {
    Bloco *atual = e->listaDeBlocos;
    while (atual != NULL) {
        Bloco *proximo = atual->proximo;
        free(atual);
        atual = proximo;
    }
    e->listaDeBlocos = NULL;
    e->blocosAtivos = 0;
}

void respawnarBlocoAleatorio(EstadoJogo* e) {
    int larguraBloco = 60;
    int alturaBloco = 20;

    int espacoHorizontal = 20;
    int espacoVertical = 10;
    int offsetHorizontal = (e->telaLargura - (BLOCO_COLUNAS * (larguraBloco + espacoHorizontal)) + espacoHorizontal) / 2;
    int offsetVertical = 50;

    Color corHP3 = (Color){ 100, 100, 100, 255 }; 
    Color corHP2 = (Color){  30,  60, 180, 255 }; 
    Color corHP1 = (Color){ 200, 100, 100, 255 }; 

    int tentativas = 0;
    while (tentativas < 50) { 
        int i = rand() % BLOCO_LINHAS;
        int j = rand() % BLOCO_COLUNAS;

        float newX = offsetHorizontal + j * (larguraBloco + espacoHorizontal);
        float newY = offsetVertical + i * (alturaBloco + espacoVertical);
        
        bool slotOcupado = false;
        Bloco *blocoAtual = e->listaDeBlocos;

        while (blocoAtual != NULL) {
            if (blocoAtual->rect.x == newX && blocoAtual->rect.y == newY) {
                slotOcupado = true;
                break;
            }
            blocoAtual = blocoAtual->proximo;
        }

        if (!slotOcupado) {
            Bloco *novoBloco = (Bloco*)malloc(sizeof(Bloco));
            if (novoBloco == NULL) return; 

            novoBloco->rect.x = newX;
            novoBloco->rect.y = newY;
            novoBloco->rect.width = larguraBloco;
            novoBloco->rect.height = alturaBloco;
            novoBloco->ativo = true;
            
            if (i < 2) { novoBloco->hp = 3; novoBloco->cor = corHP3; }
            else if (i < 4) { novoBloco->hp = 2; novoBloco->cor = corHP2; }
            else { novoBloco->hp = 1; novoBloco->cor = corHP1; }
            
            novoBloco->proximo = e->listaDeBlocos;
            e->listaDeBlocos = novoBloco;
            e->blocosAtivos++;
            return; 
        }
        tentativas++;
    }
}

void carregarNivel(EstadoJogo* e, int nivel) {
    limparBlocos(e);

    int mapaNivel[BLOCO_LINHAS][BLOCO_COLUNAS] = {
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
    };

    int larguraBloco = 60;
    int alturaBloco = 20;
    int espacoHorizontal = 20;
    int espacoVertical = 10;

    int offsetHorizontal = (e->telaLargura - (BLOCO_COLUNAS * (larguraBloco + espacoHorizontal)) + espacoHorizontal) / 2;
    int offsetVertical = 50;
    
    Color corHP3 = (Color){ 100, 100, 100, 255 }; 
    Color corHP2 = (Color){  30,  60, 180, 255 }; 
    Color corHP1 = (Color){ 200, 100, 100, 255 };

    for (int i = 0; i < BLOCO_LINHAS; i++) {
        for (int j = 0; j < BLOCO_COLUNAS; j++) {
            if (mapaNivel[i][j] == 1) {
                Bloco *novoBloco = (Bloco*)malloc(sizeof(Bloco));
                if (novoBloco == NULL) return;
                
                novoBloco->rect.x = offsetHorizontal + j * (larguraBloco + espacoHorizontal);
                novoBloco->rect.y = offsetVertical + i * (alturaBloco + espacoVertical);
                novoBloco->rect.width = larguraBloco;
                novoBloco->rect.height = alturaBloco;
                novoBloco->ativo = true;
                
                if (i < 2) {
                    novoBloco->hp = 3;
                    novoBloco->cor = corHP3;
                } else if (i < 4) {
                    novoBloco->hp = 2;
                    novoBloco->cor = corHP2;
                } else {
                    novoBloco->hp = 1;
                    novoBloco->cor = corHP1;
                }
                
                novoBloco->proximo = e->listaDeBlocos;
                e->listaDeBlocos = novoBloco;
                e->blocosAtivos++;
            }
        }
    }
}

void initGame(EstadoJogo* e) {
    e->timerSpeed = 50;
    e->pontuacao = 0;
    e->vidas = 3;
    e->nivel = 1;
    e->nivelVelocidade = 0;
    
    e->jogador.largura = 100;
    e->jogador.pos.x = e->telaLargura / 2 - (e->jogador.largura / 2);
    e->jogador.pos.y = e->telaAltura - 60;
    
    for(int i=0; i<MAX_BOLAS; i++) e->bolas[i].ativa = false;
    
    e->bolas[0].ativa = true;
    e->bolas[0].pos.x = e->telaLargura / 2;
    e->bolas[0].pos.y = e->telaAltura - 70;
    e->bolas[0].cor = DARKBLUE;
    
    if (rand() % 2 == 0) e->bolas[0].vel.dx = -4;
    else e->bolas[0].vel.dx = 4;
    
    e->bolas[0].vel.dy = -4;
    
    e->mostrarDicaControle = true;
    e->timerDicaControle = 3.0f;
    
    e->timerRespawn = 0.2f;
    e->blocosParaRespawnar = 0;
    
    e->alturaMare = e->telaAltura + 100.0f;

    e->powerupDrop.ativo = false;
    e->tipoPowerupAtivo = 0;
    e->timerPowerup = 0;
    
    e->bolaPerfurante = false;
    e->timerAncora = 0.0f;

    carregarNivel(e, 1);
}

EstadoJogo* criarEstadoInicial(int largura, int altura) {
    EstadoJogo* e = malloc(sizeof(EstadoJogo));
    if (!e) return NULL;

    e->telaLargura = largura;
    e->telaAltura = altura;
    e->jogador.largura = 100;
    e->jogador.simbolo = "=======";
    e->deveSair = 0;
    e->listaDeBlocos = NULL;
    
    e->blocosAtivos = 0;
    e->blocosParaRespawnar = 0;
    e->timerRespawn = 0.0f;

    e->telaAtual = TELA_MENU;
    
    for(int i=0; i<MAX_BOLAS; i++) e->bolas[i].ativa = false;

    e->alturaMare = altura + 100.0f;

    carregarTopScores(e);
    initGame(e);

    return e;
}

void liberarEstado(EstadoJogo* estado) {
    salvarTopScores(estado);
    limparBlocos(estado);
    free(estado);
}

void atualizarJogo(EstadoJogo* e) {
    
    if (e->telaAtual == TELA_MENU) {
        if (IsKeyPressed(KEY_ENTER)) {
            e->telaAtual = TELA_COMO_JOGAR;
        }
        if (IsKeyPressed(KEY_ESCAPE)) {
            e->deveSair = 1;
        }
    }
    else if (e->telaAtual == TELA_COMO_JOGAR) {
        if (IsKeyPressed(KEY_ENTER)) {
            initGame(e);
            e->telaAtual = TELA_JOGO;
        }
    }
    else if (e->telaAtual == TELA_NOME_RECORDE) {
        int key = GetCharPressed();
        while (key > 0) {
            if (key >= 'a' && key <= 'z') key -= 32;

            if ((key >= 32) && (key <= 125) && (e->indiceLetra < 3)) {
                e->entradaNome[e->indiceLetra] = (char)key;
                e->indiceLetra++;
                e->entradaNome[e->indiceLetra] = '\0';
            }
            key = GetCharPressed();
        }
        if (IsKeyPressed(KEY_BACKSPACE)) {
            e->indiceLetra--;
            if (e->indiceLetra < 0) e->indiceLetra = 0;
            e->entradaNome[e->indiceLetra] = '\0';
        }
        if (IsKeyPressed(KEY_ENTER) && e->indiceLetra > 0) {
            inserirNovoRecorde(e);
            e->telaAtual = TELA_EXIBIR_RECORDE;
        }
    }
    else if (e->telaAtual == TELA_EXIBIR_RECORDE) {
        if (IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_ESCAPE)) {
            e->telaAtual = TELA_MENU;
        }
    }
    else if (e->telaAtual == TELA_JOGO) {
        if (e->mostrarDicaControle) {
            e->timerDicaControle -= GetFrameTime();
            if (e->timerDicaControle <= 0.0f) e->mostrarDicaControle = false;
        }

        if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) {
            if (e->jogador.pos.x > 0) e->jogador.pos.x -= 7;
        }
        if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) {
            if (e->jogador.pos.x < e->telaLargura - e->jogador.largura) e->jogador.pos.x += 7;
        }

        if (e->tipoPowerupAtivo == 1) { 
            e->timerPowerup -= GetFrameTime();
            if (e->timerPowerup <= 0) {
                e->tipoPowerupAtivo = 0;
                e->jogador.largura = 100;
            }
        }

        if (e->bolaPerfurante) {
            e->timerAncora -= GetFrameTime();
            if (e->timerAncora <= 0.0f) e->bolaPerfurante = false;
        }

        if (e->powerupDrop.ativo) {
            e->powerupDrop.pos.y += 2.0f;
            if (CheckCollisionRecs((Rectangle){e->powerupDrop.pos.x, e->powerupDrop.pos.y, 20, 20},
                                   (Rectangle){e->jogador.pos.x, e->jogador.pos.y, e->jogador.largura, 20})) {
                e->powerupDrop.ativo = false;
                if (e->powerupDrop.tipo == 1) {
                    e->tipoPowerupAtivo = 1;
                    e->jogador.largura = 160;
                    e->timerPowerup = 10.0f; 
                } else if (e->powerupDrop.tipo == 2) {
                    for(int k=0; k<MAX_BOLAS; k++) {
                        if(!e->bolas[k].ativa) {
                            e->bolas[k] = e->bolas[0];
                            e->bolas[k].pos.x = e->jogador.pos.x + e->jogador.largura/2;
                            e->bolas[k].pos.y = e->jogador.pos.y - 20;
                            e->bolas[k].vel.dy = -fabs(e->bolas[0].vel.dy);
                            e->bolas[k].vel.dx = (rand()%2 == 0) ? 4 : -4;
                            e->bolas[k].ativa = true;
                            break;
                        }
                    }
                } else if (e->powerupDrop.tipo == 3) {
                    e->bolaPerfurante = true; 
                    e->timerAncora = 6.0f;
                }
            }
            if (e->powerupDrop.pos.y > e->telaAltura) e->powerupDrop.ativo = false;
        }

        if (e->pontuacao >= 500) {
            float tempo = GetTime();
            float nivelBase = e->telaAltura - 200.0f; 
            float amplitude = 90.0f;                  
            e->alturaMare = nivelBase + (sin(tempo * 1.5f) * amplitude);
        } else {
            e->alturaMare = e->telaAltura + 100.0f;
        }

        int nivelAtualVelocidade = e->pontuacao / 350;
        if (nivelAtualVelocidade > e->nivelVelocidade) {
            e->nivelVelocidade = nivelAtualVelocidade;
            for(int i=0; i<MAX_BOLAS; i++) {
                if(e->bolas[i].ativa) {
                    e->bolas[i].vel.dx *= 1.15f; 
                    e->bolas[i].vel.dy *= 1.15f;
                }
            }
        }

        for(int i=0; i<MAX_BOLAS; i++) {
            if (!e->bolas[i].ativa) continue;

            float fatorVelocidade = 1.0f;
            if (e->bolas[i].pos.y > e->alturaMare) fatorVelocidade = 0.65f; 

            e->bolas[i].pos.x += e->bolas[i].vel.dx * fatorVelocidade;
            e->bolas[i].pos.y += e->bolas[i].vel.dy * fatorVelocidade;

            if (e->bolas[i].pos.y <= 10) {
                e->bolas[i].pos.y = 10;
                e->bolas[i].vel.dy *= -1;
            }
            if (e->bolas[i].pos.x <= 10) {
                e->bolas[i].pos.x = 10;
                e->bolas[i].vel.dx *= -1;
            }
            if (e->bolas[i].pos.x >= e->telaLargura - 10) {
                e->bolas[i].pos.x = e->telaLargura - 10;
                e->bolas[i].vel.dx *= -1;
            }

            if (e->bolas[i].pos.y >= e->telaAltura) {
                e->bolas[i].ativa = false;
            }
        }

        int bolasAtivas = 0;
        for(int i=0; i<MAX_BOLAS; i++) {
            if(e->bolas[i].ativa) bolasAtivas++;
        }

        if (bolasAtivas == 0) {
            e->vidas--;
            if (e->vidas <= 0) {
                if (e->pontuacao > e->topScores[MAX_SCORES-1].pontuacao) {
                    e->telaAtual = TELA_NOME_RECORDE;
                    e->indiceLetra = 0;
                    e->entradaNome[0] = '\0';
                } else {
                    e->telaAtual = TELA_EXIBIR_RECORDE;
                }
            } else {
                e->jogador.largura = 100;
                e->bolaPerfurante = false;
                e->tipoPowerupAtivo = 0;
                e->nivelVelocidade = e->pontuacao / 350; 

                e->jogador.pos.x = e->telaLargura / 2 - (e->jogador.largura / 2);
                e->jogador.pos.y = e->telaAltura - 60;
                
                for(int i=1; i<MAX_BOLAS; i++) e->bolas[i].ativa = false;
                
                e->bolas[0].ativa = true;
                e->bolas[0].pos.x = e->telaLargura / 2;
                e->bolas[0].pos.y = e->telaAltura - 70;
                
                if (rand() % 2 == 0) e->bolas[0].vel.dx = -4;
                else e->bolas[0].vel.dx = 4;
                e->bolas[0].vel.dy = -4;

                float multiplicador = 1.0f + (e->nivelVelocidade * 0.15f);
                e->bolas[0].vel.dx *= multiplicador;
                e->bolas[0].vel.dy *= multiplicador;
            }
        }

        if (e->blocosAtivos <= (BLOCO_LINHAS*BLOCO_COLUNAS)*0.3 && e->blocosParaRespawnar == 0) {
            e->blocosParaRespawnar = 12;
        }
        if (e->blocosParaRespawnar > 0) {
            e->timerRespawn -= GetFrameTime();
            if (e->timerRespawn <= 0.0f) {
                respawnarBlocoAleatorio(e);
                e->blocosParaRespawnar--;
                e->timerRespawn = 0.2f;
            }
        }

        Rectangle jogadorRect = { (float)e->jogador.pos.x, (float)e->jogador.pos.y, (float)e->jogador.largura, 20.0f };

        for(int i=0; i<MAX_BOLAS; i++) {
            if(!e->bolas[i].ativa) continue;

            Vector2 bolaCentro = { (float)e->bolas[i].pos.x, (float)e->bolas[i].pos.y };
            float bolaRaio = 10.0f;

            if (CheckCollisionCircleRec(bolaCentro, bolaRaio, jogadorRect)) {
                if (e->bolas[i].vel.dy > 0) {
                    float centroJogador = e->jogador.pos.x + e->jogador.largura / 2.0f;
                    float diferenca = e->bolas[i].pos.x - centroJogador;
                    float normalizado = diferenca / (e->jogador.largura / 2.0f);
                    if (normalizado > 0.9f) normalizado = 0.9f;
                    if (normalizado < -0.9f) normalizado = -0.9f;
                    
                    float magnitudeAtual = sqrt(pow(e->bolas[i].vel.dx, 2) + pow(e->bolas[i].vel.dy, 2));
                    
                    e->bolas[i].vel.dx = normalizado * magnitudeAtual;
                    float restoVelocidade = pow(magnitudeAtual, 2) - pow(e->bolas[i].vel.dx, 2);
                    if (restoVelocidade < 0) restoVelocidade = 0;

                    e->bolas[i].vel.dy = -sqrt(restoVelocidade); 
                    e->bolas[i].pos.y = e->jogador.pos.y - bolaRaio - 2.0f;
                }
            }
            
            Bloco *blocoAtual = e->listaDeBlocos;
            Bloco *blocoAnterior = NULL;

            while (blocoAtual != NULL) {
                Bloco *proximoBloco = blocoAtual->proximo;

                if (blocoAtual->ativo) {
                    if (CheckCollisionCircleRec(bolaCentro, bolaRaio, blocoAtual->rect)) {
                        
                        spawnarPowerUp(e, blocoAtual->rect.x + blocoAtual->rect.width/2, blocoAtual->rect.y);

                        if (!e->bolaPerfurante) e->bolas[i].vel.dy *= -1;
                        
                        e->pontuacao += 10;
                        blocoAtual->hp--;
                        
                        if (e->bolaPerfurante) blocoAtual->hp = 0;

                        if (blocoAtual->hp == 2) blocoAtual->cor = (Color){ 30, 60, 180, 255 }; 
                        else if (blocoAtual->hp == 1) blocoAtual->cor = (Color){ 200, 100, 100, 255 };

                        if (blocoAtual->hp <= 0) {
                            if (blocoAnterior == NULL) e->listaDeBlocos = proximoBloco;
                            else blocoAnterior->proximo = proximoBloco;
                            
                            free(blocoAtual);
                            blocoAtual = NULL; 
                            e->blocosAtivos--;
                        }
                        
                        if (!e->bolaPerfurante) break; 
                    }
                }

                if (blocoAtual == NULL) {
                    blocoAtual = proximoBloco;
                } else {
                    blocoAnterior = blocoAtual;
                    blocoAtual = proximoBloco;
                }
            }
        }
    }
}
void desenharTelaJogo(EstadoJogo* e) {
    desenharFundoPraia(e->telaLargura, e->telaAltura);

    Bloco *blocoAtual = e->listaDeBlocos;
    while (blocoAtual != NULL) {
        if (blocoAtual->ativo) {
            DrawRectangleRec(blocoAtual->rect, blocoAtual->cor);
            DrawRectangleLinesEx(blocoAtual->rect, 1, DARKGRAY); 
        }
        blocoAtual = blocoAtual->proximo;
    }

    if (e->powerupDrop.ativo) {
        Color pColor = WHITE;
        if (e->powerupDrop.tipo == 1) pColor = GREEN;
        else if (e->powerupDrop.tipo == 2) pColor = RED;
        else pColor = DARKGRAY;
        
        DrawCircleV(e->powerupDrop.pos, 10, pColor);
        DrawText(e->powerupDrop.tipo == 3 ? "A" : (e->powerupDrop.tipo == 2 ? "2x" : "W"), 
                 e->powerupDrop.pos.x - 5, e->powerupDrop.pos.y - 10, 20, WHITE);
    }

    Color corPlayer = BLACK;
    if (e->bolaPerfurante) corPlayer = DARKGRAY;
    if (e->tipoPowerupAtivo == 1) corPlayer = DARKGREEN;

    DrawRectangle(e->jogador.pos.x, e->jogador.pos.y, e->jogador.largura, 20, corPlayer);
    
    for(int i=0; i<MAX_BOLAS; i++) {
        if(e->bolas[i].ativa) {
             DrawCircleV((Vector2){(float)e->bolas[i].pos.x, (float)e->bolas[i].pos.y}, 10, e->bolaPerfurante ? DARKGRAY : e->bolas[i].cor);
        }
    }

    int alturaAgua = e->telaAltura - (int)e->alturaMare;
    
    if (alturaAgua > 0) {
        DrawRectangle(0, (int)e->alturaMare, e->telaLargura, alturaAgua, Fade(SKYBLUE, 0.6f));
        DrawRectangle(0, (int)e->alturaMare - 2, e->telaLargura, 5, Fade(WHITE, 0.6f));
    }

    int recordeAtual = 0;
    char nomeRecorde[4] = "---";

    if (e->topScores[0].pontuacao > 0) {
        recordeAtual = e->topScores[0].pontuacao;
        strcpy(nomeRecorde, e->topScores[0].nome);
    }
    
    DrawText(TextFormat("RECORDE (%s): %d", nomeRecorde, recordeAtual), 20, 10, 20, DARKBLUE);
    
    const char* textoPontos = TextFormat("PONTOS: %d", e->pontuacao);
    DrawText(textoPontos, e->telaLargura / 2 - MeasureText(textoPontos, 20)/2, 10, 20, DARKBLUE);
    
    const char* textoVidas = TextFormat("VIDAS: %d", e->vidas);
    DrawText(textoVidas, e->telaLargura - MeasureText(textoVidas, 20) - 20, 10, 20, DARKBLUE);
    
    if (e->bolaPerfurante) {
        DrawText(TextFormat("ANCORA: %.1f", e->timerAncora), 20, 40, 20, DARKGRAY);
    }

    if (e->mostrarDicaControle) {
        DrawText("Use 'a' e 'd' para mover", e->telaLargura / 2 - 100, e->telaAltura / 2, 20, DARKGRAY);
    }
}

void desenharTudo(EstadoJogo* e, Texture2D logo, Texture2D imgRecorde, Texture2D imgTopScores, Texture2D imgComoJogar) { 
    
    if (e->telaAtual == TELA_MENU) {
        Rectangle source = { 0.0f, 0.0f, (float)logo.width, (float)logo.height };
        Rectangle dest = { 0.0f, 0.0f, (float)e->telaLargura, (float)e->telaAltura };
        Vector2 origin = { 0.0f, 0.0f };
        DrawTexturePro(logo, source, dest, origin, 0.0f, WHITE);
    }
    else if (e->telaAtual == TELA_COMO_JOGAR) {
        Rectangle source = { 0.0f, 0.0f, (float)imgComoJogar.width, (float)imgComoJogar.height };
        Rectangle dest = { 0.0f, 0.0f, (float)e->telaLargura, (float)e->telaAltura };
        Vector2 origin = { 0.0f, 0.0f };
        DrawTexturePro(imgComoJogar, source, dest, origin, 0.0f, WHITE);
    }
    else if (e->telaAtual == TELA_JOGO) {
        desenharTelaJogo(e);
    }
    else if (e->telaAtual == TELA_NOME_RECORDE) {
        Rectangle source = { 0.0f, 0.0f, (float)imgRecorde.width, (float)imgRecorde.height };
        Rectangle dest = { 0.0f, 0.0f, (float)e->telaLargura, (float)e->telaAltura };
        Vector2 origin = { 0.0f, 0.0f };
        DrawTexturePro(imgRecorde, source, dest, origin, 0.0f, WHITE);

        const char* txtTitulo = "NOVO RECORDE!";
        const char* txtPontos = TextFormat("Pontos: %d", e->pontuacao);
        const char* txtPrompt = "Digite seu nome (3 letras):";
        const char* txtNome = e->entradaNome;

        int xTitulo = e->telaLargura/2 - MeasureText(txtTitulo, 30)/2;
        int xPontos = e->telaLargura/2 - MeasureText(txtPontos, 20)/2;
        int xPrompt = e->telaLargura/2 - MeasureText(txtPrompt, 20)/2;
        int xNome = e->telaLargura/2 - MeasureText(txtNome, 40)/2;

        DrawText(txtTitulo, xTitulo, 180, 30, YELLOW);
        DrawText(txtPontos, xPontos, 230, 20, WHITE);
        DrawText(txtPrompt, xPrompt, 260, 20, SKYBLUE);
        DrawText(txtNome, xNome, 300, 40, WHITE);
    }
    else if (e->telaAtual == TELA_EXIBIR_RECORDE) {
        Rectangle source = { 0.0f, 0.0f, (float)imgTopScores.width, (float)imgTopScores.height };
        Rectangle dest = { 0.0f, 0.0f, (float)e->telaLargura, (float)e->telaAltura };
        Vector2 origin = { 0.0f, 0.0f };
        DrawTexturePro(imgTopScores, source, dest, origin, 0.0f, WHITE);
        
        const char* titulo = "TOP 3 RECORDES";
        int larguraTitulo = MeasureText(titulo, 30);
        DrawText(titulo, e->telaLargura/2 - larguraTitulo/2, 150, 30, YELLOW);

        for(int i=0; i<MAX_SCORES; i++) {
            const char* textoRecorde = TextFormat("%d. %s ....... %d", i+1, e->topScores[i].nome, e->topScores[i].pontuacao);
            int larguraTexto = MeasureText(textoRecorde, 20);
            DrawText(textoRecorde, e->telaLargura/2 - larguraTexto/2, 220 + (i*50), 20, WHITE);
        }
        
        const char* prompt = "Pressione ENTER para voltar";
        int larguraPrompt = MeasureText(prompt, 20);
        DrawText(prompt, e->telaLargura/2 - larguraPrompt/2, e->telaAltura - 80, 20, DARKBLUE);
    }
}