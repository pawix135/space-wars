#include "raylib.h"
#include <stdio.h>
#include "game.h"

int main(void){
  
  SetConfigFlags(FLAG_WINDOW_UNDECORATED | FLAG_WINDOW_RESIZABLE);

  InitWindow(800, 600, "Space War");
  InitAudioDevice();
  
  Game* game = CreateGame(GetCurrentMonitor());

  while (!WindowShouldClose()){
    RunGame(game);
  }

  DestroyGame(game);
  CloseWindow();
  
  return 0;
}