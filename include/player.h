#pragma once
#include "config.h"
#include "game_window.h"
#include "projectile.h"
#include "raylib.h"
#include "sprite_loader.h"
#include "textures.h"
#include <stdbool.h>
#include <stdlib.h>

typedef struct Player {
  int health;
  Vector2 pos;
  float speed;
  // Speed acceleration
  bool isBoosted;
  Texture2D *sprite;
  // Last time the player shot the projectile
  float lastFireTime;
} Player;

Player *CreatePlayer(Textures *textures);
void UpdatePlayer(Player *player, GameWindow *gw, Projectile *projectiles);
void MovePlayer(Player *player, GameWindow *gw);
void DrawPlayer(const Player *player, GameWindow *gw);
void UpdatePlayerPosition(Player *player, Vector2 newPos);
Vector2 CalcInitPlayerPosition(GameWindow *gw, Player *player);
void PlayerShoot(Player *player, Projectile *projectiles);
void PlayerTakeDamage(Player *player, int damage);
void DrawPlayerHealth(const Player *player, GameWindow *gw);
void DestroyPlayer(Player *player);
