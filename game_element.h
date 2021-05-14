#ifndef GAME_ELEMENT_H
#define GAME_ELEMENT_H

#include <iostream>
#include "cpputils/graphics/image.h"

class GameElement {
 public:
  GameElement() : GameElement(0, 0, 50, 50) {}
  GameElement(int x, int y, int width, int height)
      : x_(x), y_(y), width_(width), height_(height) {}
  void SetX(int x) { x_ = x; }
  void SetY(int y) { y_ = y; }
  int GetX() const { return x_; }
  int GetY() const { return y_; }
  int GetWidth() const { return width_; }
  int GetHeight() const { return height_; }

  virtual void Draw(graphics::Image& image) = 0;

  void SetIsActive(bool is_active) { is_active_ = is_active; }
  bool GetIsActive() { return is_active_; }

  virtual void Move(const graphics::Image& picture) = 0;
  bool IntersectsWith(const GameElement& game_element);
  bool IsOutOfBounds(const graphics::Image& game_element);

 protected:
  int x_;
  int y_;
  int width_;
  int height_;
  bool is_active_ = true;
};

#endif  // GAME_ELEMENT_H
