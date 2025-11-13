#pragma once
#include "enemy.h"
#include "enemy_manager.h"
#include "game_window.h"
#include "raylib.h"
#include <stdbool.h>

typedef struct Projectile {
  Vector2 velocity;
  Vector2 pos;
  Texture2D *sprite;
  bool isActive;
} Projectile;

Projectile *InitProjectiles(Textures *textures);
void UpdateProjectiles(Projectile *projectiles, EnemyManager *em, GameWindow *,
                       float dt);
void ShootProjectile(Projectile *projectiles, Vector2 startPosition,
                     Vector2 targetPosition);
bool CheckIfProjectileIsOutOfBounds(Projectile projectile, GameWindow *gw);
Rectangle GetProjectileHitbox(Projectile projectile);
void DrawProjectiles(Projectile *projectiles);
void DestroyProjectiles(Projectile *projectiles);

// FOR DEBUGGING
int GetActiveProjectileCount(Projectile *projectiles);