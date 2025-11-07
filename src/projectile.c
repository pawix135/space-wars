#include "projectile.h"
#include "config.h"
#include <stdlib.h>
#include <stdio.h>


Projectile* CreateProjectile(Vector2 pos, float speed){
  Projectile* projectile = (Projectile*)malloc(sizeof(Projectile));
  projectile->pos = pos;
  projectile->speed = speed;
  projectile->isActive = true;
  return projectile;
}

Projectile* InitProjectiles(){
  Projectile* pArray = (Projectile*)malloc(sizeof(Projectile) * MAX_PROJECTILES);
  for(int i = 0; i < MAX_PROJECTILES; i++){
    pArray[i].isActive = false;
    pArray[i].pos = (Vector2){0.0f, 0.0f};
    pArray[i].speed = 0.0f;
  }
  return pArray;
}

void UpdateProjectiles(Projectile* projectiles){
  for(int i = 0; i < MAX_PROJECTILES; i++){
    if(projectiles[i].isActive){
      projectiles[i].pos.y -= projectiles[i].speed;
      if(projectiles[i].pos.y < 0){
        projectiles[i].isActive = false;
      }
    }
  }
}

void DrawProjectiles(Projectile* projectiles){
  for(int i = 0; i < MAX_PROJECTILES; i++){
    if(projectiles[i].isActive){
      DrawRectangle((int)projectiles[i].pos.x, (int)projectiles[i].pos.y, 5, 15, YELLOW);
    }
  }
}

int GetActiveProjectileCount(Projectile* projectiles){
  int count = 0;
  for(int i = 0; i < MAX_PROJECTILES; i++){
    if(projectiles[i].isActive){
      count++;
    }
  }
  return count;
}

void DestroyProjectiles(Projectile* projectiles){
  if(projectiles != NULL){
    free(projectiles);
    printf("Projectiles memory freed\n");
  }
}