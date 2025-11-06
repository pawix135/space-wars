#pragma once
#include <stdlib.h>
#include "raylib.h"
#include "sprite_loader.h"
#include <stdbool.h>
#include <stdio.h>

typedef struct Player{
  Vector2 pos;
  float speed;
  // Speed acceleration
  bool isBoosted;
  Texture2D sprite;
  // Last time the player shot the projectile
  float lastFireTime;
} Player;

Player* CreatePlayer();
void UpdatePlayer(Player* player, Sound* shootSound);
void MovePlayer(Player* player);
void DrawPlayer(const Player* player);
void PlayerShoot(Player* player, Sound* shootSound);
void DestroyPlayer(Player* player);
