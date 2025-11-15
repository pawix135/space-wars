#pragma once
#include "raylib.h"

typedef struct Sounds
{
  Music backgroundSong;
} Sounds;

Sounds *InitializeSounds();
void DestroySounds(Sounds *sounds);