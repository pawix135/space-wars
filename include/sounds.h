#pragma once
#include "raylib.h"

typedef struct Sounds
{
  Sound shootSound;
} Sounds;

Sounds *InitializeSounds();
void DestroySounds(Sounds *sounds);