#pragma once
#include "player.h"
#include "raylib.h"

typedef struct Projectile{
  Vector2 pos;
  float speed;
  bool isActive;
} Projectile;

Projectile* CreateProjectile(Vector2 pos, float speed);
Projectile* InitProjectiles();
void UpdateProjectile(Projectile *projectile);
void DrawProjectile(const Projectile *projectile);
void DestroyProjectiles(Projectile* projectiles);