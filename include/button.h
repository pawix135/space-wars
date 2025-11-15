#pragma once
#include "raylib.h"

typedef struct {
  Rectangle rect;
  Color baseColor;
  Color hoverColor;
  const char *text;
} Button;

bool CheckButtonState(Button *btn, Vector2 mousePoint);
