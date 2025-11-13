#include "background_stars.h"
#include "config.h"
#include <stdlib.h>

Star *InitBackgroundStars(GameWindow *gw) {
  Star *stars = (Star *)malloc(sizeof(Star) * BACKGROUND_STAR_COUNT);
  if (stars == NULL) {
    return NULL;
  }

  for (int i = 0; i < BACKGROUND_STAR_COUNT; i++) {
    stars[i].position = (Vector2){GetRandomValue(0, gw->windowW),
                                  GetRandomValue(0, gw->windowH)};
    stars[i].speed = 50.0f;
    stars[i].size =
        (Vector2){(int)GetRandomValue(1, 2), (int)GetRandomValue(1, 2)};
  }
  return stars;
}

void UpdateBackgroundStarsOnResize(Star *stars, GameWindow *gw) {
  for (int i = 0; i < BACKGROUND_STAR_COUNT; i++) {
    stars[i].position = (Vector2){GetRandomValue(0, gw->windowW),
                                  GetRandomValue(0, gw->windowH)};
    stars[i].size =
        (Vector2){(int)GetRandomValue(1, 2), (int)GetRandomValue(1, 2)};
  }
}

void UpdateBackgroundStars(Star *stars, GameWindow *gw, float dt) {
  for (int i = 0; i < BACKGROUND_STAR_COUNT; i++) {
    stars[i].position.y += stars[i].speed * dt;
    if (stars[i].position.y > gw->windowH) {
      stars[i].position.y = 0;
      stars[i].position.x = GetRandomValue(0, gw->windowW);
    }
  }
}

void DrawBackgroundStars(Star *stars) {
  for (int i = 0; i < BACKGROUND_STAR_COUNT; i++) {
    DrawRectangleV(stars[i].position, stars[i].size,
                   (Color){255, 255, 255, GetRandomValue(50, 255)});
  }
}

void DestroyBackgroundStars(Star *stars) {
  if (stars != NULL) {
    free(stars);
    TraceLog(LOG_DEBUG, "Background Stars destroyed.");
  }
}