#include "game_window.h"
#include <stdlib.h>

#define SCALE_FACTOR 0.75f

GameWindow *InitGameWindow(int monitorId) {
  GameWindow *size = (GameWindow *)malloc(sizeof(GameWindow));
  size->screenW = GetMonitorWidth(monitorId);
  size->screenH = GetMonitorHeight(monitorId);
  size->windowW = size->screenW * SCALE_FACTOR;
  size->windowH = size->screenH * SCALE_FACTOR;
  int posX = (size->screenW - size->windowW) / 2;
  int posY = (size->screenH - size->windowH) / 2;
  SetWindowSize(size->windowW, size->windowH);
  SetWindowPosition(posX, posY);
  ClearWindowState(FLAG_WINDOW_UNDECORATED);
  // SetTargetFPS(144);
  return size;
}

void UpdateGameWindowSize(GameWindow *gw) {
  if (gw != NULL) {
    gw->windowW = GetScreenWidth();
    gw->windowH = GetScreenHeight();
    TraceLog(LOG_DEBUG, "GameWindow size updated: width=%d, height=%d\n",
             gw->windowW, gw->windowH);
  }
}

void DestroyGameWindow(GameWindow *gw) {
  if (gw != NULL) {
    free(gw);
    TraceLog(LOG_DEBUG, "GameWindow destroyed.");
  }
}
