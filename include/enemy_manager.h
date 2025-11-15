#pragma once
#include "enemy.h"
#include "raylib.h"

typedef struct EnemyManager {
  Enemy *enemies;
  int capacity;
  int activeCount;
} EnemyManager;

EnemyManager *InitEnemyManager(int capacity, GameWindow *gw, Texture2D *sprite);
Enemy *SpawnEnemy(EnemyManager *manager, GameWindow *gw);
void UpdateEnemies(EnemyManager *manager, GameWindow *gw, GameConfig *config);
void DrawEnemies(EnemyManager *manager, GameConfig *config);
void ResetEnemies(EnemyManager *manager);
void DestroyEnemyManager(EnemyManager *manager);
