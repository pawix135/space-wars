#pragma once
#include "game_window.h"
#include "raylib.h"

typedef struct Star {
  Vector2 position;
  Vector2 size;
  float speed;
} Star;

Star *InitBackgroundStars(GameWindow *gw);
void DrawBackgroundStars(Star *stars);
void UpdateBackgroundStarsOnResize(Star *stars, GameWindow *gw);
void UpdateBackgroundStars(Star *stars, GameWindow *gw, float dt);
void DestroyBackgroundStars(Star *stars);