#include "raylib.h"
#include "game.h"
#include <stdlib.h> 
#include <time.h>

int main(void)
{
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);

    InitWindow(LARGURA_TELA, ALTURA_TELA, "Tide Hit!");
    InitAudioDevice();
    srand(time(NULL));

    RenderTexture2D target = LoadRenderTexture(LARGURA_TELA, ALTURA_TELA);
    SetTextureFilter(target.texture, TEXTURE_FILTER_POINT);

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
        
        BeginTextureMode(target);
            ClearBackground(BLACK); 
            desenharTudo(estado, logo, imgRecorde, imgTopScores, imgComoJogar);
        EndTextureMode();

        BeginDrawing();
            ClearBackground(BLACK);
            
            Rectangle sourceRec = { 0.0f, 0.0f, (float)target.texture.width, (float)-target.texture.height };
            Rectangle destRec = { 0.0f, 0.0f, (float)GetScreenWidth(), (float)GetScreenHeight() };
            Vector2 origin = { 0.0f, 0.0f };
            
            DrawTexturePro(target.texture, sourceRec, destRec, origin, 0.0f, WHITE);
        EndDrawing();
    }

    salvarTopScores(estado);
    
    UnloadRenderTexture(target);
    UnloadTexture(logo); 
    UnloadTexture(imgRecorde);
    UnloadTexture(imgTopScores);
    UnloadTexture(imgComoJogar);
    
    liberarEstado(estado); 
    
    CloseAudioDevice();
    CloseWindow();       

    return 0;
}