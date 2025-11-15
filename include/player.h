#pragma once
#include "config.h"
#include "game_window.h"
#include "projectile.h"
#include "raylib.h"
#include "sprite_loader.h"
#include "game_config.h"
#include "textures.h"
#include <stdbool.h>
#include <stdlib.h>

typedef struct Player {
  Vector2 pos;
  Vector2 vel;
  bool isBoosted;
  Texture2D *sprite;
  float lastFireTime;
} Player;

Player *CreatePlayer(Textures *textures);
void UpdatePlayer(Player *player, GameWindow *gw, Projectile *projectiles, GameConfig *config);
void MovePlayer(Player *player, GameWindow *gw, GameConfig *config);
void DrawPlayer(const Player *player);
void UpdatePlayerPosition(Player *player, Vector2 newPos);
Vector2 CalcInitPlayerPosition(GameWindow *gw, Player *player);
void PlayerShoot(Player *player, Projectile *projectiles);
void DestroyPlayer(Player *player);
