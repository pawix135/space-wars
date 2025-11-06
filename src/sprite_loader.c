#include "sprite_loader.h"

Texture2D LoadSprite(const unsigned char *data, unsigned int dataSize){
  Image image = LoadImageFromMemory(".png", data, dataSize); 
  Texture2D texture = LoadTextureFromImage(image);
  UnloadImage(image);
  return texture;
}