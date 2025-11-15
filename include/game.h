#pragma once
#include "assets.h"
#include "background_stars.h"
#include "enemy_manager.h"
#include "game_config.h"
#include "game_window.h"
#include "player.h"
#include "projectile.h"
#include "scene_manager.h"
#include "wave_manager.h"

typedef struct Game {
  Player *player;
  Projectile *projectiles;
  EnemyManager *em;
  WaveManager *wm;
  GameWindow *gw;
  Assets *assets;
  Star *stars;
  GameConfig *config;
  float spawnTimer;
} Game;

Game *CreateGame();
void RunGame(Game *game);
void HandleResize(Game *game);
void DebugMode(Game *g);
void DrawWinScene(GameConfig *config, Star* stars, GameWindow *gw);
void DrawPauseMenu(Game *g);
void DrawHowToPlay(Game *g);
void RestartGame(Game *g);
void DrawDebug(Game *g);
void DrawGame(Game *game);
void DrawScore(int score, GameWindow *gw);
void GameLoop(Game *game);
void DestroyGame(Game *game);