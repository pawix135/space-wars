#include "enemy.h"
#include <stdlib.h>
#include "config.h"
#include "game.h"

Enemy* InitEnemies(Textures* textures, GameWindow* gw){
  Enemy* enemies = (Enemy*)malloc(sizeof(Enemy) * MAX_ENEMIES);
  for(int i = 0; i < MAX_ENEMIES; i++){
    enemies[i].health = 100;
    enemies[i].position = (Vector2){GetRandomValue(100, gw->screenW - textures->enemyTexture.width), -100};
    enemies[i].speed = GetRandomValue(1, 3);
    enemies[i].sprite = &textures->enemyTexture;
    enemies[i].isActive = true;
    enemies[i].hitbox = (Rectangle){enemies[i].position.x, enemies[i].position.y, enemies[i].sprite->width, enemies[i].sprite->height};
  }
  return enemies;
}

void DrawEnemies(Enemy* enemies){
  for(int i = 0; i < MAX_ENEMIES; i++){
    if(enemies[i].isActive){
      DrawTextureEx(*enemies[i].sprite, enemies[i].position, 0.0f, 0.2f, WHITE);
    }
  }
}

void RespawnEnemy(Enemy* enemeis, GameWindow* gw){
}

void UpdateEnemies(Enemy* enemies, GameWindow* gw){
  for(int i = 0; i < MAX_ENEMIES; i++){
    if(enemies[i].isActive){
      enemies[i].position.y += 5 * GetRandomValue(enemies[i].speed, 10);
      if(enemies[i].position.y > gw->screenH){
        enemies[i].position.y = -100;
        enemies[i].position.x = GetRandomValue(100, gw->screenW - enemies[i].sprite->width);
      }
    }
  }
}

void DestroyEnemy(Enemy* enemy){
  if(enemy != NULL){
    free(enemy);
    printf("Enemy memory freed\n");
  }
}