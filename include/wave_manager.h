#pragma once
#include "config.h"
#include "enemy_manager.h"

typedef struct WavePattern {
  int enemyCount;
  float spawnInterval;
  float speedModifier;
  int enemyType;
  float waitTime;
} WavePattern;

typedef struct WaveManager {
  WavePattern *waves;
  int totalWaves;
  int currentWaveIndex;
  int enemiesRemainingToSpawn;
  float spawnTimer;
} WaveManager;

WaveManager *ZeroInitializeWaveManager();
void UpdateWaveManager(WaveManager *wm, EnemyManager *em, GameWindow *gw,
                       GameConfig *config);
void DestroyWaveManager(WaveManager *wm);