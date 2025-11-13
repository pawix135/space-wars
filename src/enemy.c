#include "enemy.h"
#include "config.h"
#include "game.h"
#include "raymath.h"
#include <stdlib.h>

Enemy *ZeroInitializeEnemies(int capacity) {
  Enemy *enemies = (Enemy *)calloc(capacity, sizeof(Enemy));
  return enemies;
}

Vector2 EnemyRespawnCoordinates(Enemy *enemy, GameWindow *gw) {
  int randomX = GetRandomValue(0 + enemy->sprite->width,
                               gw->windowW - enemy->sprite->width);
  float spawnY = 0 - enemy->sprite->height;

  return (Vector2){(float)randomX, spawnY};
}

void ResetEnemy(Enemy *e, GameWindow *gw) {
  if (e == NULL) return;
  e->health = 100;
  e->isActive = true;
  e->pos = EnemyRespawnCoordinates(e, gw);
  e->vel = (Vector2){0.0f, ENEMY_SPEED};
}

Rectangle GetEnemyHitbox(Enemy enemy) {
  return (Rectangle){enemy.pos.x, enemy.pos.y, enemy.sprite->width * 0.5f,
                     enemy.sprite->height * 0.5f};
}

bool IsEnemyOutOfBounds(Enemy *e, GameWindow *gw) {
  return (e->pos.x <= 0 || e->pos.x > gw->windowW + e->sprite->width / 2 ||
          e->pos.y > gw->windowH + e->sprite->height / 2);
}

void DestroyEnemies(Enemy *enemy) {
  if (enemy != NULL) {
    free(enemy);
    TraceLog(LOG_ALL, "Enemies destroyed.\n");
  }
}