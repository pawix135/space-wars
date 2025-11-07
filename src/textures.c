#include "textures.h"
#include "assets.h"
#include <stdlib.h>
#include <stdio.h>

Textures *LoadTextures(){
  Textures* textures = (Textures*)malloc(sizeof(Textures));
  textures->playerTexture = LoadSprite(ship_A_png, ship_A_png_len);
  textures->enemyTexture = LoadSprite(enemy_1_png, enemy_1_png_len);
  return textures;
}

void DestroyTextures(Textures *textures){
  if(textures != NULL){
    UnloadTexture(textures->playerTexture);
    UnloadTexture(textures->enemyTexture);
    free(textures);
    printf("Textures memory freed\n");
  }
}