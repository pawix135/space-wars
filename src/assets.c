#include "assets.h"
#include "raylib.h"
#include <stdlib.h>

Assets *InitializeAssets() {
  Assets *assets = (Assets *)malloc(sizeof(Assets));
  assets->sounds = InitializeSounds();
  assets->textures = LoadTextures();
  return assets;
}

void DestroyAssets(Assets *assets) {
  if (assets != NULL) {
    if (assets->sounds != NULL) DestroySounds(assets->sounds);
    if (assets->textures != NULL) DestroyTextures(assets->textures);

    free(assets);
    TraceLog(LOG_DEBUG, "Assets destroyed successfully.");
  }
}