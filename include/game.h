#pragma once
#include "player.h"
#include "projectile.h"
#include "game_window.h"
#include "sounds.h"
#include "projectile.h"
#include "textures.h"
#include "enemy.h"

typedef struct Game{
  Player* player;
  Projectile* projectiles;
  Enemy* enemies;
  GameWindow* gw;
  Sounds* sounds;
  Textures* textures;
  int score;
  bool paused;
  bool debugMode;
} Game;

Game* CreateGame();
void RunGame(Game* game);
void HandleResize(Game* game);
void DrawGame(Game* game);
void GameLoop(Game* game);
void DestroyGame(Game* game);
