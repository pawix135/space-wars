#include "enemy_manager.h"
#include "config.h"
#include "game_config.h"
#include "game_window.h"
#include "raymath.h"
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

EnemyManager *InitEnemyManager(int capacity, GameWindow *gw,
                               Texture2D *sprite) {

  EnemyManager *manager = (EnemyManager *)calloc(1, sizeof(EnemyManager));

  if (manager == NULL) return NULL;

  manager->enemies = ZeroInitializeEnemies(capacity);

  if (manager->enemies == NULL) {
    free(manager);
    return NULL;
  }

  for (int i = 0; i < capacity; i++) {
    manager->enemies[i].health = 100;
    manager->enemies[i].sprite = sprite;
    manager->enemies[i].pos = EnemyRespawnCoordinates(&manager->enemies[i], gw);
    manager->enemies[i].vel = (Vector2){0.0f, ENEMY_SPEED};
    manager->enemies[i].isActive = false;
  }

  manager->capacity = capacity;
  manager->activeCount = 0;

  return manager;
}

Enemy *SpawnEnemy(EnemyManager *manager, GameWindow *gw) {
  if (manager == NULL || manager->enemies == NULL) return NULL;

  for (int i = 0; i < manager->capacity; i++) {
    if (!manager->enemies[i].isActive) {
      Enemy *e = &manager->enemies[i];
      ResetEnemy(e, gw);
      manager->activeCount++;
      return e;
    }
  }

  return NULL;
}

void UpdateEnemies(EnemyManager *manager, GameWindow *gw, GameConfig *config) {

  for (int i = 0; i < manager->capacity; i++) {

    Enemy *e = &manager->enemies[i];

    if (!e->isActive) continue;
    bool shouldDeactivate = false;

    Vector2 movement = Vector2Scale(e->vel, ENEMY_SPEED * config->deltaTime);
    e->pos = Vector2Add(e->pos, movement);

    if (e->health <= 0) {
      shouldDeactivate = true;
      config->score += 10;
    }

    if (IsEnemyOutOfBounds(e, gw)) {
      shouldDeactivate = true;
      TraceLog(LOG_DEBUG, "Enemy %d went out of bounds.", i);
    }

    if (shouldDeactivate) {
      manager->activeCount--;
      e->isActive = false;
      TraceLog(LOG_DEBUG, "Enemy %d deactivated.", i);
    }
  }
}

void DrawEnemies(EnemyManager *manager, GameConfig *config) {
  for (int i = 0; i < manager->capacity; i++) {

    if (!manager->enemies[i].isActive) continue;

    Enemy *enemy = &manager->enemies[i];

    DrawTextureEx(*enemy->sprite, enemy->pos, 0.0f, 0.5f, WHITE);
    DrawRectangle(enemy->pos.x,
                  enemy->pos.y + enemy->sprite->height * 0.5f + 1.0f,
                  enemy->sprite->width * 0.5f, 5, RED);
    DrawRectangle(
        enemy->pos.x, enemy->pos.y + enemy->sprite->height * 0.5f + 1.0f,
        (enemy->sprite->width * 0.5f) * ((float)enemy->health / 100.0f), 5,
        GREEN);
    if (config->debugMode) {
      DrawText(TextFormat("%d", i), enemy->pos.x, enemy->pos.y - 20, 10,
               YELLOW);
    }
  }
}

void ResetEnemyManager(EnemyManager *manager) {
  if (manager == NULL || manager->enemies == NULL) return;

  memset(manager->enemies, 0, manager->capacity * sizeof(Enemy));
  manager->activeCount = 0;
}

void DestroyEnemyManager(EnemyManager *manager) {
  if (manager == NULL) return;

  if (manager->enemies != NULL) {
    DestroyEnemies(manager->enemies);
    manager->enemies = NULL;
  }

  free(manager);
  TraceLog(LOG_DEBUG, "EnemyManager destroyed.");
}