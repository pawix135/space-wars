#pragma once
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include "raylib.h"
#include "sprite_loader.h"
#include "game_window.h"

typedef struct Player
{
  int health;
  Vector2 pos;
  float speed;
  // Speed acceleration
  bool isBoosted;
  Texture2D sprite;
  // Last time the player shot the projectile
  float lastFireTime;
} Player;

Player *CreatePlayer();
void UpdatePlayer(Player* player, GameWindow* gw);
void MovePlayer(Player* player, GameWindow* gw);
void DrawPlayer(const Player *player);
void UpdatePlayerPosition(Player *player, Vector2 newPos);
Vector2 CalcInitPlayerPosition(GameWindow* gw, Player* player);
void PlayerShoot(Player *player, Sound *shootSound);
void PlayerTakeDamage(Player *player, int damage);
void DestroyPlayer(Player *player);
