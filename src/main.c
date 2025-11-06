#include "raylib.h"
#include <stdio.h>
#include "game.h"

int main(void){
  
  SetConfigFlags(FLAG_WINDOW_UNDECORATED | FLAG_WINDOW_RESIZABLE);

  InitWindow(800, 600, "Space War");
  InitAudioDevice();
  
  Game* game = CreateGame(GetCurrentMonitor());

  // TODO: Move it to the game_window module
  int windowWidth = game->gw->w * .75;
  int windowHeight = game->gw->h * .75;
  int posX = (game->gw->w - windowWidth) / 2;
  int posY = (game->gw->h - windowHeight) / 2;
  SetWindowSize(windowWidth, windowHeight);
  SetWindowPosition(posX, posY);
  ClearWindowState(FLAG_WINDOW_UNDECORATED);
  SetTargetFPS(144);
  
  while (!WindowShouldClose()){
    RunGame(game);
  }

  DestroyGame(game);
  CloseWindow();
  
  return 0;
}