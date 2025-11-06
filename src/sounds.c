#include "sounds.h"
#include <stdio.h>
#include <stdlib.h>
#include "sound_loader.h"
#include "assets/shoot.h"

Sounds* InitializeSounds() {
  Sounds* sounds = (Sounds*)malloc(sizeof(Sounds));
  sounds->shootSound = LoadWavSound(shoot_wav, shoot_wav_len);
  return sounds;
}

void DestroySounds(Sounds *sounds) {
  if(sounds != NULL) {
    UnloadSound(sounds->shootSound);
    free(sounds);
    printf("Sounds memory freed\n");
  }
}