#include "menu.h"
#include "background_stars.h"
#include <stdbool.h>

Button startGameButton = {
  .baseColor = DARKGRAY,
  .hoverColor = GRAY,
  .rect = {0, 0, 200, 50},
  .text = "Start Game"
};

Button howToPlayButton = {.baseColor = DARKGRAY,
  .hoverColor = GRAY,
  .rect = {0, 0, 200, 50},
  .text = "How to Play"
};

Button exitButton = {
  .baseColor = RED,
  .hoverColor = DARKPURPLE,
  .rect = {0, 0, 200, 50},
  .text = "Exit"
};

void DrawMenu(Game *g) {
  Vector2 mousePoint = GetMousePosition();

  startGameButton.rect.x = (g->gw->windowW - startGameButton.rect.width) / 2;
  startGameButton.rect.y = g->gw->windowH / 2 - 80;

  howToPlayButton.rect.x = (g->gw->windowW - howToPlayButton.rect.width) / 2;
  howToPlayButton.rect.y = g->gw->windowH / 2;

  exitButton.rect.x = (g->gw->windowW - exitButton.rect.width) / 2;
  exitButton.rect.y = g->gw->windowH / 2 + 80;

  ClearBackground(BLACK);
  DrawBackgroundStars(g->stars);

  if (CheckButtonState(&startGameButton, mousePoint)) {
    RestartGame(g);
    ChangeScene(g->config, SCENE_GAMEPLAY);
  }

  if(CheckButtonState(&howToPlayButton, mousePoint)){
    ChangeScene(g->config, SCENE_HOWTOPLAY);
  }

  if (CheckButtonState(&exitButton, mousePoint)) {
    ExitGame(g->config);
  }

}