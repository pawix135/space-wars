#include "projectile.h"
#include "config.h"

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

void UpdateProjectile(Projectile* projectile){
  if(projectile->isActive){
    projectile->pos.y -= projectile->speed;
    if(projectile->pos.y < 0){
      printf("Projectile deactivated\n");
      projectile->isActive = false;
    }
  }
}

void DrawProjectile(const Projectile* projectile){
  if(projectile->isActive){
    DrawRectangle((int)projectile->pos.x, (int)projectile->pos.y, 5, 10, YELLOW);
  }
}

void DestroyProjectiles(Projectile* projectiles){
  if(projectiles != NULL){
    free(projectiles);
    printf("Projectiles memory freed\n");
  }
}