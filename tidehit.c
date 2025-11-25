#include "raylib.h"
#include "game.h"
#include <stdlib.h> 
#include <time.h>

int main(void){

    SetConfigFlags(FLAG_WINDOW_HIGHDPI);
    InitWindow(LARGURA_TELA, ALTURA_TELA, "Tide Hit!");
    InitAudioDevice();
    srand(time(NULL));

    Texture2D logo = LoadTexture("Imagem_menu.png"); 
    Texture2D imgRecorde = LoadTexture("Imagem_inserir_recorde.png");
    Texture2D imgTopScores = LoadTexture("Imagem_top_scores.png");
    Texture2D imgComoJogar = LoadTexture("Como_jogar.png");

    EstadoJogo* estado = criarEstadoInicial(LARGURA_TELA, ALTURA_TELA);
    if (estado == NULL) return 1; 

    SetTargetFPS(60); 
    
    while (!WindowShouldClose() && estado->deveSair == 0) 
    {
        atualizarJogo(estado);
        
        BeginDrawing();
            ClearBackground(BLACK); 
            desenharTudo(estado, logo, imgRecorde, imgTopScores, imgComoJogar);
        EndDrawing();
    }

    salvarTopScores(estado);
    
    UnloadTexture(logo); 
    UnloadTexture(imgRecorde);
    UnloadTexture(imgTopScores);
    UnloadTexture(imgComoJogar);
    
    liberarEstado(estado); 
    
    CloseAudioDevice();
    CloseWindow();       

    return 0;
}