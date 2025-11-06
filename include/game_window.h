#pragma once

typedef struct GameWindow {
  int w;
  int h;
} GameWindow;

GameWindow* InitGameWindow(int monitor);
void DestroyGameWindow(GameWindow* gw);


