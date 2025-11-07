#pragma once
#include "raylib.h"
#include "game_window.h"

typedef struct Star
{
  Vector2 position;
  Vector2 size;
  float speed;
} Star;

void InitBackgroundStars(GameWindow* gw);
void DrawBackgroundStars(GameWindow* gw);
void UpdateBackgroundStarsOnResize(GameWindow *gw);
void UpdateBackgroundStars(GameWindow *gw);
void DestronyStars();