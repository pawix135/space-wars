#pragma once
#include "game.h"
#include "game_config.h"
#include "raylib.h"
#include "scene_manager.h"

typedef struct {
  Rectangle rect;
  Color baseColor;
  Color hoverColor;
  const char *text;
} Button;

void DrawMenu(GameConfig *config, Star *stars, GameWindow *gw);
bool CheckButtonState(Button *btn, Vector2 mousePoint);