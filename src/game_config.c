#include "game_config.h"
#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>

GameConfig *CreateGameConfig() {
  GameConfig *config = (GameConfig *)malloc(sizeof(GameConfig));
  config->currentScene = SCENE_MENU;
  config->deltaTime = 0.0f;
  config->isRunning = true;
  config->autoShootEnabled = false;
  config->paused = false;
  config->debugMode = false;
  config->score = 0;
  return config;
}

void TogglePause(GameConfig *config) { config->paused = !config->paused; }

void ToggleDebugMode(GameConfig *config) {
  config->debugMode = !config->debugMode;
}

void ChangeScene(GameConfig *config, GameScene newScene) {
  config->currentScene = newScene;
}

void ExitGame(GameConfig *config) { config->isRunning = false; }

void DestroyGameConfig(GameConfig *config) {
  if (config != NULL) {
    free(config);
  }
  TraceLog(LOG_DEBUG, "GameConfig destroyed.");
}