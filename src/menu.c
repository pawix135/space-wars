#include "menu.h"
#include "background_stars.h"
#include <stdbool.h>

Button startGameButton = {.baseColor = DARKGRAY,
                          .hoverColor = GRAY,
                          .rect = {0, 0, 200, 50},
                          .text = "Start Game"};

Button optionButton = {.baseColor = DARKGRAY,
                       .hoverColor = GRAY,
                       .rect = {0, 0, 200, 50},
                       .text = "Options"};

Button exitButton = {.baseColor = RED,
                     .hoverColor = DARKPURPLE,
                     .rect = {0, 0, 200, 50},
                     .text = "Exit"};

void DrawMenu(GameConfig *config, Star *stars, GameWindow *gw) {
  Vector2 mousePoint = GetMousePosition();

  // Center buttons
  startGameButton.rect.x = (gw->windowW - startGameButton.rect.width) / 2;
  startGameButton.rect.y = gw->windowH / 2 - 80;

  optionButton.rect.x = (gw->windowW - optionButton.rect.width) / 2;
  optionButton.rect.y = gw->windowH / 2;

  exitButton.rect.x = (gw->windowW - exitButton.rect.width) / 2;
  exitButton.rect.y = gw->windowH / 2 + 80;

  UpdateBackgroundStars(stars, gw, config->deltaTime);

  BeginDrawing();
  ClearBackground(BLACK);
  DrawBackgroundStars(stars);

  if (CheckButtonState(&startGameButton, mousePoint)) {
    ChangeScene(config, SCENE_GAMEPLAY);
  }

  CheckButtonState(&optionButton, mousePoint);

  if (CheckButtonState(&exitButton, mousePoint)) {
    ExitGame(config);
  }

  EndDrawing();
}

bool CheckButtonState(Button *btn, Vector2 mousePoint) {

  if (CheckCollisionPointRec(mousePoint, btn->rect)) {

    DrawRectangleRec(btn->rect, btn->hoverColor);
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
      return true;
    }
  } else {
    DrawRectangleRec(btn->rect, btn->baseColor);
  }

  int textWidth = MeasureText(btn->text, 20);
  DrawText(btn->text,
           (int)(btn->rect.x + (btn->rect.width / 2) - (textWidth / 2)),
           (int)(btn->rect.y + (btn->rect.height / 2) - 10), 20, WHITE);

  return false;
}