#include "game.h"
#include "raylib.h"
#include <stdio.h>
#include <time.h>

int main(void) {

  SetConfigFlags(FLAG_WINDOW_UNDECORATED | FLAG_WINDOW_RESIZABLE |
                 FLAG_VSYNC_HINT);

  InitWindow(800, 600, "Space War");
  SetWindowMinSize(800, 600);
  SetRandomSeed((unsigned int)time(NULL));

  SetTraceLogLevel(LOG_DEBUG);

  InitAudioDevice();
  SetExitKey(KEY_NULL);

  Game *game = CreateGame(GetCurrentMonitor());

  RunGame(game);

  DestroyGame(game);

  CloseAudioDevice();
  CloseWindow();

  return 0;
}