#include "textures.h"
#include "extern_resources.h"
#include <stdlib.h>

Textures *LoadTextures() {
  Textures *textures = (Textures *)malloc(sizeof(Textures));
  textures->playerTexture = LoadSprite(ship_A_png, ship_A_png_len);
  textures->enemyTexture = LoadSprite(enemy_1_png, enemy_1_png_len);
  textures->missileTexture = LoadSprite(missile_01_png, missile_01_png_len);
  return textures;
}

void DestroyTextures(Textures *textures) {
  if (textures != NULL) {
    UnloadTexture(textures->playerTexture);
    UnloadTexture(textures->enemyTexture);
    UnloadTexture(textures->missileTexture);
    free(textures);
    TraceLog(LOG_DEBUG, "Textures destroyed.");
  }
}