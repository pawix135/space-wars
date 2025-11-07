#include "game.h"
#include <stdlib.h>
#include "background_stars.h"

Game* CreateGame(){
  Game* g = (Game*)malloc(sizeof(Game));
  g->gw = InitGameWindow(GetCurrentMonitor());
  g->textures = LoadTextures();
  g->player = CreatePlayer(g->textures);
  UpdatePlayerPosition(g->player, CalcInitPlayerPosition(g->gw, g->player));
  g->projectiles = InitProjectiles(g->projectiles);
  g->sounds = InitializeSounds();
  g->paused = false;
  g->enemies = InitEnemies(g->textures, g->gw);
  g->debugMode = false;
  g->score = 0;
  return g;
}

void RunGame(Game* g){
  GameLoop(g);
  DrawGame(g);
} 

void DrawGame(Game* g){

  HandleResize(g);
  
  BeginDrawing();
  ClearBackground(BLACK);
  DrawBackgroundStars(g->gw);

  DrawPlayer(g->player, g->gw);
  DrawProjectiles(g->projectiles);
  // DrawEnemies(g->enemies);
  
  if(g->debugMode){
    DrawText("DEBUG MODE", 10, 10, 20, GREEN);
    DrawFPS(g->gw->windowW - 80, 10);
    char buffer[50];
    int activeCount = GetActiveProjectileCount(g->projectiles);
    sprintf(buffer, "Active Projectiles: %d", activeCount);
    DrawText(buffer, 10, 40, 20, GREEN);
  }

  if(g->paused == true){
    DrawText("Game Paused", g->gw->windowW/2-MeasureText("Game Paused", 40), 20, 40, RED);
  }

  EndDrawing();
}

void GameLoop(Game* g){

  if(IsKeyPressed(KEY_F3)){
    g->debugMode = !g->debugMode;
  }

  if(IsKeyPressed(KEY_P)){
    g->paused = !g->paused;
  }
  
  // Stop all the calculations if the game is paused
  if(g->paused){
    return;
  }

  UpdatePlayer(g->player, g->gw, g->projectiles);
  UpdateProjectiles(g->projectiles);
  UpdateEnemies(g->enemies, g->gw);

  UpdateBackgroundStars(g->gw);
}

void HandleResize(Game* g){
  if (IsWindowResized()){
    UpdateGameWindowSize(g->gw);
    UpdatePlayerPosition(g->player, CalcInitPlayerPosition(g->gw, g->player));
  }
}

void DestroyGame(Game* g){

  if(g == NULL){
    return;
  }

  if(g->player != NULL){
    DestroyPlayer(g->player);
    g->player = NULL;
  }
  
  if(g->projectiles != NULL){
    DestroyProjectiles(g->projectiles);
    g->projectiles = NULL;
  }

  if(g->gw != NULL){
    DestroyGameWindow(g->gw);
    g->gw = NULL;
  }

  if(g->sounds != NULL){
    DestroySounds(g->sounds);
    g->sounds = NULL;
  }

  if(g->textures != NULL){
    DestroyTextures(g->textures);
    g->textures = NULL;
  }

  if(g->enemies != NULL){
    DestroyEnemy(g->enemies);
    g->enemies = NULL;
  }

  DestronyStars();
  free(g);
  printf("Game memory freed\n");

}