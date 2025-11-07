#pragma once
#include "raylib.h"

typedef struct Projectile{
  Vector2 pos;
  float speed;
  bool isActive;
} Projectile;

Projectile* CreateProjectile(Vector2 pos, float speed);
Projectile* InitProjectiles();
void UpdateProjectiles(Projectile *projectiles);
void DrawProjectiles(Projectile *projectiles);
void DestroyProjectiles(Projectile* projectiles);

//FOR DEBUGGING
int GetActiveProjectileCount(Projectile* projectiles);