#include "wave_manager.h"
#include <stdlib.h> 
#include <string.h>
#include "raylib.h"
#include "raymath.h"

static const WavePattern GAME_WAVES[] = {
  { .enemyCount = 10, .spawnInterval = 0.8f, .enemyType = 0, .waitTime = 1.0f, .speed_modifier = 1.05f },
  { .enemyCount = 15, .spawnInterval = 0.5f, .enemyType = 0, .waitTime = 3.0f, .speed_modifier = 1.10f },
  { .enemyCount = 25, .spawnInterval = 0.5f, .enemyType = 0, .waitTime = 3.0f, .speed_modifier = 1.15f },
  { .enemyCount = 30, .spawnInterval = 0.5f, .enemyType = 0, .waitTime = 3.0f, .speed_modifier = 1.20f },
  { .enemyCount = 35, .spawnInterval = 0.5f, .enemyType = 0, .waitTime = 3.0f, .speed_modifier = 1.25f },
  { .enemyCount = 40, .spawnInterval = 0.5f, .enemyType = 0, .waitTime = 3.0f, .speed_modifier = 1.30f },
  { .enemyCount = 45, .spawnInterval = 0.5f, .enemyType = 0, .waitTime = 3.0f, .speed_modifier = 1.35f },
  { .enemyCount = 50, .spawnInterval = 0.5f, .enemyType = 0, .waitTime = 3.0f, .speed_modifier = 1.40f },
};

static const int TOTAL_GAME_WAVES = sizeof(GAME_WAVES) / sizeof(WavePattern);

WaveManager *ZeroInitializeWaveManager() {
  WaveManager *wm = (WaveManager *)malloc(sizeof(WaveManager));
  if (!wm) {
      TraceLog(LOG_ERROR, "Failed to allocate memory for WaveManager.");
      return NULL;
  }

  wm->waves = (WavePattern *)GAME_WAVES;
  wm->totalWaves = TOTAL_GAME_WAVES;
  wm->currentWaveIndex = 0;
  wm->enemiesRemainingToSpawn = wm->waves[0].enemyCount;
  wm->spawnTimer = wm->waves[0].waitTime;

  TraceLog(LOG_DEBUG, "Wave Manager initialized with %d waves.", wm->totalWaves);
  return wm;
}

void UpdateWaveManager(WaveManager *wm, EnemyManager *em, GameWindow *gw, GameConfig *config) {

  if (wm->currentWaveIndex >= wm->totalWaves) {
    config->currentScene = SCENE_WIN;
    RestartWaveManager(wm);
    TraceLog(LOG_DEBUG, "All waves cleared! Game Complete.");
    return; 
  }

  WavePattern *currentWave = &wm->waves[wm->currentWaveIndex];

  if (wm->spawnTimer > 0.0f) {
    wm->spawnTimer -= config->deltaTime;
    if (wm->spawnTimer <= 0.0f) {
        TraceLog(LOG_DEBUG, "Wave %d STARTING.", wm->currentWaveIndex);
    }
    return;
  }

  if (wm->enemiesRemainingToSpawn > 0) {
    wm->spawnTimer -= config->deltaTime;
    
    if (wm->spawnTimer <= 0.0f) {
      Enemy *e = SpawnEnemy(em, gw);
      
      if (e != NULL) {
        e->vel = Vector2Scale(e->vel, currentWave->speed_modifier);
        wm->enemiesRemainingToSpawn--;
        
        TraceLog(LOG_DEBUG, "Spawned 1 enemy. %d left to spawn.", wm->enemiesRemainingToSpawn);
        
        wm->spawnTimer = currentWave->spawnInterval;
      }else {
        wm->spawnTimer = 0.1f; 
      }
    }
  }else {
    if (em->activeCount == 0) {
      TraceLog(LOG_DEBUG, "Wave %d cleared. Transitioning to next wave...", wm->currentWaveIndex);
      
      wm->currentWaveIndex++;

      if (wm->currentWaveIndex < wm->totalWaves) {
        WavePattern *nextWave = &wm->waves[wm->currentWaveIndex];
        
        wm->enemiesRemainingToSpawn = nextWave->enemyCount;
        wm->spawnTimer = nextWave->waitTime; 
        
        TraceLog(LOG_DEBUG, "Next wave (%d) loading. Wait time: %.1f seconds.", wm->currentWaveIndex, nextWave->waitTime);
      }
    }
  }
}

void RestartWaveManager(WaveManager *wm) {
  if (wm == NULL) return;

  wm->currentWaveIndex = 0;
  wm->enemiesRemainingToSpawn = wm->waves[0].enemyCount;
  wm->spawnTimer = wm->waves[0].waitTime;
  
  TraceLog(LOG_DEBUG, "Wave Manager restarted.");
}

void DestroyWaveManager(WaveManager *wm) {
  if (wm == NULL) return;
  free(wm);
  TraceLog(LOG_DEBUG, "Wave Manager destroyed.");
}