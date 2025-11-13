#include "sounds.h"
#include "assets/shoot.h"
#include "sound_loader.h"
#include <stdlib.h>

Sounds *InitializeSounds() {
  Sounds *sounds = (Sounds *)malloc(sizeof(Sounds));
  sounds->shootSound = LoadWavSound(shoot_wav, shoot_wav_len);
  return sounds;
}

void DestroySounds(Sounds *sounds) {
  if (sounds != NULL) {
    UnloadSound(sounds->shootSound);
    free(sounds);
    TraceLog(LOG_DEBUG, "Sounds destroyed.");
  }
}