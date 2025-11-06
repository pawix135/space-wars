#pragma once
#include "raylib.h"

typedef struct GameWindow {
  int windowW;
  int windowH;
  int screenW;
  int screenH;
} GameWindow;

GameWindow* InitGameWindow(int monitorId);
void UpdateGameWindowSize(GameWindow* gw);
void DestroyGameWindow(GameWindow* gw);


