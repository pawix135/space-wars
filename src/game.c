#include "game.h"
#include <stdlib.h>

Game* CreateGame(){
  Game* g = (Game*)malloc(sizeof(Game));
  g->gw = InitGameWindow(GetCurrentMonitor());
  g->player = CreatePlayer();
  UpdatePlayerPosition(g->player, CalcInitPlayerPosition(g->gw, g->player));
  g->projectiles = InitProjectiles(g->projectiles);
  g->sounds = InitializeSounds();
  g->paused = false;
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

  DrawPlayer(g->player);

  if(g->paused == false){
    DrawText("Game Paused", 200, 20, 40, RED);
  }
  
  EndDrawing();
}

void GameLoop(Game* g){

  if(IsKeyPressed(KEY_P)){
    g->paused = !g->paused;
  }
  
  // Stop all the calculations if the game is paused
  if(g->paused){
    return;
  }

  UpdatePlayer(g->player, g->gw);

}

void HandleResize(Game* g){
  if (IsWindowResized()){
    UpdateGameWindowSize(g->gw);
    UpdatePlayerPosition(g->player, CalcInitPlayerPosition(g->gw, g->player));
  }
}

void DestroyGame(Game* g){
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

  if(g != NULL){
    free(g);
    printf("Game memory freed\n");
  }

}