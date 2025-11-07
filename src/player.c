#include "player.h"
Player* CreatePlayer(Textures* textures){
  Player* player = (Player*)malloc(sizeof(Player));
  player->sprite = &textures->playerTexture;
  player->pos = (Vector2){0.0f, 0.0f};
  player->speed = 5.0f;
  player->health = 100;
  player->isBoosted = false;
  player->lastFireTime = 0.0f;
  return player;
}

void UpdatePlayer(Player* player, GameWindow* gw, Projectile* projectiles){
  MovePlayer(player, gw);
  PlayerShoot(player, projectiles);
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
  if((IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT) ) && player->pos.x < (gw->windowW - player->sprite->width)){
    player->pos.x += player->speed * speedMultiplier;
  }

}

void PlayerShoot(Player *player, Projectile* projectiles){

  float dt = GetFrameTime(); 

  if (player->lastFireTime > 0){
    player->lastFireTime -= dt;
  }
  
  if (player->lastFireTime <= 0){
    for(int i = 0; i < MAX_PROJECTILES; i++){
      if(projectiles[i].isActive == false){
        projectiles[i].pos = (Vector2){player->pos.x + (player->sprite->width / 2) - 5, player->pos.y};
        projectiles[i].isActive = true;
        projectiles[i].speed = 10.0f;
        break;
      }
    }
    player->lastFireTime = FIRE_RATE_SECONDS;
  }

}

Vector2 CalcInitPlayerPosition(GameWindow* gw, Player* player){
  Vector2 pos;
  pos.x = (gw->windowW / 2) - (player->sprite->width / 2);
  pos.y = gw->windowH - player->sprite->height - 100;
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

void DrawPlayerHealth(const Player *player, GameWindow* gw){
  int barWidth = gw->windowW * 0.9f;
  int barPosX = gw->windowW /2 - barWidth /2;
  int barPosY = gw->windowH - 60;
  char buffer[8];
  sprintf(buffer, "%d", player->health);
  DrawRectangle(barPosX, barPosY, barWidth, 40, RED);
  DrawText(buffer, gw->windowW/2 - MeasureText(buffer, 20), barPosY + 10, 20, WHITE);
}


void DrawPlayer(const Player* player, GameWindow* gw){
  DrawTexture(*player->sprite, (int)player->pos.x, (int)player->pos.y, WHITE);
  DrawPlayerHealth(player, gw);
}

void DestroyPlayer(Player* player){
  if(player != NULL){
    free(player);
    printf("Player memory freed\n");
  }
}