#pragma once
#include "raylib.h"
#include "sprite_loader.h"

typedef struct Textures
{
  Texture2D playerTexture;
  Texture2D enemyTexture;
} Textures;

Textures *LoadTextures();
void DestroyTextures(Textures *textures);