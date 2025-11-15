#include "player.h"
#include "raymath.h"

Player *CreatePlayer(Textures *textures) {
  Player *player = (Player *)malloc(sizeof(Player));
  player->sprite = &textures->playerTexture;
  player->pos = (Vector2){0.0f, 0.0f};
  player->vel = (Vector2){10.0f, 0.0f};
  player->isBoosted = false;
  player->lastFireTime = 0.0f;
  return player;
}

void UpdatePlayer(Player *player, GameWindow *gw, Projectile *projectiles, GameConfig *config) {
  MovePlayer(player, gw, config);
  PlayerShoot(player, projectiles);
}

void MovePlayer(Player *player, GameWindow *gw, GameConfig *config) {

  Vector2 movement = Vector2Scale(player->vel, 50.0f * config->deltaTime);
  if(player->isBoosted){
    movement = Vector2Scale(player->vel, 100.0f * config->deltaTime);
  }

  if (IsKeyPressed(KEY_LEFT_SHIFT)) {
    player->isBoosted = true;
    TraceLog(LOG_DEBUG, "Player boost activated.\n");
  } else if (IsKeyReleased(KEY_LEFT_SHIFT)) {
    player->isBoosted = false;
    TraceLog(LOG_DEBUG, "Player Boost released.\n");
  }

  if ((IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) && player->pos.x > 0) {
    player->pos = Vector2Subtract(player->pos, movement);
  }
  if ((IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) && player->pos.x < (gw->windowW - player->sprite->width)) {
    player->pos = Vector2Add(player->pos, movement);
  }
}

void PlayerShoot(Player *player, Projectile *projectiles) {

  float dt = GetFrameTime();
  Vector2 mp = GetMousePosition();

  if (player->lastFireTime > 0) {
    player->lastFireTime -= dt;
  }

  if (player->lastFireTime <= 0) {
    Vector2 startPosition =
        (Vector2){player->pos.x + player->sprite->width / 2 -
                      projectiles[0].sprite->width / 2,
                  player->pos.y + projectiles[0].sprite->height / 2};
    ShootProjectile(projectiles, startPosition, mp);
    player->lastFireTime = FIRE_RATE_SECONDS;
  }
}

Vector2 CalcInitPlayerPosition(GameWindow *gw, Player *player) {
  Vector2 pos;
  pos.x = (gw->windowW / 2) - (player->sprite->width / 2);
  pos.y = gw->windowH - player->sprite->height - 100;
  return pos;
}

void UpdatePlayerPosition(Player *player, Vector2 newPos) {
  player->pos = newPos;
}

void DrawPlayer(const Player *player) {
  DrawTexture(*player->sprite, (int)player->pos.x, (int)player->pos.y, WHITE);
}

void DestroyPlayer(Player *player) {
  if (player != NULL) {
    free(player);
    TraceLog(LOG_DEBUG, "Player destroyed.");
  }
}