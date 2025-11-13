#include "projectile.h"
#include "config.h"
#include "raymath.h"
#include <stdlib.h>

Projectile *InitProjectiles(Textures *textures) {
  Projectile *pArray =
      (Projectile *)malloc(sizeof(Projectile) * MAX_PROJECTILES);
  for (int i = 0; i < MAX_PROJECTILES; i++) {
    pArray[i].isActive = false;
    pArray[i].pos = (Vector2){0.0f, 0.0f};
    pArray[i].velocity = (Vector2){0.0f, 0.0f};
    pArray[i].sprite = &textures->missileTexture;
  }
  return pArray;
}

void ShootProjectile(Projectile *projectiles, Vector2 startPosition,
                     Vector2 targetPosition) {
  for (int i = 0; i < MAX_PROJECTILES; i++) {

    if (!projectiles[i].isActive) {

      Vector2 direction = Vector2Subtract(targetPosition, startPosition);

      Vector2 unitDirection = Vector2Normalize(direction);

      Vector2 velocity = Vector2Scale(unitDirection, PROJECTILE_SPEED);

      projectiles[i].pos = startPosition;
      projectiles[i].velocity = velocity;
      projectiles[i].isActive = true;

      break;
    }
  }
}

void UpdateProjectiles(Projectile *projectiles, EnemyManager *em,
                       GameWindow *gm, float dt) {
  for (int i = 0; i < MAX_PROJECTILES; i++) {
    if (projectiles[i].isActive) {

      Vector2 movement =
          Vector2Scale(projectiles[i].velocity, PROJECTILE_SPEED * dt);
      projectiles[i].pos = Vector2Add(projectiles[i].pos, movement);

      if (CheckIfProjectileIsOutOfBounds(projectiles[i], gm)) {
        projectiles[i].isActive = false;
        continue;
      }

      if (projectiles[i].pos.y < 0) {
        projectiles[i].isActive = false;
      }

      for (int j = 0; j < em->capacity; j++) {
        Enemy *e = &em->enemies[j];
        if (e->isActive) {
          if (CheckCollisionRecs(GetProjectileHitbox(projectiles[i]),
                                 GetEnemyHitbox(*e))) {
            e->health = Clamp(e->health - PROJECTILE_DAMAGE, 0.0f, 100.0f);
            projectiles[i].isActive = false;
          }
        }
      }
    }
  }
}

bool CheckIfProjectileIsOutOfBounds(Projectile projectile, GameWindow *gw) {
  return (projectile.pos.x < 0 || projectile.pos.x > gw->windowW ||
          projectile.pos.y < 0 || projectile.pos.y > gw->windowH);
}

Rectangle GetProjectileHitbox(Projectile projectile) {
  return (Rectangle){projectile.pos.x, projectile.pos.y, 5, 15};
}

void DrawProjectiles(Projectile *projectiles) {
  for (int i = 0; i < MAX_PROJECTILES; i++) {
    if (projectiles[i].isActive) {
      float ang_deg =
          (atan2f(projectiles[i].velocity.y, projectiles[i].velocity.x) *
           RAD2DEG) +
          90.0f;
      DrawTextureEx(*projectiles[i].sprite, projectiles[i].pos, ang_deg, 1.0f,
                    WHITE);
    }
  }
}

int GetActiveProjectileCount(Projectile *projectiles) {
  int count = 0;
  for (int i = 0; i < MAX_PROJECTILES; i++) {
    if (projectiles[i].isActive) {
      count++;
    }
  }
  return count;
}

void CalculateProjectileHitbox(Projectile *projectile) {}

void DestroyProjectiles(Projectile *projectiles) {
  if (projectiles != NULL) {
    free(projectiles);
    TraceLog(LOG_DEBUG, "Projectiles destroyed.");
  }
}