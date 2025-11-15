#pragma once
#include "raylib.h"

Sound LoadWavSound(const unsigned char *data, unsigned int dataSize);
Music LoadWavMusic(const unsigned char *data, unsigned int dataSize);