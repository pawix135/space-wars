#include "wave_manager.h"
#include <stdlib.h> 
#include <string.h>
#include "raylib.h"

static const WavePattern GAME_WAVES[] = {
    { .enemyCount = 10, .spawnInterval = 0.8f, .speedModifier = 1.0f, .enemyType = 0, .waitTime = 3.0f },
    { .enemyCount = 15, .spawnInterval = 0.5f, .speedModifier = 1.0f, .enemyType = 0, .waitTime = 5.0f },
    { .enemyCount = 12, .spawnInterval = 0.7f, .speedModifier = 1.4f, .enemyType = 1, .waitTime = 6.0f },
    { .enemyCount = 8, .spawnInterval = 1.2f, .speedModifier = 0.7f, .enemyType = 2, .waitTime = 8.0f },
    { .enemyCount = 20, .spawnInterval = 0.4f, .speedModifier = 1.2f, .enemyType = 0, .waitTime = 10.0f }
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
    wm->spawnTimer = 0.0f; 
    wm->spawnTimer = wm->waves[0].waitTime;

    TraceLog(LOG_INFO, "Wave Manager initialized with %d waves.", wm->totalWaves);
    return wm;
}

void UpdateWaveManager(WaveManager *wm, EnemyManager *em, GameWindow *gw, GameConfig *config) {
    if (wm->currentWaveIndex >= wm->totalWaves) {
        TraceLog(LOG_INFO, "All waves cleared! Game Complete.");
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
                e->vel.y *= currentWave->speedModifier;
                e->health = currentWave->enemyType == 2 ? 50 : 10;
                
                wm->enemiesRemainingToSpawn--;
                
                TraceLog(LOG_DEBUG, "Spawned 1 enemy. %d left to spawn.", wm->enemiesRemainingToSpawn);
                
                wm->spawnTimer = currentWave->spawnInterval;
            } else {
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
                
                TraceLog(LOG_INFO, "Next wave (%d) loading. Wait time: %.1f seconds.", 
                         wm->currentWaveIndex, nextWave->waitTime);
            }
        }
    }
}

void DestroyWaveManager(WaveManager *wm) {
  if (wm == NULL) return;
  free(wm);
  TraceLog(LOG_DEBUG, "Wave Manager destroyed.");
}