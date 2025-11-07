#include <stdlib.h>
#include <stdio.h>
#include "config.h"
#include "background_stars.h"

Star* stars[BACKGROUND_STAR_COUNT] = {0};

void InitBackgroundStars(GameWindow* gw){
  for(int i = 0; i < BACKGROUND_STAR_COUNT; i++){
    stars[i] = (Star*)malloc(sizeof(Star));
    stars[i]->position = (Vector2){GetRandomValue(0, gw->windowW), GetRandomValue(0, gw->windowH)};
    stars[i]->speed = 50.0f;
    stars[i]->size = (Vector2){(int) GetRandomValue(1, 2), (int) GetRandomValue(1, 2)};
  }
}

void UpdateBackgroundStars(GameWindow *gw){
  float dt = GetFrameTime();
  for(int i = 0; i < BACKGROUND_STAR_COUNT; i++){
    stars[i]->position.y +=  stars[i]->speed * dt;
    if(stars[i]->position.y > gw->windowH){
      stars[i]->position.y = 0;
      stars[i]->position.x = GetRandomValue(0, gw->windowW);
    }
  }
}

void DrawBackgroundStars(GameWindow *gw){
  for(int i = 0; i < BACKGROUND_STAR_COUNT; i++){
    DrawRectangleV(stars[i]->position, stars[i]->size, (Color){ 255, 255, 255, 125});
  }
}

void DestronyStars(){
  for(int i = 0; i < BACKGROUND_STAR_COUNT; i++){
    if(stars[i] != NULL){
      free(stars[i]);
      stars[i] = NULL;
    }
  }
  printf("Background stars memory freed\n");
}