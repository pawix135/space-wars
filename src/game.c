#include "game.h"
#include "background_stars.h"
#include "menu.h"
#include <stdio.h>
#include <stdlib.h>

Game *CreateGame() {
  Game *g = (Game *)malloc(sizeof(Game));
  g->gw = InitGameWindow(GetCurrentMonitor());
  g->assets = InitializeAssets();
  g->player = CreatePlayer(g->assets->textures);
  UpdatePlayerPosition(g->player, CalcInitPlayerPosition(g->gw, g->player));
  g->projectiles = InitProjectiles(g->assets->textures);
  g->spawnTimer = 0.0f;
  g->em =
      InitEnemyManager(MAX_ENEMIES, g->gw, &g->assets->textures->enemyTexture);
  g->wm = ZeroInitializeWaveManager();
  g->stars = InitBackgroundStars(g->gw);
  g->config = CreateGameConfig();
  return g;
}

void RunGame(Game *g) {

  while (g->config->isRunning) {
    if (WindowShouldClose()) g->config->isRunning = false;

    HandleResize(g);

    switch (g->config->currentScene) {
    case SCENE_MENU:
      DrawMenu(g->config, g->stars, g->gw);
      break;
    case SCENE_GAMEPLAY:
      GameLoop(g);
      DrawGame(g);
      break;
    default:
      DrawMenu(g->config, g->stars, g->gw);
      break;
    }
  }
}

void DrawGame(Game *g) {
  BeginDrawing();

  ClearBackground(BLACK);
  DrawBackgroundStars(g->stars);

  DrawPlayer(g->player, g->gw);
  DrawProjectiles(g->projectiles);
  DrawEnemies(g->em, g->config);
  DrawScore(g->config->score, g->gw);

  if (g->config->paused == true) {
    DrawText("PAUSED", g->gw->windowW / 2 - MeasureText("PAUSED", 40) / 2, 50,
             40, RED);
    DrawRectangle(g->gw->windowW / 2 - (g->gw->windowW / 3) / 2,
                  g->gw->windowH / 2 - (g->gw->windowH / 3) / 2,
                  g->gw->windowW / 3, g->gw->windowH / 3,
                  (Color){255, 255, 255, 155});
  }

  if (g->config->debugMode) {
    DrawDebug(g);
  }

  EndDrawing();
}

void DrawScore(int score, GameWindow *gw) {
  const char *scoreText = TextFormat("Score: %d", score);
  DrawText(scoreText, gw->windowW / 2 - MeasureText(scoreText, 20) / 2, 30, 20,
           WHITE);
}

void GameLoop(Game *g) {

  DebugMode(g);

  if (IsKeyPressed(KEY_ESCAPE)) {
    TogglePause(g->config);
  }

  // Stop all the calculations if the game is paused
  if (g->config->paused) {
    return;
  }

  g->config->deltaTime = GetFrameTime();

  UpdatePlayer(g->player, g->gw, g->projectiles);
  UpdateProjectiles(g->projectiles, g->em, g->gw, g->config->deltaTime);
  UpdateWaveManager(g->wm, g->em, g->gw, g->config);
  // UpdateEnemies(g->em, g->gw, g->config);
  UpdateBackgroundStars(g->stars, g->gw, g->config->deltaTime);
}

void DebugMode(Game *g) {

  if (IsKeyPressed(KEY_F3)) ToggleDebugMode(g->config);

  if (!g->config->debugMode) return;

  if (IsKeyDown(KEY_LEFT_CONTROL) && IsKeyPressed(KEY_H)) {
    if (SpawnEnemy(g->em, g->gw) == NULL) {
      TraceLog(LOG_DEBUG, "Failed to spawn enemy: EnemyManager is full.");
    }
  }
}

void DrawDebug(Game *g) {
  DrawText("DEBUG MODE", 10, 10, 20, GREEN);
  DrawFPS(g->gw->windowW - 80, 10);
  char buffer[50];
  sprintf(buffer, "Active Projectiles: %d",
          GetActiveProjectileCount(g->projectiles));
  DrawText(buffer, 10, 40, 20, GREEN);
  sprintf(buffer, "Active Enemies: %d", g->em->activeCount);
  DrawText(buffer, 10, 70, 20, GREEN);
  sprintf(buffer, "Player Position: (%.2f, %.2f)", g->player->pos.x,
          g->player->pos.y);
  DrawText(buffer, 10, 100, 20, GREEN);
}

void HandleResize(Game *g) {
  if (IsWindowResized()) {
    UpdateGameWindowSize(g->gw);
    UpdatePlayerPosition(g->player, CalcInitPlayerPosition(g->gw, g->player));
    UpdateBackgroundStarsOnResize(g->stars, g->gw);
  }
}

void DestroyGame(Game *g) {

  if (g == NULL) {
    return;
  }

  if (g->player != NULL) {
    DestroyPlayer(g->player);
    g->player = NULL;
  }

  if (g->projectiles != NULL) {
    DestroyProjectiles(g->projectiles);
    g->projectiles = NULL;
  }

  if (g->em != NULL) {
    DestroyEnemyManager(g->em);
    g->em = NULL;
  }

  if (g->stars != NULL) {
    DestroyBackgroundStars(g->stars);
    g->stars = NULL;
  }

  if (g->gw != NULL) {
    DestroyGameWindow(g->gw);
    g->gw = NULL;
  }

  if (g->config != NULL) {
    DestroyGameConfig(g->config);
    g->config = NULL;
  }

  if (g->assets != NULL) {
    DestroyAssets(g->assets);
    g->assets = NULL;
  }

  if(g->wm != NULL) {
    DestroyWaveManager(g->wm);
    g->wm = NULL;
  }

  free(g);
  TraceLog(LOG_DEBUG, "Game destroyed.");
}