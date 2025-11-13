#pragma once
#include "game_config.h"
#include "game_window.h"
#include "raylib.h"
#include "textures.h"
#include <stdbool.h>

typedef struct Enemy {
  int health;
  Texture2D *sprite;
  Vector2 pos;
  Vector2 vel;
  bool isActive;
} Enemy;

Enemy *ZeroInitializeEnemies(int capacity);
bool IsEnemyOutOfBounds(Enemy *e, GameWindow *gw);
void ResetEnemy(Enemy *e, GameWindow *gw);
Rectangle GetEnemyHitbox(Enemy enemy);
Vector2 EnemyRespawnCoordinates(Enemy *enemy, GameWindow *gw);
void DestroyEnemies(Enemy *enemy);