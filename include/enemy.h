#pragma once
#include "raylib.h"
#include <stdbool.h>
#include "textures.h"
#include "game_window.h"

typedef struct Enemy
{
  int health;
  Texture2D* sprite;
  Vector2 position;
  float speed;
  Rectangle hitbox;
  bool isActive;
} Enemy;

Enemy* InitEnemies(Textures* textures, GameWindow* gw);
void DrawEnemies(Enemy *enemies);
void RespawnEnemy(Enemy* enemeis, GameWindow* gw);
void UpdateEnemies(Enemy* enemies, GameWindow* gw);
void DestroyEnemy(Enemy *enemy);