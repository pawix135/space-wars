#pragma once
#include "sounds.h"
#include "textures.h"

typedef struct Assets {
  Sounds *sounds;
  Textures *textures;
} Assets;

Assets *InitializeAssets();
void DestroyAssets(Assets *assets);