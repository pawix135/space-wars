#pragma once
#include "player.h"
#include "projectile.h"
#include "game_window.h"
#include "sounds.h"

typedef struct Game{
  Player* player;
  Projectile* projectiles;
  GameWindow* gw;
  Sounds* sounds;
  bool paused;
} Game;

Game* CreateGame();
void RunGame(Game* game);
void HandleResize(Game* game);
void DrawGame(Game* game);
void GameLoop(Game* game);
void DestroyGame(Game* game);
