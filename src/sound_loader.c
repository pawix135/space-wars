#include "sound_loader.h"

Sound LoadWavSound(const unsigned char *data, unsigned int dataSize){
  Wave wave_buffer = LoadWaveFromMemory(".wav", data, dataSize); 
  Sound sound = LoadSoundFromWave(wave_buffer);
  UnloadWave(wave_buffer);
  return sound;
}

Music LoadWavMusic(const unsigned char *data, unsigned int dataSize){
  Music music = LoadMusicStreamFromMemory(".wav", data, dataSize);
  return music;
}