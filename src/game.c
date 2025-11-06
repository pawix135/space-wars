#include "game.h"
#include <stdlib.h>

Game* CreateGame(int monitorId){
  Game* game = (Game*)malloc(sizeof(Game));
  game->player = CreatePlayer();
  game->projectiles = InitProjectiles(game->projectiles);
  game->gw = InitGameWindow(monitorId);
  game->sounds = InitializeSounds();
  game->paused = false;
  return game;
}

void RunGame(Game* g){
  GameLoop(g);
  DrawGame(g);
} 

void DrawGame(Game* g){
  BeginDrawing();
  ClearBackground(BLACK);
  if(g->paused == false){
    DrawPlayer(g->player);
  }else {
    DrawText("Game Paused", 200, 20, 40, RED);
  }
  EndDrawing();
}

void GameLoop(Game* game){
  if(IsKeyPressed(KEY_P)){
    game->paused = !game->paused;
  }
}

void DestroyGame(Game* game){
  if(game->player != NULL){
    DestroyPlayer(game->player);
    game->player = NULL;
  }
  
  if(game->projectiles != NULL){
    DestroyProjectiles(game->projectiles);
    game->projectiles = NULL;
  }

  if(game->gw != NULL){
    DestroyGameWindow(game->gw);
    game->gw = NULL;
  }

  if(game->sounds != NULL){
    DestroySounds(game->sounds);
    game->sounds = NULL;
  }

  if(game != NULL){
    free(game);
    printf("Game memory freed\n");
  }

}