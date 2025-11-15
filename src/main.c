#include "game.h"
#include "raylib.h"
#include <stdio.h>
#include <time.h>

int main(void) {

  SetConfigFlags(FLAG_WINDOW_UNDECORATED | FLAG_WINDOW_RESIZABLE);
  InitWindow(800, 600, "Space Wars");
  SetExitKey(KEY_NULL);

  InitAudioDevice();

  SetRandomSeed((unsigned int)time(NULL));

  SetTraceLogLevel(LOG_DEBUG);

  Game *game = CreateGame(GetCurrentMonitor());
  RunGame(game);
  DestroyGame(game);

  CloseAudioDevice();
  CloseWindow();
  return 0;
}