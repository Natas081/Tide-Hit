#include "raylib.h"
#include "game.h"
#include <stdlib.h> 
#include <time.h>

int main(void)
{
    InitWindow(LARGURA_TELA, ALTURA_TELA, "Tide Hit!");
    InitAudioDevice();
    srand(time(NULL));

    Texture2D logo = LoadTexture("Imagem_menu.png"); 

    EstadoJogo* estado = criarEstadoInicial(LARGURA_TELA, ALTURA_TELA);
    if (estado == NULL) return 1; 

    SetTargetFPS(60); 
    
    while (!WindowShouldClose() && estado->deveSair == 0) 
    {
        atualizarJogo(estado);
        
        BeginDrawing();
            ClearBackground(BLACK); 
            desenharTudo(estado, logo);
        EndDrawing();
    }

    salvarTopScores(estado);
    UnloadTexture(logo); 
    liberarEstado(estado); 
    
    CloseAudioDevice();
    CloseWindow();       

    return 0;
}