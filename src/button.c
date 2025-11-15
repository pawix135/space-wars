#include "button.h"

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