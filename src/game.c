#include "game.h"
#include "background_stars.h"
#include "menu.h"
#include <stdio.h>
#include <stdlib.h>
#include "button.h"

Button backToMenuButton = {.baseColor = DARKGRAY,
                          .hoverColor = GRAY,
                          .rect = {0, 0, 200, 50},
                          .text = "Back to Menu"};

Button exitTheGameButton = {.baseColor = RED,
                       .hoverColor = DARKPURPLE,
                       .rect = {0, 0, 200, 50},
                       .text = "Exit"};

Game *CreateGame() {
  Game *g = (Game *)malloc(sizeof(Game));
  g->gw = InitGameWindow(GetCurrentMonitor());
  g->assets = InitializeAssets();
  SetWindowIcon(g->assets->iconImage);
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

  g->assets->sounds->backgroundSong.looping = true;
  SetAudioStreamVolume(g->assets->sounds->backgroundSong.stream, 0.1f);
  PlayMusicStream(g->assets->sounds->backgroundSong);

  while (g->config->isRunning) {
    g->config->deltaTime = GetFrameTime();

    if (WindowShouldClose()) g->config->isRunning = false;

    HandleResize(g);

    BeginDrawing();
    switch (g->config->currentScene) {
    case SCENE_MENU:
      DrawMenu(g);
      break;
    case SCENE_GAMEPLAY:
      UpdateMusicStream(g->assets->sounds->backgroundSong);
      GameLoop(g);
      DrawGame(g);
      break;
      case SCENE_HOWTOPLAY:
      DrawHowToPlay(g);
      break;
      case SCENE_PAUSE:
      DrawGame(g);
      DrawPauseMenu(g);
      break;
    case SCENE_WIN:
      DrawWinScene(g->config, g->stars, g->gw);
      break;
    default:
      DrawMenu(g);
      break;
    }
    EndDrawing();
  }
}

void DrawGame(Game *g) {

  ClearBackground(BLACK);
  DrawBackgroundStars(g->stars);
  DrawProjectiles(g->projectiles);
  DrawEnemies(g->em, g->config);
  DrawPlayer(g->player);
  DrawScore(g->config->score, g->gw);

  if (g->config->debugMode) {
    DrawDebug(g);
  }

}

void DrawPauseMenu(Game *g) {

  if (IsKeyPressed(KEY_ESCAPE)) {
    TogglePause(g->config);
  }

  backToMenuButton.rect.x = (g->gw->windowW - backToMenuButton.rect.width) / 2;
  backToMenuButton.rect.y = g->gw->windowH / 2 - 80;

  exitTheGameButton.rect.x = (g->gw->windowW - exitTheGameButton.rect.width) / 2;
  exitTheGameButton.rect.y = g->gw->windowH / 2;

  Vector2 mousePoint = GetMousePosition();

  DrawText("PAUSED", g->gw->windowW / 2 - MeasureText("PAUSED", 40) / 2, 50, 40, RED);
  DrawRectangle(g->gw->windowW / 2 - (g->gw->windowW / 4) / 2, g->gw->windowH / 2 - (g->gw->windowH / 4) / 2, 
                g->gw->windowW / 4, g->gw->windowH / 4, (Color){255, 255, 255, 155});

  if(CheckButtonState(&backToMenuButton, mousePoint)) {
    ChangeScene(g->config, SCENE_MENU);
    RestartGame(g);
  }

  if(CheckButtonState(&exitTheGameButton, mousePoint)) {
    ExitGame(g->config);
  }
}

void DrawWinScene(GameConfig *config, Star* stars, GameWindow *gw){

  if (IsKeyDown(KEY_ESCAPE)) {
    config->currentScene = SCENE_MENU;
  }

  ClearBackground(BLACK);
  DrawBackgroundStars(stars);
  DrawText("YOU WIN!", gw->windowW / 2 - MeasureText("YOU WIN!", 40) / 2, 50,
           40, GREEN);
  DrawText(TextFormat("Your final score: %d", config->score), gw->windowW / 2 - MeasureText(TextFormat("Your final score: %d", config->score), 30) / 2, 150,
           30, WHITE);
  DrawText("Press ESC to return to menu", gw->windowW / 2 - MeasureText("Press ESC to return to menu", 20) / 2, 250,
           20, WHITE);
}


void DrawScore(int score, GameWindow *gw) {
  const char *scoreText = TextFormat("Score: %d", score);
  DrawText(scoreText, gw->windowW / 2 - MeasureText(scoreText, 20) / 2, 30, 20,
           WHITE);
}


void DrawHowToPlay(Game *g){

  if(IsKeyPressed(KEY_ESCAPE)) {
    ChangeScene(g->config, SCENE_MENU);
  }

  backToMenuButton.rect.x = (g->gw->windowW - backToMenuButton.rect.width) / 2;
  backToMenuButton.rect.y = g->gw->windowH - 100;

  Vector2 mousePoint = GetMousePosition();

  ClearBackground(BLACK);
  DrawBackgroundStars(g->stars);

  const char *howToPlayLines[] = {
      "HOW TO PLAY",
      "",
      "Use the arrow left/right or 'A'/'D' to move your spaceship.",
      "Press LSHIFT to boost your spaceship.",
      "Point your mouse at the direction you want to shoot.",
      "Destroy enemies to earn as many points as possible.",
      "",
      "Good luck, pilot!",
  };

  int lineCount = sizeof(howToPlayLines) / sizeof(howToPlayLines[0]);
  for (int i = 0; i < lineCount; i++) {
    int fontSize = (i == 0) ? 40 : 20;
    int yOffset = 100 + i * (fontSize + 10);
    DrawText(howToPlayLines[i],
             g->gw->windowW / 2 - MeasureText(howToPlayLines[i], fontSize) / 2,
             yOffset, fontSize, WHITE);
  }

  if(CheckButtonState(&backToMenuButton, mousePoint)) {
    ChangeScene(g->config, SCENE_MENU);
  }

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

  UpdatePlayer(g->player, g->gw, g->projectiles, g->config);
  UpdateEnemies(g->em, g->gw, g->config);
  UpdateProjectiles(g->projectiles, g->em, g->gw, g->config->deltaTime);
  UpdateWaveManager(g->wm, g->em, g->gw, g->config);
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

void RestartGame(Game *g) {
  if (g == NULL) return;

  UpdatePlayerPosition(g->player, CalcInitPlayerPosition(g->gw, g->player));
  RestartWaveManager(g->wm);
  ResetConfig(g->config);
  ResetEnemies(g->em);

  TraceLog(LOG_DEBUG, "Game restarted.");
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