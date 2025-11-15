#include "sounds.h"
#include "extern_resources.h"
#include "sound_loader.h"
#include <stdlib.h>

Sounds *InitializeSounds() {
  Sounds *sounds = (Sounds *)malloc(sizeof(Sounds));
  sounds->backgroundSong = LoadWavMusic(song_wav, song_wav_len);
  return sounds;
}

void DestroySounds(Sounds *sounds) {
  if (sounds != NULL) {
    UnloadMusicStream(sounds->backgroundSong);
    free(sounds);
    TraceLog(LOG_DEBUG, "Sounds destroyed.");
  }
}