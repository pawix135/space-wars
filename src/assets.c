#include "assets.h"
#include "raylib.h"
#include <stdlib.h>
#include "extern_resources.h"

Assets *InitializeAssets() {
  Assets *assets = (Assets *)malloc(sizeof(Assets));
  assets->sounds = InitializeSounds();
  assets->textures = LoadTextures();
  assets->iconImage = LoadImageFromMemory(".png", icon_png, icon_png_len);
  return assets;
}

void DestroyAssets(Assets *assets) {
  if (assets != NULL) {
    if (assets->sounds != NULL) DestroySounds(assets->sounds);
    if (assets->textures != NULL) DestroyTextures(assets->textures);
    UnloadImage(assets->iconImage);

    free(assets);
    TraceLog(LOG_DEBUG, "Assets destroyed successfully.");
  }
}