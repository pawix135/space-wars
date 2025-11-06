#include "player.h"
#include "assets.h"
#include "config.h"

Player* CreatePlayer(){
  Player* player = (Player*)malloc(sizeof(Player));
  player->sprite = LoadSprite(ship_A_png, ship_A_png_len);
  player->pos = (Vector2){0.0f, 0.0f};
  player->speed = 5.0f;
  player->health = 100;
  player->isBoosted = false;
  player->lastFireTime = 0.0f;
  return player;
}

void UpdatePlayer(Player* player, GameWindow* gw){
  MovePlayer(player, gw);
  // PlayerShoot(g->player, &g->sounds->shootSound);
}

void MovePlayer(Player* player, GameWindow* gw){
  float speedMultiplier = player->isBoosted ? 2.0f : 1.0f;

  if(IsKeyPressed(KEY_LEFT_SHIFT)){
    player->isBoosted = true;
    printf("Boost pressed\n");
  }else if(IsKeyReleased(KEY_LEFT_SHIFT)){
    player->isBoosted = false;
    printf("Boost released\n");
  }

  if((IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) && player->pos.x > 0){
    player->pos.x -= player->speed * speedMultiplier;
  }
  if((IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT) ) && player->pos.x < (gw->windowW - player->sprite.width)){
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
    // PlaySound(*shootSound);
    player->lastFireTime = FIRE_RATE_SECONDS;
  }

}

Vector2 CalcInitPlayerPosition(GameWindow* gw, Player* player){
  Vector2 pos;
  pos.x = (gw->windowW / 2) - (player->sprite.width / 2);
  pos.y = gw->windowH - player->sprite.height - 100;
  return pos;
}

void PlayerTakeDamage(Player* player, int damage){
  player->health -= damage;
  if(player->health < 0){
    player->health = 0;
  }
}

void UpdatePlayerPosition(Player* player, Vector2 newPos){
  player->pos = newPos;
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