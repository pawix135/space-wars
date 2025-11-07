#pragma once
#include "raylib.h"
#include "game_window.h"

typedef struct Star
{
  Vector2 position;
  Vector2 size;
  float speed;
} Star;

Star* InitBackgroundStars(GameWindow* gw);
void DrawBackgroundStars(Star* stars, GameWindow* gw);
void UpdateBackgroundStarsOnResize(Star* stars, GameWindow *gw);
void UpdateBackgroundStars(Star* stars, GameWindow *gw);
void DestroyBackgroundStars(Star* stars);