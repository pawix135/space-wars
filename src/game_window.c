#include "game_window.h"
#include "raylib.h"
#include <stdlib.h>
#include <stdio.h>

GameWindow* InitGameWindow(int monitor) {
  GameWindow* size = (GameWindow*)malloc(sizeof(GameWindow));
  size->w = GetMonitorWidth(monitor);
  size->h = GetMonitorHeight(monitor);
  return size;
}

void DestroyGameWindow(GameWindow* gw){
  if(gw != NULL){
    free(gw);
    printf("GameWindow memory freed\n");
  }
}

