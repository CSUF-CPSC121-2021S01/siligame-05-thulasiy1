#include "game_element.h"
#include <iostream>
#include "cpputils/graphics/image.h"

bool GameElement::IntersectsWith(const GameElement &element) {
  int x = element.GetX();
  int y = element.GetY();
  int width = element.GetWidth();
  int height = element.GetHeight();
  if (x_ <= x + width && y_ <= y + height && x_ >= x && y_ >= y) {
    return true;
  } else if (x_ <= x + width && y_ + height_ <= y + height && x_ >= x &&
             y_ + height_ >= y) {
    return true;
  } else if (x_ + width_ <= x + width && y_ + height_ <= y + height &&
             x_ + width_ >= x && y_ + height_ >= y) {
    return true;
  } else if (x_ + width_ <= x + width && y_ <= y + height && x_ + width_ >= x &&
             y_ >= y) {
    return true;
  } else {
    return false;
  }
}

bool GameElement::IsOutOfBounds(const graphics::Image &element) {
  return !(element.GetWidth() > GetX() + GetWidth() && GetX() >= 0 &&
           element.GetHeight() > GetY() + GetHeight() && GetY() >= 0);
}
