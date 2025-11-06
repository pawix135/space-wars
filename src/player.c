#include "player.h"
#include "assets.h"
#include "config.h"

Player* CreatePlayer(){
  Player* player = (Player*)malloc(sizeof(Player));
  player->sprite = LoadSprite(ship_A_png, ship_A_png_len);
  player->pos = (Vector2){400.0f, 300.0f};
  player->speed = 5.0f;
  player->isBoosted = false;
  player->lastFireTime = 0.0f;
  return player;
}

void UpdatePlayer(Player* player, Sound* shootSound){
  MovePlayer(player);
  PlayerShoot(player, shootSound);
}

void MovePlayer(Player* player){
  float speedMultiplier = player->isBoosted ? 2.0f : 1.0f;

  if(IsKeyPressed(KEY_LEFT_SHIFT)){
    player->isBoosted = true;
    printf("Boost pressed\n");
  }

  if(IsKeyReleased(KEY_LEFT_SHIFT)){
    player->isBoosted = false;
    printf("Boost released\n");
  }
  if(IsKeyDown(KEY_W) || IsKeyDown(KEY_UP)){
    player->pos.y -= player->speed * speedMultiplier;
  }
  if(IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN)){
    player->pos.y += player->speed * speedMultiplier;
  }
  if(IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)){
    player->pos.x -= player->speed * speedMultiplier;
  }
  if(IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)){
    player->pos.x += player->speed * speedMultiplier;
  }
}

void PlayerShoot(Player* player, Sound* shootSound){
  float dt = GetFrameTime(); 

  if (player->lastFireTime > 0){
    player->lastFireTime -= dt;
  }
  
  if (player->lastFireTime <= 0){
    // printf("Pew Pew!\n");
    PlaySound(*shootSound);
    player->lastFireTime = FIRE_RATE_SECONDS;
  }

}

void DrawPlayer(const Player* player){
  DrawTexture(player->sprite, (int)player->pos.x, (int)player->pos.y, WHITE);
}

void DestroyPlayer(Player* player){
  if(player != NULL){
    UnloadTexture(player->sprite);
    free(player);
    printf("Player memory freed\n");
  }
}