#pragma once
#include "scene_manager.h"
#include <stdbool.h>

typedef struct GameConfig {
  // Window/Scene settings
  GameScene currentScene;
  float deltaTime;
  bool isRunning;

  // Player/Gameplay Settings
  bool autoShootEnabled;
  bool paused;
  int score;

  // Debugging/System Settings
  bool debugMode;
} GameConfig;

GameConfig *CreateGameConfig();
void TogglePause(GameConfig *config);
void ToggleDebugMode(GameConfig *config);
void ExitGame(GameConfig *config);
void ChangeScene(GameConfig *config, GameScene newScene);
void DestroyGameConfig(GameConfig *config);
